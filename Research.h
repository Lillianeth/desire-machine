#ifndef RESEARCH_H
#define RESEARCH_H

#include <string>
using namespace std;

//stores the information for one research slide
class ResearchSlide {
public:
    string title;
    string description;
    string image;
};

//number of research slides
const int ResearchSlideCount = 12;

//gets the information for a slide
ResearchSlide GetResearchSlide(int index);

#endif
