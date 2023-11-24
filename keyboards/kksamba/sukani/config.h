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

// custom analog joystick settings
#define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC

// high sensitivity
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N 5
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_XNODE {0.0, 0.075, 0.2, 0.4,  1.0}
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_YNODE {0.0, 0.25,  0.5, 0.75, 1.0}
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DY0 5.0
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DYN 0.0

// linear
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N 2
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_XNODE {0.0, 1.0}
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_YNODE {0.0, 1.0}
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DY0 1.0
// #define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DYN 1.0

// gently sloped tanh like
#define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_N 5
#define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_XNODE {0.0, 0.25, 0.5, 0.75, 1.0}
#define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_YNODE {0.0, 0.1,  0.5, 0.9,  1.0}

#define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DY0 0.0
#define ANALOG_JOYSTICK_CUSTOM_INTERP_SPLINE_CUBIC_DYN 0.0

#endif
