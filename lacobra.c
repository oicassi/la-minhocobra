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
#define WIDTH 1000
#define HEIGHT 600
#define TAMANHOMAX 50
#define TAMANHOINICIAL 3
#define GAMEFIRMA "4 NEVE(R)S GAMES!"


typedef struct _LACOBRA {
    Vector2 pos;
    Color cor;
} LACOBRA;

// declaração das funções
Color getColor(int i); // retorna aleatoriamente uma das cores possiveis para os elementos da cobra
void initVars(LACOBRA *cobra, int *inicio, int *fim, int *tam); // inicializa as variáveis
void gameIntro(); // introdução que mostra o nome da "empresa" de jogos (kkkkk)
void moveCobra(LACOBRA *cobra, int direc, int inicio, int fim, int tam); // função que faz o movimento da cobra
int colisionTest(LACOBRA *cobra, int inicio, int fim, int tam, int coli); // testa a colisão da cobra //TODO tirar o coli
void insertFila(LACOBRA *cobra, int *inicio, int *fim, int *tam, Color coraux); // faz a inserção de um elemento na fila
void removeFila(LACOBRA *cobra, int *inicio, int *fim, int *tam); // remove o elemento mais antigo da fila

int main(int argc, char *argv[]) {
    // inicializações da tela e do áudio
    InitWindow(WIDTH, HEIGHT, "LACOBRA"); // inicialização da janela do jogo    
    InitAudioDevice(); // inicialização do sistema de áudio

    // variáveis
    int direc = 0, i, spacing = 0; 
    // direc é a variável que indica a direção do movimento 
    // spacing define um espaçamento entre um elemento da cobra e outro
    int fim, inicio, tam; // fim, inicio e tam são as variáveis que controlam a fila
    int colision = 0; // variavel para controlar a colisao //TODO possivelmente isso vai sair
    int j, c;
    LACOBRA cobra[TAMANHOMAX];
    Texture2D background = LoadTexture("resources/fundolindo.png");
    
    initVars(cobra, &inicio, &fim, &tam); // inicializa as variávies
    SetTargetFPS(15);   // Velocidade do jogo

// +---------------------------- INTRODUÇÃO DO JOGO ------------------------------+//
    gameIntro();
// +-------------------- INÍCIO DO LOOP PRINCIPAL DO JOGO ------------------------+//
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        
       colision = colisionTest(cobra, inicio, fim, tam, colision);

       if (IsKeyDown(KEY_Q)) insertFila(cobra, &inicio, &fim, &tam, RED);
       if (IsKeyDown(KEY_W)) insertFila(cobra, &inicio, &fim, &tam, GREEN);
       // TODO ajeitar as condições para inserção da fila ser pela comida e nao por tecla

       if (IsKeyDown(KEY_R)) removeFila(cobra, &inicio, &fim, &tam);
       // TODO ajeitar as condições para remoção da fila ser pela comida e nao por tecla


        if (IsKeyDown(KEY_RIGHT)) {
            if (direc != 2) direc = 0;
        } else if (IsKeyDown(KEY_LEFT)) {
            if (direc != 0) direc = 2;
        } else if (IsKeyDown(KEY_UP)) {
            if (direc != 1) direc = 3;
        } else if (IsKeyDown(KEY_DOWN)) {
            if (direc != 3) direc = 1;
        }
        moveCobra(cobra, direc, inicio, fim, tam);
        c = 0;
        j = inicio;
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GetColor(0x052c46ff));
            DrawTextureEx(background, (Vector2){ 0.0f, 0 }, 0.0f, 1.0f, WHITE);
            if (colision == 1) {
                DrawText("COLIDIU", 10, 10, 20, RED);
            }
            while (c < tam) {
                if (j == TAMANHOMAX) j = 0;
                DrawCircleV(cobra[j].pos, 10, cobra[j].cor);
                c++;
                j++;
            }
           
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    CloseWindow();        // Fecha dispositivos de vídeo
    CloseAudioDevice();   // Fecha dispositivo de áudio
    //--------------------------------------------------------------------------------------

    return 0;
}

Color getColor(int i){
    /*  Os elementos da cobra podem ter 1 entre 7 cores possíveis, são elas:
    *   Vermelha, Laranja, Amarelo, Verde, Azul claro, Azul escuro e violeta.
    *   Essas cores já são pré definidas na biblioteca raylib. 
    *   Esta função gera um número aleatório entre 1 e 7 e, conforme for o resultado,
    *   retorna uma das 7 cores;
    */
    int corzinhaLinda;
    srand(time(NULL));
    corzinhaLinda = (rand() + i) % 7 + 1;
    switch(corzinhaLinda) {
        case (1): // Vermelho
            return RED;
            break;
        case (2): // Laranja
            return ORANGE;
            break;
        case (3): // Amarelo
            return YELLOW;
            break;
        case (4): // Verde
            return GREEN;
            break;
        case (5): // Azul claro
            return SKYBLUE;
            break;
        case (6): // Azul escuro
            return DARKBLUE;
            break;
        case (7): // Violeta
            return VIOLET;
            break;
        default:
            return RED; // colocado um default apenas por garantia
            break;
    }
}

void initVars(LACOBRA *cobra, int *inicio, int *fim, int *tam) {
    /*  A cobra vai inicar com 3 elementos: cabeça e mais 2 elementos do corpo
    *   Em termos de fila, a cabeça é o elemento mais antigo da fila e a ponta do corpo
    *   é o elemento mais novo. Assim sendo, a variável <inicio> indica a cabeça da cobra
    *   e a variável <fim> indica o último elemento da cobra. Logo, a variável <tam> inicia
    *   com 3 (valor que está definido nas primeiras linhas deste código, através da decalraçao
    *   #define TAMANHOINICIAL);
    *
    *   OBS: obviamente que, se for alterado o #define TAMANHOINICIAL, a inicialização da
    *   cobra muda.
    *   OBS2: se TAMANHOINICIAL for menor que 3 ou maior que 300, o código muda para o valor
    *   default de 3;
    */
    printf("Ram papapapam\n");
    int i; 
    float spacing = 0.0f;
    if ((TAMANHOINICIAL >= 3) && (TAMANHOINICIAL <= 300))(*tam) = TAMANHOINICIAL;
    else (*tam) = 3;
    (*inicio) = 0; // cabeça da cobra é o elemento do vetor indicado por <inicio>
    (*fim) = (*tam) - 1; // o último elemento do corpo da cobra é indicado por <fim>
    for (i = (*inicio); i <= (*fim); i++) {
        cobra[i].cor = getColor(i);
    }
    cobra[(*inicio)].pos.x = (float)WIDTH / 2; // posição horizontal da cabeça da cobra no meio
    cobra[(*inicio)].pos.y = (float)HEIGHT / 2; // posição vertical da cabeça da cobra no meio
    spacing -= 20;
    for (i = 1; i <= (*fim); i++) {
        cobra[i].pos.x = (float)WIDTH / 2 + spacing;
        cobra[i].pos.y = (float)HEIGHT / 2;
        spacing -= 20;
    }

    for (i = (*inicio); i <= (*fim); i++) {
        printf("Cobra %d: posx: %f e posy: %f\n", i, cobra[i].pos.x, cobra[i].pos.y);
    }
}

void gameIntro() {
    /*  A introdução usa a variável <t> para controlar o tempo de duração. Começa em 0 e
    *   quando chegar em 150 ela para. Quando <t> vale 65 ou mais aparece o nome da "empresa" 
    *   que é definido no início do código (#define GAMEFIRMA). Quando o raio do círculo
    *   chega em 700 (variável <raio>), ele para de crescer e se mantem nesse tamanho.
    *   Quando <t> vale 100 ou mais, o círculo para de mudar de cor ficando apenas branco.
    *   Quando <t> vale 120 inicia um processo de fadeout da tela. O fade out é feito pela
    *   variável int <fader> que controla a opacidade da cor apresentada. A partir de <t> 
    *   maior ou igual a 120, <fader> vai reduzindo em 8;
    *
    *   OBS: A variável int <colorInd> é usada para controlar a variação de cores do nome
    *   da firma (que fica variando entre preto e vermelho);
    */
    Sound intro = LoadSound("resources/introsound.mp3");
    Vector2 circlePos;
    Color color, textColor;
    textColor =(Color){0, 0, 0, 255};
    int colorInd = 0, t = 0, fader = 255, raio = 1;
    circlePos.x = 500;
    circlePos.y = 300;

    PlaySound(intro);
    while (t <= 150) {
        BeginDrawing();
        ClearBackground((Color){0, 0, 0, 255});
        if (raio >= 700) raio = 700;
        color = (Color){GetRandomValue(0, fader), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        if (t >= 100) color = (Color){245, 245, 245, fader};
        if (t >= 120) fader -= 8;
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
        printf("%d\n", t); // TODO remover o printf de t do console?
    }
}

void moveCobra(LACOBRA *cobra, int direc, int inicio, int fim, int tam) {
    /*  Conforme o valor da variável <direc> a cabeça da cobra move para uma direção.
    *   A cabeça se movimenta avançando 20 pixels por vez (pois o raio de cada elemento
    *   da cobra é de 10 pixels). Após o movimento da cabeça, os outros elementos do corpo
    *   apenas copiam as coordenadas do elemento imediatamente anterior.
    */
    Vector2 aux1, aux2; // variáveis que serão utilizadas para armazenar temporariemente a posição
    int i = inicio, cont = 1;

    switch (direc) {
        case 0: // direita
            aux1 = cobra[inicio].pos;
            if (cobra[inicio].pos.x == WIDTH) cobra[inicio].pos.x = 0.0f;
            cobra[inicio].pos.x += 20.0f;
            while (cont < tam) {
                i++;
                if (i == TAMANHOMAX) i = 0;
                aux2 = cobra[i].pos;
                cobra[i].pos = aux1;
                aux1 = aux2;
                cont++;
            }
            break;

        case 1: // baixo
            aux1 = cobra[inicio].pos;
            if (cobra[inicio].pos.y == HEIGHT) cobra[inicio].pos.y = 0.0f;
            cobra[inicio].pos.y += 20.0f;
            while (cont < tam) {
                i++;
                if (i == TAMANHOMAX) i = 0;
                aux2 = cobra[i].pos;
                cobra[i].pos = aux1;
                aux1 = aux2;
                cont++;
            }
            break;
                
        case 2: // esquerda
            aux1 = cobra[inicio].pos;
            if (cobra[inicio].pos.x == 0.0f) cobra[inicio].pos.x = WIDTH;
            cobra[inicio].pos.x -= 20;
            while (cont < tam) {
                i++;
                if (i == TAMANHOMAX) i = 0;
                aux2 = cobra[i].pos;
                cobra[i].pos = aux1;
                aux1 = aux2;
                cont++;
            }
            break;

        case 3: // cima
            aux1 = cobra[inicio].pos;
            if (cobra[inicio].pos.y == 0.0f) cobra[inicio].pos.y = HEIGHT;
            cobra[inicio].pos.y -= 20;
            while (cont < tam) {
                i++;
                if (i == TAMANHOMAX) i = 0;
                aux2 = cobra[i].pos;
                cobra[i].pos = aux1;
                aux1 = aux2;
                cont++;
            }
            break;
    }
}

int colisionTest(LACOBRA *cobra, int inicio, int fim, int tam, int coli) {
    /*  Testa se a posição do elemento da cabeça (<cobra[inicio]>) é igual a alguma das
    *   posições de algum dos elementos do corpo da cobra. Se for, indica uma colisão.
    *   Atualmente o indicativo de colisão é retornar 1. 
    *
    *   OBS/TODO: A titulo de teste, a deteccão de colisão tá sendo testada pra que, ao
    *   retornar 1, o programa imprima na tela uma mensagem de colisão. A titulo de teste,
    *   ele vai manter impresso na tela mesmo se não estiver mais em colisão. Por isso essa
    *   função recebe a variavel que controla colisão e a retorna do jeito que ela está
    *   caso não perceba colisão. Isso serve para retornar 1 caso tenha acontecido alguma
    *   colisão no passado.
    */
    int i = inicio + 1, cont = 1;
    while (cont < tam) {
        if (i == TAMANHOMAX) i = 0;
        if ((cobra[inicio].pos.x == cobra[i].pos.x) && (cobra[inicio].pos.y == cobra[i].pos.y)) return 1; // colisão retorna 1
        i++;
        cont++;
    }
    return coli;
}

void insertFila(LACOBRA *cobra, int *inicio, int *fim, int *tam, Color coraux) {
    /*  A inserção aumenta o valor de <fim> e o valor de <tam>. Para executar a inserção, o
    *   código primeiro testa a variável <tam> pra ver se ela não está no mesmo tamanho que
    *   o valor máximo. Caso esteja, ela não executa. A função testa se o vaor de <fim> + 1 
    *   está igual ao valor de TAMANHOMAX, caso esteja coloca <fim> como 1, pois aí significa
    *   que já foi excluído alguma coisa e tem espaço no início do vetor da cobra.
    */
    if ((*tam) < TAMANHOMAX) {
        (*fim) += 1;
        if ((*fim) == TAMANHOMAX) (*fim) = 0;
        cobra[(*fim)].cor = coraux;
        (*tam)++;
        printf("\nInserido na fila!\n");
        printf("Valor de fim: %d e valor de tam: %d\n", (*fim), (*tam));
    } else {
        printf("\nNao inserido. fila cheia!\n");
    }
    // TODO remover as impressoes no console
}

void removeFila(LACOBRA *cobra, int *inicio, int *fim, int *tam) {
    if ((*tam) > 1) {
        (*inicio) += 1;
        if ((*inicio) == TAMANHOMAX) (*inicio) = 0;
        (*tam)--;
        printf("\nRemovido da fila\n");
        printf("\nValor de inicio: %d e valor de tam: %d\n", (*inicio), (*tam));
    } else {
        printf("\nNao foi removido pois a fila ta pequenina\n");
    }
}
