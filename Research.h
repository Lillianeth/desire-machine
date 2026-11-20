#ifndef RESEARCH_H
#define RESEARCH_H

#include <string>

struct ResearchSlide {
    std::string title;
    std::string description;
    std::string image;
};

const int ResearchSlideCount = 5;

ResearchSlide GetResearchSlide(int index);

#endif