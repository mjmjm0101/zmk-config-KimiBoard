#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// キーマップで定義されたキーコードを監視するイベントリスナー
static int trackball_rotate_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);

    if (ev == NULL || !ev->state) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (trackball_rotation_handle_keycode(ev->keycode)) {
        return ZMK_EV_EVENT_CAPTURED;
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(trackball_rotate, trackball_rotate_listener);
ZMK_SUBSCRIPTION(trackball_rotate, zmk_keycode_state_changed);
