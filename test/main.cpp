#include "gtest/gtest.h"
#include "glog/logging.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    google::InitGoogleLogging(argv[0]);
    // Seed our random generator so that the tests are deterministic.
    // TODO: this should be done for every test.
    return RUN_ALL_TESTS();
}
