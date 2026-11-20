#include "Graphics.h"
#include <cmath>

using namespace std;
//custom colors for the GUI, defined using raylib's color structure
//{red, green, blue, alpha}
const Color Navy{ 15, 23, 42, 255 };
const Color PanelColor{ 25, 37, 58, 255 };
const Color Teal{ 125, 231, 213, 255 };
const Color Lavender{ 196, 171, 245, 255 };
const Color Ink{ 241, 246, 252, 255 };
const Color Muted{ 179, 194, 215, 255 };

const int TealBranches = 0;
const int LavenderBranches = 1;

//helper functions
void Panel(Rectangle bounds) {
	/*
		Receives a rectangle containing position and size
		bounds : deetermines where the card appears and how big it is
	*/
	DrawRectangleRounded(bounds, 0.12f, 12, DARKGREEN);
}

void Center(string text, Rectangle bounds, int size, Color color) {
	/*
		Centers text and reduces the font size when it needs more room.
		parameters:
			text: line to draw
			bounds: area used for centering
			size: starting font size
			color: text color
	*/
	while (size > 12 && MeasureText(text.c_str(), size) > bounds.width - 24) {
		//if the text is too wide, size-- reduces the font size by one 
		// each time until it fits or reaches 12
		size--;
	}
	int width = MeasureText(text.c_str(), size);
	//text.c_str() converts the c++ string into the character-string format expected by raylib
	int x = bounds.x + (bounds.width - width) / 2;//do i need to use static_cast here?
	int y = bounds.y + (bounds.height - size) / 2;
	//this display the text at the positions we calculated
	DrawText(text.c_str(), x, y, size, color);
}

int Wrap(string text, int x, int y, int width, int size, Color color) {
	/*
		Draws each line within the given width. What this means?
		automatically divides long text into multiple lines so it fits 
		inside our GUI panels. I think this function is important
		because we can put large text without caring about wrap each line
		CHECK LATER IF WE REALLY NEEDED OR NOT TO DELETE THIS FUNCTION
		parameters
			text: words to draw for exp a complete paragraph
			x, y : startinf positions
			width: maximun line width
			size: font size
			color: text color

		returns
			it returns the Y coordinate after the last line, so we know where
			to draw the next element without overlapping the paragraph
	*/

	//stores the words that currently fit on the same line
	string line;
	//stores the word currently being built, one character at a time
	string word;

	int textLength = text.size();
	for (int i = 0; i <= textLength; i++) {
		//<= extra iteration to now te word has ended 
		char letter = ' ';
		//to prevent accessing text.at(i) outside the string C A T _= 0 1 2 3-> 3<3? FALSE Is a space
		if (i < textLength) {
			letter = text.at(i);
		}//i want happiness = w wa wan want
		if (letter != ' ' && letter != '\n' && letter != '\t' && letter != '\r') {
			word += letter;
		}
		//--------------it fit or not?-------------------------
		else if (word.size()>0) {
			if (line.size()==0) {
				line = word;
			}
			else {
				string nextLine = line + " " + word;
				if (MeasureText(nextLine.c_str(), size ) > width) {
					DrawText(line.c_str(), x, y, size, color);
					y += size + 8;
					line = word;
				}
				else {
					line = nextLine;
				}
			}
			word.clear();
		}
	}
	DrawText(line.c_str(), x, y, size, color);
	return y + size + 8;
}

void DrawButton(Rectangle button, string text, Color accent) {
	/*
		Draws a rounded button that highlights on hover
		-the button changes appearance when the mouse moves over it
		parameter:
			button: button position and size
			text: button label
			accent: border and hover color
		returns:
			nothing
	*/
	bool hover = CheckCollisionPointRec(GetMousePosition(), button);
	Color fill = PanelColor;
	Color textColor = accent;
	if (hover) {
		fill = accent;
		textColor = Navy;
	}
	//drawwing the actual button
	DrawRectangleRounded(button, 0.24f, 10, fill);
	DrawRectangleRoundedLinesEx(button, 0.24f, 10, 2, accent);

	Center(text, button, 20, textColor);
}

void Header(string section, string progress, Color accent) {
	/*
		draw the heading at the top of each screen, display 
		progress on the right, and add a separating line underneath
		parameters:
			section: screen heading
			progress: text aligned on the right
			accent: heading color
		returns nothing
		
	*/
	//the left heading
	//DrawText(text, x, y, fontSize, color);
	DrawText(section.c_str(), 60, 48, 21, BLACK);
	//the right - aligned progress
	//if mt=150 --> x = 940 - 150 = 790
	int progressWidth = MeasureText(progress.c_str(), 18);
	int progressX = 940 - progressWidth;
	DrawText(progress.c_str(), progressX, 50, 18, BLACK);
	//separator, draws a line across the screen
	//DrawLine(startX, startY, endX, endY, color);
	DrawLine(60, 88, 940, 88, PanelColor);
}

//---------lets put in practice recursion---------------------------
void DrawBranches(float x, float y, float angle, float length, int remaining, int style) {
	/*
	Inspired by the official raylib example:
	"shapes_recursive_tree"
	Original example by Jopestpe (@jopestpe).
	Source:
	https://www.raylib.com/examples/shapes/loader.html?name=shapes_recursive_tree
	This implementation uses recursion instead of
	the iterative approach shown in the example.
	Drawss a branch followed by its left and right brancches
		parameters:
			x,y: branch starting position
			angle: direction in radians
			length: length in pixels
			remaining: levels left to draw
			style: teal or lvander branch styles
		returns
			nothng
	*/


	//base case: an empty level has no branch and makes no more calls
	//calls itself to create a branching tree

    const int TealBranches = 0;
    const int LavenderBranches = 1;

	if (remaining <= 0) {
		return;
	}

	Color accent = Teal;
	if (style == LavenderBranches) {
		accent = Lavender;
	}

	//calculating where the branch ends
	Vector2 start = { x, y };
	Vector2 tip = { x + length * cos(angle), y + length * sin(angle) };
	float opacity = 0.9f;//90%
	if (remaining == 1) {
		opacity = 0.62f;//62%
	}
	DrawLineEx(start, tip, 1.2f + remaining * 0.37f, Fade(accent, opacity));
	if (remaining == 1) {
		DrawCircleV(tip, 2.2f, accent);
	}

	//both children start at the tip, hey turn in opposite directions and are shorter
	float childLength = length * 0.74f;
	//creates a branch angled toward one side
	DrawBranches(tip.x, tip.y, angle - 0.55f, childLength, remaining - 1, style);
	//creates a branch angled toward the other side
	DrawBranches(tip.x, tip.y, angle + 0.55f, childLength, remaining - 1, style);
	//B(d)=d^2 -1
	//O(2^d)
}

void TreeCard(int depth, float y, Color accent, int style) {
	/*
		Draws the desire tree and its statistics inside a card
		connects the recursive tree  with the actual GUI
		parameters:
			depth: levels to draw
			y: top of the card,position where the card begins
			accent: text color
			style: teal or lavender branch style
		returns:
			noting
	*/
	//draw the card
	Panel({ 60, y, 880, 228 });
	//draw the title
	int titleY = y + 30;
	DrawText("THE DESIRE TREE", 88, titleY, 22, accent);
	
	int branches = BranchCount(depth);

	//create the statistic text
	string stats = "Depth " + to_string(depth);
	stats += " / 7 | ";
	stats += to_string(branches);
	stats += " branch segments";

	//draw the statistics
	DrawText(stats.c_str(), 88, y + 71, 20, Ink);

	//explain the branching process
	Wrap("Each branch can produce two more. Depths 1, 2, and 3 draw 1, 3, and 7 segments.", 88, y + 110, 380, 17, Muted);
	
	//display the compexity
	DrawText("Time O(2^depth)  |  Depth cap: 7", 88, y + 183, 17, Muted);
	
	//draw the recursive tree
	DrawBranches(695, y + 205, -1.5708f, 57, depth, style);
}






//------------------------------------------------------------

bool IsButtonClicked(Rectangle button) {

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
		CheckCollisionPointRec(GetMousePosition(), button)) {

		return true;
	}

	return false;
}

void DrawWelcomeScreen() {

    const int TealBranches = 0;

	Panel({ 60, 65, 880, 634 });
	DrawBranches(500, 235, -1.5708f, 36, 5, TealBranches);
	Center("HAPPINESS MACHINES", { 60, 256, 880, 82 }, 62, Ink);
	Center("when will the infinite cycle of consumerism end?", { 60, 356, 880, 44 }, 24, Teal);
	Center("An interactive exhibit about technology, human desires,", { 60, 424, 880, 30 }, 21, Muted);
	Center("consumer behavior, and commercial incentives.", { 60, 456, 880, 30 }, 21, Muted);
	DrawButton(Explore, "START", Teal);
	DrawLine(60, 725, 940, 725, PanelColor);
	DrawText("TEAM 1 | CSC 103 | HACKATHON 2", 60, 750, 17, Muted);
	const std::string credit = "Inspired by Calculating Empires";
	DrawText(credit.c_str(), 940 - MeasureText(credit.c_str(), 17), 750, 17, Lavender);
}

void DrawResearchScreen(int slide, Texture2D image) {
	//this function combines our several helpers to create an entire screen

	//draw the header and the background
	Header("Our research :)", "SLIDE " + to_string(slide + 1) + " / " + to_string(ResearchSlideCount), BLACK);
	
	//draw the main rounded card where the research content apprears
	Panel({ 60, 108, 880, 550 });

	//retrieve the slide content(defined in our Research.h file)
	//same concept as accessing members of a class or struct in our c++ exercises from the lab
	ResearchSlide content = GetResearchSlide(slide);

	//draw the title and description using Wrap()
	//wy 18?? because need an extra espace between the research title and the description
	int bodyY = Wrap(content.title, 90, 142, 820, 37, Ink); //+18;
	bodyY = 200;
	Wrap(content.description, 90, bodyY, 810, 23, Muted);

	//here im defininf the image area
	Rectangle frame{ 90, 340, 820, 282 };
	//frame= where the research image will appear.
	DrawRectangleRounded(frame, 0.12f, 10, Navy);

	//chek if whether the image loaded
	if (IsTextureValid(image)) {
		//resize the image without distorting its
		float scale = 780.0f / image.width;
		float heightScale = 224.0f / image.height;
		if (heightScale < scale) {
			scale = heightScale;
		}
		float w = image.width * scale;
		float h = image.height * scale;
		//draw the image using DrawTexturePro()
		Rectangle source = { 0,0, (float)image.width, (float)image.height };
		//500-w/2, 1000wide xceter = 500-> 500-400/2=300, start x=300,end x=700
		Rectangle destination = { 500 - w / 2,463 - h / 2, w, h };
		Vector2 origin = { 0, 0 };
		DrawTexturePro(image, source, destination, origin, 0, WHITE);
		Center("Existing project image", { 90, 575, 820, 40 }, 16, Muted);
	}
	else {
		Center("RESEARCH IMAGE PLACEHOLDER", frame, 20, Lavender);
	}
	//draw the navigation buttons
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


void DrawExperiment(Scenario scenario, int completed, int depth) {
	//also used my beloved helper functions to make it easier
	//Scenario is a struct defined in HappinessMachine.h -->go and check

	//start drawing the header
	string progress = "SCENARIO ";
	progress += to_string(completed + 1);//completed count how many scenarios have already been finished
	progress += " / ";
	progress += to_string(ScenarioCount);
	Header("THE DESIRE EXPERIMENT", progress, Teal);

	//draw the prigress bar
	DrawRectangleRounded({ 60, 103, 880, 9 }, 0.8f, 8, PanelColor);//full 880px
	if (completed > 0) {
		//880/10=88 -->88x completed
		DrawRectangleRounded({ 60, 103, 88.0f * completed, 9 }, 0.8f, 8, Teal);//colored progress, 10scenarios
	}
	//scenario card
	Panel({ 60, 130, 880, 286 });
	//tittle of the current scenario
	DrawText(scenario.title.c_str(), 90, 160, 38, Ink);

	//draw the description of the situation
	Wrap(scenario.situation, 90, 221, 820, 25, Muted);//thats why i decided to create this helper funcion!

	//draw the two choices
	DrawButton(FirstChoice, scenario.first, Teal);
	DrawButton(SecondChoice, scenario.second, Lavender);

	//draw the recursive tree card!!! best part
	TreeCard(depth, 438, Teal, TealBranches);
	//explanatory sentence
	DrawText("Each decision changes illustrative simulation values.", 60, 708, 19, Muted);
}

void DrawOffer(string product, string pitch, int offers, int depth) {

	//the machine starts with realistic situations, but eventually 
	// begins recommending increasingly ridiculous products :D

	//draw the header
	string progress = "OFFER ";
	progress += to_string(offers);
	progress += " / ";
	progress += to_string(OfferLimit);
	Header("THE RECOMMENDATION MACHINE", progress, Lavender);

	//draw the product pannel (like a backgroudn pannel)
	Panel({ 60, 119, 880, 258 });

	//shows a small heading above the recommendations
	DrawText("FICTIONAL PRODUCT", 90, 147, 19, Lavender);

	//draw the product name and description
	int bodyY = Wrap(product, 90, 189, 810, 40, Ink) + 12;
	bodyY = Wrap(product, 90, 189, 810, 40, Ink);

	bodyY += 12;

	Wrap(pitch, 90, bodyY, 810, 25, Muted);

	//draw the tree
	TreeCard(depth, 403, Lavender, LavenderBranches);//note the change in what??

	//check whether the machine has reached its maximum number of offers
	if (offers == OfferLimit) {
		DrawButton(Next, "VIEW RESULTS", Lavender);
	}
	else {
		DrawButton(Next, "ANOTHER OFFER", Lavender);
		DrawButton(Home, "STOP AND VIEW RESULTS", Muted);
	}
}

void DrawResults(Values scores, vector<Decision> decisions, int offers) {
	//draw the header
	string progress = to_string(offers);
	progress += " FICTIONAL OFFERS VIEWED";
	Header("EXPERIMENT RESULTS", progress, Lavender);

	//draw the score panel
	Panel({ 60, 110, 880, 138 });
	DrawText("Illustrative simulation values", 84, 131, 26, Ink);

	//score text
	string totals = "Engagement: ";
	totals += to_string(scores.engagement);

	totals += "   Desire pressure: ";
	totals += to_string(scores.pressure);

	totals += "   Company profit: ";
	totals += to_string(scores.profit);
	//displays the scores
	DrawText(totals.c_str(), 84, 171, 22, Teal);

	//draw the decision history panel
	DrawText("These totals describe the fictional system's response to your decisions.", 84, 212, 17, Muted);
	//decision history pannel
	Panel({ 60, 267, 880, 392 });
	DrawText("YOUR DECISIONS", 84, 291, 20, Lavender);

	//where the first decision is located
	int y = 327;
	int decisionCount = decisions.size();

	//display every decision
	for (int i = 0; i < decisionCount; i++) {
		Decision decision = decisions.at(i);
		DrawText(decision.scenario.c_str(), 84, y, 18, Ink);
		DrawText(decision.choice.c_str(), 467, y, 18, Muted);
		//separator
		DrawLine(84, y + 24, 916, y + 24, Navy);

		//need to move next row
		y += 30;
	}
	//final buttons
	DrawButton(Home, "BACK TO HOME", Muted);
	DrawButton(Next, "RESTART EXPERIMENT", Teal);
}

int BranchCount(int depth) {
	/*
		counts the branches level by level
		parameters:
			depth: number of levels to count
		returns:
			the total number of visible branches segments
	*/
	int segments = 0;
	int branchesAtLevel = 1;
	for (int level = 0; level < depth; level++) {
		segments += branchesAtLevel;
		//every branch has two children, so the next level is twice as wide
		branchesAtLevel *= 2;
	}
	return segments;
}
