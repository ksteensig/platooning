#pragma once

#include "project.h"
#include <stdint.h>


typedef struct {
    uint16_t reference_dist; // platoon follower reference distance
    float Kp; // P-controller constant
} motor_t;

motor_t motor_init(uint16_t reference_dist, float Kp) {
 return (motor_t) {reference_dist, Kp};   
}

void motor_update(motor_t *m, uint16_t real_dist, uint16_t velocity) {
    int16_t err_dist = m->reference_dist - real_dist;
    int32_t duty_cycle = m->Kp * err_dist + velocity;
            
    // if duty_cycle ends up being negative, it needs to be capped at 0
    if (duty_cycle < 0)
    {
        duty_cycle = 0;
    }else if(duty_cycle > 150){
        duty_cycle = 150;
    }
            
    PWM_H_BRIDGE_WriteCompare(duty_cycle);
}