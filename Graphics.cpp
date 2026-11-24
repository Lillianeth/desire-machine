#include "Graphics.h"
#include <cmath>
using namespace std;

//colors for the application
const Color Navy = { 121, 101, 155, 255 };   //background
const Color PanelColor = { 67, 49, 94, 255 };   //dark panels
const Color Teal = { 118, 255, 234, 255 };   //cyan titles/buttons
const Color Lavender = { 255, 186, 138, 255 }; //peach/orange accent
const Color Ink = { 241, 236, 245, 255 };  //main light text
const Color Muted = { 220, 210, 230, 255 };  //secondary text
const Color TreePink = { 255, 0, 255, 255 };  //tree branches

class Branch {
    /*this piece of code is inspired in the raylib example "recursive tree" created by Jopestpe
    https://www.raylib.com/examples/shapes/loader.html?name=shapes_recursive_tree

    also checked this resources:
    https://natureofcode.com/fractals/#trees
    https://www.youtube.com/watch?v=0jjeOYMjmDU

    asked gemini:
        how does drawlineex work in Raylib?
        what is this formula doing: ...?
        typedefs and classes are the same?
        remind me how to apply recursion in c++
        what is wrong with initializing global variables vs doing it in main?*/
public:
    Vector2 start;
    Vector2 end;
    float angle;
    float length;
};

//tree settings
const float branchDecay = 0.66f;
const float branchAngle = 50.0f * DEG2RAD;

//draws the branches using recursion
void drawBranch(Branch branch, int currentDepth, int targetDepth, Color treeColor) {
    /*draws a fractal tree using recursion
        parameters:
            branch: current branch
            currentDepth: current generation
            targetDepth: number of generations to draw
        returns:
            nothing*/
    //draw the current branch
    DrawLineEx(branch.start, branch.end, 2.0f, treeColor);
    // asked gemini: "how does drawlineex work in Raylib?"
    //base case
    if (currentDepth >= targetDepth) {
        return;
    }
    //calculate the next branch length
    float nextLength = branch.length * branchDecay;
   
    //left branch
    float angle1 = branch.angle + branchAngle;

    Branch leftBranch;
    leftBranch.start = branch.end;
    leftBranch.angle = angle1;
    leftBranch.length = nextLength;

    leftBranch.end = {
        branch.end.x + nextLength * sinf(angle1),
        branch.end.y - nextLength * cosf(angle1)
    };
    //right branch
    float angle2 = branch.angle - branchAngle;

    Branch rightBranch;
    rightBranch.start = branch.end;
    rightBranch.angle = angle2;
    rightBranch.length = nextLength;

    rightBranch.end = {
        branch.end.x + nextLength * sinf(angle2),
        branch.end.y - nextLength * cosf(angle2)
    };
    //recursive calls
    drawBranch(leftBranch, currentDepth + 1, targetDepth, treeColor);
    drawBranch(rightBranch, currentDepth + 1, targetDepth, treeColor);
}

//draws the tree inside the right panel
void DrawTree(int depth, Color treeColor) {
    /*creates the first branch and draws the entire tree
        parameters:
            depth: number of generations
        returns:
            nothing*/
    Branch root;
    //start near the bottom of the right panel
    root.start = { 1105, 650 };
    root.angle = 0.0f;
    root.length = 145.0f;

    //calculate the end of the first branch
    root.end = {
        root.start.x + root.length * sinf(root.angle),
        root.start.y - root.length * cosf(root.angle)
    }; // prompted gemini: "what is this formula doing: ...?"

    //draw the tree
    drawBranch(root, 0, depth, treeColor);
}

//helper functions
bool IsButtonClicked(Rectangle button) {
    /*checks if the user clicked a button
        parameters:
            button: position and size of the button
        returns:
            true if clicked, otherwise false*/
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), button)) {
            return true;
        }
    }
    return false;
}

void DrawButton(Rectangle button, string text, Color color) {
    /* draws a simple button
        parameters:
            button: position and size
            text: button name
            color: button color
        returns:
            nothing*/
    Color background = PanelColor;
    Color textColor = color;

    //change the color when the mouse is over the button
    if (CheckCollisionPointRec(GetMousePosition(), button)) {
        background = color;
        textColor = Navy;
    }
    DrawRectangleRec(button, background);
    DrawRectangleLinesEx(button, 2, color);
    //center the text inside the button
    int width = MeasureText(text.c_str(), 20);
    int x = button.x + (button.width - width) / 2;
    int y = button.y + (button.height - 20) / 2;

    DrawText(text.c_str(), x, y, 20, textColor);
}

int BranchCount(int depth) {
    /*counts the number of tree branches
        parameters:
            depth: number of tree levels
        returns:
            total number of branches */
    int total = 0;
    int branches = 1;

    //i fixed the i< detph, wasnt calculating every iteration including 0
    for (int i = 0; i <= depth; i++) {
        total += branches;
        branches *= 2;
    }

    return total;
}
//welcome screen
void DrawWelcomeScreen() {

    DrawRectangle(40, 100, 1320, 570, PanelColor);

    DrawText("HAPPINESS MACHINES", 280, 225, 70, Lavender);

    DrawText("technology, desires, and consumption",370, 325, 28, Teal);

    DrawText("an interactive computer science experiment",360, 390, 25, Muted);

    /*AI assistance: Open AI ChatGT (november 22, 2026)
        prompted: the time for the animation appear doesnt work in my code
        can you giveme a hint where i have the mistake?

        answer: you should use gettime like this: int step = (int)(GetTime() * 2) % 3;

        source: https://chatgpt.com/ */
    //time since the application started
    //get the time
    float time = GetTime();

    //move the words left and right
    int x = 450 + 30 * sinf(time);

    //repeat the animation every 1.5 seconds
    int step = (int)(time * 2) % 3;

    //show needs
    if (step == 0) {
        DrawText("NEEDS", x, 450, 25, Teal);
    }
    
    //show desires after 0.5 seconds
    if (step >= 1) {
        DrawText("DESIRES", x, 500, 25, Lavender);
    }

    //show consumption after 1 second
    if (step >= 2) {
        DrawText("CONSUMPTION", x, 550, 25, Ink);
    }

    DrawTree(5, MAGENTA);

    DrawButton(Explore, "EXPLORE THE RESEARCH", Teal);

    DrawText("team 1 | csc 103 | hackathon 2",40, 850, 20, Muted);
    DrawText("Inspired by Calculating Empires", 1050, 850, 20, Muted);
}
//research screen

void DrawResearchScreen(int slide, Texture2D image) {
    /*displays the research title, information and image
        parameters:
            slide: current slide number
            image: image for the current slide
        returns:
            nothing*/
    DrawText("EXPLORE THE RESEARCH", 40, 45, 28, Teal);

    string progress = "SLIDE ";
    progress += to_string(slide + 1);
    progress += " / ";
    progress += to_string(ResearchSlideCount);

    DrawText(progress.c_str(), 1150, 50, 22, Muted);

    //left panel for the research
    DrawRectangle(40, 110, 780, 670, PanelColor);

    //right panel for the image
    DrawRectangle(850, 110, 510, 670, PanelColor);

    ResearchSlide content = GetResearchSlide(slide);

    //draw the research title
    DrawText(content.title.c_str(), 70, 145, 34, Ink);

    //draw the research description
    DrawText(content.description.c_str(), 70, 250, 23, Muted);

    //display the image
    if (IsTextureValid(image)) {
        float scale = 470.0f / image.width;
        float heightScale = 630.0f / image.height;

        if (heightScale < scale) {
            scale = heightScale;
        }
        float width = image.width * scale;
        float height = image.height * scale;

        //center the image in the right panel
        float x = 1105 - width / 2;
        float imageY = 445 - height / 2;

        DrawTextureEx(image, { x, imageY }, 0, scale, WHITE);
    }
    else {
        DrawText("IMAGE NOT FOUND", 965, 430, 25, Muted);
    }

    //navigation
    if (slide > 0) {
        DrawButton(Previous, "PREVIOUS", Lavender);
    }
    DrawButton(Home, "BACK TO HOME", Muted);

    if (slide == ResearchSlideCount - 1) {
        DrawButton(Next, "BEGIN EXPERIMENT", Teal);
    }
    else {
        DrawButton(Next, "NEXT", Teal);
    }
}
//experiment screen
void DrawExperiment(Scenario scenario, int completed, int depth, Values totals, Color treeColor) {//new parmtr added (remember later change the main)
    /*displays a scenario and two possible choices
        parameters:
            scenario: current situation
            completed: number of finished scenarios
            depth: tree depth
        returns:
            nothing*/
    DrawText("THE DESIRE EXPERIMENT", 40, 45, 28, Teal);

    string progress = "SCENARIO ";
    progress += to_string(completed + 1);
    progress += " / ";
    progress += to_string(ScenarioCount);

    DrawText(progress.c_str(), 1100, 50, 22, Muted);

    //left panel for the situation
    DrawRectangle(40, 110, 780, 670, PanelColor);

    //right panel for the tree
    DrawRectangle(850, 110, 510, 670, PanelColor);

    //draw the scenario title
    DrawText(scenario.title.c_str(), 70, 155, 38, Ink);

    //draw the scenario description----------------------------
    //draw the scenario title
    DrawText(scenario.title.c_str(), 70, 155, 38, Ink);

    //label for the situation
    DrawText("CURRENT OFFER", 70, 215, 20, BLUE);

    //draw a box for the situation text
    DrawRectangle(70, 245, 700, 130, { 78, 60, 110, 255 });
    DrawRectangleLines(70, 245, 700, 130, Muted);

    //draw the scenario description
    DrawText(scenario.situation.c_str(), 90, 275, 26, Muted);
    //----------------------------------------------------------

    DrawButton(FirstChoice, scenario.first, Teal);
    DrawButton(SecondChoice, scenario.second, Lavender);

    DrawText("CHOOSE ONE OPTION", 70, 425, 20, BLUE);

    //draw the tree on the right
    DrawText("THE TREE OF POSIBILITIES", 930, 150, 27, ORANGE);

    DrawTree(depth, treeColor);

    //explain what the recursive tree represents
    //explain the purpose of the recursive tree
    DrawText("A recursive visualization of expanding",910, 730, 20, YELLOW);

    DrawText("possibilities, not personal predictions.",910, 755, 20, YELLOW);

    string stats = "depth: ";
    stats += to_string(depth);
    stats += " / 7";

    DrawText(stats.c_str(), 1050, 680, 22, Muted);
    //-------------------compexity, and recursive calls here------
    //display the total number of recursive function calls
    string calls = "recursive calls: ";
    calls += to_string(BranchCount(depth));
    DrawText(calls.c_str(), 870, 600, 19, Teal);

    //show the time complexity of the recursive tree
    DrawText("time complexity: O ( 2^d )", 1150, 600, 18, Lavender);
    //-----------------------------------------------------------------

    //here im going to put the scores to try first
    //i have to add an extra parameter, because totals is not declares inside this duncion or passes to it
    //display the decision scores
    DrawText("YOUR DECISION SCORES", 70, 570, 24, RED);

    //engagement score
    string engagement = "Engagement: ";
    engagement += to_string(totals.engagement);
    DrawText(engagement.c_str(), 70, 625, 20, Teal);

    //desire pressure score
    string pressure = "Desire pressure: ";
    pressure += to_string(totals.pressure);
    DrawText(pressure.c_str(), 70, 660, 20, Lavender);

    //company profit score
    string profit = "Company profit: ";
    profit += to_string(totals.profit);
    DrawText(profit.c_str(), 70, 695, 20, Ink);

}
//fictional offers screen

void DrawOffer(string product, string pitch, int offers, int depth) {
    /*displays a fictional product recommendation
        parameters:
            product: product name
            pitch: product description
            offers: number of offers shown
            depth: tree depth
        returns:
            nothing*/
    DrawText("THE RECOMMENDATION MACHINE",40, 45, 28, Lavender);
    //left panel
    DrawRectangle(40, 110, 780, 670, PanelColor);
    //right panel
    DrawRectangle(850, 110, 510, 670, PanelColor);

    //draw the product name
    DrawText(product.c_str(), 70, 225, 40, Ink);

    //draw the product description
    DrawText(pitch.c_str(), 70, 310, 26, Muted);

    DrawText("FICTIONAL PRODUCT", 70, 155, 22, Lavender);

    DrawText("this is a fictional recommendation", 70, 580, 22, Muted);

    //draw the tree
    DrawText("THE DESIRE TREE", 930, 150, 27, Lavender);

    DrawTree(depth, MAGENTA);

    //navigation
    if (offers == OfferLimit) {
        DrawButton(Next, "VIEW RESULTS", Lavender);
    }
    else {
        DrawButton(Home, "STOP AND VIEW RESULTS", Muted);
        DrawButton(Next, "ANOTHER OFFER", RED);
    }
}
//results screen
void DrawResults(Values scores, vector<Decision> decisions, int offers) {
    /*displays the final scores and decision history
        parameters:
            scores: fictional experiment scores
            decisions: choices made by the user
            offers: number of offers viewed
        returns:
            nothing*/
    DrawText("EXPERIMENT RESULTS", 40, 45, 28, Lavender);
    //left panel for results
    DrawRectangle(40, 110, 780, 670, PanelColor);
    //right panel for the tree
    DrawRectangle(850, 110, 510, 670, PanelColor);

    DrawText("YOUR RESULTS", 70, 145, 30, Ink);

    string engagement = "engagement: ";
    engagement += to_string(scores.engagement);

    string pressure = "desire pressure: ";
    pressure += to_string(scores.pressure);

    string profit = "company profit: ";
    profit += to_string(scores.profit);

    DrawText(engagement.c_str(), 70, 205, 23, Teal);
    DrawText(pressure.c_str(), 70, 245, 23, Teal);
    DrawText(profit.c_str(), 70, 285, 23, Teal);

    DrawText("YOUR DECISIONS", 70, 345, 25, Lavender);

    //show the choices made during the experiment
    int y = 395;
    for (int i = 0; i < decisions.size(); i++) {
        Decision decision = decisions.at(i);

        DrawText(decision.scenario.c_str(), 70, y, 17, Ink);
        DrawText(decision.choice.c_str(), 440, y, 17, Muted);
        y += 35;
    }
    //calculate the final tree depth
    //calculate the final tree depth using decisions and offers
    int depth = (int)decisions.size() * 7 / 10 + offers;

    if (depth > 11) {
        depth = 11;
    }

    DrawText("FINAL DESIRE TREE", 940, 150, 27, Lavender);

    DrawTree(depth, MAGENTA);

    string total = "total branches: ";
    total += to_string(BranchCount(depth));

    DrawText(total.c_str(), 965, 720, 22, Ink);

    //navigation
    DrawButton(Home, "BACK TO HOME", Muted);
    DrawButton(Next, "RESTART EXPERIMENT", Teal);
}