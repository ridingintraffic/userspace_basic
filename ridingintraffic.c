#include "ridingintraffic.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "action.h"
#include "process_keycode/process_tap_dance.h"

#define KC_ZOOMMUTE LGUI(LSFT(KC_A))  // zoom mute / unmute
#define KC_ZOOMSCREENSHARE LGUI(LSFT(KC_S))  // zoom screenshare start stop
#define KC_ZOOMSCREENSHAREPAUSE LGUI(LSFT(KC_T))  // zoom screenshare pause resume
#define KC_ZOOMVIDEO LGUI(LSFT(KC_V))  // zoom start stop video

void register_ctrl_shift (void) {
  register_code (KC_LSFT);
  register_code (KC_LCTL);
}

void unregister_ctrl_shift (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_LCTL);
}

void register_alt_shift (void) {
  register_code (KC_LSFT);
  register_code (KC_LALT);
}

void unregister_alt_shift (void) {
  unregister_code (KC_LSFT);
  unregister_code (KC_LALT);
}

// beginTapDance
//
// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      //     if (!state->pressed) return SINGLE_TAP;
      //need "permissive hold" here.
      //     else return SINsGLE_HOLD;
      //If the interrupting key is released before the tap-dance key, then it is a single HOLD
      //However, if the tap-dance key is released first, then it is a single TAP
      //But how to get access to the state of the interrupting key????
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8; //magic number. At some point this method will expand to work for more presses
}

static xtap htap_state = {
  .is_press_action = true,
  .state = 0
};

void h_finished (qk_tap_dance_state_t *state, void *user_data) {
  htap_state.state = cur_dance(state);
  switch (htap_state.state) {
    case SINGLE_TAP: register_code(KC_H); break;
    case SINGLE_HOLD: layer_on(8); register_code(KC_LALT); break;
    case DOUBLE_TAP: layer_invert(8); register_code(KC_LALT); break;
    // case DOUBLE_HOLD: register_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: register_code(KC_H);unregister_code(KC_H);register_code(KC_H);
  }
}

void h_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (htap_state.state) {
    case SINGLE_TAP: unregister_code(KC_H); break;
    case SINGLE_HOLD: layer_off(8); unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_LALT);break;
    // case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_H);
  }
  htap_state.state = 0;
}
/**************** QUAD FUNCTION FOR TAB ****************/
// TAB, ALT + SHIFT, TAB TAB, CTRL + SHIFT
static xtap tab_state = {
  .is_press_action = true,
  .state = 0
};
void esc_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_Q); break;  //send tab on single press
    case DOUBLE_TAP: register_code(KC_ESC); unregister_code(KC_TAB); register_code(KC_TAB); break; //tab tab
  }
}

void esc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_Q); break; //unregister tab
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
  }
  tab_state.state = 0;
}
void tab_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_TAB); break;  //send tab on single press
    case SINGLE_HOLD: register_ctrl_shift(); break;
    case DOUBLE_HOLD: register_alt_shift(); break; //alt shift on single hold
    case DOUBLE_TAP: register_code(KC_TAB); unregister_code(KC_TAB); register_code(KC_TAB); break; //tab tab
    case TRIPLE_TAP: register_code(KC_LSFT) ;register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LGUI); break;
  }
}

void tab_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_TAB); break; //unregister tab
    case DOUBLE_HOLD: unregister_alt_shift(); break; //let go of alt shift
    case DOUBLE_TAP: unregister_code(KC_TAB); break;
    case SINGLE_HOLD: unregister_ctrl_shift(); break;
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LGUI); break;
  }
  tab_state.state = 0;
}

void enter_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_TAB); break;  //send tab on single press
    case SINGLE_HOLD: register_ctrl_shift(); break;
    case DOUBLE_HOLD: register_alt_shift(); break; //alt shift on single hold
    case DOUBLE_TAP: register_code(KC_TAB); unregister_code(KC_TAB); register_code(KC_TAB); break; //tab tab
    case TRIPLE_TAP: register_code(KC_LSFT) ;register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LGUI); break;
  }
}

void enter_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_TAB); break; //unregister tab
    case DOUBLE_HOLD: unregister_alt_shift(); break; //let go of alt shift
    case DOUBLE_TAP: unregister_code(KC_TAB); break;
    case SINGLE_HOLD: unregister_ctrl_shift(); break;
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LGUI); break;
  }
  tab_state.state = 0;
}

void l1_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: layer_on(1); break;  //send tab on single press
    case SINGLE_HOLD: register_ctrl_shift(); break;
    case DOUBLE_HOLD: register_alt_shift(); break; //alt shift on single hold
    case DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
    case TRIPLE_TAP: register_code(KC_LSFT) ;register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LGUI); break;
  }
}

void l1_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: layer_off(1); break; //unregister tab
    case DOUBLE_HOLD: unregister_alt_shift(); break; //let go of alt shift
    case DOUBLE_TAP: break;
    case SINGLE_HOLD: unregister_ctrl_shift(); break;
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LGUI); break;
  }
  tab_state.state = 0;
}

void l2_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_TAB); break;  //send tab on single press
    case SINGLE_HOLD: register_ctrl_shift(); break;
    case DOUBLE_HOLD: register_alt_shift(); break; //alt shift on single hold
    case DOUBLE_TAP: set_oneshot_layer(2, ONESHOT_START); set_oneshot_layer(2, ONESHOT_PRESSED); break;
    case TRIPLE_TAP: register_code(KC_LSFT) ;register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LGUI); break;
  }
}

void l2_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_TAB); break; //unregister tab
    case DOUBLE_HOLD: unregister_alt_shift(); break; //let go of alt shift
    case DOUBLE_TAP: break;
    case SINGLE_HOLD: unregister_ctrl_shift(); break;
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LGUI); break;
  }
  tab_state.state = 0;
}
/**************** QUAD FUNCTION FOR TAB ****************/
void f_shift_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_F); break;  //send tab on single press
    case SINGLE_HOLD: register_code(KC_LSFT); break;
  }
}

void f_shift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_F); break; //unregister tab
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
  }
  tab_state.state = 0;
}
void j_shift_finished (qk_tap_dance_state_t *state, void *user_data) {
  tab_state.state = cur_dance(state);
  switch (tab_state.state) {
    case SINGLE_TAP: register_code(KC_J); break;  //send tab on single press
    case SINGLE_HOLD: register_code(KC_LSFT); break;
  }
}

void j_shift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tab_state.state) {
    case SINGLE_TAP: unregister_code(KC_J); break; //unregister tab
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
  }
  tab_state.state = 0;
}
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // simple tap dance
  [TABCOMBO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished, tab_reset),
  [Q_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished, esc_reset),
  [F_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_shift_finished, f_shift_reset),
  [J_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, j_shift_finished, j_shift_reset),

};

// endTapDance
//

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
  debug_matrix=false;
  //debug_keyboard=true;
  //debug_mouse=true;
}

void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};


#ifdef ENCODER_ENABLE
_Bool encoder_update_user(uint8_t index, bool clockwise) {
    // default behavior if undefined
    if (index == 0) {
        // Conditional to reverse the direction of encoder number 1
        // The reason I have this is that for some of my boards, it supports two different types of encoders, and they may differ in direction
        #ifdef ENCODERS_A_REVERSE
        if (!clockwise) {
        #else
        if (clockwise) {
        #endif
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
    // Conditional to reverse the direction of encoder number 1
    // The reason I have this is that for some of my boards, it supports two different types of encoders, and they may differ in direction
    #ifdef ENCODERS_B_REVERSE
    if (!clockwise) {
    #else
    if (clockwise) {
    #endif
        tap_code16(C(KC_RGHT));
    }
    else{
        tap_code16(C(KC_LEFT));
    }
    }
    else if (index == 2) {
    #ifdef ENCODERS_C_REVERSE
    if (!clockwise) {
    #else
    if (clockwise) {
    #endif
        tap_code16(C(KC_RGHT));
    } else {
        tap_code16(C(KC_LEFT));
    }
    }

    return true;
}
#endif


