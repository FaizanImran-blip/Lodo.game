#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

class LodoGame {
public:
    string name;
    string color;
    LodoGame(string n, string c) : name(n), color(c) {}
};

class Game {
public:
    vector<LodoGame> play;
    Game() {
        play.push_back(LodoGame("Player 1", "Red"));
        play.push_back(LodoGame("Player 2", "Green"));
        play.push_back(LodoGame("Player 3", "Blue"));
        play.push_back(LodoGame("Player 4", "Yellow"));
    }
};

class TokenPas {
public:
    vector<int> tokens;
    int completedTokens = 0;

    TokenPas() {
        tokens = vector<int>(4, 0);
    }

    int rollDice(int playerNum) {
        cout << "Press Enter to roll the dice for Player " << playerNum << endl;
        cin.ignore();
        int roll = rand() % 6 + 1;
        cout << "Player " << playerNum << " rolled a " << roll << endl;
        return roll;
    }

    void moveToken(int tokenIndex, int diceRoll) {
        if (tokens[tokenIndex] < 50) {
            tokens[tokenIndex] += diceRoll;
            if (tokens[tokenIndex] >= 50) {
                tokens[tokenIndex] = 50;
                completedTokens++;
                cout << "Token " << tokenIndex << " completed!" << endl;
            } else {
                cout << "Token " << tokenIndex << " moved to position " << tokens[tokenIndex] << endl;
            }
        } else {
            cout << "Token " << tokenIndex << " already completed." << endl;
        }
    }

    bool hasWon() {
        return completedTokens == 4;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Game g1;
    vector<TokenPas> players(4);
    vector<bool> playerWon(4, false);
    int winners = 0;

    cout << "Welcome to Ludo King" << endl;
    cout << "Press Enter to Start" << endl;
    cin.get();

    while (winners < 4) {
        for (int i = 0; i < 4; i++) {
            if (playerWon[i]) continue;

            cout << "Turn of: " << g1.play[i].name << " (" << g1.play[i].color << ")" << endl;
            int dice = players[i].rollDice(i + 1);

            cout << "Token positions: ";
            for (int j = 0; j < 4; j++) {
                cout << "[" << j << "]:" << players[i].tokens[j] << "  ";
            }
            cout << "\nChoose a token to move (0-3): ";
            int tokenChoice;
            cin >> tokenChoice;
            cin.ignore();

            if (tokenChoice < 0 || tokenChoice >= 4) {
                cout << "Invalid token number. Skipping turn." << endl;
                continue;
            }

            players[i].moveToken(tokenChoice, dice);

            if (players[i].hasWon()) {
                playerWon[i] = true;
                winners++;
                cout << "Player " << g1.play[i].name << " has completed all 4 tokens!" << endl;
                if (winners == 4) {
                    cout << "All players have completed their tokens!" << endl;
                }
            }
        }
    }

    cout << "Game Over!" << endl;

    for (int i = 0; i < 4; i++) {
        cout << g1.play[i].name << " completed: " << players[i].completedTokens << " tokens." << endl;
    }

    int loser = -1, minComplete = 5;
    for (int i = 0; i < 4; i++) {
        if (players[i].completedTokens < minComplete) {
            minComplete = players[i].completedTokens;
            loser = i;
        }
    }

    if (loser != -1) {
        cout << g1.play[loser].name << " is the LOSER with only " << minComplete << " tokens completed!" << endl;
    }

    return 0;
}
