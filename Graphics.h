
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include "raylib.h"

using namespace std;


void DrawButton(Rectangle button, string text, Color borderColor);
/*
Draws a customizable button on the screen.

Creates a rounded rectangle with a colored border
and centers the button's text inside it.

-param button The button's position and dimensions.
-param text The message displayed inside the button.
-param borderColor The color of the border and text.
 
-return nothing.
*/

//------------------------------------------------


void DrawFooter();
/*
Draws the footer section of the welcome screen.

This function draws a horizontal separator line near the bottom
of the window, then displays the project information on the left
side and the "Inspired by Calculating Empires" text on the right side.

-return nothing.
*/
//--------------------------------------------------


void DrawWelcomeScreen();
/*
Draws the welcome screen of the project.

This function displays the main introduction screen for
The Desire Machine. It draws the title, the main research
question, a short research description, two interactive-style
buttons, and the footer at the bottom of the screen.

It uses the DrawButton() function to display the
"START SIMULATION" and "EXPLORE THE RESEARCH" buttons,
and it calls DrawFooter() to draw the footer section.

return nothing.
*/

//-------------------------------------------------


bool IsButtonClicked(Rectangle button);
/*
brief Checks if the user clicked a button.

Gets the mouse position and checks if the left mouse
button was pressed inside the given rectangle.

-param button The rectangle representing the button.

return True if the button was clicked, false otherwise.
*/



#endif
