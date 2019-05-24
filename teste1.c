/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

/*******************************************************************
*
*	Mais importante de tudo. Como executar as coisas:
*	1) copiar o arquivo libraylib.a pra pasta onde está o arquivo principal
	2)
*	2) compilar o código usando o seguinte comando no terminal:
*	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a arquivo.c -o saida
*	3) vlw eh nós
*
********************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1200;
    int screenHeight = 700;
    int direc = 0, i;
    float spacing = 0.0, auxx, auxy, auxx2, auxy2;

    InitWindow(screenWidth, screenHeight, "minhoquitos");

    Vector2 ballPosition[40];
    Vector2 aux1, aux2;
    Color colors[40], back, temp, backyeah;

    ballPosition[0].x = (float)screenWidth / 2;
    ballPosition[0].y = (float)screenHeight / 2;
    colors[0] = (Color) {255, 0, 0, 255};
    spacing -= 20;
    for (i = 1; i < 40; i++) {
    	ballPosition[i].x = ((float)screenWidth / 2) + spacing;
    	ballPosition[i].y = ((float)screenHeight / 2);
    	spacing -= 20;
    	colors[i] = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(100, 255) };
    }
    SetTargetFPS(20);       // Set target frames-per-second
    //--------------------------------------------------------------------------------------
    back = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(100, 255) };
    backyeah = back;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    	
    	spacing = 0;
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) {
			if (direc != 2) direc = 0;
        }
       	else
        if (IsKeyDown(KEY_LEFT)) {
        	if (direc != 0) direc = 2;
        }else
        if (IsKeyDown(KEY_UP)) {
        	if (direc != 1) direc = 3;
        }else
        if (IsKeyDown(KEY_DOWN)) {
        	if (direc != 3) direc = 1;
        }

        switch (direc) {
        	case 0: // direita
        		aux1 = ballPosition[0];
        		ballPosition[0].x += 20.0f;
        		for (i = 1; i < 40; i++) {
        			aux2 = ballPosition[i];
        			ballPosition[i] = aux1;
        		//	ballPosition[i].x -= 18.0;
        			aux1 = aux2;
        		}
        	break;

        	case 1: //baixo
        		aux1 = ballPosition[0];
        		ballPosition[0].y += 20.0f;
        		for (i = 1; i < 40; i++) {
        			aux2 = ballPosition[i];
        			ballPosition[i] = aux1;
        		//	ballPosition[i].y -= 18.0;
        			aux1 = aux2;
        		}
        		break;
        		
        	case 2: // esquerda
        		aux1 = ballPosition[0];
        		ballPosition[0].x -= 20.0f;
        		for (i = 1; i < 40; i++) {
        			aux2 = ballPosition[i];
        			ballPosition[i] = aux1;
        			//ballPosition[i].x += 18.0;
        			aux1 = aux2;
        		}
        		break;

        	case 3: // cima
        		aux1 = ballPosition[0];
        		ballPosition[0].y -= 20.0f;
        		for (i = 1; i < 40; i++) {
        			aux2 = ballPosition[i];
        			ballPosition[i] = aux1;
        			//ballPosition[i].y += 18.0;
        			aux1 = aux2;
        		}
        		break;
        }
        for (i = 1; i < 40; i++) {
        	if ((ballPosition[0].x == ballPosition[i].x) && (ballPosition[0].y == ballPosition[i].y)) {
        		backyeah = back;
        		temp = (Color){255, 0, 0, 255}; //Colisao muda o fundo para vermelho
        		back = temp;
        	}
        	//else back = backyeah;
        }
        
        //----------------------------------------------------------------------------------
		
    	

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

           // ClearBackground((Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 });
        	ClearBackground(back);
            DrawText("minhocao", 10, 10, 20, DARKGRAY);
            for (i = 0; i < 40; i++)	DrawCircleV(ballPosition[i], 10, colors[i]);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}