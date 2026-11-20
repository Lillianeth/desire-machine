
#include "Graphics.h"
#include <iostream>
#include <string>

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

//MAINN!!
int main() {

    //create the application window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1000, 800, "Happiness Machines");
    SetTargetFPS(60);


    // --------LOAD RESEARCH IMAGES HERE! --------

    Texture2D researchImages[ResearchSlideCount] = {};

    string imageDirectory = GetApplicationDirectory();
    imageDirectory += "img/";

    for (int i = 0; i < ResearchSlideCount; i++) {

        //get the image filename for the current slide
        ResearchSlide research = GetResearchSlide(i);
        string imageName = research.image;

        if (imageName.size() > 0) {

            string path = imageDirectory + imageName;

            //load the image only if the file exists
            if (FileExists(path.c_str())) {
                researchImages[i] = LoadTexture(path.c_str());
            }
        }
    }

    //-------- INITIAL VARIABLES --------

    // 0 = Welcome
    // 1 = Research
    // 2 = Experiment
    // 3 = Fictional Offers
    // 4 = Results

    int currentScreen = 0;
    int slide = 0;

    //create an object from our HappinessMachine class
    HappinessMachine machine;


    //-------- MAIN APPLICATION LOOP --------

    while (!WindowShouldClose()) {


        //-------- HANDLE USER INPUT --------

        // WELCOME SCREEN
        if (currentScreen == 0) {

            if (IsButtonClicked(Explore)) {

                slide = 0;
                currentScreen = 1;
            }
        }


        //--------RESEARCH SCREEN
        else if (currentScreen == 1) {

            if (IsButtonClicked(Home)) {
                currentScreen = 0;
            }
            else if (IsButtonClicked(Previous) && slide > 0) {
                slide--;
            }
            else if (IsButtonClicked(Next)) {

                //move to the next research slide
                if (slide < ResearchSlideCount - 1) {
                    slide++;
                }
                else {

                    //start the experiment after the last slide
                    machine.Start();

                    LogTree(machine.Depth());

                    currentScreen = 2;
                }
            }
        }


        //---------EXPERIMENT SCREEN
        else if (currentScreen == 2) {

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


        //-------------FICTIONAL OFFERS SCREEN
        else if (currentScreen == 3) {

            //stop early and view the results
            if (machine.GetOfferCount() < OfferLimit && IsButtonClicked(Home)) {

                currentScreen = 4;
            }

            //get another offer or finish the experiment
            else if (IsButtonClicked(Next)) {

                if (machine.GetOfferCount() == OfferLimit) {

                    currentScreen = 4;
                }
                else {

                    machine.Recommend();

                    LogTree(machine.Depth());
                }
            }
        }


        //--------------ESULTS SCREEN
        else if (currentScreen == 4) {

            //return to the welcome screen
            if (IsButtonClicked(Home)) {

                currentScreen = 0;
            }

            //restart the experiment
            else if (IsButtonClicked(Next)) {

                machine.Start();

                LogTree(machine.Depth());

                currentScreen = 2;
            }
        }


        //-------- DRAW THE CURRENT SCREEN --------

        BeginDrawing();

        ClearBackground({ 15, 23, 42, 255 });


        if (currentScreen == 0) {

            DrawWelcomeScreen();
        }
        else if (currentScreen == 1) {

            DrawResearchScreen(
                slide,
                researchImages[slide]
            );
        }
        else if (currentScreen == 2) {

            DrawExperiment(
                machine.GetCurrentScenario(),
                machine.GetDecisionCount(),
                machine.Depth()
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

        EndDrawing();
    }


    //--------------RELEASE RESEARCH IMAGES --------

    for (int i = 0; i < ResearchSlideCount; i++) {

        if (IsTextureValid(researchImages[i])) {
            UnloadTexture(researchImages[i]);
        }
    }


    //close the application
    CloseWindow();

    return 0;
}
