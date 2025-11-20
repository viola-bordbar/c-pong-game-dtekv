#ifndef DRAW_H
#define DRAW_H

#define FONT_SCALE 2
#define WHITE 0xFF
#define CLEAR 0x00

void initialize_VGA(void);
void clear_screen(void);
void draw_pixel(int pixel_x, int pixel_y);
void clear_pixel(int pixel_x, int pixel_y);
void draw_paddles(void);
void draw_char(int x, int y, unsigned char letter[7]);
void draw_game_over_screen(void);
void draw_ready_to_play_text(void);
void draw_start_screen(void);
void draw_lives(void);
void draw_ball(int x, int y, int size);

#endif
