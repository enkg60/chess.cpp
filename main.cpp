#include <iostream>
using namespace std;

char board[8][8];

/*
char display[10][18];
//10 tall, 18 wide

//chess = 9 tall 17 wide
*/


void reset_board(){

  char pawns[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
  char others[8] = {'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'};

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
}

void display_board(){
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

bool check_moves(char piece){
  bool pawn, bishop, knight, rook, queen, king;
  pawn = bishop = knight = rook = queen = king = true;
  if(pawn){

  }
  if(bishop){

  }
  if(knight){

  }
  if(rook){

  }
  if(king){

  }
  if(queen){

  }
  return false;
}

int main(){
  reset_board();
  while(true){
    string input;
    cin >> input;
    
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
