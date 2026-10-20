#include QMK_KEYBOARD_H

/* ── Bootloader Combos ────────────────────────────────────────────── */
/*
 * Left:  MO(1) + Tab + Alt + Ctrl
 * Right: MO(2) + Esc + Win + Enter
 */

const uint16_t PROGMEM combo_boot_left[]  = {MO(1), KC_TAB, KC_LALT, KC_LCTL, COMBO_END};
const uint16_t PROGMEM combo_boot_right[] = {MO(2), KC_ESC, KC_RGUI, KC_ENT,  COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_boot_left,  QK_BOOT),
    COMBO(combo_boot_right, QK_BOOT),
};

/* ── Custom Keycodes ──────────────────────────────────────────────── */
/*
 * Escaped quotes: US-Intl treats ' and " as dead keys.
 * These send the key followed by Space to output the literal character.
 */

enum custom_keycodes {
    CK_QUOT = SAFE_RANGE,
    CK_DQUO,
};

/* ── Key Processing ───────────────────────────────────────────────── */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case CK_QUOT:
            tap_code(KC_QUOT);
            tap_code(KC_SPC);
            return false;
        case CK_DQUO:
            tap_code16(S(KC_QUOT));
            tap_code(KC_SPC);
            return false;
    }
    return true;
}

/* ── RGB Per-Layer Colors ─────────────────────────────────────────── */

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
    rgb_matrix_sethsv_noeeprom(0, 255, 255);  // Red for base layer
    rgb_matrix_set_speed_noeeprom(160);        // Faster breathing
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1:
            rgb_matrix_sethsv_noeeprom(170, 255, 255);  // Blue
            rgb_matrix_set_speed_noeeprom(200);          // Faster
            break;
        case 2:
            rgb_matrix_sethsv_noeeprom(85, 255, 255);   // Green
            rgb_matrix_set_speed_noeeprom(200);          // Faster
            break;
        default:
            rgb_matrix_sethsv_noeeprom(0, 255, 255);    // Red
            rgb_matrix_set_speed_noeeprom(80);           // Slower
            break;
    }
    return state;
}

/* ── Keymap Layers ────────────────────────────────────────────────── */
/*
 * Requires US International keyboard layout on the OS.
 * Nordic chars use AltGr (Right Alt) combos.
 * Dead keys (´ ¨ ` ^ ~) are handled by the OS layout.
 * Literal ' and " on Layer 1 are escaped with Space.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0: Base QWERTY
     * ┌─────┬───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬─────┐
     * │ Tab │ Q │ W │ E │ R │ T │ ( │   │ ) │ Y │ U │ I │ O │ P │ Esc │
     * ├─────┼───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┼─────┤
     * │ Alt │ A │ S │ D │ F │ G │ , │   │ . │ H │ J │ K │ L │ Å │ Win │
     * ├─────┼───┼───┼───┼───┼───┼───┘   └───┼───┼───┼───┼───┼───┼─────┤
     * │ Ctrl│ Z │ X │ C │ V │ B │           │ N │ M │ Ç │ Æ │ Ø │Enter│
     * └─────┴───┴───┴───┴─┬─┴─┬─┴─┬───┐ ┌───┬─┴─┬─┴─┬─┴───┴───┴─────┘
     *                      │Sft│L1 │Spc│ │Bsp│L2 │Del│
     *                      └───┴───┴───┘ └───┴───┴───┘
     */
    [0] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, S(KC_9),       S(KC_0), KC_Y, KC_U, KC_I,         KC_O,       KC_P,       KC_ESC,
        KC_LALT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_COMM,       KC_DOT,  KC_H, KC_J, KC_K,         KC_L,       RALT(KC_W), KC_RGUI,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                          KC_N, KC_M, RALT(KC_COMM),RALT(KC_Z), RALT(KC_L), KC_ENT,
                              KC_LSFT, MO(1), KC_SPC,       KC_BSPC, MO(2), KC_DEL
    ),

    /* Layer 1: Numbers / Symbols
     * ┌─────┬───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬─────┐
     * │ Tab │ 1 │ 2 │ 3 │ 4 │ 5 │ [ │   │ ] │ 6 │ 7 │ 8 │ 9 │ 0 │ Esc │
     * ├─────┼───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┼─────┤
     * │ Alt │ ! │ @ │ # │ $ │ % │ - │   │ + │ | │ & │ * │ ' │ " │ Win │
     * ├─────┼───┼───┼───┼───┼───┼───┘   └───┼───┼───┼───┼───┼───┼─────┤
     * │ Ctrl│ ? │ : │ ; │ € │ _ │           │ = │ < │ > │ / │ \ │Enter│
     * └─────┴───┴───┴───┴─┬─┴─┬─┴─┬───┐ ┌───┬─┴─┬─┴─┬─┴───┴───┴─────┘
     *                      │Sft│L1 │Spc│ │Bsp│L2 │Del│
     *                      └───┴───┴───┘ └───┴───┴───┘
     */
    [1] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,  KC_1,      KC_2,      KC_3,    KC_4,       KC_5,      KC_LBRC,       KC_RBRC,    KC_6,       KC_7,      KC_8,      KC_9,    KC_0,    KC_ESC,
        KC_LALT, S(KC_1),   S(KC_2),   S(KC_3), S(KC_4),    S(KC_5),   KC_MINS,       S(KC_EQL),  S(KC_BSLS), S(KC_7),   S(KC_8),   CK_QUOT, CK_DQUO,KC_RGUI,
        KC_LCTL, S(KC_SLSH),S(KC_SCLN),KC_SCLN, RALT(KC_5), S(KC_MINS),                           KC_EQL,     S(KC_COMM),S(KC_DOT), KC_SLSH, KC_BSLS, KC_ENT,
                                        KC_LSFT, MO(1), KC_SPC,       KC_BSPC, MO(2), KC_DEL
    ),

    /* Layer 2: Function / Navigation / Dead Keys
     * ┌─────┬────┬────┬────┬─────┬────┬───┐   ┌───┬────┬────┬────┬────┬────┬─────┐
     * │ Tab │ F1 │ F2 │ F3 │ F4  │ F5 │ { │   │ } │ F6 │ F7 │ F8 │ F9 │F10 │ Esc │
     * ├─────┼────┼────┼────┼─────┼────┼───┤   ├───┼────┼────┼────┼────┼────┼─────┤
     * │ Alt │Caps│ ←  │ ↑  │  →  │ ~  │   │   │   │ ^  │Home│PgUp│End │F11 │ Win │
     * ├─────┼────┼────┼────┼─────┼────┼───┘   └───┼────┼────┼────┼────┼────┼─────┤
     * │ Ctrl│Brk │PScr│ ↓  │  ¨  │    │           │ `  │ ´  │PgDn│Ins │F12 │Enter│
     * └─────┴────┴────┴────┴──┬──┴─┬──┴─┬───┐ ┌───┬──┴─┬──┴─┬──┴────┴────┴─────┘
     *                         │Sft │ L1 │Spc│ │Bsp│ L2 │Del │
     *                         └────┴────┴───┘ └───┴────┴────┘
     */
    [2] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,      S(KC_LBRC),    S(KC_RBRC), KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_ESC,
        KC_LALT, KC_CAPS, KC_LEFT, KC_UP,   KC_RGHT,    S(KC_GRV),  XXXXXXX,       XXXXXXX,    S(KC_6), KC_HOME, KC_PGUP, KC_END,  KC_F11,  KC_RGUI,
        KC_LCTL, KC_PAUS, KC_PSCR, KC_DOWN, S(KC_QUOT), XXXXXXX,                                KC_GRV,  KC_QUOT, KC_PGDN, KC_INS,  KC_F12,  KC_ENT,
                                    KC_LSFT, MO(1), KC_SPC,       KC_BSPC, MO(2), KC_DEL
    ),
};
