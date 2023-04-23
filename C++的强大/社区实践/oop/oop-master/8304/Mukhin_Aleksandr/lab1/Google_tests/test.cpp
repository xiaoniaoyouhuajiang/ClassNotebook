#include "gtest/gtest.h"
#include "Boardfield.h"


TEST(sample_test, check_constructor) {
    Boardfield a(5, 4);
    Boardfield second(0, 0);
    EXPECT_EQ(true, a.is_free_space());
    EXPECT_EQ(false, second.is_free_space());
}


TEST(sample_test, check_array_container) {
    for (int max_size = 1; max_size < 10; max_size++) {
        Array<int> arr_instance(max_size);
        EXPECT_EQ(arr_instance.size(), arr_instance.size());

        for (size_t i = 0; i < arr_instance.size(); i++) {
            arr_instance[i] = i;
        }

        for (size_t i = 0; i < arr_instance.size(); i++) {
            EXPECT_EQ(arr_instance[i], i);
        }

        EXPECT_THROW(arr_instance[15 + max_size], std::out_of_range);
    }
}


TEST(sample_test, add_unit_random) {
    Boardfield a(5, 3);
    bool result = a.add_unit_random(3);
    EXPECT_EQ(result, true);
}


TEST(sample_test, constructor) {
    std::cout << std::endl;
    Boardfield a(5, 4);
    a.get_board();
    std::cout << std::endl;
}

TEST(sample_test, is_free_space) {
    Boardfield a(1, 2);
    Boardfield b(0, 0);
    EXPECT_EQ(a.is_free_space(), true);
    EXPECT_EQ(b.is_free_space(), false);
}

TEST(sample_test, add_unit) {
    Boardfield a(3, 5);
    bool result = a.add_unit_random(2);
    EXPECT_EQ(result, true);

    result = a.add_unit_at(1, 2, 4);
    EXPECT_EQ(result, true);

    result = a.add_unit_at(1, 2, 4);
    EXPECT_EQ(result, false);

    result = a.delete_unit(0, 0);
    EXPECT_EQ(result, true);
}


TEST(sample_test, move) {
    Boardfield a(7, 5);
    bool result = a.add_unit_at(4, 3, 4);
    EXPECT_EQ(result, true);

    result = a.add_unit_at(2, 6, 2);
    EXPECT_EQ(result, true);

    result = a.move(6, 2, 1, 4);
    EXPECT_EQ(result, true);
}