#include "termcolor.hpp"
#include <array>
// #include <cmath> don't know why this is here
#include <iostream>
#include <stack>
#include <sys/wait.h>
// p = pawn
// r = rook
// h = horse/knight
// b = bishop
// q = queen
// k = king

using namespace std;
using namespace termcolor;

stack<array<int, 2> /* */> emptyStack;
// just a empty stack to pass to nerd_display_board

struct piece {
  char type;
  bool white; // issue here because empty spots on the board have a color
  // possible solution is to turn it into an int where
  // 1 = white, 2 = black and 0 = nothing
};

piece board[8][8];

// planned display size: 10 tall, 18 wide
// chess: 9 tall 17 wide

piece create_piece(char type, bool white) {
  piece piece;
  piece.type = type;
  piece.white = white;
  return piece;
}

void reset_board() {
  char pieces[8] = {'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'};
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (y == 0) {
        board[y][x] = create_piece(pieces[x], false);
      } else if (y == 7) {
        board[y][x] = create_piece(pieces[x], true);
      } else if (y == 1) {
        board[y][x] = create_piece('p', false);
      } else if (y == 6) {
        board[y][x] = create_piece('p', true);
      } else {
        board[y][x] = create_piece('+', false);
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
      cout << board[y][x].type << ' ';
    }
    cout << "\n";
  }
  cout << "  a b c d e f g h\n";
}

void nerd_display_board(stack<array<int, 2> /* */> possibleMoves) {
  // bad thing about having to pass argument is that if i just want to print
  // board i have to pass a empty stack
  bool color = true;
  piece tempBoard[8][8];

  // this 2d for loop is just to copy board to tempBoard
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      tempBoard[y][x] = board[y][x];
    }
  }

  while (!possibleMoves.empty()) {
    // get the position of the possible move and replace it with a 'x' on the
    // temp board
    tempBoard[possibleMoves.top()[0]][possibleMoves.top()[1]].type = 'x';
    possibleMoves.pop();
  }

  // doing all this temp board stuff allows us to overlay possibleMoves
  // without changing the actual board. this is essentially a poorly stitched
  // display system, will make a real display system later

  cout << " ╔════════════════════════╗\n";
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (x == 0) {
        cout << y << "║";
      }
      char type = tempBoard[y][x].type;
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

      // CODE BELOW IS HORRENDOUS
      // goal is to print the checkered board and color the piece
      // if it's to hard to understand, ask me, cause it's just bad code ngl
      // going to fix later
      if (x == 7) {
        if (color) {
          if (tempBoard[y][x].white) {
            cout << on_blue << " " << white << icon << " " << reset << "║";
          } else {
            cout << on_blue << " " << grey << icon << " " << reset << "║";
          }
        } else {
          if (tempBoard[y][x].white) {
            cout << on_bright_grey << " " << white << icon << " " << reset
                 << "║";
          } else {
            cout << on_bright_grey << " " << grey << icon << " " << reset
                 << "║";
          }
        }
      } else {
        if (color) {
          if (!(x % 2 == 0)) {
            if (tempBoard[y][x].white) {
              cout << on_blue << " " << white << icon << " " << reset;
            } else {
              cout << on_blue << " " << grey << icon << " " << reset;
            }
          } else {
            if (tempBoard[y][x].white) {
              cout << on_bright_grey << " " << white << icon << " " << reset;
            } else {
              cout << on_bright_grey << " " << grey << icon << " " << reset;
            }
          }
        } else {
          if (x % 2 == 0) {
            if (tempBoard[y][x].white) {
              cout << on_blue << " " << white << icon << " " << reset;
            } else {
              cout << on_blue << " " << grey << icon << " " << reset;
            }
          } else {
            if (tempBoard[y][x].white) {
              cout << on_bright_grey << " " << white << icon << " " << reset;
            } else {
              cout << on_bright_grey << " " << grey << icon << " " << reset;
            }
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
  if (board[location[0]][location[1]].type != '+') {
    return true;
  } else {
    return false;
  }
}

stack<array<int, 2> /* */> possible_pawn_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
  int flip = 1;
  if (board[y][x].white == false) {
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
  return possibleMoves;
}

stack<array<int, 2> /* */> possible_bishop_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
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
  return possibleMoves;
}

stack<array<int, 2> /* */> possible_knight_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
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
    if (forward[0] > 7 || forward[0] < 0 || forward[1] > 7 || forward[1] < 0) {
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
  return possibleMoves;
}

stack<array<int, 2> /* */> possible_rook_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
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
  return possibleMoves;
}

stack<array<int, 2> /* */> possible_king_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
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
  return possibleMoves;
}

stack<array<int, 2> /* */> possible_queen_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
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
  return possibleMoves;
}

stack<array<int, 2> /* */> possible_moves(array<int, 2> position) {
  int y = position[0];
  int x = position[1];
  char type = board[y][x].type;
  stack<array<int, 2> /* */> possibleMoves;
  if (type == 'p') {
    possibleMoves = possible_pawn_moves(y, x);
  }
  if (type == 'b') {
    possibleMoves = possible_bishop_moves(y, x);
  }

  if (type == 'h') {
    possibleMoves = possible_knight_moves(y, x);
  }
  if (type == 'r') {
    possibleMoves = possible_rook_moves(y, x);
  }
  if (type == 'k') {
    possibleMoves = possible_king_moves(y, x);
  }
  if (type == 'q') {
    possibleMoves = possible_king_moves(y, x);
  }
  return possibleMoves;
}

/*
REIMPLEMENT ONCE DISPLAY SYSTEM IS FINSIHED

void overlay_possible_moves(array<int, 2> position) {
  stack<array<int, 2> > possibleMoves = possible_moves(position);
  while (!possibleMoves.empty()) {
    board[possibleMoves.top()[0]][possibleMoves.top()[1]].type = 'x';
    possibleMoves.pop();
  }
}
*/

array<int, 2> convert_chess_notation_to_array(string input) {
  // not finished
  array<int, 2> x;
  x[0] = int(x[0]) - 96;
  x[1] = input[1];

  return x;
}

bool move_piece(array<int, 2> position, array<int, 2> target) {
  stack<array<int, 2> /* */> possibleMoves = possible_moves(position);
  int positionY = position[0];
  int positionX = position[1];
  int targetY = target[0];
  int targetX = target[1];
  bool condition = true;
  bool ifFunctionWorked = false;

  for (int i = 0; i < possibleMoves.size(); i++) {
    if (possibleMoves.top()[0] == targetY &&
        possibleMoves.top()[1] == targetX) {
      // copy over properties of piece to target
      board[targetY][targetX].type = board[positionY][positionX].type;
      board[targetY][targetX].white = board[positionY][positionX].white;

      // replace piece with empty spot
      board[positionY][positionX].type = '+';
      ifFunctionWorked = true;
    } else {
      possibleMoves.pop();
    }
  }

  if (ifFunctionWorked) {
    cout << "WORKED\n";
  } else {
    cout << "DID NOT WORKED\n";
  }

  return ifFunctionWorked;
}

int main() {
  reset_board();
  nerd_display_board(emptyStack);
  while (true) {
    array<int, 2> in1;
    array<int, 2> in2;
    cout << "piece to move:\ny: ";
    cin >> in1[0];
    cout << "x: ";
    cin >> in1[1];
    nerd_display_board(possible_moves(in1));

    cout << "position to move to:\ny: ";
    cin >> in2[0];
    cout << "x: ";
    cin >> in2[1];
    move_piece(in1, in2);
    nerd_display_board(emptyStack);
    display_board();
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
