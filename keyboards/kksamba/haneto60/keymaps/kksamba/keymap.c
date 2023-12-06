/* Copyright 2021 kksamba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _CURSOR,
    _NUMSYM,
    _ADJUST,
    _WASD,
    _CALC
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    ALTAB = SAFE_RANGE,
    S_ALTAB
};

#define LT_NUM    LT(_NUMSYM, KC_TAB)
#define LT_CUR    LT(_CURSOR, KC_ESC)
#define MO_ADJ    MO(_ADJUST)

#define ALTBSL    LALT_T(KC_BSLS)
#define GUIGRV    LGUI_T(KC_GRV)
#define SFTSPC    LSFT_T(KC_SPC)
#define CTLENT    LCTL_T(KC_ENT)

#define C_TAB     C(KC_TAB)
#define SC_TAB    S(C(KC_TAB))
#define C_LEFT    C(KC_LEFT)
#define C_RGHT    C(KC_RGHT)

// Layer indicator using pro micro LEDs
#define PRO_MICRO_LED_TX D5
#define PRO_MICRO_LED_RX B0


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* | Esc |  1  |  2  |  3  |  4  |  5  |                          |  6  |  7  |  8  |  9  |  0  |  =  |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* |  `  |  Q  |  W  |  E  |  R  |  T  |-----+              +-----|  Y  |  U  |  I  |  O  |  P  |  -  |
* +-----+-----+-----+-----+-----+-----|  [  |              |  ]  |-----+-----+-----+-----+-----+-----+
* |  '  |  A  |  S  |  D  |  F  |  G  |-----+              +-----|  H  |  J  |  K  |  L  |  Z  |  ;  |
* +-----+-----+-----+-----+-----+-----|IMEOn|              |IMEOf|-----+-----+-----+-----+-----+-----+
* |Ctrl |Shift|  X  |  C  |  V  |  B  |-----+              +-----|  N  |  M  |  ,  |  .  |  /  |Shift|
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| / Tab /  \  /    \  `  \ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_NUM / Alt /      \ GUI \_CUR \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,                      KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_EQL,
  KC_GRV,  KC_Q, KC_W, KC_E, KC_R, KC_T,                      KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_MINS,
  KC_QUOT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_LBRC,    KC_RBRC, KC_H, KC_J, KC_K,    KC_L,   KC_Z,    KC_SCLN,
  KC_LCTL,KC_LSFT,KC_X,KC_C, KC_V, KC_B, KC_LNG1,    KC_LNG2, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
                 KC_BSPC, SFTSPC, LT_NUM, ALTBSL,    GUIGRV,  LT_CUR, CTLENT, KC_DEL
),


/* Cursor
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |                          |     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* | GUI | F1  | F2  | F3  | F4  | F5  |-----+              +-----| F6  | F7  | F8  | F9  | F10 | F11 |
* +-----+-----+-----+-----+-----+-----| Ins |              |Caps |-----+-----+-----+-----+-----+-----+
* |Shift|Home |PgDn |PgUp | End |Enter|-----+              +-----|Enter|Left |Down | Up  |Right| F12 |
* +-----+-----+-----+-----+-----+-----| Del |              |BSpc |-----+-----+-----+-----+-----+-----+
* |     |CLft |     |     |CRght|Space|-----+              +-----|Space|SALTB|SCTab|CTab |ALTAB|PrtSc|
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| /     /  \  /    \  `  \ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_ADJ / Alt /      \ GUI \_CUR \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_CURSOR] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  KC_LGUI, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_LSFT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ENT,  KC_INS,      KC_CAPS, KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12,
  _______, C_LEFT,  XXXXXXX, XXXXXXX, C_RGHT,  KC_SPC,  KC_DEL,      KC_BSPC, KC_SPC,  S_ALTAB, SC_TAB,  C_TAB,   ALTAB,   KC_PSCR,
                             _______, _______, MO_ADJ,  _______,     _______, _______, _______, _______
),


/* Number & Symbols
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* |     | F1  | F2  | F3  | F4  | F5  |                          | F6  | F7  | F8  | F9  | F10 | F11 |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* | Esc |  1  |  2  |  3  |  4  |  5  |-----+              +-----|  6  |  7  |  8  |  9  |  0  |  -  |
* +-----+-----+-----+-----+-----+-----|  {  |              |  }  |-----+-----+-----+-----+-----+-----+
* |Shift|  !  |  @  |  #  |  $  |  %  |-----+              +-----|  ^  |  &  |  *  |  (  |  )  |  '  |
* +-----+-----+-----+-----+-----+-----| Del |              |BSpc |-----+-----+-----+-----+-----+-----+
* |     |  [  |  {  |  }  |  ]  |  |  |-----+              +-----|  ~  |  +  |  ,  |  .  |  /  |  =  |
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| /     /  \  /    \  `  \     \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_NUM / Alt /      \ GUI \_ADJ \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_NUMSYM] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_ESC , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_LSFT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LCBR,     KC_RCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT,
  _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_PIPE, _______,     _______, KC_TILD, KC_PLUS, KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
                             _______, _______, _______, _______,     _______, MO_ADJ,  _______, _______
),


/* Adjuster
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* |Reset|     |     |     |     |     |                          |     |     |     |     |     |Reset|
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |-----+              +-----|     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----|     |              |     |-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |-----+              +-----|     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----|     |              |     |-----+-----+-----+-----+-----+-----+
* |RCtrl|     |     |     |     |     |-----+              +-----|     |     |     |     |     |RSft |
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| / Tab /_CALC/    \_WASD\ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_NUM /     /      \     \_CUR \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_RCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                             XXXXXXX, XXXXXXX, MO_ADJ,  TG(_CALC),TG(_WASD),  MO_ADJ, XXXXXXX, XXXXXXX
),


/* WASD
*
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* | Esc |  Q  |  2  |  3  |  4  |  5  |                          |  6  |  7  |  8  |  9  |  0  |BSpc |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* |Home |  A  |  W  |  E  |  R  |  T  |-----+              +-----|  Y  |  U  |  I  |  O  |  P  |  -  |
* +-----+-----+-----+-----+-----+-----|  [  |              |  ]  |-----+-----+-----+-----+-----+-----+
* |  Z  |  1  |  S  |  D  |  F  |  G  |-----+              +-----|  H  |  J  |  K  |  L  |  Z  |  ;  |
* +-----+-----+-----+-----+-----+-----|IMEOn|              |IMEOf|-----+-----+-----+-----+-----+-----+
* |Ctrl |Shift|  X  |  C  |  V  |  B  |-----+              +-----|  N  |  M  |  ,  |  .  |  /  |  =  |
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  | End |Space| / Tab /     /    \_QWER\ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |     |/     / Alt /      \     \_CUR \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_WASD] = LAYOUT(
  KC_ESC,  KC_Q,    KC_2, KC_3, KC_4, KC_5,                      KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_BSPC,
  KC_HOME, KC_A,    KC_W, KC_E, KC_R, KC_T,                      KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_MINS,
  KC_Z,    KC_1,    KC_S, KC_D, KC_F, KC_G, KC_LBRC,    KC_RBRC, KC_H, KC_J, KC_K,    KC_L,   KC_QUOT, KC_SCLN,
  KC_LCTL, KC_LSFT, KC_X, KC_C, KC_V, KC_B, KC_LNG1,    KC_LNG2, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL,
                    KC_END, KC_SPC, KC_TAB, KC_LALT,    TG(_WASD), LT_CUR, CTLENT, KC_DEL
),



/* Calculator
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* | Esc |     |     |     |     |     |                          |  [  |  ^  |  /  |  *  |  -  |  ]  |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* |     |  6  |  7  |  8  |  9  |  0  |-----+              +-----|  {  |  7  |  8  |  9  |  +  |  }  |
* +-----+-----+-----+-----+-----+-----|  ,  |              |  %  |-----+-----+-----+-----+-----+-----+
* |     |  1  |  2  |  3  |  4  |  5  |-----+              +-----|  (  |  4  |  5  |  6  |  =  |  )  |
* +-----+-----+-----+-----+-----+-----| Del |              |BSpc |-----+-----+-----+-----+-----+-----+
* |Ctrl |Left |Down | Up  |Right|  .  |-----+              +-----| Tab |  1  |  2  |  3  |  ,  |Shift|
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| / Tab /_QWER/    \Space\Enter\ |  0  |  .  |  <-Tap
*              Hold->  |     |Shift|/     /     /      \     \     \|     |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_CALC] = LAYOUT(
  KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LBRC, KC_CIRC, KC_SLSH, KC_ASTR, KC_MINS, KC_RBRC,
  XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                         KC_LCBR, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_RCBR,
  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_COMM,    KC_PERC, KC_LPRN, KC_4,    KC_5,    KC_6,    KC_EQL,  KC_RPRN,
  KC_LCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DOT,  KC_DEL,     KC_BSPC, KC_TAB,  KC_1,    KC_2,    KC_3,    KC_COMM, KC_LSFT,
                             KC_BSPC, SFTSPC,  KC_TAB, TG(_CALC),   KC_SPC,  KC_ENT,  KC_0,    KC_DOT
)

};



bool alt_pressed = false;
bool ctrl_pressed = false;
bool exceptionaly_ctrl_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_ALTAB:
        case ALTAB:
            if (record->event.pressed) {
                if (!alt_pressed) {
                    alt_pressed = true;
                    register_code(KC_LALT);
                }
                if (keycode == S_ALTAB) {
                    register_code(KC_LSFT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                if (keycode == S_ALTAB) {
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;

        case KC_LCTL:
            if (record->event.pressed){
                ctrl_pressed = true;

            } else {
                ctrl_pressed = false;
            }
            break;

        default:
            if (alt_pressed) {
                alt_pressed = false;
                unregister_code(KC_LALT);
                if (record->event.pressed) {
                    return false;
                }
            }
            if (ctrl_pressed || exceptionaly_ctrl_pressed) {
                switch (keycode) {
                case KC_QUOT:
                    if (record->event.pressed) {
                        register_code(KC_Z);
                        exceptionaly_ctrl_pressed = true;
                    } else {
                        unregister_code(KC_Z);
                        exceptionaly_ctrl_pressed = false;
                    }
                    return false;
                    break;
                }

            }
            break;
    }
    return true;
}


// Layer indicator using pro micro LEDs
void matrix_init_user(void) {
    setPinOutput(PRO_MICRO_LED_TX);
    setPinOutput(PRO_MICRO_LED_RX);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(PRO_MICRO_LED_TX, \
      !(layer_state_cmp(state, _WASD) || layer_state_cmp(state, _CURSOR) || layer_state_cmp(state, _ADJUST)) );
    writePin(PRO_MICRO_LED_RX, \
      !(layer_state_cmp(state, _CALC) || layer_state_cmp(state, _NUMSYM) || layer_state_cmp(state, _ADJUST)) );
    return state;
}
