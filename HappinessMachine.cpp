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
    
    //these are the ten situations used in the experiment.
    //each scenario has a title, description, two choices,
    //and the score changes for each choice.

   
    {"Visibility for sale", "Your posts are getting less engagement. The platform offers a paid boost to reach more people.", "Buy a profile boost", "Keep your usual reach", {3,2,3}, {0,-1,0}},
    {"A quieter commute", "Your music app offers an ad-free plan after playing ads during a stressful commute.", "Subscribe for quiet", "Listen to a downloaded album", {2,1,3}, {-1,-1,0}},
    {"The streak", "Your fitness app offers a paid streak freeze when you take a rest day.", "Protect the streak", "Take the rest day", {2,2,2}, {0,-2,0}},
    {"Dinner within reach", "A delivery app remembers your favorite meal and sends a discount just before dinner.", "Use the timed discount", "Cook what you have", {2,1,2}, {0,-1,0}},
    {"A gift for later", "A shopping app offers a discount on a gift if you let it remind you about future birthdays.", "Enable gift reminders", "Set a calendar reminder", {3,1,2}, {0,0,0}},
    {"One more episode", "Your video app queues another episode when the credits roll. You planned to go to bed.", "Let autoplay continue", "Turn off autoplay", {3,2,1}, {-1,-2,0}},
    {"The better seat", "A ticket site offers an upgrade after showing where your friends will be sitting.", "Pay to sit closer", "Keep your original seat", {1,2,3}, {0,-1,0}},
    {"A focus upgrade", "Your productivity app offers a premium dashboard that compares your focus time to other users.", "Try the comparison plan", "Use the basic timer", {2,3,2}, {1,-1,0}},
    {"Almost yours", "A store offers free shipping if you add another item to a cart that already contains what you need.", "Add a small extra item", "Pay for shipping only", {2,2,3}, {0,0,1}},
    {"A warmer welcome", "A multiplayer game offers a paid celebration animation for welcoming a new teammate.", "Buy the celebration", "Welcome them in chat", {2,1,2}, {1,0,0}}
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
