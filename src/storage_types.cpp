// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "storage_types.hpp"
#include "package.hpp"


Package PackageQueue::pop() {
    Package pck;

    switch(get_queue_type()){
        case PackageQueueType::FIFO:{
            pck = std::move(package_list.front());
            package_list.pop_front();
            break;
        }
        case PackageQueueType::LIFO:{
            pck = std::move(package_list.back());
            package_list.pop_back();
            break;
        }
    }

    return pck;
}
