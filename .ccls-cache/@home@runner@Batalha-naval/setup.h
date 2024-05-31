#include <stdio.h> 

#define SIZE 8

void buildBoard(int board[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      board[i][j] = 0;
    }
  }
}

void displayBoard(int board[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%d ", board[i][j]);
    }

    printf("\n");
  }
}