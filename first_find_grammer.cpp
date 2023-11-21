#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// Define a structure to represent a production rule
struct Production {
    char lhs;
    string rhs;

    Production(char left, const string& right) : lhs(left), rhs(right) {}
};

// Define a map to store the productions for each non-terminal
unordered_map<char, vector<Production>> productions;

// Define a map to store the FIRST sets for each non-terminal
unordered_map<char, set<char>> firstSets;

// Function to calculate the FIRST set for a non-terminal
set<char> calculateFirst(char nonTerminal) {
    if (firstSets.find(nonTerminal) != firstSets.end()) {
        return firstSets[nonTerminal];
    }

    set<char> result;

    for (const Production& production : productions[nonTerminal]) {
        char firstSymbol = production.rhs[0];

        if (isupper(firstSymbol)) {
            set<char> firstOfFirstSymbol = calculateFirst(firstSymbol);
            result.insert(firstOfFirstSymbol.begin(), firstOfFirstSymbol.end());
        } else {
            result.insert(firstSymbol);
        }
    }

    firstSets[nonTerminal] = result;
    return result;
}

int main() {
    // Initialize the grammar productions
    productions['X'].emplace_back('X', "TnS");
    productions['X'].emplace_back('X', "Rm");
    productions['T'].emplace_back('T', "q");
    productions['T'].emplace_back('T', "#");
    productions['S'].emplace_back('S', "p");
    productions['S'].emplace_back('S', "#");
    productions['R'].emplace_back('R', "om");
    productions['R'].emplace_back('R', "ST");

    // Calculate the FIRST sets for each non-terminal
    for (const auto& entry : productions) {
        char nonTerminal = entry.first;
        calculateFirst(nonTerminal);
    }

    // Print the FIRST sets
    for (const auto& entry : firstSets) {
        char nonTerminal = entry.first;
        set<char> firstSet = entry.second;

        cout << "FIRST(" << nonTerminal << ") = { ";
        for (char symbol : firstSet) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    return 0;
}
