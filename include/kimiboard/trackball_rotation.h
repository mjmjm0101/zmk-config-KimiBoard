#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <dt-bindings/zmk/pointing.h>
#include <dt-bindings/zmk/kimiboard.h>

#ifdef __cplusplus
extern "C" {
#endif

void rotate_left_45(void);
void rotate_right_45(void);
uint16_t trackball_rotation_angle_deg(void);
void trackball_rotate_delta(int16_t dx, int16_t dy, int16_t *out_dx, int16_t *out_dy);
bool trackball_rotation_handle_keycode(uint32_t keycode);

#ifdef __cplusplus
}
#endif
