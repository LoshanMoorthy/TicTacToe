#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard(char*** board);
void printBoard(char** board);
int checkFreeSpaces(char** board);
void playerMove(char** board);
void computerMove(char** board);
char checkWinner(char** board);
void printWinner(char);

int main()
{
    char winner = ' ';
    char response;

    do
    {
        winner = ' ';
        response = ' ';
        char** board = NULL;
        resetBoard(&board);

        while (winner == ' ' && checkFreeSpaces(board) != 0)
        {
            printBoard(board);

            computerMove(board);
            winner = checkWinner(board);
            if (winner != ' ' || checkFreeSpaces(board) == 0)
                break;

            playerMove(board);
            winner = checkWinner(board);
            if (winner != ' ' || checkFreeSpaces(board) == 0)
                break;
        }

        printBoard(board);
        printWinner(winner);    

        printf("\nWould yo like to play again? (Y/N): ");
        scanf("%c");
        scanf("%c", &response);
        response = toupper(response);
        free(board[0]);
        free(board);
    } while (response == 'Y');

    printf("Thanks for playing !");
    return 0;
}

void resetBoard(char*** board)
{
    *board = (char**)malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++)
    {
        (*board)[i] = (char*)malloc(3 * sizeof(char));
        for (int j = 0; j < 3; j++)
        {
            (*board)[i][j] = ' ';
        }
    }
}

void printBoard(char** board)
{
    printf(" %c | %c | %c", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpaces(char** board)
{
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != ' ')
                freeSpaces--;
    
    return freeSpaces;
}

void playerMove(char** board)
{
    int x, y;

    do
    {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;

        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}

void computerMove(char** board)
{
    // Creates a seed based on current time
    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces(board) > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
        printWinner(' ');
}

char checkWinner(char** board)
{
    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];

    // Check columns
    for (int i = 0; i < 3; i++)
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];

    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];

    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];

    return ' ';
}

void printWinner(char winner)
{
    if (winner == PLAYER)
        printf("YOU WIN!");
    else if (winner == COMPUTER)
        printf("YOU LOSE!");
    else
        printf("IT'S A TIE!");
}