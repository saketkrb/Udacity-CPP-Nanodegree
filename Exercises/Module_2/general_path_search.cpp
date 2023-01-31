#include <bits/stdc++.h>
using namespace std;

/* 
finding shortest distance between two grid position 
grid value 0 represents free path
grid value 1 represents obstacle
only move in 4 directions, up, down, left and right

*/

void printBoard(vector<vector<int>> gridBoard) {

    for (vector<int> row : gridBoard) {
        for (int col : row) {
            cout << col << "  ";
        }
        cout << endl;
    }
}


bool valid(int i, int j, int row, int col) {
    return (i >= 0 && i <= row-1 && j >= 0 && j <= col-1) ? true : false;
}


void minPathsolve(vector<vector<int>>& gridBoard, int i, int j, vector<vector<bool>>& visited) {

    queue<pair<int,int>> nodes;
    pair<int, int> node;
    node.first = i;
    node.second = j;
    nodes.push(node);
    int n = gridBoard.size();

    while (!nodes.empty()) {

        pair<int,int> node = nodes.front();
        nodes.pop();
        int i = node.first;
        int j = node.second;
        int m = gridBoard[i].size();
        /*
            movements - (i+1, j), (i-1, j), (i, j+1), (i, j-1)
        */
        visited[i][j] = true;
        pair<int, int> tempNode;


        if ((valid(i,j+1,n,m)) && (gridBoard[i][j+1] == 0) && !visited[i][j+1]) {
            gridBoard[i][j+1] = 1 + gridBoard[i][j];
            visited[i][j+1] = true;
            tempNode.first = i;
            tempNode.second = j+1;
            nodes.push(tempNode);

        }

        if ((valid(i,j-1,n,m)) && (gridBoard[i][j-1] == 0) && !visited[i][j-1]) {
            gridBoard[i][j-1] = 1 + gridBoard[i][j];
            visited[i][j-1] = true;
            tempNode.first = i;
            tempNode.second = j-1;
            nodes.push(tempNode);

        }

        if ((valid(i+1,j,n,m)) && (gridBoard[i+1][j] == 0) && !visited[i+1][j]) {
            gridBoard[i+1][j] = 1 + gridBoard[i][j];
            visited[i+1][j] = true;
            tempNode.first = i+1;
            tempNode.second = j;
            nodes.push(tempNode);

        }

        if ((valid(i-1,j,n,m)) && (gridBoard[i-1][j] == 0) && !visited[i-1][j]) {
            gridBoard[i-1][j] = 1 + gridBoard[i][j];
            visited[i-1][j] = true;
            tempNode.first = i-1;
            tempNode.second = j;
            nodes.push(tempNode);

        }

        
    }

    printBoard(gridBoard);

}




int main() {

    vector<vector<int>> gridBoard {
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,0,1,0},
        {0,0,1,1,1,0},
        {0,0,0,0,1,0}
    };

    vector<vector<bool>> visited(gridBoard.size(), vector<bool>(gridBoard[0].size(), false));

    minPathsolve(gridBoard, 0, 0, visited);

}