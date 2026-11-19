#include "raylib.h"
#include <cmath>

/*
this piece of code is inspired in the raylib example "recursive tree" created by Jopestpe
https://www.raylib.com/examples/shapes/loader.html?name=shapes_recursive_tree

also checked this resources:
https://natureofcode.com/fractals/#trees
https://www.youtube.com/watch?v=0jjeOYMjmDU

asked gemini:
how does drawlineex work in Raylib?
what is this formula doing: ...?
typedefs and classes are the same?
remind me how to apply recursion in c++
what is wrong with initializing global variables vs doing it in main?
*/

class Branch {
    public:
        Vector2 start;
        Vector2 end;
        float angle;
        float length;
};

// initialize some parameters
const int screenWidth = 800;
const int screenHeight = 450;

const float initialLength = 120.0f;
const float branchDecay = 0.66f;
const float angle = 50.0f * DEG2RAD;
const int maxDepth = 10;

// Recursive function
void drawBranch(Branch branch, int currentDepth, int targetDepth) {

    // Draw current branch
    DrawLineEx(branch.start, branch.end, 2.0f, MAGENTA);
    // asked gemini: "how does drawlineex work in Raylib?"

    // Base case
    if (currentDepth >= targetDepth) {
        return;
    }

    // Calculate next generation
    float nextLength = branch.length * branchDecay;
    float angle1 = branch.angle + angle;

    // left branch
    Branch leftBranch;
    leftBranch.start = branch.end;
    leftBranch.angle = angle1;
    leftBranch.length = nextLength;

    leftBranch.end = {
        branch.end.x + nextLength * sinf(angle1),
        branch.end.y - nextLength * cosf(angle1)
    };

    float angle2 = branch.angle - angle;

    // right branch!
    Branch rightBranch;
    rightBranch.start = branch.end;
    rightBranch.angle = angle2;
    rightBranch.length = nextLength;

    rightBranch.end = {
        branch.end.x + nextLength * sinf(angle2),
        branch.end.y - nextLength * cosf(angle2)
    };

    drawBranch(leftBranch, currentDepth + 1, targetDepth);
    drawBranch(rightBranch, currentDepth + 1, targetDepth);
}

int main() {

    InitWindow(screenWidth, screenHeight, "Recursive Fractal Tree");

    // Initialize root branch
    Branch root;

    root.start = { screenWidth / 2.0f, (float)screenHeight }; // root start point (vector: x and y coords)
    root.angle = 0.0f;
    root.length = initialLength;

    root.end = {
        root.start.x + root.length * sinf(0),
        root.start.y - root.length * cosf(0)
    }; // root end point
    // prompted gemini: "what is this formula doing: ...?"

    int generation = 0;

    while (!WindowShouldClose()) {

        // add generation with each mouse click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (generation < maxDepth) {
                generation++;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw fractal up to current generation
        drawBranch(root, 0, generation);

        DrawText(TextFormat("Generation: %i", generation), 20, 20, 20, RAYWHITE);

        DrawText("Click to grow the tree", 20, 50, 16, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}