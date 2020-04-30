/********************************************************************
*                                                                   *
*           Project:            Sudoku Solver                       *
*                                                                   *
*           Author:             Joel Howell                         *
*                                                                   *
*           Date Created:       4/20/2020                           *
*                                                                   *
*           Last Modified:      4/29/2020                           *
*                                                                   *
********************************************************************/	 

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define SIZE        9
#define UNASSIGNED  0

unsigned int calls = 0;

typedef unsigned int Sudoku[SIZE][SIZE];

bool empty(Sudoku board, int *r, int *c);
bool inBox(Sudoku board, int r, int c, int n);
bool inCol(Sudoku board, int c, int n);
bool inD1(Sudoku board, int n);
bool inD2(Sudoku board, int n);
bool inRow(Sudoku board, int r, int n);
bool possible(Sudoku board, int r, int c, int n);
bool solve(Sudoku board);
void print(Sudoku board);
void reset(Sudoku board);

int main()
{
    clock_t start, end;
    double elapsed;

    start = clock();

    Sudoku board =
    {
        {0, 3, 0,   8, 4, 0,    0, 0, 0},
        {0, 0, 0,   9, 0, 0,    0, 0, 0},
        {0, 0, 5,   0, 0, 0,    0, 0, 0},

        {2, 5, 0,   0, 0, 7,    4, 8, 0},
        {0, 0, 1,   0, 0, 0,    0, 3, 0},
        {0, 7, 3,   0, 0, 0,    0, 0, 1},

        {0, 4, 0,   0, 0, 0,    0, 0, 0},
        {0, 0, 8,   6, 0, 0,    9, 0, 0},
        {9, 0, 0,   0, 0, 0,    0, 0, 0}
    };

    printf("Unsolved :\n");
    print(board);

    if(solve(board))
    {
        printf("\nSolved:\n");
        print(board);
        printf("\nCalls: %d", calls);
    }    
    else
    {
        printf("\nCannot solve :(\n");
    }

    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f seconds\n", elapsed);

    return 0;
}

bool solve(Sudoku board)
{
    int r, c;

    calls++;

    if (!empty(board, &r, &c))
        return true;

    for (int n = 1; n <= SIZE; n++)
    {
        if (possible(board, r, c, n))
        {             
            board[r][c] = n;
            if(solve(board))
                return true;
            board[r][c] = UNASSIGNED;       
        }
    }    
    return false;  
}

bool inRow(Sudoku board, int r, int n)
{
    for (int c = 0; c < SIZE; c++)
        if (board[r][c] == n)
            return true;
    return false;
}

bool inCol(Sudoku board, int c, int n)
{
    for (int r = 0; r < SIZE; r++)
        if (board[r][c] == n)
            return true;
    return false;
}

bool inBox(Sudoku board, int r, int c, int n)
{
    int box = sqrt(SIZE);
    int x = floor(r / box) * box;
    int y = floor(c / box) * box;

    for (int i = 0; i < box; i++)
        for (int j = 0; j < box; j++)
            if(board[x + i][y + j] == n)
                return true;
    return false;  
}

bool inD1(Sudoku board, int n)
{
    for (int i = 0; i < SIZE; i++)
        if (board[i][i] == n)
            return true;
    return false;    
}

bool inD2(Sudoku board, int n)
{
    for (int i = 0; i < SIZE; i++)
        if (board[i][SIZE - i - 1] == n)
            return true;
    return false;
}

bool empty(Sudoku board, int *r, int *c)
{
    for (*r = 0; *r < SIZE; (*r)++)
        for (*c = 0; *c < SIZE; (*c)++)
            if (board[*r][*c] == UNASSIGNED)
                return true;
    return false;
}

bool possible(Sudoku board, int r, int c, int n)
{
    if (r == c && ((r + c) == (SIZE - 1)))
        return !inRow(board, r, n) && !inCol(board, c, n) && !inBox(board, r, c, n) && !inD1(board, n) && !inD2(board, n);
    if (r == c)
        return !inRow(board, r, n) && !inCol(board, c, n) && !inBox(board, r, c, n) && !inD1(board, n);
    if ((r + c) == (SIZE - 1))
        return !inRow(board, r, n) && !inCol(board, c, n) && !inBox(board, r, c, n) && !inD2(board, n);
    return !inRow(board, r, n) && !inCol(board, c, n) && !inBox(board, r, c, n);
}

void print(Sudoku board)
{
    int box = sqrt(SIZE);
    for (int r = 0; r < SIZE; r++)
    {
        if (r % box == 0 && r != 0)
            printf("\n");

        for (int c = 0; c < SIZE; c++)
        {
            if (c % box == 0 && c != 0)
                printf(" %d ", board[r][c]);
            else
                printf("%d ", board[r][c]);
        }
        printf("\n");
    }
}

void reset(Sudoku board)
{
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            board[r][c] = UNASSIGNED;
}