// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nodes.hpp"

TEST(StorehouseTest, ReceiverFIFOTest) {
    PackageQueue queue(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> uniquePtr = std::make_unique<PackageQueue>(queue);

    Storehouse storehouse(1, std::move(uniquePtr));
    Ramp ramp(1, 2);

    ramp.receiver_preferences_.add_receiver(&storehouse);

    ramp.deliver_goods(0);
    ramp.send_package();

    ramp.deliver_goods(1);
    ramp.send_package();

    EXPECT_EQ(1, storehouse.cend()->get_id());
}


TEST(StorehouseTest, ReceiverLIFOTest) {
    PackageQueue queue(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> uniquePtr = std::make_unique<PackageQueue>(queue);

    Storehouse storehouse(1, std::move(uniquePtr));
    Ramp ramp(1, 2);

    ramp.receiver_preferences_.add_receiver(&storehouse);

    ramp.deliver_goods(0);
    ramp.send_package();

    ramp.deliver_goods(1);
    ramp.send_package();

    EXPECT_EQ(1, storehouse.cend()->get_id());
}


TEST(PackageSenderTest, BufferFIFOTest){
    PackageQueue queue(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> uniquePtr = std::make_unique<PackageQueue>(queue);

    Ramp ramp(1, 1);
    Worker worker(1, 1, std::move(uniquePtr));

    ramp.receiver_preferences_.add_receiver(&worker);
    ramp.deliver_goods(0);
    ramp.send_package();

    EXPECT_EQ(std::nullopt, ramp.get_sending_buffer());
}


TEST(PackageSenderTest, BufferLIFOTest){
    PackageQueue queue(PackageQueueType::LIFO);

    std::unique_ptr<IPackageQueue> uniquePtr = std::make_unique<PackageQueue>(queue);
    Ramp ramp(1, 1);
    Worker worker(1, 1, std::move(uniquePtr));

    ramp.receiver_preferences_.add_receiver(&worker);
    ramp.deliver_goods(0);
    ramp.send_package();

    EXPECT_EQ(std::nullopt, ramp.get_sending_buffer());
}

//
//TEST(RampTest, DeliveryFIFOTest){
//    PackageQueue queue(PackageQueueType::FIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr = std::make_unique<PackageQueue>(queue);
//
//    Ramp ramp(2, 2);
//    Worker worker(1, 1, std::move(uniquePtr));
//
//    ramp.receiver_preferences_.add_receiver(&worker);
//
//    ramp.deliver_goods(0);
//    ramp.send_package();
//
//    ramp.deliver_goods(1);
//    ramp.send_package();
//
//    ramp.deliver_goods(2);
//
//    EXPECT_EQ(1, ramp.get_sending_buffer().has_value());
//}
//
//
//TEST(RampTest, DeliveryLIFOTest){
//    PackageQueue queue(PackageQueueType::LIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr = std::make_unique<PackageQueue>(queue);
//
//    Ramp ramp(2, 2);
//    Worker worker(1, 1, std::move(uniquePtr));
//
//    ramp.receiver_preferences_.add_receiver(&worker);
//
//    ramp.deliver_goods(0);
//    ramp.send_package();
//
//    ramp.deliver_goods(1);
//    ramp.send_package();
//
//    ramp.deliver_goods(2);
//
//    EXPECT_EQ(1, ramp.get_sending_buffer().has_value());
//}
//
//TEST(RampTest, NoDeliveryFIFOTest){
//    PackageQueue queue(PackageQueueType::FIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr = std::make_unique<PackageQueue>(queue);
//
//    Ramp ramp(2, 2);
//    Worker worker(1, 1, std::move(uniquePtr));
//
//    ramp.receiver_preferences_.add_receiver(&worker);
//
//    ramp.deliver_goods(0);
//    ramp.send_package();
//    ramp.deliver_goods(1);
//
//    EXPECT_EQ(0, ramp.get_sending_buffer().has_value());
//}
//
//
//TEST(RampTest, NoDeliveryLIFOTest){
//    PackageQueue queue(PackageQueueType::LIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr = std::make_unique<PackageQueue>(queue);
//
//    Ramp ramp(2, 2);
//    Worker worker(1, 1, std::move(uniquePtr));
//
//    ramp.receiver_preferences_.add_receiver(&worker);
//
//    ramp.deliver_goods(0);
//    ramp.send_package();
//    ramp.deliver_goods(1);
//
//    EXPECT_EQ(0, ramp.get_sending_buffer().has_value());
//}

//
//TEST(WorkerTime, CorrectTimeFIFOTest){
//    PackageQueue queue1(PackageQueueType::FIFO);
//    PackageQueue queue2(PackageQueueType::FIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr1 = std::make_unique<PackageQueue>(queue1);
//    std::unique_ptr<IPackageStockpile> uniquePtr2 = std::make_unique<PackageQueue>(queue2);
//
//    Worker worker(1, 2, std::move(uniquePtr1));
//    Ramp ramp(1, 2);
//    Storehouse storehouse(1, std::move(uniquePtr2));
//
//    ramp.receiver_preferences_.add_receiver(&worker);
//    worker.receiver_preferences_.add_receiver(&storehouse);
//
//    ramp.deliver_goods(0);
//    ramp.send_package();
//
//    worker.do_work(0);
//    worker.send_package();
//
//    ramp.deliver_goods(1);
//    ramp.send_package();
//
//    worker.do_work(1);
//    worker.send_package();
//
//    ramp.deliver_goods(2);
//    ramp.send_package();
//
//    worker.do_work(2);
//    worker.send_package();
//
//    EXPECT_EQ(1, storehouse.cbegin()->get_id());
//}

//
//TEST(WorkerTime, CorrectTimeLIFOTest){
//    PackageQueue queue1(PackageQueueType::LIFO);
//    PackageQueue queue2(PackageQueueType::LIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr1 = std::make_unique<PackageQueue>(queue1);
//    std::unique_ptr<IPackageStockpile> uniquePtr2 = std::make_unique<PackageQueue>(queue2);
//
//    Worker worker(1, 2, std::move(uniquePtr1));
//    Ramp ramp(1, 2);
//    Storehouse storehouse(1, std::move(uniquePtr2));
//
//    ramp.receiver_preferences_.add_receiver(&worker);
//    worker.receiver_preferences_.add_receiver(&storehouse);
//
//    ramp.deliver_goods(0);
//    ramp.send_package();
//
//    worker.do_work(0);
//    worker.send_package();
//
//    ramp.deliver_goods(1);
//    ramp.send_package();
//
//    worker.do_work(1);
//    worker.send_package();
//
//    ramp.deliver_goods(2);
//    ramp.send_package();
//
//    worker.do_work(2);
//    worker.send_package();
//
//    EXPECT_EQ(1, storehouse.cbegin()->get_id());
//}


//TEST(ReceiverPreferencesTest, ChooseReceiverTest){
//    PackageQueue queue1(PackageQueueType::FIFO);
//    PackageQueue queue2(PackageQueueType::LIFO);
//
//    std::unique_ptr<IPackageQueue> uniquePtr1 = std::make_unique<PackageQueue>(queue1);
//    std::unique_ptr<IPackageQueue> uniquePtr2 = std::make_unique<PackageQueue>(queue2);
//
//    Worker worker1(1, 1, std::move(uniquePtr1));
//    Worker worker2(2, 2, std::move(uniquePtr2));
//
//    std::function<double(void)> generator = my_generator;
//    ReceiverPreferences receiverPreferences(generator);
//
//    IPackageReceiver* receiver1;
//    IPackageReceiver* receiver2;
//
//    receiver1 = &worker1;
//    receiver2 = &worker2;
//
//    receiverPreferences.add_receiver(&worker1);
//    receiverPreferences.add_receiver(&worker2);
//
//    EXPECT_EQ((receiver1<receiver2) ? receiver1 : receiver2, receiverPreferences.choose_receiver());
//}