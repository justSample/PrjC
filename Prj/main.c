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
    //�� ������� ������� ����. ��������. 1251
    //strcpy - �����������
    //strcat - ��������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char *locale = setlocale(LC_ALL, "");



    return;

    Init();
    MainLogic();

    printf("\n����� ���������.\n");

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
        printf("\n������� ����\n");

        printf("1. ������� ��� ������\n");
        printf("2. ����� ������\n");
        printf("3. ���������� ����� ������\n");
        printf("4. �������� ������\n");
        printf("5. ������� 3-�� ������� � ���������� ����������� �����\n");
        printf("6. ������� �������� ������ ������ �� ������������ ������\n");
        
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

            default:
                printf("������ ������ ����. ���������� ������!\n");
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

    printf("������� ������ �� ����� �������: ");
    scanf("%s", chessGame.PlayerFioWhite.Surname);

    printf("��� ������ �� ����� �������: ");
    scanf("%s", chessGame.PlayerFioWhite.Name);

    printf("������� ������ �� ������ �������: ");
    scanf("%s", chessGame.PlayerFioBlack.Surname);

    printf("��� ������ �� ������ �������: ");
    scanf("%s", chessGame.PlayerFioBlack.Name);

    printf("�������� ������: ");
    //scanf("%s%s", &f, &s);
    getchar();
    gets(chessGame.DebutName);

    
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
        printf("������������ ������(� ��������): ");
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
    printf("|%-3s||%-20s||%-30s||%-20s||%-30s||%-45s||%-20s||%-5s||%-5s|\n", "ID", "��� ������ �����", "���. ������ �����", "��� ������ ������", "���. ������ ������", "����. ������", "���������", "�����", "����");

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


// �������:
//  1. �������� � ����������
//  2. ������ ��������
//  3. �������� ����� ������� �� �������
//  4. ����� �� ����� � ��������� ���� (��� � �����, ���� ��� ������)
//  5. ����� ������� (����� ���������� �� ����� ����������?)
//  6. �������� ������ �� ������
//  7. ����� �������� ������ ������������� � ���������� ������
//
// ������:
//  1. ����, ������. ������: ������� � ��� �����������, ����� ������, ����� ����������� �� ������, �������� ������ [OK]
//  2. ����� ��� ������� � ���������� ����������� ��������� �����
//  3. �������� ������ ������ �� �������� ��������� ������������ ������. (����� �� �������� ������)