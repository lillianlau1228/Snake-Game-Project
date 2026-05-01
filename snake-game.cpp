#include <iostream>
#include <vector>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

using namespace std;

// Global Variables (To be managed by the Architect)
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Tail Data (For the Growth Specialist - Week 8 Arrays/Vectors)
vector<int> tailX(100), tailY(100); 
int nTail;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    // UI Designer: Implement the nested loops to draw the map, snake, and fruit
    system("cls"); // Clears the console
    
    // Example: Top Wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    // Logic for middle rows, snake head ('O'), and tail ('o') goes here...
    for (int mapY = 0; mapY < height; mapY++) {
        cout << "#";
        for (int mapX = 0; mapX < width; mapX++) {
            if ((mapX == x) && (mapY == y)) {
                cout << "O";
            }
            else if ((mapX == fruitX) && (mapY == fruitY)) {
                cout << "F";
            }
            else {
                bool print = false;
                for (int i = 0; i < nTail; ++i) {
                    if ((tailX[i] == mapX) && (tailY[i] == mapY)) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << "#" << endl;
    }

    // Bottom Wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }

    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    // Physics Lead: Handle key presses (W, A, S, D)
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    // Architect & Growth Specialist:
    // 4. Check if fruit is eaten (if x == fruitX && y == fruitY)
    if ((x == fruitX) && (y == fruitY)) {
        score += 10;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    // 1. Update tail positions (shifting coordinates in the vector)
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 2. Update head position based on 'dir'
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // 3. Check for collisions (Wall or Self)
    if (x>= width) {
        x=0;
    }
    else if (x < 0) {
        x = width;
    }

    if(y>= height) {
        y = 0;
    }
    else if (y < 0) {
        y = height;
    }

    for (int i =0; i < nTail; i++) {
        if ((tailX[i] == x) && (tailY[i] == y)) {
            gameOver = true;
        }
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Controls game speed
    }
    return 0;
}