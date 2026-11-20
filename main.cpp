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
    int slide = 0;
    int totalSlides = 5;
    // Texture researchImage = LoadTexture("cats-img.jpg");
    Texture researchImages[totalSlides] = {
    LoadTexture("./images/research-1.jpg"),
    LoadTexture("./images/research-2.jpg"),
    LoadTexture("./images/research-3.jpg"),
    LoadTexture("./images/research-4.jpg"),
    LoadTexture("./images/research-5.jpg")
    };
    // asked gemini: how to load an image in raylib?

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(Color(ORANGE));

        if (currentScreen == 0) {
            DrawWelcomeScreen();
            //Rectangle startButton = { 340, 535, 320, 60 };

            if (IsButtonClicked(Explore)) {
                currentScreen = 1;
            }
        }

        else if (currentScreen == 1) { // enter in presentation mode and draw slides
            DrawResearchScreen(slide, researchImages[slide]);

            if (IsButtonClicked(Home)) {
                currentScreen = 0;
                slide = 0;
            }
            else if (IsButtonClicked(Next) && slide < totalSlides - 1) { // slide < 4 because it's from 0 to 4 (5 slides total)
                slide++;
            }
            else if (IsButtonClicked(Previous) && slide > 0) {
                slide--;
        }
    }

        EndDrawing();
    }
    for (int i = 0; i < totalSlides; i++) {
        UnloadTexture(researchImages[i]);
    }
    CloseWindow();

    return 0;
}