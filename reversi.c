
//
// Author: 
// Santiago Piovesanel Lain
// Mar. 29, 2024
//

#include "reversi.h"

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

bool checkAllDirections(char board[][26], int n, int row, int col, char colour, bool direction[8]) {
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

void changeTiles(char board[][26], int n, int row, int col, char colour, bool direction[8]) {
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

int main(void) {
  int n = -1;
  while (n < 0) {
    printf("Enter the board dimension: ");
    scanf("%d", &n);
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

  char configs[3] = {'U', 'U', 'U'};
  printf("Enter board configuration:\n");
  while (configs[0] != '!' && configs[1] != '!' && configs[2] != '!') {
    scanf("%*c", NULL);
    scanf("%c%c%c", &configs[0], &configs[1], &configs[2]);

    if (positionInBounds(n, configs[1] - 'a', configs[2] - 'a')) {
      if (configs[0] == 'B') {
        board[configs[1] - 'a'][configs[2] - 'a'] = 'B';
      } else if (configs[0] == 'W') {
        board[configs[1] - 'a'][configs[2] - 'a'] = 'W';
      }
    }
  }
  printBoard(board, n);

  bool direction[8] = { 0 };
  int possible = 0;
  printf("Available moves for W:\n");
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      if (checkAllDirections(board, n, i, j, 'W', direction)) {
        printf("%c%c\n", 'a' + i, 'a' + j);
        possible++;
      }
    }
  }
  printf("Available moves for B:\n");
  possible = 0;
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      if (checkAllDirections(board, n, i, j, 'B', direction)) {
        printf("%c%c\n", 'a' + i, 'a' + j);
        possible++;
      }
    }
  }

  char move[3] = {'U', 'U', 'U'};
  printf("Enter a move:\n");
  scanf("%*c", NULL);
  scanf("%c%c%c", &move[0], &move[1], &move[2]);

  if (checkAllDirections(board, n, move[1] - 'a', move[2] - 'a', move[0], direction)) {
    printf("Valid move.\n");
    checkAllDirections(board, n, move[1] - 'a', move[2] - 'a', move[0], direction);
    changeTiles(board, n, move[1] - 'a', move[2] - 'a', move[0], direction);
  } else {
    printf("Invalid move.\n");
  }
  
  printBoard(board, n);
  return 0;
}
