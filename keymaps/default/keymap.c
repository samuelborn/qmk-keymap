#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FUNCTION,
    _SYMBOLS,
    _NAV,
    _NUMPAD
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
                 KC_Q,         KC_L,         KC_D,         KC_C,         KC_V,               KC_J,    KC_F,         KC_O,         KC_U,         KC_COMMA,
                 LGUI_T(KC_N), LALT_T(KC_R), LCTL_T(KC_T), LSFT_T(KC_S), KC_G,               KC_Y,    RSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E), LGUI_T(KC_I),
        KC_RALT, KC_Z,         KC_X,         KC_M,         KC_W,         KC_B,               KC_K,    KC_P,         KC_QUOTE,     KC_SEMICOLON, KC_DOT,       KC_LGUI,
        LT(_FUNCTION, KC_TAB), LT(_SYMBOLS, KC_SPACE), LT(_NAV, KC_DELETE),                  LT(_NUMPAD, KC_ENTER), LT(_SYMBOLS, KC_BACKSPACE), LT(_FUNCTION, KC_ESCAPE)
    ),

    [_FUNCTION] = LAYOUT(
                 KC_F10, KC_F9, KC_F8,   KC_F7,   _______,        _______, KC_BRIGHTNESS_DOWN,  KC_BRIGHTNESS_UP,    KC_PRINT_SCREEN,     _______,
                 KC_F11, KC_F3, KC_F2,   KC_F1,   _______,        _______, KC_KB_VOLUME_DOWN,   KC_KB_VOLUME_UP,     KC_MUTE,             KC_PRINT_SCREEN,
        _______, KC_F12, KC_F6, KC_F5,   KC_F4,   _______,        _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE, _______,         _______,
                                _______, _______, _______,        _______, _______, _______
    ),

    [_SYMBOLS] = LAYOUT(
                 KC_CIRC, KC_MINUS, KC_LT, KC_GT, KC_BACKSLASH,     KC_BACKSLASH, KC_LBRC, KC_RBRC, KC_GRAVE, _______,
                 KC_ASTERISK, KC_PLUS, KC_SLASH, KC_EQUAL,          KC_AMPERSAND, KC_HASH, KC_LPRN, KC_RPRN, KC_EXCLAIM, KC_QUESTION,
        _______, KC_PERCENT, KC_TILDE, CURR_DIR, UP_DIR,            HOME_DIR, KC_AT, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_DOLLAR, RALT(KC_E), _______,
                                     _______, _______, _______,     _______, _______, _______
    ),

    [_NAV] = LAYOUT(
                 _______, _______, _______, _______, _______,            KC_PGUP,  KC_HOME,  _______, KC_END,  _______,
                 KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,            KC_PGDN,  KC_LEFT,  KC_UP,   KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______,            SEL_LINE, SEL_BACK, KC_DOWN, SEL_FWD,  _______, _______,
                                   _______, _______, _______,            _______,  _______,  _______
    ),

    [_NUMPAD] = LAYOUT(
                 KC_CIRC,  KC_9,    KC_8,    KC_7,    _______,        _______, _______, _______, _______, _______,
                 KC_ASTERISK,  KC_3,    KC_2,    KC_1,    KC_PLUS,        _______, KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI,
        _______, KC_SLASH,    KC_6,    KC_5,    KC_4,    KC_MINUS,       _______, _______, _______, _______, _______, _______,
                                       KC_0,    KC_DOT,  KC_COMMA,       _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_DIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
        case CURR_DIR:
            if (record->event.pressed) {
                SEND_STRING("./");
            }
            return false;
        case HOME_DIR:
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            return false;
        case SEL_FWD:
            if (record->event.pressed) {
                tap_code16(LCTL(LSFT(KC_RGHT)));
            }
            return false;
        case SEL_BACK:
            if (record->event.pressed) {
                tap_code16(LCTL(LSFT(KC_LEFT)));
            }
            return false;
        case SEL_LINE:
            if (record->event.pressed) {
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
            }
            return false;
    }
    return true;
}
