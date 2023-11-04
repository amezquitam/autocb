#include "catch.hpp"
#include "trigonometric.hpp"

TEST_CASE("trigonometric functions") {
    SECTION("simpler cases") {
        REQUIRE(is_trigonometric("sen(id)"));
        REQUIRE(is_trigonometric("cos(id)"));
        REQUIRE(is_trigonometric("tan(id)"));
    }

    SECTION("addition cases") {
        REQUIRE(is_trigonometric("sen(id) + tan(id)"));
        REQUIRE(is_trigonometric("cos(id) + sen(id)"));
        REQUIRE(is_trigonometric("tan(id) + cos(id)"));
    }

    SECTION("substraction cases") {
        REQUIRE(is_trigonometric("sen(id) - tan(id)"));
        REQUIRE(is_trigonometric("cos(id) - sen(id)"));
        REQUIRE(is_trigonometric("tan(id) - cos(id)"));
    }
    
    SECTION("product cases") {
        REQUIRE(is_trigonometric("sen(id) * tan(id)"));
        REQUIRE(is_trigonometric("cos(id) * sen(id)"));
        REQUIRE(is_trigonometric("tan(id) * cos(id)"));
    }
    
    SECTION("divition cases") {
        REQUIRE(is_trigonometric("sen(id) / tan(id)"));
        REQUIRE(is_trigonometric("cos(id) / sen(id)"));
        REQUIRE(is_trigonometric("tan(id) / cos(id)"));
    }

    SECTION("power cases") {
        REQUIRE(is_trigonometric("sen(id) ^ tan(id)"));
        REQUIRE(is_trigonometric("cos(id) ^ sen(id)"));
        REQUIRE(is_trigonometric("tan(id) ^ cos(id)"));
    }

    SECTION("parenthesis cases") {
        REQUIRE(is_trigonometric("sen(id) ^ tan(id)"));
        REQUIRE(is_trigonometric("cos(id) ^ sen(id)"));
        REQUIRE(is_trigonometric("tan(id) ^ cos(id)"));
    }
}