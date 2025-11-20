#ifndef INPUT_H
#define INPUT_H

int get_sw(void);
int get_player1(void);
int get_player2(void);
int get_button(void);
void initialize_timer(void);
int check_timer_status(void);
void game_delay(int delay);
void handle_interrupt(void);

#endif