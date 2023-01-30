#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

using namespace std;

enum State {
    kEmpty, kObstacle
};

string CellString(State state) {
    if (state == kObstacle) return "⛰️  "; 
    else return "0 ";
}


vector<State> ParseLine(string line) {
    vector<State> parsedRow;
    istringstream my_stream(line);
    int n;
    char c;
    while (my_stream) {
        my_stream >> n;
        my_stream >> c;
        if (n == 0) parsedRow.push_back(kEmpty);
        else parsedRow.push_back(kObstacle);
        
    }

    return parsedRow;
}

vector<vector<State>> ReadBoardFile(string filepath) {
    
    string line;
    ifstream fin;      
    fin.open(filepath);    // ifstream myfile (path);

    vector<vector<State>> board;

    while (getline(fin,line)) {
        vector<State> row = ParseLine(line);
        board.push_back(row);
    }
    
    fin.close();
    return board;

}

int main()
{
    vector<vector<int>> board {{0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 0}};


    // Printing board

    for (vector<int> row : board) {
        for (int col : row) {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << "Reading board from file " << endl;
    // Reading the Board from a File
    vector<vector<State>> boardFromFile = ReadBoardFile("1.board");

    for (vector<State> row : boardFromFile) {
        for (State col : row) {
            cout << CellString(col);
        }
        cout << endl;
    }


}