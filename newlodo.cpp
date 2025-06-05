#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
using namespace std;

class f {
public:
    int p;
    string c;
    string pl;
    bool co;

    f(int a, string b, string z, bool con) : p(a), c(b), pl(z), co(con) {}

    void dice();
    void posi(int a);
    void cond();
    bool win();
};

void f::dice() {
    int i = rand() % 6 + 1;
    cout << pl << " (" << c << ") rolls dice: " << i << endl;
    p += i;
    if (p > 100) p = 100;
    posi(p);
}

void f::posi(int a) {
    cout << pl << " is now at position: " << a << endl;
    cond();
}

void f::cond() {
    co = (p >= 100);
    if (win()) {
        cout << pl << " WINS the game!" << endl;
    }
    else{
        cout<<"enter to dice the next player:: "<<endl;
        cin.ignore();
    }
}

bool f::win() {
    return co;
}

class lodo {
public:
    vector<f> players;

    void add_player(int p, string color, string player) {
        players.push_back(f(p, color, player, false));
    }
void screen()
{
    system("cls");
}
    void start_game() {
        cout<<"press enter to roll the dice:: "<<endl;
        cin.ignore();
        bool game_over = false;
        while (!game_over) {
            for (int i = 0; i < players.size(); i++) {
                screen();
                cout << "----- Turn of " << players[i].pl << " -----" << endl;
                players[i].dice();
                if (players[i].win()) {
                    game_over = true;
                    break;
                }
            }
        }
    }
};

int main() {
    srand(time(0));
    int a;
    cout << "Enter number of players (max 4): ";
    cin >> a;

    lodo d;
    vector<string> colors = {"Yellow", "Green", "Red", "Blue"};
    for (int i = 0; i < a; i++) {
        string pname = "Player " + to_string(i + 1);
        d.add_player(0, colors[i], pname);
    }
   
    d.start_game();
    return 0;
}
