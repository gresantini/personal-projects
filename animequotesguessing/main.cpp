
// guess which anime does the quote come from!



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

string toLower(string str){
    for (char& c: str) {
        c = tolower(c);
    }
    return str;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

int main() {
    ifstream file("C:\\Users\\gresa\\CLionProjects\\animequotesguessing\\quotes.txt");
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    srand(time(NULL));

    vector<string> quotes;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            quotes.push_back(line);
        }
    }

    string playAgain;

    do {
        string quoteOnly, actualAnime;

        // Keep picking until valid format found
        while (true) {
            int random_Index = rand() % quotes.size();
            string fullQuote = quotes[random_Index];

            size_t dashPos = fullQuote.find("—");
            if (dashPos == string::npos) continue;

            quoteOnly = trim(fullQuote.substr(0, dashPos));
            string afterDash = fullQuote.substr(dashPos + 1);

            size_t lastComma = afterDash.rfind(',');
            if (lastComma == string::npos) continue;

            actualAnime = trim(afterDash.substr(lastComma + 1));
            if (!quoteOnly.empty() && !actualAnime.empty()) break;
        }

        cout << "\nGuess the anime for this quote:\n" << quoteOnly << endl;

        string userGuess;
        getline(cin, userGuess);

        if (toLower(userGuess) == toLower(actualAnime)) {
            cout << "Correct!" << endl;
        } else {
            cout << "That's wrong. The correct answer was: " << actualAnime << endl;
        }

        cout << "\nDo you want to play again? (yes/no): ";
        getline(cin, playAgain);

    } while (toLower(playAgain) == "yes");

    cout << "Thanks for playing!" << endl;
    return 0;
}
