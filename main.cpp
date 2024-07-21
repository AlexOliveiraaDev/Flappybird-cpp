#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h> // Para Sleep()
#include <conio.h>

using namespace std;

/*Configs do jogo*/
int linhas = 10;
int colunas = 20;
int gameSpeed = 300; // Valor em milessegundos para a próxima atualização

/*Personalização do jogo*/
char character = 'o';
char obstacle = '#';
char bg = '*';

/*Variaveis de Jogo*/
int characterLocation;

/*Matriz do grid*/
vector<vector<char>> grid(linhas, vector<char>(colunas, bg));

// y é o índice da linha
// x é o índice da coluna.

void Render(vector<vector<char>> grid)
{
    system("cls");
    for (auto &&y : grid)
    {
        for (auto &&x : y)
        {
            cout << x;
        }
        cout << endl;
    }
}

bool CheckInput()
{
    if (_kbhit())
    {
        char ch = _getch();
        ch = toupper(ch);
        if (ch == ' ')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void SpawnCharacter()
{
    characterLocation = linhas / 2;
    grid[characterLocation][1] = character;
}

void ApplyGravity()
{
    cout << CheckInput();
    if (CheckInput() == 0)
    {
        // cout << "++";
        grid[characterLocation][1] = bg;
        characterLocation++;
        grid[characterLocation][1] = character;
    }
    else
    {
        // cout << "--";
        grid[characterLocation][1] = bg;
        characterLocation--;
        grid[characterLocation][1] = character;
    }
    Sleep(300);
}

void HorizontalMovement()
{
    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid[y].size() - 1; x++)
        {
            grid[y][x] = grid[y][x + 1];
        }
    }
}

void SpawnObstacle()
{
    int altura = 3;
    // Obstaculo de cima
    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid[y].size(); x++)
        {
            if (x >= colunas - 4 && x != colunas - 1)
            {
                if (y <= (altura - 1))
                {
                    grid[y][x] = '%';
                }
            }
        }
    }

    // Obstaculo de baixo
    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid[y].size(); x++)
        {
            if (x >= colunas - 4 && x != colunas - 1)
            {
                if (y >= linhas - altura)
                {
                    grid[y][x] = '#';
                }
            }
        }
    }
}

int main()
{
    SpawnCharacter();
    SpawnObstacle();
    while (true)
    {
        ApplyGravity();
        Render(grid);

        Sleep(gameSpeed);
        HorizontalMovement();
    }

    // Render(grid);
}
