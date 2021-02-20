cmake_minimum_required(VERSION 3.16.3)
project(serialization)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp struct.cpp serializer.cpp)

# creating variables for methods of serialization
set(BOOST_SER boost_serialization/boost_serializer.cpp)
set(BOOST_JSON boost_json/boost_json.cpp)

# importing Tabulate for pretty-printing results
include(FetchContent)
FetchContent_Declare(
        tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate
)
FetchContent_MakeAvailable(tabulate)
include_directories(${tabulate_SOURCE_DIR}/include)


# for making root headers visible
include_directories(".")

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

