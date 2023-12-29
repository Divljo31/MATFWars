#include "catch.hpp"
#include "../src/Obstacle.h"
#include <QPointF>

TEST_CASE("Funkcije u klasi Obstacle", "[Obstacle]") {
    SECTION("konstruktor za Obstacle") {
        Obstacle obj;

        REQUIRE(obj.health() >= 1);
        REQUIRE(obj.health() <= 5);

        REQUIRE(obj.maxHealth() == obj.health());
    }

    SECTION("center() vraca tacku centra", "[Obstacle]") {
        Obstacle obstacle;

        QPointF expectedCenter(50, 50);
        obstacle.setCenter(expectedCenter);
        QPointF center = obstacle.center();
        REQUIRE(center == expectedCenter);
    }

    SECTION("setCenter() postavlja tacku centra", "[Obstacle]") {
        Obstacle obstacle;
        QPointF newCenter(10, 20);


        obstacle.setCenter(newCenter);
        REQUIRE(obstacle.center() == newCenter);
    }

    SECTION("diameter() vraca vrednost diameter", "[Obstacle]") {
        float expectedDiameter = 10.0f;
        Obstacle obstacle;
        obstacle.setDiameter(expectedDiameter);

        float diameter = obstacle.diameter();
        REQUIRE(diameter == Approx(expectedDiameter).epsilon(0.001));

    }


    SECTION("setDiameter() postavlja vrednost diameter", "[Obstacle]") {
        Obstacle obstacle;
        double newDiameter = 15.5;

        obstacle.setDiameter(newDiameter);
        REQUIRE(obstacle.diameter() == Approx(newDiameter).epsilon(0.001));

    }

    SECTION("flipX() invertuje x koordinate", "[Obstacle]") {
        QPointF initialCenter(10, 20);
        Obstacle obstacle;
        obstacle.setCenter(initialCenter);

        obstacle.flipX();
        QPointF flippedCenter = obstacle.center();

        REQUIRE(flippedCenter.x() == Approx(-initialCenter.x()).epsilon(0.001));
        REQUIRE(flippedCenter.y() == Approx(initialCenter.y()).epsilon(0.001));

    }
}
