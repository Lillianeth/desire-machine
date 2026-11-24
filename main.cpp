#include <iostream>
#include "Graphics.h"
#include "rlgl.h"
#include <string>
using namespace std;

int main() {

    //original size of our gui
    int gameWidth = 1400;
    int gameHeight = 900;

    //create the window
    InitWindow(gameWidth, gameHeight, "Happiness Machines");

    //get the monitor resolution
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    //make the window fullscreen
    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen();

    SetTargetFPS(60);

    //calculate how much we need to enlarge the gui
    float scaleX = (float)GetScreenWidth() / gameWidth;
    float scaleY = (float)GetScreenHeight() / gameHeight;

    //use the smaller scale to avoid stretching
    float scale = scaleX;

    if (scaleY < scaleX) {
        scale = scaleY;
    }

    //calculate the space around our gui
    int offsetX = (GetScreenWidth() - gameWidth * scale) / 2;
    int offsetY = (GetScreenHeight() - gameHeight * scale) / 2;

    //adjust the mouse coordinates for the new size
    SetMouseOffset(-offsetX, -offsetY);
    SetMouseScale(1.0f / scale, 1.0f / scale);

    //load the research images
    Texture2D researchImages[ResearchSlideCount] = {};

    //string imageDirectory = GetApplicationDirectory();
    //location of our research images
    string imageDirectory = "../../../img/";
    cout << "Looking for images in: " << imageDirectory << endl;

    for (int i = 0; i < ResearchSlideCount; i++) {

        ResearchSlide research = GetResearchSlide(i);
        string imageName = research.image;

        //check if this slide has an image
        if (imageName.size() > 0) {

            string path = imageDirectory + imageName;

            //load the image if the file exists
            if (FileExists(path.c_str())) {
                researchImages[i] = LoadTexture(path.c_str());
            }
        }
    }
    //screens
    //0 = welcome
    //1 = research
    //2 = experiment
    //3 = offers
    //4 = results

    int currentScreen = 0;
    int slide = 0;

    //when the player made a decision
    double lastChoiceTime = -10.0;

    //which color the tree should use?
    Color treeColor = MAGENTA;

    //create the happiness machine object
    HappinessMachine machine;

    //main loop
    while (!WindowShouldClose()) {

        //welcome screen
        if (currentScreen == 0) {
            cout << "Youre in screen 0";

            if (IsButtonClicked(Explore)) {
                cout << "Explore clicked...";
                slide = 0;
                currentScreen = 1;
            }
            else if (IsButtonClicked(Credits)) {
                currentScreen = 5;
            }
        }
        //research screen
        else if (currentScreen == 1) {

            if (IsButtonClicked(Home)) {
                cout << "Home clicked...";
                currentScreen = 0;
            }
            else if (IsButtonClicked(Previous) && slide > 0) {
                slide--;
            }
            else if (IsButtonClicked(Next)) {

                if (slide < ResearchSlideCount - 1) {
                    slide++;
                }
                else {
                    machine.Start();
                    currentScreen = 2;
                }
            }
        }

        //experiment screen
        else if (currentScreen == 2) {

            //first choice
            if (IsButtonClicked(FirstChoice)) {
                machine.Choose(true);

                lastChoiceTime = GetTime();
                treeColor = LIME;
            }

            //second choice
            else if (IsButtonClicked(SecondChoice)) {
                machine.Choose(false);

                lastChoiceTime = GetTime();
                treeColor = SKYBLUE;
            }

            //start the offers after ten decisions
            if (machine.GetDecisionCount() == ScenarioCount) {
                machine.Recommend();
                currentScreen = 3;
            }
        }
        //offers screen
        else if (currentScreen == 3) {

            //stop and view results
            if (IsButtonClicked(Home)) {
                currentScreen = 4;
            }
            else if (IsButtonClicked(Next)) {

                if (machine.GetOfferCount() == OfferLimit) {
                    currentScreen = 4;
                }
                else {
                    machine.Recommend();
                }
            }
        }

        //results screen
        else if (currentScreen == 4) {

            if (IsButtonClicked(Home)) {
                currentScreen = 0;
            }
            else if (IsButtonClicked(Next)) {
                machine.Start();
                currentScreen = 2;
            }
        }
        //credits screen
        else if (currentScreen == 5) {
            if (IsButtonClicked(Home)) {
                currentScreen = 0;
            }
        }
        //return the tree to its original color after half a second
        if (GetTime() - lastChoiceTime >= 0.5) {
            treeColor = MAGENTA;
        }


        //draw the current screen
        BeginDrawing();

        ClearBackground({ 121, 101, 155, 255 });

        //move and enlarge the gui
        rlPushMatrix();
        rlTranslatef(offsetX, offsetY, 0);
        rlScalef(scale, scale, 1.0f);


        if (currentScreen == 0) {
            DrawWelcomeScreen();
        }
        else if (currentScreen == 1) {
            DrawResearchScreen(slide, researchImages[slide]);
        }
        else if (currentScreen == 2) {
            DrawExperiment(
                machine.GetCurrentScenario(),
                machine.GetDecisionCount(),
                machine.Depth(),
                machine.GetTotals(),
                treeColor//omg!! 
            );
        }
        else if (currentScreen == 3) {
            DrawOffer(
                machine.GetProduct(),
                machine.GetPitch(),
                machine.GetOfferCount(),
                machine.Depth()
            );
        }
        else if (currentScreen == 4) {
            DrawResults(
                machine.GetTotals(),
                machine.GetDecisions(),
                machine.GetOfferCount()
            );
        }
        else if (currentScreen == 5) {
            DrawCreditsScreen();
        }

        //finish scaling the gui
        rlPopMatrix();

        EndDrawing();
    }
    //unload the research images
    for (int i = 0; i < ResearchSlideCount; i++) {

        if (IsTextureValid(researchImages[i])) {
            UnloadTexture(researchImages[i]);
        }
    }
    //close the window
    CloseWindow();

    return 0;
}

