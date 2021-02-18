cmake_minimum_required(VERSION 3.17)
project(serialization)

set(CMAKE_CXX_STANDARD 20)

add_executable(serialization main.cpp serializer.hpp struct.cpp struct.hpp boost_serialization/boost_serializer.cpp
        boost_serialization/boost_serializer.hpp boost_json/boost_json.cpp boost_json/boost_json.hpp serializer.cpp)

# importing include single-header files
include_directories(include)

# importing BOOST library
set(Boost_INCLUDE_DIR "C:/Program Files/boost/include")
set(Boost_LIBRARY_DIR "C:/Program Files/boost/lib")
find_package(Boost REQUIRED COMPONENTS serialization json)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(serialization ${Boost_LIBRARIES})


