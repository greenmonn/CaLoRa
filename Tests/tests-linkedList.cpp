#include <stdint.h>
#include "catch.hpp"

#include "List.h"

TEST_CASE("Add Item to List", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item1 = 1;
    uint8_t item2 = 2;

    list.Add(&item1);
    list.Add(&item2);

    REQUIRE(*list.GetFirst() == 1);
    REQUIRE(*list.GetLast() == 2);

    REQUIRE(list.GetFirst() != &item1);

    REQUIRE(list.Length() == 2);
}

TEST_CASE("Remove Item from List", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item = 1;

    list.Add(&item);
    list.Remove(&item);

    REQUIRE(list.GetFirst() == NULL);

    REQUIRE(list.Length() == 0);

}

TEST_CASE("Iterate from beginning to end", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t items[5] = {1, 2, 3, 4, 5};

    for (uint8_t item : items) {
        list.Add(&item);
    }

    List<uint8_t>::iterator iter = list.Begin();

    int i = 0;
    while (iter != list.End()) {
        REQUIRE(*iter.Data() == items[i++]);

        iter++;
    }

    REQUIRE(i == 5);
}