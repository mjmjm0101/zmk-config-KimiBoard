#include <kimiboard/trackball_rotation.h>

#include <limits.h>
#include <stddef.h>

#define Q15_ONE 32768
#define Q15_COS_45 23170

static const int32_t q15_cos_table[8] = {Q15_ONE, Q15_COS_45, 0, -Q15_COS_45, -Q15_ONE, -Q15_COS_45, 0,
                                         Q15_COS_45};
static const int32_t q15_sin_table[8] = {0, Q15_COS_45, Q15_ONE, Q15_COS_45, 0, -Q15_COS_45, -Q15_ONE,
                                         -Q15_COS_45};

static uint8_t rotation_step;

static int16_t clamp_i32_to_i16(int32_t value) {
    if (value > INT16_MAX) {
        return INT16_MAX;
    }

    if (value < INT16_MIN) {
        return INT16_MIN;
    }

    return (int16_t)value;
}

static int16_t q15_mul_round(int16_t value, int32_t coeff_q15) {
    int32_t product = (int32_t)value * coeff_q15;
    if (product >= 0) {
        product += (Q15_ONE / 2);
    } else {
        product -= (Q15_ONE / 2);
    }

    return (int16_t)(product / Q15_ONE);
}

void rotate_left_45(void) { rotation_step = (uint8_t)((rotation_step + 1U) & 0x07U); }

void rotate_right_45(void) { rotation_step = (uint8_t)((rotation_step + 7U) & 0x07U); }

uint16_t trackball_rotation_angle_deg(void) { return (uint16_t)rotation_step * 45U; }

void trackball_rotate_delta(int16_t dx, int16_t dy, int16_t *out_dx, int16_t *out_dy) {
    int32_t cos_q15 = q15_cos_table[rotation_step];
    int32_t sin_q15 = q15_sin_table[rotation_step];

    int32_t rotated_x = (int32_t)q15_mul_round(dx, cos_q15) - (int32_t)q15_mul_round(dy, sin_q15);
    int32_t rotated_y = (int32_t)q15_mul_round(dx, sin_q15) + (int32_t)q15_mul_round(dy, cos_q15);

    if (out_dx != NULL) {
        *out_dx = clamp_i32_to_i16(rotated_x);
    }

    if (out_dy != NULL) {
        *out_dy = clamp_i32_to_i16(rotated_y);
    }
}

bool trackball_rotation_handle_keycode(uint32_t keycode) {
    switch (keycode) {
    case TB_ROT_CCW:
        rotate_left_45();
        return true;
    case TB_ROT_CW:
        rotate_right_45();
        return true;
    default:
        return false;
    }
}
