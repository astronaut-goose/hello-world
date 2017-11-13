#include <iostream>
#include "chip8.h"

//#include coś z OpenGL


int main(int argc, char **argv)
{
  std::cout<< "kompiluje siem" << '\n';

// PONIŻEJ JAK MA MNIEJ WIĘCEJ WYGLĄDAĆ WYKONANIE PROGRAMU W MAINIE

  Chip8 chip8;

/*
  Set up render system and register input callbacks
  setupGraphics();
  setupInput();

  ^openGL, ogarnij

  Initialize the Chip8 system and load the game into the memory
*/

  chip8.initialize();

/*
  chip8.loadGame(WHATEVER JESZCZE NIE ZROBIŁEM)

  Emulation loop
    for(;;)     <- jakas nieskonczona petla
    {
     chip8.emulateOneCycle();

      If the draw flag is set (true), update the screen
      if(chip8.drawFlag)
        drawGraphics();
        drawFlag = false;

      Store key press state (Press and Release)
      chip8.setKeys();
    }
    SLOW DOWN THE EXECUTION OF PROGRAM TO FIT 60Hz!!!
*/

  return 0;
}
