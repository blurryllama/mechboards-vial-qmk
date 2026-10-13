# blurryllama: Mechboards Lily58 Pro R2G with two TFT displays

A Vial keymap for the [Mechboards Lily58 Pro R2G](https://mechboards.co.uk) (RP2040, a colour TFT screen on each half), in a synthwave/cyberpunk style. It's a port of the [blurryllama keymap for the splitkb Halcyon Lily58](https://github.com/blurryllama/qmk_userspace/tree/halcyon/keyboards/splitkb/halcyon/lily58/keymaps/blurryllama), with the same layout, shortcut keys and displays.

## What it does

**Mac/PC/Linux detection.** The keyboard detects the computer's OS when it's plugged in and sets itself up to match. Mac mode swaps Ctrl and Cmd. Anything that isn't Windows, macOS or iOS is reported as Linux, including Android, SteamOS, Raspberry Pi and consoles, and uses PC mode.

**OS-aware shortcut keys.** These are Vial custom keys, found in Vial's **User** tab, that send the right shortcut for the detected OS:

| Key | PC | Mac | Linux |
|---|---|---|---|
| Insp | Ctrl+Shift+I | Cmd+Opt+I | Ctrl+Shift+I |
| Shot | Print Screen | Cmd+Shift+5 | Print Screen |
| Lock | Win+L | Ctrl+Cmd+Q | Lock-screen media key |
| Kill | Alt+F4 | Cmd+Opt+Esc | Alt+F4 |
| Calc | Calculator key | Opens Calculator via Spotlight | Calculator key |
| VolMx | Ctrl+Alt+V | Opt+Volume Up (Sound settings) | nothing |
| WinX | Win+X | nothing | nothing |

**Status display** (the half plugged into USB):
- The layer name on a neon bar ("Fun", "RGB"), or "CAPS" on the base layer while caps lock is on.
- A neon Apple, Windows or Tux logo.
- Which modifiers are held (SHF, CTL, ALT/OPT, WIN/CMD/SUP).

**Second display** (the other half):
- Typing speed and a graph of the last minute. On the RGB layer it switches to the lighting effect, colour, brightness, speed and on/off state.
- Luna the keyboard pet, redrawn in neon, at the bottom of both screens. She sits, walks or runs with your typing speed, barks on Shift or caps lock, sneaks on Ctrl or Cmd, and jumps on Space.

Either half can be plugged into the computer; the screens swap to match.

**Screen timeout.** The screens and their backlight turn off after 10 minutes without typing on either half.

**Lighting effects.** All 50 effects from the R2G and the Halcyon Lily58 are included.

## Building

This builds from Mechboards' fork of [vial-qmk](https://github.com/MechboardsLTD/vial-qmk), on its `r2g` branch, which is where the Lily58 Pro R2G is defined. Set up QMK with this repository as its home, then:

```bash
qmk compile -kb mechboards/lily58/r2g -km blurryllama
```

**Flashing.** Flash the same `.uf2` to both halves. For each half, plug it in on its own while holding its outer top corner key: **Esc** on the left half, the **top-right** key on the right. It appears as an `RPI-RP2` drive; copy the `.uf2` onto it. Holding the BOOT button on the underside while plugging in works too. The halves send each other extra data, so they must run the same build. If anything goes wrong, Mechboards' official firmware from their guides site gets the board working again.

**Vial layout.** Every new build resets your Vial layout to the default in `keymap.json`, because Vial gives each build a random ID. Save your layout in Vial first (File → Save current layout) and load it again after flashing.

## Customising

| To change | Where |
|---|---|
| Layout and default keys | `keymap.json`, or in Vial. The two encoder-press positions at the end of each layer are unused, as no encoders are fitted. |
| Shortcut keys and what each OS sends | `os_shortcuts` table in `blurryllama.c`; the key names Vial shows are in `vial.json` under `customKeycodes` |
| Colours | The colour list at the top of `display.c`, with the hex value next to each |
| Layer names | `layer_names` in `display.c`. `RGB_LAYER` sets which layer shows the lighting info. |
| Shortened lighting effect names | `effect_short_names` in `display.c` |
| Screen timeout | `QUANTUM_PAINTER_DISPLAY_TIMEOUT` in `config.h`, in milliseconds |
| Luna's animation speed | `LUNA_FRAME_MS` in `display.c` |
| Second display performance | `SECOND_JOB_GAP_MS` in `display.c`: the gap between drawing jobs, which leaves time to scan keys on that half. Raise it if keys get dropped. |

**Images and fonts** are stored as C files in `graphics/`, made with QMK's painter tools in QMK MSYS. Run these from the `graphics/` folder:

- **Logos:** `python3 prepare_logos.py <apple image> <windows image> <tux image>`, then convert the PNGs as described at the top of `prepare_logos.py`.
- **Luna:** `python3 prepare_luna.py`, then convert the PNGs as described at the top of the script. Her original sprites are in `luna_sprites.h`.
- **Fonts:** see the comment above the font definitions in `display.c`.

## How it fits Mechboards' code, and things to know

- **Mechboards' screen setup is reused.** `keyboards/mechboards/common/display_lcd.c` still sets up the screens. This keymap's `display_init_user()` returns `false`, which turns off Mechboards' own screen UI and its refresh timer, and `display.c` draws everything from `housekeeping_task_user()` instead. It also takes over the backlight timeout that Mechboards' timer handled.
- **Link-time optimisation is off** (`LTO_ENABLE = no` in `rules.mk`). The board's `keyboard.json` turns it on, and with the older compiler in QMK MSYS that produces firmware that doesn't start: dead keys and static on the screens. This happens even with Mechboards' own Vial keymap. Builds with QMK's current toolchain may be fine either way.
- **`SPLIT_ACTIVITY_ENABLE` is turned off** (`config.h`). It copies keypress times from the USB half, and they can be slightly in the future on the other half, which briefly made its screen think it had timed out. `blurryllama.c` tells the other half about typing instead, timed with its own clock.
- **Full-colour images need `QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS`**, set in `config.h`; without it the neon logos aren't drawn.
- **256-colour images:** Luna uses a 256-colour palette, which needs `QUANTUM_PAINTER_SUPPORTS_256_PALETTE`. Mechboards' board config already sets it.
- **Lighting effects:** Mechboards' `rgb_effects.h` tries to enable several effects under names QMK doesn't use (for example `ENABLE_RGB_MATRIX_COLORBAND_SAT`), so they stay off. `config.h` enables them under their real names.
- **Safe mode:** building with `-e BLURRYLLAMA_NO_DISPLAY=1` gives the same keymap with the screens left blank, which is useful for telling display problems apart from others.
- **Second display drawing** blocks key scanning on that half, which is why it does one small job per pass. Keep new drawing small, or split it into steps.

## Credits

- Luna the keyboard pet is by HellSingCoder.
- Russo One by Jovanny Lemonad, under the SIL Open Font License (`graphics/fonts/OFL.txt`).
- Apple, Windows and the Tux mascot are trademarks or logos of their owners, and are used here only to show which OS is connected.
- Based on Mechboards' Lily58 Pro R2G firmware by dasky.
