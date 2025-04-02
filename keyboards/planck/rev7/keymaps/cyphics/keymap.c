/* Copyright 2015-2023 Jack Humbert

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

#include "keycodes.h"
#include "keymap_us.h"
#include QMK_KEYBOARD_H
#include "keymap_swiss_fr.h"



enum planck_layers { _QWERTY, _QWERTZ, _LOWER, _RAISE, _SYMBOLS, _ADJUST, _PLOVER, _MISC, _PEPPY };

enum planck_keycodes { PLOVER = SAFE_RANGE, BACKLIT, EXT_PLV };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define MISC  MO(_MISC)

#define QWERTY PDF(_QWERTY)
// #define QWERTZ PDF(_QWERTZ)
// #define COLEMAK PDF(_COLEMAK)
// #define DVORAK PDF(_DVORAK)

// Tap dance declarations
enum {
    CT_CLN, TD_CTRL_ESC, TD_TAB_CAPS,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] =      ACTION_TAP_DANCE_TAP_HOLD(KC_COLN, KC_SCLN),
    //[CT_CLN] =      ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
    [TD_CTRL_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_ESC),
    [TD_TAB_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS),
};


void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}


#define ALGR_A  ALGR(KC_A)
#define ALGR_S  ALGR(KC_S)
#define ALGR_6  ALGR(KC_6)
#define ALGR_0  ALGR(KC_0)
#define ALGR_U  ALGR(KC_U)
#define ALGR_C  ALGR(KC_C)
#define ALGR_E  ALGR(KC_E)
#define ALGR_QU ALGR(KC_QUOT)

// TODO :
// - put arrow keys in other layer
// - create held layer (possibly with CTRL?)

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────────────┬─────┬──────┬──────┬───────┬──────┬─────┬───────┬──────┬──────┬────┬──────┐
//    │       tab       │  q  │  w   │  e   │   r   │  t   │  y  │   u   │  i   │  o   │ p  │ bspc │
//    ├─────────────────┼─────┼──────┼──────┼───────┼──────┼─────┼───────┼──────┼──────┼────┼──────┤
//    │ TD(TD_CTRL_ESC) │  a  │  s   │  d   │   f   │  g   │  h  │   j   │  k   │  l   │ ;  │  '   │
//    ├─────────────────┼─────┼──────┼──────┼───────┼──────┼─────┼───────┼──────┼──────┼────┼──────┤
//    │      lsft       │  z  │  x   │  c   │   v   │  b   │  n  │   m   │  ,   │  .   │ /  │ ent  │
//    ├─────────────────┼─────┼──────┼──────┼───────┼──────┼─────┼───────┼──────┼──────┼────┼──────┤
//    │     BACKLIT     │     │ lgui │ lalt │ LOWER │ MISC │ spc │ RAISE │ left │ down │ up │ rght │
//    └─────────────────┴─────┴──────┴──────┴───────┴──────┴─────┴───────┴──────┴──────┴────┴──────┘
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB          , KC_Q    , KC_W    , KC_E    , KC_R  , KC_T , KC_Y   , KC_U  , KC_I    , KC_O    , KC_P    , KC_BSPC ,
  TD(TD_CTRL_ESC) , KC_A    , KC_S    , KC_D    , KC_F  , KC_G , KC_H   , KC_J  , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
  KC_LSFT         , KC_Z    , KC_X    , KC_C    , KC_V  , KC_B , KC_N   , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , KC_ENT  ,
  BACKLIT         , _______ , KC_LGUI , KC_LALT , LOWER , MISC , KC_SPC , RAISE , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬──────┬──────┬──────┬──────┐
//    │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8   │  9   │  0   │ bspc │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼──────┼──────┤
//    │  ~  │  (  │  )  │  #  │  =  │  %  │  ^  │  -  │  *   │  {   │  }   │  [   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼──────┼──────┤
//    │  |  │  !  │  @  │  +  │  $  │     │  _  │  &  │  <   │  >   │  \   │  ]   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼──────┼──────┤
//    │     │     │     │     │     │     │     │     │ mnxt │ vold │ volu │ mply │
//    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴──────┴──────┴──────┴──────┘
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC,
  KC_TILD , KC_LPRN , KC_RPRN , KC_HASH , KC_EQL  , KC_PERC , KC_CIRC , KC_MINS , KC_ASTR , KC_LCBR , KC_RCBR , KC_LBRC,
  KC_PIPE , KC_EXLM , KC_AT   , KC_PLUS , KC_DLR  , _______ , KC_UNDS , KC_AMPR , KC_LT   , KC_GT   , KC_BSLS , KC_RBRC,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MNXT , KC_VOLD , KC_VOLU , KC_MPLY
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
//    │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │  ~  │  (  │  )  │  #  │  =  │  %  │  ^  │  -  │  *  │  {  │  }  │  [  │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │  |  │  !  │  @  │  +  │  $  │  :  │  _  │  &  │  <  │  >  │  \  │  ]  │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │     │     │     │     │     │     │     │     │
//    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_PEPPY] = LAYOUT_planck_grid(
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______,
  KC_TILD , KC_LPRN , KC_RPRN , KC_HASH , KC_EQL  , KC_PERC , KC_CIRC , KC_MINS , KC_ASTR , KC_LCBR , KC_RCBR , KC_LBRC,
  KC_PIPE , KC_EXLM , KC_AT   , KC_PLUS , KC_DLR  , KC_COLN , KC_UNDS , KC_AMPR , KC_LT   , KC_GT   , KC_BSLS , KC_RBRC,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────┬─────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
//    │  `  │     │     │      │ home │      │      │ end  │ ms_u │      │      │ del  │
//    ├─────┼─────┼─────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
//    │ del │     │     │ btn2 │ btn1 │ btn3 │ wh_d │ ms_l │ ms_d │ ms_r │ wh_u │      │
//    ├─────┼─────┼─────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │     │     │ btn4 │ btn5 │ bTN6 │      │ pgdn │ pgup │      │      │      │
//    ├─────┼─────┼─────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
//    │     │     │     │      │      │      │      │      │ mnxt │ vold │ volu │ mply │
//    └─────┴─────┴─────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
[_LOWER] = LAYOUT_planck_grid(
  KC_GRV  , _______ , _______ , _______ , KC_HOME , _______ , _______ , KC_END  , KC_MS_U , _______ , _______ , KC_DEL ,
  KC_DEL  , _______ , _______ , KC_BTN2 , KC_BTN1 , KC_BTN3 , KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_U , _______,
  _______ , _______ , _______ , KC_BTN4 , KC_BTN5 , KC_BTN6 , _______ , KC_PGDN , KC_PGUP , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MNXT , KC_VOLD , KC_VOLU , KC_MPLY
),

//    ┌─────────┬─────┬─────┬─────┬─────┬─────┬─────┬────────┬────────┬────────┬────────┬─────────┐
//    │ QK_BOOT │ f1  │ f2  │ f3  │ f4  │     │     │        │        │ ALGR_6 │ ALGR_U │ ALGR_0  │
//    ├─────────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┼────────┼────────┼────────┼─────────┤
//    │ DB_TOGG │ f5  │ f6  │ f7  │ f8  │     │     │        │ ALGR_E │ ALGR_A │ ALGR_S │ ALGR_QU │
//    ├─────────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┼────────┼────────┼────────┼─────────┤
//    │  caps   │ f9  │ f10 │ f11 │ f12 │     │     │ ALGR_C │        │        │        │         │
//    ├─────────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┼────────┼────────┼────────┼─────────┤
//    │         │     │     │     │     │     │     │        │        │        │        │         │
//    └─────────┴─────┴─────┴─────┴─────┴─────┴─────┴────────┴────────┴────────┴────────┴─────────┘
[_ADJUST] = LAYOUT_planck_grid(
  QK_BOOT , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ , _______ , _______ , _______ , ALGR_6  , ALGR_U  , ALGR_0 ,
  DB_TOGG , KC_F5   , KC_F6   , KC_F7   , KC_F8   , _______ , _______ , _______ , ALGR_E  , ALGR_A  , ALGR_S  , ALGR_QU,
  KC_CAPS , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ , _______ , ALGR_C  , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────────┬─────┬─────┬─────┬─────┬─────┬─────┬────────┬──────┬────────┬────────┬─────────┐
//    │ QK_BOOT │ f1  │ f2  │ f3  │ f4  │     │     │        │  up  │ ALGR_6 │ ALGR_U │ ALGR_0  │
//    ├─────────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┼──────┼────────┼────────┼─────────┤
//    │ DB_TOGG │ f5  │ f6  │ f7  │ f8  │     │     │  left  │ down │  rght  │ ALGR_S │ ALGR_QU │
//    ├─────────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┼──────┼────────┼────────┼─────────┤
//    │  caps   │ f9  │ f10 │ f11 │ f12 │     │     │ ALGR_C │      │        │        │         │
//    ├─────────┼─────┼─────┼─────┼─────┼─────┼─────┼────────┼──────┼────────┼────────┼─────────┤
//    │         │     │     │     │     │     │     │        │      │        │        │         │
//    └─────────┴─────┴─────┴─────┴─────┴─────┴─────┴────────┴──────┴────────┴────────┴─────────┘
[_MISC] = LAYOUT_planck_grid(
  QK_BOOT , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ , _______ , _______ , KC_UP   , ALGR_6   , ALGR_U  , ALGR_0 ,
  DB_TOGG , KC_F5   , KC_F6   , KC_F7   , KC_F8   , _______ , _______ , KC_LEFT , KC_DOWN , KC_RIGHT , ALGR_S  , ALGR_QU,
  KC_CAPS , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ , _______ , ALGR_C  , _______ , _______  , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______
)
};

/* clang-format on */

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool play_encoder_melody(uint8_t index, bool clockwise);

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ENCODER_MAP_ENABLE
    if (IS_ENCODEREVENT(record->event) && record->event.pressed) {
        play_encoder_melody(record->event.key.col, record->event.type == ENCODER_CCW_EVENT);
    }
#endif
    tap_dance_action_t *action;
    switch (keycode) {
        case TD(CT_CLN):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
        case PLOVER:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
#endif
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw  = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
            break;
        case EXT_PLV:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
#endif
                layer_off(_PLOVER);
            }
            return false;
            break;
    }
    return true;
}

// /* clang-format off */
// float melody[8][2][2] = {
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
//     {{440.0f, 8}, {440.0f, 24}},
// };
/* clang-format on */

#define JUST_MINOR_THIRD 1.2
#define JUST_MAJOR_THIRD 1.25
#define JUST_PERFECT_FOURTH 1.33333333
#define JUST_TRITONE 1.42222222
#define JUST_PERFECT_FIFTH 1.33333333

#define ET12_MINOR_SECOND 1.059463
#define ET12_MAJOR_SECOND 1.122462
#define ET12_MINOR_THIRD 1.189207
#define ET12_MAJOR_THIRD 1.259921
#define ET12_PERFECT_FOURTH 1.33484
#define ET12_TRITONE 1.414214
#define ET12_PERFECT_FIFTH 1.498307

deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float*)note = 440.0f;
    return 0;
}

// bool play_encoder_melody(uint8_t index, bool clockwise) {
//     cancel_deferred_exec(tokens[index]);
//     if (clockwise) {
//         melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
//         melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
//         audio_play_melody(&melody[index], 2, false);
//     } else {
//         melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
//         melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
//         audio_play_melody(&melody[index], 2, false);
//     }
//     tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
//     return false;
// }

// bool encoder_update_user(uint8_t index, bool clockwise) {
//     return play_encoder_melody(index, clockwise);
// }

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
    }
    return true;
}
