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

    SECTION("setCenter postavlja tacku centra", "[Obstacle]") {
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


    SECTION("setDiameter postavlja vrednost diameter", "[Obstacle]") {
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

    SECTION("gotHit() smanjuje health za 1", "[Obstacle]") {
        int initialHealth = 5;
        Obstacle obstacle;
        obstacle.setHealth(initialHealth);

        obstacle.gotHit();
        int expectedHealth = initialHealth - 1;
        REQUIRE(obstacle.health() == expectedHealth);

    }

    SECTION("isAlive() vraca status na osnovu health-a", "[Obstacle]") {

        Obstacle obstacle;
        obstacle.setHealth(1);
        REQUIRE(obstacle.isAlive() == true);

        SECTION("isAlive() vraca false","[Obstacle]"){
            Obstacle obstacle;
            obstacle.setHealth(0);
            REQUIRE(obstacle.isAlive() == false);
        }

    }

    SECTION("health() vraca vrednost health", "[Obstacle]") {
        double initialHealth = 10.0;
        Obstacle obstacle;
        obstacle.setHealth(initialHealth);

        double health = obstacle.health();
        REQUIRE(health == Approx(initialHealth).epsilon(0.001));
    }

    SECTION("Obstacle health i max health funkcionalnost", "[Obstacle]") {
        Obstacle obstacle;

        double newHealth = 50.0;
        obstacle.setHealth(newHealth);
        REQUIRE(obstacle.health() == Approx(newHealth).epsilon(0.001));


        double newMaxHealth = 100.0;
        obstacle.setMaxHealth(newMaxHealth);
        REQUIRE(obstacle.maxHealth() == Approx(newMaxHealth).epsilon(0.001));

    }

    SECTION("maxHealth() vraca maxHealth", "[Obstacle]") {
        double initialMaxHealth = 100.0;
        Obstacle obstacle;
        obstacle.setMaxHealth(initialMaxHealth);


        double maxHealth = obstacle.maxHealth();
        REQUIRE(maxHealth == Approx(initialMaxHealth).epsilon(0.001));

    }

    SECTION("generateDiameter() vraca diameter u odredjenom intervalu", "[Obstacle]") {
        Obstacle obstacle;


        double diameter = obstacle.generateDiameter();
        REQUIRE(diameter >= 1.5);
        REQUIRE(diameter <= 1.5 + 10 * 10);

    }
}
