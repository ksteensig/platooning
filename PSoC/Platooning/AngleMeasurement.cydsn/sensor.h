#pragma once

#include "project.h"
#include <stdint.h>

typedef struct {
    uint16_t distance; // distance between cars
    float angle;       // angle between platoon follower and platoon leader
    
    /* feedforward parameters */
    uint16_t velocity;   // platoon leader velocity
    int8_t leader_angle; // angle of platoon leader's wheels
} sensor_t;

sensor_t sensor_init() {
    return (sensor_t){0, 0, 0, 0};
}

void sensor_update_feedforward_params(sensor_t *s, uint16_t velocity, int8_t leader_angle) {
    s->velocity = velocity;
    s->leader_angle = leader_angle;
}

void sensor_update_data(sensor_t *s, uint16_t *chan_a, uint16_t *chan_b, uint16_t chan_len) {
    // defining a and b for the highest amplitude of the signals
    uint16_t a = 0, b = 0;
    uint16_t ai = 0, bi = 0;
            
    // find the 3 biggest time indices of DataA and DataB
    for (uint16_t i = 0; i < chan_len; i++) {
        if (chan_a[i] > a) {
            a = chan_a[i];
            ai = i;
        }
                
        if (chan_b[i] > b) {
            b = chan_b[i];
            bi = i;
        }
    }
            
        // angle from -60 to 60
        // 2.25 us per sample
        // 1 us = 0.2 degrees
        // 0.45 = 2.25 * 0.2
        s->angle = (ai - bi) * 0.45;            
        
        // distance in mm, where speed of sound is 343 mm/ms
        // first convert the time difference from us to ms, and then multiply by the speed of sound
        // use ai and bi depending on which has the closest peak to the network ping
        // The 100 value subtracted has been experimentally found
        // 0.77 = 2.25/1000.0 * 343
        if (ai < bi) {
            s->distance = ai*0.77 - 100;
        } else {
            s->distance = bi * 0.77 -100;
        }
}