#include <iostream>
#include <stack>

using namespace std;

char board[8][8];

/*
char display[10][18];
//10 tall, 18 wide

//chess = 9 tall 17 wide
*/

void reset_board() {

  char pawns[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
  char others[8] = {'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'};

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (y == 0 || y == 7) {
        board[y][x] = others[x];
      } else if (y == 1 || y == 6) {
        board[y][x] = pawns[x];
      } else {
        board[y][x] = '+';
      }
    }
  }
}

void display_board() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (x == 0) {
        cout << 8 - (y) << ' ';
      }
      cout << board[y][x] << ' ';
    }
    cout << "\n";
  }
  cout << "  a b c d e f g h\n";
}

bool check_for_piece(int location[2]) {
  if (board[location[0]][location[1]] != '+') {
    return true;
  } else {
    return false;
  }
}

stack<int[2]> check_moves(bool white, int position[2], int target[2]) {
  int y = position[0];
  int x = position[1];
  char type = board[y][x];

  stack<int[2]> possibleMoves;
  if (type == 'p') {
    if (white) {
      int diagonalRight[2] = {y + 1, x + 1};
      int diagonalLeft[2] = {y + 1, x - 1};
      int forward[2] = {y + 1, x};

      if (check_for_piece(forward)) {
        possibleMoves.push(forward);
      }
      if (x == 0) {
        if (check_for_piece(diagonalRight)) {
          possibleMoves.push(diagonalRight);
        }
      } else if (x == 7) {
        if (check_for_piece(diagonalLeft)) {
          possibleMoves.push(diagonalLeft);
        }
      } else {
        if (check_for_piece(diagonalRight)) {
          possibleMoves.push(diagonalRight);
        }
        if (check_for_piece(diagonalLeft)) {
          possibleMoves.push(diagonalLeft);
        }
      }
    } else {
      int diagonalRight[2] = {y - 1, x - 1};
      int diagonalLeft[2] = {y - 1, x + 1};
      int forward[2] = {y - 1, x};

      if (check_for_piece(forward)) {
        possibleMoves.push(forward);
      }
      if (x == 0) {
        if (check_for_piece(diagonalRight)) {
          possibleMoves.push(diagonalRight);
        }
      } else if (x == 7) {
        if (check_for_piece(diagonalLeft)) {
          possibleMoves.push(diagonalLeft);
        }
      } else {
        if (check_for_piece(diagonalRight)) {
          possibleMoves.push(diagonalRight);
        }
        if (check_for_piece(diagonalLeft)) {
          possibleMoves.push(diagonalLeft);
        }
      }
    }
  }
  if (type == 'b') {
  }
  if (type == 'n') {
  }
  if (type == 'r') {
  }
  if (type == 'k') {
  }
  if (type == 'q') {
  }
  return possibleMoves;
}

int main() {
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
