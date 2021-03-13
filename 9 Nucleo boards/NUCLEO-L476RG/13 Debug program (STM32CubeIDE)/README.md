# Imagine-IoT

#### Debug:
* NUCLEO-L476RG
* Toolchain: CubeIDE
* CUBE MX: Default board settings (80MHZ)
* debug header file to send txt, int, float etc. to computer using serial com.
* Select USART2 under tab Connectivity and set its Mde to Asynchronous
* In Parameter Settings, set the Baud Rate to 9600, Word Lenght to 8, Parity to None, and Stop Bits to 1
* Configure the MCO for 80MHz clock.
* Use Tera Term to connect to the board, find the port (windows 10) under +.
* Start => Control Panel => System => Device Manager => 
* Click to expand Ports (COM & LPT) and check the STMMicroeectronics STLink Virtual Com Port number (after connecting the board)