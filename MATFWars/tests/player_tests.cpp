#include "catch.hpp"
#include "../src/Player.h"
#include <QString>
#include <QPointF>

TEST_CASE("Funkcije u klasi Player", "[Player]") {

    SECTION("name vraca ocekivano ime", "[Player]") {
        QString expectedName = "John Doe";
        Player player(expectedName);

        QString name = player.name();
        REQUIRE(name == expectedName);
    }

    SECTION("setName azurira igracevo ime", "[Player]") {
        Player player;
        QString newName = "Alice Smith";

        player.setName(newName);
        REQUIRE(player.name() == newName);
    }

    SECTION("coordinate vraca ispravne koordinate igraca", "[Player]") {
        QPointF expectedCoordinate(10.0, 20.0);
        Player player;
        player.setCoordinates(expectedCoordinate);

        QPointF coordinate = player.coordinate();
        REQUIRE(coordinate == expectedCoordinate);
    }

    SECTION("setCoordinates azurira koordinate igraca", "[Player]") {
        Player player;
        QPointF newCoordinates(30.0, 40.0);

        player.setCoordinates(newCoordinates);
        REQUIRE(player.coordinate() == newCoordinates);
    }

    SECTION("diameter vraca tacnu vrednost poluprecnika", "[Player]") {
        Player player;
        double initialDiameter = 1.0;

        double diameter = player.diameter();
        REQUIRE(diameter == Approx(initialDiameter).epsilon(0.001));

    }

    SECTION("flipX invertuje x-koordinatu igraca", "[Player]") {
        QPointF initialCoordinate(10, 20);
        Player player;
        player.setCoordinates(initialCoordinate);


        player.flipX();
        QPointF flippedCoordinate = player.coordinate();

        REQUIRE(flippedCoordinate.x() == Approx(-initialCoordinate.x()).epsilon(0.001));
        REQUIRE(flippedCoordinate.y() == Approx(initialCoordinate.y()).epsilon(0.001));

    }

    SECTION("playerID vraca ispravan ID igraca", "[Player]") {
        int initialPlayerID = 42;
        Player player;
        player.setPlayerID(initialPlayerID);

        int playerID = player.playerID();
        REQUIRE(playerID == initialPlayerID);
    }

    SECTION("setPlayerID azurira ID igraca", "[Player]") {
        Player player;
        int newPlayerID = 123;

        player.setPlayerID(newPlayerID);
        REQUIRE(player.playerID() == newPlayerID);
    }
}

