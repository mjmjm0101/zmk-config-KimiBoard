cmake_minimum_required(VERSION 3.20.0)

zephyr_library()
zephyr_library_sources(
    src/trackball_rotation.c
)
zephyr_library_include_directories(include)
