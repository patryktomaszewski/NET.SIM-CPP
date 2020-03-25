// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "gtest/gtest.h"

#include "storage_types.hpp"


TEST(PackageQueueInitIsEmptyLIFOTest, IsEmptyTest) {
    PackageQueue packageQueue(PackageQueueType::LIFO);

    EXPECT_EQ(true, packageQueue.empty());
}


TEST(PackageQueueInitIsEmptyFIFOTest, IsEmptyTest) {
    PackageQueue packageQueue(PackageQueueType::FIFO);

    EXPECT_EQ(true, packageQueue.empty());
}

TEST(PackageQueueInitSizeLIFOTest, SizeTest) {
    PackageQueue packageQueue(PackageQueueType::LIFO);

    EXPECT_EQ(0, packageQueue.size());
}


TEST(PackageQueueInitSizeFIFOTest, SizeTest) {
    PackageQueue packageQueue(PackageQueueType::FIFO);

    EXPECT_EQ(0, packageQueue.size());
}


TEST(PackageQueueLIFOGetQueueTypeTest, GetQueueTest) {
    PackageQueue packageQueue(PackageQueueType::LIFO);

    EXPECT_EQ(PackageQueueType::LIFO, packageQueue.get_queue_type());
}


TEST(PackageQueueFIFOGetQueueTypeTest, GetQueueTest) {
    PackageQueue packageQueue(PackageQueueType::FIFO);

    EXPECT_EQ(PackageQueueType::FIFO, packageQueue.get_queue_type());
}


TEST(PackageQueuePushSizeTest, PackagePushSizeTest) {
    Package pack;

    PackageQueue packageQueue(PackageQueueType::LIFO);
    packageQueue.push(static_cast<Package &&>(pack));

    EXPECT_EQ(1, packageQueue.size());
}


TEST(PackageQueuePushIsEmptyTest, PackageQueuePushIsEmptyTest) {
    Package pack;

    PackageQueue packageQueue(PackageQueueType::LIFO);
    packageQueue.push(static_cast<Package &&>(pack));

    EXPECT_EQ(false, packageQueue.empty());
}


TEST(PackageQueuePopLIFOTest, PackageQueuePopTest) {
     Package pack1;
     Package pack2;

     PackageQueue packageQueue(PackageQueueType::LIFO);
     packageQueue.push(static_cast<Package &&>(pack1));
     packageQueue.push(static_cast<Package &&>(pack2));

     packageQueue.pop();

     EXPECT_EQ(1, packageQueue.size());
}


TEST(PackageQueuePopFIFOTest, PackageQueuePopTest) {
    Package pack1;
    Package pack2;

    PackageQueue packageQueue(PackageQueueType::FIFO);
    packageQueue.push(static_cast<Package &&>(pack1));
    packageQueue.push(static_cast<Package &&>(pack2));

    packageQueue.pop();

    EXPECT_EQ(1, packageQueue.size());
}

TEST(PackageQueuePopFIFOTest_id,PackageQueuePopTest){
    Package pack1;
    Package pack2;

    PackageQueue packageQueue(PackageQueueType::FIFO);
    packageQueue.push(static_cast<Package &&>(pack1));
    packageQueue.push(static_cast<Package &&>(pack2));

    EXPECT_EQ(1, (packageQueue.pop()).get_id());
}

TEST(PackageQueuePopLIFOTest_id,PackageQueuePopTest){
    Package pack1;
    Package pack2;
    Package pack3;

    PackageQueue packageQueue(PackageQueueType::LIFO);
    packageQueue.push(static_cast<Package &&>(pack1));
    packageQueue.push(static_cast<Package &&>(pack2));
    packageQueue.push(static_cast<Package &&>(pack3));

    EXPECT_EQ(3, (packageQueue.pop()).get_id());
}