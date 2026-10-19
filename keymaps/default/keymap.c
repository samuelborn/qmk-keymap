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
    CUT_ALL,
};

// macOS treats the board as ISO, which swaps the grave and non-US backslash keys
#define MAC_GRV KC_NUBS
#define MAC_TILD S(KC_NUBS)

const uint16_t PROGMEM cut[]        = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM copy[]       = {KC_L, KC_D, COMBO_END};
const uint16_t PROGMEM paste[]      = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM search[]     = {KC_F, KC_O, COMBO_END};
const uint16_t PROGMEM select_all[] = {KC_O, KC_U, COMBO_END};
const uint16_t PROGMEM copy_all[]   = {KC_M, RALT_T(KC_W), COMBO_END};
const uint16_t PROGMEM cut_all[]    = {KC_X, KC_M, RALT_T(KC_W), COMBO_END};

combo_t key_combos[] = {
    COMBO(cut, LGUI(KC_X)), COMBO(copy, LGUI(KC_C)), COMBO(paste, LGUI(KC_V)), COMBO(search, LGUI(KC_F)), COMBO(select_all, LGUI(KC_A)), COMBO(copy_all, COPY_ALL), COMBO(cut_all, CUT_ALL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [BASE] = LAYOUT(
                       KC_B, KC_L,         KC_D,         KC_C,         KC_V,        KC_J,    KC_F,         KC_O,         KC_U,            KC_DOT,
               LCTL_T(KC_N), LALT_T(KC_R), LGUI_T(KC_T), LSFT_T(KC_S), KC_G,        KC_Y,    RSFT_T(KC_H), LGUI_T(KC_A), LALT_T(KC_E),    LCTL_T(KC_I),
              KC_LCTL, KC_Q, KC_X,         KC_M,         RALT_T(KC_W), KC_Z,        KC_K,    RALT_T(KC_P), KC_QUOT,      KC_SCLN, KC_COMM, KC_CAPS,
                         LT(FUNC, KC_TAB), LT(NUM, KC_SPC), LT(NAV, KC_ESC),        LT(NAV, KC_ENT), LT(NUM, KC_BSPC), LT(FUNC, KC_DEL)
    ),

    [FUNC] = LAYOUT(
        XXXXXXX, XXXXXXX,         KC_BRID,         KC_BRIU,         XXXXXXX,        KC_F10, KC_F7,   KC_F8, KC_F9, XXXXXXX,
LCTL_T(KC_PSCR), LALT_T(KC_MUTE), LGUI_T(KC_VOLD), RSFT_T(KC_VOLU), XXXXXXX,        KC_F11, XXXXXXX, KC_F1, KC_F2, KC_F3,
KC_PWR, KC_SLEP, KC_MPLY,         KC_MPRV,         KC_MNXT,         XXXXXXX,        KC_F12, KC_F4,   KC_F5, KC_F6, XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),

    [NUM] = LAYOUT(
         XXXXXXX, KC_MINS,         KC_LT,           KC_GT,       RALT(KC_5),        KC_COLN, KC_7,         KC_8,         KC_9,         XXXXXXX,
 LCTL_T(KC_PAST), LALT_T(KC_PPLS), LGUI_T(KC_SLSH), LSFT_T(KC_EQL), KC_UNDS,        KC_DOT,  LSFT_T(KC_0), LGUI_T(KC_1), LALT_T(KC_2), LCTL_T(KC_3),
XXXXXXX, KC_CIRC, KC_PERC,         KC_EXLM,         KC_QUES,         KC_DLR,        KC_COMM, KC_4,         KC_5,         KC_6,         XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),

    [NAV] = LAYOUT(
        XXXXXXX, KC_BSLS,         KC_LBRC,         KC_RBRC,         MAC_GRV,        KC_PGUP, LGUI(KC_LEFT), DEL_END,  LGUI(KC_RGHT), XXXXXXX,
LCTL_T(KC_PIPE), LALT_T(KC_AMPR), LGUI_T(KC_LPRN), RSFT_T(KC_RPRN), KC_HASH,        KC_PGDN, KC_LEFT,       KC_UP,    KC_RGHT,       XXXXXXX,
XXXXXXX, MAC_TILD, HOME,          KC_LCBR,         KC_RCBR,           KC_AT,        XXXXXXX, LALT(KC_LEFT), KC_DOWN,  LALT(KC_RGHT), XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,        _______, _______, _______
    ),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case HOME:
                tap_code16(MAC_TILD);
                tap_code(KC_SLSH);
                return false;
            case DEL_END:
                tap_code16(LSFT(LGUI(KC_RGHT)));
                tap_code(KC_DEL);
                return false;
            case COPY_ALL:
                tap_code16(LGUI(KC_A));
                tap_code16(LGUI(KC_C));
                return false;
            case CUT_ALL:
                tap_code16(LGUI(KC_A));
                tap_code16(LGUI(KC_X));
                return false;

            // Workaround for mod tap with non basic keycodes
            case LCTL_T(KC_PSCR):
                if (record->tap.count) {
                    // macOS has no print screen, snip a region to the clipboard instead
                    tap_code16(LCTL(LSFT(LGUI(KC_4))));
                    return false;
                }
                break;
            case RSFT_T(KC_RPRN):
                if (record->tap.count) {
                    tap_code16(KC_RPRN);
                    return false;
                }
                break;
            case LGUI_T(KC_LPRN):
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
            case LCTL_T(KC_PIPE):
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

bool is_keyboard_left_impl(void);

// Override master detection: Left half is always USB master, Right half is always slave.
bool is_keyboard_master_impl(void) {
    return is_keyboard_left_impl();
}
