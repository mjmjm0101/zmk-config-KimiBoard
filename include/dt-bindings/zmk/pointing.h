/*
 * KimiBoard local pointing keycodes
 *
 * 目的:
 * - CPI増減ではなく、PCへ送るポインタ座標系の回転状態を切り替えるためのローカルキーコード。
 */

#pragma once

#if defined(__has_include_next)
#if __has_include_next(<dt-bindings/zmk/pointing.h>)
#include_next <dt-bindings/zmk/pointing.h>
#endif
#endif

/*
 * 0xF600-0xF6FF はローカル拡張キーコードとして使用。
 */
#ifndef TB_ROT_CW
#define TB_ROT_CW 0xF611
#endif

#ifndef TB_ROT_CCW
#define TB_ROT_CCW 0xF612
#endif

/*
 * 既存キーマップ互換のため残置（非推奨）。
 * 旧名: CPI_INC/CPI_DEC
 */
#ifndef CPI_INC
#define CPI_INC TB_ROT_CW
#endif

#ifndef CPI_DEC
#define CPI_DEC TB_ROT_CCW
#endif
