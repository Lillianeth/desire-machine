#include "Research.h"

const ResearchSlide researchSlides[ResearchSlideCount] = {
    {
        "Happiness Machines",
        "In 1929, U.S. President Herbert Hoover described consumers as happiness machines while addressing advertising executives. The underlying idea was that advertising could continually stimulate people's desires, helping drive consumption and economic growth.",
        ""
    },
    {
        "Historical Context - Calculating Empires",
        "What the hell are we building beneath our feet? Our society relies on an immense infrastructure of machines, networks, and data systems. Yet most of us have only a vague idea of how it all works. In Calculating Empires, Kate Crawford and Vladan Joler explore the relationship between technology, power, and society.",
        "happymachines.png"
    },
    {
        "Technology and Human Desires",
        "From the first stone knives to smartphones, technology has always promised to improve human life. So why are so many people unhappy with the machines surrounding them? Perhaps the problem is not technology itself, but the system that determines what it becomes.",
        ""
    },
    {
        "Audience Research, Advertising, and Consumer Behavior",
        "Profit drives the market, often before ethical considerations. This shapes the technology we use every day. Our behavior is tracked, our attention is sold, and our desires are constantly studied. Advertising is no longer confined to magazines or television. It follows us everywhere.",
        ""
    },
    {
        "From Research to Simulation",
        "What does it mean to own a machine? You can understand, modify, and repair a hammer. But a smartphone offers no such freedom. We imagined a machine that promises happiness with every decision. As it grows, are we controlling it, or is it controlling us?",
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
