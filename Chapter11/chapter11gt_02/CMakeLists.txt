include_directories(${GTEST_PATH})
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${GTEST_PATH_LIB})
add_executable(chapter11gt_02 main.cpp)

if(MSVC)
  set_property(TARGET chapter11gt_02 PROPERTY
               MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_link_libraries(chapter11gt_02 debug gtestd.lib)
target_link_libraries(chapter11gt_02 optimized gtest.lib)