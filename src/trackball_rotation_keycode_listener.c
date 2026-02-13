#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
// #include <zmk/events/pointer_changed.h>   // <- 削除/コメントアウト

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_REGISTER(trackball_rotation_keycode, CONFIG_ZMK_LOG_LEVEL);

static int trackball_rotation_keycode_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    /* TB_ROT_* はローカル処理用。押下/解放どちらも送信しない */
    if (trackball_rotation_handle_keycode(ev->keycode)) {
        if (ev->state) {
            LOG_INF("Trackball rotation updated");
        }
        return ZMK_EV_EVENT_CAPTURED;
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(trackball_rotation_keycode, trackball_rotation_keycode_listener);
ZMK_SUBSCRIPTION(trackball_rotation_keycode, zmk_keycode_state_changed);

/* ポインタイベント側は pmw3610 ドライバで補正済みなのでここでは無効化 */
