#include "../include/third_party/doctest/doctest.h"
#include "../include/common/view.h"

TEST_CASE("Test constructor"){
    CHECK_NOTHROW(View(new ScoreboardService(vector<Player*>()), new PlayerService(), "header"));
    CHECK_THROWS_AS(View(new ScoreboardService(vector<Player*>()), nullptr, "header"), InvalidArgumentException);
    CHECK_THROWS_AS(View(nullptr, new PlayerService(), "header"), InvalidArgumentException);
    CHECK_THROWS_AS(View(nullptr, nullptr, "header"), InvalidArgumentException);
    
    CHECK_NOTHROW(View(new ScoreboardService(vector<Player*>()), new PlayerService(), ""));
}

TEST_CASE("Test content logic"){
    string content = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    View view = View(new ScoreboardService(vector<Player*>()), new PlayerService(), "header");
    view.setContent(content);
    CHECK(view.getContent()[0] == content);
    CHECK(view.getContent().size() == 11);

    content = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"; // 76 chars
    view.setContent(content);
    CHECK(view.getContent().size() == 11);
}