#include <stdio.h> 
#include <unistd.h>
#include "./game.h"

int main(void) {

  Board* player1Board = getPlayerBoard(1);
  Board* player2Board = getPlayerBoard(2);
  
  initializeBoard(player1Board);
  initializeBoard(player2Board);

  printFancyPausedText("Inicializando tabuleiros dos jogadores...");
  
  placeShipPhase(1);
  placeShipPhase(2);

  printFancyPausedText("Todas as embarcações a postos, iniciando jogo...");

  gamePhase();

  return 0;
}