zephyr_library()

zephyr_library_sources_ifdef(CONFIG_PMW3610 src/pmw3610.c)
zephyr_include_directories(${WEST_TOPDIR}/include)
zephyr_include_directories(${WEST_TOPDIR}/zmk/app/include)
