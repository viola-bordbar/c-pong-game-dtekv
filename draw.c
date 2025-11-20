/*
This file defines functions to draw game components and text to the VGA display

-

Author: Sofia Mohamed
*/

#include "font.h"
#include "game_constants.h"
#include "draw.h"

volatile char* VGA = (volatile char*)0x08000000;
volatile int *VGA_CTRL = (volatile int*)0x04000100;

extern int player1_lives;
extern int player2_lives;
extern int paddle1_y;
extern int paddle2_y;

int prev_paddle1_y = 0;
int prev_paddle2_y = 0;
int prev_ball_x = 0;
int prev_ball_y =0;

/*Below are functions for drawing game components and visual screen handling (ball, paddles, clearing screen, drawing and clearing pixels)*/


//initializes VGA control
void initialize_VGA(void){
    VGA_CTRL[1] = (unsigned int)VGA;
    VGA_CTRL[0] = 0;
}

// clears the screen by looping through all the screen's pixels and setting them to 0
void clear_screen(void){
    for(int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++){
        VGA[i] = 0;
    }
}

// draws a pixel on the screen based on a given x and y coordinate 
void draw_pixel(int pixel_x, int pixel_y){
    VGA[pixel_y * SCREEN_WIDTH + pixel_x] = WHITE;
}

//clears a pixel by setting it to 0
void clear_pixel(int pixel_x, int pixel_y){
    VGA[pixel_y * SCREEN_WIDTH + pixel_x] = CLEAR;
}

//with nested loops, the previous paddles are first cleared and then new ones are drawn 
//so it updates correctly (nested loops because of height and width of paddle)
void draw_paddles(void){

     for(int i = prev_paddle1_y; i <= prev_paddle1_y + PADDLE_HEIGHT; i++){
        for(int j = 0; j < PADDLE_WIDTH; j++){
            clear_pixel(PADDLE1_X + j, i);
        }
    }

    for(int i = prev_paddle2_y; i <= prev_paddle2_y + PADDLE_HEIGHT; i++){
        for(int j = 0; j < PADDLE_WIDTH; j++){  
          clear_pixel(PADDLE2_X + j, i);
        }
    }

    for(int i = paddle1_y; i < paddle1_y + PADDLE_HEIGHT; i++){
        for(int j = 0; j < PADDLE_WIDTH; j++){
            draw_pixel(PADDLE1_X + j, i);
        }
    }

    for(int i = paddle2_y; i <= paddle2_y + PADDLE_HEIGHT; i++){
        for(int j = 0; j < PADDLE_WIDTH; j++){  
            draw_pixel(PADDLE2_X + j, i);
        }
    }

    prev_paddle1_y = paddle1_y; //updates the old position so it knows where to clear next
    prev_paddle2_y = paddle2_y;
}

//Also clears previous ball and then draws a new one (just like the function for drawing paddles)
void draw_ball(int x, int y, int size){
     for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            clear_pixel(prev_ball_x + j, prev_ball_y + i);
        }
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            draw_pixel(x + j, y + i);
        }
    }

    prev_ball_x = x;
    prev_ball_y = y;
}

//Function for drawing letters or symbols (nested loops iterating through a 
//"matrix" so it can later be filled with values to form symbols/letters)
void draw_char(int x, int y, unsigned char letter[7]){
    for (int row = 0; row < 7; row++) {
        unsigned char line = letter[row];
        for (int col = 0; col < 5; col++) {
            if ((line >> (4 - col)) & 1) {
                for (int i = 0; i < FONT_SCALE; i++) {
                    for (int j = 0; j < FONT_SCALE; j++) {
                        draw_pixel(x + col * FONT_SCALE + j, y + row * FONT_SCALE + i);
                    }
                }
            }
        }
    }
}

/*Below are functions for drawing the wanted words and symbols on the display*/

void draw_game_over_screen(void){
    clear_screen(); 

    draw_char(100, 80, letter_G);
    draw_char(112, 80, letter_A);
    draw_char(124, 80, letter_M);
    draw_char(136, 80, letter_E);

    draw_char(162, 80, letter_O);
    draw_char(174, 80, letter_V);
    draw_char(188, 80, letter_E);
    draw_char(200, 80, letter_R);

    draw_char(20, 100, letter_P);
    draw_char(32, 100, letter_R);
    draw_char(44, 100, letter_E);
    draw_char(56, 100, letter_S);
    draw_char(68, 100, letter_S);

    draw_char(94, 100, letter_B);
    draw_char(106, 100, letter_U);
    draw_char(118, 100, letter_T);
    draw_char(130, 100, letter_T);
    draw_char(142, 100, letter_O);
    draw_char(154, 100, letter_N);

    draw_char(180, 100, letter_T);
    draw_char(192, 100, letter_O);

    draw_char(218, 100, letter_R);
    draw_char(230, 100, letter_E);
    draw_char(242, 100, letter_S);
    draw_char(254, 100, letter_T);
    draw_char(268, 100, letter_A);
    draw_char(280, 100, letter_R);
    draw_char(292, 100, letter_T);
}

void draw_start_screen(void){
    clear_screen();

    draw_char(130, 80, letter_P); 
    draw_char(142, 80, letter_O);
    draw_char(154, 80, letter_N);
    draw_char(168, 80, letter_G);

    draw_char(30, 100, letter_P);
    draw_char(42, 100, letter_R);
    draw_char(54, 100, letter_E);
    draw_char(66, 100, letter_S);
    draw_char(78, 100, letter_S);

    draw_char(104, 100, letter_B);
    draw_char(116, 100, letter_U);
    draw_char(128, 100, letter_T);
    draw_char(140, 100, letter_T);
    draw_char(152, 100, letter_O);
    draw_char(164, 100, letter_N);

    draw_char(190, 100, letter_T);
    draw_char(202, 100, letter_O);

    draw_char(228, 100, letter_S);
    draw_char(240, 100, letter_T);
    draw_char(252, 100, letter_A);
    draw_char(264, 100, letter_R);
    draw_char(276, 100, letter_T);
}

void draw_ready_to_play_text(void){
    draw_char(80, 80, letter_P);
    draw_char(92, 80, letter_R);
    draw_char(104, 80, letter_E);
    draw_char(116, 80, letter_S);
    draw_char(128, 80, letter_S);

    draw_char(154, 80, letter_B);
    draw_char(166, 80, letter_U);
    draw_char(178, 80, letter_T);
    draw_char(190, 80, letter_T);
    draw_char(202, 80, letter_O);
    draw_char(214, 80, letter_N);

    draw_char(110, 100, letter_T);
    draw_char(122, 100, letter_O);

    draw_char(148, 100, letter_P);
    draw_char(160, 100, letter_L);
    draw_char(172, 100, letter_A);
    draw_char(184, 100, letter_Y);
}

//removes a drawn heart if a player loses a life
void draw_lives(void){
    if(player1_lives >= 1) draw_char(10, 10, symbol_HEART);
    if(player1_lives >= 2) draw_char(24, 10, symbol_HEART);
    if(player1_lives >= 3) draw_char(38, 10, symbol_HEART);

    if(player1_lives >= 1) draw_char(270, 10, symbol_HEART);
    if(player2_lives >= 2) draw_char(284, 10, symbol_HEART);
    if(player2_lives >= 3) draw_char(298, 10, symbol_HEART);
}









