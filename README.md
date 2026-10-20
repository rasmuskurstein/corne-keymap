# Corne (crkbd rev4.1) keymap

Personal QMK keymap for a Corne split keyboard. Three layers (base QWERTY, numbers/symbols, function/nav), bootloader combos on both halves, breathing RGB per layer, and Nordic characters via US-International.

## Files

- `keymap.c` — layers, custom keycodes (escaped `'` / `"`), bootloader combos, RGB per-layer behaviour.
- `config.h` — enables `RGB_MATRIX_BREATHING`.
- `rules.mk` — enables `COMBO_ENABLE`.
- `keymap_visual.html` — reference diagram of the three layers.

## Tools

- **QMK MSYS** (Windows): bundled MSYS2 toolchain, `qmk` CLI, and board drivers. Installed to `../QMK_MSYS/` in the sibling folder.
- **QMK firmware tree**: upstream `qmk/qmk_firmware` cloned to `../qmk_firmware/`. The build happens here, not in this folder.
- A Corne rev4.1 (standard, not LP) with the stock bootloader.

## Target location in the QMK tree

These files are a working copy. The build reads from:

```
qmk_firmware/keyboards/crkbd/rev4_1/standard/keymaps/custom/
```

Copy `keymap.c`, `config.h`, and `rules.mk` into that folder before building.

## Update workflow

From a **QMK MSYS** shell on Windows:

1. **Sync the source** into the QMK tree:

   ```sh
   cp /c/Users/rkurs/dev/misc/personal/input-device-firmware/keyboard/{keymap.c,config.h,rules.mk} \
      /c/Users/rkurs/dev/misc/personal/input-device-firmware/qmk_firmware/keyboards/crkbd/rev4_1/standard/keymaps/custom/
   ```

2. **Compile**:

   ```sh
   cd /c/Users/rkurs/dev/misc/personal/input-device-firmware/qmk_firmware
   qmk compile -kb crkbd/rev4_1/standard -km custom
   ```

3. **Enter bootloader** on the half you want to flash, using one of the combos defined in `keymap.c`:
   - Left half: `MO(1) + Tab + Alt + Ctrl`
   - Right half: `MO(2) + Esc + Win + Enter`

4. **Flash** the connected half:

   ```sh
   qmk flash -kb crkbd/rev4_1/standard -km custom
   ```

   Repeat steps 3–4 for the other half (unplug the first, plug in the second, enter its bootloader combo, flash again).

## OS layout

The host OS must be set to **US-International**. Nordic chars (`Å Æ Ø Ç`) and symbols are sent via `AltGr` combos; dead keys (`´ ¨ \` ^ ~`) are produced by the OS layout.
