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
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      if(x == 0){
        cout << 8-(y) << ' ';
      }
      cout << board[y][x] << ' ';
    }
    cout << "\n";
  }
  cout << "  a b c d e f g h\n";
}

bool check_spot_for_piece(int location[2]){
  if(board[location[0]][location[1]] != '+'){
    return true;
  }else{
    return false;
  }
}

bool check_move(bool white, int location[2], int target[2]){
  int size = 0;

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

  //check if possibleMoves line up with target
  for(int i = 0; i < size; i++){
    if(possibleMoves[i] == target){
      
      return true;
    }

  }
  return false;
}

int main(){
  reset_board();
  display_board();
  /*
  while(true){
    cout << "piece to move (line 1) and where (line 2)"
    string piece;
    cin >> piece;
    //string location;
    //cin >> location;
  }
  */
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
