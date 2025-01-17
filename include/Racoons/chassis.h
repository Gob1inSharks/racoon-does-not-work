#include "main.h"

void drive_with_voltage(float leftVoltage, float rightVoltage);

void timed_drive(float voltage_left, float voltage_right, int time);

void drive_to_distance(float desired_position, float drive_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout);

void drive_to_distance(float desired_position);

void drive_to_distance(float desired_position, float drive_max_voltage);

void drive_to_distance(float desired_position, float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd);

void drive_to_distance(float desired_position, float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_settle_error, int drive_settle_time, int drive_timeout);

void turn_to_angle(float desired_position, float turn_max_voltage, float turn_settle_error, int turn_settle_time, int turn_timeout);

void turn_to_angle(float desired_position);

void turn_to_angle(float desired_position, float turn_max_voltage);

void turn_to_angle(float desired_position, float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti);

void turn_to_angle(float desired_position, float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_settle_error, int turn_settle_time, int turn_timeout);