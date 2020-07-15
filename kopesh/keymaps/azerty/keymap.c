#include "kopesh.h"
#include "keymap_french.h"
#include <string.h>
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE,
  LOWER,
  ADJUST,
  BACKLIT
};
// FR_OVRR, FR_PLUS,
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
	KC_ESC,         KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO,                      KC_BSPACE,      KC_Y, KC_U, KC_I,    KC_O,   KC_P,      KC_BSPACE, FR_OVRR, FR_PLUS, \
	LSFT_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_LGUI,                    KC_APP,     KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,   KC_DELETE, KC_UP, FR_PIPE, \
	KC_LCTRL, 		KC_Z, KC_X, KC_C, KC_V, LT(_LOWER, KC_B), LALT_T(KC_SPC),   RSFT_T(KC_ENT), LT(_RAISE,KC_N), LT(_ADJUST,KC_M), KC_COMM, KC_DOT, KC_SLSH,   KC_LEFT, KC_DOWN, KC_RIGHT  \
),
	KEYMAP(
	FR_AMP,         KC_2, KC_3, KC_4, FR_LPRN, FR_MINS, KC_NO,             KC_BSPACE,     FR_EGRV, FR_UNDS, FR_CCED, FR_AGRV, FR_RPRN, FR_EQL,  KC_NO, KC_NO, \
	LSFT_T(KC_TAB), KC_NO,   KC_NO,   KC_BSLS, KC_TILD, KC_NUHS, KC_LGUI,       KC_APP,     KC_LCBR, KC_QUOT, KC_BSLS, KC_LBRC, KC_RBRC, KC_DEL,  KC_UP, KC_NO, \
	KC_LCTRL,       KC_NUBS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   LALT_T(KC_SPC),   RSFT_T(KC_ENT), KC_NO,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LEFT, KC_DOWN, KC_RIGHT  \
),

	KEYMAP(
	FR_1,           FR_2,    FR_3,    FR_4,    FR_5,    FR_6,  KC_NO,              KC_BSPACE,     FR_7,    FR_8,    FR_9,    FR_0, FR_OVRR, FR_PLUS,  RGB_HUI, RGB_MODE_FORWARD, \
	LSFT_T(KC_TAB),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_LGUI,       KC_APP,     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_DEL,  KC_PGUP, KC_NO, \
	KC_LCTRL,       KC_F11,  KC_F12, KC_COPY, KC_PSTE,   KC_NO,   LALT_T(KC_SPC),   RSFT_T(KC_ENT), KC_NO,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_HOME, KC_PGDN, KC_END  \
),

	KEYMAP(
	KC_ESC,        FR_TILD, FR_HASH, ALGR(KC_E), FR_LCBR, FR_LBRC,  KC_NO,              KC_BSPACE,     FR_GRV, FR_BSLS, FR_CCIRC,   FR_AT, FR_RBRC, FR_RCBR,  BL_TOGG, RGB_TOG, \
	LSFT_T(KC_TAB), RGB_VAI, RGB_HUI,    RGB_SAI, RGB_MOD, FR_LCBR, KC_LGUI,                   KC_APP,     FR_PIPE, FR_PERC,  KC_NO, KC_NO, KC_NO, FR_RCBR,  KC_PGUP, RESET, \
	KC_LCTRL,       RGB_VAD, RGB_HUD,    RGB_SAD, RGB_RMOD, KC_NO,   LALT_T(KC_SPC),   RSFT_T(KC_ENT),  KC_NO, FR_QUES,   FR_DOT, FR_SLSH, FR_SECT, KC_HOME, KC_PGDN, KC_END  \
)

};

//const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
//	keyevent_t event = record->event;

//	switch (id) {

//	}
//	return MACRO_NONE;
//}

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
	#ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(false);   // turns on the display
    #endif
}


// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void matrix_scan_user(void) {
	  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (true) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
  }
  return true;
}


void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}