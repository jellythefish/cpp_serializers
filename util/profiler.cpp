#include "util.hpp"

#include <vector>

void profile(void (Serializer::*ser_func)(), void (Serializer::*deser_func)(), long int iter,
             Serializer& obj, const Entry& e, tabulate::Table& t) {
    std::vector<std::pair<time_t, size_t>> ser, deser; // {time, memory}
    long int cnt = 1;
    while (cnt <= iter) {
        clock_t time_ser;
        time_ser = clock();
        (obj.*ser_func)(); // calling function which is a non-static method of class Serializer
        double diff_ser = clock() - time_ser;
        size_t data_ser = obj.GetDataSize();

        clock_t time_deser;
        time_deser = clock();
        (obj.*deser_func)();
        double diff_deser = clock() - time_deser;
        size_t data_deser = obj.GetDataSize();

        ser.push_back({diff_ser, data_ser});
        deser.push_back({diff_deser, data_deser});

        std::cout << e.type << " running - iteration: " << cnt << " out of " << iter << ". Operations with " << e.place <<
            ". Ser time - " << diff_ser / (CLOCKS_PER_SEC / 1000)  << "ms, Ser memory - " << data_ser / 1024 << " Kb."
            " Deser time - " << diff_deser / (CLOCKS_PER_SEC / 1000)  << "ms, Deser memory - " << data_deser / 1024 << " Kb."
            << "\r" << std::flush;
        ++cnt;
    }
    std::cout << std::endl;

    // Counting averages
    double average_time_ser = 0, average_time_deser = 0;
    size_t average_memory_ser = 0, average_memory_deser = 0;
    for (const auto& [cur_time, cur_memory] : ser) {
        average_time_ser += cur_time;
        average_memory_ser += cur_memory;
    }
    for (const auto& [cur_time, cur_memory] : deser) {
        average_time_deser += cur_time;
        average_memory_deser += cur_memory;
    }
    average_time_ser /= ser.size();
    average_memory_ser /= ser.size();
    average_time_deser /= deser.size();
    average_memory_deser /= deser.size();

    // Output to table

    std::stringstream time_ser_ss, memory_ser_ss, time_deser_ss, memory_deser_ss;
    time_ser_ss << average_time_ser / (CLOCKS_PER_SEC / 1000)  << " ms/" << average_time_ser / CLOCKS_PER_SEC << " s";
    memory_ser_ss << average_memory_ser << " b/" << average_memory_ser / 1024 << " Kb/" << average_memory_ser / (1024 * 1024) << " Mb";
    time_deser_ss << average_time_deser / (CLOCKS_PER_SEC / 1000)  << " ms/" << average_time_deser / CLOCKS_PER_SEC << " s";
    memory_deser_ss << average_memory_deser << " b/" << average_memory_deser / 1024 << " Kb/" << average_memory_deser / (1024 * 1024) << " Mb";
    t.add_row({{e.type, "Serialization", e.place, time_ser_ss.str(), memory_ser_ss.str()}});
    t.add_row({{e.type, "Deserialization", e.place, time_deser_ss.str(), memory_deser_ss.str()}});
}