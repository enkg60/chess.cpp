#include "termcolor.hpp"
#include <array>
#include <iostream>
#include <stack>
// p = pawn
// r = rook
// h = horse/knight
// b = bishop
// q = queen
// k = king

using namespace std;
using namespace termcolor;

char board[8][8];

// planned display size: 10 tall, 18 wide
// chess: 9 tall 17 wide

struct piece {
  char type;
  bool white;
};

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

void nerd_display_board() {
  bool color = true;
  cout << " ╔════════════════════════╗\n";
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (x == 0) {
        cout << y << "║";
      }
      char type = board[y][x];
      string icon;
      if (type == 'p') {
        icon = "󰡙";
      }
      if (type == 'b') {
        icon = "󰡜";
      }
      if (type == 'h') {
        icon = "󰡘";
      }
      if (type == 'r') {
        icon = "󰡛";
      }
      if (type == 'k') {
        icon = "󰡗";
      }
      if (type == 'q') {
        icon = "󰡚";
      }
      if (type == '+') {
        icon = " ";
      }
      if (type == 'x') {
        icon = "x";
      }
      if (x == 7) {
        if (color) {
          cout << on_blue << " " << icon << " " << reset << "║";
        } else {
          cout << on_grey << " " << icon << " " << reset << "║";
        }
      } else {
        if (color) {
          if (!(x % 2 == 0)) {
            cout << on_blue << " " << icon << " " << reset;
          } else {
            cout << on_grey << " " << icon << " " << reset;
          }
        } else {
          if (x % 2 == 0) {
            cout << on_blue << " " << icon << " " << reset;
          } else {
            cout << on_grey << " " << icon << " " << reset;
          }
        }
      }
      // ▒░
    }
    cout << "\n";
    color = !color;
  }
  cout << " ╚════════════════════════╝\n";
  cout << "   0  1  2  3  4  5  6  7 \n";
}

bool check_for_piece(array<int, 2> location) {
  if (board[location[0]][location[1]] != '+') {
    return true;
  } else {
    return false;
  }
}

stack<array<int, 2> /* */> possible_moves(bool white, array<int, 2> position) {
  int y = position[0];
  int x = position[1];
  char type = board[y][x];
  stack<array<int, 2> /* */> possibleMoves;

  if (type == 'p') {
    int flip = 1;
    if (!white) {
      flip = -1;
    }

    array<int, 2> diagonalRight = {y - (1 * flip), x + (1 * flip)};
    array<int, 2> diagonalLeft = {y - (1 * flip), x - (1 * flip)};
    array<int, 2> forward = {y - (1 * flip), x};

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
    for (int side = 0; side < 4; side++) {
      int iterator = 1;
      while (true) {
        array<int, 2> forward;
        if (side == 0) { // diagonalUpRight
          forward[0] = y - iterator;
          forward[1] = x + iterator;
        }
        if (side == 1) { // diagonalUpLeft
          forward[0] = y - iterator;
          forward[1] = x - iterator;
        }
        if (side == 2) { // diagonalDownRight
          forward[0] = y + iterator;
          forward[1] = x + iterator;
        }
        if (side == 3) { // diagonalDownLeft
          forward[0] = y + iterator;
          forward[1] = x - iterator;
        }
        if (forward[0] > 7 || forward[0] < 0 || forward[1] > 7 ||
            forward[1] < 0) {
          break;
        }
        if (check_for_piece(forward) == false) {
          possibleMoves.push(forward);
          iterator++;
          continue;
        } else {
          possibleMoves.push(forward);
          break;
        }
      }
    }
  }
  if (type == 'h') {
    int iterator = 1;
    while (true) {
      array<int, 2> forward;
      if (iterator == 1) {
        forward[0] = y - 1;
        forward[1] = x - 2;
      }
      if (iterator == 2) {
        forward[0] = y - 2;
        forward[1] = x - 1;
      }
      if (iterator == 3) {
        forward[0] = y - 2;
        forward[1] = x + 1;
      }
      if (iterator == 4) {
        forward[0] = y - 1;
        forward[1] = x + 2;
      }
      if (iterator == 5) {
        forward[0] = y + 1;
        forward[1] = x + 2;
      }
      if (iterator == 6) {
        forward[0] = y + 2;
        forward[1] = x + 1;
      }
      if (iterator == 7) {
        forward[0] = y + 2;
        forward[1] = x - 1;
      }
      if (iterator == 8) {
        forward[0] = y + 1;
        forward[1] = x - 2;
      }

      iterator++;
      if (forward[0] > 7 || forward[0] < 0 || forward[1] > 7 ||
          forward[1] < 0) {
        if (iterator == 9) {
          break;
        }
        continue;
      }
      possibleMoves.push(forward);
      if (iterator == 9) {
        break;
      }
    }
  }
  if (type == 'r') {
    for (int side = 0; side < 4; side++) {
      int iterator = 1;
      while (true) {
        array<int, 2> forward;
        if (side == 0) {
          if (y == 0) {
            break;
          }
          forward[0] = y - iterator;
          forward[1] = x;
        }
        if (side == 1) {
          if (y == 7) {
            break;
          }
          forward[0] = y + iterator;
          forward[1] = x;
        }
        if (side == 2) {
          if (x == 0) {
            break;
          }
          forward[0] = y;
          forward[1] = x - iterator;
        }
        if (side == 3) {
          if (x == 7) {
            break;
          }
          forward[0] = y;
          forward[1] = x + iterator;
        }

        if (forward[0] > 7 || forward[0] < 0 || forward[1] > 7 ||
            forward[1] < 0) {
          break;
        }

        if (check_for_piece(forward) == false) {
          possibleMoves.push(forward);
          iterator++;
          continue;
        } else {
          possibleMoves.push(forward);
          break;
        }
      }
    }
  }
  if (type == 'k') {
    array<int, 2> forward;
    for (int y1 = 1; y1 > -2; y1--) {
      for (int x1 = 1; x1 > -2; x1--) {
        forward[0] = y - y1;
        forward[1] = x - x1;
        if (x1 == 0 && y1 == 0) {
          continue;
        }
        if (forward[0] > 7 || forward[0] < 0 || forward[1] > 7 ||
            forward[1] < 0) {
          continue;
        }
        possibleMoves.push(forward);
      }
    }
  }
  if (type == 'q') {
    for (int side = 0; side < 8; side++) {
      int iterator = 1;
      while (true) {
        array<int, 2> forward;
        if (side == 0) {
          if (y == 0) {
            break;
          }
          forward[0] = y - iterator;
          forward[1] = x;
        }
        if (side == 1) {
          if (y == 7) {
            break;
          }
          forward[0] = y + iterator;
          forward[1] = x;
        }
        if (side == 2) {
          if (x == 0) {
            break;
          }
          forward[0] = y;
          forward[1] = x - iterator;
        }
        if (side == 3) {
          if (x == 7) {
            break;
          }
          forward[0] = y;
          forward[1] = x + iterator;
        }
        if (side == 4) { // diagonalUpRight
          forward[0] = y - iterator;
          forward[1] = x + iterator;
        }
        if (side == 5) { // diagonalUpLeft
          forward[0] = y - iterator;
          forward[1] = x - iterator;
        }
        if (side == 6) { // diagonalDownRight
          forward[0] = y + iterator;
          forward[1] = x + iterator;
        }
        if (side == 7) { // diagonalDownLeft
          forward[0] = y + iterator;
          forward[1] = x - iterator;
        }

        if (forward[0] > 7 || forward[0] < 0 || forward[1] > 7 ||
            forward[1] < 0) {
          break;
        }

        if (check_for_piece(forward) == false) {
          possibleMoves.push(forward);
          iterator++;
          continue;
        } else {
          possibleMoves.push(forward);
          break;
        }
      }
    }
  }
  return possibleMoves;
}

void print_possible_moves(bool white, array<int, 2> position) {
  stack<array<int, 2> /* */> possibleMoves = possible_moves(white, position);
  while (!possibleMoves.empty()) {
    board[possibleMoves.top()[0]][possibleMoves.top()[1]] = 'x';
    possibleMoves.pop();
  }
}

array<int, 2> convert_chess_notation_to_array(string input) {
  array<int, 2> x;
  x[0] = int(x[0]) - 96;
  x[1] = input[1];

  return x;
}

int main() {
  reset_board();
  nerd_display_board();
  while (true) {
    array<int, 2> in1;
    array<int, 2> in2;
    cout << "piece to move:\ny: ";
    cin >> in1[0];
    cout << "x: ";
    cin >> in1[1];
    print_possible_moves(true, in1);
    nerd_display_board();

    cout << "position to move to:\ny: ";
    cin >> in2[0];
    cout << "x: ";
    cin >> in2[1];
    nerd_display_board();
  }
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
