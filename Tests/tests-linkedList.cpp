#include <stdint.h>
#include "catch.hpp"

#include "List.h"

TEST_CASE("Add Item to List", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item1 = 1;
    uint8_t item2 = 2;

    List<uint8_t>::Iterator iter = list.Begin();

    List<uint8_t>::Iterator iter1 = list.Insert(iter, item1);
    List<uint8_t>::Iterator iter2 = list.Insert(iter1, item2);

    REQUIRE(*iter1 == 1);
    REQUIRE(*iter2 == 2);

    REQUIRE(*list.Begin() == 2);

    REQUIRE(list.Length() == 2);
}

TEST_CASE("Add Item to the end of List", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item1 = 1;
    uint8_t item2 = 2;

    List<uint8_t>::Iterator iter = list.End();

    iter = list.Insert(iter, item1);

    iter = list.End();
    iter = list.Insert(iter, item2);

    REQUIRE(*list.Begin() == 1);
    REQUIRE(*(list.Begin()++) == 2);

    REQUIRE(list.Length() == 2);
}

TEST_CASE("Remove Item from List", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item = 1;

    List<uint8_t>::Iterator iter = list.Begin();

    iter = list.Insert(iter, item);
    iter = list.Erase(iter);

    REQUIRE(iter == list.End());

    REQUIRE(list.Length() == 0);
}

TEST_CASE("Iterate items in list", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t items[5] = {1, 2, 3, 4, 5};

    for(uint8_t item : items) {
        List<uint8_t>::Iterator iter = list.End();
        list.Insert(iter, item);
    }

    List<uint8_t>::Iterator iter = list.Begin();

    int i = 0;
    while(iter != list.End()) {
        REQUIRE(*iter == items[i++]);
        iter++;
    }

}