cmake_minimum_required(VERSION 3.20.0)

zephyr_library()
zephyr_library_sources(
    src/trackball_rotation.c
    src/behaviors/behavior_tb_rotate.c
    # src/trackball_rotation_keycode_listener.c
)

# 自分の公開ヘッダ
zephyr_library_include_directories(include)

# ZMK のヘッダ（event_manager.h / keycode_state_changed.h 等が必要）
zephyr_library_include_directories(${WEST_TOPDIR}/zmk/app/include)
zephyr_library_include_directories(${WEST_TOPDIR}/zmk/app/src)
