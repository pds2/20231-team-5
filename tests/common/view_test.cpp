#include "../include/third_party/doctest/doctest.h"
#include "../include/common/view.h"

#include <iostream>

using namespace std;

TEST_CASE("Test constructor"){
    CHECK_NOTHROW(View(new PlayerService(), "header"));
    CHECK_THROWS_AS(View(nullptr, "header"), InvalidArgumentException);
    CHECK_NOTHROW(View(new PlayerService(), ""));
}

TEST_CASE("Scoreboard logic"){
    View view = View(new PlayerService(), "header");
    CHECK_NOTHROW(view.setScoreboardService(new ScoreboardService(vector<Player*>())));

    CHECK_THROWS_AS(view.setScoreboardService(nullptr), InvalidArgumentException);
    CHECK_THROWS_AS(view.setScoreboardService(new ScoreboardService(vector<Player*>())), InvalidStateException);
}

TEST_CASE("Test content logic without scoreboard"){
    View view = View(new PlayerService(), "header");
    CHECK(view.getContent().size() == 20);
    
    string empty_line = "";
    view.setContent(empty_line);
    CHECK(view.getContent()[0] == "");
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent().size() == 20);

    string one_incomplete_line = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    view.setContent(one_incomplete_line);
    CHECK(view.getContent()[0] == one_incomplete_line);
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent().size() == 20);

    string one_complete_line= "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 76 chars
    view.setContent(one_complete_line);
    CHECK(view.getContent()[0] == one_complete_line);
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent().size() == 20);

    string two_complete_lines = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 152 chars
    view.setContent(two_complete_lines);
    CHECK(view.getContent()[0] == one_complete_line);
    CHECK(view.getContent()[1] == one_complete_line);
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent()[3] == "");
    CHECK(view.getContent().size() == 20);

    string two_complete_lines_and_one_half = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    string one_half_line = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    view.setContent(two_complete_lines_and_one_half);
    CHECK(view.getContent()[0] == one_complete_line);
    CHECK(view.getContent()[1] == one_complete_line);
    CHECK(view.getContent()[2] == one_half_line);
    CHECK(view.getContent()[3] == "");
    CHECK(view.getContent()[4] == "");
    CHECK(view.getContent().size() == 20);

    string full_content_size_string = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 836 chars
    view.setContent(full_content_size_string);
    for (int i=0; i<11; i++){
        CHECK(view.getContent()[i] == one_complete_line);
    }

    string overflow_content_size_string = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 1524 chars
    view.setContent(overflow_content_size_string);
    for (int i=0; i<19; i++){
        CHECK(view.getContent()[i] == one_complete_line);
    }
    CHECK(view.getContent()[19] == one_complete_line.substr(0, 73) + "...");
}

TEST_CASE("Test content logic with scoreboard"){
    View view = View(new PlayerService(), "header");
    CHECK(view.getContent().size() == 20);

    ScoreboardService scoreboardService = ScoreboardService(vector<Player*>());
    view.setScoreboardService(&scoreboardService);

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

    string overflow_content_size_string = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 840 chars
    view.setContent(overflow_content_size_string);
    for (int i=0; i<10; i++){
        CHECK(view.getContent()[i] == one_complete_line);
    }
    CHECK(view.getContent()[10] == one_complete_line.substr(0, 73) + "...");
}

TEST_CASE("Test setContent(vector<string> content)"){
    View view = View(new PlayerService(), "header");

    vector<string> content = vector<string>();
    string line_content = "aaaaaaaaaaaaaaaaaaaaaaaaa";
    content.push_back(line_content);
    content.push_back("");
    content.push_back(line_content);
    
    view.setContent(content);
    CHECK(view.getContent()[0] == line_content);
    CHECK(view.getContent()[1] == "");
    CHECK(view.getContent()[2] == line_content);
    for(int i=3; i<20; i++){
        CHECK(view.getContent()[i] == "");
    }

    content = vector<string>();
    string overflow_line_content = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; // 80 chars
    content.push_back(overflow_line_content);
    content.push_back("");
    content.push_back(line_content);
    content.push_back(overflow_line_content);

    view.setContent(content);
    CHECK(view.getContent()[0] == overflow_line_content.substr(0, 76));
    CHECK(view.getContent()[1] == "bbbb");
    CHECK(view.getContent()[2] == "");
    CHECK(view.getContent()[3] == line_content);
    CHECK(view.getContent()[4] == overflow_line_content.substr(0, 76));
    CHECK(view.getContent()[5] == "bbbb");
    for(int i=6; i<20; i++){
        CHECK(view.getContent()[i] == "");
    }
}