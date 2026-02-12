#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int kimiboard_trackball_rotation_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);

    if (ev == NULL || !ev->state) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (trackball_rotation_handle_keycode(ev->keycode)) {
        return ZMK_EV_EVENT_CAPTURED;
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(kimiboard_trackball_rotation, kimiboard_trackball_rotation_listener);
ZMK_SUBSCRIPTION(kimiboard_trackball_rotation, zmk_keycode_state_changed);
