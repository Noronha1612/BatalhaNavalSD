#include "keyboard.h"

#define SIZE 4

#define EMPTY_WATER_CELL -1
#define WATER_CELL 0
#define LIVING_SHIP_CELL 1
#define DESTROYED_SHIP_CELL 2

typedef struct {
  int x;
  int y;
} Coord;

typedef struct {
  int size;
  int remainingShipCells;
  int cells[SIZE][SIZE];
} Board;

Board boardPlayer1;
Board boardPlayer2;

void initializeBoard(Board* board) {
  board->size = SIZE;
  board->remainingShipCells = 0;
  
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      board->cells[i][j] = 0;
    }
  }
}

Board* getPlayerBoard(int player) {
  return player == 1 ? &boardPlayer1 : &boardPlayer2;
}

char getBoardCellLabel(int cellValue, bool hideLivingShips) {
  switch (cellValue) {
    case EMPTY_WATER_CELL:
      return '-';
    case WATER_CELL:
      return '~';
    case LIVING_SHIP_CELL:
      return hideLivingShips ? '~' : 'N';
    case DESTROYED_SHIP_CELL:
      return '#';
    default:
      return ' ';
  }
}

int getBoardCellValue(Coord coord, Board* playerBoard) {
  return playerBoard->cells[coord.y][coord.x];
}

void displayBoard(Board* board, bool hideLivingShips, Coord selectedCoord) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (i == selectedCoord.y && j == selectedCoord.x) {
        printf("X ");
      } else {
        printf("%c ", getBoardCellLabel(board->cells[i][j], hideLivingShips));
      }
    }

    printf("\n");
  }
}


void renderBoard(Board* board) {
  clearScreen();

  Coord hiddenSelectedCoord;
  hiddenSelectedCoord.x = -1;
  hiddenSelectedCoord.y = -1;

  displayBoard(board, false, hiddenSelectedCoord);
}

void renderBoardWithCoordSelection(Board* board, bool hideLivingShips, Coord selectedCoord) {
  clearScreen();
  displayBoard(board, hideLivingShips, selectedCoord);
}

Coord selectBoardCoord(Board* board, bool hideLivingShips, const char *description) {
  Coord coord;

  coord.x = 0;
  coord.y = 0;

  while (1) {
    renderBoardWithCoordSelection(board, hideLivingShips, coord);
    printf("\n%s\n", description);

    int command = readKeyboardCommand();

    if (command == ENTER_KEY) {
      break;
    }

    if (command == INVALID_KEY) {
      printf("Invalid key pressed\n");
      continue;
    }

    if (command == ARROW_UP && coord.y > 0) {
      coord.y--;
    } else if (command == ARROW_DOWN && coord.y < SIZE - 1) {
      coord.y++;
    } else if (command == ARROW_LEFT && coord.x > 0) {
      coord.x--;
    } else if (command == ARROW_RIGHT && coord.x < SIZE - 1) {
      coord.x++;
    }
  }

  return coord;
}

int checkValidCoord(Coord coord) {
  return coord.x >= 0 && coord.x < SIZE && coord.y >= 0 && coord.y < SIZE;
}