[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/TIPYexe/POO_ClashRoyale/blob/master/README.en.md)
[![ro](https://img.shields.io/badge/lang-ro-red.svg)](https://github.com/TIPYexe/POO_ClashRoyale/blob/master/README.md)

# 2D Clash Royale | Object Oriented Programming | C++

In this project, I have implemented a simplified version of the game [Clash Royale](https://supercell.com/en/games/clashroyale/). I have kept all the rules of the game, but I have limited the number of entities on the battlefield and have implemented only a portion of the characters.

# Requirements:
  - MinGW v8
  - C++ 17
  - Run the program from the console or PowerShell (either from CodeBlocks or directly from the console)
      - g++ should be added to the PATH
      - Command: g++ -std=c++17 *.cpp -o FileName -pthread
  - I have kept only two characters to ensure that the battle ends in a reasonable time;

# The program contains
  - [Multi-threading](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/ConsoleApplication1.cpp#L61-L67) for each character and tower individually, and for displaying the map;
  - Virtual function ([Elixir::printElixir](https://github.com/TIPYexe/POO_ClashRoyale/blob/e68358130cd3d86c33fa093938a929d9d68237fe/Elixir.cpp#L21-L23) [Side::printElixir](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/Side.cpp#L45-L50));
  - Inheritance (class Side [inherits class Character and class Elixir](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/Side.h#L9));
  - [Factory](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/Personaj_factory.h#L8-L14) with static methods;
  - Smart pointers: [The list of Character types is a unique_ptr](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/ConsoleApplication1.cpp#L16);
  - [Exceptions](https://github.com/TIPYexe/POO_ClashRoyale/blob/main/ConsoleApplication1.cpp#L41-L53);
  - Class definitions, constructors, method creation;

# Rules
  - The Friendly team starts from the left side of the map (so Enemy from the right side);
  - Each team consists of a tower and a randomly chosen character from the available ones;
  - Each team can collect a maximum of 10 elixir;
  - The game ends when a tower is destroyed or when both characters die at the same time;
  
    ## Characters
        - Each character is unique: in terms of HP, attack cooldown, attack power, attack range;
        - Some characters walk on the ground, while others fly (none can do both);
        - Some characters can only attack ground targets, while others can attack both ground and air targets (none can attack only flying characters);
        - Characters can only move in one direction (so they cannot turn back to attack an enemy character passing by them);
  
    ## Towers
        - The towers of both teams are identical: in terms of attack power, attack cooldown, and attack range;
        - Towers cannot attack their own team members (no friendly fire);
        - Towers cannot change their position;
  
    ## Elixir
        - Elixir increases at a rate of 0.35/s;
        - With elixir, a new character of the same type as the starting one can be purchased, but only when the other character dies (so we cannot have two characters on the same team simultaneously);
