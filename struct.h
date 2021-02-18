#ifndef SERIALIZATION_STRUCT_H_
#define SERIALIZATION_STRUCT_H_

#include <vector>
#include <map>

enum class StructSize {
    Small,
    Medium,
    Large
};

struct DataStruct {
    std::string str;
    int int_num;
    double double_num;
    std::vector<int> v_int;
    std::map<std::string, std::string> map_str_str;
    std::map<std::string, std::map<std::string, int>> map_map;
    std::map<std::string, std::vector<std::map<std::string, std::string>>> map_vector_map;
};

DataStruct GenerateStruct(StructSize size);

/* Example for DataStruct
{
    "str": "Hello",
    "int_1": 1245,
    "double_1": 3.1415,
    "v_int_1": [12, 43, 65, 23],
    "map_1": {
        "hi": "oh, hello",
        "ur good?": "ye, im fine",
    }
    "map_2": {
        "address": {
            "street": 454,
            "postcode": 544235,
            "city_code": 161
        }
    },
    "map_3": {
        "dataset": [
            {
                "name": "Bob",
                "surname": "Cooper"
            },
            {
                "name": "Alice",
                "surname": "Not Cooper"
            }
        ]
    }
} */

#endif // SERIALIZATION_STRUCT_H_