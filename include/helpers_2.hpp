// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#ifndef NET_SLIM_HELPERS_HPP
#define NET_SLIM_HELPERS_HPP
#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>

#include "types.hpp"

//double default_probability_generator();

double my_generator();

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;

#endif //NET_SLIM_HELPERS_HPP
