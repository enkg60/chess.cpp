#include "termcolor.hpp"
#include <array>
// #include <cmath> don't know why this is here
#include <iostream>
#include <stack>
#include <vector>
#include <sys/wait.h> //why this here
// p = pawn
// r = rook
// h = horse/knight
// b = bishop
// q = queen
// k = king

using namespace std;

stack<array<int, 2> /* */> emptyStack;

vector<char> takenBlack;
vector<char> takenWhite;
// just a empty stack to pass to nerd_display_board

struct piece {
  char type;
  int color;
  int turn;
  bool enPassent; // just to check if a pawn can be en passent

  // 1 = white, 2 = black and 0 = nothing
};
int white = 1;
int black = 2;
int nothing = 0;

piece board[8][8];

// planned display size: 10 tall, 18 wide
// chess: 9 tall 17 wide

piece create_piece(char type, int color, int turn) {
  piece piece;
  piece.type = type;
  piece.color = color;
  piece.turn = turn; // if turn == 0 then there is no piece there
  piece.enPassent = false;
  return piece;
}

void reset_board() {
  char pieces[8] = {'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'};
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (y == 0) {
        board[y][x] = create_piece(pieces[x], black, 1);
      } else if (y == 7) {
        board[y][x] = create_piece(pieces[x], white, 1);
      } else if (y == 1) {
        board[y][x] = create_piece('p', black, 1);
      } else if (y == 6) {
        board[y][x] = create_piece('p', white, 1);
      } else {
        board[y][x] = create_piece('+', nothing, 0);
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
    tempBoard[possibleMoves.top()[0]][possibleMoves.top()[1]].color = nothing;
    possibleMoves.pop();
  }

  // doing all this temp board stuff allows us to overlay possibleMoves
  // without changing the actual board. this is essentially a poorly stitched
  // display system, will make a real display system later

  cout << " ╔════════════════════════╗\n";
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (x == 0) {
        cout << 8 - y << "║";
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
          if (tempBoard[y][x].color == white) {
            cout << termcolor::on_blue << " " << termcolor::white << icon << " "
                 << termcolor::reset << "║";
          } else if (tempBoard[y][x].color == black) {
            cout << termcolor::on_blue << " " << termcolor::grey << icon << " "
                 << termcolor::reset << "║";
          } else {
            cout << termcolor::on_blue << " " << termcolor::bright_red << icon
                 << " " << termcolor::reset << "║";
          }
        } else {
          if (tempBoard[y][x].color == white) {
            cout << termcolor::on_bright_grey << " " << termcolor::white << icon
                 << " " << termcolor::reset << "║";
          } else if (tempBoard[y][x].color == black) {
            cout << termcolor::on_bright_grey << " " << termcolor::grey << icon
                 << " " << termcolor::reset << "║";
          } else {
            cout << termcolor::on_bright_grey << " " << termcolor::bright_red
                 << icon << " " << termcolor::reset << "║";
          }
        }
      } else {
        if (color) {
          if (!(x % 2 == 0)) {
            if (tempBoard[y][x].color == white) {
              cout << termcolor::on_blue << " " << termcolor::white << icon
                   << " " << termcolor::reset;
            } else if (tempBoard[y][x].color == black) {
              cout << termcolor::on_blue << " " << termcolor::grey << icon
                   << " " << termcolor::reset;
            } else {
              cout << termcolor::on_blue << " " << termcolor::bright_red << icon
                   << " " << termcolor::reset;
            }
          } else {
            if (tempBoard[y][x].color == white) {
              cout << termcolor::on_bright_grey << " " << termcolor::white
                   << icon << " " << termcolor::reset;
            } else if (tempBoard[y][x].color == black) {
              cout << termcolor::on_bright_grey << " " << termcolor::grey
                   << icon << " " << termcolor::reset;
            } else {
              cout << termcolor::on_bright_grey << " " << termcolor::bright_red
                   << icon << " " << termcolor::reset;
            }
          }
        } else {
          if (x % 2 == 0) {
            if (tempBoard[y][x].color == white) {
              cout << termcolor::on_blue << " " << termcolor::white << icon
                   << " " << termcolor::reset;
            } else if (tempBoard[y][x].color == black) {
              cout << termcolor::on_blue << " " << termcolor::grey << icon
                   << " " << termcolor::reset;
            } else {
              cout << termcolor::on_blue << " " << termcolor::bright_red << icon
                   << " " << termcolor::reset;
            }
          } else {
            if (tempBoard[y][x].color == white) {
              cout << termcolor::on_bright_grey << " " << termcolor::white
                   << icon << " " << termcolor::reset;
            } else if (tempBoard[y][x].color == black) {
              cout << termcolor::on_bright_grey << " " << termcolor::grey
                   << icon << " " << termcolor::reset;
            } else {
              cout << termcolor::on_bright_grey << " " << termcolor::bright_red
                   << icon << " " << termcolor::reset;
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
  cout << "   a  b  c  d  e  f  g  h \n";
  cout << "Black Pieces Taken: ";
  for (int i = 0; i < takenBlack.size(); i++) {
    cout << takenBlack[i] << ' ';
  }
  cout << "\nWhite Pieces Taken: ";
  for (int i = 0; i < takenWhite.size(); i++) {
    cout << takenWhite[i] << ' ';
  }
  cout << '\n';
}

bool check_for_piece(array<int, 2> location) {
  if (board[location[0]][location[1]].type != '+') {
    cout << "IN THE BOUNDS \n";
    return true;
  } else {
    cout << "NOT IN THE BOUNDS \n";
    return false;
  }
}

bool piece_in_boundaries(array<int, 2> piece) {
  if (piece[0] <= 8 && piece[0] >= 0  && piece[1] <= 7 && piece[1] >= 0) {
    return true;
  } else {
    return false;
  }
}

stack<array<int, 2> /* */> possible_pawn_moves(int y, int x) {
  stack<array<int, 2> /* */> possibleMoves;
  int flip = 1;
  if (board[y][x].color == black) {
    flip = -1;
  }

  array<int, 2> diagonalRight = {y - (1 * flip), x + (1 * flip)};
  array<int, 2> diagonalLeft = {y - (1 * flip), x - (1 * flip)};
  array<int, 2> forward = {y - (1 * flip), x};
  array<int, 2> forwardBy2 = {y - (2 * flip), x};
  array<int, 2> right = {y, x + (1 * flip)};
  array<int, 2> left = {y, x - (1 * flip)};

  cout << "\nTURN: " << board[y][x].turn << '\n';

  if (!check_for_piece(forward) && piece_in_boundaries(forward)) {
    possibleMoves.push(forward);
    if (!check_for_piece(forwardBy2) && piece_in_boundaries(forwardBy2) && board[y][x].turn == 1) {
      possibleMoves.push(forwardBy2);
    }
  }


  //en passent rules
  if (piece_in_boundaries(left) ) {
    if(board[left[0]][left[1]].enPassent == true && check_for_piece(left)){
      possibleMoves.push(left);
    }
  }
  if (piece_in_boundaries(right) ) {
    if(board[right[0]][right[1]].enPassent == true && check_for_piece(right)){
      possibleMoves.push(right);
    }
  }
  
  if (x == 0) { // if pawn is on right wall only check diagonal right
    if (check_for_piece(diagonalRight) &&
        board[diagonalRight[0]][diagonalRight[1]].color != board[y][x].color &&
        piece_in_boundaries(diagonalRight)) {
      possibleMoves.push(diagonalRight);
    }
  } else if (x == 7) { // if pawn is on left wall only check diagonal right
    if (check_for_piece(diagonalLeft) &&
        board[diagonalLeft[0]][diagonalLeft[1]].color != board[y][x].color &&
        piece_in_boundaries(diagonalLeft)) {
      possibleMoves.push(diagonalLeft);
    }
  } else { // else check both diagonal right and diagonal left
    if (check_for_piece(diagonalRight) &&
        board[diagonalRight[0]][diagonalRight[1]].color != board[y][x].color &&
        piece_in_boundaries(diagonalRight)) {
      possibleMoves.push(diagonalRight);
    }
    if (check_for_piece(diagonalLeft) &&
        board[diagonalLeft[0]][diagonalLeft[1]].color != board[y][x].color &&
        piece_in_boundaries(diagonalLeft)) {
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
      if (board[forward[0]][forward[1]].color == board[y][x].color) {
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
    if (board[forward[0]][forward[1]].color == board[y][x].color) {
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
      if (board[forward[0]][forward[1]].color == board[y][x].color) {
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
      if (board[forward[0]][forward[1]].color == board[y][x].color) {
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
  stack<array<int, 2> /**/> part1 = possible_bishop_moves(y, x);
  stack<array<int, 2> /**/> part2 = possible_rook_moves(y, x);
  while (!part1.empty()) {
    possibleMoves.push(part1.top());
    part1.pop();
  }
  while (!part2.empty()) {
    possibleMoves.push(part2.top());
    part2.pop();
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
    possibleMoves = possible_queen_moves(y, x);
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
  x[0] = 8 - (int(input[1]) - 48);
  x[1] = int(input[0]) - 97;
  cout << "position: " << x[0] << ", " << x[1] << '\n';
  return x;
}

bool move_piece(array<int, 2> position, array<int, 2> target) {
  int positionY = position[0];
  int positionX = position[1];
  int targetY = target[0];
  int targetX = target[1];
  bool ifFunctionWorked = false;
  // make a variable of the size of possible moves because possibleMoves.size()
  // changes when i use .pop() so store it in variable so it don't change


  //EN PASSENT CODE
  if(board[positionY][positionX].color == black){
    if(board[positionY][positionX].type == 'p' && targetY == positionY + 2 && board[positionY][positionX].turn == 1 && !check_for_piece(target)){ //if piece moving is a pawn
      cout << "ENPASSENT ON: " << targetY << ", " << targetX << '\n';
      // copy over properties of piece to target
      board[targetY][targetX].type = board[positionY][positionX].type;
      board[targetY][targetX].color = board[positionY][positionX].color;
      board[targetY][targetX].turn = board[positionY][positionX].turn;
      board[targetY][targetX].turn++;
      board[targetY][targetX].enPassent = true; //this is the special line

      // replace piece with empty spot
      board[positionY][positionX].type = '+';
      board[positionY][positionX].color = nothing;
      board[positionY][positionX].turn = 0;
      board[positionY][positionX].enPassent = false;

      ifFunctionWorked = true;
      return ifFunctionWorked;
    }
  }
  if(board[positionY][positionX].color == white){
    if(board[positionY][positionX].type == 'p' && targetY == positionY - 2 && board[positionY][positionX].turn == 1 && !check_for_piece(target)){ //if piece moving is a pawn
      cout << "ENPASSENT ON: " << targetY << ", " << targetX << '\n';
      // copy over properties of piece to target
      board[targetY][targetX].type = board[positionY][positionX].type;
      board[targetY][targetX].color = board[positionY][positionX].color;
      board[targetY][targetX].turn = board[positionY][positionX].turn;
      board[targetY][targetX].turn++;
      board[targetY][targetX].enPassent = true; //this is the special line

      // replace piece with empty spot
      board[positionY][positionX].type = '+';
      board[positionY][positionX].color = nothing;
      board[positionY][positionX].turn = 0;
      board[positionY][positionX].enPassent = false;

      ifFunctionWorked = true;
      return ifFunctionWorked;
    }
  }
  //END OF EN PASSENT CODE

  stack<array<int, 2> /* */> possibleMoves = possible_moves(position);
  int sizeOfPossibleMoves = possibleMoves.size();

  for (int i = 0; i < sizeOfPossibleMoves; i++) {
    if (possibleMoves.top()[0] == targetY &&
        possibleMoves.top()[1] == targetX) {
      // check if the target is a piece and if it is push it to taken pieces in
      // it's color
      if (check_for_piece(target)) {
        if (board[targetY][targetX].color == white) {
          takenWhite.push_back(board[targetY][targetX].type);
        } else {
          takenBlack.push_back(board[targetY][targetX].type);
        }
      }

      // copy over properties of piece to target
      board[targetY][targetX].type = board[positionY][positionX].type;
      board[targetY][targetX].color = board[positionY][positionX].color;
      board[targetY][targetX].turn = board[positionY][positionX].turn;
      board[targetY][targetX].turn++;

      // replace piece with empty spot
      board[positionY][positionX].type = '+';
      board[positionY][positionX].color = nothing;
      board[positionY][positionX].turn = 0;
      board[targetY][targetX].enPassent = false;


      ifFunctionWorked = true;
      break;
    } else {
      possibleMoves.pop();
    }
  }

  return ifFunctionWorked;
}

int main() {
  reset_board();
  nerd_display_board(emptyStack);
  while (true) {
    string input1;
    string input2;

    cout << "piece to move:\n";
    cin >> input1;
    array<int, 2> position = convert_chess_notation_to_array(input1);
    nerd_display_board(possible_moves(position));
    cout << "position to move to:\ny: ";
    cin >> input2;
    array<int, 2> target = convert_chess_notation_to_array(input2);
    move_piece(position, target);
    nerd_display_board(emptyStack);
  }
}
