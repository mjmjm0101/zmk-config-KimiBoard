#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/events/pointer_move.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_REGISTER(trackball_rotation_keycode, CONFIG_ZMK_LOG_LEVEL);

static int trackball_rotation_keycode_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    // キーが押された時だけ処理
    if (ev->state) {
        if (trackball_rotation_handle_keycode(ev->keycode)) {
            LOG_INF("Trackball rotation updated");
            return ZMK_EV_EVENT_CAPTURED;  // キーコードを送信しない
        }
    }

    return ZMK_EV_EVENT_BUBBLE;
}

static int trackball_rotation_pointer_listener(const zmk_event_t *eh) {
    struct zmk_pointer_move_event *ev = as_zmk_pointer_move_event(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    int16_t rotated_x = 0, rotated_y = 0;
    trackball_rotate_delta(ev->dx, ev->dy, &rotated_x, &rotated_y);
    
    ev->dx = rotated_x;
    ev->dy = rotated_y;
    
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(trackball_rotation_keycode, trackball_rotation_keycode_listener);
ZMK_SUBSCRIPTION(trackball_rotation_keycode, zmk_keycode_state_changed);

ZMK_LISTENER(trackball_rotation_pointer, trackball_rotation_pointer_listener);
ZMK_SUBSCRIPTION(trackball_rotation_pointer, zmk_pointer_move_event);
