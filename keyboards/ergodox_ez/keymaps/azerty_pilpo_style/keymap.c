/**
 cd /C/Quentin/Programmes/QMK
 make ergodox_ez:bepo_pilpo_style
 make ergodox_ez:azerty_pilpo_style
*/

#include QMK_KEYBOARD_H
//#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "action_tapping.h"
#include "keymap_extras/keymap_french.h"

#define BASE 0 // default layer
#define SHIFT 1
#define LAYER_2 2
#define TAPPING_TOGGLE 1
#define M_1        LSFT(KC_1)
#define M_2        LSFT(KC_2)
#define M_3        LSFT(KC_3)
#define M_4        LSFT(KC_4)
#define M_5        LSFT(KC_5)
#define M_6        LSFT(KC_6)
#define M_7        LSFT(KC_7)
#define M_8        LSFT(KC_8)
#define M_9        LSFT(KC_9)
#define M_0        LSFT(KC_0)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  // LAST LETTER
  // FIRST "MACRO"
  CUT,
  COPY,
  PAST,
  SAVE,
  UNDO,
  COMMENT_BLOCK_OR_RENAME,
  REFRESH_CACHE
  // LAST "MACRO"
};

enum custom_layer {
  SHIFTED
};

#define KEY_DELAY 130
static uint16_t key_timer;

enum enum_combo_code {
  COMBO_CUT,
  COMBO_COPY,
  COMBO_PAST,
  COMBO_SAVE,
  COMBO_UNDO,
  COMBO_COMMENT_BLOCK_OR_RENAME,
  COMBO_REFRESH_CACHE
};

char *combo_codes[][2] = {
    {
        SS_LCTRL(SS_TAP(X_X)),                  // CUT
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_C)),                  // COPY
        SS_LALT(SS_TAP(X_RBRACKET))             // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_V)),                  // PAST
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_S)),                  // SAVE
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_W)),                  // UNDO
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }, {
         SS_LCTRL(SS_LSFT(SS_TAP(X_DOT))),      // COMBO_COMMENT_BLOCK_OR_RENAME
         SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_F5)),                  // REFRESH_CACHE
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox(  // layer 0 : default
/* Keymap 0: Basic layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   &  |   é  |   "  |   '  |   (  |  ù   |           |  =   |   -  |   è  |   _  |   ç  |   à  |  TL2   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   A  |  Z   |  E   |  R   |  T   |      |           |  *   |   Y  |   U  |   I  |   O  |   P  | BCKSPC |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |CAPSLOCK|   Q  |  S   |  D   |  F   |  G   |------|           |------|   H  |   J  |   K  |   L  |   M  | ENTER  |
 * |--------+------+------+------+------+------|  !   |           |  ,   |------+------+------+------+------+--------|
 * | LShift |   W  |   X  |   C  |   V  |  B   |      |           |      |   B  |   N  |   .  |   :  |  ↑   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |CTRL  | < > | Alt  | space | SPACE|                                       |SPACE| AltGR |   ←  |  ↓  |   →   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | F8   | F9   |       | WIN  | DEL  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | LT(  |      | F10  |       | PgUp |        |      |
 *                                 |SPACE |  F5  |------|       |------|   F2   |  COMBO_COMMENT_BLOCK_OR_RENAME |
 *                                 | ,L2) |      | F11  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */  //KC_RCTL
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// KC_COMM/*;.*/
// left hand
KC_ESCAPE,             KC_1,                   KC_2,             KC_3,             KC_4,               KC_5,                 FR_UGRV,
KC_TAB,                KC_Q,                   KC_W,             KC_E,             KC_R,               KC_T,                 KC_TRNS,
KC_CAPSLOCK,           KC_A,                   SAVE,             KC_D,             KC_F,               KC_G,
KC_LSHIFT,             KC_Z,                   CUT,              COPY,             PAST,               KC_B,                 FR_EXLM,
//LCTL_T(LCTL(KC_SPC))
KC_LCTL,  FR_LESS,             KC_LALT,          KC_SPC,          KC_SPC,

                                                                                                                        KC_F8,                      KC_F9,
                                                                                                                                                    KC_F10,
                                                                                                                        LT(LAYER_2,KC_SPC), KC_F5,  KC_F11,

// right hand
FR_EQL,          KC_6,                   KC_7,             KC_8,             KC_9,               KC_0,                 TG(LAYER_2),
FR_ASTR,          KC_Y,                   KC_U,             KC_I,             KC_O,               KC_P,                 KC_BSPACE,
                  KC_H,                   KC_J,             KC_K,             KC_L,               KC_SCLN,              KC_ENT,
FR_COLN,          KC_B,                   KC_N,             FR_DOT,           KC_DOT/*:/*/,       KC_UP,                KC_RSHIFT,
                                          KC_SPC,          KC_RALT,          KC_LEFT,            KC_DOWN,              KC_RIGHT,

                                                                                                                        KC_RGUI, KC_DEL,
                                                                                                                        KC_PGUP,
                                                                                                                        KC_PGDN,KC_F2, COMMENT_BLOCK_OR_RENAME
    ),
/* Keymap 1: Shift Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |     |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |       |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Keymap 1: SHIFT Layer-1
[SHIFT] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Layer-2
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |PrtScr|        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |  \   | HOME |           |      |  °   |   ^  |  7   |  8   | 9    |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |  ~   |  `   |  [   |  ]   |------|           |------|  ¨   |   $  |  4   |  5   | 6    |        |
 * |---------+------+------+------+------+------|  END |           |      |------+------+------+------+------+--------|
 * |         |      |      |  {   |  }   |  |   |      |           |      |  =   |   +  |  1   |  2   | 3    |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |  &   |  $   |                                       |   ?  |  0   |  .   | !    |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |       |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[LAYER_2] = LAYOUT_ergodox(
       KC_TRNS, KC_F1,              KC_F2,     KC_F3,  KC_F4,    KC_F5,   KC_TRNS,
       KC_TRNS, KC_TRNS,            KC_TRNS,   KC_TRNS,KC_TRNS,  FR_BSLS, KC_HOME,
       KC_TRNS, FR_TILD,            FR_GRV,    FR_LBRC, FR_RBRC,  KC_TRNS,
       KC_TRNS, KC_TRNS,            KC_TRNS,   FR_LCBR, FR_RCBR,  FR_PIPE, KC_END,
       KC_TRNS, KC_TRNS,            KC_TRNS,        FR_AMP,      FR_DLR,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_F6, KC_F7, KC_F8, KC_F9, KC_PSCREEN, KC_TRNS,
       KC_TRNS,  FR_OVRR, FR_CIRC, M_7, M_8, M_9, KC_TRNS,
                 FR_UMLT, FR_DLR, M_4, M_5, M_6, KC_TRNS,
       KC_TRNS,  FR_EQL, FR_PLUS, M_1, M_2, M_3, KC_TRNS,
                          FR_EXLM, M_0, FR_DOT, FR_QUES, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SHIFT)                // FN1 - Momentary Layer 1 (SHIFTED)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case SHIFTED:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            layer_on(SHIFT);
        } else {
            layer_off(SHIFT);
            unregister_code(KC_LSFT);
        }
        break;
  }
  return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
/*      case CUT:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          uint16_t index = M_A_GRAVE - M_C_CEDILLE_MAJ;
          send_string(alt_codes[index][is_mac]); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_CUT][0]);
        }
      }
      return false;
      break;    */
    case CUT:
        if (record->event.pressed) {
          key_timer = timer_read(); // if the key is being pressed, we start the timer.
        } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("x"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_CUT][0]);
        }
      }
      return false;
      break;
      case COPY:
        if (record->event.pressed) {
          key_timer = timer_read(); // if the key is being pressed, we start the timer.
        } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("c"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_COPY][0]);
        }
      }
      return false;
      break;
    case PAST:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("v"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_PAST][0]);
        }
      }
      return false;
      break;
    case SAVE:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("s"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_SAVE][0]);
        }
      }
      return false;
      break;
    case COMMENT_BLOCK_OR_RENAME:
        if (record->event.pressed) {
            key_timer = timer_read(); // if the key is being pressed, we start the timer.
        } else {
            if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
                register_code(KC_F6); // if the key is released before KEY_DELAY then we send ...
            }else{ // if the key is released after KEY_DELAY then we send CTRL+c
             send_string(combo_codes[COMBO_COMMENT_BLOCK_OR_RENAME][0]);
            }
        }
    return false;
    break;
    case REFRESH_CACHE:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          register_code(KC_F5); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_REFRESH_CACHE][0]);
        }
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
          rgblight_init();
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};

/* Empty Keymap: -
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |       |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
