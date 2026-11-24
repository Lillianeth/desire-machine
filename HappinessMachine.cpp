#include "HappinessMachine.h"
#include "raylib.h"
using namespace std;

//the ten situations used in the experiment
const Scenario scenarios[ScenarioCount] = {

    {"Visibility for sale",
     "Your posts are getting less engagement.\n"
     "The platform offers a paid boost to reach \nmore people.",
     "Buy a profile boost",
     "Keep your usual reach",
     {3, 2, 3}, {0, -1, 0}},

    {"A quieter commute",
     "Your music app offers an ad-free plan after\n"
     "playing ads during a stressful commute.",
     "Subscribe for quiet",
     "Listen to a downloaded album",
     {2, 1, 3}, {-1, -1, 0}},

    {"The streak",
     "Your fitness app offers a paid streak \nfreeze\n"
     "when you take a rest day.",
     "Protect the streak",
     "Take the rest day",
     {2, 2, 2}, {0, -2, 0}},

    {"Dinner within reach",
     "A delivery app remembers your favorite \nmeal\n"
     "and sends a discount just before dinner.",
     "Use the timed discount",
     "Cook what you have",
     {2, 1, 2}, {0, -1, 0}},

    {"A gift for later",
     "A shopping app offers a discount on a \ngift\n"
     "if you enable future birthday reminders.",
     "Enable gift reminders",
     "Set a calendar reminder",
     {3, 1, 2}, {0, 0, 0}},

    {"One more episode",
     "Your video app queues another episode.\n"
     "You originally planned to go to bed.",
     "Let autoplay continue",
     "Turn off autoplay",
     {3, 2, 1}, {-1, -2, 0}},

    {"The better seat",
     "A ticket site offers an upgrade after \nshowing\n"
     "where your friends will be sitting.",
     "Pay to sit closer",
     "Keep your original seat",
     {1, 2, 3}, {0, -1, 0}},

    {"A focus upgrade",
     "Your productivity app offers a premium \ndashboard\n"
     "that compares your focus time to other \nusers.",
     "Try the comparison plan",
     "Use the basic timer",
     {2, 3, 2}, {1, -1, 0}},

    {"Almost yours",
     "A store offers free shipping if you \nadd\n"
     "another item to your shopping cart.",
     "Add a small extra item",
     "Pay for shipping only",
     {2, 2, 3}, {0, 0, 1}},

    {"A warmer welcome",
     "A multiplayer game offers a paid \ncelebration\n"
     "animation for welcoming a new teammate.",
     "Buy the celebration",
     "Welcome them in chat",
     {2, 1, 2}, {1, 0, 0}}
};

void HappinessMachine::Start() {
    /*starts a new experiment
        clears the previous decisions and resets the scores
        parameters:
            none
        returns:
            nothing*/
    //clear the previous order
    order.clear();

    //store the scenario positions from 0 to 9
    for (int i = 0; i < ScenarioCount; i++) {
        order.push_back(i);
    }
    decisions.clear();  //clear previous decisions
    
    totals.engagement = 0;//reset the fictional scores
    totals.pressure = 0;
    totals.profit = 0;

    offers = 0;//reset the offers
    product = "";
    pitch = "";
}

//gets the next scenario
Scenario HappinessMachine::GetCurrentScenario() const {
    /*returns the next scenario in the shuffled order
        parameters:
            none
        returns:
            a scenario*/
    int position = GetDecisionCount();
    if (position >= order.size()) {
        return {};
    }
    int index = order.at(position);
    return scenarios[index];
}

//records the user's choice
void HappinessMachine::Choose(bool first) {
    /*saves a decision and updates the fictional scores
        parameters:
            first: true for the first option
                   false for the second option
        returns:
            nothing*/
    if (decisions.size() >= order.size()) {
        return;
    }
    Scenario scenario = GetCurrentScenario();
    Decision decision;

    decision.scenario = scenario.title;

    
    if (first) {//check which option was selected
        decision.choice = scenario.first;
        decision.effect = scenario.firstEffect;
    }
    else {
        decision.choice = scenario.second;
        decision.effect = scenario.secondEffect;
    }
    //save the decision
    decisions.push_back(decision);

    //update the fictional scores
    totals.engagement += decision.effect.engagement;
    totals.pressure += decision.effect.pressure;
    totals.profit += decision.effect.profit;
}

//generates fictional product recommendations
void HappinessMachine::Recommend() {
    /*selects a random product and description
        parameters:
            none
        returns:
            nothing*/
    if (offers >= OfferLimit) {
        return;
    }
    //products become more absurd with each offer
    string products[OfferLimit][3] = {
        {"Focus Lamp", "Routine Assistant", "Mood Fridge"},
        {"Dream Pillow", "Luxury Ice Service", "Applause Pass"},
        {"Nostalgia Printer", "Compliment Meter", "Silence Subscription"},
        {"Positive Emotion License", "Prepaid Satisfaction Plan",
         "Certified Inner Peace"}
    };
    string descriptions[OfferLimit][3] = {
        {"suggests a routine based on your recent choices",
         "offers a more personalized evening",
         "recommends a daily comfort upgrade"},

        {"sells a deluxe version of your next good mood",
         "charges extra for the satisfying part",
         "adds a subscription to an ordinary comfort"},

        {"requires a refill whenever the good feeling wears off",
         "charges a convenience fee for forgetting your worries",
         "sells milestones toward a feeling you already had"},

        {"automatically renews whenever you feel content",
         "charges you for the relief of canceling it",
         "sells you a monthly exemption from its own recommendations"}
    };
    string modifiers[3] = {
        "Adaptive",
        "Premium",
        "Personalized"
    };

    //select random positions
    int modifierIndex = GetRandomValue(0, 2);
    int productIndex = GetRandomValue(0, 2);
    int descriptionIndex = GetRandomValue(0, 2);

    //create the product name
    product = modifiers[modifierIndex];
    product += " ";
    product += products[offers][productIndex];

    //create the description
    pitch = "This offer ";
    pitch += descriptions[offers][descriptionIndex];
    pitch += ".";

    offers++;
}

//calculates the tree depth
int HappinessMachine::Depth() const {
    /*increases tree depth as the experiment progresses
        parameters:
            none
        returns:
            tree depth from 0 to 7*/

    //i changed the depth pf the tree when starts, now it makes sence omgggg!!!!
    int depth = GetDecisionCount() * 7 / 10;

    if (depth > 7) {
        depth = 7;
    }
    return depth;
}

//gets the number of decisions
int HappinessMachine::GetDecisionCount() const {
    return decisions.size();
}

//gets the number of offers
int HappinessMachine::GetOfferCount() const {
    return offers;
}

//gets the product name
string HappinessMachine::GetProduct() const {
    return product;
}

//gets the product description
string HappinessMachine::GetPitch() const {
    return pitch;
}

//gets the fictional scores
Values HappinessMachine::GetTotals() const {
    return totals;
}

//gets the user's decisions
vector<Decision> HappinessMachine::GetDecisions() const {
    return decisions;
}
