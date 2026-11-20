#include "Research.h"

const ResearchSlide researchSlides[ResearchSlideCount] = {
{
    "Happiness Machines: Who Shapes Our Desires?",

    "Every day, digital platforms recommend what to watch, "
    "buy, or do next. These suggestions can be helpful, "
    "but they can also influence our choices and encourage "
    "spending. Inspired by Calculating Empires (Crawford "
    "and Joler, 2023), our project explores the relationship "
    "between technology, human desire, and commercial power. "
    "Are platforms responding to what we want, or helping "
    "shape what we want?",
    "1.jpg"},    
    
    
    {"", "Their central argument is that technology does not develop separately from society; it also reflects and shapes economic and political power. One especially relevant part of their research examines how human emotions and intelligence became subjects of measurement and classification.",""},
    {"","Source: https://calculatingempires.net/about.html "},
};


ResearchSlide GetResearchSlide(int index) {
    /*
        Gets the title, text, and optional image filename for a research slide.
        parameters:
            index - zero-based slide number
        returns:
            a copy of the requested slide, or an empty slide for an invalid index
    */

    if (index < 0 || index >= ResearchSlideCount) {
        return {};
    }
    return researchSlides[index];
}
