#ifndef HAPPINESSMACHINE_H
#define HAPPINESSMACHINE_H
#include <vector>
#include <string>
using namespace std;

struct Values {
    int engagement = 0;
    int pressure = 0;
    int profit = 0;
};

struct Scenario {
    string title, situation, first, second;
    Values firstEffect, secondEffect;
};

struct Decision {
    string scenario, choice;
    Values effect;
};

const int ScenarioCount = 10;
const int OfferLimit = 4;

class HappinessMachine {
public:
    HappinessMachine();
    void Start();
    Scenario GetCurrentScenario() const;
    void Choose(bool first);
    void Recommend();
    int Depth() const;
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
    int offers;
    string product;
    string pitch;
};

#endif