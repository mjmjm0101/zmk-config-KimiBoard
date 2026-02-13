/*
 * kimiboard/trackball_rotation.h
 * 公開 API (プロトタイプ)
 */

#ifndef KIMIBOARD_TRACKBALL_ROTATION_H
#define KIMIBOARD_TRACKBALL_ROTATION_H

#include <stdint.h>
#include <stdbool.h>

/* TB_ROT_* を使う実装があるので、ここで定義(または定義元)を見えるようにする */
#include <dt-bindings/zmk/pointing.h>
#include <dt-bindings/zmk/kimiboard.h>

/* 念のため: dt-bindings の解決が別物になってもビルドが落ちないように保険 */
#ifndef TB_ROT_CW
#define TB_ROT_CW 0xF611
#endif
#ifndef TB_ROT_CCW
#define TB_ROT_CCW 0xF612
#endif

void rotate_left_45(void);
void rotate_right_45(void);
uint16_t trackball_rotation_angle_deg(void);
void trackball_rotate_delta(int16_t dx, int16_t dy, int16_t *out_dx, int16_t *out_dy);
bool trackball_rotation_handle_keycode(uint32_t keycode);

#endif /* KIMIBOARD_TRACKBALL_ROTATION_H */
