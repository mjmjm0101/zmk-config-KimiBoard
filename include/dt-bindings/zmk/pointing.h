/*
 * KimiBoard local pointing keycodes
 *
 * ZMK v0.3 系では dt-bindings 側に CPI_INC/CPI_DEC が存在しない環境があるため、
 * ローカルで補完定義する。
 */

#pragma once

#if defined(__has_include_next)
#if __has_include_next(<dt-bindings/zmk/pointing.h>)
#include_next <dt-bindings/zmk/pointing.h>
#endif
#endif

/*
 * 0xF600-0xF6FF は ZMK の内部制御キーコード用に使うローカル拡張レンジとして利用。
 * 同一ヘッダーを参照することで、keymap と実装側で値の整合を取る。
 */
#ifndef CPI_INC
#define CPI_INC 0xF601
#endif

#ifndef CPI_DEC
#define CPI_DEC 0xF602
#endif
