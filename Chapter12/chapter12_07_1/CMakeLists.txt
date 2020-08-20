file(GLOB headers *.h ${headers})
add_executable(chapter12_07_1 main.cpp "${CPPCORO_PATH}/lib/lightweight_manual_reset_event.cpp" ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CPPCORO_PATH}/include)

if(MSVC)
  message(status "Suporting coroutines")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
  
  target_link_libraries(chapter12_07_1 debug Synchronization.lib)
  target_link_libraries(chapter12_07_1 optimized Synchronization.lib)
endif()
