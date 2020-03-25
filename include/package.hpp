// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

// plik nagłówkowy "package.hpp" zawierający definicję klasy Package

#ifndef NET_SLIM_PACKAGE_HPP
#define NET_SLIM_PACKAGE_HPP

#include <set>
#include <iostream>
#include "types.hpp"

class Package{
private:
    ElementID id_;
    ElementID assign_id();
    static std::set<ElementID>assigned_IDs;
    static std::set<ElementID>freed_IDs;
public:
    Package() { id_ = assign_id(); assigned_IDs.insert(get_id()); }
    Package(const Package& pack) = default;
    explicit Package(ElementID id) { id_ = id; assigned_IDs.insert(id); freed_IDs.erase(id);  }

    ~Package() { assigned_IDs.erase(id_); freed_IDs.insert(id_); }

    Package& operator = (Package&& pack) { freed_IDs.emplace(id_); id_ = std::move(pack.id_); return *this; };
    Package(Package&& pack) : id_(std::move(pack.id_)) {};
    ElementID get_id() const { return id_; }
};

#endif //NET_SLIM_PACKAGE_HPP
