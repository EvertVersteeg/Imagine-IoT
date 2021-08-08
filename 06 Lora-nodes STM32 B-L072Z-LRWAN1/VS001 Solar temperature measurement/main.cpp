/**
 * Copyright (c) 2017, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include "lorawan/LoRaWANInterface.h"
#include "lorawan/system/lorawan_data_structures.h"
#include "events/EventQueue.h"
#include "trace_helper.h"
#include "lora_radio_helper.h"
#include "mbed.h"
#include "MAX31865.h"
#include "CayenneLPP.h"


// Setup serial interface (Arduino)
//Serial pc(SERIAL_TX, SERIAL_RX);
// Setup RTD SPI interface, PT100 Miso Mosi CLK en Slave select
MAX31865_RTD rtd1(MAX31865_RTD::RTD_PT100,D11, D12, D13, D10);
MAX31865_RTD rtd2(MAX31865_RTD::RTD_PT100,D11, D12, D13, D9);

// Setup IO
AnalogIn lm35s1(A0);  
AnalogIn lm35s2(A1);

DigitalOut ledTest(LED1);

using namespace events;

// Max payload size can be LORAMAC_PHY_MAXPAYLOAD.
// This example only communicates with much shorter messages (<30 bytes).
// If longer messages are used, these buffers must be changed accordingly.
uint8_t tx_buffer[30] = {};
uint8_t rx_buffer[30] = {};


/*
 * Sets up an application dependent transmission timer in ms. Used only when Duty Cycling is off for testing
 */
#define TX_TIMER                        300000

/**
 * Maximum number of events for the event queue.
 * 10 is the safe number for the stack events, however, if application
 * also uses the queue for whatever purposes, this number should be increased.
 */
#define MAX_NUMBER_OF_EVENTS            10

/**
 * Maximum number of retries for CONFIRMED messages before giving up
 */
#define CONFIRMED_MSG_RETRY_COUNTER     3

// Setup Cayenne

CayenneLPP cayenne(100);

/**
* This event queue is the global event queue for both the
* application and stack. To conserve memory, the stack is designed to run
* in the same thread as the application and the application is responsible for
* providing an event queue to the stack that will be used for ISR deferment as
* well as application information event queuing.
*/
static EventQueue ev_queue(MAX_NUMBER_OF_EVENTS *EVENTS_EVENT_SIZE);

/**
 * Event handler.
 *
 * This will be passed to the LoRaWAN stack to queue events for the
 * application which in turn drive the application.
 */
static void lora_event_handler(lorawan_event_t event);

/**
 * Constructing Mbed LoRaWANInterface and passing it the radio object from lora_radio_helper.
 */
static LoRaWANInterface lorawan(radio);

/**
 * Application specific callbacks
 */
static lorawan_app_callbacks_t callbacks;

/**
 * Entry point for application
 */
int main(void)
{
    // setup tracing
    setup_trace();

    // stores the status of a call to LoRaWAN protocol
    lorawan_status_t retcode;

    // Initialize LoRaWAN stack
    if (lorawan.initialize(&ev_queue) != LORAWAN_STATUS_OK) {
        printf("\r\n LoRa initialization failed! \r\n");
        return -1;
    }

    printf("\r\n Mbed LoRaWANStack initialized \r\n");

    // prepare application callbacks
    callbacks.events = mbed::callback(lora_event_handler);
    lorawan.add_app_callbacks(&callbacks);

    // Set number of retries in case of CONFIRMED messages
    if (lorawan.set_confirmed_msg_retries(CONFIRMED_MSG_RETRY_COUNTER)
            != LORAWAN_STATUS_OK) {
        printf("\r\n set_confirmed_msg_retries failed! \r\n\r\n");
        return -1;
    }

    printf("\r\n CONFIRMED message retries : %d \r\n",
           CONFIRMED_MSG_RETRY_COUNTER);

    // Enable adaptive data rate
    if (lorawan.enable_adaptive_datarate() != LORAWAN_STATUS_OK) {
        printf("\r\n enable_adaptive_datarate failed! \r\n");
        return -1;
    }

    printf("\r\n Adaptive data  rate (ADR) - Enabled \r\n");

    retcode = lorawan.connect();

    if (retcode == LORAWAN_STATUS_OK ||
            retcode == LORAWAN_STATUS_CONNECT_IN_PROGRESS) {
    } else {
        printf("\r\n Connection error, code = %d \r\n", retcode);
        return -1;
    }

    printf("\r\n Connection - In Progress ...\r\n");

    // make your event queue dispatching events forever
    ev_queue.dispatch_forever();

    return 0;
}

/**
 * Sends a message to the Network Server
 */
static void send_message()
{
    uint16_t packet_len;
    int16_t retcode;
    float tempLM35s1;
    float tempLM35s2;
    printf("\r\n *********************************** \r\n");
    
    tempLM35s1=lm35s1.read()*330.0;
    printf("\r\n Temperature value 1 LM35 : %3.2f C\r\n", tempLM35s1);
    tempLM35s2=lm35s2.read()*330.0;
    printf("\r\n Temperature value 2 LM35 : %3.2f C\r\n", tempLM35s2);

    rtd1.configure( true, true, false, true, MAX31865_FAULT_DETECTION_NONE,true, true, 0x0000, 0x7fff );
    wait(0.5);
    if( rtd1.status( ) != 0 ) {
        printf( "\r\n Status 1: ERROR!! \r\n");}
    rtd1.read_all( );
    wait(0.5);
    

    
    wait(0.5);
    rtd2.configure( true, true, false, true, MAX31865_FAULT_DETECTION_NONE,true, true, 0x0000, 0x7fff );
    wait(0.5);
    if( rtd2.status( ) != 0 ) {
        printf( "\r\n Status 2: ERROR!! \r\n");}
    rtd2.read_all( );
    wait(0.5);
    
    
    double temperature1 = rtd1.temperature( );
    printf("\r\n PT100-1 Sensor Value = %f \r\n", temperature1);
    double resistance1 = rtd1.resistance( );
    printf("\r\n PT100-1 Resistance Value = %f \r\n", resistance1);
    uint16_t low_threshold1 = rtd1.low_threshold( );
    printf("\r\n PT100-1 Low_threshold Value = %d \r\n", low_threshold1);
    uint16_t high_threshold1 = rtd1.high_threshold( );
    printf("\r\n PT100-1 High_threshold Value = %d \r\n", high_threshold1);
    double temperature2 = rtd2.temperature( );
    printf("\r\n PT100-2 Sensor Value = %f \r\n", temperature2);
    double resistance2 = rtd2.resistance( );
    printf("\r\n PT100-2 Resistance Value = %f \r\n", resistance2);
    uint16_t low_threshold2 = rtd2.low_threshold( );
    printf("\r\n PT100-2 Low_threshold Value = %d \r\n", low_threshold2);
    uint16_t high_threshold2 = rtd2.high_threshold( );
    printf("\r\n PT100-2 High_threshold Value = %d \r\n", high_threshold2);
    printf("\r\n *********************************** \r\n");
    
    

    // packet_len = sprintf((char *) tx_buffer, "%f ; %f",temperature1, resistance1);
    cayenne.reset();

    cayenne.addTemperature(1, temperature1);
    cayenne.addAnalogInput(2, resistance1);
    cayenne.addTemperature(3, temperature2);
    cayenne.addAnalogInput(4, resistance2);
    cayenne.addTemperature(5, tempLM35s1);
    cayenne.addTemperature(6, tempLM35s2);
    cayenne.copy(tx_buffer);
    packet_len=cayenne.getSize();
    printf("Inhoud pakket : \n\r");
    for (int i=0;i<packet_len;i++) printf("%02X ",tx_buffer[i]);
    printf("\n\r");

    retcode = lorawan.send(MBED_CONF_LORA_APP_PORT, tx_buffer, packet_len,
                           MSG_UNCONFIRMED_FLAG);

    if (retcode < 0) {
        retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - WOULD BLOCK\r\n")
        : printf("\r\n send() - Error code %d \r\n", retcode);

        if (retcode == LORAWAN_STATUS_WOULD_BLOCK) {
            //retry in 3 seconds
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                ev_queue.call_in(3000, send_message);
            }
        }
        return;
    }

    printf("\r\n %d bytes scheduled for transmission \r\n", retcode);
    memset(tx_buffer, 0, sizeof(tx_buffer));
}

/**
 * Receive a message from the Network Server
 */
static void receive_message()
{
    int16_t retcode;
    uint8_t port; // var to store port number provided by the stack
    int flags; // var to store flags provided by the stack
    retcode = lorawan.receive( rx_buffer,sizeof(rx_buffer), port, flags);
    printf("\x1B[1m");  // yellow text
    if (retcode < 0) {
        printf("receive() - Error code %d \r\n", retcode);
        return;
    }
    printf(" Reception on port : %d \n",port);
    printf(" Flags are : %d \n",flags);
    printf(" Data: ");
 
    for (uint8_t i = 0; i < retcode; i++) {
        printf("%02X ", rx_buffer[i]);
    }
 
    printf("\n\r Data Length: %d\r\n", retcode);
    printf("\x1B[0m");  // white text
    printf("End reception\n\r");
 
    if (rx_buffer[0]==0x01) ledTest=1;
    if (rx_buffer[0]==0x00) ledTest=0;
    printf("\n\r Buffer ledtest: %d\r\n", rx_buffer[0]);
    
    memset(rx_buffer, 0, sizeof(rx_buffer));
}

/**
 * Event handler
 */
static void lora_event_handler(lorawan_event_t event)
{
    switch (event) {
        case CONNECTED:
            printf("\r\n Connection - Successful \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            } else {
                ev_queue.call_every(TX_TIMER, send_message);
            }

            break;
        case DISCONNECTED:
            ev_queue.break_dispatch();
            printf("\r\n Disconnected Successfully \r\n");
            break;
        case TX_DONE:
            printf("\r\n Message Sent to Network Server \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        case TX_TIMEOUT:
        case TX_ERROR:
        case TX_CRYPTO_ERROR:
        case TX_SCHEDULING_ERROR:
            printf("\r\n Transmission Error - EventCode = %d \r\n", event);
            // try again
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        case RX_DONE:
            printf("\r\n Received message from Network Server \r\n");
            receive_message();
            break;
        case RX_TIMEOUT:
        case RX_ERROR:
            printf("\r\n Error in reception - Code = %d \r\n", event);
            break;
        case JOIN_FAILURE:
            printf("\r\n OTAA Failed - Check Keys \r\n");
            break;
        case UPLINK_REQUIRED:
            printf("\r\n Uplink required by NS \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        default:
            MBED_ASSERT("Unknown Event");
    }
}

// EOF
