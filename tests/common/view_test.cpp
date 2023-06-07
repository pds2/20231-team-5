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
    View view = View(new ScoreboardService(vector<Player*>()), new PlayerService(), "header");
    
    string empty_line = "";
    view.setContent(empty_line);
    CHECK(view.getContent()[0] == "");
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent().size() == 11);

    string one_incomplete_line = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    view.setContent(one_incomplete_line);
    CHECK(view.getContent()[0] == one_incomplete_line);
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent().size() == 11);

    string one_complete_line= "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 76 chars
    view.setContent(one_complete_line);
    CHECK(view.getContent()[0] == one_complete_line);
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent().size() == 11);

    string two_complete_lines = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 152 chars
    view.setContent(two_complete_lines);
    CHECK(view.getContent()[0] == one_complete_line);
    CHECK(view.getContent()[1] == one_complete_line);
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent()[3] == "");
    CHECK(view.getContent().size() == 11);

    string two_complete_lines_and_one_half = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    string one_half_line = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    view.setContent(two_complete_lines_and_one_half);
    CHECK(view.getContent()[0] == one_complete_line);
    CHECK(view.getContent()[1] == one_complete_line);
    CHECK(view.getContent()[2] == one_half_line);
    CHECK(view.getContent()[3] == "");
    CHECK(view.getContent()[4] == "");
    CHECK(view.getContent().size() == 11);

    string full_content_size_string = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 836 chars
    view.setContent(full_content_size_string);
    for (int i=0; i<11; i++){
        CHECK(view.getContent()[i] == one_complete_line);
    }

    string overflow_content_size_string = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaa"; // 840 chars
    view.setContent(overflow_content_size_string);
    for (int i=0; i<10; i++){
        CHECK(view.getContent()[i] == one_complete_line);
    }
    CHECK(view.getContent()[10] == one_complete_line.substr(0, 73) + "...");

}