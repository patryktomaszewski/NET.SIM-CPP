// =====================================//
// NET_SLIM - NET SIMULATION            //
// AUTHOR: DOMINIK WOŹNIAK              //
//         PATRYK TOMASZEWSKI           //
// DATE: 11.12.2019 - XX.XX.XXXX        //
// =====================================//

#include "gtest/gtest.h"

#include "package.hpp"

TEST(PackageInitTest, firstPackageID) {
    Package pack1;

    EXPECT_EQ(1, pack1.get_id());
}

TEST(PackageAssignTest, secondPackageID) {
    Package pack1;
    Package pack2;

    EXPECT_EQ(2, pack2.get_id());
}


TEST(PackageCopyTest, changePackageID) {
    Package pack1;
    Package pack2(static_cast<Package&&>(pack1));

    EXPECT_EQ(1, pack2.get_id());
}

TEST(PackageOperatorTest, changingPackageID) {
    Package pack1;
    Package pack2;

    pack2.operator=(static_cast<Package&&>(pack1));

    EXPECT_EQ(1, pack2.get_id());
}

TEST(PackageidTest, changePackageID){
    Package pack1;
    Package pack2;

    EXPECT_TRUE(pack1.get_id() != pack2.get_id());
}
