#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zmk/behavior.h>

#include <kimiboard/trackball_rotation.h>

#define DT_DRV_COMPAT kimiboard_behavior_trackball_rotate

struct behavior_trackball_rotate_config {
    bool clockwise;
};

static int on_binding_pressed(const struct device *dev, struct zmk_behavior_binding *binding,
                              struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);

    const struct behavior_trackball_rotate_config *config = dev->config;

    if (config->clockwise) {
        rotate_right_45();
    } else {
        rotate_left_45();
    }

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_binding_released(const struct device *dev, struct zmk_behavior_binding *binding,
                               struct zmk_behavior_binding_event event) {
    ARG_UNUSED(dev);
    ARG_UNUSED(binding);
    ARG_UNUSED(event);

    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_trackball_rotate_driver_api = {
    .binding_pressed = on_binding_pressed,
    .binding_released = on_binding_released,
};

#define TRACKBALL_ROTATE_INST(n)                                                                     \
    static const struct behavior_trackball_rotate_config behavior_trackball_rotate_config_##n = {    \
        .clockwise = DT_INST_PROP(n, clockwise),                                                     \
    };                                                                                                \
                                                                                                      \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, &behavior_trackball_rotate_config_##n,             \
                            POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                        \
                            &behavior_trackball_rotate_driver_api);

DT_INST_FOREACH_STATUS_OKAY_SEP(TRACKBALL_ROTATE_INST, (;))
