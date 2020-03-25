// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#ifndef NET_SLIM_STORAGE_TYPES_HPP
#define NET_SLIM_STORAGE_TYPES_HPP

#include <cstddef>
#include "package.hpp"
#include <string>
#include <list>
#include <deque>

enum class PackageQueueType{
    FIFO,
    LIFO
};


class IPackageStockpile{
public:
    virtual void push(Package&& pack) = 0;
    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;

    using const_iterator = std::list<Package>::const_iterator;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
};


class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
    virtual ~IPackageQueue() = default;
};

class PackageQueue: public IPackageQueue{
private:
    PackageQueueType queue_type;
    std::list<Package> package_list;
public:
    PackageQueue(PackageQueueType queue_type_): queue_type(queue_type_) {}

    Package pop() override;
    PackageQueueType get_queue_type() const override { return queue_type; }
    void push(Package&& pack) override { package_list.push_back(std::move(pack)); }
    bool empty() const override { return package_list.empty(); }
    std::size_t size() const override { return package_list.size(); }

    const_iterator cbegin() const override { return package_list.cbegin(); }
    const_iterator cend() const override { return package_list.cend(); }
    const_iterator begin() const override { return package_list.begin(); }
    const_iterator end() const override { return package_list.end(); }
};

#endif //NET_SLIM_STORAGE_TYPES_HPP
