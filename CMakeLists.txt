cmake_minimum_required(VERSION 3.17)
project(serialization)

set(CMAKE_CXX_STANDARD 20)

add_executable(serialization main.cpp struct.cpp serializer.cpp
        struct.h serializer.h)

# importing BOOST library
set(Boost_INCLUDE_DIR "C:/Program Files/boost/include")
set(Boost_LIBRARY_DIR "C:/Program Files/boost/lib")
find_package(Boost COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(serialization ${Boost_LIBRARIES})


