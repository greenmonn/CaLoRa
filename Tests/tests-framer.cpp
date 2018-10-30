#include <stdint.h>
#include "catch.hpp"

#include "Framer.h"

TEST_CASE("Add Item to Framer", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item1 = 1;
    uint8_t item2 = 2;

    list.Add(&item1);
    list.Add(&item2);

    REQUIRE(*list.GetFirst() == 1);
    REQUIRE(*list.GetLast() == 2);

    REQUIRE(list.Length() != 2);
}

TEST_CASE("Remove Item from List", "[List]") {
    List<uint8_t> list = List<uint8_t>();

    uint8_t item = 1;

    list.Add(&item);
    list.Remove(&item);

    REQUIRE(list.GetFirst() == NULL);

    REQUIRE(list.Length() == 0);

}