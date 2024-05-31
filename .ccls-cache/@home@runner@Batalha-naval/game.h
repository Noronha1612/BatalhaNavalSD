#include "ship.h"

int player1Points = 0;
int player2Points = 0;

int playerTurn = 1;
int hasGameEnded = 0;

bool playerPlay(int player) {
  Board* enemyBoard = getPlayerBoard(player == 1 ? 2 : 1);
  int* currentPlayerPoints = player == 1 ? &player1Points : &player2Points;
  
  char prompt[52];
  sprintf(prompt, "Jogador %d - selecione a coordenada para dar o tiro.", player);

  Coord shotCoord = selectBoardCoord(enemyBoard, true, prompt);

  bool hasHitATarget = attemptToShootShip(shotCoord, enemyBoard);

  if (hasHitATarget) {
    (*currentPlayerPoints) += 1;
  }

  if (enemyBoard->remainingShipCells == 0) {
    hasGameEnded = 1;
  }

  return hasHitATarget;
}

void flipTurn() {
  playerTurn = playerTurn == 1 ? 2 : 1;
}

void gamePhase() {
  while (!hasGameEnded) {
    bool hasHitATarget = playerPlay(playerTurn);

    if (hasHitATarget) {
      printFancyPausedTextWithSeconds("Você acertou o tiro!", 1);
    } else {
      printFancyPausedTextWithSeconds("Oops, o tiro não acertou um navio vivo.", 1);
    }
    
    flipTurn();
  }

  clearScreen();

  printf("=======================================================\n");
  printf("Obrigado por jogar. Aqui está o placar:\n\n");
  
  printf("Jogador 1 acertou: %d parte(s) do návio.\n", player1Points);
  printf("Jogador 2 acertou: %d parte(s) do návio.\n\n", player2Points);

  printf(player1Points > player2Points ? "Jogador 1 venceu!" : "Jogador 2 venceu!");
  printf("\n=======================================================\n");
}
