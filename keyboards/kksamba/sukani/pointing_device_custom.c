// Copyright 2023 kksamba (@kksamba)
// SPDX-License-Identifier: GPL-2.0-or-later

// custom analog joystick device driver

#include "pointing_device.h"
#include "wait.h"
#include "timer.h"
#include <stdint.h>
#include <stdlib.h>

#include "analog.h"
#include "gpio.h"


// Set Parameters
uint16_t minAxisValue = ANALOG_JOYSTICK_AXIS_MIN;
uint16_t maxAxisValue = ANALOG_JOYSTICK_AXIS_MAX;

uint8_t maxCursorSpeed = ANALOG_JOYSTICK_SPEED_MAX;
uint8_t speedRegulator = ANALOG_JOYSTICK_SPEED_REGULATOR; // Lower Values Create Faster Movement

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;

int16_t axisCoordinate(pin_t pin, uint16_t origin);
int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed);

#ifdef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC
void spline_cubic_init(void);
float calc_spline_cubic(float px);
#endif


int16_t axisCoordinate(pin_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
#ifdef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC
    int16_t coordinate = (int16_t)(calc_spline_cubic(percent) * 100);
#else
    int16_t coordinate = (int16_t)(percent * 100);
#endif
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed) {
    int16_t coordinate = axisCoordinate(pin, origin);
    if (coordinate != 0) {
        float percent = (float)coordinate / 100;
        return percent * maxCursorSpeed * (abs(coordinate) / speedRegulator);
    } else {
        return 0;
    }
}

#ifdef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC

// interpolated points
#ifndef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N
#define    ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N 2
#endif
int8_t n = ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N;
float xnode[] = ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_XNODE;
float ynode[] = ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_YNODE;
// boundary conditions
#ifdef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DY0
    float dy0 = ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DY0;
#else
    float dy0 = 1.0;
#endif
#ifdef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DYN
    float dyn = ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DYN;
#else
    float dyn = 1.0;
#endif
// float a[ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N, 3];
float b[ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N];

float dx[ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N - 1];
// float dx2[ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N - 1];
float dx2_6[ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N - 1];

void spline_cubic_init(void) {
    float a[ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N][3];

    for (int8_t i = 0; i < n - 1; i++) {
        dx[i] = -xnode[i] + xnode[i + 1];
        // dx2[i] = dx[i] * dx[i];
        dx2_6[i] = dx[i] * dx[i] / 6.0;
    }

    // calculate coefficients simultaneous equations
    // i = 0
    a[0][0] = 0.0;
    a[0][1] = dx[0] / 3.0;
    a[0][2] = dx[0] / 6.0;
    b[0] = (-ynode[0] + ynode[1]) / dx[0] - dy0;
    // i = 1 ~ n - 2
    for (int8_t i = 1; i < n - 1; i++) {
        a[i][0] = dx[i - 1] / 6.0;
        a[i][1] = (dx[i - 1] + dx[i]) / 3.0;
        a[i][2] = dx[i] / 6.0;
        // b[i] = -(ynode[i] - ynode[i - 1]) / dx[i - 1] + (ynode[i + 1] - ynode[i]) / dx[i];
        b[i] = (ynode[i - 1] - ynode[i]) / dx[i - 1] + (-ynode[i] + ynode[i + 1]) / dx[i];
    }
    // i = n - 1
    a[n - 1][0] = dx[n - 2] / 6.0;
    a[n - 1][1] = dx[n - 2] / 3.0;
    a[n - 1][2] = 0.0;
    // b[n - 1] = -(ynode[n - 1] - ynode[n - 2]) / dx[n - 2] + dyn;
    b[n - 1] = (ynode[n - 2] - ynode[n - 1]) / dx[n - 2] + dyn;

    // solve by Gaussian elimination
    // i = 0 ~ n - 2
    for (int8_t i = 0; i < n - 1; i++) {
        b[i] /= a[i][1];

        a[i][2] /= a[i][1];
        b[i + 1] -= b[i] * a[i + 1][0];
        a[i + 1][1] -= a[i][2] * a[i + 1][0];
    }
    // i = n - 1
    b[n - 1] /= a[n - 1][1];

    // i = n - 2 ~ 0
    for (int8_t i = n - 2; i > -1; i--) {
        b[i] -= b[i + 1] * a[i][2];
    }
}

float calc_spline_cubic(float px) {
    if (px > 1.0) {
        return 1.0;
    }

    int8_t j = 0;
    for (int8_t i = 0; i < n - 1; i++) {
        j = i;
        if (px < xnode[i]) {
            j = i - 1;
            break;
        }
    }
    float h = (px - xnode[j]) / dx[j];
    float h_1 = 1.0 - h;

    float py = (h_1 * h_1 * h_1 * b[j] + h * h * h * b[j + 1]) * dx2_6[j]  \
             + (ynode[j] - b[j] * dx2_6[j]) * h_1 + (ynode[j + 1] - b[j + 1] * dx2_6[j]) * h;

    return py;
}

#endif


void pointing_device_driver_init(void) {
#ifdef ANALOG_JOYSTICK_CLICK_PIN
    setPinInputHigh(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    // Account for drift
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);

#ifdef ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC
    spline_cubic_init();
#endif
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {

    if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
        lastCursor = timer_read();
        mouse_report.x   = axisToMouseComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, maxCursorSpeed);
        mouse_report.y   = axisToMouseComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, maxCursorSpeed);
    }

#ifdef ANALOG_JOYSTICK_CLICK_PIN
    mouse_report.button = !readPin(ANALOG_JOYSTICK_CLICK_PIN);
#endif

    return mouse_report;
}

// this driver don't use following functions
uint16_t pointing_device_driver_get_cpi(void) { return 0; }
void pointing_device_driver_set_cpi(uint16_t cpi) {}
