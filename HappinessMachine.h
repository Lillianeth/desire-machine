#ifndef HAPPINESSMACHINE_H
#define HAPPINESSMACHINE_H

#include <string>
#include <vector>
using namespace std;

//stores the fictional scores
class Values {
public:
    int engagement = 0;
    int pressure = 0;
    int profit = 0;
};

//stores one situation with two choices
class Scenario {
public:
    string title;
    string situation;
    string first;
    string second;
    Values firstEffect;
    Values secondEffect;
};

//stores one decision made by the user
class Decision {
public:
    string scenario;
    string choice;
    Values effect;
};

//experiment limits
const int ScenarioCount = 10;
const int OfferLimit = 4;

class HappinessMachine {
public:
    void Start();
    Scenario GetCurrentScenario() const;
    void Choose(bool first);
    void Recommend();
    int Depth() const;

    //gets information needed by main.cpp
    int GetDecisionCount() const;
    int GetOfferCount() const;
    string GetProduct() const;
    string GetPitch() const;
    Values GetTotals() const;
    vector<Decision> GetDecisions() const;



private:
    vector<int> order;
    vector<Decision> decisions;

    Values totals;
    int offers = 0;

    string product;
    string pitch;
};
/*AI assistance: OpenAI ChatGPT (November 2026)
    Prompted:
    "If I cant use pointers or references, How can I store multiple decisions using vectors
    and return information from my class without them?"

    Answer:
    ChatGPT explained that a vector can store multiple decision objects and that getter functions can return
    values or copies instead of pointers or references.
    For example, vector<Decision> GetDecisions() const returns a copy of the stored decisions.

    Source:
    OpenAI. (2026). ChatGPT [Large language model].*/
#endif

    
