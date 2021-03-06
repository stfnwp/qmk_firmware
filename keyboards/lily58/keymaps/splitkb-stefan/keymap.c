#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _FOO 4
#define _BAR 5
#define _NUM 6

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  FOO,
  BAR,
  NUM,
  DE_OE,
  DE_UE,
  DE_AE,
  DE_SS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LOWER |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  =   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Del   | /Space  /       \Enter \  |BackSP|RAISE | RAlt |
 *                   |      |      |      |/ LShift/         \RShift\ |      |Ins   | `    |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,            KC_1,   KC_2,    KC_3,         KC_4,         KC_5,                                      KC_6,     KC_7,         KC_8,         KC_9,         KC_0,    KC_MINS, \
  LT(_BAR, KC_TAB),  KC_Q,   KC_W,    KC_E,         KC_R,         KC_T,                                      KC_Y,     KC_U,         KC_I,         KC_O,         KC_P,    KC_BSLS, \
  LOWER,             KC_A,   KC_S,    LALT_T(KC_D), LCTL_T(KC_F), KC_G,                                      KC_H,     LCTL_T(KC_J), LALT_T(KC_K), KC_L,         KC_SCLN, KC_QUOT, \
  KC_LSHIFT,         KC_Z,   KC_X,    KC_C,         KC_V,         KC_B,    KC_LBRC,               KC_RBRC,   KC_N,     KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,  KC_EQL, \
                             KC_LGUI, KC_INS,       LT(_NUM, KC_GRV), KC_SPC,  KC_SFTENT,                               KC_BSPC,  FOO,  KC_RALT \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  _______, _______, _______, _______, _______, _______,                   _______, DE_UE,  _______,DE_OE, KC_INSERT, KC_F12, \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_RPRN, KC_TILD, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
                             _______, _______, _______, _______, _______,  KC_DEL, _______, _______\
),
  [_FOO] = LAYOUT( \
  XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW, RGB_M_SN,                  RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, DE_AE,   DE_SS,   XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, RGB_TOG, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, \
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),
  [_BAR] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC__MUTE, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, KC__VOLUP, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC__VOLDOWN, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
  ),
  [_NUM] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8, KC_9, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5, KC_6, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2, KC_3, \
                             _______, _______, _______,  _______, _______,  _______, _______, KC_0 \
  ),
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
// const char *read_logo(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    // oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    // set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case FOO:
        if (record->event.pressed) {
          layer_on(_FOO);
        } else {
          layer_off(_FOO);
        }
        return false;
        break;
    case BAR:
        if (record->event.pressed) {
          layer_on(_BAR);
        } else {
          layer_off(_BAR);
        }
        return false;
        break;
    case NUM:
        if (record->event.pressed) {
          layer_on(_NUM);
        } else {
          layer_off(_NUM);
        }
        return false;
        break;
    case DE_OE:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_O);
      } else {
        unregister_code(KC_O);
        unregister_code(KC_RALT);
      }
      break;
    case DE_UE:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_U);
      } else {
        unregister_code(KC_U);
        unregister_code(KC_RALT);
      }
      break;
    case DE_AE:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_A);
      } else {
        unregister_code(KC_A);
        unregister_code(KC_RALT);
      }
      break;
    case DE_SS:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_S);
      } else {
        unregister_code(KC_S);
        unregister_code(KC_RALT);
      }
      break;
  }
  return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _QWERTY:
                // Move whole words. Hold shift to select while moving.
                if (clockwise) {
                    tap_code16(C(KC_RGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            default:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(C(KC_Z));
                } else {
                    tap_code16(C(KC_Y));
                }
                break;
        }
    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case _QWERTY:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            default:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        rgblight_sethsv(HSV_PURPLE);
        break;
    case _BAR:
        rgblight_sethsv(HSV_YELLOW);
        break;
    case _NUM:
        rgblight_sethsv(HSV_MAGENTA);
        break;
    case _FOO:
        rgblight_sethsv(HSV_SPRINGGREEN);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv(HSV_CYAN);
        break;
    }
  return state;
}

