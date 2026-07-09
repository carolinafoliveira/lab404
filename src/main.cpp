#include "raylib.h"
#include <string>

using namespace std;

int main()
{
    const int larguraTela = 900;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Lab 404 - Demo Academica");
    SetTargetFPS(60);

    Rectangle jogador = {100, 450, 35, 45};
    Rectangle professor = {420, 250, 40, 50};
    Rectangle bug = {700, 430, 40, 40};

    float velocidade = 4.0f;

    bool missaoAtiva = false;
    bool bugDerrotado = false;
    bool mostrarDialogo = false;

    string dialogo = "Prof. Josivan: Bem-vinda ao Lab 404!";

    while (!WindowShouldClose())
    {
        // Movimento do jogador
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) jogador.y -= velocidade;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) jogador.y += velocidade;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) jogador.x -= velocidade;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) jogador.x += velocidade;

        // Limites da tela
        if (jogador.x < 20) jogador.x = 20;
        if (jogador.y < 100) jogador.y = 100;
        if (jogador.x + jogador.width > larguraTela - 20) jogador.x = larguraTela - 20 - jogador.width;
        if (jogador.y + jogador.height > alturaTela - 20) jogador.y = alturaTela - 20 - jogador.height;

        bool pertoProfessor = CheckCollisionRecs(jogador, professor);
        bool pertoBug = CheckCollisionRecs(jogador, bug);

        // Conversa com professor
        if (pertoProfessor && IsKeyPressed(KEY_E))
        {
            mostrarDialogo = true;

            if (!missaoAtiva)
            {
                missaoAtiva = true;
                dialogo = "Prof. Josivan: O sistema apresentou um erro.\nEncontre o Bug.exe e corrija o problema.";
            }
            else if (bugDerrotado)
            {
                dialogo = "Prof. Josivan: Muito bem!\nConceito desbloqueado: a CPU executa instrucoes.";
            }
            else
            {
                dialogo = "Prof. Josivan: O Bug.exe ainda esta ativo.\nChegue perto dele e pressione ESPACO.";
            }
        }

        // Atacar Bug
        if (missaoAtiva && !bugDerrotado && pertoBug && IsKeyPressed(KEY_SPACE))
        {
            bugDerrotado = true;
            mostrarDialogo = true;
            dialogo = "Sistema: Bug.exe corrigido!\nVolte ao Prof. Josivan.";
        }

        BeginDrawing();
        ClearBackground(Color{230, 230, 235, 255});

        // Cabeçalho
        DrawRectangle(0, 0, larguraTela, 90, Color{20, 25, 45, 255});
        DrawText("LAB 404", 30, 20, 34, WHITE);

        if (!missaoAtiva)
            DrawText("Missao: converse com o Prof. Josivan", 30, 60, 18, YELLOW);
        else if (!bugDerrotado)
            DrawText("Missao: encontre e corrija o Bug.exe", 30, 60, 18, YELLOW);
        else
            DrawText("Missao: volte ao Prof. Josivan", 30, 60, 18, GREEN);

        // Cenário simples do laboratório
        DrawRectangle(60, 130, 140, 55, BROWN);
        DrawText("PC", 110, 148, 22, WHITE);

        DrawRectangle(260, 130, 140, 55, BROWN);
        DrawText("PC", 310, 148, 22, WHITE);

        DrawRectangle(600, 130, 140, 55, BROWN);
        DrawText("PC", 650, 148, 22, WHITE);

        DrawRectangle(360, 310, 180, 40, DARKBROWN);
        DrawText("Mesa", 420, 318, 20, WHITE);

        DrawRectangle(760, 140, 60, 120, DARKGRAY);
        DrawText("Servidor", 730, 270, 18, BLACK);

        // Professor
        DrawRectangleRec(professor, BLACK);
        DrawText("Josivan", professor.x - 10, professor.y - 22, 16, BLACK);

        // Jogador
        DrawRectangleRec(jogador, BLUE);
        DrawText("Player", jogador.x - 8, jogador.y - 22, 16, BLACK);

        // Bug
        if (!bugDerrotado)
        {
            DrawRectangleRec(bug, RED);
            DrawText("Bug.exe", bug.x - 10, bug.y - 22, 16, BLACK);
        }

        // Dicas de interação
        if (pertoProfessor)
            DrawText("[E] Conversar", 360, 560, 22, DARKBLUE);

        if (pertoBug && !bugDerrotado)
            DrawText("[ESPACO] Corrigir Bug", 330, 560, 22, RED);

        // Caixa de diálogo
        if (mostrarDialogo)
        {
            DrawRectangle(70, 390, 760, 120, Color{15, 20, 40, 245});
            DrawRectangleLines(70, 390, 760, 120, WHITE);
            DrawText(dialogo.c_str(), 100, 420, 22, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}