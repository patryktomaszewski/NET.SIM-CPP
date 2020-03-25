// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#ifndef NET_SLIM_TYPES_HPP
#define NET_SLIM_TYPES_HPP

#include <cstdint>
#include <functional>

using ElementID = uint64_t ;
using TimeOffset = uint64_t ;
using Time = uint64_t ;
using ProbabilityGenerator = std::function<double()>;

#endif //NET_SLIM_TYPES_HPP
