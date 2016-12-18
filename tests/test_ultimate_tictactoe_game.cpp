#include <gtest/gtest.h>
#include <vector>

#include "../UltimateTicTacToeGame.h"
#include "../position.h"

namespace {

TEST(UltimateTicTacToeGameTest, GetPossibleActionsWithEmptyBoard) {
  UltimateTicTacToeGame game;
  auto board = std::vector<int>{
          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,

          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,

          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,
          0,0,0 ,0,0,0, 0,0,0 };

  auto macroboard = std::vector<int>{
          -1, -1, -1,
          -1, -1, -1,
          -1, -1, -1
  };
  game.setBoard(board);
  game.setMacroboard(macroboard);
  std::vector<pos> true_free_cells;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      true_free_cells.push_back(pos(i, j));
    }
  }

  std::vector<pos> game_free_cells = game.GetPossibleActions();

  ASSERT_EQ(true_free_cells.size(), game_free_cells.size());
  for (size_t i = 0; i < true_free_cells.size(); ++i) {
    ASSERT_EQ(true_free_cells[i].r, game_free_cells[i].r);
    ASSERT_EQ(true_free_cells[i].c, game_free_cells[i].c);
  }
}

TEST(UltimateTicTacToeGameTest, GetPossibleActionsWithRandomBoard) {
  UltimateTicTacToeGame game;
  auto board = std::vector<int>{
          1,2,2, 1,2,2, 1,1,1,
          2,2,0, 2,1,2, 0,0,0,
          2,0,2, 0,2,2, 0,0,0,

          1,1,1, 1,1,2, 1,1,1,
          2,0,0, 2,1,2, 0,0,2,
          0,0,0, 0,2,0, 0,0,0,

          1,0,0, 1,1,0, 1,1,2,
          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,
  };

  auto macroboard = std::vector<int>{
          2, 2, 1,
          1, -1, 1,
          0, 0, 0
  };
  game.setBoard(board);
  game.setMacroboard(macroboard);
  std::vector<pos> true_free_cells = {
          pos(5, 3), pos(5, 5),
  };

  std::vector<pos> game_free_cells = game.GetPossibleActions();

  ASSERT_EQ(true_free_cells.size(), game_free_cells.size());
  for (size_t i = 0; i < true_free_cells.size(); ++i) {
    ASSERT_EQ(true_free_cells[i].r, game_free_cells[i].r);
    ASSERT_EQ(true_free_cells[i].c, game_free_cells[i].c);
  }
}

TEST(UltimateTicTacToeGameTest, GetPossibleActionsWithRandomBoard2) {
  UltimateTicTacToeGame game;
  auto board = std::vector<int>{
          1,2,0, 1,0,0, 0,0,0,
          2,0,2, 0,0,0, 0,0,0,
          2,0,0, 0,0,0, 0,0,0,

          0,0,0, 0,0,0, 1,0,0,
          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,

          1,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,
          0,0,0, 0,0,0, 0,0,0,
  };

  auto macroboard = std::vector<int>{
          0, 0, 0,
          -1, 0, 0,
          0, 0, 0,
  };
  game.setBoard(board);
  game.setMacroboard(macroboard);
  std::vector<pos> true_free_cells;
  for (int r = 3; r < 6; ++r) {
    for (int c = 0; c < 3; ++c) {
      true_free_cells.push_back(pos(r, c));
    }
  }

  std::vector<pos> game_free_cells = game.GetPossibleActions();

  ASSERT_EQ(true_free_cells.size(), game_free_cells.size());
  for (size_t i = 0; i < true_free_cells.size(); ++i) {
    ASSERT_EQ(true_free_cells[i].r, game_free_cells[i].r);
    ASSERT_EQ(true_free_cells[i].c, game_free_cells[i].c);
  }
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
