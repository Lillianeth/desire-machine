#include "HappinessMachine.h"
#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

/*
    Algorithm: Fisher-Yates Shuffle
    Reference: Durstenfeld, R. (1964).
    "Algorithm 235: Random permutation."
    Communications of the ACM, 7(7), 420.
    
    This algorithm randomly rearranges the ten scenarios
    without repeating any of them.

    Time complexity: O(n).

    Source:
        https://xlinux.nist.gov/dads/HTML/fisherYatesShuffle.html
 */


const Scenario scenarios[ScenarioCount] = {
    {
        "INSTANTANEOUS DOPAMINE INJECTOR",
        "Select your preferred happiness delivery method.",
        "BUY GTA VI",
        "DO NOTHING",
        {20, 0, 10},
        {0, 0, 0}
    },
    {
        "ARTIFICIAL INTELLIGENCE PRODUCTIVITY BOOSTER",
        "Why waste time thinking when we can think for you?",
        "COPY & PASTE FROM AI",
        "THINK FOR YOURSELF",
        {15, 0, 10},
        {-10, 5, 0}
    },
    {
        "INFINITE SOCIAL VALIDATION ENGINE",
        "Human interaction is unpredictable. Likes aren't.",
        "SCROLL INSTAGRAM",
        "TALK TO A STRANGER",
        {5, 0, 10},
        {-50, 5, 0}
    },
    {
        "INSTANT NUTRITION SOLUTION",
        "Eating is a task. Let us optimize it.",
        "ORDER DELIVERY",
        "COOK REAL FOOD",
        {20, 0, 10},
        {-15, 0, 0}
    },
    {
        "PERSONAL STATUS UPGRADE",
        "You deserve the latest version of yourself.",
        "BUY IPHONE 99",
        "BUY FLOWERS FOR GRANDMA",
        {100, 0, 100},
        {-5, 0, 0}
    }
};

HappinessMachine::HappinessMachine() {
    /*
        constructor that creates an emoty machine befre the first experiment

    */
    offers = 0;
}

void HappinessMachine::Start() {
    /*
        crerls the last run and suffless the ten scenario indices.

    */
    //remove the previous scenario order
    order.clear();

    //store the indices 0 through 9
    for (int i = 0; i < ScenarioCount; i++) {
        order.push_back(i);
    }

    //Fisher-Yates: fill each position from the end using the indices still available

    for (int i = ScenarioCount - 1; i > 0; i--) {
        int randomIndex = GetRandomValue(0, i);
        int temp = order.at(i);
        //swap two positions using a temporary variable
        order.at(i) = order.at(randomIndex);
        order.at(randomIndex) = temp;
    }
    //reset previuos decisions and fictional scores and offers
    decisions.clear();
    totals.engagement = 0;
    totals.pressure = 0;
    totals.profit = 0;
    offers = 0;
    product = "";
    pitch = "";

    ////print the shuffled order in the terminal
    cout << "Experiment started. Scenario order: ";
    for (int i = 0; i < ScenarioCount; i++) {
        cout << order.at(i) + 1 << " ";
    }

    cout << endl;

}

Scenario HappinessMachine::GetCurrentScenario() const {
    /*
        looks u the next scenario in the shuffled order.
        returns the next escenario
    */

    int position = GetDecisionCount();
    if (position >= order.size()) {
        return {};
    }
    int index = order.at(position);
    return scenarios[index];
}

void HappinessMachine::Choose(bool first) {
    /*
        records a choice and adds its effects to the scores
        parameter:
            first: true for first choice or false for second
    */
    if (decisions.size() >= order.size()) {
        return;
    }

    Scenario scenario = GetCurrentScenario();
    Decision decision;
    decision.scenario = scenario.title;
    if (first) {
        decision.choice = scenario.first;
        decision.effect = scenario.firstEffect;
    }
    else {
        decision.choice = scenario.second;
        decision.effect = scenario.secondEffect;
    }
    //add the desicion to the history
    decisions.push_back(decision);
    totals.engagement += decision.effect.engagement;
    totals.pressure += decision.effect.pressure;
    totals.profit += decision.effect.profit;

    cout << "Scenario: " << decision.scenario << endl;
    cout << "Choice: " << decision.choice << endl;
    cout << "Engagement change: " << decision.effect.engagement << endl;
    cout << "Desire pressure change: " << decision.effect.pressure << endl;
    cout << "Profit change: " << decision.effect.profit << endl;
}

void HappinessMachine::Recommend() {
    /*
        generates an offer from the next row of products and descriptions
    */
    if (offers >= OfferLimit) {
        return;
    }
    //possible products for each offer level
    string products[OfferLimit][3] = {
        {"Focus Lamp", "Routine Assistant", "Mood Fridge"},
        {"Dream Pillow", "Luxury Ice Service", "Applause Pass"},
        {"Nostalgia Printer", "Compliment Meter", "Silence Subscription"},
        {"Positive Emotion License", "Prepaid Satisfaction Plan", "Certified Inner Peace"}
    };
    string descriptions[OfferLimit][3] = {
        {"suggests a routine based on your recent choices", "offers a more personalized evening", "recommends a daily comfort upgrade"},
        {"sells a deluxe version of your next good mood", "charges extra for the satisfying part", "adds a subscription to an ordinary comfort"},
        {"requires a refill whenever the good feeling wears off", "charges a convenience fee for forgetting your worries", "sells milestones toward a feeling you already had"},
        {"automatically renews whenever you feel content", "charges you for the relief of canceling it", "sells you a monthly exemption from its own recommendations"}
    };
    //words added before the product name
    string modifiers[3] = { "Adaptive", "Premium", "Personalized" };

    //choose random indices
    int modifierIndex = GetRandomValue(0, 2);
    int productIndex = GetRandomValue(0, 2);
    int descriptionIndex = GetRandomValue(0, 2);

    //create the fictional product name
    product = modifiers[modifierIndex];
    product += " ";
    product += products[offers][productIndex];

    //create the fictional description
    pitch = "This offer ";
    pitch += descriptions[offers][descriptionIndex];
    pitch += ".";

    //increase the number of offers
    offers++;

    cout << "Fictional offer " << offers << ": " << product << endl;
    cout << pitch << endl;
}


int HappinessMachine::Depth() const {
    /*
        Calculates the depth of the recursive tree.
        the tree grows with decisions and offers.
        reurns:
            tree depth, with a maximum of seven.
    */
    int depth = 1 + GetDecisionCount() / 3 + offers;
    if (depth > 7) {
        depth = 7;
    }
    return depth;
}

int HappinessMachine::GetDecisionCount() const {
    /*
        reads the current experiment state
        returns:
            the number of decisions
    */
    return decisions.size();
}

int HappinessMachine::GetOfferCount() const {
    /*
        gets the number of generated offers
        returns: 
            the number of offers
    */
    return offers;
}

string HappinessMachine::GetProduct() const {
    /*
        gets the latest fictional producr name
        returns:
            product name as a string
    */
    return product;
}

string HappinessMachine::GetPitch() const {
    /*
        get the latest fictional product description.
        returns: 
            product description as a string.
    */
    return pitch;
}

Values HappinessMachine::GetTotals() const {
    /*
        gets the current fictional scores.
        returns: 
            a copy of the Values structure.
    */
    return totals;
}


vector<Decision> HappinessMachine::GetDecisions() const {
    /*
        gets the history of user decisions.
        returns: 
            a vector containing the recorded decisions.
    */
    return decisions;
}