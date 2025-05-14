cmake_minimum_required(VERSION 3.20)

zephyr_include_directories(include)
zephyr_syscall_include_directories(include)

add_subdirectory_ifdef(CONFIG_ZPL zpl)
