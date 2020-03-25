// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//


#include <helpers.hpp>

double default_probability_generator() {
    srand(time(0));
    return (double) (rand() % RAND_MAX) / RAND_MAX;
}

std::function<double()> probability_generator = default_probability_generator;

double my_generator() {
    return 0.4;
}
