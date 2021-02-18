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
DataStruct GetSimpleStruct();

/* Example for DataStruct
{
  "str": "Hello From Slava!",
  "int_num": 42,
  "double_num": 3.1415926,
  "v_int": [1, 2, 3, 4, 5],
  "map_str_str": {
    "statusCode": "200"
    "message": "i am ok",
  },
  "map_map": {
    "Jack": {
      "age": 25,
      "birthYear": 1996
    },
    "Mary": {
      "age": 22,
      "birthYear": 1999
    }
  },
  "map_vector_map": {
    "requests": [
      {
        "method": "POST"
        "data": "post it",
      },
      {
        "method": "GET"
        "data": "get me some",
      },
      {
        "method": "PUT"
        "data": "put it or die",
      }
    ],
    "responses": [
      {
        "statusCode": "400"
        "message": "loh",
      },
      {
        "statusCode": "200"
        "message": "ok, boy",
      },
      {
        "statusCode": "418"
        "message": "I'm a teapot",
      }
    ]
  }
}
*/

#endif // SERIALIZATION_STRUCT_H_