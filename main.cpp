#include <array>
#include <iostream>
#include <stack>

using namespace std;

char board[8][8];

//planned display size: 10 tall, 18 wide
//chess: 9 tall 17 wide

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

bool check_for_piece(array<int, 2> location) {
  if (board[location[0]][location[1]] != '+') {
    return true;
  } else {
    return false;
  }
}

stack<array<int, 2> > check_moves(bool white, array<int, 2> position) {
  int y = position[0];
  int x = position[1];
  char type = board[y][x];

  stack<array<int, 2> > possibleMoves;
  if (type == 'p') {
    int flip = 1;
    
    if (!white) {
      flip = -1;
    }
    array<int,2> diagonalRight = {y-(1*flip), x+(1*flip)};
    array<int,2> diagonalLeft = {y-(1*flip), x-(1*flip)};
    array<int,2> forward = {y-(1*flip), x};
    
    if (!check_for_piece(forward)) {
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
  array<int, 2> p = {6, 2};
  stack<array<int, 2> /* */> y = check_moves(true, p);
  while (!y.empty()) {
    cout << y.top()[0] << " " << y.top()[1] << '\n';
    board[y.top()[0]][y.top()[1]] = 'x';
    y.pop();
  }
  display_board();
}
/*
while(true){
  cout << "piece to move (line 1) and where (line 2)"
  string piece;
  cin >> piece;
  //string location;
  //cin >> location;
}
*/

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
