#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zmk/behavior.h>
#include <zmk/behavior_binding.h>
#include <zmk/behavior_driver.h>

#include <kimiboard/trackball_rotation.h>

struct behavior_tb_rotate_config {
    int8_t dir; /* +1: CCW, -1: CW */
};

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_tb_rotate_config *cfg = dev->config;

    if (cfg->dir > 0) {
        rotate_left_45();
    } else {
        rotate_right_45();
    }

    /* 何も送らない（= o/n 等にならない） */
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    /* リリースでも何も送らない（押しっぱなし防止） */
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_tb_rotate_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

#define TB_ROTATE_INST(n)                                                                          \
    static const struct behavior_tb_rotate_config behavior_tb_rotate_config_##n = {                \
        .dir = DT_INST_PROP(n, dir),                                                               \
    };                                                                                             \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, &behavior_tb_rotate_config_##n, POST_KERNEL,      \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_tb_rotate_api);

DT_INST_FOREACH_STATUS_OKAY(TB_ROTATE_INST)

DT_DRV_COMPAT kimiboard_tb_rotate
