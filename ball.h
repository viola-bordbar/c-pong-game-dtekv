#ifndef BALL_H
#define BALL_H

extern int ball_x;
extern int ball_y;
extern int x_step;
extern int y_step;

void ball_movement(void);
int check_paddle_collision(int paddle1_y, int paddle2_y);
void change_ball_direction(int paddle_y);

#endif
