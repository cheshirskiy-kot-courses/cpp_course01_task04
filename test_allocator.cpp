#define BOOST_TEST_MODULE allocator_test_module

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(allocator_test_suite)

using namespace std;

auto emplace_element(std::map<int, hard> & m, int k, int fa, int fi)
{
    m.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(k),
        std::forward_as_tuple(fa, fi));
}

auto generate_m()
{
    std::map<int, hard> m;

    emplace_element(m, 0, 1, 0);
    emplace_element(m, 1, 1, 1);
    emplace_element(m, 2, 2, 1);
    emplace_element(m, 3, 6, 2);
    emplace_element(m, 4, 24, 3);
    emplace_element(m, 5, 120, 5);
    emplace_element(m, 6, 720, 8);
    emplace_element(m, 7, 5040, 13);
    emplace_element(m, 8, 40320, 21);
    emplace_element(m, 9, 362880, 34);

    return m;
}

BOOST_AUTO_TEST_CASE(test_def_alloc)
{
    auto out = create_map_0();
    auto test_out = generate_m();

    BOOST_CHECK(rs::equal(out, test_out));
}

BOOST_AUTO_TEST_CASE(test_custom_alloc)
{
    auto out = create_map_1();
    auto test_out = generate_m();

    BOOST_CHECK(rs::equal(out, test_out));
}

//BOOST_AUTO_TEST_CASE(test_custom_container_def_alloc)
//{
//    auto out = create_container_0();
//    auto gen_map = generate_m();
//
//    auto rng = rv::zip(out, gen_map | rv::values);
//
//    auto res = true;
//    for (auto && [first, second] : rng) {
//        res &= (first == second);
//    }
//
//    BOOST_CHECK(res);
//}
//
//BOOST_AUTO_TEST_CASE(test_custom_container_custom_alloc)
//{
//    auto out = create_container_1();
//    auto gen_map = generate_m();
//
//    auto rng = rv::zip(out, gen_map | rv::values);
//
//    auto res = true;
//    for (auto && [first, second] : rng) {
//        res &= (first == second);
//    }
//
//    BOOST_CHECK(res);
//}

BOOST_AUTO_TEST_SUITE_END()