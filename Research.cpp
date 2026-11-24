#include "Research.h"
using namespace std;

//research slides
const ResearchSlide researchSlides[ResearchSlideCount] = {
    //slide 1
    {
        "Welcome to Happiness Machines!!",
        "Happiness Machines is an interactive C++ project inspired by \nCalculating Empires, created by Kate Crawford and V.Joler."
        "\n\nOur project explores how technology, advertising, and digital \nplatforms can influence human desires and consumer behavior."
        "\n\nWhat will you experience?"
        "\n\nYou will answer 10 everyday scenarios, make choices, and \nobserve how three fictional values change: engagement, desire \npressure, and company profit."
        "\n\nA recursive tree grows as you progress, and the program \neventually presents fictional product recommendations. "
        "\n\nOur goal is to encourage you to question how digital systems \ninfluence everyday decisions.",
        "happinessmachines.png"
    },

    //slide 2
    {

        "Happiness Machines: From Needs to Desires",
        "Our Reserach main question."
        "\n\nIn the early 20th century, advertising began to focus not only\non what people needed, but also on what they desired."
        "\n\nResearchers such as Ernest Dichter explored how emotions and \nunconscious motivations could influence consumer behavior."
        "\n\nIn Calculating Empires(2023), Kate Crawford and Vladan Joler \nconnect these ideas to audience research, consumer \nclassification, and the measurement of human behavior."
        "\n\nToday, digital platforms use data and algorithms to recommend \nproducts, entertainment, and services."
        "\n\nThis raises an important question : \n\nAre technologies simply responding to our desires, or can they \nalso help create them ? ",
        "6.jpg"
    },

    //slide 3
    {
        "Happiness Machines and Consumer Culture",
        "During the 1920s, advertising became an important part of \nAmerican consumer culture. Companies increasingly focused on \ncreating desires, not simply satisfying people's needs."
        "\n\nHerbert Hoover, who later became U.S. president, is often \ncredited with describing consumers as happiness machines."
        "\n\nEdward Bernays, a pioneer of public relations, also explored how \npsychology and advertising could influence consumer behavior."
        "\n\nThese developments helped establish an approach to advertising \nthat focused on more than practical needs."
        "\n\nAlmost a century later, digital platforms use data, personalized \nadvertising, and recommendation algorithms to influence what \npeople see and consider buying.",
        "presiandresearcher.png"
    },

    //slide 4
    {
        "Can Happiness Be Measured? \nThe Problem of Abstraction",
        "In computer science, abstraction means simplifying something \ncomplex by representing only certain details."
        "\n\nDigital platforms can collect information about our behavior, \nsuch as clicks, purchases, and watch time. But these numbers \ncannot fully explain our emotions or intentions."
        "\n\nFor example, watching a video for 30 minutes does not \nnecessarily mean we enjoyed it. A system can measure our \nactivity, but happiness is much harder to measure."
        "\n\nIn our C++ experiment, we use three fictional values to \nrepresent decisions: engagement, desire pressure, and company \nprofit."
        "\n\nThese values demonstrate how programmers can turn human \nbehavior into data, but they do not measure real happiness."
        "\n\nThe important question is: What gets lost when we represent \nhuman experiences using numbers?",
        "measuring.png"
    },

    //slide 5
    {
        "How Recommendation Systems Work",
        "Recommendation systems try to predict what a user\n"
        "may want next.\n"
        "\nThey collect behavioral data such as clicks, likes,\n"
        "watch time, searches, and purchases.\n"
        "\nThen, algorithms use patterns in that data to decide\n"
        "what content, product, or suggestion should appear\n"
        "next.\n"
        "\nThis may feel helpful or personalized, but it also\n"
        "gives platforms power to shape attention and\n"
        "influence decisions.\n"
        "\nThey do not only respond to behavior.\n"
        "They can also help guide it.",
        "recomendationloop.png"
    },
    //slide 6

    {
        "What Do Algorithms Optimize?",
        "In computer science, optimization means finding\n"
        "a better solution according to a specific goal.\n"
        "\nRecommendation systems can prioritize engagement,\n"
        "sales, or content that is relevant to users.\n"
        "\nFor example, an algorithm maximizing watch time\n"
        "might recommend different videos than one designed\n"
        "to help users learn.\n"
        "\nWhat benefits a platform does not always benefit\n"
        "the people using it.\n"
        "\nOur C++ experiment uses three fictional values:\n"
        "\nWhat should an algorithm be designed to achieve?",
        "optimization.png"
    },
    //slide 7
    {
        "Feedback Loops and the Formation \nof Preferences",
        "\nDigital platforms do not only respond to what users\n"
        "do once.\n"
        "\nEach click, purchase, or view becomes new data that\n"
        "can affect future recommendations.\n"
        "\nThis creates a feedback loop: behavior produces data,\n"
        "data shapes recommendations, and those recommendations\n"
        "can influence later behavior.\n"
        "\nOver time, this process may reinforce habits,\n"
        "interests, or desires.\n"
        "\nTechnology may not only reflect what users want.\n"
        "It can also help shape what they want next.",
        "9.jpg"
    },

    //slide 8
    {
        "Digital Consumption and Commercial \nIncentives",
        "Today, consumption is not limited to physical\n"
        "products. Digital platforms also sell convenience,\n"
        "access, attention, and personalized experiences.\n"
        "\nFor example, free applications may charge users to\n"
        "remove advertisements or unlock extra features.\n"
        "\nThese business models are not always harmful, but\n"
        "they show how needs can become profit opportunities.\n"
        "\nIn Happiness Machines, fictional products become\n"
        "increasingly absurd, such as subscriptions to\n"
        "\nWhen does convenience become another product?",
        "streaming.png"
    },

    //slide 9
    {
        "Dark Patterns and Interface Design",
        "Human-Computer Interaction (HCI) studies how people\n"
        "interact with technology.\n"
        "\nButtons, colors, messages, and the presentation of\n"
        "options can influence our decisions.\n"
        "\nSome interfaces use dark patterns: deceptive design\n"
        "techniques that can manipulate consumer choices.\n"
        "\nExamples include fake countdown timers, hidden\n"
        "subscription fees, and difficult cancellation.\n"
        "\nThese designs raise an important question:\n"
        "\nAre users choosing freely, or is the interface\n"
        "pushing them toward a particular decision?",
        "darkinterface.png"
    },

    //slide 10
    {
        "Inside Happiness Machines: \nOur C++ Simulation",
        "We developed Happiness Machines using C++ and\n"
        "raylib, connecting programming with our research.\n"
        "\nOur program presents ten predefined scenarios,\n"
        "each with two possible choices.\n"
        "\nEvery decision changes three fictional values:\n"
        "engagement, desire pressure, and company profit.\n"
        "\nWe use classes to organize scenarios, decisions,\n"
        "and scores. Loops and conditions control the flow.\n"
        "\nThe program generates imaginary products using\n"
        "random selections and draws a recursive tree.\n"
        "\nThese are simplified models, not real predictions\n"
        "of human happiness.",
        "fractal.png"
    },

    //slide 11
    {
        "The Limits of Happiness Machines",
        "Our C++ program is an educational simulation,\n"
        "not a real psychological experiment.\n"
        "\nIt presents ten predefined scenarios and assigns\n"
        "fictional values to each decision.\n"
        "\nThese numbers do not measure real emotions or\n"
        "happiness.\n"
        "\nOur imaginary products are generated randomly,\n"
        "not by personalized recommendation algorithms.\n"
        "\nThe recursive tree represents possible branches,\n"
        "not a record of each user's decisions.\n"
        "\nOur goal is to question what software measures,\n"
        "how it is designed, and whose interests it serves.",
        "humanemotions.png"
    },
    //slide 12

    {
        "Who Defines What We Want?",
        "Technology can help us discover information,\n"
        "products, and services that match our needs.\n"
        "\nHowever, recommendation systems can also influence\n"
        "what we see, how we spend our time, and our choices.\n"
        "\nThrough Happiness Machines, we explored how human\n"
        "behavior becomes data, how software follows rules,\n"
        "and how commercial goals can affect digital life.\n"
        "\nOur simulation does not measure real happiness.\n"
        "Instead, it encourages us to question the design\n"
        "and purpose of the technologies we use.\n"
        "\nAs future computer scientists, we should ask:\n"
        "Whose interests does our software serve?\n"
        "\nWho gets to define happiness in the first place?",
        "humanandtech.png"
    },

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

