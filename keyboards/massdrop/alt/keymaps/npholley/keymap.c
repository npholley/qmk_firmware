#include QMK_KEYBOARD_H

uint8_t rgb_matrix_effects[] = {
    RGB_MATRIX_GRADIENT_UP_DOWN,
    RGB_MATRIX_SOLID_COLOR,
    RGB_MATRIX_BAND_SPIRAL_SAT,
    RGB_MATRIX_NONE,
    RGB_MATRIX_JELLYBEAN_RAINDROPS
};

uint8_t current_rgb_matrix_effect_index = 0;

char *alt_codes[][2] = {
    {
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_9)), // Alt+0229 → å
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_9)SS_TAP(X_KP_7)), // Alt+0197 → Å
    },
    {
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_5)), // Alt+145 → æ
        SS_LALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_6)), // Alt+146 → Æ
    },
    {
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_4)SS_TAP(X_KP_8)), // Alt+0248 → ø
        SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_2)SS_TAP(X_KP_1)SS_TAP(X_KP_6)), // Alt+0216 → Ø
    },
};

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    RGB_NXT,               //Custom index for RGB mode
    KX_AO,                 //Numpad ALTGR
    KX_AE,                 //Numpad ALTGR
    KX_OI,                 //Numpad ALTGR
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker( // MAC base
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                        LT(1, KC_SPC),                          KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker( // MAC FN
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
    _______,LALT(KC_QUOT),RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI,U_T_AUTO,U_T_AGCR,LALT(KC_O),KC_PSCR,KC_SLCK, KC_PAUS, _______, KC_END, \
       _______,LALT(KC_A),RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, RGB_NXT, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______,   DF(2), KC_HOME, KC_PGDN, KC_END  \
    ),
    [2] = LAYOUT_65_ansi_blocker( // Windows base
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                        LT(3, KC_SPC),                          KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [3] = LAYOUT_65_ansi_blocker( // Windows FN
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
   _______,RALT(KC_QUOT), RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, U_T_AUTO,U_T_AGCR,RALT(KC_O),KC_PSCR,KC_SLCK,KC_PAUS, _______, KC_END, \
   _______,RALT(KC_A), RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, RGB_NXT, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______,   DF(0), KC_HOME, KC_PGDN, KC_END  \
    ),
};

// Apply current matrix settings
void set_matrix_mode(void) {
    rgb_matrix_mode(rgb_matrix_effects[current_rgb_matrix_effect_index]);
};

// Bump and change RGB mode in a limited subset
void increment_current_rgb_matrix_effect(void) {
    current_rgb_matrix_effect_index++;
    uint8_t effect_count = sizeof(rgb_matrix_effects) / sizeof(uint8_t);
    if (current_rgb_matrix_effect_index >= effect_count) {
        current_rgb_matrix_effect_index = 0;
    }
    set_matrix_mode();
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    set_matrix_mode();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case KX_AO: case KX_AE: case KX_OI: {
            uint16_t index = keycode - KX_AO;
            uint8_t shift = get_mods()&MODS_SHIFT_MASK;

            unregister_code(KC_LSFT); // Must temporarily disable both shift keys, else this whole thing may behave oddly
            unregister_code(KC_RSFT);

            // Choose Alt code based on which key was pressed and whether Shift was held.
            send_string(alt_codes[index][ (bool)shift]);

            if (shift &MOD_BIT(KC_LSFT)) register_code(KC_LSFT); // Restore shift keys to previous state
            if (shift &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);

            return false;
        }
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_NXT:
            if (record->event.pressed) {
                increment_current_rgb_matrix_effect();
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}