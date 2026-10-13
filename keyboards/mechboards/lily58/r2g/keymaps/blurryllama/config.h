/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x61, 0xA3, 0x70, 0xEA, 0xD8, 0xF2, 0x6F, 0x5B}

#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

// blurryllama: state the halves share for the displays
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_STATE
#define SPLIT_WPM_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE

// blurryllama: Mechboards' SPLIT_ACTIVITY_ENABLE copies the USB half's keypress times to the other half,
// which can be slightly in the future there and briefly makes its display think it has timed out.
// blurryllama.c tells the other half about typing instead, timed with its own clock.
#undef SPLIT_ACTIVITY_ENABLE

// blurryllama: turn the displays and backlight off after 10 minutes without typing
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 600000

// blurryllama: Mechboards' display code loads two fonts, and the blurryllama displays load five more
#define QUANTUM_PAINTER_NUM_FONTS 8

// blurryllama: RGB effects the Halcyon Lily58 has. Mechboards' rgb_effects.h tries to enable most of
// these too, but under names QMK doesn't use (e.g. ENABLE_RGB_MATRIX_COLORBAND_SAT), so they stay off.
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_MULTISPLASH

// blurryllama: the neon logos are full-colour images. Mechboards' board config doesn't enable this
// (splitkb's Halcyon display module does), so without it the logos aren't drawn.
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
