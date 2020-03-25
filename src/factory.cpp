// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "factory.hpp"

void Factory::remove_ramp(ElementID id) {
    ramps_.remove_by_id(id);
}

void Factory::remove_worker(ElementID id) {

    std::for_each(ramps_.begin(),ramps_.end(),[id](Ramp &ramp){
        auto preferences = ramp.receiver_preferences_.get_preferences();

        for(auto & preference : preferences){
            if(preference.first->get_id()==id){
                ramp.receiver_preferences_.remove_receiver(preference.first);
            }
        }
    });

    workers_.remove_by_id(id);

}

void Factory::remove_storehouse(ElementID id) {

    std::for_each(workers_.begin(),workers_.end(),[id](Worker &worker)
    {
        auto preferences =worker.receiver_preferences_.get_preferences();
        for(auto & preference : preferences){
            if(preference.first->get_id()==id){
                worker.receiver_preferences_.remove_receiver(preference.first);
            }
        }
    });

    storehouses_.remove_by_id(id);
}


bool Factory::is_consistent() {

    if(ramps_.begin() == ramps_.end()) { return false; }
    if(workers_.begin() == workers_.end()) { return false; }
    if(storehouses_.begin() == storehouses_.end()) { return false; }

    bool corresponding = true;

    std::for_each(ramps_.begin(),ramps_.end(),[&corresponding](Ramp &ramp)
    {
        auto preferences = ramp.receiver_preferences_.get_preferences();
        if(preferences.empty()) { corresponding = false; }
    } );

    std::for_each(workers_.begin(),workers_.end(),[this,&corresponding](Worker &worker)
    {
        bool check = false;
        bool least =false;

        auto prefs = worker.receiver_preferences_.get_preferences();
        ElementID id = worker.get_id();

        std::for_each(ramps_.begin(),ramps_.end(),[id,&least](Ramp &ramp)
        {
            auto preferences=ramp.receiver_preferences_.get_preferences();
            for(auto & preference : preferences){
                if(preference.first->get_id() == id){
                    least = true;
                }
            }
        });

        std::for_each(workers_.begin(),workers_.end(),[id,&least](Worker &worker) {
            if(worker.get_id()!=id) {
                auto preferences = worker.receiver_preferences_.get_preferences();
                for (auto & preference : preferences){
                    if (preference.first->get_id() == id){
                        least = true;
                    }
                }
            }});

        for(auto & preference : prefs){
            auto type = preference.first->get_receiver_type();

            if(preference.first->get_id() != id || type == ReceiverType::STOREHOUSE){
                check = true;
            }
        }

        if(!least){ corresponding=false;}
        if(!check){ corresponding=false;}
    });

    std::for_each(storehouses_.begin(),storehouses_.end(),[this,&corresponding](Storehouse &storehouse)
    {
        ElementID id = storehouse.get_id();
        bool least = false;
        std::for_each(workers_.begin(),workers_.end(),[id,&least](Worker &worker)
        {
            auto preferences = worker.receiver_preferences_.get_preferences();
            for(auto & preference : preferences){
                if(preference.first->get_id()==id){
                    least = true;
                }
            }
        } );

        if(!least){ corresponding=false;}
    });

    return corresponding;
}


void Factory::do_deliveries(Time t) {
    for(auto & ramp: ramps_){
        ramp.deliver_goods(t);
    }
}


void Factory::do_package_passing() {
    for(auto &ramp: ramps_){
        if(ramp.get_sending_buffer().has_value()){
            ramp.send_package();
        }
    }

    for(auto &worker: workers_){
        if(worker.get_sending_buffer().has_value()){
            worker.send_package();
        }
    }
}


void Factory::do_work(Time t) {
    for(auto & worker: workers_){
        worker.do_work(t);
    }
}

