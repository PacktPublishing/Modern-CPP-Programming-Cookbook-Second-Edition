file(GLOB headers *.h)
add_executable(chapter06 main.cpp ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()