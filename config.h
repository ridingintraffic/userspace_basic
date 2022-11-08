#pragma once

// Common QMK variables
#define TAPPING_TERM 275
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT


#ifdef KEYBOARD_crkbd_rev1
    #include "keymaps/crkbd.h"
#endif // KEYBOARD_crkbd_rev1

#include "wrappers.h"
