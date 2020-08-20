include_directories(${GTEST_PATH})
link_directories(${GTEST_PATH_LIB})
add_executable(chapter11gt_04 main.cpp)

if(MSVC)
  set_property(TARGET chapter11gt_04 PROPERTY
               MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_link_libraries(chapter11gt_04 debug gtestd.lib)
target_link_libraries(chapter11gt_04 optimized gtest.lib)