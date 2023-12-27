#include "catch.hpp"
#include "../Function.h"

TEST_CASE("Function Construction", "[Function]") {
    SECTION("Default Construction") {
        Function f("x^2");
        REQUIRE(f.points().size() == 1000);
        REQUIRE(f.points().first().x() == -15);
        REQUIRE(f.points().last().x() == 15);
    }
    SECTION("Parameterized Construction") {
        Function f("x^2", -10, 10, 500);
        REQUIRE(f.points().size() == 500);
        REQUIRE(f.points().first().x() == -10);
        REQUIRE(f.points().last().x() == 10);
    }
}

TEST_CASE("Function Points", "[Function]") {
    Function f("x^2");
    auto points = f.points();
    REQUIRE_FALSE(points.isEmpty());
    REQUIRE(points.size() == 1000);
}

TEST_CASE("Function Translation", "[Function]") {
    Function f("x^2");
    QPointF originalFirstPoint = f.points().first();

    SECTION("Player View Translation") {
        f.translatePointsPlayerView(5, 5);
        auto translatedFirstPoint = f.points().first();
        REQUIRE(translatedFirstPoint.x() == originalFirstPoint.x() + 5);
        // Additional checks for y-coordinate
    }
    SECTION("Observer View Translation") {
        f.translatePointsObserverView(5, 5);
        auto translatedFirstPoint = f.points().first();
        REQUIRE(translatedFirstPoint.x() == originalFirstPoint.x() + 5);
        // Additional checks for y-coordinate
    }
}

TEST_CASE("Function Scaling", "[Function]") {
    Function f("x^2");
    f.scaleToCanvas(800, 600, 50);
    for (const auto &point : f.points()) {
        REQUIRE(point.x() >= 0);
        REQUIRE(point.x() <= 800);
        REQUIRE(point.y() >= -600);
        REQUIRE(point.y() <= 600);
    }
}

TEST_CASE("Function Equality", "[Function]") {
    Function f1("x^2");
    Function f2("x^2");
    Function f3("x^3");
    REQUIRE(f1.equals(&f2));
    REQUIRE_FALSE(f1.equals(&f3));
}

TEST_CASE("Remove Points After Cutoff", "[Function]") {
    Function f("x^2");
    f.removePointsAfterCutoff(500);
    REQUIRE(f.points().size() == 500);
    // Additional checks to ensure correct points are present
}
