#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define ARR_LEN 1024

struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};

struct Person {
    char Surname[90];
    char Name[90];
};

struct ChessGame 
{
    int id;
    struct Person PlayerFioBlack;
    struct Person PlayerFioWhite;
    char DebutName[90];
    int Result;
    int TimeSpent;
    int Score;
};

void Init();
void adjustWindowSize();
void MainLogic();


void AddRecord();
void PrintAllGames();
void FindRecord();
void RemoveRecord();


void PrintBestPlayers();
void PrintLongerDebutByName();


struct ChessGame *_chessGames;


int main(void)
{
    //Не работал русский язык. Исправил. 1251
    //strcpy - Скопировать
    //strcat - Добавить
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char *locale = setlocale(LC_ALL, "");



    return;

    Init();
    MainLogic();

    printf("\nКонец программы.\n");

    return 0;
}

void Init() 
{
    //Screen size
    adjustWindowSize();

    _chessGames = (struct ChessGame*)malloc(sizeof(struct ChessGame) * ARR_LEN);

    for (int i = 0; i < ARR_LEN; i++)
    {
        _chessGames[i].id = -1;
    }

}

void adjustWindowSize()
{
    struct SMALL_RECT test;

    HANDLE hStdout;
    COORD coord;
    BOOL ok;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 200;
    coord.Y = 30;
    ok = SetConsoleScreenBufferSize(hStdout, coord);

    test.Left = 0;
    test.Top = 0;
    test.Right = coord.X - 1;
    test.Bottom = coord.Y - 1;

    SetConsoleWindowInfo(hStdout, ok, &test);

}


void MainLogic() {

    while(1)
    {
        printf("\nГлавное меню\n");

        printf("1. Вывести все партии\n");
        printf("2. Поиск партий\n");
        printf("3. Добавление новой партии\n");
        printf("4. Удаление партии\n");
        printf("5. Вывести 3-ёх игроков с наибольшим количеством очков\n");
        printf("6. Вывести наиболее долгии партии по наименованию дебюта\n");
        
        printf("\n");

        printf("-1: Выход\n");

        printf("\n");

        printf("Выбор: ");
        int userSelect;
        scanf("%d", &userSelect);

        printf("Пользователь выбрал: %d\n", userSelect);

        switch (userSelect) {

            case -1:
                return;

            case 1: 
                PrintAllGames();
                break;
            case 2:
                FindRecord();
                break;
            case 3:
                AddRecord();
                break;
            case 4:
                RemoveRecord();
                break;
            case 5:
                PrintBestPlayers();
                break;
            case 6:
                PrintLongerDebutByName();
                break;

            default:
                printf("Такого выбора нету. Попробуйте другой!\n");
                break;
        }

    }

}


void AddRecord() {

    struct ChessGame chessGame;

    chessGame.Result = -1;
    chessGame.TimeSpent = -1;
    chessGame.Score = -1;
    chessGame.id = -1;

    printf("Фамилия игрока за белую сторону: ");
    scanf("%s", chessGame.PlayerFioWhite.Surname);

    printf("Имя игрока за белую сторону: ");
    scanf("%s", chessGame.PlayerFioWhite.Name);

    printf("Фамилия игрока за черную сторону: ");
    scanf("%s", chessGame.PlayerFioBlack.Surname);

    printf("Имя игрока за черную сторону: ");
    scanf("%s", chessGame.PlayerFioBlack.Name);

    printf("Название дебюта: ");
    //scanf("%s%s", &f, &s);
    getchar();
    gets(chessGame.DebutName);

    
    while (chessGame.Result == -1)
    {
        int result;
        printf("Результат матча (0 - победа белых, 1 - победа черных, 2 - ничья): ");
        scanf("%d", &result);

        if (result >= 0 && result <= 2) 
        {
            chessGame.Result = result;
        }
        else 
        {
            printf("Вы выбрали не правильный результат. Будьте внимательнее и попробуйте ещё раз!\n");
        }
    }

    while (chessGame.TimeSpent == -1)
    {
        int result;
        printf("Длительность партии(в секундах): ");
        scanf("%d", &result);
        if (result > 0)
        {
            chessGame.TimeSpent = result;
        }
        else
        {
            printf("Вы ввели плохие данные. Будьте внимательнее и попробуйте ещё раз!\n");
        }
    }

    while (chessGame.Score == -1)
    {
        int result;
        printf("Количество очков: ");
        scanf("%d", &result);
        if (result > 0)
        {
            chessGame.Score = result;
        }
        else
        {
            printf("Вы ввели плохие данные. Будьте внимательнее и попробуйте ещё раз!\n");
        }
    }

    for (int i = 0; i < ARR_LEN; i++) 
    {
        if (_chessGames[i].id == -1) 
        {
            chessGame.id = (i + 1);

            _chessGames[i] = chessGame;

            printf("Запись добавлена под номером %d\n", _chessGames[i].id);
            return;
        }
    }

}

void PrintAllGames() {

    printf("\n");
    printf("|%-3s||%-20s||%-30s||%-20s||%-30s||%-45s||%-20s||%-5s||%-5s|\n", "ID", "Имя игрока белых", "Фам. игрока белых", "Имя игрока черных", "Фам. игрока черных", "Назв. дебюта", "Результат", "Время", "Очки");

    for (int i = 0; i < ARR_LEN; i++)
    {
        if(_chessGames[i].id != -1)
            printf("|%-3d||%-20s||%-30s||%-20s||%-30s||%-45s||%-20d||%-5d||%-5d|\n", 
                _chessGames[i].id, 
                _chessGames[i].PlayerFioWhite.Name, _chessGames[i].PlayerFioWhite.Surname, 
                _chessGames[i].PlayerFioBlack.Name, _chessGames[i].PlayerFioBlack.Surname,
                _chessGames[i].DebutName,
                _chessGames[i].Result,
                _chessGames[i].TimeSpent,
                _chessGames[i].Score);
    }

    printf("\n");

}

void FindRecord() {

}

void RemoveRecord() {

}

void PrintBestPlayers() {

}

void PrintLongerDebutByName() {

}


// Условия:
//  1. Хранение в структурах
//  2. Массив структур
//  3. Создание новых записей из консоли
//  4. Вывод на экран в табличном виде (Как я понял, даже при поиске)
//  5. Поиск записей (Нужно определить по каким параметрам?)
//  6. Удаление записи из списка
//  7. Выбор действий должен производиться в диалоговом режиме
//
// Задача:
//  1. Файл, строки. Строка: Фамилия и имя шахматистов, исход партии, время затраченное на партию, название дебюта [OK]
//  2. Поиск трёх игроков с наибольшим количеством набранных очков
//  3. Наиболее долгая партия по заданной подстроке наименования дебюта. (Поиск по названию дебюта)