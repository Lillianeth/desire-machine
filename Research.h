#ifndef RESEARCH_H
#define RESEARCH_H
#include <string>
using namespace std;

struct ResearchSlide {
    string title;
    string description;
    string image;
};

const int ResearchSlideCount = 7;

ResearchSlide GetResearchSlide(int index);

#endif