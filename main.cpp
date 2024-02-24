#include <iostream>
using namespace std;

void start_game(){
  board = {
    ['t', 'h', 'b', 'q', 'k', 'b', 'h', 't'],
    ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
    ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
    ['t', 'h', 'b', 'q', 'k', 'b', 'h', 't'],
  };
}

void print_board(){
  for(int x = 0; x < 8; x++){
    for(int y = 0; y < ;8 y++){
      cout << board[x][y];
    }
    cout << "\n";
  }
}

int main(){
  char board[8][8];
  start_game();
  print_board();
}
