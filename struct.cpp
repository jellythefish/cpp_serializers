#include "struct.h"

#include <ctime>
#include <iostream>

using namespace std;

string generateRandomString(size_t size) {
    string res;
    for (size_t i = 0; i < size; ++i) {
        char c = ' ' + rand() % 95; // random char from ascii 32 - ' ' to 126 - '~'
        res += c;
    }
    return res;
}

void fillVector(vector<int>& v, size_t vec_size) {
    for (size_t i = 0; i < vec_size; ++i) {
        v.push_back(rand() % INT_MAX);
    }
}

void fillMap(map<string, string>& m, size_t map_size, size_t stringSize) {
    for (size_t i = 0; i < map_size; ++i) {
        m[generateRandomString(stringSize)] = generateRandomString(stringSize);
    }
}

void fillMapMap(map<string, map<string, int>>& m, size_t map_size, size_t nested_map_size, size_t stringSize) {
    for (size_t i = 0; i < map_size; ++i) {
        map<string, int> p;
        for (size_t j = 0; j < nested_map_size; ++j) {
            p[generateRandomString(stringSize)] = rand() % INT_MAX;
        }
        m[generateRandomString(stringSize)] = p;
    }
}

void fillMapVectorMap(map<string, vector<map<string,string>>>& m,
                      size_t map_size, size_t vector_size, size_t second_map_size, size_t stringSize) {
    for (size_t i = 0; i < map_size; ++i) {
        vector<map<string, string>> v;
        for (size_t j = 0; j < vector_size; ++j) {
            map<string, string> second_map;
            fillMap(second_map, second_map_size, stringSize);
            v.push_back(second_map);
        }
        m[generateRandomString(stringSize)] = v;
    }
}

DataStruct generateStruct(StructSize size) {
    srand(time(nullptr)); // use current time as seed for random generator
    DataStruct dataStruct;
    dataStruct.str = "Test string: Hello From Slava!";
    dataStruct.int_num = 42;
    dataStruct.double_num = 3.1415926;
    size_t stringSize, vecSize, mapSize, nestedMapSize;
    if (size == StructSize::Small) { // configuring size for different scale of D
        stringSize = 20, vecSize = 40, mapSize = 80, nestedMapSize = 15;
    } else if (size == StructSize::Medium) {
        stringSize = 100, vecSize = 130, mapSize = 50, nestedMapSize = 30;
    } else if (size == StructSize::Large) {
        stringSize = 200, vecSize = 200, mapSize = 100, nestedMapSize = 50;
    }
    fillVector(dataStruct.v_int, vecSize);
    fillMap(dataStruct.map_, mapSize, stringSize);
    fillMapMap(dataStruct.map_map, mapSize, nestedMapSize, stringSize);
    fillMapVectorMap(dataStruct.map_vector_map, mapSize, vecSize, nestedMapSize, stringSize);
    return dataStruct;
}