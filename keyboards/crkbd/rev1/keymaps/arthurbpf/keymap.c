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
     LMOD0,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              CLIP_RDO, CLIP_PST, CLIP_CPY, CLIP_CUT, CLIP_UND, _______,
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
     LMOD0,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              CLIP_RDO, CLIP_PST, CLIP_CPY, CLIP_CUT, CLIP_UND, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     LMOD1,    LMOD2,   LMOD3,   LMOD4,   KC_NO,   KC_NO,              KC_NO,    MS_LEFT,  MS_DOWN,  MS_UP,    MS_RIGHT, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_NO,   KC_ALGR, KC_NO,   KC_NO,   KC_NO,              KC_NO,    MS_WH_LEFT, MS_WH_DOWN, MS_WH_UP, MS_WH_RIGHT, _______,
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
     LMOD0,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              RM_TOGG,  RM_NEXT,  RM_HUEU,  RM_SATU,  RM_VALU,  _______,
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
     _______,  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    _______,
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
     _______,  KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    _______,
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
     _______,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                TO(_GAME), KC_NO,   KC_NO,   KC_NO,   KC_NO,    _______,
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
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_EXTRA]  = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_TAP]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_BUTTON] = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_NAV]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_MOUSE]  = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_MEDIA]  = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_NUM]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_SYM]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_FUN]    = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_GAME]   = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(MS_WH_DOWN, MS_WH_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
};
#endif
