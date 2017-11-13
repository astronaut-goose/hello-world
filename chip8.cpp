#include <iostream>
#include "chip8.h"


Chip8::Chip8() {};
Chip8::~Chip8() {};

std::array<std::uint8_t, 80> fontset =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
    0x20, 0x60, 0x20, 0x20, 0x70, //1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
    0x90, 0x90, 0xF0, 0x10, 0x10, //4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
    0xF0, 0x10, 0x20, 0x40, 0x40, //7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
    0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

void Chip8::initialize(){

  // Initialize registers and memory once

  pc = 0x200;  // Most Chip-8 programs start at location 0x200 (512)
  sp = 0;      // Reset stack Pointer
  I  = 0;      // Reset memory address register
  opcode = 0;  // Reset opcode

  // Clear the stack, keypads and V registers

  V = {};
  stack = {};
  key = {};

  // Clear memory

  memory = {};

  // Reseting timers

  delay_timer = 0;
  sound_timer = 0;

  // Clear the display

  gfx = {};

  // Load font set into memory [przypomnij sobie o wypełnianiu arraya z STL i popraw]

  for (size_t i = 0; i < 80; i++) {
    memory[i] = fontset[i];
  }

}

/*
void Chip8::loadGame(){

   NO CÓŻ HEHE DO ZROBIENIA CAŁE POWODZENIA -- poczytaj o fopen (binary mode)

}
*/

void Chip8::emulateOneCycle(){

  // Fetch Opcode [ the first fetching takes place at memory at 0x200 and 0x201 -- where the program data is starting ]

  opcode = memory[pc] << 8 | memory[pc+1];

  // Decode Opcode [ "wyciągamy" tutaj informację o tym jaki znak stoi na pierwszym miejscu danego opcodu - działa to dla większości opcodów,
  //                 ale dla niektórych będziemy musieli zrobić dodatkowe switche sprawdzające znaki na kolejnych miejscach ]

  switch (opcode & 0xF000){

    //case 0x0000:
      //switch  DO ZROBIENIA BLOK SWITCHÓW DLA 0x0000
    
    case 0x1000:  // 1nnn
      pc = opcode & 0x0FFF;
      break;

    case 0x2000:  // 2nnn
      sp++;
      stack[sp - 1] = pc; // ???
      pc = opcode & 0x0FFF;
      break;

    case 0x3000:  // 3xkk -- błąd w instrukcji, powinno być pc += 4
      if( V[opcode & 0x0F00 >> 8] == opcode & 0x00FF )
        pc += 4;
      else
        pc += 2;
      break;

    case 0x4000:  // 4xkk
      if( V[opcode & 0x0F00 >> 8] != opcode & 0x00FF )
        pc += 4;
      else
        pc += 2;
      break;

    case 0x5000:  // 5xy0
      if( V[opcode & 0x0F00 >> 8] == V[opcode & 0x00F0 >> 4] )
        pc += 4;
      else
        pc += 2;
      break;

    case 0x6000:  // 6xkk
      V[opcode & 0x0F00 >> 8] = opcode & 0x00FF;
      pc += 2;
      break;

    case 0x7000:  // 7xkk
      V[opcode & 0x0F00 >> 8] += opcode & 0x00FF;
      pc += 2;
      break;

    //case 0x8000:
      //switch  DO ZROBIENIA BLOK SWITCHÓW DLA 0x8000

    case 0x9000:  // 9xy0
      if( V[opcode & 0x0F00 >> 8] != V[opcode & 0x00F0 >> 4] )
        pc += 4;
      else
        pc += 2;
      break;

    case 0xA000:  // Annn
      I = opcode & 0x0FFF;
      pc += 2;
      break;

    case 0xB000:  // Bnnn
      pc = opcode & 0x0FFF

    case 0xC000:  // Cxkk

    case 0xD000:  // Dxyn

    //case 0xE000:  
      // switch DO ZROBIENIA BLOK SWITCHÓW DLA 0xE000

    case 0xA000:  // Annn


  }

  // Update timers
  if(delay_timer > 0)
    delay_timer--;

  if(sound_timer > 0)
    if(sound_timer == 1)
      //DŹWIĘK
    sound_timer--;
}
