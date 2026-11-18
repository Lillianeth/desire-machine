
#include "Graphics.h"

void DrawButton(Rectangle button, string text, Color borderColor) {

    //draw the rounded background
    DrawRectangleRounded(button, 0.2f, 10, Color{ 22, 35, 50, 255 });

    //draw the border
    DrawRectangleRoundedLinesEx(button, 0.2f, 10, 2.0f, borderColor);

    //calculate the width of the text
    int fontSize = 20;
    int textWidth = MeasureText(text.c_str(), fontSize);

    //center the text inside the button
    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;

    DrawText(text.c_str(), textX, textY, fontSize, borderColor);
}

//--------------------------------------------------------------------
void DrawFooter() {

    DrawLine(40, 720, 960, 720, DARKGRAY);

    string leftFooter = "TEAM 1 | CSC 103 | HACKATHON #2";
    DrawText(leftFooter.c_str(), 40, 750, 17, LIGHTGRAY);

    string rightFooter = "Inspired by Calculating Empires";

    int footerWidth = MeasureText(rightFooter.c_str(), 17);
    int footerX = GetScreenWidth() - footerWidth - 40;

    DrawText(rightFooter.c_str(), footerX, 750, 17, LIGHTGRAY);
}
//---------------------------------------------------------------
void DrawWelcomeScreen() {

    //title
    string title = "THE DESIRE MACHINE";

    int titleWidth = MeasureText(title.c_str(), 55);
    int titleX = (GetScreenWidth() - titleWidth) / 2;

    DrawText(title.c_str(), titleX, 180, 55, WHITE);

    //main question
    string subtitle = "Can technology satisfy our desires, or does it keep us wanting more?";

    int subtitleWidth = MeasureText(subtitle.c_str(), 20);
    int subtitleX = (GetScreenWidth() - subtitleWidth) / 2;

    DrawText(subtitle.c_str(), subtitleX, 270, 20, LIGHTGRAY);

    //research introduction
    string line1 = "An interactive experiment exploring how technology can";
    string line2 = "predict and influence human desires, and how satisfaction";
    string line3 = "can intersect with commercial incentives.";

    int line1X = (GetScreenWidth() - MeasureText(line1.c_str(), 20)) / 2;
    int line2X = (GetScreenWidth() - MeasureText(line2.c_str(), 20)) / 2;
    int line3X = (GetScreenWidth() - MeasureText(line3.c_str(), 20)) / 2;

    DrawText(line1.c_str(), line1X, 325, 20, GRAY);
    DrawText(line2.c_str(), line2X, 350, 20, GRAY);
    DrawText(line3.c_str(), line3X, 375, 20, GRAY);

    //buttons
    Rectangle startButton = { 350, 460, 300, 65 };
    Rectangle researchButton = { 350, 540, 300, 65 };

    DrawButton(startButton, "START SIMULATION", Color{ 125, 211, 197, 255 });
    DrawButton(researchButton, "EXPLORE THE RESEARCH", LIGHTGRAY);

    DrawFooter();
}

//-----------------------------------------------------------------------
bool IsButtonClicked(Rectangle button) {

    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        return true;
    }

    return false;
}