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
    _NUMBER,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    ALTAB = SAFE_RANGE,
    S_ALTAB
};

#define LT_NUM    LT(_NUMBER, KC_TAB)
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* | Esc |  1  |  2  |  3  |  4  |  5  |                          |  6  |  7  |  8  |  9  |  0  |  *  |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* |  `  |  Q  |  W  |  E  |  R  |  T  |-----+              +-----|  Y  |  U  |  I  |  O  |  P  |  -  |
* +-----+-----+-----+-----+-----+-----|  [  |              |  ]  |-----+-----+-----+-----+-----+-----+
* |Shift|  A  |  S  |  D  |  F  |  G  |-----+              +-----|  H  |  J  |  K  |  L  |  ;  |  '  |
* +-----+-----+-----+-----+-----+-----| Del |              |BSpc |-----+-----+-----+-----+-----+-----+
* |Ctrl |  Z  |  X  |  C  |  V  |  B  |-----+              +-----|  N  |  M  |  ,  |  .  |  /  |  =  |
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| / Tab /  \  /    \  `  \ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_NUM / Alt /      \ GUI \_CUR \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,                      KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_ASTR,
  KC_GRV,  KC_Q, KC_W, KC_E, KC_R, KC_T,                      KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_MINS,
  KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_LBRC,    KC_RBRC, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_DEL,     KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL,
                KC_BSPC, SFTSPC, LT_CUR, ALTBSL,     GUIGRV, LT_NUM, CTLENT, KC_DEL
),


/* CURSOR
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |                          |     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* | GUI | F1  | F2  | F3  | F4  | F5  |-----+              +-----| F6  | F7  | F8  | F9  | F10 | F11 |
* +-----+-----+-----+-----+-----+-----| Ins |              |Caps |-----+-----+-----+-----+-----+-----+
* |     |Home |PgDn |PgUp | End |Enter|-----+              +-----|Enter|Left |Down | Up  |Right| F12 |
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
  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ENT,  KC_INS,      KC_CAPS, KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12,
  _______, C_LEFT,  XXXXXXX, XXXXXXX, C_RGHT,  KC_SPC,  _______,     _______, KC_SPC,S(LALT(KC_TAB)),SC_TAB,C_TAB,LALT(KC_TAB),KC_PSCR,
                            _______, _______, MMO_ADJ,  _______,     _______, _______, _______, _______
),


/* NUMBER
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* |     | F1  | F2  | F3  | F4  | F5  |                          | F6  | F7  | F8  | F9  | F10 | F11 |
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* | Esc |  !  |  @  |  #  |  $  |  %  |-----+              +-----|  ^  |  &  |  *  |  (  |  )  |  -  |
* +-----+-----+-----+-----+-----+-----|  {  |              |  }  |-----+-----+-----+-----+-----+-----+
* |     |  1  |  2  |  3  |  4  |  5  |-----+              +-----|  6  |  7  |  8  |  9  |  0  |  '  |
* +-----+-----+-----+-----+-----+-----| Del |              |BSpc |-----+-----+-----+-----+-----+-----+
* |     |Left |Down | Up  |Right|  |  |-----+              +-----|  ~  |  +  |  ,  |  .  |  /  |  =  |
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| / Tab /  \  /    \  `  \ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_NUM / Alt /      \ GUI \_ADJ \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_NUMBER] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_ESC , KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LCBR,     KC_RCBR, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_QUOT,
  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PIPE, _______,     _______, KC_TILD, KC_PLUS, KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
                             _______, _______, _______, _______,     _______, MO_ADJ,  _______, _______
),


/* ADJUST
* +-----+-----+-----+-----+-----+-----+                          +-----+-----+-----+-----+-----+-----+
* |Reset|     |     |     |     |     |                          |     |     |     |     |     |Reset|
* +-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |-----+              +-----|     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----|     |              |     |-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |-----+              +-----|     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----|     |              |     |-----+-----+-----+-----+-----+-----+
* |     |     |     |     |     |     |-----+              +-----|     |     |     |     |     |     |
* +-----+-----+-----+-----+-----+-----+-----+-----+  +-----+-----+-----+-----+-----+-----+-----+-----+
*               Tap->  |BSpc |Space| / Tab /  \  /    \  `  \ Esc \ |Enter| Del |  <-Tap
*              Hold->  |     |Shift|/_NUM / Alt /      \ GUI \_CUR \|Ctrl |     |  <-Hold
*                      +-----+-----+-----+-----+        +-----+-----+-----+-----+
*/
[_ADJUST] = LAYOUT(
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                              XXXXXXX, XXXXXXX, MO_ADJ, XXXXXXX,    XXXXXXX, MO_ADJ,  XXXXXXX, XXXXXXX
)

};



bool alt_pressed = false;

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

        default:
            if (alt_pressed) {
                alt_pressed = false;
                unregister_code(KC_LALT);
                if (record->event.pressed) {
                    return false;
                }
            }
            break;
    }
    return true;
}
