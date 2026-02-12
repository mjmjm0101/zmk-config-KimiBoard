#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/keymap.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define KIMIBOARD_SCROLL_LAYER 1
#define KIMIBOARD_ROTATE_LEFT_KEY_POSITION 2
#define KIMIBOARD_ROTATE_RIGHT_KEY_POSITION 3

static int kimiboard_trackball_rotation_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);

    if (ev == NULL || !ev->state) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (!zmk_keymap_layer_active(KIMIBOARD_SCROLL_LAYER)) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    switch (ev->position) {
    case KIMIBOARD_ROTATE_LEFT_KEY_POSITION:
        rotate_left_45();
        return ZMK_EV_EVENT_CAPTURED;
    case KIMIBOARD_ROTATE_RIGHT_KEY_POSITION:
        rotate_right_45();
        return ZMK_EV_EVENT_CAPTURED;
    default:
        return ZMK_EV_EVENT_BUBBLE;
    }
}

ZMK_LISTENER(kimiboard_trackball_rotation, kimiboard_trackball_rotation_listener);
ZMK_SUBSCRIPTION(kimiboard_trackball_rotation, zmk_position_state_changed);
