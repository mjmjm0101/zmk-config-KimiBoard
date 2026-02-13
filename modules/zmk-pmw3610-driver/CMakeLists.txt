zephyr_library()

zephyr_library_sources_ifdef(CONFIG_PMW3610 src/pmw3610.c)

# Ensure the KimiBoard config repo's top-level include/ is visible from this module build.
zephyr_include_directories(${WEST_TOPDIR}/include)
