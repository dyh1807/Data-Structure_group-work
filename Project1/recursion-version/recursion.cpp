/**
 * @file simple_test.cpp
 * @author dyh
 * @brief 用作参考的递归dfs递归版本, version of recursion dfs
 * @version 0.1
 * @date 2022-06-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#define MATRIXSIZE 64
#define BOARDSIZE 8

using namespace std;

int matrix[MATRIXSIZE][MATRIXSIZE];
int board[BOARDSIZE][BOARDSIZE];
int outputNum = 0;

void initBoart()
{
    for (int i = 0; i < BOARDSIZE; i++)
        for (int j = 0; j < BOARDSIZE; j++)
            board[i][j] = 0;
}
void clearMatrix()
{
    for (int i = 0; i < MATRIXSIZE; i++)
        for (int j = 0; j < MATRIXSIZE; j++)
            matrix[i][j] = 0;

    return;
}

void initMatrix()
{
    clearMatrix();
    for (int i = 0; i < BOARDSIZE; i++)
        for (int j = 0; j < BOARDSIZE; j++)
            for (int sign_i = 0; sign_i < 1; sign_i++)
                for (int sign_j = 0; sign_j < 2; sign_j++)
                    for (int off = 1; off <= 2; off++)
                    {
                        int temp_i = sign_j ? i + off : i - off;
                        int temp_j = sign_i ? j + 3 - off : j - 3 + off;
                        if (0 <= temp_i && temp_i < BOARDSIZE && 0 <= temp_j && temp_j < BOARDSIZE)
                        {
                            int tempIndex = (temp_i * BOARDSIZE) + temp_j;
                            int presentIndex = (i * BOARDSIZE) + j;
                            matrix[presentIndex][tempIndex] = 1;
                            matrix[tempIndex][presentIndex] = 1;
                        }
                    }
    return;
}

int outputMatrix()
{
    cout << "start output matrix" << endl;
    for (int i = 0; i < MATRIXSIZE; i++, cout << endl)
        for (int j = 0; j < MATRIXSIZE; j++)
            cout << matrix[i][j] << ' ';
    cout << "end output matrix" << endl;
    return 1;
}
int outputRefer()
{

    cout << "start output refer" << endl;
    for (int i = 0; i < MATRIXSIZE; i++)
    {
        int out_degree = 0;
        for (int j = 0; j < MATRIXSIZE; j++)
        {
            out_degree += matrix[i][j];
        }
        cout << "outdegree of " << i << "point is " << out_degree << endl;
    }
    cout << "end output refer" << endl;
    return 0;
}
void outputBoard()
{
    cout << "start output board:" << endl;
    for (int i = 0; i < BOARDSIZE; i++, cout << endl)
        for (int j = 0; j < BOARDSIZE; j++)
            cout << board[i][j] << ' ';
    outputNum++;
    cout << "end output board, outputNum:" << outputNum << endl;
}

int dfs(int vex, int depth)
{
    int i = vex / BOARDSIZE;
    int j = vex % BOARDSIZE;
    if (board[i][j] == 0)
        board[i][j] = depth;
    else
        return 0; // fail to put chess this branch
    if (depth == MATRIXSIZE)
    {
        outputBoard();
        board[i][j] = 0; // reset
        return 1;        // find a path
    }
    else
    {
        for (int k = 0; k < MATRIXSIZE; k++)
        {
            if (matrix[vex][k]) // vex connected with k
                dfs(k, depth + 1);
            if (outputNum == 10)
                return 0; // finish
        }
    }
    board[i][j] = 0;
    return 0; // end this branch
}

int main()
{
    cout << "start" << endl;
    initMatrix();
    initBoart();
    cout << "start dfs:" << endl;
    dfs(0, 1);
    cout << "end dfs" << endl;
    return 0;
}