#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/input/input.h>
#include <zephyr/logging/log.h>

#include <kimiboard/trackball_rotation.h>

LOG_MODULE_REGISTER(trackball_rotation_processor, CONFIG_ZMK_LOG_LEVEL);

struct trackball_rotation_config {
    int dummy;
};

struct trackball_rotation_data {
    const struct device *dev;
};

static int trackball_rotation_process(const struct device *dev,
                                      struct input_event *evt)
{
    if (evt->type != INPUT_EV_REL) {
        return 0;
    }

    if (evt->code == INPUT_REL_X || evt->code == INPUT_REL_Y) {
        int16_t x = 0, y = 0;

        // 一時的に値を保持（この処理は簡略版です）
        static int16_t stored_x = 0, stored_y = 0;

        if (evt->code == INPUT_REL_X) {
            stored_x = evt->value;
        } else if (evt->code == INPUT_REL_Y) {
            stored_y = evt->value;
        }

        // 両方の値が揃ったら回転処理
        if (stored_x != 0 || stored_y != 0) {
            trackball_rotate_delta(stored_x, stored_y, &x, &y);
            
            if (evt->code == INPUT_REL_X) {
                evt->value = x;
                stored_x = 0;
            } else if (evt->code == INPUT_REL_Y) {
                evt->value = y;
                stored_y = 0;
            }
        }
    }

    return 0;
}

static int trackball_rotation_init(const struct device *dev)
{
    LOG_INF("Trackball rotation processor initialized");
    return 0;
}

#define TRACKBALL_ROTATION_INIT(inst) \
    static const struct trackball_rotation_config trackball_rotation_cfg_##inst = {}; \
    static struct trackball_rotation_data trackball_rotation_data_##inst = {}; \
    DEVICE_DT_INST_DEFINE(inst, trackball_rotation_init, NULL, \
                          &trackball_rotation_data_##inst, \
                          &trackball_rotation_cfg_##inst, \
                          POST_KERNEL, \
                          CONFIG_INPUT_PROCESSOR_PRIORITY, \
                          NULL);

DT_INST_FOREACH_STATUS_OKAY(TRACKBALL_ROTATION_INIT)

// Input processor registration
void trackball_rotation_processor_register(const struct device *dev)
{
    input_register_processor(dev, trackball_rotation_process);
}
