#define BOOST_TEST_MODULE testboost

#include <utility>
#include "my_allocator.h"
#include "list.h"
#include "lib.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(testboost)

BOOST_AUTO_TEST_CASE(test_allocator)
{
    auto p1 = std::make_pair(0, 1);
    BOOST_CHECK(fact(p1.first) == p1.second);

    auto p2 = std::make_pair(0, 120);
    BOOST_CHECK(fact(p2.first) == p2.second);

    auto p3 = std::make_pair(10, 362800);
    BOOST_CHECK(fact(p3.first) == p3.second);

    containerList<int, myAlloc<int, 10> > testCont;
    for(int i = 0; i < 10; ++i)
        testCont.pushFront(i);
 
}

BOOST_AUTO_TEST_SUITE_END()
