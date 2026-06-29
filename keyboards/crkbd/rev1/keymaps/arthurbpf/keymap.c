/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Manna Harbour

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Miryoku layout (QWERTY) adapted for Corne 3x6+3 with outer columns kept.
*/

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _EXTRA,
    _TAP,
    _BUTTON,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN,
    _GAME,
};

// Row/col helper macros for the outer columns (kept from original layout)
#define OLB_L0 KC_TAB   // Left outer top
#define OLB_L1 KC_LCTL  // Left outer middle
#define OLB_L2 KC_LSFT  // Left outer bottom
#define OLB_R0 KC_BSPC  // Right outer top
#define OLB_R1 KC_QUOT  // Right outer middle
#define OLB_R2 KC_ESC   // Right outer bottom

// Clipboard keys (CUA-compatible defaults)
#define CLIP_RDO KC_AGIN
#define CLIP_PST S(KC_INS)
#define CLIP_CPY C(KC_INS)
#define CLIP_CUT S(KC_DEL)
#define CLIP_UND KC_UNDO

// Home row mods
#define H_A LGUI_T(KC_A)
#define H_S LALT_T(KC_S)
#define H_D LCTL_T(KC_D)
#define H_F LSFT_T(KC_F)
#define H_J RSFT_T(KC_J)
#define H_K RCTL_T(KC_K)
#define H_L RALT_T(KC_L)
#define H_Q LGUI_T(KC_QUOT)

// Thumb keys
#define T_ESC  LT(_MEDIA, KC_ESC)
#define T_SPC  LT(_NAV,   KC_SPC)
#define T_TAB  LT(_MOUSE, KC_TAB)
#define T_ENT  LT(_SYM,   KC_ENT)
#define T_BSPC LT(_NUM,   KC_BSPC)
#define T_DEL  LT(_FUN,   KC_DEL)

// Common left-hand mod column (for Nav/Mouse/Media layers)
#define LMOD0 QK_BOOT
#define LMOD1 KC_LGUI
#define LMOD2 KC_LALT
#define LMOD3 KC_LCTL
#define LMOD4 KC_LSFT

// Tap-dance: Miryoku-style layer selection (double-tap to set default layer)
enum td_keycodes {
    TD_BASE,
    TD_EXTRA,
    TD_TAP,
    TD_BOOT,
};

void td_fn_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
}

void td_fn_base(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _BASE);
    }
}

void td_fn_extra(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _EXTRA);
    }
}

void td_fn_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _TAP);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BASE]  = ACTION_TAP_DANCE_FN(td_fn_base),
    [TD_EXTRA] = ACTION_TAP_DANCE_FN(td_fn_extra),
    [TD_TAP]   = ACTION_TAP_DANCE_FN(td_fn_tap),
    [TD_BOOT]  = ACTION_TAP_DANCE_FN(td_fn_boot),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base: QWERTY with home row mods (Miryoku)
 *
 * Outer columns preserved: TAB/LCTL/LSFT on left, BSPC/'/ESC on right.
 * Thumbs: Esc(Media)  Space(Nav)  Tab(Mouse)  |  Enter(Sym)  Bspc(Num)  Del(Fun)
 */
[_BASE] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     OLB_L0,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   OLB_R0,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L1,   H_A,    H_S,    H_D,    H_F,    KC_G,                    KC_H,   H_J,    H_K,    H_L,    H_Q,    OLB_R1,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L2,   LT(_BUTTON, KC_Z), ALGR_T(KC_X), KC_C, KC_V, KC_B,      KC_N,   KC_M,   KC_COMM, ALGR_T(KC_DOT), LT(_BUTTON, KC_SLSH), OLB_R2,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              T_ESC,  T_SPC,  T_TAB,    T_ENT,  T_BSPC, T_DEL
//                                           `--------------------------'  `--------------------------'
),

/*
 * Extra: QWERTY (alternative base accessed via hold)
 */
[_EXTRA] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     OLB_L0,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   OLB_R0,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L1,   H_A,    H_S,    H_D,    H_F,    KC_G,                    KC_H,   H_J,    H_K,    H_L,    H_Q,    OLB_R1,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L2,   KC_Z,   ALGR_T(KC_X), KC_C, KC_V, KC_B,                 KC_N,   KC_M,   KC_COMM, ALGR_T(KC_DOT), KC_SLSH, OLB_R2,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              T_ESC,  T_SPC,  T_TAB,    T_ENT,  T_BSPC, T_DEL
//                                           `--------------------------'  `--------------------------'
),

/*
 * Tap: QWERTY without dual-function keys (no HRMs, no layer-tap)
 */
[_TAP] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     OLB_L0,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   OLB_R0,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L1,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                    KC_H,   KC_J,   KC_K,   KC_L,   KC_QUOT, OLB_R1,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L2,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                    KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, OLB_R2,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              KC_ESC, KC_SPC, KC_TAB,    KC_ENT, KC_BSPC, KC_DEL
//                                           `--------------------------'  `--------------------------'
),

/*
 * Button: mouse buttons + clipboard + mods (for integrated/external pointing devices)
 */
[_BUTTON] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, CLIP_UND, CLIP_CUT, CLIP_CPY, CLIP_PST, CLIP_RDO,     CLIP_RDO, CLIP_PST, CLIP_CPY, CLIP_CUT, CLIP_UND, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_NO,        KC_NO,   KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LGUI,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, CLIP_UND, CLIP_CUT, CLIP_CPY, CLIP_PST, CLIP_RDO,     CLIP_RDO, CLIP_PST, CLIP_CPY, CLIP_CUT, CLIP_UND, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_NO,   MS_BTN1, MS_BTN2,  MS_BTN2, MS_BTN1, MS_BTN3
//                                           `--------------------------'  `--------------------------'
),

/*
 * Nav: navigation and editing (hold left Space)
 * Cursor keys on home, line/page movement below, clipboard above.
 */
[_NAV] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LMOD0,    TD(TD_BOOT), TD(TD_TAP), TD(TD_EXTRA), TD(TD_BASE), KC_NO, CLIP_RDO, CLIP_PST, CLIP_CPY, CLIP_CUT, CLIP_UND, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     LMOD1,    LMOD2,   LMOD3,   LMOD4,   KC_NO,   KC_NO,              CW_TOGG,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_NO,   KC_ALGR, KC_NO,   KC_NO,   KC_NO,              KC_INS,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,  KC_ENT,   KC_BSPC,  KC_DEL
//                                           `--------------------------'  `--------------------------'
),

/*
 * Mouse: mouse emulation (hold left Tab)
 * Cursor movement mirrors Nav, wheel mirrors page movement. Mouse buttons on thumbs.
 */
[_MOUSE] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LMOD0,    TD(TD_BOOT), TD(TD_TAP), TD(TD_EXTRA), TD(TD_BASE), KC_NO, CLIP_RDO, CLIP_PST, CLIP_CPY, CLIP_CUT, CLIP_UND, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     LMOD1,    LMOD2,   LMOD3,   LMOD4,   KC_NO,   KC_NO,              KC_NO,    MS_LEFT,  MS_DOWN,  MS_UP,    MS_RGHT,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_NO,   KC_ALGR, KC_NO,   KC_NO,   KC_NO,              KC_NO,    MS_WHLL,  MS_WHLD,  MS_WHLU,  MS_WHLR,  _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,  MS_BTN2,  MS_BTN1,  MS_BTN3
//                                           `--------------------------'  `--------------------------'
),

/*
 * Media: media control + RGB (hold left Esc)
 * Media keys mirror Nav layout. RGB on top row. Bluetooth on bottom row.
 */
[_MEDIA] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LMOD0,    TD(TD_BOOT), TD(TD_TAP), TD(TD_EXTRA), TD(TD_BASE), KC_NO, RM_TOGG,  RM_NEXT,  RM_HUEU,  RM_SATU,  RM_VALU,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     LMOD1,    LMOD2,   LMOD3,   LMOD4,   KC_NO,   KC_NO,              KC_NO,    KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_NO,   KC_ALGR, KC_NO,   KC_NO,   KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,  KC_MSTP,  KC_MPLY,  KC_MUTE
//                                           `--------------------------'  `--------------------------'
),

/*
 * Num: numerals and symbols (hold right Backspace)
 * Numpad-style numerals with symbols in remaining positions.
 */
[_NUM] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                TD(TD_BASE), TD(TD_EXTRA), TD(TD_TAP), TD(TD_BOOT), KC_NO,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                  KC_LSFT,  KC_LCTL, KC_LALT, KC_LGUI, KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,                KC_NO,    KC_NO,   KC_ALGR, KC_NO,   KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,   KC_MINS,  KC_0,    KC_DOT
//                                           `--------------------------'  `--------------------------'
),

/*
 * Sym: shifted symbols (hold right Enter)
 * Shifted symbols mirrored from Num layer.
 */
[_SYM] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,  KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                TD(TD_BASE), TD(TD_EXTRA), TD(TD_TAP), TD(TD_BOOT), KC_NO,  _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                KC_LSFT,  KC_LCTL, KC_LALT, KC_LGUI, KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,                KC_NO,    KC_NO,   KC_ALGR, KC_NO,   KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,   KC_UNDS,  KC_LPRN, KC_RPRN
//                                           `--------------------------'  `--------------------------'
),

/*
 * Fun: function keys + system (hold right Delete)
 * F-keys mirror Num layout with extras. App on tertiary thumb.
 */
[_FUN] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                TO(_GAME), TD(TD_BASE), TD(TD_EXTRA), TD(TD_TAP), TD(TD_BOOT), _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                KC_LSFT,  KC_LCTL, KC_LALT, KC_LGUI, KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,                KC_NO,    KC_NO,   KC_ALGR, KC_NO,   KC_NO,    _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,   KC_TAB,   KC_SPC,  KC_APP
//                                           `--------------------------'  `--------------------------'
),

/*
 * Game: plain QWERTY with no dual-function keys (no HRMs, no LT thumbs).
 * Activate: hold right Del (Fun) + tap right inner top key.
 * Deactivate: tap right outer bottom key.
 * Outer columns kept for Ctrl/Shift access during gaming.
 */
[_GAME] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     OLB_L0,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L1,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OLB_L2,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                    KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, TO(_BASE),
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              KC_ESC,  KC_SPC,  KC_TAB,   KC_ENT,  KC_BSPC, KC_DEL
//                                           `--------------------------'  `--------------------------'
),

};

#ifdef ENCODER_MAP_ENABLE
// Miryoku default encoders:
//   Left:  Volume down/up, Prev/Next track
//   Right: Mouse scroll down/up, Cursor left/right
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_EXTRA]  = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_TAP]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_BUTTON] = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_NAV]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_MOUSE]  = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_MEDIA]  = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_NUM]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_SYM]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_FUN]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_GAME]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
};
#endif

#ifdef OLED_ENABLE
#include <string.h>

// WPM / keylogger state
static uint16_t oled_activity_timer = 0;
static uint16_t oled_wpm_timer      = 0;
static uint16_t oled_key_count      = 0;
static uint8_t  oled_current_wpm    = 0;

#define KEYLOG_SIZE 10
static char    keylog_buf[KEYLOG_SIZE + 1] = "          ";

// Bongo cat frames (128x32 = 512 bytes each, generated by generate_bongo.py)
static const char PROGMEM bongo_idle[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xF0, 0xB8, 0x0C, 0x86, 0x82, 0x83, 0x83,
    0x83, 0xE3, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x83, 0x83, 0x83, 0x03, 0x03, 0xE3, 0xE3, 0xE3, 0x83,
    0x83, 0x83, 0x83, 0x82, 0x06, 0x0C, 0xB8, 0xF0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0xFC, 0x08, 0xF8, 0xF8,
    0xF8, 0xF8, 0x18, 0x18, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x18, 0xF8,
    0xF8, 0xF8, 0xF8, 0x08, 0xFC, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x64, 0x64, 0x67, 0x64, 0xEF, 0x6F,
    0xEF, 0x6F, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6F,
    0x6F, 0x6F, 0x6F, 0x64, 0x67, 0x64, 0xE0, 0x60, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const char PROGMEM bongo_typing[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xF0, 0xB8, 0x0C, 0x86, 0x82, 0x83, 0x83,
    0x83, 0xE3, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x83, 0x83, 0x83, 0x03, 0x03, 0xE3, 0xE3, 0xE3, 0x83,
    0x83, 0x83, 0x83, 0x82, 0x06, 0x0C, 0xB8, 0xF0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0xFC, 0x08, 0xF8, 0xF8,
    0xF8, 0xF8, 0x18, 0x18, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x18, 0x18, 0xF8,
    0xF8, 0xF8, 0xF8, 0x08, 0xFC, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0x03, 0x03, 0x03, 0x43, 0x8F, 0x0F,
    0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFC, 0xFC, 0xFC, 0xFF,
    0xFF, 0xFF, 0x0F, 0x03, 0x03, 0x43, 0x80, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static void render_bongo(void) {
    oled_write_raw_P(timer_elapsed(oled_activity_timer) < 1000 ? bongo_typing : bongo_idle, 512);
}

static void render_info(void) {
    char buf[12];
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    const char *names[] = {"BASE", "EXTRA","TAP",  "BUTTON","NAV",  "MOUSE",
                           "MEDIA","NUM",  "SYM",  "FUN",   "GAME"};
    uint8_t mods = get_mods();
    led_t   leds = host_keyboard_led_state();

    oled_write_P(PSTR(" "), false);
    oled_write(layer < 11 ? names[layer] : "?", false);

    oled_write_P(leds.caps_lock   ? PSTR(" CAP") : PSTR("    "), false);
    oled_write_P(leds.num_lock    ? PSTR(" NUM") : PSTR("    "), false);
    oled_write_P(leds.scroll_lock ? PSTR(" SCR") : PSTR("    "), false);

    oled_set_cursor(0, 1);
    oled_write_P((mods & MOD_MASK_GUI)   ? PSTR("GUI ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_ALT)   ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL)  ? PSTR("CTL ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SFT")  : PSTR("   "), false);

    oled_set_cursor(0, 2);
    oled_write_P(PSTR("WPM:"), false);
    uint8_t w = oled_current_wpm;
    buf[0] = '0' + (w / 100);
    buf[1] = '0' + (w / 10) % 10;
    buf[2] = '0' + w % 10;
    buf[3] = '\0';
    oled_write(buf, false);

    oled_set_cursor(0, 3);
    oled_write(keylog_buf, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? rotation : OLED_ROTATION_180;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_bongo();
    } else {
        render_info();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_activity_timer = timer_read();
        oled_key_count++;

        if (timer_elapsed(oled_wpm_timer) > 5000) {
            oled_current_wpm = (oled_key_count * 12) / 5;
            oled_key_count   = 0;
            oled_wpm_timer   = timer_read();
        }

        char c = 0;
        if (keycode >= KC_A && keycode <= KC_Z) {
            c = 'a' + (keycode - KC_A);
            if (get_mods() & MOD_MASK_SHIFT) c -= 32;
        } else if (keycode == KC_SPACE) {
            c = '_';
        } else if (keycode >= KC_1 && keycode <= KC_9) {
            c = '1' + (keycode - KC_1);
        } else if (keycode == KC_0) {
            c = '0';
        }

        if (c) {
            memmove(keylog_buf, keylog_buf + 1, KEYLOG_SIZE - 1);
            keylog_buf[KEYLOG_SIZE - 1] = c;
        }
    }
    return true;
}

#endif
