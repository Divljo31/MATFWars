#include "catch.hpp"
#include "../src/Player.h"
#include <QString>
#include <QPointF>

TEST_CASE("Functions in Player class", "[Player]") {

    SECTION("Functions in Player class", "[Player]") {
        QString expectedName = "John Doe";
        Player player(expectedName);

        QString name = player.name();
        REQUIRE(name == expectedName);
    }

    SECTION("setName updates the player's name", "[Player]") {
        Player player;
        QString newName = "Alice Smith";

        player.setName(newName);
        REQUIRE(player.name() == newName);
    }

    SECTION("coordinate returns the correct player coordinates", "[Player]") {
        QPointF expectedCoordinate(10.0, 20.0);
        Player player;
        player.setCoordinates(expectedCoordinate);

        QPointF coordinate = player.coordinate();
        REQUIRE(coordinate == expectedCoordinate);
    }

    SECTION("setCoordinates updates the player's coordinates", "[Player]") {
        Player player;
        QPointF newCoordinates(30.0, 40.0);

        player.setCoordinates(newCoordinates);
        REQUIRE(player.coordinate() == newCoordinates);
    }

    SECTION("player diameter returns the correct diameter value", "[Player]") {
        Player player;
        double initialDiameter = 1.0;

        double diameter = player.diameter();
        REQUIRE(diameter == Approx(initialDiameter).epsilon(0.001));

    }

    SECTION("flipX inverts the x-coordinate of the player", "[Player]") {
        QPointF initialCoordinate(10, 20);
        Player player;
        player.setCoordinates(initialCoordinate);


        player.flipX();
        QPointF flippedCoordinate = player.coordinate();

        REQUIRE(flippedCoordinate.x() == Approx(-initialCoordinate.x()).epsilon(0.001));
        REQUIRE(flippedCoordinate.y() == Approx(initialCoordinate.y()).epsilon(0.001));

    }

    SECTION("playerID returns the correct player ID", "[Player]") {
        int initialPlayerID = 42;
        Player player;
        player.setPlayerID(initialPlayerID);

        int playerID = player.playerID();
        REQUIRE(playerID == initialPlayerID);
    }

    SECTION("setPlayerID updates the player's ID", "[Player]") {
        Player player;
        int newPlayerID = 123;

        player.setPlayerID(newPlayerID);
        REQUIRE(player.playerID() == newPlayerID);
    }
}

