#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _SYMBOLS,
    _NAV,
    _NUMPAD,
    _FUNCTION
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
                 KC_Q,         KC_L,         KC_D,         KC_C,         KC_V,               KC_J,    KC_F,         KC_O,         KC_U,         KC_DOT,
                 LGUI_T(KC_N), LALT_T(KC_R), LCTL_T(KC_T), LSFT_T(KC_S), KC_G,               KC_Y,    RSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E), LGUI_T(KC_I),
        KC_RALT, KC_Z,         KC_X,         KC_M,         KC_W,         KC_B,               KC_K,    KC_P,         KC_QUOTE,     KC_SEMICOLON, KC_COMMA,     KC_LGUI,
        LT(_FUNCTION, KC_TAB), LT(_SYMBOLS, KC_SPACE), LT(_NAV, KC_DELETE),                  LT(_NUMPAD, KC_ENTER), LT(_SYMBOLS, KC_BACKSPACE), LT(_FUNCTION, KC_ESCAPE)
    ),

    [_SYMBOLS] = LAYOUT(
                 KC_BACKSLASH, KC_LT, KC_GT, KC_MINUS, KC_PERCENT,                                        KC_PIPE, KC_LBRC, KC_RBRC, KC_GRAVE, _______,
                 LGUI_T(KC_ASTERISK), LALT_T(KC_PLUS), LCTL_T(KC_SLASH), LSFT_T(KC_EQUAL), KC_AMPERSAND,  KC_HASH, RSFT_T(KC_LPRN), LCTL_T(KC_RPRN), LALT_T(KC_EXCLAIM), LGUI_T(KC_QUESTION),
        _______, KC_CIRC,  KC_TILDE, CURR_DIR, UP_DIR, HOME_DIR,                                          KC_AT, KC_LCBR, KC_RCBR, KC_DOLLAR, RALT(KC_E), _______,
                                      _______, _______, _______,                                          _______, _______, _______
    ),

    [_NAV] = LAYOUT(
                 _______, _______, _______, _______, _______,           KC_PGUP,  KC_HOME,  _______, KC_END,   _______,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,           KC_PGDN,  KC_LEFT,  KC_UP,   KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______,           SEL_LINE, SEL_BACK, KC_DOWN, SEL_FWD,  _______, _______,
                                   _______, _______, _______,           _______,  _______,  _______
    ),

    [_NUMPAD] = LAYOUT(
                 KC_CIRC,     KC_9, KC_8, KC_7,   _______,              _______, _______, _______, _______, _______,
                 KC_ASTERISK, KC_3, KC_2, KC_1,   KC_PLUS,              _______, KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI,
        _______, KC_SLASH,    KC_6, KC_5, KC_4,   KC_MINUS,             _______, _______, _______, _______, _______, _______,
                                    KC_DOT, KC_0, KC_COMMA,             _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
                 KC_F10, KC_F9, KC_F8,   KC_F7,   _______,              _______, KC_BRIGHTNESS_DOWN,  KC_BRIGHTNESS_UP,    KC_PRINT_SCREEN,     _______,
                 KC_F11, KC_F3, KC_F2,   KC_F1,   _______,              _______, KC_KB_VOLUME_DOWN,   KC_KB_VOLUME_UP,     KC_MUTE,             KC_PRINT_SCREEN,
        _______, KC_F12, KC_F6, KC_F5,   KC_F4,   _______,              _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE, _______,         _______,
                                _______, _______, _______,              _______, _______, _______
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
