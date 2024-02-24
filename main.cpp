#include <iostream>
using namespace std;

char board[8][8];

void reset_board(){

  char pawns[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
  char others[8] = {'t', 'h', 'b', 'q', 'k', 'b', 'h', 't'};

  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      if(y == 0 || y == 7){
        board[y][x] = pawns[x];
      } else if (y == 1 || y == 6){
        board[y][x] = others[x];
      } else {
        board[y][x] = '+';
      }

    }
  }
  /*
  board = {
    {'t', 'h', 'b', 'q', 'k', 'b', 'h', 't'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'t', 'h', 'b', 'q', 'k', 'b', 'h', 't'},
  };
  */
}

void print_board(){
  cout << "  a b c d e f g h\n";
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      if(x == 0){
        cout << y+1 << ' ';
      }
      cout << board[y][x] << ' ';
    }
    cout << "\n";
  }
}

int main(){
  reset_board();
  while(true){
    string input;
    cin >> input;
  }
}
