#include <iostream>

#include "factory.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "nodes.hpp"

int main() {

    std::list<Ramp> ramps;
    Ramp ramp1(1, 2);
    Ramp ramp2(2, 2);
    Ramp ramp3(3, 2);

    ramps.push_back(ramp1);
    ramps.push_back(ramp3);
    ramps.push_back(ramp2);

    Factory factory;

    NodeCollection<Ramp> nodeCollection(ramps);

    nodeCollection.remove_by_id(2);

//    std::cout << nodeCollection.find_by_id(2)->get_id() << std::endl;
//    std::cout << nodeCollection.collection_.end()->get_id() << std::endl;

    for (const auto& elem : nodeCollection.collection_){
        std::cout << elem.get_id() << std::endl;
    }


    factory.add_ramp(std::move(ramp1));
    return 0;
}