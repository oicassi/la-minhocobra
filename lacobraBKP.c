/* ESTRUTURA DE DADOS 1
*  Trabalho Snake
*  La-Cobra
*  Alunos: André Klingenfus Antunes & Cassiano Kruchelski Vidal
*
*/
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
#define GAMEFIRMA "PEREPEPEPE GAMES"


void gameIntro();

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 600;
    int direc = 0, i;
    float spacing = 0.0, auxx, auxy, auxx2, auxy2;

    InitWindow(screenWidth, screenHeight, "minhoquitos");
    InitAudioDevice();

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
    gameIntro();
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
                if (ballPosition[0].x == screenWidth) ballPosition[0].x = 0;
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
                if (ballPosition[0].y == screenHeight) ballPosition[0].y = 0.;
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
                if (ballPosition[0].x == 0.0) ballPosition[0].x = screenWidth;
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
                if (ballPosition[0].y == 0.0f) ballPosition[0].y = screenHeight;
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
    CloseAudioDevice();
    return 0;
}


void gameIntro() {
    Sound intro = LoadSound("resources/introsound.mp3");
    Vector2 circlePos;
    Color color, textColor;
    textColor =(Color){0, 0, 0, 255};
    int colorInd = 0, t = 0;;
    int fader = 255;
    circlePos.x = 500;
    circlePos.y = 300;
    int raio = 1;

    PlaySound(intro);
while (t <= 150) {
    BeginDrawing();
    ClearBackground((Color){0, 0, 0, 255});
    if (raio >= 700) raio = 700;
    color = (Color){GetRandomValue(0, fader), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
    if (t >=100) {
        color = (Color){245, 245, 245, fader};
    }
    if (t >=120)
        fader -= 8;
    
    DrawCircleV(circlePos, raio, color);
    if (t >= 65){
        DrawText(GAMEFIRMA, 600, 350, 30, textColor);
        if (colorInd == 0) {
            textColor = (Color){255, 0, 0, fader};
            colorInd = 1;
        } else {
            textColor = (Color){0, 0, 0, fader};
            colorInd = 0;
        }
    }
    EndDrawing();
    raio += 10;
    t++;
    printf("%d\n", t);
}

}