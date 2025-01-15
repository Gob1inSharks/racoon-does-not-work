#include "main.h"

void ladybrown_turn_to(int desired_position);
void ladybrown_turn_to(int desired_position,int kp, int ki, int kd, int starti, int settle_error, int settle_time, int timeout);

void ladybrown_turn_to_with_rotary_encoder(int desired);
void ladybrown_turn_to_with_rotary_encoder(int desired,int kp, int ki, int kd, int starti, int settle_error, int settle_time, int timeout);

void ladybrown_turn_to_with_motor_encoder(int desired_position);
void ladybrown_turn_to_with_motor_encoder(int desired_position,int kp, int ki, int kd, int starti, int settle_error, int settle_time, int timeout);