// XO.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool IfXWin(char* positions)
{
    return ((positions[0] == 'X' && positions[1] == 'X' && positions[2] == 'X') || (positions[0] == 'X' && positions[3] == 'X' && positions[6] == 'X')
        || (positions[1] == 'X' && positions[4] == 'X' && positions[7] == 'X') || (positions[2] == 'X' && positions[5] == 'X' && positions[8] == 'X')
        || (positions[0] == 'X' && positions[4] == 'X' && positions[8] == 'X') || (positions[2] == 'X' && positions[4] == 'X' && positions[6] == 'X')
        || (positions[0] == 'X' && positions[3] == 'X' && positions[6] == 'X') || (positions[3] == 'X' && positions[4] == 'X' && positions[5] == 'X')
        || (positions[6] == 'X' && positions[7] == 'X' && positions[8] == 'X'));
}
bool IfOWin(char* positions)
{
    return ((positions[0] == 'O' && positions[1] == 'O' && positions[2] == 'O') || (positions[0] == 'O' && positions[3] == 'O' && positions[6] == 'O')
        || (positions[1] == 'O' && positions[4] == 'O' && positions[7] == 'O') || (positions[2] == 'O' && positions[5] == 'O' && positions[8] == 'O')
        || (positions[0] == 'O' && positions[4] == 'O' && positions[8] == 'O') || (positions[2] == 'O' && positions[4] == 'O' && positions[6] == 'O')
        || (positions[0] == 'O' && positions[3] == 'O' && positions[6] == 'O') || (positions[3] == 'O' && positions[4] == 'O' && positions[5] == 'O')
        || (positions[6] == 'O' && positions[7] == 'O' && positions[8] == 'O'));
}

bool gameOver = false;
int Input()
{
    int num;
    cin >> num;
    if (num == 0)
        gameOver = true;
    return num;
}

class Game
{
public:
    Game()
    {
        PointX = 0;
        PointY = 0;
        FieldHeight = 24;
        FieldWidth = 48;
        SetPositions();
        Draw();
    }
    void TurnX()
    {
        cout << "0, чтобы покинуть игру\n";
        cout << "Введите цифру от 1 до 9, чтобы выбрать клетку для X:\n";
        int num = Input();
        if (num > 0) {
            positions[num - 1] = 'X';
            Draw();
        }
        WinLogic();
    }
    void TurnO()
    {
        cout << "0, чтобы покинуть игру\n";
        cout << "Введите цифру от 1 до 9, чтобы выбрать клетку для O:\n";
        int num = Input();
        if (num > 0) {
            positions[num - 1] = 'O';
            Draw();
        }
        WinLogic();
    }
private:
    int PointX;
    int PointY;
    int FieldHeight;
    int FieldWidth;
    int position_count = 0;
    vector <pair<int, int>> default_positions;
    char positions[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    void SetPositions()
    {
        int y = FieldHeight / 3 / 2;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
            {
                if (j == 0) {
                    default_positions.push_back({ FieldWidth / 3 / 2, y });
                    continue;
                }
                default_positions.push_back({ default_positions[j - 1].first + (FieldWidth / 3), y });
            }
            y += FieldHeight / 3;
        }
    }
    void Draw()
    {
        system("cls");
        while (PointY <= FieldHeight)
        {
            if (PointY % (FieldHeight/3)  == 0)
            {
                cout << "#";
            }

            if (PointX % (FieldWidth / 3) == 0 && PointY % (FieldHeight / 3) != 0)
            {
                cout << "#";
            }
            else if (count_if(default_positions.begin(), default_positions.end(), [this](pair<int, int> def_pos)
                {
                    pair <int, int> pair = make_pair(PointX, PointY);
                    return pair == def_pos;
                })>0)
            {
                cout<<positions[position_count];
                position_count++;
            }
            else if (PointY % (FieldHeight / 3) != 0)
            {
                cout << " ";
            }

            if (PointX < FieldWidth)
            {
                PointX++;
            }
            else {
                PointY++;
                PointX = 0;
                cout << endl;
            }
        }
        PointY = 0;
        PointX = 0;
        position_count = 0;
    }
    void WinLogic()
    {
        if (IfXWin(positions) && !gameOver)
        {
            cout << "Крестики победили!" << endl;
            gameOver = true;
        }
        if (IfOWin(positions) && !gameOver)
        {
            cout << "Нолики победили!" << endl;
            gameOver = true;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Game newgame;
    while (!gameOver)
    {
        newgame.TurnX();
        if (!gameOver)
            newgame.TurnO();
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


