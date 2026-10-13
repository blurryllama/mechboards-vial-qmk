ENCODER_MAP_ENABLE = yes

# The R2G's keyboard.json turns on link-time optimisation. With the GCC 10 toolchain in QMK MSYS
# that produces firmware that doesn't start (even Mechboards' own Vial keymap), so leave it off.
LTO_ENABLE = no
VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes

# blurryllama: Mac/PC/Linux detection, shortcut keys and the two displays
SRC += blurryllama.c \
       display.c \
       graphics/logo_apple.qgf.c \
       graphics/logo_windows.qgf.c \
       graphics/logo_tux.qgf.c \
       graphics/russo_one_35.qff.c \
       graphics/russo_one_23.qff.c \
       graphics/russo_one_20.qff.c \
       graphics/russo_one_14.qff.c \
       graphics/russo_one_52_digits.qff.c \
       graphics/luna_sit_0.qgf.c \
       graphics/luna_sit_1.qgf.c \
       graphics/luna_walk_0.qgf.c \
       graphics/luna_walk_1.qgf.c \
       graphics/luna_run_0.qgf.c \
       graphics/luna_run_1.qgf.c \
       graphics/luna_bark_0.qgf.c \
       graphics/luna_bark_1.qgf.c \
       graphics/luna_sneak_0.qgf.c \
       graphics/luna_sneak_1.qgf.c

# Safe mode for testing: build with -e BLURRYLLAMA_NO_DISPLAY=1 to leave the screens blank
ifeq ($(strip $(BLURRYLLAMA_NO_DISPLAY)), 1)
    OPT_DEFS += -DBLURRYLLAMA_NO_DISPLAY
endif
