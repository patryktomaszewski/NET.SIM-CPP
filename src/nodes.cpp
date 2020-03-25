// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "nodes.hpp"
#include "helpers.hpp"
#include <iostream>


void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    preferences_.emplace(std::make_pair(r, 1.0));
    rebuild_pref();
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    preferences_.erase(r);
    rebuild_pref();
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double num = probabilityFunc_();
    IPackageReceiver* wanted_elem;
    double sum = 0;

    for (auto it=cbegin(); it!=cend(); ++it){
        sum = sum + it->second;
        if(sum >= num){
            wanted_elem = it->first;
            break;
        }
        else{
            wanted_elem = preferences_.end()->first;
        }
    }

    return wanted_elem;
}

void ReceiverPreferences::rebuild_pref(){
    double sum = 0;

    for(auto& elem : preferences_){
        elem.second = 1;
        sum+=1;
    }

    for(auto& elem : preferences_){
        elem.second=1/sum;
    }
}

void PackageSender::send_package(){

    if(buff_send_){
        receiver_preferences_.choose_receiver()->receive_package(std::move(*buff_send_));
        buff_send_.reset();
    }
}

void Ramp::deliver_goods(Time t){

    if(t % get_delivery_interval() == 1){
        Package pack;
        push_package(std::move(pack));
    }
}

void Worker::do_work(Time t){

    if((t- get_package_processing_start_time()) % get_processing_duration() == 1){
        if(worker_buffer_){
            push_package(std::move(*worker_buffer_));
            worker_buffer_.reset();
        }

        worker_buffer_.emplace(uniquePtr_->pop());
        startTime_ = t;
    }

}

