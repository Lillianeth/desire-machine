#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "raylib.h"
#include "HappinessMachine.h"
#include "Research.h"
#include <string>
#include <vector>

using namespace std;


//button positions
const Rectangle Explore = { 500, 710, 400, 65 };
const Rectangle Credits = { 920, 710, 180, 65 };
const Rectangle Previous = { 40, 810, 210, 60 };
const Rectangle Home = { 280, 810, 260, 60 };
const Rectangle Next = { 1100, 810, 260, 60 };
const Rectangle Skip = { 700, 810, 300, 60 };

//experiment choices
const Rectangle FirstChoice = { 70, 470, 340, 70 };
const Rectangle SecondChoice = { 440, 470, 340, 70 };

//helper functions
bool IsButtonClicked(Rectangle button);

void DrawButton(Rectangle button, string text, Color color);

//screens
void DrawWelcomeScreen();

void DrawResearchScreen(int slide, Texture2D image);

void DrawExperiment(Scenario scenario, int completed, int depth, Values totals, Color treeColor);

void DrawOffer(string product, string pitch, int offers, int depth);

void DrawResults(Values scores, vector<Decision> decisions, int offers);

//tree statistics
int BranchCount(int depth);

void DrawCreditsScreen();

#endif
