#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define ARR_LEN 1024
#define CHAR_LEN 25
#define FILE_NAME "ChessGames.txt"

struct tChessGame 
{
    int id;
    char PlayerFioBlack[CHAR_LEN];
    char PlayerFioWhite[CHAR_LEN];
    char DebutName[CHAR_LEN];
    int Result;
    int TimeSpent;
    int Score;
};

typedef struct tChessGame ChessGame;

void Init();
void MainLogic();


void AddRecord();
void PrintAllGames();
void FindRecord();
void RemoveRecord();


void PrintBestPlayers();
void PrintLongerDebutByName();

void RemoveNL(char* msg);
void Save();
void Load();

void PrintGame(ChessGame* game);
char* IntToStr(const int* number);
void SetGame(ChessGame* to, ChessGame* from);

ChessGame *_chessGames;

int main(void)
{
    //Не работал русский язык. Исправил. 1251
    //strcpy - Скопировать
    //strcat - Добавить
    //strtok - split C#
    //strstr - contains
    //void* ptr
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char *locale = setlocale(LC_ALL, "");

    int* intes = (int*)malloc(sizeof(int) * 3);



    //intes[0] = 12;
    *(intes + 1) = 14;
    intes[1] = 25;
    intes[2] = 4;

    //ChessGame** pGames = (ChessGame**)malloc(sizeof(ChessGame) * 20);

    //games[0].id = 3;
    //games[0].Result = 333;
    //games[0].TimeSpent = 999;

    //pGames[0] = &games[0];

    //printf("%d, %d, %d", (*pGames[0]).id, (*pGames[0]).Result, (*pGames[0]).TimeSpent);

    //free(games);
    //free(pGames);

    //void* ptr = games;

    //strcpy(words, "Hello!");

    //char str[] = "Example text check need";

    //printf("%s\n", str);

    //char* p = strstr(str, "e");

    //printf("%s", p);

    //int** pptrInt = &intes;
    ////**pptrInt++;

    //printf("%d: %p\n", *(**&pptrInt + 1), **&pptrInt + 1);

    //for (int i = 0; i < 3; i++)
    //{
    //    printf("Int: %d, P: %p\n", intes[i], &intes[i]);
    //}

    //intes

    //printf("%p : %p", intes[0], pptrInt);
    
    //return 0;

    Init();
    Load();
    MainLogic();

    printf("\nКонец программы.\n");

    return 0;
}

void Init() 
{
    _chessGames = malloc(sizeof(ChessGame) * ARR_LEN);

    for (int i = 0; i < ARR_LEN; i++)
    {
        _chessGames[i].id = -1;
    }

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
        printf("7. Сохранить\n");
        printf("8. Загрузить\n");
        
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
            case 7:
                Save();
                break;
            case 8:
                Load();
                break;

            default:
                printf("Такого выбора нету. Попробуйте другой!\n");
                break;
        }

    }

}


void AddRecord() {

    ChessGame chessGame;

    chessGame.Result = -1;
    chessGame.TimeSpent = -1;
    chessGame.Score = -1;
    chessGame.id = -1;

    getchar();

    printf("Фамилия и имя игрока за белую сторону: ");
    fgets(chessGame.PlayerFioWhite, (sizeof(chessGame.PlayerFioWhite) / sizeof(chessGame.PlayerFioWhite[0])), stdin);
    RemoveNL(chessGame.PlayerFioWhite);

    printf("Фамилия и имя игрока за черную сторону: ");
    fgets(chessGame.PlayerFioBlack, (sizeof(chessGame.PlayerFioBlack) / sizeof(chessGame.PlayerFioBlack[0])), stdin);
    RemoveNL(chessGame.PlayerFioBlack);

    printf("Название дебюта: ");
    fgets(chessGame.DebutName, (sizeof(chessGame.DebutName) / sizeof(chessGame.DebutName[0])), stdin);
    RemoveNL(chessGame.DebutName);

    
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
        printf("Длительность партии(в минутах): ");
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
    printf("|%-3s||%-25s||%-25s||%-25s||%-10s||%-5s||%-5s|\n", "ID", "Фам. и имя игрока белых", "Фам. и имя игрока черных", "Назв. дебюта", "Результат", "Время", "Очки");

    for (int i = 0; i < ARR_LEN; i++)
    {
        if (_chessGames[i].id == -1) continue;

        PrintGame(&_chessGames[i]);
    }

    printf("\n");
}

void FindRecord() {

    int choice = -1;

    printf("Какой поиск будет?\n");
    printf("1. Поиск трёх игроков с наибольшим кол-вом набранных очков\n");
    printf("2. Поиск наиболее долгой партии по наименованию дебюта\n");

    printf("Любое другое число. Уйти\n");

    scanf("%d", &choice);

    switch (choice) 
    {
        case 1: 
            PrintBestPlayers();
            break;

        case 2:
            PrintLongerDebutByName();
            break;

        default: return;
    }

}

void RemoveRecord() {

    int id = -1;
    printf("Выберите ID для удаления: ");
    scanf("%d", &id);
    if (id <= -1) return;

    _chessGames[id - 1].id = -1;

}

void PrintBestPlayers() 
{
    ChessGame** games = malloc(sizeof(ChessGame*) * ARR_LEN);

    for (int i = 0; i < ARR_LEN; i++)
    {
        games[i] = &_chessGames[i];
    }

    //Сортировка пузырьком
    for (int i = 0; i < ARR_LEN - 1; i++) {
        // сравниваем два соседних элемента.
        for (int j = 0; j < ARR_LEN - i - 1; j++)
        {
            //Чтоб сменить с 'большего к меньшему' на 'меньшего к большему' смени знак < на > и наоборот
            if ((*(games[j])).Score < (*(games[j + 1])).Score)
            {
                ChessGame* temp = NULL;
                temp = games[j];
                games[j] = games[j + 1];
                games[j + 1] = temp;
            }
        }
    }

    printf("\n");
    printf("|%-3s||%-25s||%-25s||%-25s||%-10s||%-5s||%-5s|\n", "ID", "Фам. и имя игрока белых", "Фам. и имя игрока черных", "Назв. дебюта", "Результат", "Время", "Очки");

    for (int i = 0; i < 3; i++)
    {
        PrintGame(&*games[i]);
    }

    free(games);
}

void PrintLongerDebutByName() 
{
    ChessGame** games = NULL;
    int length = 0;
    char nameDeb[CHAR_LEN];

    printf("Введите подстроку наименования дебюта: ");
    
    scanf("%s", nameDeb);

    for (int i = 0; i < ARR_LEN; i++)
    {
        if (_chessGames[i].id == -1) continue;
        if ((strstr(_chessGames[i].DebutName, nameDeb)) == NULL) continue;
        length++;
        
        games = realloc(games, sizeof(ChessGame*) * length);
        games[length - 1] = &_chessGames[i];
    }

    if (length == 0) 
    {
        printf("Ничего не найдено!");
        return;
    }

    //Сортировка пузырьком
    for (int i = 0; i < length - 1; i++) {
        // сравниваем два соседних элемента.
        for (int j = 0; j < length - i - 1; j++) 
        {
            //Чтоб сменить с 'большего к меньшему' на 'меньшего к большему' смени знак < на > и наоборот
            if ((*(games[j])).TimeSpent < (*(games[j + 1])).TimeSpent)
            {
                ChessGame* temp = NULL;
                temp = games[j];
                games[j] = games[j + 1];
                games[j + 1] = temp;
            }
        }
    }

    printf("\n");
    printf("|%-3s||%-25s||%-25s||%-25s||%-10s||%-5s||%-5s|\n", "ID", "Фам. и имя игрока белых", "Фам. и имя игрока черных", "Назв. дебюта", "Результат", "Время", "Очки");

    for (int i = 0; i < length; i++)
    {
        PrintGame(&*games[i]);
    }

    free(games);
}

void RemoveNL(char* msg) {
    msg[strcspn(msg, "\n\r")] = 0;
}

void Save() 
{
    FILE* file = fopen(FILE_NAME, "w");

    for (int i = 0; i < ARR_LEN; i++)
    {
        if (_chessGames[i].id == -1) continue;

        char txtSave[150];

        strcpy(txtSave, _chessGames[i].PlayerFioWhite);
        strcat(txtSave, ";");

        strcat(txtSave, _chessGames[i].PlayerFioBlack);
        strcat(txtSave, ";");

        strcat(txtSave, _chessGames[i].DebutName);
        strcat(txtSave, ";");

        strcat(txtSave, IntToStr(&_chessGames[i].Result));
        strcat(txtSave, ";");

        strcat(txtSave, IntToStr(&_chessGames[i].TimeSpent));
        strcat(txtSave, ";");

        strcat(txtSave, IntToStr(&_chessGames[i].Score));
        strcat(txtSave, ";");

        strcat(txtSave, "\n");

        fputs(txtSave, file);
    }

    fclose(file);
}

void Load() 
{
    FILE* file = fopen(FILE_NAME, "r");

    if (file == NULL) return;

    char text[150];

    for (int i = 0; i < ARR_LEN; i++)
    {
        _chessGames[i].id = -1;
    }

    while (fgets(text, 150, file) != NULL) 
    {
        RemoveNL(text);

        char* chessGameText = strtok(text, ";");
        
        for (int i = 0; i < ARR_LEN; i++)
        {
            if (_chessGames[i].id != -1) continue;

            _chessGames[i].id = (i + 1);
            strcpy(_chessGames[i].PlayerFioWhite, chessGameText);
            chessGameText = strtok(NULL, ";");
            strcpy(_chessGames[i].PlayerFioBlack, chessGameText);
            chessGameText = strtok(NULL, ";");
            strcpy(_chessGames[i].DebutName, chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].Result = atoi(chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].TimeSpent = atoi(chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].Score = atoi(chessGameText);
            chessGameText = strtok(NULL, ";"); //Обнуление на всякий

            break;
        }
        
    }

    fclose(file);
}

void PrintGame(ChessGame* game) 
{
    char gameResultText[7];
    switch (game->Result)
    {
        //Белые
    case 0:
        strcpy(gameResultText, "Белые");
        break;

        //Черные
    case 1:
        strcpy(gameResultText, "Черные");
        break;

        //Ничья
    case 2:
        strcpy(gameResultText, "Ничья");
        break;

        //Кто-то фигню написал
    default:
        strcpy(gameResultText, "None");
        break;
    }

    printf("|%-3d||%-25s||%-25s||%-25s||%-10s||%-5d||%-5d|\n",
        game->id,
        game->PlayerFioWhite,
        game->PlayerFioBlack,
        game->DebutName,
        gameResultText,
        game->TimeSpent,
        game->Score);
}

char* IntToStr(const int* number)
{
    char* numStr[15];

    sprintf(numStr, "%d", *number);

    return numStr;
}

void SetGame(ChessGame* to, ChessGame* from) 
{
    to->id = from->id;

    strcpy(to->PlayerFioWhite, from->PlayerFioWhite);
    strcpy(to->PlayerFioBlack, from->PlayerFioBlack);
    strcpy(to->DebutName, from->DebutName);
    
    to->Result = from->Result;
    to->TimeSpent = from->TimeSpent;
    to->Score = from->Score;
}


// Условия:
//  1. Хранение в структурах [OK]
//  2. Массив структур [OK]
//  3. Создание новых записей из консоли [OK]
//  4. Вывод на экран в табличном виде (Как я понял, даже при поиске) [OK]
//  5. Поиск записей (Нужно определить по каким параметрам?)
//  6. Удаление записи из списка [OK]
//  7. Выбор действий должен производиться в диалоговом режиме [OK]
//
// Задача:
//  1. Файл, строки. Строка: Фамилия и имя шахматистов, исход партии, время затраченное на партию, название дебюта [OK]
//  2. Поиск трёх игроков с наибольшим количеством набранных очков
//  3. Наиболее долгая партия по заданной подстроке наименования дебюта. (Поиск по названию дебюта)