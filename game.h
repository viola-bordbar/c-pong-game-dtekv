#ifndef GAME_H
#define GAME_H

#define START_SCREEN 0
#define READY_TO_PLAY 1
#define PLAYING 2
#define RESTART 3
#define GAME_OVER 4

void initialize_game(void);
void update_lives(int player);
void play_game(void);
void game_over(void);
void reset_screen(void);

#endif
