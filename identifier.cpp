#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    bool foo = false;
    getline(cin, str);

    if (!str.empty() &&
        (str[0] == '_' || (str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))) {
        foo = true;
        for (int i = 1; i < str.size(); i++) {
            if (str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '$') {
                foo = true;
            } 
            else if (str[i] >= '0' && str[i] <= '9') {
                foo = false; // A digit in the middle, not a valid identifier
                break;
            } 
            else if (str[i] == ' ') {
                foo = false; // Space found, not a valid identifier
                break;
            } 
            else {
                foo = false;
                break;
            }
        }
    }

    if (foo) {
        // Check for keywords "int" or "float"
        if (str == "int" || str == "float" || str=="string" || str=="if" ) {
            cout << "keyword" << endl;
        } else {
            cout << "identifier" << endl;
        }
    } else {
        cout << "not identifier" << endl;
    }

    return 0;
}
