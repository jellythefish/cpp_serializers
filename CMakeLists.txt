cmake_minimum_required(VERSION 3.16.3)
project(serialization)

set(CMAKE_CXX_STANDARD 20)

# for making root headers visible
include_directories(".")

set(SOURCE main.cpp struct.cpp serializer.cpp)

# creating variables for project sources
set(BOOST_SER boost_serialization/boost_serializer.cpp)
set(BOOST_JSON boost_json/boost_json.cpp)
set(PROTOBUF protobuf/protobuf_serializer.cpp)
set(AVRO_SER avro/avro_serializer.cpp)
set(YAML_SER yaml/yaml_serializer.cpp)
set(MSGPACK_SER message_pack/msgpack_serializer.cpp)
set(PROFILER util/profiler.cpp)

# importing Tabulate for pretty-printing results
include(FetchContent)
FetchContent_Declare(
        tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate
)
FetchContent_MakeAvailable(tabulate)
include_directories(${tabulate_SOURCE_DIR}/include)

# importing BOOST library
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS serialization json)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find boost components")
    return()
else()
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# importing Google Protobuf
set(Protobuf_USE_STATIC_LIBS OFF)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protobuf/data_struct.proto) # Building protobuf stubs

# importing Apache Avro
add_library(Avro SHARED IMPORTED)
find_library(Avro_LOCATION NAMES libavrocpp.so)
set_target_properties(Avro PROPERTIES IMPORTED_LOCATION ${Avro_LOCATION})

# importing YAML
add_library(YAML SHARED IMPORTED)
find_library(YAML_LOCATION NAMES libyaml-cpp.so)
set_target_properties(YAML PROPERTIES IMPORTED_LOCATION ${YAML_LOCATION})

# importing MessagePack
include_directories("/usr/local/include/msgpack")

add_executable(${PROJECT_NAME} ${SOURCE}
        ${BOOST_SER} ${BOOST_JSON} ${PROTOBUF} ${PROTO_SRCS} ${PROTO_HDRS}
        ${AVRO_SER} ${YAML_SER} ${MSGPACK_SER} ${PROFILER})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${Protobuf_LIBRARIES}
        Avro YAML)
