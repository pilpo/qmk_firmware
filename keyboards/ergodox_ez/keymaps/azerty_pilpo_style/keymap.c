#include QMK_KEYBOARD_H
//#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "action_tapping.h"
//#include "keymap_extras/keymap_bepo.h"
#include "keymap_extras/keymap_french.h"

#define BASE 0 // default layer
#define SHIFT 1 // shift layer 
#define LAYER_2 2 // "first" true layer 
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
  // FIRST LETTER
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
  M_DIESE,
  M_DOLLAR,
  M_A_MAJ,
  M_Q_MAJ,
  M_A,
  M_Q,
  M_W_MAJ,
  M_W,  
  M_Z_MAJ,
  M_Z,
  // LAST LETTER
  // FIRST "MACRO"
  CUT,
  COPY,
  PAST,
  SAVE,
  UNDO,
  REFRESH_CACHE
  // LAST "MACRO"
};

enum custom_layer {
  SHIFTED
};

#define KEY_DELAY 130
static uint16_t key_timer;

bool is_mac = false;  // Default to windows operation for extended character code sequences 
                      // for linux we have to use unicode
                      // for example see https://askubuntu.com/questions/88347/how-can-i-type-ascii-characters-like-alt-numpad-in-windows
                      // Alt + 255 on Windows creates a non-breaking space (ASCII 255)
                      // This character in Unicode is U+00A0
                      // On Ubuntu, type it as Ctrl + Shift + U then 00A0
                      // (cf https://docs.qmk.fm/#/feature_unicode)
                      // SEND_STRING("€");
                      // unicode_input_start(); register_hex(0x20AC); unicode_input_finish();
  
char *alt_codes[][3] = { // if use on windows & mac & linux, use [][3], 0 for windows, 1 for mac et 2 for linux
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
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_5)SS_TAP(X_KP_1)),                // ALT+151 ù
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
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_5)),                              // ALT+35 # 
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_3)SS_TAP(X_KP_6)),                              // ALT+36 $ 
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_6)SS_TAP(X_KP_5)),                              // ALT+65 A 
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_8)SS_TAP(X_KP_1)),                              // ALT+81 Q
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_7)),                              // ALT+97 a
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_1)SS_TAP(X_KP_3)),                // ALT+113 q
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_8)SS_TAP(X_KP_7)),                              // ALT+87 W
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_1)SS_TAP(X_KP_9)),                // ALT+119 w
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_9)SS_TAP(X_KP_0)),                              // ALT+90 Z
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }, {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_2)),                // ALT+122 z
        SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET)))                                // mac shortcut for later
    }}; 

enum enum_combo_code {
  COMBO_CUT,
  COMBO_COPY,
  COMBO_PAST, 
  COMBO_SAVE,
  COMBO_UNDO,
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
        SS_LCTRL(SS_TAP(X_F5)),                  // REFRESH_CACHE
        SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET)))    // mac shortcut for later
    }}; 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
[BASE] = LAYOUT_ergodox(  // layer 0 : default
/* Keymap 0: Basic layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   &  |   é  |   "  |   '  |   (  | _    |           | %    |   -  |   è  |   _  |   ç  |   à  |  TL1   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   A  |  Z   |  E   |  R   |  T   |  !   |           |  '   |   Y  |   U  |   I  |   O  |   P  | BCKSPC |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TL1    |   Q  |  S   |  D   |  F   |  G   |------|           |------|   H  |   J  |   K  |   L  |   M  | ENTER  |
 * |--------+------+------+------+------+------|  ;   |           |  ,   |------+------+------+------+------+--------|
 * | LShift |   W  |   X  |   C  |   V  |  B   |      |           |      |   N  |   ,  |   ;  |   :  |  ↑   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |CTRL  | UNDO | Alt  |   K  |   Z  |                                       |   V  | CTRL |   ←  |  ↓  |   →   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | F8   | F9   |       | WIN  | DEL  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | LT(  |      | F10  |       | PgUp |        |      |
 *                                 |SPACE |  F5  |------|       |------|   F2   |SPACE |
 *                                 | ,L1) |      | F11  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// left hand
KC_ESCAPE,        KC_1,                   KC_2,             KC_3,             KC_4,               KC_5,                 M_TIRET_BAS,
KC_TAB,           KC_Q,                   KC_W,             KC_E,             KC_R,               KC_T,                 M_PT_EXCLAM,
TT(LAYER_2),      KC_A,                   KC_S,             KC_D,             KC_F,               KC_G,
M(SHIFTED),       KC_Z,                   KC_X,             KC_C,             KC_V,               KC_B,                 M_PT_VIRGULE,
KC_RCTL,          LCTL(KC_W),             KC_LALT,          SAVE,             KC_W,

                                                                                                                        KC_F8,                      KC_F9,
                                                                                                                                                    KC_F10,
                                                                                                                        LT(LAYER_2,KC_SPC), KC_F5,  KC_F11,

// right hand
M_PRCT,           KC_6,                   KC_7,             KC_8,             KC_9,               KC_0,                 TG(LAYER_2),
M_SIMPLE_QUOTE,   KC_Y,                   KC_U,             KC_I,             KC_O,               KC_P,                 KC_BSPACE,
                  KC_H,                   KC_J,             KC_K,             KC_L,               KC_SCLN,              KC_ENT,                 
M_VIRGULE,        KC_N,                   KC_M/*,?*/,       KC_COMM/*;.*/,    KC_DOT/*:/*/,       KC_UP,                M(SHIFTED),
                                          KC_V,             KC_LCTL,          KC_LEFT,            KC_DOWN,              KC_RIGHT,       

                                                                                                                        KC_RGUI, KC_DEL,
                                                                                                                        KC_PGUP,
                                                                                                                        KC_PGDN,KC_F2, KC_SPC
    ),
/* Keymap 1: Shift Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  1   |  2   |  3   |  4   |  5   |  #   |           |  ^   | 6    |  7   | 8    | 9    | 0    |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |  É   |      |      |      |      |           |  ?   |      |      |      |      | Ç    |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  È   |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  Ê   |  À   |      |      | :    |      |           |      |     |   ?  |   .  |   /  |       |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      | $    |                                       |     |      |      |      |      |
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
       KC_TRNS, KC_1,                 KC_2,   KC_3,     KC_4,   KC_5,         M_DIESE,
       KC_TRNS, KC_TRNS,              M_E_AIGUE_MAJ, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
       KC_TRNS, M_E_GRAVE_MAJ,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, M_E_CIRCONFLEXE_MAJ,  M_A_GRAVE_MAJ, KC_TRNS, KC_TRNS, M_DOUBLE_PT,  KC_TRNS,
       KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, M_DOLLAR,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       M_ACCENT_CIRCONF,  KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
       M_PT_INTERROG,  KC_TRNS, KC_TRNS, KC_TRNS, M_W_MAJ, M_C_CEDILLE_MAJ, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_Q_MAJ, KC_TRNS,
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
 * |         |      |      |  &   |   |  |  €   | HOME |           |      |      |      |  7   |  8   | 9    |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   ~  |  ù   |  `   |  [   |  ]   |------|           |------|      |      |  4   |  5   | 6    |        |
 * |---------+------+------+------+------+------|  END |           |      |------+------+------+------+------+--------|
 * |         |      |  \   |  {   |  }   |  /   |      |           |      |  F12 |      |  1   |  2   | 3    |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |  $   |                                       |      |  0   |  .   |      |      |
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
       KC_TRNS, KC_F1,              KC_F2,          KC_F3,          KC_F4,              KC_F5,          KC_TRNS,
       KC_TRNS, KC_TRNS,            KC_TRNS,        M_ET_COM,       M_BARRE_VERTICALE,  M_EURO,         KC_HOME,
       KC_TRNS, M_TILD,             M_U_GRAVE,      M_QHOTE_INVERS, M_CROCHET_OUV,      M_CROCHET_FERM,
       KC_TRNS, KC_TRNS,            M_BACKSLASH,    M_ACCO_OUV,     M_ACCO_FERM,        M_SLASH,         KC_END,
       KC_TRNS, KC_TRNS,            KC_TRNS,        KC_TRNS,        M_DOLLAR,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_F6, KC_F7, KC_F8, KC_F9, KC_PSCREEN, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, M_7, M_8, M_9, KC_TRNS,
                 KC_TRNS, KC_TRNS, M_4, M_5, M_6, KC_TRNS,
       KC_TRNS,  KC_F12, KC_TRNS, M_1, M_2, M_3, KC_TRNS,
                          KC_TRNS, M_0, M_POINT, KC_TRNS, KC_TRNS,
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
    case M_C_CEDILLE_MAJ ... M_Z :
      if( // handle the shift layer
          keycode == M_PT_VIRGULE 
        || keycode == M_DOUBLE_PT
        || keycode == M_ACCENT_CIRCONF
        || keycode == M_PT_INTERROG
        || keycode == M_DIESE
        || keycode == M_DOLLAR
        || keycode == M_C_CEDILLE_MAJ
        || keycode == M_A_GRAVE_MAJ
        || keycode == M_E_AIGUE_MAJ
        || keycode == M_E_GRAVE_MAJ
        || keycode == M_E_CIRCONFLEXE_MAJ
        || keycode == M_M_MAJ
        || keycode == M_A_MAJ
        || keycode == M_Q_MAJ
        || keycode == M_W_MAJ
        || keycode == M_Z_MAJ
      ){
        unregister_code(KC_LSFT);
      }
      if (record->event.pressed) {
        uint16_t index = keycode - M_C_CEDILLE_MAJ;
        send_string(alt_codes[index][is_mac]);
      }
      return false;
      break;
    case CUT:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          uint16_t index = M_A_GRAVE - M_C_CEDILLE_MAJ;
          send_string(alt_codes[index][is_mac]); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_CUT][is_mac]);
        }
      }
      return false;
      break;    
    case COPY:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("y"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_COPY][is_mac]);
        }
      }
      return false;
      break;    
    case PAST:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("x"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_PAST][is_mac]);
        }
      }
      return false;
      break;    
    case SAVE:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer) < KEY_DELAY) { // when the key is being released, we check the timer
          send_string("k"); // if the key is released before KEY_DELAY then we send ...
        }else{ // if the key is released after KEY_DELAY then we send CTRL+c
          send_string(combo_codes[COMBO_SAVE][is_mac]);
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
          send_string(combo_codes[COMBO_REFRESH_CACHE][is_mac]);
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