#include "catch.hpp"
#include "trigonometric.hpp"

TEST_CASE("trigonometric functions") {
    SECTION("simpler cases") {
        REQUIRE(is_trigonometric("sen(5)"));
        REQUIRE(is_trigonometric("cos(12)"));
        REQUIRE(is_trigonometric("tan(35.2)"));
    }

    SECTION("addition cases") {
        REQUIRE(is_trigonometric("sen(3.1416) + tan(25.1524)"));
        REQUIRE(is_trigonometric("cos(84.1) + sen(95.1215)"));
        REQUIRE(is_trigonometric("tan(0) + cos(8)"));
    }

    SECTION("substraction cases") {
        REQUIRE(is_trigonometric("sen(8) - tan(57)"));
        REQUIRE(is_trigonometric("cos(2.1) - sen(48.1)"));
        REQUIRE(is_trigonometric("tan(5.7) - cos(84.2)"));
    }
    
    SECTION("product cases") {
        REQUIRE(is_trigonometric("sen(0) * tan(0)"));
        REQUIRE(is_trigonometric("cos(0) * sen(0)"));
        REQUIRE(is_trigonometric("tan(0) * cos(0)"));
    }
    
    SECTION("divition cases") {
        REQUIRE(is_trigonometric("sen(1.10) / tan(25)"));
        REQUIRE(is_trigonometric("cos(1.10) / sen(85)"));
        REQUIRE(is_trigonometric("tan(1.10) / cos(98)"));
    }

    SECTION("power cases") {
        REQUIRE(is_trigonometric("sen(1.1) ^ tan(1)"));
        REQUIRE(is_trigonometric("cos(1.1) ^ sen(1)"));
        REQUIRE(is_trigonometric("tan(1.1) ^ cos(1)"));
    }

    SECTION("parenthesis cases") {
        REQUIRE(is_trigonometric("sen(1) ^ tan(1)"));
        REQUIRE(is_trigonometric("cos(1) ^ sen(1)"));
        REQUIRE(is_trigonometric("tan(1) ^ cos(1)"));
    }
}