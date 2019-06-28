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
#define WIDTH 1000 // largura da tela
#define HEIGHT 600 // altura da tela
#define TAMANHOMAX 300 // tamanho máximo da cobra
#define TAMANHOINICIAL 3 // tamanho inicial da cobra
#define MAXCOMIDA 10 // quantidade de comidas que irao aparecer por vez
#define GAMEFIRMA "4 NEVE(R)S GAMES!" // nome da firma que faz o jogo
#define RAIO 10

typedef struct _LACOBRA {
    Vector2 pos;
    Color cor;
    int colorInd;
} LACOBRA;

// declaração das funções
Color getColor(int *colorInd); // retorna aleatoriamente uma das cores possiveis para os elementos da cobra
void initVars(LACOBRA *cobra, int *inicio, int *fim, int *tam); // inicializa as variáveis
void gameIntro(Sound *intt); // introdução que mostra o nome da "empresa" de jogos (kkkkk)
void moveCobra(LACOBRA *cobra, int direc, int inicio, int fim, int tam); // função que faz o movimento da cobra
void insertFila(LACOBRA *cobra, int *inicio, int *fim, int *tam, Color coraux, int colorInd); // faz a inserção de um elemento na fila
void removeFila(LACOBRA *cobra, int *inicio, int *fim, int *tam); // remove o elemento mais antigo da fila
Vector2 getPosicao(); // Retorna uma posição x e y aleatórias
void createPapa(LACOBRA *papa, LACOBRA *cobra, int inicio, int tam); // cria comida para adicionar ao cenário.
void colisionTest(LACOBRA *cobra, LACOBRA *papa, int *inicio, int *fim, int *tam, int *coli, int *score, float b1x, float b1y, float b2x, float b2y, Sound *ifila, Sound *rfila); // testa a colisão da cobra //TODO tirar o coli
void gameOver(Sound *songg); // Para aparecer o game over;
int gameMenu(int *dif, Sound *songg); // Menu para selecionar a dificuldade;

float b1x, b1y, b2x, b2y; // posicoes dos blocos

int main(int argc, char *argv[]) {
    // inicializações da tela e do áudio
    InitWindow(WIDTH, HEIGHT, "LACOBRA"); // inicialização da janela do jogo    
    InitAudioDevice(); // inicialização do sistema de áudio
    Texture2D background;
    Texture2D block = LoadTexture("resources/blockBackground.png");
    Sound intro = LoadSound("resources/introTheme.mp3");
    Sound menuTheme = LoadSound("resources/menuTheme.mp3");
    Sound mainTheme;
    Sound gameOverTheme = LoadSound("resources/gameOverTheme.mp3");
    Sound remfila = LoadSound("resources/remHit2.mp3");
    Sound insfila = LoadSound("resources/insHit2.mp3");
    Sound colhit = LoadSound("resources/colHit2.mp3");
    // variáveis
    int direc = 0, i, spacing = 0; 
    // direc é a variável que indica a direção do movimento 
    // spacing define um espaçamento entre um elemento da cobra e outro
    int fim, inicio, tam; // fim, inicio e tam são as variáveis que controlam a fila
    int colision = 0; // variavel para controlar a colisao //TODO possivelmente isso vai sair
    int j, c, score = 0, option, dif = 0, blockCheck = 0;
    LACOBRA cobra[TAMANHOMAX];
    LACOBRA papa[MAXCOMIDA];
    char scoreText[10];
    initVars(cobra, &inicio, &fim, &tam); // inicializa as variávies
    SetTargetFPS(15);   // Velocidade do jogo
    createPapa(papa, cobra, inicio, tam);
    b1x = 120.0f;
    b1y = 40.0f;
    b2x = 640.0f;
    b2y = 300.0f;
// +---------------------------- INTRODUÇÃO DO JOGO ------------------------------+//
  
    gameIntro(&intro);

// +------------------------------- MENU DO JOGO ---------------------------------+//

    do {    
        option = gameMenu(&dif, &menuTheme);
    } while (option != 1);
    if (dif == 1) {
        background = LoadTexture("resources/hardcoreBack.png");
        mainTheme = LoadSound("resources/hardcoreTheme.mp3");
    } else {
        background = LoadTexture("resources/fundoLindo.png");
        mainTheme = LoadSound("resources/mainTheme.mp3");
    }
// +-------------------- INÍCIO DO LOOP PRINCIPAL DO JOGO ------------------------+//
   
    while ((tam > 0) && (colision != 1))  {    // Detect window close button or ESC key
        if (!IsSoundPlaying(mainTheme)) PlaySound(mainTheme);
        if (IsKeyDown(KEY_Q)) break;
        
        moveCobra(cobra, direc, inicio, fim, tam);
        
        if (IsKeyDown(KEY_RIGHT)) {
            if (direc != 2) direc = 0;
        } else if (IsKeyDown(KEY_LEFT)) {
            if (direc != 0) direc = 2;
        } else if (IsKeyDown(KEY_UP)) {
            if (direc != 1) direc = 3;
        } else if (IsKeyDown(KEY_DOWN)) {
            if (direc != 3) direc = 1;
        
        }
        c = 0;
        j = inicio;
        
        sprintf(scoreText, "%d", score);

        BeginDrawing();
            ClearBackground(GetColor(0x052c46ff));
            DrawTextureEx(background, (Vector2){ 0.0f, 0 }, 0.0f, 1.0f, WHITE);
            while (c < tam) {
                if (j == TAMANHOMAX) j = 0;
                DrawCircleV(cobra[j].pos, RAIO, cobra[j].cor);
                c++;
                j++;
            }
            c = 0;
            while (c < MAXCOMIDA) {
                DrawCircleV(papa[c].pos, RAIO, papa[c].cor);
                c++;
            }
            DrawTextureEx(block, (Vector2){ b1x, b1y }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(block, (Vector2){ b2x, b2y }, 0.0f, 1.0f, WHITE);
            DrawText("score:  ", 720, 10, 20, GRAY);
            DrawText(scoreText, 800, 10, 20, GRAY);    
        EndDrawing();

        colisionTest(cobra, papa, &inicio, &fim, &tam, &colision, &score, b1x, b1y, b2x, b2y, &insfila, &remfila);
        if (colision == 1) {
            PlaySound(colhit);
            break;
        }
    }
    StopSound(mainTheme);
// +------------------------------ GAME OVER ---------------------------------+//   

    gameOver(&gameOverTheme);


// +---------------------------- DEINITIALIZATION ----------------------------+//

    UnloadTexture(background);
    UnloadSound(intro);
    UnloadSound(menuTheme);
    UnloadSound(mainTheme);
    UnloadSound(gameOverTheme);
    UnloadSound(colhit);
    UnloadSound(insfila);
    UnloadSound(remfila);
    CloseWindow();        // Fecha dispositivos de vídeo
    CloseAudioDevice();   // Fecha dispositivo de áudio

// +---------------- THE END ---------------- //
    return 0;
}

Color getColor(int *colorInd){
    /*  Os elementos da cobra podem ter 1 entre 7 cores possíveis, são elas:
    *   Vermelha, Laranja, Amarelo, Verde, Azul claro, Azul escuro e violeta.
    *   Essas cores já são pré definidas na biblioteca raylib. 
    *   Esta função gera um número aleatório entre 1 e 7 e, conforme for o resultado,
    *   retorna uma das 7 cores;
    */
    int corzinhaLinda;
    corzinhaLinda = GetRandomValue(1, 7);
    *(colorInd) = corzinhaLinda;
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
    int i; 
    float spacing = 0.0f;
    if ((TAMANHOINICIAL >= 3) && (TAMANHOINICIAL <= 300))(*tam) = TAMANHOINICIAL;
    else (*tam) = 3;
    (*inicio) = 0; // cabeça da cobra é o elemento do vetor indicado por <inicio>
    (*fim) = (*tam) - 1; // o último elemento do corpo da cobra é indicado por <fim>
    for (i = (*inicio); i <= (*fim); i++) {
        cobra[i].cor = getColor(&cobra[i].colorInd);
    }
    cobra[(*inicio)].pos.x = (float)(WIDTH / 2) - RAIO; // posição horizontal da cabeça da cobra no meio
    cobra[(*inicio)].pos.y = (float)(HEIGHT / 2) - RAIO; // posição vertical da cabeça da cobra no meio
    spacing -= 20;
    for (i = 1; i <= (*fim); i++) {
        cobra[i].pos.x = (float)WIDTH / 2 - RAIO + spacing;
        cobra[i].pos.y = (float)HEIGHT / 2 - RAIO;
        spacing -= 20;
    }

    for (i = (*inicio); i <= (*fim); i++) {
        printf("Cobra %d: posx: %f e posy: %f\n", i, cobra[i].pos.x, cobra[i].pos.y);
    }
}

void gameIntro(Sound *intt) {
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
    Vector2 circlePos;
    Color color, textColor;
    textColor =(Color){0, 0, 0, 255};
    int colorInd = 0, t = 0, fader = 255, raio = 1;
    circlePos.x = 500;
    circlePos.y = 300;

    PlaySound((*intt));
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
    if (cobra[inicio].pos.x > WIDTH) cobra[inicio].pos.x = 10.0f;
    else if (cobra[inicio].pos.x < 0.0f) cobra[inicio].pos.x = WIDTH - 10.0f;
    if (cobra[inicio].pos.y > HEIGHT) cobra[inicio].pos.y = 10.0f;
    else if (cobra[inicio].pos.y < 0.0f) cobra[inicio].pos.y = HEIGHT - 10.0f;
   // printf("Posicao x: %f Posicao y: %f\n", cobra[inicio].pos.x, cobra[inicio].pos.y);
}

void insertFila(LACOBRA *cobra, int *inicio, int *fim, int *tam, Color coraux, int colorInd) {
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
        cobra[(*fim)].colorInd = colorInd;
        (*tam)++;
        printf("\nInserido na fila!\n");
        printf("Valor de fim: %d e valor de tam: %d\n", (*fim), (*tam));
    } else {
        printf("\nNao inserido. fila cheia!\n");
    }
    // TODO remover as impressoes no console
}

void removeFila(LACOBRA *cobra, int *inicio, int *fim, int *tam) {
    (*inicio) += 1;
    if ((*inicio) == TAMANHOMAX) (*inicio) = 0;
    (*tam)--;
}

Vector2 getPosicao() {
    /*  A ideia dessa função é retornar uma posição que seja compatível com o tamanho da tela
    *   e com a divisão de possíveis posições, baseado no raio do circulo. Essa função é
    *   constantemente utilizada pela void createPapa para gerar posições aleatórias para 
    *   as comidas.
    */
    Vector2 posTemp;
    posTemp.x = (GetRandomValue(0, (WIDTH / (RAIO * 2)) - 1) * (RAIO * 2) + 10) * 1.0f;
    posTemp.y = (GetRandomValue(0, (HEIGHT / (RAIO * 2)) - 1) * (RAIO * 2) + 10) * 1.0f;
    return posTemp;
}

void createPapa(LACOBRA *papa, LACOBRA *cobra, int inicio, int tam) {
    /*  A função simplesmente vai gerar valores de x e y para os alimentos que estao no 
    *   array papa. Além das posições, também vai definir cores aleatórias. O único detalhe
    *   é que uma (ou mais) comidas vai ter a mesma cor da cabeça.
    */
    int i = 1, j = 0, t, posCheck = 0, k = 0, cont = 0;
    t = MAXCOMIDA;
    papa[0].cor = cobra[inicio].cor;
    papa[0].colorInd = cobra[inicio].colorInd;
    do {
        posCheck = 0;
        papa[0].pos = getPosicao();
        if (((papa[0].pos.x >= b1x) && (papa[0].pos.x <= (b1x + 240))) && ((papa[0].pos.y >= b1y) && (papa[0].pos.y <= (b1y + 240)))) posCheck = 1;
        if (((papa[0].pos.x >= b2x) && (papa[0].pos.x <= (b2x + 240))) && ((papa[0].pos.y >= b2y) && (papa[0].pos.y <= (b2y + 240)))) posCheck = 1;
    } while (posCheck != 0);

    t--;
    while (t > 0) {
        posCheck = 0;
        k = 0;
        cont = 0;
        papa[i].cor = getColor(&papa[i].colorInd);
        do {
            posCheck = 0;
            papa[i].pos = getPosicao();
            for (j = 0; j < i; j++) { // compara com as outras comidas criadas
                if ((papa[i].pos.x == papa[j].pos.x) && (papa[i].pos.y == papa[j].pos.y)) posCheck = 1;
            } 
            if (posCheck == 0) {
                while (cont < tam) { // compara com os elementos da cobra
                    if (k == TAMANHOMAX) k = 0;
                    if ((papa[i].pos.x == cobra[k].pos.x) && (papa[i].pos.y == cobra[k].pos.y)) {
                        posCheck = 1; 
                        break;
                    }
                    k++;
                    cont++;
                }
            }
            if (posCheck == 0) {
                if (((papa[i].pos.x >= b1x) && (papa[i].pos.x <= (b1x + 240))) && ((papa[i].pos.y >= b1y) && (papa[i].pos.y <= (b1y + 240)))) posCheck = 1; // compara com o bloco 1
                if (((papa[i].pos.x >= b2x) && (papa[i].pos.x <= (b2x + 240))) && ((papa[i].pos.y >= b2y) && (papa[i].pos.y <= (b2y + 240)))) posCheck = 1; // compara com o bloco 2 
            }
        } while (posCheck != 0);
        t--;
        i++;
    }
}

void colisionTest(LACOBRA *cobra, LACOBRA *papa, int *inicio, int *fim, int *tam, int *coli, int *score, float b1x, float b1y, float b2x, float b2y, Sound *ifila, Sound *rfila ) {
    /*  Testa se a posição do elemento da cabeça (<cobra[inicio]>) é igual a alguma das
    *   posições de algum dos elementos do corpo da cobra. Se for, indica uma colisão.
    *   Atualmente o indicativo de colisão é mudar a variavel <colision> pra 1.
    *   Também testa se houve colisao com alguma comida. Se a comida for da mesma cor da 
    *   cabeça, chama a funçao removeFila. Se for diferente chama a funçao insertFila
    *
    *   OBS/TODO: A titulo de teste, a deteccão de colisão tá sendo testada pra que, ao
    *   retornar 1, o programa imprima na tela uma mensagem de colisão. A titulo de teste,
    *   ele vai manter impresso na tela mesmo se não estiver mais em colisão. Por isso essa
    *   função recebe a variavel que controla colisão e a retorna do jeito que ela está
    *   caso não perceba colisão. Isso serve para retornar 1 caso tenha acontecido alguma
    *   colisão no passado.
    */
    int i = (*inicio) + 1, cont = 1;
    while (cont < (*tam)) {
        if (i == TAMANHOMAX) i = 0;
        if ((cobra[(*inicio)].pos.x == cobra[i].pos.x) && (cobra[(*inicio)].pos.y == cobra[i].pos.y)) {
            (*coli) = 1; // colisão retorna 1
            return;
        }
        i++;
        cont++;
    }
    if (((cobra[(*inicio)].pos.x >= b1x) && (cobra[(*inicio)].pos.x <= (b1x + 240))) && ((cobra[(*inicio)].pos.y >= b1y) && (cobra[(*inicio)].pos.y <= (b1y + 240)))) {
        (*coli) = 1;
        return;
    }
    if (((cobra[(*inicio)].pos.x >= b2x) && (cobra[(*inicio)].pos.x <= (b2x + 240))) && ((cobra[(*inicio)].pos.y >= b2y) && (cobra[(*inicio)].pos.y <= (b2y + 240)))) {
        (*coli) = 1;
        return;
    }

    for (i = 0; i < MAXCOMIDA; i++) {
        if ((cobra[(*inicio)].pos.x == papa[i].pos.x) && (cobra[(*inicio)].pos.y == papa[i].pos.y)) {
            if (papa[i].colorInd == cobra[(*inicio)].colorInd) {
                PlaySound((*rfila));
                removeFila(cobra, inicio, fim, tam);
            }
            else {
                (*score) += (*tam);
                PlaySound((*ifila));
                insertFila(cobra, inicio, fim, tam, papa[i].cor, papa[i].colorInd);
            }
            createPapa(papa, cobra, (*inicio), (*tam));
            break;
        }
    }
}
void gameOver(Sound *songg) {
    SetTargetFPS(15);
    int gameOverInd = 0;
    Color gameOverColor = (Color){255, 0, 0, 255};
    Texture2D gameOverBG = LoadTexture("resources/gameOverBack.png");
    while (!WindowShouldClose()) { 
        if (!IsSoundPlaying((*songg))) PlaySound((*songg));
        BeginDrawing();
            ClearBackground(GetColor(0x052c46ff));
            DrawTextureEx(gameOverBG, (Vector2){ 0.0f, 0 }, 0.0f, 1.0f, WHITE);
            DrawText("GAME OVER", 170, 270, 100, gameOverColor);
            if (gameOverInd == 0) {
                gameOverColor = (Color){255, 0, 0, 255};
                gameOverInd = 1;
            } else {
                gameOverColor = (Color){0, 0, 0, 255};
                gameOverInd = 0;
            }
            DrawText("pressione ESC para sair", 20, 570, 20, BLACK);
        EndDrawing();
    }
    UnloadTexture(gameOverBG);
    StopSound((*songg));
}

int gameMenu(int *dif, Sound *songg)
{   

    
    int screenWidth = 1100;
    int screenHeight = 600;
    
    //Sound menu = LoadSound(" xxx Musiquinha do Menu xxx");

    Sound fxButton = LoadSound("resources/buttonfx.wav");   // Som ao pressionar botao

    Texture2D menuBackground = LoadTexture("resources/menuBackground.png");         // Textura do botaoFacil
    Texture2D buttonFacil = LoadTexture("resources/buttonFacil.png");               // Textura do botaoFacil
    Texture2D buttonMedio = LoadTexture("resources/buttonMedio.png");               // Textura do botaoMedio
    Texture2D buttonDificil = LoadTexture("resources/buttonDificil.png");           // Textura do botaoDificil
    Texture2D placaMenu = LoadTexture("resources/Menu.png");                        // Textura do menu

    //PlaySound(menu);
    
    Rectangle sourceMenuBackground = {0, 0, menuBackground.width, menuBackground.height};                     // Define frame do background do menu
    Rectangle sourceRecFacil = {0, 0, buttonFacil.width, buttonFacil.height};               // Define frame do botao Facil
    Rectangle sourceRecMedio = { 0, 0, buttonMedio.width, buttonMedio.height };             // Define frame do botao Medio
    Rectangle sourceRecDificil = { 0, 0, buttonDificil.width, buttonDificil.height };       // Define frame do botao Dificil
    Rectangle sourceMenu = { 0, 0, placaMenu.width, placaMenu.height };                     // Define frame do menu

    // Define button bounds on screen
    Rectangle btnBoundsFacil = { screenWidth/4 - buttonMedio.width/2, screenHeight/2 - buttonFacil.height , buttonFacil.width, buttonFacil.height };
    Rectangle btnBoundsMedio = { screenWidth/4 - buttonMedio.width/2, screenHeight/2, buttonMedio.width, buttonMedio.height };
    Rectangle btnBoundsDificil = { screenWidth/4 - buttonMedio.width/2, screenHeight/2 + buttonDificil.height, buttonDificil.width, buttonDificil.height };    
    Rectangle placaBoundsMenu = { screenWidth/2- placaMenu.width/2, screenHeight/6 - placaMenu.height/2, placaMenu.width, placaMenu.height };

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (!IsSoundPlaying((*songg))) PlaySound((*songg));
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();
        btnAction = false;

        // Check button state
        if (CheckCollisionPointRec(mousePoint, btnBoundsFacil))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                SetTargetFPS(20);
                StopSound((*songg));
                btnAction = true;
            } 
        }

        if (CheckCollisionPointRec(mousePoint, btnBoundsMedio))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                SetTargetFPS(50);
                StopSound((*songg));
                btnAction = true;
            }
        }

        if (CheckCollisionPointRec(mousePoint, btnBoundsDificil))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                SetTargetFPS(90);
                (*dif) = 1;
                StopSound((*songg));
                btnAction = true;
            }
        }
        else btnState = 0;

        if (btnAction)
        {
            PlaySound(fxButton);

            return 1;
        }

        BeginDrawing();

            ClearBackground(DARKGRAY);

            DrawTextureRec(menuBackground, sourceMenuBackground, (Vector2){ 0, 0 }, WHITE); // Draw button frame
            DrawTextureRec(buttonFacil, sourceRecFacil, (Vector2){ btnBoundsFacil.x, btnBoundsFacil.y }, WHITE); // Draw button frame
            DrawTextureRec(buttonMedio, sourceRecMedio, (Vector2){ btnBoundsMedio.x, btnBoundsMedio.y }, WHITE); // Draw button frame
            DrawTextureRec(buttonDificil, sourceRecDificil, (Vector2){ btnBoundsDificil.x, btnBoundsDificil.y }, WHITE); // Draw button frame
            DrawTextureRec(placaMenu, sourceMenu, (Vector2){ placaBoundsMenu.x, placaBoundsMenu.y }, WHITE); // Draw button frame

        EndDrawing();        
    }
    UnloadTexture(menuBackground);
    UnloadTexture(buttonFacil);
    UnloadTexture(buttonMedio);  
    UnloadTexture(buttonDificil);  
    UnloadTexture(placaMenu);
    UnloadSound(fxButton);
}

