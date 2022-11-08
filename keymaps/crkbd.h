#define LAYOUT_wrapper_split_3x6_3(...) LAYOUT_split_3x6_3(__VA_ARGS__)

#define BASE \
QK_GESC,   _________________QWERTY_L1_________________,              _________________QWERTY_R1_________________,    KC_MINS, \
KC_TAB,    _________________QWERTY_L2_________________,              _________________QWERTY_R2_________________, KC_QUOT, \
KC_LSFT,   _________________QWERTY_L3_________________,              _________________QWERTY_R3_________________,  KC_BSLS, \
                                __THUMBS_3L__, __THUMBS_3R__
#define RAISE \
KC_GRV,   _________________RAISE_L1__________________,              _________________RAISE_R1__________________,    KC_MINS, \
KC_TAB,    _________________RAISE_L2__________________,              _________________RAISE_R2__________________, KC_QUOT, \
KC_LSFT,   _________________RAISE_L3__________________,              _________________RAISE_R3__________________,  KC_BSLS, \
                                __THUMBS_3L_RAISE__, __THUMBS_3R_RAISE__
#define LOWER \
KC_TILD,   _________________LOWER_L1__________________,              _________________LOWER_R1__________________,    KC_MINS, \
KC_TAB,    _________________LOWER_L2__________________,              _________________LOWER_R2__________________, KC_QUOT, \
KC_LSFT,   _________________LOWER_L3__________________,              _________________LOWER_R3__________________,  KC_BSLS, \
                                __THUMBS_3L_LOWER__, __THUMBS_3R_LOWER__
