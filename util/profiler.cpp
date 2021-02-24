#include "util.hpp"

void profile(void (Serializer::*function)(), Serializer& obj, const Entry& e, tabulate::Table& t) {
    clock_t time;
    time = clock();
    (obj.*function)(); // calling function which is a non-static method of class Serializer
    double diff = clock() - time;
    size_t data_size = obj.GetDataSize();
    std::stringstream time_ss, memory_ss;
    time_ss << diff / (CLOCKS_PER_SEC / 1000)  << " ms/" << diff / CLOCKS_PER_SEC << " s";
    memory_ss << data_size << " b/" << data_size / 1024 << " Kb/" << data_size / (1024 * 1024) << " Mb";
    t.add_row({{e.type, e.operation, e.place, time_ss.str(), memory_ss.str()}});
}