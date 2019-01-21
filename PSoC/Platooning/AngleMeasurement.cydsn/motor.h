#pragma once

#include "project.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t reference_dist; // platoon follower reference distance
    float Kp; // P-controller constant
} motor_t;

motor_t motor_init(uint16_t reference_dist, float Kp) {
 return (motor_t) {reference_dist, Kp};   
}

void motor_update(motor_t *m, uint16_t real_dist, int16_t velocity) {
    int16_t err_dist = m->reference_dist - real_dist;
    int32_t duty_cycle = m->Kp * err_dist + velocity;
            
    // if duty_cycle ends up being negative, it needs to be capped at 0
    if (duty_cycle < -150)
    {
        duty_cycle = -150;
    }else if(duty_cycle > 150){
        duty_cycle = 150;
    }
        //drive forward    
    if(duty_cycle >0)
    {
        P1_Write(1);
        P2_Write(0);
        PWM_H_BRIDGE_WriteCompare1(duty_cycle);
        PWM_H_BRIDGE_WriteCompare2(0);
    }
    else if(duty_cycle<0)
    {
        P1_Write(0);
        P2_Write(0);
        PWM_H_BRIDGE_WriteCompare1(duty_cycle*-1);
        PWM_H_BRIDGE_WriteCompare2(255);
    }    
    
  char out[200];
//sprintf(out,"duty: %d",duty_cycle);
//UART_PutString(out);
}