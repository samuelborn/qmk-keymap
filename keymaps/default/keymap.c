#include QMK_KEYBOARD_H

enum layers {
    _L0,
    _L1,
    _L2,
    _L3,
    _L4,
};

enum custom_keycodes {
    UP_DIR = SAFE_RANGE,
    CURR_DIR,
    HOME_DIR,
    WRD_FWD,
    WRD_BCK,
    SEL_LINE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT(
                       KC_B, KC_L,         KC_D,         KC_C,         KC_V,        KC_J,    KC_F,         KC_O,         KC_U,            KC_DOT,
               LGUI_T(KC_N), LALT_T(KC_R), LCTL_T(KC_T), LSFT_T(KC_S), KC_G,        KC_Y,    RSFT_T(KC_H), LCTL_T(KC_A), LALT_T(KC_E),    LGUI_T(KC_I),
              KC_LGUI, KC_Q, KC_X,         KC_M,         RALT_T(KC_W), KC_Z,        KC_K,    RALT_T(KC_P), KC_QUOT,      KC_SCLN, KC_COMM, TG(_L4),
                          LT(_L1, KC_TAB), LT(_L2, KC_SPC), LT(_L3, KC_ESC),        LT(_L3, KC_ENT), LT(_L2, KC_BSPC), LT(_L1, KC_DEL)
    ),

    [_L1] = LAYOUT(
       KC_F10,         KC_F9,         KC_F8,         KC_F7,         XXXXXXX,        KC_PERC, KC_7,         KC_8,         KC_9,         KC_CIRC,
       LGUI_T(KC_F11), LALT_T(KC_F3), LCTL_T(KC_F2), LSFT_T(KC_F1), XXXXXXX,        KC_PLUS, LSFT_T(KC_1), LCTL_T(KC_2), LALT_T(KC_3), LGUI_T(KC_PAST),
      XXXXXXX, KC_F12, KC_F6,         KC_F5,         KC_F4,         XXXXXXX,        KC_MINS, KC_4,         KC_5,         KC_6,         KC_SLSH, XXXXXXX,
                                                  XXXXXXX, XXXXXXX, XXXXXXX,        KC_COMM, KC_0, KC_DOT    
    ),
    
    [_L2] = LAYOUT(
 KC_BSLS,         KC_LT,           KC_GT,           KC_MINS,        KC_UNDS,        KC_PIPE, KC_LBRC,         KC_RBRC,         KC_GRV,          KC_PERC,
 LGUI_T(KC_PAST), LALT_T(KC_PPLS), LCTL_T(KC_SLSH), LSFT_T(KC_EQL), KC_AMPR,        KC_HASH, RSFT_T(KC_LPRN), LCTL_T(KC_RPRN), LALT_T(KC_EXLM), LGUI_T(KC_QUES),
XXXXXXX, KC_CIRC, KC_TILD,         CURR_DIR,        UP_DIR,        HOME_DIR,        KC_AT,   KC_LCBR,         KC_RCBR,         KC_DLR,          RALT(KC_E), XXXXXXX,
                                                  XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_L3] = LAYOUT(
XXXXXXX,         XXXXXXX,         KC_BRID,         KC_BRIU,         XXXXXXX,        KC_PGUP, KC_HOME, SEL_LINE, KC_END,  XXXXXXX,
LGUI_T(KC_PSCR), LALT_T(KC_MUTE), LCTL_T(KC_VOLD), RSFT_T(KC_VOLU), XXXXXXX,        KC_PGDN, KC_LEFT, KC_UP,    KC_RGHT, XXXXXXX,
KC_PWR, KC_SLEP, KC_MPLY,         KC_MPRV,         KC_MNXT,         XXXXXXX,        XXXXXXX, WRD_BCK, KC_DOWN,  WRD_FWD, XXXXXXX, XXXXXXX,
                                                  XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    // Disable home row mods: useful for gaming
    [_L4] = LAYOUT(
                                               KC_B, KC_L, KC_D, KC_C, KC_V,        KC_J, KC_F, KC_O, KC_U, KC_DOT,
                                               KC_N, KC_R, KC_T, KC_S, KC_G,        KC_Y, KC_H, KC_A, KC_E, KC_I,
                                KC_LGUI, KC_Q, KC_X, KC_M, KC_W, KC_Z, KC_K,        KC_P, KC_QUOT, KC_SCLN, KC_COMM, TG(_L4),
                                                     KC_TAB, KC_SPC, KC_ESC,        KC_ENT, KC_BSPC, KC_DEL
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
            case WRD_FWD:
                tap_code16(LCTL(KC_RGHT));
                return false;
            case WRD_BCK:
                tap_code16(LCTL(KC_LEFT));
                return false;
            case SEL_LINE:
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
                return false;  

            // Workaround for mod tap with non basic keycodes
            case RSFT_T(KC_LPRN):
                if (record->tap.count && record->event.pressed) {
                    tap_code16(KC_LPRN);
                    return false;
                }
                break;
            case LCTL_T(KC_RPRN):
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
