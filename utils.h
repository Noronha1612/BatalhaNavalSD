#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int system(const char *command);

void clearScreen() { system("clear"); }

void _printFancyPausedText(const char* text, int seconds) {
  clearScreen();

  printf("=======================================================\n");
  printf("%s\n", text);
  printf("=======================================================\n");

  sleep(seconds);
}

void printFancyPausedText(const char* text) {
  _printFancyPausedText(text, 3);
}

void printFancyPausedTextWithSeconds(const char* text, int seconds) {
  _printFancyPausedText(text, seconds);
}