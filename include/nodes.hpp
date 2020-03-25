// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#ifndef NET_SLIM_NODES_HPP
#define NET_SLIM_NODES_HPP


#include <bits/unique_ptr.h>
#include <map>
#include <functional>
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"
#include <optional>
#include <utility>

enum class ReceiverType{
    WORKER,
    STOREHOUSE
};

class IPackageReceiver{
public:
    using iterator = IPackageStockpile::const_iterator;

    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() const = 0;

    virtual iterator cbegin() const = 0;
    virtual iterator cend() const = 0;
    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
};


class ReceiverPreferences{
private:
    ProbabilityGenerator probabilityFunc_;
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    preferences_t preferences_;
    ReceiverPreferences(ProbabilityGenerator probability_function = probability_generator): probabilityFunc_(std::move(probability_function)) {};

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    void rebuild_pref();
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const { return preferences_; }

    const_iterator cbegin() const { return preferences_.cbegin(); }
    const_iterator cend() const { return preferences_.cend(); }
    const_iterator begin() { return preferences_.begin(); }
    const_iterator end() { return preferences_.end(); }
};


class PackageSender{
private:
    std::optional<Package> buff_send_;
public:
    PackageSender(PackageSender&&) = default;
    explicit PackageSender() : buff_send_() , receiver_preferences_() {};

    ReceiverPreferences receiver_preferences_;
    std::optional<Package> & get_sending_buffer() { return buff_send_; }
    void send_package();
protected:
    void push_package(Package&& pack){ buff_send_.emplace(std::move(pack)); }
};


class Ramp : public PackageSender{
private:
    ElementID  id_;
    TimeOffset timeOffset_;
    std::optional<Time > ramp_buff_;
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), timeOffset_(di) {}

    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return timeOffset_; };
    ElementID get_id() const { return id_; }
};


class Worker : public PackageSender, public IPackageReceiver{
private:
    Time startTime_;
    TimeOffset timeOffset_;
    ElementID id_;
    std::optional<Time> opt;
    std::optional<Package> worker_buffer_;
    std::unique_ptr<IPackageQueue> uniquePtr_;
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : startTime_(0), timeOffset_(pd), id_(id), uniquePtr_(std::move(q)) {}

    void do_work(Time t);
    TimeOffset get_processing_duration() const { return timeOffset_; }
    Time get_package_processing_start_time() const { return startTime_; }
    ElementID get_id() const override { return id_; }
    ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; } // !!!
    void receive_package(Package&& p) override { uniquePtr_->push(std::move(p)); }

    iterator cbegin() const override { return uniquePtr_->cbegin(); }
    iterator cend() const override { return uniquePtr_->cend(); }
    iterator begin() const override { return uniquePtr_->begin(); }
    iterator end() const override{ return uniquePtr_->end(); }
};


class Storehouse : public IPackageReceiver{
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> uniquePtr_;
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id), uniquePtr_(std::move(d)) {}
    Storehouse(ElementID id) : id_(id) {}

    ElementID get_id() const override { return id_; }
    ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE; } // !!!
    void receive_package(Package&& p) override { uniquePtr_->push(std::move(p)); }

    iterator cbegin() const override { return uniquePtr_->cbegin(); }
    iterator cend() const override { return uniquePtr_->cend(); }
    iterator begin() const override { return uniquePtr_->begin(); }
    iterator end() const override{ return uniquePtr_->end(); }
};


#endif //NET_SLIM_NODES_HPP

