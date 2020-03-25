// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "package.hpp"

std::set<ElementID>Package::assigned_IDs = {};
std::set<ElementID>Package::freed_IDs = {};

ElementID Package::assign_id() {

    ElementID id_to_assign;

    if(freed_IDs.empty()){
        if(assigned_IDs.empty()){
            id_to_assign = 1;
            assigned_IDs.insert(id_to_assign);
        }else{
            id_to_assign = *(assigned_IDs.rbegin()) + 1;
            assigned_IDs.insert(id_to_assign);
        }
    }else{
        id_to_assign = *(freed_IDs.begin());
        freed_IDs.erase(id_to_assign);
        assigned_IDs.insert(id_to_assign);
    }

    return id_to_assign;
}