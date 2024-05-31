#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Coord getNextShipCoordByOrientation(Board* board, Coord initialCoord) {
  printf("Selecione a orientação do seu navio. (Use as setas do teclado)\n");
  
  while(1) {
    int shipOrientation = readKeyboardCommand();

    int canShipBeOrientedAsChosen;
    Coord newCoord;
    newCoord.x = initialCoord.x;
    newCoord.y = initialCoord.y;

    switch (shipOrientation) {
      case ARROW_UP:
        newCoord.y += -1;
        canShipBeOrientedAsChosen = checkValidCoord(newCoord);
        break;
      case ARROW_DOWN:
        newCoord.y += 1;
        canShipBeOrientedAsChosen = checkValidCoord(newCoord);
        break;
      case ARROW_LEFT:
        newCoord.x += -1;
        canShipBeOrientedAsChosen = checkValidCoord(newCoord);
        break;
      case ARROW_RIGHT:
        newCoord.x += 1;
        canShipBeOrientedAsChosen = checkValidCoord(newCoord);
        break;
      default:
        printf("Orientação inválida\n");
        continue;
    }

    if (!canShipBeOrientedAsChosen) {
      printf("Não é possível orientar o navio nessa direção.\n");
      continue;
    }

    return newCoord;
  }
}

void placeShipCellInBoard(Board* board, Coord cellCoord) {
  board->cells[cellCoord.y][cellCoord.x] = LIVING_SHIP_CELL;
  board->remainingShipCells += 1;
}

void placeShipPhase(int player) {
  Board* playerBoard = getPlayerBoard(player);

  char selectionDescription[50];
  
  sprintf(selectionDescription, "Jogador %d - selecione a coordenada do seu navio.", player);
  
  Coord selectedShipCoord =
      selectBoardCoord(playerBoard, false, selectionDescription);
  
  Coord orientedCoord = getNextShipCoordByOrientation(playerBoard, selectedShipCoord);

  printFancyPausedTextWithSeconds("Colocando embarcação...", 1);

  placeShipCellInBoard(playerBoard, selectedShipCoord);
  placeShipCellInBoard(playerBoard, orientedCoord);
}

bool attemptToShootShip(Coord shot, Board* playerShotBoard) {
  int cellHitByShot = getBoardCellValue(shot, playerShotBoard);

  if (cellHitByShot == LIVING_SHIP_CELL) {
    playerShotBoard->cells[shot.y][shot.x] = DESTROYED_SHIP_CELL;
    playerShotBoard->remainingShipCells -= 1;

    return true;
  } else if (cellHitByShot == WATER_CELL) {
    playerShotBoard->cells[shot.y][shot.x] = EMPTY_WATER_CELL;
  }

  return false;
}
