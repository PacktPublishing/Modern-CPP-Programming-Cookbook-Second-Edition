file(GLOB headers *.h ${headers})
add_executable(chapter12_06 main.cpp ${headers})

if(${USE_RANGES_V3})
   include_directories(${RANGES_PATH})
   add_compile_definitions(USE_RANGES_V3)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)