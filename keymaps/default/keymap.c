#include QMK_KEYBOARD_H

enum layers {
    BASE,
    FUNC,
    NUM,
    NAV,
};

enum custom_keycodes {
    HOME = SAFE_RANGE,
    DEL_END,
    COPY_ALL,
};

const uint16_t PROGMEM cut[]        = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM copy[]       = {KC_L, KC_D, COMBO_END};
const uint16_t PROGMEM paste[]      = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM search[]     = {KC_F, KC_O, COMBO_END};
const uint16_t PROGMEM select_all[] = {KC_O, KC_U, COMBO_END};
const uint16_t PROGMEM copy_all[]   = {KC_M, RALT_T(KC_W), COMBO_END};

combo_t key_combos[] = {
    COMBO(cut, LCTL(KC_X)), COMBO(copy, LCTL(KC_C)), COMBO(paste, LCTL(KC_V)), COMBO(search, LCTL(KC_F)), COMBO(select_all, LCTL(KC_A)), COMBO(copy_all, COPY_ALL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [BASE] = LAYOUT(
                       KC_B, KC_L,         KC_D,         KC_C,         KC_V,        KC_J,    KC_F,         KC_O,         KC_U,            KC_DOT,
               LGUI_T(KC_N), LALT_T(KC_R), LCTL_T(KC_T), LSFT_T(KC_S), KC_G,        KC_Y,    RSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E),    LGUI_T(KC_I),
              KC_LGUI, KC_Q, KC_X,         KC_M,         RALT_T(KC_W), KC_Z,        KC_K,    RALT_T(KC_P), KC_QUOT,      KC_SCLN, KC_COMM, KC_LGUI,
                         LT(FUNC, KC_TAB), LT(NUM, KC_SPC), LT(NAV, KC_ESC),        LT(NAV, KC_ENT), LT(NUM, KC_BSPC), LT(FUNC, KC_DEL)
    ),

    [FUNC] = LAYOUT(
        XXXXXXX, XXXXXXX,         KC_BRID,         KC_BRIU,         XXXXXXX,        KC_F10, KC_F7,   KC_F8, KC_F9, XXXXXXX,
LGUI_T(KC_PSCR), LALT_T(KC_MUTE), LCTL_T(KC_VOLD), RSFT_T(KC_VOLU), XXXXXXX,        KC_F11, XXXXXXX, KC_F1, KC_F2, KC_F3,
KC_PWR, KC_SLEP, KC_MPLY,         KC_MPRV,         KC_MNXT,         XXXXXXX,        KC_F12, KC_F4,   KC_F5, KC_F6, XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),

    [NUM] = LAYOUT(
         XXXXXXX, KC_MINS,         KC_LT,           KC_GT,       RALT(KC_5),        KC_COLN, KC_7,         KC_8,         KC_9,         XXXXXXX,
 LGUI_T(KC_PAST), LALT_T(KC_PPLS), LCTL_T(KC_SLSH), LSFT_T(KC_EQL), KC_UNDS,        KC_DOT,  LSFT_T(KC_0), LCTL_T(KC_1), LALT_T(KC_2), LGUI_T(KC_3),
XXXXXXX, KC_CIRC, KC_PERC,         KC_EXLM,         KC_QUES,         KC_DLR,        KC_COMM, KC_4,         KC_5,         KC_6,         XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),

    [NAV] = LAYOUT(
        XXXXXXX, KC_BSLS,         KC_LBRC,         KC_RBRC,          KC_GRV,        KC_PGUP, KC_HOME,       DEL_END,  KC_END,         XXXXXXX,
LGUI_T(KC_PIPE), LALT_T(KC_AMPR), LCTL_T(KC_LPRN), RSFT_T(KC_RPRN), KC_HASH,        KC_PGDN, KC_LEFT,       KC_UP,    KC_RGHT,        XXXXXXX,
XXXXXXX, KC_TILD, HOME,           KC_LCBR,         KC_RCBR,           KC_AT,        XXXXXXX, LCTL(KC_LEFT), KC_DOWN,  LCTL(KC_RIGHT), XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case HOME:
                send_string("~/");
                return false;
            case DEL_END:
                tap_code16(LSFT(KC_END));
                tap_code(KC_DEL);
                return false;
            case COPY_ALL:
                tap_code16(LCTL(KC_A));
                tap_code16(LCTL(KC_C));
                return false;

            // Workaround for mod tap with non basic keycodes
            case RSFT_T(KC_RPRN):
                if (record->tap.count) {
                    tap_code16(KC_RPRN);
                    return false;
                }
                break;
            case LCTL_T(KC_LPRN):
                if (record->tap.count) {
                    tap_code16(KC_LPRN);
                    return false;
                }
                break;
            case LALT_T(KC_AMPR):
                if (record->tap.count) {
                    tap_code16(KC_AMPR);
                    return false;
                }
                break;
            case LGUI_T(KC_PIPE):
                if (record->tap.count) {
                    tap_code16(KC_PIPE);
                    return false;
                }
                break;
        }
    }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
