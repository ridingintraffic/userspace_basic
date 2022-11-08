#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

//beginTapDance
typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
};

enum
{
  F12TAP = 0,
  TABCOMBO

};

// Declare your tapdance functions:

// Function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);
int hold_cur_dance (qk_tap_dance_state_t *state);

void tab_finished (qk_tap_dance_state_t *state, void *user_data);
void tab_reset (qk_tap_dance_state_t *state, void *user_data);

void esc_finished (qk_tap_dance_state_t *state, void *user_data);
void esc_reset (qk_tap_dance_state_t *state, void *user_data);

void enter_finished (qk_tap_dance_state_t *state, void *user_data);
void enter_reset (qk_tap_dance_state_t *state, void *user_data);

void l1_finished (qk_tap_dance_state_t *state, void *user_data);
void l1_reset (qk_tap_dance_state_t *state, void *user_data);

void l2_finished (qk_tap_dance_state_t *state, void *user_data);
void l2_reset (qk_tap_dance_state_t *state, void *user_data);

void register_ctrl_shift (void);
void unregister_ctrl_shift (void);

void register_alt_shift (void);
void unregister_alt_shift (void);

//endTapDance