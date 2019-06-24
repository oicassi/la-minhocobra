# LA MINHOCOBRA DEL ARCO-IRO  - A SNAKE GAME USING QUEUE DATA STRUCTURE
---
## Abstract  
This is an implementation of the traditional snake game with a few differences using the C programming language and the Raylib game library. The motivation to make this game is to make use of the *queue datastructure*. In this version, the snake can grow or reduce it's size depending on the it's color and the color of the "food" that is passing above in the map.  
  
## Contents of the repository  
This repository contains two main "parts":
- The root folder that contains the .c file, resources, the executable (lacobrafinal) and the Makefile to build the game for macOS
- The la-minhocobra-Linux folder that contains the c. file, resources, executable (lacobrita) and the Makefile to build the game for Linux systems.

*Note: for some reason the .mp3 files in Linux didn't work, so a .ogg version of the sounds were made. It was only for this reason that was decided to separate the folders (specially the resourcers folder) for macOS and Linux*

## Credits
This game was made for evaluation purposes of the Data Structures Class of the TADS course from Federal University of Parana (Universidade Federal do Paraná - UFPR).  
Made in collaboration with André Klingenfus Antunes [(André's Github Page)](https://github.com/andrekantunes) and using the amazing Raylib library from raysan5 [(raysan5's Raylib library on GitHub)](https://github.com/raysan5/raylib)  

## Installation/Execution instructions
In order to compile and/or execute the game, you need to install or build a static library fo Raylib (check the wiki in the raylib official repository page - [Working on macOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS) and [working on GNU Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux))
---
*NOTE: We didn't compile for Windows. The code probably will work "as is"  with the .mp3 files or .ogg files) but you must read the wiki on raylib repository about [Working on Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows). In this case, we can only wish you luck.*  

## Game instructions
As in any other "Snake game", the player controls a snake that must "eat" foods spreaded out across the map. The difference here is that, depending on the color of the snake's head and the food that is trying to eat, the snake will reduce it's size or increase.

Here is how the game works:
- At the start of the game, the snake starts with 3 elements: A head and 2 parts of tail
- Each part of the snake have one of the 7 following colors: red, orange, yellow, green, light blue, dark blue and violet
- Every moment will spawn some kinds of "food" to the snake.At least one of the foods will be the same color as the head and the others food will be one of the random colors from above.
- If the snake eats a food with the same color of the head, the head disappear and, therefore, the snake will be reduced.
- If the snake eats a food with a different color of the head, then this food will became a part of the snake as an element of the tail.
- The score will be a function based on the size of the snake and the time that the snake is running.
---
To handle graphical interface, the Raylib library was chosen
[Raylib by raysan5 on GitHub](https://github.com/raysan5/raylib "RayLib GitHub repository")
