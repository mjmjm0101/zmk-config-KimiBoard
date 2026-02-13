#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_REGISTER(trackball_rotate, CONFIG_ZMK_LOG_LEVEL);

static int trackball_rotate_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    LOG_INF("Event received - keycode: 0x%04X, state: %d (TB_ROT_CCW=0x%04X, TB_ROT_CW=0x%04X)", 
            ev->keycode, ev->state, TB_ROT_CCW, TB_ROT_CW);

    if (!ev->state) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (trackball_rotation_handle_keycode(ev->keycode)) {
        LOG_INF("Trackball rotation executed!");
        return ZMK_EV_EVENT_CAPTURED;
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(trackball_rotate, trackball_rotate_listener);
ZMK_SUBSCRIPTION(trackball_rotate, zmk_keycode_state_changed);
