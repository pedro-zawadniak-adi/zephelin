cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)
target_sources(app PRIVATE src/main.c src/model.cpp)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/src")

# generate header with model data

set(model_path "${CMAKE_CURRENT_LIST_DIR}/model/magic-wand.tflite")

add_custom_command(
  OUTPUT
    src/generated/model_data.h
  DEPENDS
    ${model_path}
  COMMAND
    cp ${model_path} model_data
  COMMAND
    xxd -i model_data src/generated/model_data.h
  COMMAND
    rm model_data
  COMMAND
    sed -i -e "'s/unsigned/const unsigned/g'"
      src/generated/model_data.h
  COMMAND
    sed -i -e "'s/const unsigned char/const unsigned char __attribute((aligned(32)))/g'"
      src/generated/model_data.h
)

add_custom_target(
  generate_model_data_h
  DEPENDS
    src/generated/model_data.h
)

add_dependencies(app generate_model_data_h)
