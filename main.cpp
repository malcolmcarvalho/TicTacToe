//
//  main.cpp
//  TicTacToe
//
//  Created by Malcolm Carvalho on 12/01/21.
//

#include <iostream>
using namespace std;

char blank = ' ';
char board[3][3];
bool isPlayer1 = true;
int movesLeft;

enum eState
{
    InProgress = 0,
    Draw,
    P1Wins,
    P2Wins
};

void initBlankBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = blank;
        }
    }
    movesLeft = 9;
}

void drawBoard()
{
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "-----------\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "-----------\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

eState GameState()
{
    auto  ret = (board[0][0] != ' ' && board[0][0] == board[0][1] && board[0][1] == board[0][2])
    ||  (board[1][0] != ' ' && board[1][0] == board[1][1] && board[1][1] == board[1][2])
    ||  (board[2][0] != ' ' && board[2][0] == board[2][1] && board[2][1] == board[2][2])

    ||  (board[0][0] != ' ' && board[0][0] == board[1][0] && board[1][0] == board[2][0])
    ||  (board[0][1] != ' ' && board[0][1] == board[1][1] && board[1][1] == board[2][1])
    ||  (board[0][2] != ' ' && board[0][2] == board[1][2] && board[1][2] == board[2][2])

    ||  (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    ||  (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]);
    
    if (ret)
    {
        return movesLeft % 2 ? P2Wins : P1Wins;
    }
    else if (movesLeft == 0)
        return Draw;
    else
        return InProgress;
}

bool updateBoard(int r, int c)
{
    if (board[r][c] != blank)
        return false;
    
    board[r][c] = isPlayer1 ? 'X' : 'O';
    return true;
}

void getInput()
{
    while (true)
    {
        if (isPlayer1)
            cout << "Player1: Enter cell no ";
        else
            cout << "Player2: Enter cell no ";
        int index = -1;
        cin >> index;
        if (index < 0 || index > 8)
        {
            cout << "Cell index should be between 0 and 8\n";
            continue;
        }
        else
        {
            int r = index / 3;
            int c = index % 3;
            if (!updateBoard(r, c))
            {
                cout << "Cell already filled\n";
                continue;
            }
            
            --movesLeft;
            isPlayer1 = !isPlayer1;
            break;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    initBlankBoard();
    drawBoard();
    isPlayer1 = true;
    
    while (true)
    {
        getInput();
        drawBoard();
        
        switch (GameState())
        {
            case P1Wins:
                cout << "Player1 wins!\n";
                return 0;
            case P2Wins:
                cout << "Player2 wins!\n";
                return 0;
            case Draw:
                cout << "Game drawn\n";
                return 0;
            case InProgress:
                break;
        }
    }
    
    return 0;
}
