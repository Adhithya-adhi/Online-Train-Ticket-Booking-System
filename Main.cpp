#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Train {
    int no, seats;
    string name, src, dst, dep, arr;
    double fare;
};

struct Booking {
    string pnr, user, date, status;
    int train, seat;
    double fare;
};

class System {
    vector<Train> t = {
        {12675, 50, "Chennai Kovai Express", "Chennai", "Coimbatore", "06:10", "12:45", 385.0},
        {12608, 50, "Chennai Mail", "Chennai", "Coimbatore", "21:40", "05:50", 350.0}
    };
    vector<Booking> b;
    map<string, string> pass;
    int pnr = 900000000;

    int find(int n) {
        for (int i = 0; i < t.size(); i++) {
            if (t[i].no == n) return i;
        }
        return -1;
    }

    void show(Train x) {
        cout << x.no << " " << x.name << " " << x.src << "-" << x.dst
             << " | " << x.dep << "-" << x.arr << " | Rs." << x.fare
             << " | Seats: " << x.seats << "\n";
    }

    void reg() {
        string n, u, p;
        cout << "Name: "; getline(cin, n);
        cout << "Username: "; getline(cin, u);
        cout << "Password: "; getline(cin, p);

        if (n.empty() || u.empty() || p.empty() || pass.count(u)) {
            cout << "Invalid/duplicate details.\n";
            return;
        }
        pass[u] = p;
        cout << "Registration successful.\n";
    }

    bool login(string &u) {
        string p;
        cout << "Username: "; getline(cin, u);
        cout << "Password: "; getline(cin, p);

        if (pass.count(u) && pass[u] == p) {
            cout << "Login successful.\n";
            return true;
        }
        cout << "Invalid login.\n";
        return false;
    }

    void search() {
        string s, d;
        cout << "Source: "; getline(cin, s);
        cout << "Destination: "; getline(cin, d);
        bool ok = false;
        for (auto x : t) {
            if (x.src == s && x.dst == d) {
                show(x);
                ok = true;
            }
        }
        if (!ok) cout << "No train found.\n";
    }

    void book(string u) {
        string s, d, date;
        int n;
        cout << "Source: "; getline(cin, s);
        cout << "Destination: "; getline(cin, d);
        cout << "Date: "; getline(cin, date);

        for (auto x : t) {
            if (x.src == s && x.dst == d) show(x);
        }

        cout << "Train number: "; cin >> n; cin.ignore();
        int i = find(n);
        if (i < 0 || t[i].src != s || t[i].dst != d || t[i].seats <= 0) {
            cout << "Invalid train/no seats.\n";
            return;
        }

        int pay;
        cout << "1.UPI 2.Card 3.Net Banking\nPayment: ";
        cin >> pay; cin.ignore();
        if (pay < 1 || pay > 3) {
            cout << "Invalid payment.\n";
            return;
        }

        int seat = 51 - t[i].seats--;
        string id = "PNR" + to_string(pnr++);
        b.push_back({id, u, date, "Confirmed", n, seat, t[i].fare});
        cout << "Booking successful. PNR: " << id << " Seat: " << seat << "\n";
    }

    void mybook(string u) {
        for (auto x : b) {
            if (x.user == u) {
                cout << x.pnr << " Train:" << x.train
                     << " Seat:" << x.seat << " Fare:Rs." << x.fare
                     << " Status:" << x.status << "\n";
            }
        }
    }

    void cancel(string u) {
        string p;
        cout << "PNR: "; getline(cin, p);
        for (auto &x : b) {
            if (x.pnr == p && x.user == u && x.status == "Confirmed") {
                x.status = "Cancelled";
                int i = find(x.train);
                if (i >= 0) t[i].seats++;
                cout << "Cancelled. Refund: Rs." << (x.fare * 0.90) << "\n";
                return;
            }
        }
        cout << "Booking not found.\n";
    }

public:
    void run() {
        int c;
        do {
            cout << "\nONLINE TRAIN TICKET BOOKING SYSTEM\n1.Register 2.Login 3.Search 4.Exit\nChoice: ";
            cin >> c; cin.ignore();
            if (c == 1) reg();
            else if (c == 3) search();
            else if (c == 2) {
                string u;
                if (login(u)) {
                    int x;
                    do {
                        cout << "\n1.Search 2.Book 3.My Bookings 4.Cancel 5.Logout\nChoice: ";
                        cin >> x; cin.ignore();
                        if (x == 1) search();
                        else if (x == 2) book(u);
                        else if (x == 3) mybook(u);
                        else if (x == 4) cancel(u);
                    } while (x != 5);
                }
            }
        } while (c != 4);
    }
};

int main() {
    System s;
    s.run();
    return 0;
}
