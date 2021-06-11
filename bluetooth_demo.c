/***************************************************
 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 08-Jul-2020
 Filename		: bluetooth_demo.c
 Purpose		: Bluetooth Demo
 Description		:  Bluetooth Demo with uart interface
 Author(s)		: Premjith A V
 Email			: premjith@cdac.in

 See LICENSE for license details.
 ***************************************************/
/**
 @file bluetooth_demo.c
 @brief Contains routines for demonstrates the bluetooth sensor communication
 */
 
/*  Include section
 ***************************************************/

#include "uart.h"
#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include <string.h>
#include "pwmc.h"

#define SYS_CLK_FREQ 40000000UL
#define DISABLE 0
#define ENABLE 1

#define LEFT_A 3
#define LEFT_B 4

#define RIGHT_A 5
#define RIGHT_B 6

#define LEFT_EN 7
#define RIGHT_EN 8



void start(void){
	GPIO_write_pin(LEFT_EN,ENABLE);
	GPIO_write_pin(RIGHT_EN,ENABLE);
}
void stop(void){
	GPIO_write_pin(LEFT_EN,DISABLE);
	GPIO_write_pin(RIGHT_EN,DISABLE);
}
void initRobot(void){
	stop();
	GPIO_write_pin(LEFT_A,DISABLE);
	GPIO_write_pin(LEFT_B,DISABLE);
	GPIO_write_pin(RIGHT_A,DISABLE);
	GPIO_write_pin(RIGHT_B,DISABLE);
	start();
}

void moveForward(){
	//stop();
	//udelay(100);
	GPIO_write_pin(LEFT_A,ENABLE);
	GPIO_write_pin(LEFT_B,DISABLE);
	GPIO_write_pin(RIGHT_A,ENABLE);
	GPIO_write_pin(RIGHT_B,DISABLE);
	printf("FORWARD\n");
	
}

void moveBack(){
	//stop();
	//udelay(100);
	GPIO_write_pin(LEFT_A,DISABLE);
	GPIO_write_pin(LEFT_B,ENABLE);
	GPIO_write_pin(RIGHT_A,DISABLE);
	GPIO_write_pin(RIGHT_B,ENABLE);
	printf("BACK\n");
}

void moveRight(){
	//stop();
	//udelay(100);
	GPIO_write_pin(LEFT_A,ENABLE);
	GPIO_write_pin(LEFT_B,DISABLE);
	GPIO_write_pin(RIGHT_A,DISABLE);
	GPIO_write_pin(RIGHT_B,ENABLE);
	printf("RIGHT\n");
}

void moveLeft(){
	//stop();
	//udelay(100);
	GPIO_write_pin(LEFT_A,DISABLE);
	GPIO_write_pin(LEFT_B,ENABLE);
	GPIO_write_pin(RIGHT_A,ENABLE);
	GPIO_write_pin(RIGHT_B,DISABLE);
	printf("LEFT\n");
}

void moveHalt(){
	GPIO_write_pin(LEFT_A,DISABLE);
	GPIO_write_pin(LEFT_B,DISABLE);
	GPIO_write_pin(RIGHT_A,DISABLE);
	GPIO_write_pin(RIGHT_B,DISABLE);
	printf("STOP\n");
}


int send_string(char * str)
{
char error;
  while(*str!='\0'){
	 uart_putchar(UART_1,*str, &error);
	if(*str=='\n')
	 uart_putchar(UART_1,'\r', &error);
	str++;
  }
  return 0;
}

void receive_string(char * str)
{
  char error;  
  char data;

  while(1){
	 data = uart_getchar(UART_1, &error);	
	 *str=data;
	  str++;
	 if(data=='\n'){	
	 *str='\r';	
	 break;
	}	
  }
}



/**
 @fn main
 @brief transmit and reception through uart
 @details 1 character is transmitted and received through uart
 @param[in] No input parameter.
 @param[Out] No ouput parameter.
 @return Void function.

 */
void main() {
	char error;       
	char str[100]={0,};

	printf("\n\r *****************************************************************************");
	printf("\n\r INFO: Connect HC-05 Bluetooth module to UART 1 ");	
	printf("\n\r INFO: Please try to connect the Bluetooth device 'HC-05'");	
	printf("\n\r INFO: Press the 'SCAN' button in VEGA bluetooth App from your Android phone");	
	printf("\n\r *****************************************************************************");

	printf("\n\r Setting up Bluetooth Device \n\r");
	uart_set_baud_rate(UART_1,9600,40000000);
	start();

while(1){
		memset(str,0,sizeof(str));
		receive_string(str);	
		printf("%s", str);
		/*if(strncmp(str,"ON",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			send_string("LED ON\n");
		}
		else
		{
			send_string("LED OFF\n");
			GPIO_write_pin(22,OFF_LED);
		}*/
	
		if(strncmp(str,"F",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			//moveForward();                //this function is not getting executed
			GPIO_write_pin(LEFT_A,ENABLE);
			GPIO_write_pin(LEFT_B,DISABLE);
			GPIO_write_pin(RIGHT_A,ENABLE);
			GPIO_write_pin(RIGHT_B,DISABLE);
			send_string("FORWARD\n"); //even these lines are too not getting executed
			send_string("F\n"); //F GETS PRINTED WHEN F BUTTON ON THE BLUETOOTH APP IS PRESSED.
		}
		else if(strncmp(str,"L",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			moveLeft();
			send_string("L\n");
		}
		else if(strncmp(str,"R",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			moveRight();
			send_string("R\n");
		}
		esle if(strncmp(str,"B",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			moveBack();
			send_string("B\n");
		}
		else if (strncmp(str,"S",2)==0)
		{	
			GPIO_write_pin(22,ON_LED);
			moveHalt();
			send_string("S\n");
		}
		else
		{
			send_string("S\n");
			moveHalt();
			GPIO_write_pin(22,OFF_LED);
			
		}	
		
	}
	
	
}

