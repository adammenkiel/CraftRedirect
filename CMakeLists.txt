cmake_minimum_required(VERSION 3.15)
project(CraftRedirect)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE CORE_SRC
    src/*
)

add_executable(app ${CORE_SRC})

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(app PRIVATE
    Boost::boost
    ws2_32
    spdlog::spdlog
)

set_target_properties(app PROPERTIES OUTPUT_NAME "craft_redirect_app")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    target_link_libraries(app PRIVATE ws2_32)
endif()