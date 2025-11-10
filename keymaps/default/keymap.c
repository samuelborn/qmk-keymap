#include QMK_KEYBOARD_H

enum layers {
    _L0,
    _L1,
    _L2,
    _L3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_L0] = LAYOUT(
                       KC_B, KC_L,         KC_D,         KC_C,         KC_V,        KC_J,    KC_F,         KC_O,         KC_U,            KC_DOT,
               LGUI_T(KC_N), LALT_T(KC_R), LCTL_T(KC_T), LSFT_T(KC_S), KC_G,        KC_Y,    RSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E),    LGUI_T(KC_I),
              KC_LGUI, KC_Q, KC_X,         KC_M,         RALT_T(KC_W), KC_Z,        KC_K,    RALT_T(KC_P), KC_QUOT,      KC_SCLN, KC_COMM, KC_LGUI,
                          LT(_L1, KC_TAB), LT(_L2, KC_SPC), LT(_L3, KC_ESC),        LT(_L3, KC_ENT), LT(_L2, KC_BSPC), LT(_L1, KC_DEL)
    ),

    [_L1] = LAYOUT(
        XXXXXXX, XXXXXXX,         KC_BRID,         KC_BRIU,         XXXXXXX,        XXXXXXX, KC_F7,         KC_F8,         KC_F9,         KC_F10,
LGUI_T(KC_PSCR), LALT_T(KC_MUTE), LCTL_T(KC_VOLD), RSFT_T(KC_VOLU), XXXXXXX,        XXXXXXX, LSFT_T(KC_F1), LCTL_T(KC_F2), LALT_T(KC_F3), LGUI_T(KC_F11),
KC_PWR, KC_SLEP, KC_MPLY,         KC_MPRV,         KC_MNXT,         XXXXXXX,        XXXXXXX, KC_F4,         KC_F5,         KC_F6,         KC_F12, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),

    [_L2] = LAYOUT(
         XXXXXXX, KC_LT,           KC_GT,           KC_MINS,        KC_UNDS,        KC_COLN, KC_7,         KC_8,         KC_9,         XXXXXXX,
 LGUI_T(KC_PAST), LALT_T(KC_PPLS), LCTL_T(KC_SLSH), LSFT_T(KC_EQL), KC_AMPR,        KC_DOT,  LSFT_T(KC_1), LCTL_T(KC_2), LALT_T(KC_3), LGUI_T(KC_0),
XXXXXXX, KC_CIRC, KC_PERC,         RALT(KC_E),      KC_DLR,         KC_PIPE,        KC_COMM, KC_4,         KC_5,         KC_6,         XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),

    [_L3] = LAYOUT(
        XXXXXXX, KC_BSLS,         KC_LBRC,         KC_RBRC,          KC_GRV,        KC_PGUP, KC_HOME,       XXXXXXX,  KC_END,         XXXXXXX,
LGUI_T(KC_QUES), LALT_T(KC_EXLM), LCTL_T(KC_LPRN), RSFT_T(KC_RPRN), KC_HASH,        KC_PGDN, KC_LEFT,       KC_UP,    KC_RGHT,        XXXXXXX,
XXXXXXX, XXXXXXX, KC_TILD,        KC_LCBR,         KC_RCBR,           KC_AT,        XXXXXXX, LCTL(KC_LEFT), KC_DOWN,  LCTL(KC_RIGHT), XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // Workaround for mod tap with non basic keycodes
            case RSFT_T(KC_RPRN):
                if (record->tap.count && record->event.pressed) {
                    tap_code16(KC_LPRN);
                    return false;
                }
                break;
            case LCTL_T(KC_LPRN):
                if (record->tap.count && record->event.pressed) {
                    tap_code16(KC_RPRN);
                    return false;
                }
                break;
            case LALT_T(KC_EXLM):
                if (record->tap.count && record->event.pressed) {
                    tap_code16(KC_EXLM);
                    return false;
                }
                break;
            case LGUI_T(KC_QUES):
                if (record->tap.count && record->event.pressed) {
                    tap_code16(KC_QUES);
                    return false;
                }
                break;
        }
    }
    return true;
}
