#include "../include/third_party/doctest/doctest.h"
#include "../include/common/services/player_service.h"

TEST_CASE("Test CRUD methods") {
    PlayerService player_service;
    player_service.addPlayer("Alice");
    player_service.addPlayer("Bob");
    player_service.addPlayer("Charlie");

    CHECK(player_service.getPlayers().size() == 3);
    CHECK(player_service.getPlayers()[0]->getName() == "Alice");
    CHECK(player_service.getPlayers()[1]->getName() == "Bob");
    CHECK(player_service.getPlayers()[2]->getName() == "Charlie");

    CHECK(player_service.getPlayer(0).getName() == "Alice");
    CHECK(player_service.getPlayer(1).getName() == "Bob");
    CHECK(player_service.getPlayer(2).getName() == "Charlie");
}

TEST_CASE("Test current player logic"){
    PlayerService player_service;
    player_service.addPlayer("Alice");
    player_service.addPlayer("Bob");
    player_service.addPlayer("Charlie");

    CHECK(player_service.getCurrentPlayer().getName() == "Alice");
    player_service.changeCurrentPlayer();
    CHECK(player_service.getCurrentPlayer().getName() == "Bob");
    player_service.changeCurrentPlayer();
    CHECK(player_service.getCurrentPlayer().getName() == "Charlie");
    player_service.changeCurrentPlayer();
    CHECK(player_service.getCurrentPlayer().getName() == "Alice");
}

TEST_CASE("Test NoPlayersException") {
    PlayerService player_service;

    CHECK_THROWS_AS(player_service.getCurrentPlayer(), NoPlayersException);
    CHECK_THROWS_AS(player_service.getPlayer(0), NoPlayersException);
}

TEST_CASE("Test PlayerOverloadException"){
    PlayerService player_service;
    player_service.addPlayer("Alice");
    player_service.addPlayer("Bob");
    player_service.addPlayer("Charlie");
    player_service.addPlayer("Dave");

    CHECK_THROWS_AS(player_service.addPlayer("Eve"), PlayerOverloadException);
}

TEST_CASE("Test InvalidPlayerException"){
    PlayerService player_service;
    player_service.addPlayer("Alice");
    player_service.addPlayer("Bob");
    player_service.addPlayer("Charlie");

    CHECK_THROWS_AS(player_service.getPlayer(3), InvalidPlayerException);
}

TEST_CASE("Test InvalidNameException"){
    PlayerService player_service;
    player_service.addPlayer("Alice");
    player_service.addPlayer("Bob");
    player_service.addPlayer("Charlie");

    CHECK_THROWS_AS(player_service.addPlayer("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), InvalidNameException);
    CHECK_THROWS_AS(player_service.addPlayer("João"), InvalidNameException);
}