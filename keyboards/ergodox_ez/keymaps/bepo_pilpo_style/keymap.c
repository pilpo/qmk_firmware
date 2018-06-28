#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "action_tapping.h"

#define BASE 0 // default layer
#define SHIFT 1 // shift layer 
#define LAYER_2 2 // "first" true layer 

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  M_C_CEDILLE,
  M_DOUBLE_QUOTE,
  M_CHEVRON_INF,
  M_CHEVRON_SUP,
  M_PARENTHESE_OUV,
  M_PARENTHESE_FERM,
  M_TIRET_BAS,
  M_PRCT,
  M_AROBASE,
  M_PLUS,
  M_MOINS,
  M_FOIS,
  M_EGAL,
  CPY
};

#define KEY_DELAY 200
static uint16_t key_timer_cpy;

bool is_mac = false;  // Default to windows operation for extended character code sequences 
                      // for future, use this on linux with unicode
                      // for example see https://askubuntu.com/questions/88347/how-can-i-type-ascii-characters-like-alt-numpad-in-windows
                      // Alt + 255 on Windows creates a non-breaking space (ASCII 255)
                      // This character in Unicode is U+00A0
                      // On Ubuntu, type it as Ctrl + Shift + U then 00A0
char *alt_codes[][2] = {
    {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8)),                // ALT+128 Ç
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_4)),                              // ALT+34 "
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_0)),                              // ALT+60 <
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_2)),                              // ALT+62 >
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_0)),                              // ALT+40 (
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_1)),                              // ALT+41 )
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_5)),                              // ALT+95 _
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_7)),                              // ALT+37 %
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_4)),                              // ALT+64 @
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_3)),                              // ALT+43 + 
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_5)),                              // ALT+45 -
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_2)),                              // ALT+42 * 
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_7)),                              // ALT+47 /
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_1)),                              // ALT+61 =
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }}; 

char *combo_codes[][2] = {
    {
        SS_LCTRL(SS_TAP(X_C)),                  // COPY
        SS_LALT(SS_TAP(X_RBRACKET))             // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_V)),                  // PAST
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }, {
        SS_LCTRL(SS_TAP(X_X)),                  // CUT
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }}; 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   "  |   <  |   >  |   (  |   )  | _    |           | %    |   @  |   +  |   -  |   *  |   =  |  TL1   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   B  |   É  |   P  |   O  |   È  | HOME |           |  V   |   D  |   L  |   J  |   W  |   Ç  |  DEL   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TL1    |   A  |   U  |   I  |   E  |   ,  |------|           |------|   T  |   S  |   R  |   N  |   Q  |  ENTER |
 * |--------+------+------+------+------+------| END  |           |  C   |------+------+------+------+------+--------|
 * | LShift |   Ê  |   À  |   Y  |   X  |   .  |      |           |      |   '  |   M  |   G  |   H  |   F  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl  |   Z  | Alt  |   K  |   !  |                                       |   ←  |   ↑  |   ↓  |   →  |  F4  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | F5   | F6   |       | WIN  | DEL  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | F7   |       | PgUp |        |      |
 *                                 | SPACE|ALTTAB|------|       |------|  FN      |SPACE |
 *                                 |      |      | F8   |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
// left hand
KC_ESCAPE,      M_DOUBLE_QUOTE,         M_CHEVRON_INF,   M_CHEVRON_SUP,   M_PARENTHESE_OUV,   M_PARENTHESE_FERM,   M_TIRET_BAS,
KC_DELT,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SHIFT),
KC_BSPC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
M(0),        CTL_T(KC_Z),  KC_X,   M_C_CEDILLE,   M(2),   CPY,   ALL_T(KC_NO),
LT(SHIFT,KC_GRV),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
                                      ALT_T(KC_APP),  KC_LGUI,
                                                      KC_HOME,
                                       KC_SPC,KC_BSPC,KC_END,

// right hand
M_PRCT,     M_AROBASE,   M_PLUS,  M_MOINS,   M_FOIS,   M_EGAL,             KC_MINS,
TG(SHIFT),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
KC_H,   KC_J,  KC_K,   KC_L,   LT(LAYER_2, KC_SCLN),GUI_T(KC_QUOT),
MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          KC_FN1,
KC_LALT,        CTL_T(KC_ESC),
KC_PGUP,
KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 1: Shift Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  1   |  2   |  3   |  4   |  5   |  #   |           |  $   | 6    |  7   | 8    | 9    | 0    |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      | ;    |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      | :    |      |           |      | ?    |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      | ^    |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |       |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SHIFTOLS
[SHIFT] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, M(1), KC_COMM, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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
/* Keymap 2: Layer-1
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |PrtScr|        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   |  |      |  &   |  [   |  ]   |      |           |      |      |      |  7   |  8   | 9    |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |  ù   |  `   |  €   |      |------|           |------|      |      |  4   |  5   | 6    |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  /   |  \   |  {   |  }   |  ~   |      |           |      |      |      |  1   |  2   | 3    |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |  0   |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |       |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[LAYER_2] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SHIFT)                // FN1 - Momentary Layer 1 (SHIFTols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0: // M(0)
        if (record->event.pressed) {
            register_code(KC_LSFT);
            layer_on(1);
        } else {
            layer_off(1);
            unregister_code(KC_LSFT);
        }
        break;       
    case 1: // M(1)
        if (record->event.pressed) {
            unregister_code(KC_LSFT);
            register_code(KC_DOT);
        } else {
            unregister_code(KC_DOT);
        }
        break; 
    case 2:
          if (record->event.pressed) {
            if (record->tap.count) {
              if (record->tap.interrupted) {
                record->tap.count = 0;
                // hold press action
                return MACRO(D(LCTRL), T(C));
              } else {
                // tap press action
                register_code(KC_C);
              }
            } else {
              // hold press action
              return MACRO(D(LCTRL), T(C));

            }
          } else {
            if (record->tap.count) {
              // tap release action
              unregister_code(KC_C);
            } else {
              // hold release action
              unregister_code(KC_LCTRL);
              unregister_code(KC_C);
            }
            record->tap.count = 0;
          }
          break;
    case 3:
          if (record->event.pressed) {
            if (record->tap.count) {
              if (record->tap.interrupted) {
                record->tap.count = 0;
                // hold press action
                return MACRO(D(LCTRL), T(V));

              } else {
                // tap press action
                register_code(KC_V);
              }
            } else {
              // hold press action
              return MACRO(D(LCTRL), T(V));

            }
          } else {
            if (record->tap.count) {
              // tap release action
              unregister_code(KC_V);
            } else {
              // hold release action
              unregister_code(KC_LCTRL);
              unregister_code(KC_V);
            }
            record->tap.count = 0;
          }
          break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_C_CEDILLE ... M_EGAL :
      if (record->event.pressed) {
        uint16_t index = keycode - M_C_CEDILLE;
        send_string(alt_codes[index][is_mac]);
      }
      return false;
      break;
    case CPY:
      if (record->event.pressed) {
        key_timer_cpy = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_cpy) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string(SS_TAP(X_C)); // if the key is released before KEY_DELAY then we send c
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[0][is_mac]);
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