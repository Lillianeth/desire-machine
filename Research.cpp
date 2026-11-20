#include "Research.h"

const ResearchSlide researchSlides[ResearchSlideCount] = {

    {
        "Happiness Machines: Who Shapes Our Desires?",
        "Every day, digital platforms recommend what to watch, buy, or do next. These suggestions can be helpful, but they can also influence our choices and encourage consumption. Are platforms responding to what we want, or helping shape what we want?",
        ""
    },

    {
        "Calculating Empires",
        "Created by Kate Crawford and Vladan Joler (2023), Calculating Empires explores the relationship between technology and power over the past 500 years. Technology does not develop separately from society: it reflects economic and political interests, while also shaping how we live.",
        ""
    },

    {
        "Abstraction and Consumption",
        "Abstraction simplifies complex things by focusing on selected details. Digital platforms use clicks, purchases, and watch time to represent our interests. But clicking does not necessarily mean we like something, and spending time on an app does not necessarily mean we are happy.",
        ""
    },

    {
        "Building the Happiness Machine",
        "Our C++ application presents ten everyday scenarios involving digital platforms. Each decision changes three fictional values: engagement, desire pressure, and company profit. The simulation uses randomization, structs, classes, vectors, and recursion to represent how these choices accumulate.",
        ""
    },

    {
        "Are We in Control?",
        "Our goal is not to claim that technology is bad. We want to question how digital systems influence our everyday decisions. When algorithms measure our behavior and turn it into numbers, what gets lost? Are we using technology to satisfy our desires, or is technology teaching us what to desire?",
        ""
    }

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
