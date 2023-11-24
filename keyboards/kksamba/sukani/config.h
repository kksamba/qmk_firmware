// Copyright 2023 kksamba (@kksamba)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RETRO_TAPPING_PER_KEY

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT


/* pointing device driver settings */
#ifdef POINTING_DEVICE_ENABLE

#define ANALOG_JOYSTICK_X_AXIS_PIN        B4
#define ANALOG_JOYSTICK_Y_AXIS_PIN        B5
#define ANALOG_JOYSTICK_AXIS_MIN         200  // 0
#define ANALOG_JOYSTICK_AXIS_MAX         700  // 1023
#define ANALOG_JOYSTICK_SPEED_REGULATOR   20  // 20, divisor used to slow down movement
#define ANALOG_JOYSTICK_READ_INTERVAL     10  // 10, [ms]
#define ANALOG_JOYSTICK_SPEED_MAX          2  // 2, maximum value used for motion
#define POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y

// #define ANALOG_JOYSTICK_CLICK_PIN

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_LEFT

#endif
