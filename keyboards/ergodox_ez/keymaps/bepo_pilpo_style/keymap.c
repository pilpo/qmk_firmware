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
  M_C_CEDILLE_MAJ,
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
  M_SLASH,
  M_E_AIGUE_MAJ,
  M_E_GRAVE_MAJ,
  M_E_CIRCONFLEXE_MAJ,
  M_VIRGULE,
  M_POINT,
  M_BARRE_VERTICALE,
  M_ET_COM,
  M_CROCHET_OUV,
  M_CROCHET_FERM,
  M_SIMPLE_QUOTE,
  M_PT_EXCLAM,
  M_DOUBLE_PT,
  M_PT_VIRGULE,
  M_PT_INTERROG,
  M_ACCENT_CIRCONF,
  M_U_GRAVE,
  M_QHOTE_INVERS,
  M_EURO,
  M_BACKSLASH,
  M_ACCO_OUV,
  M_ACCO_FERM,
  M_TILD,
  M_E_AIGUE,
  M_E_GRAVE,
  M_E_CIRCONFLEXE,
  M_E_TREMA,
  M_C_CEDILLE,
  M_A_GRAVE_MAJ,
  M_A_GRAVE,  
  M_M,
  M_M_MAJ,
  CPY
};
enum custom_macro {
  SHIFTED,
  SHIFTED_DOUBLE_PT,
  SHIFTED_PT_VIRGULE
};

#define KEY_DELAY 200
static uint16_t key_timer_cpy;

bool is_mac = false;  // Default to windows operation for extended character code sequences 
                      // for linux we have to use unicode
                      // for example see https://askubuntu.com/questions/88347/how-can-i-type-ascii-characters-like-alt-numpad-in-windows
                      // Alt + 255 on Windows creates a non-breaking space (ASCII 255)
                      // This character in Unicode is U+00A0
                      // On Ubuntu, type it as Ctrl + Shift + U then 00A0
                      // (cf unicode_map)
                      
char *alt_codes[][2] = { // if use on windows & mac & linux, use [][3], 0 for windows, 1 for mac et 2 for linux
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
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_1)),                              // ALT+61 =
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_7)),                              // ALT+47 /
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_4)),                // ALT+144 É
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_2)SS_TAP(X_KP_1)SS_TAP(X_KP_2)),                // ALT+212 È
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_2)SS_TAP(X_KP_1)SS_TAP(X_KP_0)),                // ALT+210 Ê
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_4)),                              // ALT+44 ,
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_4)SS_TAP(X_KP_6)),                              // ALT+46 .
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_4)),                // ALT+124 |
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_8)),                              // ALT+38 &
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_1)),                              // ALT+91 [
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_3)),                              // ALT+93 ]
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_9)),                              // ALT+39 '
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_3)),                              // ALT+33 !
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_5)SS_TAP(X_KP_8)),                              // ALT+58 :
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_5)SS_TAP(X_KP_9)),                              // ALT+59 ;
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_3)),                              // ALT+63 ?
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_4)),                              // ALT+94 ^
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_6)SS_TAP(X_KP_3)),                // ALT+163 ú
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_6)),                              // ALT+96 `
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_8)),  // ALT+0128 €
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_2)),                              // ALT+92 
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_3)),                // ALT+123 {
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_5)),                // ALT+125 }
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_6)),                // ALT+126 ~
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_0)),                // ALT+130 é
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_8)),                // ALT+138 è
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_6)),                // ALT+136 ê
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_7)),                // ALT+137 ë
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_5)),                // ALT+135 ç
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_8)SS_TAP(X_KP_3)),                // ALT+183 À
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_3)),                // ALT+133 à
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_0)SS_TAP(X_KP_9)),                // ALT+109 m
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_7)SS_TAP(X_KP_7)),                              // ALT+77 M
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
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   "  |   <  |   >  |   (  |   )  | _    |           | %    |   @  |   +  |   -  |   *  |   =  |  TL1   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   B  |   É  |   P  |   O  |   È  | HOME |           |  V   |   D  |   L  |   J  |   W  |   Ç  |  DEL   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TL1    |   A  |   U  |   I  |   E  |   ,  |------|           |------|   T  |   S  |   R  |   N  |   Q  |  ENTER |
 * |--------+------+------+------+------+------| END  |           |  C   |------+------+------+------+------+--------|
 * | LShift |   Ê  |   À  |   Y  |   X  |   .  |      |           |      |   '  |   M  |   G  |   H  |   F  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl  |   Z  | Alt  |   K  |   !  |                                       |   ←  |   ↑  |   ↓  |   →  | Ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | F4   | F5   |       | WIN  | DEL  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | F6   |       | PgUp |        |      |
 *                                 | SPACE|  F7  |------|       |------|  TL1   |SPACE |
 *                                 |      |      | F8   |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// X = M(2)
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
// left hand
KC_ESCAPE,        M_DOUBLE_QUOTE,         M_CHEVRON_INF,    M_CHEVRON_SUP,    M_PARENTHESE_OUV,   M_PARENTHESE_FERM,    M_TIRET_BAS,
KC_TAB,           KC_B,                   M_E_AIGUE,        KC_P,             KC_O,               M_E_GRAVE,            KC_HOME,
MO(LAYER_2),      KC_A,                   KC_U,             KC_I,             KC_E,               M_VIRGULE,
M(SHIFTED),       M_E_CIRCONFLEXE,        M_A_GRAVE,        KC_Y,             KC_X,               M_POINT,              KC_END,
KC_LCTRL,         KC_Z,                   KC_LALT,          KC_K,             M_PT_EXCLAM,

                                                                                                                        KC_F4,  KC_F5,
                                                                                                                                KC_F6,
                                                                                                                        KC_SPC,KC_F7, KC_F8,

// right hand
M_PRCT,           M_AROBASE,              M_PLUS,           M_MOINS,          M_FOIS,             M_EGAL,               TG(LAYER_2),
KC_V,             KC_D,                   KC_L,             KC_J,             KC_W,               M_C_CEDILLE,          KC_DEL,
                  KC_T,                   KC_S,             KC_R,             KC_N,               KC_Q,                 KC_ENT,                 
KC_C,             M_SIMPLE_QUOTE,         M_M,              KC_G,              KC_H,               KC_F,                M(SHIFTED),
                                          KC_LEFT,          KC_UP,            KC_DOWN,            KC_RIGHT,             KC_RCTRL,       

                                                                                                                        KC_RGUI, KC_DEL,
                                                                                                                        KC_PGUP,
                                                                                                                        KC_PGDN,MO(LAYER_2), KC_SPC
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
// Keymap 1: SHIFT Layer-1
[SHIFT] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_1,     KC_2,   KC_3,     KC_4,   KC_5,         KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_PT_VIRGULE,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_DOUBLE_PT,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_ACCENT_CIRCONF,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  M_PT_INTERROG, M_M_MAJ, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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

[LAYER_2] = LAYOUT_ergodox(
       KC_TRNS, KC_F1,              KC_F2,        KC_F3,          KC_F4,          KC_F5,          KC_TRNS,
       KC_TRNS, M_BARRE_VERTICALE,  KC_TRNS,      M_ET_COM,       M_CROCHET_OUV,  M_CROCHET_FERM, KC_TRNS,
       KC_TRNS, KC_TRNS,            M_U_GRAVE,    M_QHOTE_INVERS, M_EURO,         KC_TRNS,
       KC_TRNS, M_SLASH,            M_BACKSLASH,  M_ACCO_OUV,     M_ACCO_FERM,    M_TILD,         KC_TRNS,
       KC_TRNS, KC_TRNS,            KC_TRNS,      KC_TRNS,        KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_F6, KC_F7, KC_F8, KC_F9, KC_PSCREEN, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS,
                          KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_TRNS,
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
    case SHIFTED: // M(0)
        if (record->event.pressed) {
            register_code(KC_LSFT);
            layer_on(SHIFT);
        } else {
            layer_off(SHIFT);
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
;;;;;;;;;;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_PT_VIRGULE :
    case M_DOUBLE_PT :
    case M_ACCENT_CIRCONF :
    case M_PT_INTERROG :
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        uint16_t index = keycode - M_C_CEDILLE_MAJ;
        send_string(alt_codes[index][is_mac]);
      }
      return false;
      break;
  }

  switch (keycode) {
    case M_C_CEDILLE_MAJ ... M_M_MAJ :
      if (record->event.pressed) {
        uint16_t index = keycode - M_C_CEDILLE_MAJ;
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