#include "catch.hpp"
#include "../src/Player.h"
#include <QString>
#include <QPointF>

TEST_CASE("Functions in Player class", "[Player]") {

    SECTION("Functions in Player class", "[Player]") {
        QString expectedName = "John Doe";
        Player player(expectedName); // Assume a constructor that sets the player's name

        QString name = player.name();
        REQUIRE(name == expectedName);
    }

    SECTION("setName updates the player's name", "[Player]") {
        Player player;
        QString newName = "Alice Smith";

        player.setName(newName);
        REQUIRE(player.name() == newName); // Assuming that name() is a getter for m_name
    }

    SECTION("coordinate returns the correct player coordinates", "[Player]") {
        QPointF expectedCoordinate(10.0, 20.0);
        Player player;
        player.setCoordinates(expectedCoordinate); // Set the initial coordinate

        QPointF coordinate = player.coordinate();
        REQUIRE(coordinate == expectedCoordinate);
    }

    SECTION("setCoordinates updates the player's coordinates", "[Player]") {
        Player player;
        QPointF newCoordinates(30.0, 40.0);

        player.setCoordinates(newCoordinates);
        REQUIRE(player.coordinate() == newCoordinates); // Assuming that coordinate() is a getter for m_coordinate
    }
}

