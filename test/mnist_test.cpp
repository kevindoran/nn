#include "mnist/mnist_reader.hpp"
#include "gtest/gtest.h"
#include <cstdint>

/**
 * Tests that we can load the MNIST data.
 *
 * Tests that:
 *   * the MNIST library creates a data vector of the expected size.
 *
 * The test doesn't actually inspect the data for validity.
 */
TEST(mnist, read) {
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset =
            mnist::read_dataset<>(MNIST_DATA_LOCATION);

    size_t expected_training_set_count = 60000;
    ASSERT_EQ(expected_training_set_count, dataset.training_images.size());
    ASSERT_EQ(expected_training_set_count, dataset.training_labels.size());
    size_t expected_test_set_count = 10000;
    ASSERT_EQ(expected_test_set_count, dataset.test_images.size());
    ASSERT_EQ(expected_test_set_count, dataset.test_labels.size());
}
