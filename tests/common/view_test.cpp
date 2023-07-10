#include "../include/third_party/doctest/doctest.h"
#include "../include/common/view.h"

#include <iostream>

using namespace std;

TEST_CASE("Scoreboard logic"){
    View view = View();
    CHECK_NOTHROW(view.setPlayerService(new PlayerService()));
    CHECK_NOTHROW(view.setScoreboardService(new ScoreboardService(vector<Player*>())));

    CHECK_THROWS_AS(view.setScoreboardService(nullptr), InvalidArgumentException);
    CHECK_THROWS_AS(view.setScoreboardService(new ScoreboardService(vector<Player*>())), InvalidStateException);
}