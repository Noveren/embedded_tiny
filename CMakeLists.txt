cmake_minimum_required(VERSION 3.22)

project(
    tiny
    LANGUAGES C
)

add_library(tiny STATIC)
target_include_directories(tiny
    PUBLIC inc
    PRIVATE src
)
aux_source_directory(src VAR_SOURCES)
target_sources(tiny
    PRIVATE ${VAR_SOURCES}
)