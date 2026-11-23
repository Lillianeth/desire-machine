#include "Research.h"
using namespace std;

//research slides
const ResearchSlide researchSlides[ResearchSlideCount] = {
    //slide 1
    {
        "Happiness Machines: From Needs to Desires",

        "In the early 20th century, advertising began to focus not only\non what people needed, but also on what they desired."

        "\n\nResearchers such as Ernest Dichter explored how emotions and \nunconscious motivations could influence consumer behavior."

        "\n\nIn Calculating Empires(2023), Kate Crawford and Vladan Joler \nconnect these ideas to audience research, consumer \nclassification, and the measurement of human behavior."

        "\n\nToday, digital platforms use data and algorithms to recommend \nproducts, entertainment, and services."

        "\n\nThis raises an important question : \n\nAre technologies simply responding to our desires, or can they \nalso help create them ? ",

        "happymachines.png"
    },

    //slide 2
    {
        "",

        "Their central argument is that technology does not\n"
        "develop separately from society. It also reflects\n"
        "and shapes economic and political power.\n"
        "\n"
        "One especially relevant part of their research\n"
        "examines how human emotions and intelligence became\n"
        "subjects of measurement and classification.",

        ""
    },

    //slide 3
    {
        "",

        "Source: https://calculatingempires.net/about.html",

        ""
    }
};

//gets a specific research slide
ResearchSlide GetResearchSlide(int index) {
    /*gets the information for a research slide
        parameters:
            index: position of the slide
        returns:
            the requested slide*/
    //check if the position is valid
    if (index < 0 || index >= ResearchSlideCount) {
        return {};
    }
    return researchSlides[index];
}
