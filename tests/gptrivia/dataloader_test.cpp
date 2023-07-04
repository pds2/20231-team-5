#include "../../include/gptrivia/database/dataloader.h"
#include "../../include/third_party/doctest/doctest.h"

TEST_CASE("Test constructor"){
  CHECK_NOTHROW(DataLoader("triviacards.txt"));
  CHECK_THROWS_AS(DataLoader(""),FileDoesNotOpen);
}