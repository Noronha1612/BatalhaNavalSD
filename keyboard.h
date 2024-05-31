#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "utils.h"

#define ARROW_UP 1000
#define ARROW_DOWN 1001
#define ARROW_RIGHT 1002
#define ARROW_LEFT 1003
#define ENTER_KEY 1004
#define INVALID_KEY 1005

int readKeyboardCommand() {
  struct termios original, modified;
  char ch;

  // Get current terminal attributes
  if (tcgetattr(STDIN_FILENO, &original) != 0) {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  // Copy the original attributes to modified
  modified = original;

  // Disable canonical mode and echo
  modified.c_lflag &= ~(ICANON | ECHO);

  // Set new terminal attributes
  if (tcsetattr(STDIN_FILENO, TCSANOW, &modified) != 0) {
    perror("tcsetattr");
    exit(EXIT_FAILURE);
  }

  // Read a single character
  if (read(STDIN_FILENO, &ch, 1) == -1) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  // Restore original terminal attributes
  if (tcsetattr(STDIN_FILENO, TCSANOW, &original) != 0) {
    perror("tcsetattr");
    exit(EXIT_FAILURE);
  }

  if (ch == '\n') {
      return ENTER_KEY;
  }

  // Check for arrow key sequences and Enter key
  if (ch == '\x1b') {
    char seq[2];
    // Read the next character to identify the arrow key
    if (read(STDIN_FILENO, &seq[0], 1) == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    // Read the next character to identify the arrow key
    if (read(STDIN_FILENO, &seq[1], 1) == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    // Determine arrow key
    switch (seq[1]) {
    case 'A':
      return ARROW_UP;
    case 'B':
      return ARROW_DOWN;
    case 'C':
      return ARROW_RIGHT;
    case 'D':
      return ARROW_LEFT;
    default:
      return INVALID_KEY;
    }
  }

  return ch;
}