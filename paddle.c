/*
This file defines the function for how the paddles should move based on the switch states 

-

Author: Viola Bordbar
*/

#include "paddle.h"
#include "input.h"
#include "game_constants.h"

//Function for moving the paddles up and down depending on if the switches are on or off
void paddle_movement(int *paddle_y, int sw_state){
    if(sw_state == 1 && *paddle_y > 0){
        *paddle_y -= PADDLE_STEP;
    }
    else if(sw_state == 0 && *paddle_y + PADDLE_HEIGHT < SCREEN_HEIGHT){
        *paddle_y += PADDLE_STEP;
    }

    if(*paddle_y < 0) *paddle_y = 0;  // if paddle_y is less than 0, stop at top of the screen (at 0)
    if(*paddle_y + PADDLE_HEIGHT > SCREEN_HEIGHT) *paddle_y = SCREEN_HEIGHT - PADDLE_HEIGHT; 
}
