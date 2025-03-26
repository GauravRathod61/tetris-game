#include <iostream>
#include <vector>
#include <windows.h> 
#include <conio.h>   
#include <ctime> 

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// Tetromino shapes (I, O, T, S, Z, J, L)
const vector<vector<vector<int>>> TETROMINOES = {
    // I-piece
    {{1, 1, 1, 1}},
    // O-piece
    {{1, 1}, {1, 1}},
    // T-piece
    {{0, 1, 0}, {1, 1, 1}},
    // S-piece
    {{0, 1, 1}, {1, 1, 0}},
    // Z-piece
    {{1, 1, 0}, {0, 1, 1}},
    // J-piece
    {{1, 0, 0}, {1, 1, 1}},
    // L-piece
    {{0, 0, 1}, {1, 1, 1}}
};

class Tetromino {
public:
    vector<vector<int>> shape;
    int x, y;

    Tetromino(vector<vector<int>> s) : shape(s), x(WIDTH / 2 - s[0].size() / 2), y(0) {}

    void rotate() {
        int rows = shape.size(), cols = shape[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows, 0));

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                rotated[j][rows - 1 - i] = shape[i][j];

        shape = rotated;
    }
};

class Game {
private:
    vector<vector<int>> grid;
    Tetromino* currentPiece;
    int score;
    bool gameOver;

    bool checkCollision(const Tetromino& piece) {
        for (int i = 0; i < piece.shape.size(); ++i) {
            for (int j = 0; j < piece.shape[i].size(); ++j) {
                if (piece.shape[i][j]) {
                    int newX = piece.x + j;
                    int newY = piece.y + i;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && grid[newY][newX])) {
                        return true;                    }
                }
            }
        }
        return false;
    }

    void mergePiece(const Tetromino& piece) {
        for (int i = 0; i < piece.shape.size(); ++i) {
            for (int j = 0; j < piece.shape[i].size(); ++j) {
                if (piece.shape[i][j]) {
                    grid[piece.y + i][piece.x + j] = 1;
                }
            }
        }
    }

    void clearLines() {
        for (int i = HEIGHT - 1; i >= 0; --i) {
            bool full = true;
            for (int j = 0; j < WIDTH; ++j) {
                if (!grid[i][j]) {
                    full = false;
                    break;
                }
            }
            if (full) {
                grid.erase(grid.begin() + i);
                grid.insert(grid.begin(), vector<int>(WIDTH, 0));
                score += 100;
            }
        }
    }

public:

    Game() : grid(HEIGHT, vector<int>(WIDTH, 0)), score(0), gameOver(false) {
        srand(static_cast<unsigned>(time(0)));
        currentPiece = new Tetromino(TETROMINOES[rand() % TETROMINOES.size()]);
    }

    ~Game() {
        delete currentPiece;
    }

    void handleInput() {
        if (_kbhit()) {
            char key = _getch();
            Tetromino temp = *currentPiece;
            switch (key) {
                case 'a': temp.x--; break; // Move left
                case 'd': temp.x++; break; // Move right
                case 's': temp.y++; break; // Move down
                case 'w': temp.rotate(); break; // Rotate
                case ' ': while (!checkCollision(temp)) temp.y++; temp.y--; break; // Hard drop
                case 27: gameOver = true; break; // ESC to quit
            }
            if (!checkCollision(temp)) *currentPiece = temp;
        }
    }

    void update() {
        Tetromino temp = *currentPiece;
        temp.y++;
        if (checkCollision(temp)) {
            mergePiece(*currentPiece);
            clearLines();
            delete currentPiece;
            currentPiece = new Tetromino(TETROMINOES[rand() % TETROMINOES.size()]);
            if (checkCollision(*currentPiece)) gameOver = true;
        } else {
            *currentPiece = temp;
        }
    }

    void render() {
        system("cls"); // Clear the console
        vector<vector<int>> display = grid;

        for (int i = 0; i < currentPiece->shape.size(); ++i) {
            for (int j = 0; j < currentPiece->shape[i].size(); ++j) {
                if (currentPiece->shape[i][j] && (currentPiece->y + i) >= 0) {
                    display[currentPiece->y + i][currentPiece->x + j] = 1;
                }
            }
        }

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                cout << (display[i][j] ? "[]" : " .");
            }
            cout << endl;
        }

        cout << "Score: " << score << endl;
        if (gameOver) cout << "Game Over!" << endl;
    }

    bool isGameOver() const {
        return gameOver;
    }
};

int main() {
    Game game;
    while (!game.isGameOver()) {
        game.handleInput();
        game.update();
        game.render();
        Sleep(200); // Adjust game speed
    }
    return 0;
}
