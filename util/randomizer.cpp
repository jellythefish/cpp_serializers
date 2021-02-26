#include "util.hpp"

Randomizer::Randomizer() {
    std::random_device rd_int;
    gen_int.seed(rd_int());
    rand_ind.param(std::uniform_int_distribution<int32_t>::param_type(0, std::numeric_limits<int32_t>::max()));
}

int32_t Randomizer::GetRandInt() {
    return rand_ind(gen_int);
}
