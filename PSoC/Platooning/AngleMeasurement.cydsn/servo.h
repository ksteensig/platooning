#pragma once

#include "project.h"
#include <stdint.h>
#include <stdlib.h>

static const uint16_t t_right = 1035;
static const uint16_t t_left = 1694;
static const uint16_t t_center =  1364;
static const uint16_t theta_total = 60; // (uint16_t)(t_right + t_left)/2
static const float turn_factor = -11; // approx (t_right - t_left)/theta_total;
static const int8_t offset = -40;

typedef struct {
    float reference_angle; // reference angle between platoon leader and follower
    float Kp; // P-controller constant
    float previous_angles[3]; // [a1, a2, a3], where a1 is the newest angle and a3 is the oldest angle
    int8_t leader_angles[3]; // the longer the array, the longer the delay before using the value
    float old_angle_servo;
} servo_t;

servo_t servo_init(float reference_angle, float Kp) {
    return (servo_t){reference_angle, Kp, {0}, {0}, 0};
}

/*
 * servo_t *s: pointer to the object itself
 * angle: current angle
 * leader_angle: platoon leader's angle
 * velocity: current pwm for the velocity
 */
void servo_update(servo_t *s, float angle, int leader_angle, int16_t velocity) {    
    float weighted_Kp = s->Kp;
    
    s->leader_angles[2] = s->leader_angles[1];
    s->leader_angles[1] = s->leader_angles[0];
    s->leader_angles[0] = leader_angle;
    
    if (angle < 60 || angle > -60) {
       s->previous_angles[2] = s->previous_angles[1];
       s->previous_angles[1] = s->previous_angles[0];
       s->previous_angles[0] = angle;
    }
    
    if (velocity > 0) {
        if (!(s->Kp/(velocity*0.031*0.58) < s->Kp)) {
            weighted_Kp = s->Kp/(velocity*0.031*0.58);
        }
    }
    
    float err_angle = s->reference_angle - (s->previous_angles[0] + s->previous_angles[1] + s->previous_angles[2])/3.0;
    
    // angle that should be turned
    float angle_servo = weighted_Kp * err_angle;
    
    if(angle_servo > abs((int)s->old_angle_servo)+10){
        angle_servo = s->old_angle_servo;
    }
    
    s->old_angle_servo = angle_servo;
    
    // convert angle_servo into the correct signal that can be applied to the servo
    int16_t servo_signal = angle_servo * turn_factor + t_center + offset;
    
    /*        
    if(servo_signal_counter == 3){
        servo_signal_RB[servo_signal_counter] = servo_signal;
        servo_signal_counter = 0;
    } else {
        servo_signal_RB[servo_signal_counter] = servo_signal;
        servo_signal_counter++;
    }
    */
    
    //int16_t servo_signal_avg; //= (servo_signal_RB[0] + servo_signal_RB[1] + servo_signal_RB[2])/3;
    
    PWM_SERVO_WriteCompare(servo_signal);
}