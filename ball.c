/*
This file defines functions for the ball

- 

Author: Viola Bordbar
*/

#include "ball.h"
#include "game_constants.h"
#include "font.h"
#include "draw.h"

int ball_x = 0;
int ball_y = 0; 
int x_step = 1; 
int y_step = 1; 
int first_hit = 1;

/*This function makes the ball move */
void ball_movement(void){
    //makes the ball move slower by using a static delay variable
    static int move_delay = 0;
    move_delay++;
    if(move_delay < 1){
        return;
    }
    move_delay = 0;

    //defines the movement of the ball in x-y coordinates
    ball_x += x_step *1.2;
    ball_y += y_step *1.2;

    //bounce on top and bottom edges
    if(ball_y <= 0 || ball_y + BALL_SIZE >= SCREEN_HEIGHT){
        y_step = -y_step;
    }
}

/*Function for checking if the ball has collided/hit oneof the paddles*/
int check_paddle_collision(int paddle1_y, int paddle2_y){
    //Returns 1 if player 1 missed and 2 if player 2 missed
    if(ball_x < 0) return 1;  
    if(ball_x + BALL_SIZE >= SCREEN_WIDTH) return 2;

    //Checks if the ball collided with the left paddle by checking if the balls x position overlaps 
    //the paddle's width and if the balls y position overlaps the paddle's height
    if(ball_x <= PADDLE1_X + PADDLE_WIDTH && ball_x >= PADDLE1_X && 
    ball_y + BALL_SIZE >= paddle1_y && ball_y <= paddle1_y + PADDLE_HEIGHT){

        ball_x = PADDLE1_X + PADDLE_WIDTH + 1;
        x_step = 1;

        //only change the balls direction/angle when its not the first "serve" of the game
        if (!first_hit) change_ball_direction(paddle1_y);
    } 

    //same as if statement above but for opposite side (collision with right paddle)
    else if(ball_x + BALL_SIZE >= PADDLE2_X && ball_x + BALL_SIZE <= PADDLE2_X + PADDLE_WIDTH &&
    ball_y + BALL_SIZE >= paddle2_y && ball_y <= paddle2_y + PADDLE_HEIGHT ){

        ball_x = PADDLE2_X - BALL_SIZE - 1;
        x_step = -1;

        if (!first_hit) change_ball_direction(paddle2_y);
    }
    if(first_hit) first_hit = 0;
    //return 0 if no one misses/a collision happened
    return 0;
}


/*Function for making the ball move in different angles depending on where the ball hits the paddle*/
void change_ball_direction(int paddle_y){
    int distance = ball_y - paddle_y;
    //divide the paddle into 5 segments
    int paddle_segment = PADDLE_HEIGHT / 5;
    int segment = distance / paddle_segment;
    //change the angle depending on which segment was hit
    y_step = segment -0.5;
}