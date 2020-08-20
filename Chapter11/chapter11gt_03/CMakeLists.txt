include_directories(${GTEST_PATH})
link_directories(${GTEST_PATH_LIB})
add_executable(chapter11gt_03 main.cpp)

if(MSVC)
  set_property(TARGET chapter11gt_03 PROPERTY
               MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_link_libraries(chapter11gt_03 debug gtestd.lib)
target_link_libraries(chapter11gt_03 optimized gtest.lib)