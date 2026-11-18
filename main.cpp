#include <iostream>
#include "raylib.h"
#include "Graphics.h"

using namespace std;

int main() {
    cout << "Hello CSC 103!" << endl;
    cout << "This is Team 1's Hackathon project!" << endl;

    InitWindow(1000, 800, "Desire Machine");
    SetTargetFPS(30);

    int currentScreen = 0;

    while (!WindowShouldClose()) {

        //test to print something in the terminal when START is clicked
        if (currentScreen == 0) {

            Rectangle startButton = { 350, 460, 300, 65 };

            if (IsButtonClicked(startButton)) {
                currentScreen = 1;
                cout << "Opening simulation..." << endl;
            }
        }

        BeginDrawing();

        ClearBackground(Color{ 15, 23, 42, 255 });

        if (currentScreen == 0) {
            DrawWelcomeScreen();
        }
        else if (currentScreen == 1) {
            DrawText("SIMULATION SCREEN", 300, 200, 40, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}