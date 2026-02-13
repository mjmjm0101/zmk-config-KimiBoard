#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/pointer_move.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int trackball_rotation_pointer_listener(const zmk_event_t *eh) {
    struct zmk_pointer_move_event *ev = as_zmk_pointer_move_event(eh);

    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    // トラックボール移動ベクトルを現在の回転角度で補正
    int16_t rotated_x = 0;
    int16_t rotated_y = 0;
    
    trackball_rotate_delta(ev->dx, ev->dy, &rotated_x, &rotated_y);
    
    // 補正されたベクトルを適用
    ev->dx = rotated_x;
    ev->dy = rotated_y;
    
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(trackball_rotation_pointer, trackball_rotation_pointer_listener);
ZMK_SUBSCRIPTION(trackball_rotation_pointer, zmk_pointer_move_event);
