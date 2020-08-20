file(GLOB headers *.h ${headers})
add_executable(chapter12_08_1 main.cpp ${headers})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CPPCORO_PATH}/include)

if(MSVC)
  message(status "Suporting coroutines")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
endif()
