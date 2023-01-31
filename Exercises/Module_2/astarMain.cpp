// #include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream fin (path);
  vector<vector<State>> board{};
  if (fin) {
    string line;
    while (getline(fin, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}


// string CellString(State cell) {
//   switch(cell) {
//     case State::kObstacle: return "⛰   ";
//     case State::kPath: return "🚗   ";
//     case State::kStart: return "🚦   ";
//     case State::kFinish: return "🏁   ";
//     default: return "0   "; 
//   }
// } 


string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️  ";
    case State::kStart: return "S  ";
    case State::kFinish: return "E  ";
    case State::kPath: return "-  ";
    default: return "0  "; 
  }
}


void PrintBoard(const vector<vector<State>>& board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

/* 
  Sorting nodes on basis of f value (f = g + h(x)), in descending order
*/
bool Compare(vector<int> a, vector<int> b) { 
  return ((a[2] + a[3]) > (b[2] + b[3]));
}


void CellSort(vector<vector<int>> *openNodes) {
    sort(openNodes->begin(), openNodes->end(), Compare);
}


/*
  Check that the (x, y) coordinate pair is on the grid.
  Check that the grid at (x, y) is kEmpty
*/

bool checkValidCell(int x, int y, vector<vector<State>>& board) {

  bool on_gridX = (x >= 0 && x < board.size());
  bool on_gridY = (y >= 0 && y < board[0].size());
  if (on_gridX && on_gridY) {
    return board[x][y] == State::kEmpty;
  }

  return false;

}

// adding nodes to the openNodes vector
void AddToOpen(int x, int y, int g, int h, vector<vector<int>>& openNodes, vector<vector<State>>& board) {
      vector<int> node{x, y, g, h};
      openNodes.push_back(node);
      board[x][y] = State::kClosed;
}

/* Heuristic function will be used to guide the A* search. 
  return an int which is the Manhattan Distance from one coordinate to the other: |x2-x1| + |y2-y1|
*/

int Heuristic(int x1, int y1, int x2, int y2) {
      return abs(x2-x1) + abs(y2-y1);
}

void ExpandNeighbors(vector<int>& currentNode, vector<vector<int>>& openNodes, vector<vector<State>>& board, int goal[]) {

  // : Get current node's data.
  int currentNodeX = currentNode[0];
  int currentNodeY = currentNode[1];
  int currentNodeGValue = currentNode[2];
  int currentNodeHValue = currentNode[3];

  //  Loop through current node's potential neighbors.
  //  Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
  //  Increment g value, compute h value, and add neighbor to open list.

  for (int i = 0; i < 4; i++) {
        int neighbourX = currentNodeX + delta[i][0];
        int neighbourY = currentNodeY + delta[i][1];
        if (checkValidCell(neighbourX, neighbourY, board)) {
            int neighbourGValue = currentNodeGValue+1;
            int neighbourNodeHValue = Heuristic(neighbourX, neighbourY, goal[0], goal[1]);
            AddToOpen(neighbourX, neighbourY, neighbourGValue, neighbourNodeHValue, openNodes, board);
        } 
  }

}

// return the board with a path from the start to the goal

vector<vector<State>>& Search(vector<vector<State>>& board, int start[], int goal[]) { // or int start[2], int goal[2]

  vector<vector<int>> openNodes {};
  //Initialize first node and add it to openNodes vector
  int x = start[0];
  int y = start[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, openNodes, board);

  while (!openNodes.empty()) { 

    CellSort(&openNodes); // sorting the nodes

    auto currentNode = openNodes.back(); // using the node with the lowest f value
    openNodes.pop_back();
    int x = currentNode[0];
    int y = currentNode[1];
    board[x][y] = State::kPath;
    
    if (x == goal[0] && y == goal[1]) {
      board[start[0]][start[1]] = State::kStart;
      board[goal[0]][goal[1]] = State::kFinish;
      return board;
    }

    ExpandNeighbors(currentNode, openNodes, board, goal);

  }

  return board;

}


int main() {
  int init[2] = {0, 0}; // or: int init[2]{0, 0}; or: int init[] = {0, 0}
  int goal[2] = {4, 5};
  auto board = ReadBoardFile("1.board");
  PrintBoard(board);
  cout << endl;
  vector<vector<State>> solution = Search(board, init, goal);
  PrintBoard(solution);
}


