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
    //�� ������� ������� ����. ��������. 1251
    //strcpy - �����������
    //strcat - ��������
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

    printf("\n����� ���������.\n");

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
        printf("\n������� ����\n");

        printf("1. ������� ��� ������\n");
        printf("2. ����� ������\n");
        printf("3. ���������� ����� ������\n");
        printf("4. �������� ������\n");
        printf("5. ������� 3-�� ������� � ���������� ����������� �����\n");
        printf("6. ������� �������� ������ ������ �� ������������ ������\n");
        printf("7. ���������\n");
        printf("8. ���������\n");
        
        printf("\n");

        printf("-1: �����\n");

        printf("\n");

        printf("�����: ");
        int userSelect;
        scanf("%d", &userSelect);

        printf("������������ ������: %d\n", userSelect);

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
                printf("������ ������ ����. ���������� ������!\n");
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

    printf("������� � ��� ������ �� ����� �������: ");
    fgets(chessGame.PlayerFioWhite, (sizeof(chessGame.PlayerFioWhite) / sizeof(chessGame.PlayerFioWhite[0])), stdin);
    RemoveNL(chessGame.PlayerFioWhite);

    printf("������� � ��� ������ �� ������ �������: ");
    fgets(chessGame.PlayerFioBlack, (sizeof(chessGame.PlayerFioBlack) / sizeof(chessGame.PlayerFioBlack[0])), stdin);
    RemoveNL(chessGame.PlayerFioBlack);

    printf("�������� ������: ");
    fgets(chessGame.DebutName, (sizeof(chessGame.DebutName) / sizeof(chessGame.DebutName[0])), stdin);
    RemoveNL(chessGame.DebutName);

    
    while (chessGame.Result == -1)
    {
        int result;
        printf("��������� ����� (0 - ������ �����, 1 - ������ ������, 2 - �����): ");
        scanf("%d", &result);

        if (result >= 0 && result <= 2) 
        {
            chessGame.Result = result;
        }
        else 
        {
            printf("�� ������� �� ���������� ���������. ������ ������������ � ���������� ��� ���!\n");
        }
    }

    while (chessGame.TimeSpent == -1)
    {
        int result;
        printf("������������ ������(� �������): ");
        scanf("%d", &result);
        if (result > 0)
        {
            chessGame.TimeSpent = result;
        }
        else
        {
            printf("�� ����� ������ ������. ������ ������������ � ���������� ��� ���!\n");
        }
    }

    while (chessGame.Score == -1)
    {
        int result;
        printf("���������� �����: ");
        scanf("%d", &result);
        if (result > 0)
        {
            chessGame.Score = result;
        }
        else
        {
            printf("�� ����� ������ ������. ������ ������������ � ���������� ��� ���!\n");
        }
    }

    for (int i = 0; i < ARR_LEN; i++) 
    {
        if (_chessGames[i].id == -1) 
        {
            chessGame.id = (i + 1);

            _chessGames[i] = chessGame;

            printf("������ ��������� ��� ������� %d\n", _chessGames[i].id);
            return;
        }
    }

}

void PrintAllGames() {

    printf("\n");
    printf("|%-3s||%-25s||%-25s||%-25s||%-10s||%-5s||%-5s|\n", "ID", "���. � ��� ������ �����", "���. � ��� ������ ������", "����. ������", "���������", "�����", "����");

    for (int i = 0; i < ARR_LEN; i++)
    {
        if (_chessGames[i].id == -1) continue;

        PrintGame(&_chessGames[i]);
    }

    printf("\n");
}

void FindRecord() {

    int choice = -1;

    printf("����� ����� �����?\n");
    printf("1. ����� ��� ������� � ���������� ���-��� ��������� �����\n");
    printf("2. ����� �������� ������ ������ �� ������������ ������\n");

    printf("����� ������ �����. ����\n");

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
    printf("�������� ID ��� ��������: ");
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

    //���������� ���������
    for (int i = 0; i < ARR_LEN - 1; i++) {
        // ���������� ��� �������� ��������.
        for (int j = 0; j < ARR_LEN - i - 1; j++)
        {
            //���� ������� � '�������� � ��������' �� '�������� � ��������' ����� ���� < �� > � ��������
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
    printf("|%-3s||%-25s||%-25s||%-25s||%-10s||%-5s||%-5s|\n", "ID", "���. � ��� ������ �����", "���. � ��� ������ ������", "����. ������", "���������", "�����", "����");

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

    printf("������� ��������� ������������ ������: ");
    
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
        printf("������ �� �������!");
        return;
    }

    //���������� ���������
    for (int i = 0; i < length - 1; i++) {
        // ���������� ��� �������� ��������.
        for (int j = 0; j < length - i - 1; j++) 
        {
            //���� ������� � '�������� � ��������' �� '�������� � ��������' ����� ���� < �� > � ��������
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
    printf("|%-3s||%-25s||%-25s||%-25s||%-10s||%-5s||%-5s|\n", "ID", "���. � ��� ������ �����", "���. � ��� ������ ������", "����. ������", "���������", "�����", "����");

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
            chessGameText = strtok(NULL, ";"); //��������� �� ������

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
        //�����
    case 0:
        strcpy(gameResultText, "�����");
        break;

        //������
    case 1:
        strcpy(gameResultText, "������");
        break;

        //�����
    case 2:
        strcpy(gameResultText, "�����");
        break;

        //���-�� ����� �������
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


// �������:
//  1. �������� � ���������� [OK]
//  2. ������ �������� [OK]
//  3. �������� ����� ������� �� ������� [OK]
//  4. ����� �� ����� � ��������� ���� (��� � �����, ���� ��� ������) [OK]
//  5. ����� ������� (����� ���������� �� ����� ����������?)
//  6. �������� ������ �� ������ [OK]
//  7. ����� �������� ������ ������������� � ���������� ������ [OK]
//
// ������:
//  1. ����, ������. ������: ������� � ��� �����������, ����� ������, ����� ����������� �� ������, �������� ������ [OK]
//  2. ����� ��� ������� � ���������� ����������� ��������� �����
//  3. �������� ������ ������ �� �������� ��������� ������������ ������. (����� �� �������� ������)