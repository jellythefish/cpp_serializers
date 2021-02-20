cmake_minimum_required(VERSION 3.16.3)
project(serialization)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp struct.cpp serializer.cpp)

# creating variables for methods of serialization
set(BOOST_SER boost_serialization/boost_serializer.cpp)
set(BOOST_JSON boost_json/boost_json.cpp)

# importing include single-header files
include_directories(include)
include_directories(".") # for making root headers visible

add_executable(${PROJECT_NAME} ${SOURCE}
        ${BOOST_SER} ${BOOST_JSON})

# importing BOOST library
#set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS serialization json)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find boost components")
    return()
else()
    include_directories(${Boost_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


