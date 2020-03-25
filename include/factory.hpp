// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#ifndef NET_SLIM_FACTORY_HPP
#define NET_SLIM_FACTORY_HPP

#include <utility>
#include "nodes.hpp"


template <typename Node>
class NodeCollection{
public:
    using container_t = typename std::list<Node>;
    using iterator = typename  std::list<Node>::iterator;
    using const_iterator = typename std::list<Node>::const_iterator;

//    NodeCollection() : container_() {}
//    NodeCollection(std::list<Node> collection) : container_(std::move(collection)) {}

    void add(Node &node) { container_.push_back(std::move(node)); }

    iterator find_by_id(ElementID id_) {
        auto it = std::find_if(container_.begin(), container_.end(),
                                   [id_](const auto& elem){ return (elem.get_id() == id_); });
        return it;
    }

    const_iterator find_by_id(ElementID id_) const {
        auto it = std::find_if(container_.cbegin(), container_.cend(),
                                         [id_](const auto& elem){ return (elem.get_id() == id_); });
        return it;
    }

    void remove_by_id(ElementID id_){
        auto it = this->find_by_id(id_);

        if(it != container_.end()){
            container_.erase(it);
        }
    }

    const_iterator cbegin() const { return container_.cbegin(); }
    const_iterator cend() const { return container_.cend(); }
    const_iterator begin() const { return container_.cbegin(); }
    const_iterator end() const { return container_.cend(); }
    iterator end() { return container_.end(); }
    iterator begin() { return container_.begin(); }

private:
    container_t container_;

};


class Factory{
private:
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;

//    template <typename Node>
//    void remove_receiver(NodeCollection<Node>& collection, ElementID id) { collection.remove_by_id(id); }
public:
//    Factory() : ramps_(), workers_(), storehouses_() {}
//    Factory(std::list<Worker> workers, std::list<Ramp> ramps, std::list<Storehouse> storehouses) : workers_(std::move(workers)), ramps_(std::move(ramps)), storehouses_(std::move(storehouses)) {}

    void add_ramp(Ramp&& ramp) { ramps_.add(ramp); }
    void remove_ramp(ElementID id);
//    void remove_ramp(ElementID id) { remove_receiver(ramps_, id); } // ???

    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){ return ramps_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramps_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator ramp_cbegin(){ return ramps_.cbegin(); };
    NodeCollection<Ramp>::const_iterator ramp_cend(){ return ramps_.cend(); };

    void add_worker(Worker&& worker) { workers_.add(worker); }
    void remove_worker(ElementID id);

    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){ return workers_.find_by_id(id); };
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return workers_.find_by_id(id); };
    NodeCollection<Worker>::const_iterator worker_cbegin(){ return workers_.cbegin(); };
    NodeCollection<Worker>::const_iterator worker_cend(){ return workers_.cend(); };

    void add_storehouse(Storehouse&& storehouse) { storehouses_.add(storehouse); }
    void remove_storehouse(ElementID id);

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){ return storehouses_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouses_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin(){ return storehouses_.cbegin(); };
    NodeCollection<Storehouse>::const_iterator storehouse_cend(){ return storehouses_.cend(); };

    bool is_consistent();
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
};


#endif //NET_SLIM_FACTORY_HPP
