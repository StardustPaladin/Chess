#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;


// Chess Game
// This is a simplified chess game created in C++.
// Two players can move pieces and capture pieces.
// This version does not include advanced chess rules such as:
// - Check
// - Checkmate
// - Castling
// - En passant
// - Pawn promotion


// ChessGame Class
// This class contains the chess board and the functions needed
// to operate the game.

class ChessGame
{
private:

    // A two-dimensional STL vector represents the board.
    // Each character represents a chess piece.
    // White:
    // P = Pawn
    // R = Rook
    // N = Knight
    // B = Bishop
    // Q = Queen
    // K = King
    // Black uses lowercase letters.
    // . = Empty square
    vector<vector<char>> board;

    // W means White's turn.
    // B means Black's turn.
    char currentPlayer;


public:
    // Constructor
    // The constructor creates an empty board, sets White as
    // the first player, and places all of the pieces.

    ChessGame()
    {
        currentPlayer = 'W';

        // Create an 8 x 8 board.
        // Every square starts as an empty period.
        board = vector<vector<char>>(8, vector<char>(8, '.'));

        setupBoard();
    }
    // setupBoard
    // Places all chess pieces in their starting positions.

    void setupBoard()
    {
        // Black's major pieces

        board[0][0] = 'r';
        board[0][1] = 'n';
        board[0][2] = 'b';
        board[0][3] = 'q';
        board[0][4] = 'k';
        board[0][5] = 'b';
        board[0][6] = 'n';
        board[0][7] = 'r';

        // Black's pawns

        for (int column = 0; column < 8; column++)
        {
            board[1][column] = 'p';
        }
        // White's major pieces

        board[7][0] = 'R';
        board[7][1] = 'N';
        board[7][2] = 'B';
        board[7][3] = 'Q';
        board[7][4] = 'K';
        board[7][5] = 'B';
        board[7][6] = 'N';
        board[7][7] = 'R';

        // White's pawns

        for (int column = 0; column < 8; column++)
        {
            board[6][column] = 'P';
        }
    }


    // displayBoard
    // Displays the current board to the console.

    void displayBoard()
    {
        cout << "\n";
        cout << "       A B C D E F G H\n";
        cout << "     -----------------\n";

        for (int row = 0; row < 8; row++)
        {
            // Chess rows go from 8 down to 1.
            cout << " " << (8 - row) << " |  ";

            for (int column = 0; column < 8; column++)
            {
                cout << board[row][column] << " ";
            }

            cout << " | " << (8 - row) << "\n";
        }

        cout << "     -----------------\n";
        cout << "       A B C D E F G H\n";
        cout << "\n";
    }

    // columnToIndex
    // Converts a chess column such as A or E into a vector
    // index.
    //
    // A = 0
    // B = 1
    // C = 2
    // ...
    // H = 7

    int columnToIndex(char column)
    {
        column = static_cast<char>(toupper(column));

        return column - 'A';
    }

    // rowToIndex
    // Converts a chess row into a vector index.
    //
    // Chess row 8 = vector row 0
    // Chess row 1 = vector row 7

    int rowToIndex(char row)
    {
        return 8 - (row - '0');
    }


    // isInsideBoard
    // Checks whether a row and column are inside the board.

    bool isInsideBoard(int row, int column)
    {
        return row >= 0 &&
            row < 8 &&
            column >= 0 &&
            column < 8;
    }
    // belongsToCurrentPlayer
    // Determines whether a piece belongs to the player whose
    // turn it currently is.

    bool belongsToCurrentPlayer(char piece)
    {
        if (piece == '.')
        {
            return false;
        }

        if (currentPlayer == 'W')
        {
            return isupper(static_cast<unsigned char>(piece));
        }

        return islower(static_cast<unsigned char>(piece));
    }


    // belongsToOpponent
    // Determines whether a piece belongs to the opponent.

    bool belongsToOpponent(char piece)
    {
        if (piece == '.')
        {
            return false;
        }

        if (currentPlayer == 'W')
        {
            return islower(static_cast<unsigned char>(piece));
        }

        return isupper(static_cast<unsigned char>(piece));
    }


    // validPawnMove
    // Checks whether a pawn can make the requested move.
    // Simplified pawn rules:
    // - Move forward one square
    // - Capture diagonally
    // The normal two-square opening pawn move is not included.
    // validPawnMove
    // Checks whether a pawn can make the requested move.
    // Pawn rules:
    // 1. Move forward one square.
    // 2. Move forward two squares on its first move.
    // 3. Capture diagonally one square.

    bool validPawnMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        int direction;

        // White moves toward row 0.
        // Black moves toward row 7.
        if (currentPlayer == 'W')
        {
            direction = -1;
        }
        else
        {
            direction = 1;
        }

        // RULE 1:
        // Pawn moves forward one square.

        if (startColumn == endColumn &&
            endRow == startRow + direction &&
            board[endRow][endColumn] == '.')
        {
            return true;
        }
        // RULE 2:
        // Pawn can move forward two squares on its first move.
        // White pawns start at row 6.
        // Black pawns start at row 1.

        bool firstMove = false;

        if (currentPlayer == 'W' && startRow == 6)
        {
            firstMove = true;
        }
        else if (currentPlayer == 'B' && startRow == 1)
        {
            firstMove = true;
        }

        if (firstMove &&
            startColumn == endColumn &&
            endRow == startRow + (2 * direction) &&
            board[startRow + direction][startColumn] == '.' &&
            board[endRow][endColumn] == '.')
        {
            return true;
        }

        // RULE 3:
        // Pawn captures one square diagonally.

        if (abs(endColumn - startColumn) == 1 &&
            endRow == startRow + direction &&
            belongsToOpponent(board[endRow][endColumn]))
        {
            return true;
        }

        // If none of the rules were satisfied, the move
        // is invalid.
        return false;
    }
    // validRookMove
    // Rooks move horizontally or vertically.

    bool validRookMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        // A rook cannot move diagonally.
        if (startRow != endRow &&
            startColumn != endColumn)
        {
            return false;
        }

        return pathIsClear(
            startRow,
            startColumn,
            endRow,
            endColumn);
    }
    // validBishopMove
    // Bishops move diagonally.

    bool validBishopMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        int rowDifference = abs(endRow - startRow);
        int columnDifference = abs(endColumn - startColumn);

        // Diagonal movement requires equal differences.
        if (rowDifference != columnDifference)
        {
            return false;
        }

        return pathIsClear(
            startRow,
            startColumn,
            endRow,
            endColumn);
    }
    // validKnightMove
    // Knights move in an L shape.

    bool validKnightMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        int rowDifference = abs(endRow - startRow);
        int columnDifference = abs(endColumn - startColumn);

        return
            (rowDifference == 2 && columnDifference == 1) ||
            (rowDifference == 1 && columnDifference == 2);
    }


    // validQueenMove
    // Queens can move like rooks or bishops.

    bool validQueenMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        int rowDifference = abs(endRow - startRow);
        int columnDifference = abs(endColumn - startColumn);

        // Check for horizontal movement.
        bool horizontal = startRow == endRow;

        // Check for vertical movement.
        bool vertical = startColumn == endColumn;

        // Check for diagonal movement.
        bool diagonal = rowDifference == columnDifference;

        if (horizontal || vertical || diagonal)
        {
            return pathIsClear(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        return false;
    }

    // validKingMove
    // Kings can move one square in any direction.

    bool validKingMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        int rowDifference = abs(endRow - startRow);
        int columnDifference = abs(endColumn - startColumn);

        if (rowDifference <= 1 &&
            columnDifference <= 1 &&
            !(rowDifference == 0 &&
                columnDifference == 0))
        {
            return true;
        }

        return false;
    }
    // pathIsClear
    // Checks whether a piece can move from its starting square
    // to its destination without another piece blocking it.
    // This is used by rooks, bishops, and queens.

    bool pathIsClear(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        int rowStep = 0;
        int columnStep = 0;

        // Determine which direction the row should move.
        if (endRow > startRow)
        {
            rowStep = 1;
        }
        else if (endRow < startRow)
        {
            rowStep = -1;
        }

        // Determine which direction the column should move.
        if (endColumn > startColumn)
        {
            columnStep = 1;
        }
        else if (endColumn < startColumn)
        {
            columnStep = -1;
        }

        int row = startRow + rowStep;
        int column = startColumn + columnStep;

        // Continue until the destination is reached.
        while (row != endRow || column != endColumn)
        {
            // If another piece is found, the path is blocked.
            if (board[row][column] != '.')
            {
                return false;
            }

            row += rowStep;
            column += columnStep;
        }

        return true;
    }
    // validMove
    // This function decides which movement function should be
    // used based on the type of chess piece.
    bool validMove(
        int startRow,
        int startColumn,
        int endRow,
        int endColumn)
    {
        // Make sure both positions are on the board.
        if (!isInsideBoard(startRow, startColumn) ||
            !isInsideBoard(endRow, endColumn))
        {
            return false;
        }

        char piece = board[startRow][startColumn];

        // There must be a piece at the starting position.
        if (piece == '.')
        {
            return false;
        }

        // Players can only move their own pieces.
        if (!belongsToCurrentPlayer(piece))
        {
            return false;
        }

        // A player cannot capture their own piece.
        if (belongsToCurrentPlayer(board[endRow][endColumn]))
        {
            return false;
        }

        // Convert the piece to uppercase so the same movement
        // rules can be used for both players.
        char type = static_cast<char>(toupper(piece));

        if (type == 'P')
        {
            return validPawnMove(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        if (type == 'R')
        {
            return validRookMove(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        if (type == 'N')
        {
            return validKnightMove(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        if (type == 'B')
        {
            return validBishopMove(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        if (type == 'Q')
        {
            return validQueenMove(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        if (type == 'K')
        {
            return validKingMove(
                startRow,
                startColumn,
                endRow,
                endColumn);
        }

        return false;
    }
    // movePiece
    // Attempts to move a piece from one square to another.

    bool movePiece(string start, string destination)
    {
        // Chess coordinates should contain exactly two characters.
        if (start.length() != 2 ||
            destination.length() != 2)
        {
            return false;
        }

        // Convert the user's input into board indexes.
        int startColumn = columnToIndex(start[0]);
        int startRow = rowToIndex(start[1]);

        int endColumn = columnToIndex(destination[0]);
        int endRow = rowToIndex(destination[1]);

        // Make sure the letters and numbers are valid.
        if (!isInsideBoard(startRow, startColumn) ||
            !isInsideBoard(endRow, endColumn))
        {
            return false;
        }

        // Check whether the move follows the piece's rules.
        if (!validMove(
            startRow,
            startColumn,
            endRow,
            endColumn))
        {
            return false;
        }

        // Check for a capture.
        if (board[endRow][endColumn] != '.')
        {
            cout << "\n*** Piece captured! ***\n";
        }

        // Move the piece.
        board[endRow][endColumn] =
            board[startRow][startColumn];

        // Empty the original square.
        board[startRow][startColumn] = '.';

        return true;
    }
    // changeTurn
    // Changes the current player after a successful move.

    void changeTurn()
    {
        if (currentPlayer == 'W')
        {
            currentPlayer = 'B';
        }
        else
        {
            currentPlayer = 'W';
        }
    }
    // displayTurn
    // Displays which player's turn it is.

    void displayTurn()
    {
        if (currentPlayer == 'W')
        {
            cout << "White's turn.\n";
        }
        else
        {
            cout << "Black's turn.\n";
        }
    }
    // play
    // Runs the main game loop.

    void play()
    {
        string start;
        string destination;

        cout << "====================================\n";
        cout << "       SIMPLE C++ CHESS GAME\n";
        cout << "====================================\n";

        cout << "\nHow to play:\n";
        cout << "Enter the starting square and destination square.\n";
        cout << "Example: E2 E3\n";
        cout << "\n";
        cout << "Type 'quit' at any time to exit.\n";

        while (true)
        {
            displayBoard();

            displayTurn();

            cout << "\nStarting square: ";
            cin >> start;

            // Allow the player to quit.
            if (start == "quit" ||
                start == "QUIT" ||
                start == "Quit")
            {
                cout << "\nGame ended.\n";
                break;
            }

            cout << "Destination square: ";
            cin >> destination;

            // Allow the player to quit.
            if (destination == "quit" ||
                destination == "QUIT" ||
                destination == "Quit")
            {
                cout << "\nGame ended.\n";
                break;
            }

            // Try to make the move.
            if (movePiece(start, destination))
            {
                cout << "\nMove successful!\n";

                // Change players after a successful move.
                changeTurn();
            }
            else
            {
                cout << "\nInvalid move!\n";
                cout << "Please try again.\n";
            }
        }
    }
};


// main
// The main function creates a ChessGame object and starts the
// game.

int main()
{
    // Create the chess game.
    ChessGame game;

    // Start playing.
    game.play();

    // Tell Windows the program ended successfully.
    return 0;
}
