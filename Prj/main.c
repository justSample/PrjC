#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define ARR_LEN 1024
#define CHAR_LEN 25
#define FILE_NAME "ChessGames.txt"

struct stPerson {
    char Fio[CHAR_LEN];
    int Score;
};

typedef struct stPerson Person;

struct tChessGame 
{
    int id;
    Person PlayerBlack;
    Person PlayerWhite;
    char DebutName[CHAR_LEN];
    int Result;
    int TimeSpent;
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

void PrintTitle();
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

    chessGame.id = -1;

    chessGame.PlayerWhite.Score = -1;
    chessGame.PlayerBlack.Score = -1;

    chessGame.Result = -1;
    chessGame.TimeSpent = -1;

    getchar();

    printf("������� � ��� ������ �� ����� �������: ");
    fgets(chessGame.PlayerWhite.Fio, (sizeof(chessGame.PlayerWhite.Fio) / sizeof(chessGame.PlayerWhite.Fio[0])), stdin);
    RemoveNL(chessGame.PlayerWhite.Fio);

    while (chessGame.PlayerWhite.Score == -1)
    {
        int result;
        printf("���������� ����� ������ �� ����� �������: ");
        scanf("%d", &result);
        if (result > 0)
        {
            chessGame.PlayerWhite.Score = result;
        }
        else
        {
            printf("�� ����� ������ ������. ������ ������������ � ���������� ��� ���!\n");
        }
    }

    printf("������� � ��� ������ �� ������ �������: ");
    fgets(chessGame.PlayerBlack.Fio, (sizeof(chessGame.PlayerBlack.Fio) / sizeof(chessGame.PlayerBlack.Fio[0])), stdin);
    RemoveNL(chessGame.PlayerBlack.Fio);

    while (chessGame.PlayerBlack.Score == -1)
    {
        int result;
        printf("���������� ����� ������ �� ������ �������: ");
        scanf("%d", &result);
        if (result > 0)
        {
            chessGame.PlayerBlack.Score = result;
        }
        else
        {
            printf("�� ����� ������ ������. ������ ������������ � ���������� ��� ���!\n");
        }
    }

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

    PrintTitle();

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
    
    Person** persons = NULL; //malloc(sizeof(Person*) * lenPersons);

    int lenPersons = 0;

    for (int i = 0; i < ARR_LEN; i++)
    {
        if (_chessGames[i].id == -1) continue;

        lenPersons += 2;
        persons = realloc(persons, sizeof(Person*) * lenPersons);

        persons[lenPersons - 2] = &_chessGames[i].PlayerWhite;
        persons[lenPersons - 1] = &_chessGames[i].PlayerBlack;

    }

    //���������� ���������
    for (int i = 0; i < lenPersons - 1; i++) {
        // ���������� ��� �������� ��������.
        for (int j = 0; j < lenPersons - i - 1; j++)
        {
            //���� ������� � '�������� � ��������' �� '�������� � ��������' ����� ���� < �� > � ��������
            if (persons[j]->Score < persons[j + 1]->Score)
            {
                Person* temp = NULL;
                temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;
            }
        }
    }

    printf("\n");
    printf("|%-25s||%-5s|\n", "��� ������", "�����");

    for (int i = 0; i < 3; i++)
    {
        printf("|%-25s||%-5d|\n", persons[i]->Fio, persons[i]->Score);
    }

    free(persons);
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

    PrintTitle();

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

        strcpy(txtSave, _chessGames[i].PlayerWhite.Fio);
        strcat(txtSave, ";");
        strcat(txtSave, IntToStr(_chessGames[i].PlayerWhite.Score));
        strcat(txtSave, ";");

        strcat(txtSave, _chessGames[i].PlayerBlack.Fio);
        strcat(txtSave, ";");
        strcat(txtSave, IntToStr(_chessGames[i].PlayerBlack.Score));
        strcat(txtSave, ";");

        strcat(txtSave, _chessGames[i].DebutName);
        strcat(txtSave, ";");

        strcat(txtSave, IntToStr(&_chessGames[i].Result));
        strcat(txtSave, ";");

        strcat(txtSave, IntToStr(&_chessGames[i].TimeSpent));
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

            strcpy(_chessGames[i].PlayerWhite.Fio, chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].PlayerWhite.Score = atoi(chessGameText);
            chessGameText = strtok(NULL, ";");

            strcpy(_chessGames[i].PlayerBlack.Fio, chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].PlayerBlack.Score = atoi(chessGameText);
            chessGameText = strtok(NULL, ";");

            strcpy(_chessGames[i].DebutName, chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].Result = atoi(chessGameText);
            chessGameText = strtok(NULL, ";");
            _chessGames[i].TimeSpent = atoi(chessGameText);
            chessGameText = strtok(NULL, ";"); //��������� �� ������

            break;
        }
        
    }

    fclose(file);
}

void PrintTitle() {

    printf("\n");
    printf("|%-3s||%-25s||%-5s||%-25s||%-5s||%-25s||%-10s||%-5s|\n", "ID", "���. � ��� ������ �����", "�����", "���. � ��� ������ ������", "�����", "����. ������", "���������", "�����");

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

    printf("|%-3d||%-25s||%-5d||%-25s||%-5d||%-25s||%-10s||%-5d|\n",
        game->id,
        
        game->PlayerWhite.Fio,
        game->PlayerWhite.Score,
        
        game->PlayerBlack.Fio,
        game->PlayerBlack.Score,
        
        game->DebutName,
        gameResultText,
        game->TimeSpent
        );
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

    strcpy(to->PlayerWhite.Fio, from->PlayerWhite.Fio);
    to->PlayerWhite.Score = from->PlayerWhite.Score;

    strcpy(to->PlayerBlack.Fio, from->PlayerBlack.Fio);
    to->PlayerBlack.Score = from->PlayerBlack.Score;

    strcpy(to->DebutName, from->DebutName);
    
    to->Result = from->Result;
    to->TimeSpent = from->TimeSpent;
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