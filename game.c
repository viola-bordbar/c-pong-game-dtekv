/*This file defines the game logic and different game states with functions that for example update player lives, initializes the start and end of the game, etc.*/

#include "game.h"
#include "ball.h"
#include "draw.h"
#include "game_constants.h"
#include "input.h"
#include "paddle.h"
#include "font.h"

extern int paddle1_y;
extern int paddle2_y;

int game_state;
int player1_lives;
int player2_lives;
int paddle1_y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;
int paddle2_y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;

/*Function for initializing game variables, paddle positions and drawing the start screen

- 

Author: Sofia Mohamed
*/
void initialize_game(void){
    player1_lives = 3;
    player2_lives = 3;
    game_state = START_SCREEN;
    
    paddle1_y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddle2_y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

    draw_start_screen();
}



/*Function to update player lives and ending game if a player has no lives left

-

Author: Sofia Mohamed
*/
void update_lives(int player){
    if(player == 1){
        player1_lives--;
    }
    else if(player == 2){
    player2_lives--;}

    if(player1_lives == 0 || player2_lives == 0){
        game_state = GAME_OVER;
        game_over();
        return;
    }
}


/*Function for game logic: movign ball, checking collisions, drawing game components

-

Author: Viola Bordbar
*/
void play_game(void){
    //make the ball and paddles move
    ball_movement();
    paddle_movement(&paddle1_y, get_player1());
    paddle_movement(&paddle2_y, get_player2());

    //check misses/collisions and update accordingly for both players
    int miss = check_paddle_collision(paddle1_y, paddle2_y);
    if (miss == 1){
        update_lives(1);
        game_delay(100);
        reset_screen();

    }
    else if(miss == 2){
        update_lives(2);
        game_delay(100);
        reset_screen();
    }
    //draw game components again at the end
    draw_paddles();
    draw_lives(); 
    draw_ball(ball_x,ball_y,BALL_SIZE);
}


/*Calls function to draw the game over text on the display

-

Author: Viola Bordbar
*/
void game_over (void){
    draw_game_over_screen();
}


/*Function for reseting the screen by clearing screen, reseting ball and paddle positions and drawing components

-

Author: Viola Bordbar
*/
void reset_screen(void){
    clear_screen();

    paddle1_y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddle2_y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

    ball_x = PADDLE1_X + PADDLE_WIDTH + 5;
    ball_y = SCREEN_HEIGHT /2 - BALL_SIZE / 2;

    x_step = 1; 
    y_step = 0;
    extern int first_hit;
    first_hit = 1;
    draw_paddles();
    draw_lives();
}







