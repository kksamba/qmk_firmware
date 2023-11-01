// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _OHNISHI,
    _NUM,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes {
//     QMKBEST = SAFE_RANGE,
//     QMKURL
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ Q │ L │ U │, <│. >│       │ F │ W │ R │ Y │ P │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ E │ O │ A │ I │- _│       │ K │ J │ N │ S │ H │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │/ ?│       │ G │ D │ M │ J │ B │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┬───┐           ┌───┬───┐
      *           │Bsp│Spc├───┐   ┌───┤Del│Esc│
      *           └───┴───┤Tab│   │Ent├───┴───┘
      *            Ctr Sft└───┘   └───┘Alt Win
      *                    NUM     NUM
      */
    [_OHNISHI] = LAYOUT(
        KC_Q, KC_L, KC_U, KC_COMM, KC_DOT,                          KC_F, KC_W, KC_R, KC_Y, KC_P,
        KC_E, KC_O, KC_A, KC_I,    KC_MINS,                         KC_K, KC_T, KC_N, KC_S, KC_H,
        KC_Z, KC_X, KC_C, KC_V,    KC_SLSH,                         KC_G, KC_D, KC_M, KC_J, KC_B,
        LCTL_T(KC_BSPC), LSFT_T(KC_SPC), LT(_NUM, KC_TAB),          LT(_NUM, KC_ENT), LALT_T(KC_DEL), LGUI_T(KC_ESC)
    ),


     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │1 !│2 @│3 #│4 $│5 %│       │[ {│F2 │F3 │F4 │F5 │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │6 ^│7 &│8 *│9 (│0 )│       │F6 │F7 │F8 │F9 │F10│
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │' "│; :│` ~│= +│\ |│       │] }│ < │ v │ ^ │ > │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┬───┐           ┌───┬───┐
      *           │Ctr│JPN├───┐   ┌───┤ENG│Sft│
      *           └───┴───┤Tab│   │Ent├───┴───┘
      *            --- ---└───┘   └───┘--- ---
      *                    NUM     NUM
      */
    [_NUM] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_LBRC, KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_QUOT, KC_SCLN, KC_GRV,  KC_EQL,  KC_BSLS,        KC_RBRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                          KC_LCTL, KC_LNG1, _______,        _______, KC_LNG2, KC_LSFT
    )


     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ ! │ @ │ # │ $ │ % │       │ ^ │ & │ * │ ( │ ) │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ ' │ ; │ ~ │ + │ | │       │ \ │ < │ v │ ^ │ > │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┬───┐           ┌───┬───┐
      *           │Sft│JPN├───┐   ┌───┤ENG│Ctr│
      *           └───┴───┤Tab│   │Ent├───┴───┘
      *            --- ---└───┘   └───┘--- ---
      *                    NUM     NUM
      */
    // [_NUM] = LAYOUT(
    //     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    //     KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    //     KC_QUOT, KC_SCLN, KC_TILD, KC_PLUS, KC_PIPE,        KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    //                       _______, KC_LNG1, _______,        _______, KC_LNG2, _______
    // )

};


#ifdef RETRO_TAPPING_PER_KEY

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_BSPC):
        case LALT_T(KC_DEL):
            return true;

        default:
            return false;
    }
}

#endif
