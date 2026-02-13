zephyr_library()

zephyr_library_sources_ifdef(CONFIG_PMW3610 src/pmw3610.c)

# このモジュールがあるリポジトリの include/ を確実に参照させる
zephyr_include_directories(${CMAKE_CURRENT_LIST_DIR}/../../include)

# ZMK keymap を使うため
zephyr_include_directories(${WEST_TOPDIR}/zmk/app/include)
