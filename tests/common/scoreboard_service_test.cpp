#include "../include/third_party/doctest/doctest.h"
#include "../include/common/services/scoreboard_service.h"

#include <vector>

using namespace std;

vector<Player*> getTestPlayers(){
    vector<Player*> players = vector<Player*>();
    players.push_back(new Player(0, "Alice"));
    players.push_back(new Player(1, "Bob"));
    players.push_back(new Player(2, "Charlie"));
    return players;
}

void destroyTestPlayers(vector<Player*> players){
    for (Player* player : players) {
        delete player;
    }
}

TEST_CASE("Test changeScore") {
    vector<Player*> test_players = getTestPlayers();
    ScoreboardService scoreboard_service = ScoreboardService(test_players);

    CHECK(scoreboard_service.getScore(0) == 0);
    CHECK(scoreboard_service.getScore(1) == 0);
    CHECK(scoreboard_service.getScore(2) == 0);

    scoreboard_service.changeScore(0, 10);
    scoreboard_service.changeScore(1, 30);
    scoreboard_service.changeScore(2, 20);

    CHECK(scoreboard_service.getScore(0) == 10);
    CHECK(scoreboard_service.getScore(1) == 30);
    CHECK(scoreboard_service.getScore(2) == 20);

    scoreboard_service.changeScore(0, -10);
    scoreboard_service.changeScore(1, -20);
    scoreboard_service.changeScore(2, -15);

    CHECK(scoreboard_service.getScore(0) == 0);
    CHECK(scoreboard_service.getScore(1) == 10);
    CHECK(scoreboard_service.getScore(2) == 5);

    destroyTestPlayers(test_players);
}

TEST_CASE("Test getRanking"){
    vector<Player*> test_players = getTestPlayers();
    ScoreboardService scoreboard_service = ScoreboardService(test_players);

    CHECK(scoreboard_service.getRanking().size() == 3);
    CHECK(scoreboard_service.getRanking()[0] == 0);
    CHECK(scoreboard_service.getRanking()[1] == 1);
    CHECK(scoreboard_service.getRanking()[2] == 2);

    scoreboard_service.changeScore(0, 8.989);
    scoreboard_service.changeScore(1, 41.9595);
    scoreboard_service.changeScore(2, 36);

    CHECK(scoreboard_service.getRanking().size() == 3);
    CHECK(scoreboard_service.getRanking()[0] == 1);
    CHECK(scoreboard_service.getRanking()[1] == 2);
    CHECK(scoreboard_service.getRanking()[2] == 0);

    scoreboard_service.changeScore(0, 10);
    scoreboard_service.changeScore(1, 30);
    scoreboard_service.changeScore(2, 20);

    CHECK(scoreboard_service.getRanking().size() == 3);
    CHECK(scoreboard_service.getRanking()[0] == 1);
    CHECK(scoreboard_service.getRanking()[1] == 2);

    scoreboard_service.changeScore(0, -11.5648);
    scoreboard_service.changeScore(1, -18);
    scoreboard_service.changeScore(2, -11.9987);

    CHECK(scoreboard_service.getRanking().size() == 3);
    CHECK(scoreboard_service.getRanking()[0] == 2);
    CHECK(scoreboard_service.getRanking()[1] == 1);
    CHECK(scoreboard_service.getRanking()[2] == 0);

    destroyTestPlayers(test_players);
}