#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _SYMBOLS,
    _NAV,
    _FUNCTION,
};

enum custom_keycodes {
    UP_DIR = SAFE_RANGE,
    CURR_DIR,
    HOME_DIR,
    SEL_FWD,
    SEL_BACK,
    SEL_LINE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
                       KC_Q, KC_L,         KC_D,         KC_C,         KC_V,                KC_J,    KC_F,         KC_O,         KC_U,         KC_DOT,
               LGUI_T(KC_N), LALT_T(KC_R), LCTL_T(KC_T), LSFT_T(KC_S), KC_G,                KC_Y,    RSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E), LGUI_T(KC_I),
              KC_RALT, KC_Z, KC_X,         KC_M,         KC_W,         KC_B,                KC_K,    KC_P,         KC_QUOT,      KC_SCLN,      KC_COMM, KC_LGUI,
              LT(_FUNCTION, KC_TAB), LT(_SYMBOLS, KC_SPC), LT(_NAV, KC_ENT),                LT(_NAV, KC_ESC), LT(_SYMBOLS, KC_BSPC), LT(_FUNCTION, KC_DEL)
    ),

    [_SYMBOLS] = LAYOUT(
                               KC_BSLS, KC_LT,   KC_GT,    KC_MINS, KC_PERC,                KC_PIPE, KC_LBRC, KC_RBRC, KC_GRV,  _______,
                               KC_ASTR, KC_PLUS, KC_SLSH,  KC_EQL,  KC_AMPR,                KC_HASH, KC_LPRN, KC_RPRN, KC_EXLM, KC_QUES,
                      KC_LGUI, KC_CIRC, KC_TILD, CURR_DIR, UP_DIR, HOME_DIR,                KC_AT,   KC_LCBR, KC_RCBR, KC_DLR,  RALT(KC_E), KC_LGUI,
                                                 KC_LALT,  KC_LCTL, KC_LSFT,                KC_RSFT, KC_LCTL, KC_LALT
    ),

    [_NAV] = LAYOUT(
                 KC_CIRC, KC_9,         KC_8,         KC_7,         _______,                KC_PGUP,  KC_HOME,         _______,       KC_END,          _______,
         LGUI_T(KC_PAST), LALT_T(KC_3), LCTL_T(KC_2), LSFT_T(KC_1), KC_PLUS,                KC_PGDN,  RSFT_T(KC_LEFT), LCTL_T(KC_UP), LALT_T(KC_RGHT), KC_LGUI,
        _______, KC_SLSH, KC_6,         KC_5,         KC_4,         KC_MINS,                SEL_LINE, SEL_BACK,        KC_DOWN,       SEL_FWD,         _______, _______,
                                                      KC_DOT, KC_0, KC_COMM,                _______,  _______,  _______
    ),

    [_FUNCTION] = LAYOUT(
                                       KC_F10, KC_F9, KC_F8, KC_F7, _______,                _______, KC_BRID, KC_BRIU, ______, _______,
       LGUI_T(KC_F11), LALT_T(KC_F3), LCTL_T(KC_F2), LSFT_T(KC_F1), _______,                _______, RSFT_T(KC_VOLD), LCTL_T(KC_VOLU), LALT_T(KC_MUTE), LGUI_T(KC_PSCR),
                              _______, KC_F12, KC_F6, KC_F5, KC_F4, _______,                _______, KC_MPRV, KC_MNXT, KC_MPLY, _______, _______,
                                                  _______, _______, _______,                _______, _______, _______
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case UP_DIR:
                send_string("../");
                return false;
            case CURR_DIR:
                send_string("./");
                return false;
            case HOME_DIR:
                send_string("~/");
                return false;
            case SEL_FWD:
                tap_code16(LCTL(LSFT(KC_RGHT)));
                return false;
            case SEL_BACK:
                tap_code16(LCTL(LSFT(KC_LEFT)));
                return false;
            case SEL_LINE:
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
                return false;
        }
    }
    return true;
}
