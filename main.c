/*
This file includes only the main game loop, where button presses and game states define how the game is played

-

Author: Viola Bordbar 
*/

#include "game_constants.h"
#include "input.h"
#include "draw.h"
#include "font.h"
#include "game.h"

extern int game_state;
int prev_button = 0;

//main function
int main(void){
    initialize_VGA();
    initialize_timer();
    initialize_game();

    while(1){
        int current_button = get_button();

        if(current_button == 1 && prev_button == 0){ //updates game states based on button pressees
            if(game_state == GAME_OVER){
                clear_screen();
                initialize_game();
                game_state = START_SCREEN;
            }
            else if(game_state == START_SCREEN){
                game_state = READY_TO_PLAY;
            }
            else if(game_state == READY_TO_PLAY){
                game_state = PLAYING;
            }
            else if (game_state == PLAYING){ 
                game_state = START_SCREEN;
                initialize_game();
            }
        }

        prev_button = current_button;

        if(check_timer_status()){  //loops game and delays with timer
            static int last_state = -1;
            if(game_state != last_state){
                if(game_state == READY_TO_PLAY){  //gives each game state something to do in the game loop 
                    reset_screen();
                    draw_ready_to_play_text();
                }
                else if(game_state == PLAYING){
                    reset_screen();
                }
                else if(game_state == RESTART){
                    clear_screen();
                    initialize_game();
                }
                else if(game_state == GAME_OVER){
                    game_over();
                }
                
                last_state = game_state;
            }
        
            if(game_state == PLAYING){
                play_game();
            }
        }
    }
}
