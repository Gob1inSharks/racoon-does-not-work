#include "main.h"

void ladybrown_turn_to(float desired_position);
void ladybrown_turn_to(float desired_position,float kp, float ki, float kd, float starti, float settle_error, int settle_time, int timeout);

void ladybrown_turn_to_with_rotary_encoder(float desired);
void ladybrown_turn_to_with_rotary_encoder(float desired,float kp, float ki, float kd, float starti, float settle_error, int settle_time, int timeout);

void ladybrown_turn_to_with_motor_encoder(float desired_position);
void ladybrown_turn_to_with_motor_encoder(float desired_position,float kp, float ki, float kd, float starti, float settle_error, int settle_time, int timeout);