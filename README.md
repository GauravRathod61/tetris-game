## group name :- "The Debuggers" 

## group members 
1. prince savaliya, ID :- 202401191
  lab group 3.
2. Raj kachhadiya, ID :- 202401255
lab group 4.
3. Gaurav Rathod, ID-202401178
lab group 3.
4. Tanish solanki, ID :- 202401264
lab group 4.
# 🎮 TETRIS - CLASSIC BLOCK FALLING GAME

## 📌 How to Play the Game

- **Game Start**: The game begins automatically upon running the program.
- **Controls**:
  - `A`: Move the tetromino left.
  - `D`: Move the tetromino right.
  - `S`: Move the tetromino down.
  - `W`: Rotate the tetromino.
  - `Space`: Hard drop (instantly places the tetromino at the lowest position).
  - `ESC`: Quit the game.
- **Objective**: Complete horizontal lines by properly placing the falling tetrominoes. Each cleared line awards **100 points**.
- **Game Over**: The game ends when the tetrominoes stack up to the top of the screen, leaving no space for new pieces.

## 🛠 How the Code Works

### 1️⃣ Grid and Tetrominoes

- **Grid**: The game operates on a **10x20 grid**, where tetrominoes fall from the top.
- **Tetromino Shapes**: The available tetromino shapes (I, O, T, S, Z, J, L) are stored in a **3D vector**, allowing easy access and manipulation.

### 2️⃣ Tetromino Class

- **Purpose**: Represents the individual pieces that move and rotate.
- **Attributes**: Stores the shape of the tetromino and its current position `(x, y)` on the grid.
- **Rotation**: The `rotate()` function allows tetrominoes to rotate by 90 degrees using matrix transformation.

### 3️⃣ Game Logic

Managed by the `Game` class:

- **User Input Handling**: Detects key presses to move or rotate the tetromino accordingly.
- **Collision Detection**: Ensures tetrominoes do not overlap with existing blocks or move out of bounds.
- **Merging Pieces**: When a tetromino reaches the bottom, it gets merged into the grid and stays there permanently.
- **Clearing Lines**: A row is removed when all its cells are filled, shifting the above rows down and increasing the score.
- **Rendering**: The game state is printed in the console, displaying tetrominoes and empty spaces.
- **Game Over Condition**: If a new tetromino collides immediately after spawning, the game ends.

### 4️⃣ Game Loop

The main loop continues until `gameOver` is `true`:

1. Handles player input.
2. Moves the active tetromino down.
3. Checks for collisions and merges pieces.
4. Clears full lines and updates the score.
5. Renders the updated grid.
6. Waits for a short duration to control the speed.

## 🖥 Supported Operating System

- **Windows**: The game uses:
  - `windows.h` for clearing the console screen.
  - Functions from `conio.h` for handling real-time user input.
  - `Sleep()` function for controlling game speed.
- **Linux/macOS**: For compatibility:
  - Replace `system("cls")` with `system("clear")`.
  - Use alternative methods for real-time key detection since `conio.h` is Windows-specific.
  - Replace `Sleep(milliseconds)` with `usleep(microseconds)` (from `unistd.h`).



Enjoy playing **Tetris Clone**! 🚀
