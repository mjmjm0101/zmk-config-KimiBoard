cmake_minimum_required(VERSION 3.20.0)

zephyr_library()
zephyr_library_sources(
    src/trackball_rotation.c
    src/behaviors/behavior_tb_rotate.c
)

zephyr_library_include_directories(include)
zephyr_library_include_directories(${WEST_TOPDIR}/zmk/app/include)
zephyr_library_include_directories(${WEST_TOPDIR}/zmk/app/src)
