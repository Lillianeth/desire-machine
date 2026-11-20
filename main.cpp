#include <iostream>
#include "raylib.h"
#include "Graphics.h"
#include "HappinessMachine.h"

using namespace std;

void LogTree(int depth) {
    /*
        displays info about the recursive tree in terminal
        parameter:
            depth: number of levels in the tree
    */

    //calculate the number of visible branches
    int segments = BranchCount(depth);

    //count all recursive calls, including the base cases
    int calls = 2 * segments + 1;

    cout << "Tree depth: " << depth << endl;
    cout << "Branch segments: " << segments << endl;
    cout << "Recursive calls: " << calls << endl;
}

int main() {

    HappinessMachine machine;

    cout << "Hello CSC 103!" << endl;
    cout << "This is Team 1's Hackathon project!" << endl;

    InitWindow(1000, 800, "Desire Machine");
    SetTargetFPS(30);

    int currentScreen = 0;
    int slide = 0;
    int totalSlides = 5;
    // Texture researchImage = LoadTexture("cats-img.jpg");
    Texture researchImages[totalSlides] = {
    LoadTexture("research-1.jpg"),
    LoadTexture("research-2.jpg"),
    LoadTexture("research-3.jpg"),
    LoadTexture("research-4.jpg"),
    LoadTexture("research-5.jpg")
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

        else if (currentScreen == 1) {

            DrawResearchScreen(slide, researchImages[slide]);

            if (IsButtonClicked(Home)) {
                currentScreen = 0;
                slide = 0;
            }
            else if (IsButtonClicked(Previous) && slide > 0) {
                slide--;
            }
            else if (IsButtonClicked(Next)) {

                if (slide < totalSlides - 1) {
                    slide++;
                }
                else {
                    machine.Start();
                    LogTree(machine.Depth());
                    currentScreen = 2;
                }
            }
        }

        else if (currentScreen == 2) {

            DrawExperiment(
                machine.GetCurrentScenario(),
                machine.GetDecisionCount(),
                machine.Depth()
            );

            //check whether the first choice was selected
            if (IsButtonClicked(FirstChoice)) {

                machine.Choose(true);

                LogTree(machine.Depth());
            }

            //check whether the second choice was selected
            else if (IsButtonClicked(SecondChoice)) {

                machine.Choose(false);

                LogTree(machine.Depth());
            }

            //after ten decisions, open the offers screen
            if (machine.GetDecisionCount() == ScenarioCount) {

                machine.Recommend();

                currentScreen = 3;
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