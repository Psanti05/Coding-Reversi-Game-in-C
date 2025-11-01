//
// Author: 
// Santiago Piovesanel Lain
// Mar. 29, 2024
//

#include "lab8part2.h"
#include "liblab8part2.h"

#include <stdbool.h>
#include <stdio.h>

void printBoard(char board[][26], int n) {
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("%c", 'a' + i);
  }
  printf("\n");

  for (int i = 0; i < n; i++) {
    printf("%c ", 'a' + i);
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col) {
  if (row >= 0 && row < n && col >= 0 && col < n) {
    return true;
  } else {
    return false;
  }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  if (positionInBounds(n, row, col)) {
    if (board[row][col] == 'U') {
      if (board[row + deltaRow][col + deltaCol] != colour &&
          board[row + deltaRow][col + deltaCol] != 'U') {
        for (int i = 2; i < n; i++) {
          if (row + (i * deltaRow) >= 0 && row + (i * deltaRow) < n &&
              col + (i * deltaCol) >= 0 && col + (i * deltaCol) < n &&
              board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
            return true;
          } else if (row + (i * deltaRow) >= 0 && row + (i * deltaRow) < n &&
                     col + (i * deltaCol) >= 0 && col + (i * deltaCol) < n &&
                     board[row + (i * deltaRow)][col + (i * deltaCol)] == 'U') {
            return false;
          }
        }
      }
    }
  }
  return false;
}

bool checkAllDirections(char board[][26], int n, int row, int col, char colour,
                        bool direction[8]) {
  int directions = 0;
  for (int i = 0; i < 8; i++) {
    direction[i] = false;
  }
  if (checkLegalInDirection(board, n, row, col, colour, -1, 0)) {  // N
    direction[0] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, -1, 1)) {  // NE
    direction[1] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 0, 1)) {  // E
    direction[2] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 1, 1)) {  // SE
    direction[3] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 1, 0)) {  // S
    direction[4] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 1, -1)) {  // SW
    direction[5] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, 0, -1)) {  // W
    direction[6] = true;
    directions++;
  }
  if (checkLegalInDirection(board, n, row, col, colour, -1, -1)) {  // NW
    direction[7] = true;
    directions++;
  }
  if (directions > 0) {
    return true;
  } else {
    return false;
  }
}

void changeTiles(char board[][26], int n, int row, int col, char colour,
                 bool direction[8]) {
  board[row][col] = colour;
  int deltaRow = 0, deltaCol = 0;
  if (direction[0] == true) {
    deltaRow = -1, deltaCol = 0;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[1] == true) {
    deltaRow = -1, deltaCol = 1;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[2] == true) {
    deltaRow = 0, deltaCol = 1;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[3] == true) {
    deltaRow = 1, deltaCol = 1;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[4] == true) {
    deltaRow = 1, deltaCol = 0;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[5] == true) {
    deltaRow = 1, deltaCol = -1;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[6] == true) {
    deltaRow = 0, deltaCol = -1;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
  if (direction[7] == true) {
    deltaRow = -1, deltaCol = -1;
    for (int i = 1; i < n; i++) {
      if (board[row + (i * deltaRow)][col + (i * deltaCol)] == colour) {
        break;
      } else {
        board[row + (i * deltaRow)][col + (i * deltaCol)] = colour;
      }
    }
  }
}

int calcBestMove(char board[][26], int n, char colour, bool direction[8], int score[][26]) {
  int row, col;
  int deltaRow = 0, deltaCol = 0;
  int total = 0, number = 0, count = 0, newcount = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (checkAllDirections(board, n, i, j, colour, direction)) {
        row = i;
        col = j;
        checkAllDirections(board, n, row, col, colour, direction);
        if (direction[0] == true) {
          deltaRow = -1, deltaCol = 0;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[1] == true) {
          deltaRow = -1, deltaCol = 1;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[2] == true) {
          deltaRow = 0, deltaCol = 1;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[3] == true) {
          deltaRow = 1, deltaCol = 1;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[4] == true) {
          deltaRow = 1, deltaCol = 0;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[5] == true) {
          deltaRow = 1, deltaCol = -1;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[6] == true) {
          deltaRow = 0, deltaCol = -1;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
        if (direction[7] == true) {
          deltaRow = -1, deltaCol = -1;
          for (int k = 1; k < n; k++) {
            if (board[row + (k * deltaRow)][col + (k * deltaCol)] == colour) {
              break;
            } else {
              score[row][col]++;
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (score[i][j] > 0) {
        total ++;
        newcount = score[i][j];
        if (newcount > count) {
          count = newcount;
          number = total;
        }
      }
    }
  }
  return number;
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {
    
}

int main(void) {
  int n = -1;
  int score[26][26] = {0};
  char colour = 'U';
  while (n < 0) {
    printf("Enter the board dimension: ");
    scanf("%d", &n);
  }
  printf("Computer plays (B/W): ");
  while (!(colour == 'B' || colour == 'W')) {
    scanf(" %c", &colour);
  }

  char board[26][26];
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      board[i][j] = 'U';
    }
  }
  board[n / 2 - 1][n / 2 - 1] = 'W';
  board[n / 2][n / 2] = 'W';
  board[n / 2][n / 2 - 1] = 'B';
  board[n / 2 - 1][n / 2] = 'B';
  printBoard(board, n);

  bool computer = true;  // bool that says if it's computer's turn
  if (colour == 'B') {   // if computer is B, it gets first turn
    computer = true;
  } else {
    computer = false;
  }
  bool running = true;
  int row, col;
  char rowC, colC;
  bool direction[8] = {0};
  int possibleW = 0, possibleB = 0;
  int counter = 0;
  bool playerLoss = false;
  bool action = true;

  while (running == true) {
    if (action == true) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          score[i][j] = 0;
        }
      }
      counter = 0;
      possibleW = 0;
      possibleB = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (checkAllDirections(board, n, i, j, 'W', direction)) {
            possibleW++;
          }
        }
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (checkAllDirections(board, n, i, j, 'B', direction)) {
            possibleB++;
          }
        }
      }
    }

    if (possibleW == 0 && possibleB == 0) {
      running = false;
    } else if (colour == 'B') {  // if computer has black
      if (computer == true) {    // if it is computer's turn
        if (possibleB > 0) {
          counter = calcBestMove(board, n, 'B', direction, score);
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
              if (checkAllDirections(board, n, i, j, 'B', direction)) {
                counter --;
                if (counter == 0) {
                  row = i;
                  col = j;
                }
              }
            }
          }
          checkAllDirections(board, n, row, col, 'B', direction);
          changeTiles(board, n, row, col, 'B', direction);
          printf("Computer places B at %c%c.\n", row + 'a', col + 'a');
          printBoard(board, n);
          computer = false;
          action = true;
        } else {
          printf("B player has no valid move.\n");
          computer = false;
          action = false;
        }
      } else {  // if it is player's turn
        if (possibleW > 0) {
          printf("Enter move for colour W (RowCol): ");
          scanf(" %c%c", &rowC, &colC);
          if (checkAllDirections(board, n, rowC - 'a', colC - 'a', 'W', direction)) {
            checkAllDirections(board, n, rowC - 'a', colC - 'a', 'W', direction);
            changeTiles(board, n, rowC - 'a', colC - 'a', 'W', direction);
            printBoard(board, n);
          } else {
            printf("Invalid move.\n");
            playerLoss = true;
            running = false;
          }
          computer = true;
          action = true;
        } else {
          printf("W player has no valid move.\n");
          computer = true;
          action = false;
        }
      }
    } else {  // if computer has white
      if (computer == true) {    // if it is computer's turn
        if (possibleW > 0) {
          counter = calcBestMove(board, n, 'W', direction, score);
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
              if (checkAllDirections(board, n, i, j, 'W', direction)) {
                counter --;
                if (counter == 0) {
                  row = i;
                  col = j;
                }
              }
            }
          }
          checkAllDirections(board, n, row, col, 'W', direction);
          changeTiles(board, n, row, col, 'W', direction);
          printf("Computer places W at %c%c.\n", row + 'a', col + 'a');
          printBoard(board, n);
          computer = false;
          action = true;
        } else {
          printf("W player has no valid move.\n");
          computer = false;
          action = false;
        }
      } else {  // if it is player's turn
        if (possibleB > 0) {
          printf("Enter move for colour B (RowCol): ");
          scanf(" %c%c", &rowC, &colC);
          if (checkAllDirections(board, n, rowC - 'a', colC - 'a', 'B', direction)) {
            checkAllDirections(board, n, rowC - 'a', colC - 'a', 'B', direction);
            changeTiles(board, n, rowC - 'a', colC - 'a', 'B', direction);
            printBoard(board, n);
          } else {
            printf("Invalid move.\n");
            playerLoss = true;
            running = false;
          }
          computer = true;
          action = true;
        } else {
          printf("B player has no valid move.\n");
          computer = true;
          action = false;
        }
      }
    }
  }
  
  if (playerLoss == true) {
    printf("%c player wins.\n", colour);
  } else {
    int countB = 0;
    int countW = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j] == 'B') {
          countB++;
        }
        if (board[i][j] == 'W') {
          countW++;
        }
      }
    }
    if (countB > countW) {
      printf("B player wins.\n");
    } else if (countW > countB) {
      printf("W player wins.\n");
    } else {
      printf("Draw!\n");
    }
  }
  
  return 0;
}

