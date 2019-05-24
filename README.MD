# LA MINHOCOBRA - A SNAKE GAME USING QUEUE DATA STRUCTURE
---
## This is a task for implement a queue data structure throug a snake game. In general the game is similar to the traditional snake game, with only a few different rules
---
Here is how the game works:
- At the start of the game, the snake starts with 3 elements: A head and 2 parts of tail
- Each part of the snake have one of the following colors: red, orange, yellow, green , light blue, dark blue and violet
- Every moment will spawn 2 kinds of "food" to the snake. One of the foods will be the same color as the head and the other food will be one of the random colors from above.
- If the snake eats a food with the same color of the head, the head disappear and, therefore, the snake will be reduced.
- If the snake eats a food with a different color of the head, then this food will became a part of the snake as an element of the tail.
- The score will be a function based on the size of the snake and the time that the snake is running.
---
To handle graphical interface, the Raylib library was chosen
[Raylib by raysan5 on GitHub] (https://github.com/raysan5/raylib "RayLib GitHub repository")
