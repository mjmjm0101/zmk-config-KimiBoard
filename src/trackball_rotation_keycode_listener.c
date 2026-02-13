#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/key_position_state_changed.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_REGISTER(trackball_rotation_keypos, CONFIG_ZMK_LOG_LEVEL);

/*
 * 回転キーの「物理キー位置」を指定する。
 * - kimiboard.keymap の scroll_layer では 3個目/4個目に回転キーを置いているため、
 *   まずは 2, 3 を仮定（0始まり）する。
 * - もし違う場合はここだけ実機に合わせて修正。
 */
#define TB_ROT_POS_CCW 2
#define TB_ROT_POS_CW  3

static int trackball_rotation_keypos_listener(const zmk_event_t *eh) {
    const struct zmk_key_position_state_changed *ev = as_zmk_key_position_state_changed(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    /* 回転キー位置なら、押下/解放の両方を必ず握り潰す */
    if (ev->position == TB_ROT_POS_CCW) {
        if (ev->state) {
            rotate_left_45();
            LOG_INF("Trackball rotation CCW -> %u deg", trackball_rotation_angle_deg());
        }
        return ZMK_EV_EVENT_CAPTURED;
    }

    if (ev->position == TB_ROT_POS_CW) {
        if (ev->state) {
            rotate_right_45();
            LOG_INF("Trackball rotation CW -> %u deg", trackball_rotation_angle_deg());
        }
        return ZMK_EV_EVENT_CAPTURED;
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(trackball_rotation_keypos, trackball_rotation_keypos_listener);
ZMK_SUBSCRIPTION(trackball_rotation_keypos, zmk_key_position_state_changed);
