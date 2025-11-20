/*
This file defines the input logic: buttons, switches and timer. Note: All functions taken from lab3 code, some with adjustments

-

Author: Sofia Mohamed
*/

#include "input.h"

//Function for getting all the state of all the 10 switches
int get_sw(void){
  volatile int *sw = (volatile int*)0x04000010;
  int value = *sw;
  value = value & 0x3FF;
  return value;
}

//Function for getting the state of switch 9 (player 1 switch)
int get_player1(void){ 
  int player1 = (get_sw() >> 9) & 0x01;
  return player1;
}

//Function for getting the state of switch 0 (player 2 switch)
int get_player2(void){ 
  int player2 = get_sw() & 0x01;
  return player2;
}

//Function for getting the state of button 2 (KEY1)
int get_button(void){
  volatile int *button = (volatile int*)0x040000d0;
  int value = *button;
  value = value & 0x01;
  return value;
}

//Function for initializing the timer
void initialize_timer(void){
  volatile int *periodL = (volatile int*)0x04000028;
  volatile int *periodH = (volatile int*)0x0400002C;
  volatile int *control = (volatile int*)0x04000024;

  *periodL = 0x8000; 
  *periodH = 0x0004; //together the period is 294,912
  *control = 0x0006; 

}

//Function for checking the timer status flag
int check_timer_status(void){
  volatile int *status = (volatile int*)0x04000020;
  int value = *status & 0x1;
  if(value){
    *status = 0;
    return 1;
  }
  return 0;
}

//Function for creating a simple delay (waits for a certain number of timer triggers)
void game_delay(int delay){
  int count = 0;
  while(count < delay){
    if(check_timer_status()){
      count++;
    }
  }
}

void handle_interrupt(void){
}
