/**
 ******************************************************************************
 * @file           : main.h
 * @author         : E. Versteeg @ Imagine Solutions BV
 * @brief          : Main header file
 ******************************************************************************
 */
// LEDS:
// LD1 COM default is red, turn on green of communications are in progress PC => board
// LD2 PWR is red when powered
// User LD3 orange LED is a user LED connected to the I/O PD13
// User LD4 green LED is a user LED connected to the I/O PD12
// User LD5 red LED is a user LED connected to the I/O PD14
// User LD6 blue LED is a user LED connected to the I/O PD15
// User LD7 green LED indicates when Vbus s present on CN5 and is connected to the I/O PA9
// User LD8 red LED indicates overcurrent from Vbus of CN5 nd is connected to the IO PD5


// GPIOA
// GPIOB
// GPIOC
// GPIOD
// GPIOE
// GPIOF
// GPIOG
// GPIOH
// GPIOI

#include<stdint.h>
#include<stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
