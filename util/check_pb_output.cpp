#include <iostream>
#include "data_struct.pb.h"

// Function to check output from Deserialized Protobuf (a hard one)
void CheckOutput(const proto::DataStruct ds_message) {
    std::cout << ds_message.str() << " " <<  ds_message.int_num() << std::endl;
    std::cout << "{\n";
    for (size_t i = 0; i < ds_message.map_str_str_size(); ++i) {
        proto::DataStruct::BasicMap base_map = ds_message.map_str_str(i);
        std::string key_bm = base_map.key();
        std::string key_value = base_map.value();
        std::cout << "\t" << key_bm << ": " << key_value << ",\n";
    }
    std::cout << "}\n";

    std::cout << "{\n";
    for (size_t i = 0; i < ds_message.map_vector_map_size(); ++i) {
        const proto::DataStruct::MapVectorMap& mvm = ds_message.map_vector_map(i);
        std::cout << "\t" << mvm.key() << ":\n";
        std::cout << "\t\t[\n";
        for (size_t j = 0; j < mvm.value_size(); ++j) {
            auto vm = mvm.value(j);
            std::cout << "\t\t\t{\n";
            for (size_t k = 0; k < vm.vm_size(); ++k) {
                auto base_map = vm.vm(k);
                std::cout << "\t\t\t\t" << base_map.key() << ": " << base_map.value() << ",\n";
            }
            std::cout << "\t\t\t},\n";
        }
        std::cout << "\t\t],\n";
    }
    std::cout << "}\n";
}