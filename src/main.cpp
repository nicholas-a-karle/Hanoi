#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <math.h>
#include "data.h"
#include <random>

using namespace std;

#include <chrono>
#include <ctime>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

#define SRC 0
#define DST 1
#define TMP 2

struct Towers {
    vector<vector<int>> peg;
    int n;

    public:
    Towers() {
        peg.push_back(vector<int>{}); peg.push_back(vector<int>{}); peg.push_back(vector<int>{});
        n = 50;
        for (int i = 50; i >= 1; --i) peg[SRC].push_back(i);
        //tower should look like [max, max-1, ... min+1, min]
    }
    Towers(int in) {
        peg.push_back(vector<int>{}); peg.push_back(vector<int>{}); peg.push_back(vector<int>{});
        n = in;
        for (int i = in; i >= 1; --i) peg[SRC].push_back(i);
    }

    bool move(int a, int b) {
        if (a < 0 || a > 2 || b < 0 || b > 2) return false;
        if (a == b) return false;
        if (peg[a].size() <= 0) return false;
        if (peg[b].size() > 0 && peg[a].back() > peg[b].back()) return false;

        peg[b].push_back(peg[a].back());
        peg[a].pop_back();
        return true;
    }

    bool move(int a, int b, int k) {
        if (k == 1) {
            cout << "" << a << " " << b << " \t";
            cout << (peg[SRC].size() > 0 ? to_string(peg[SRC].back()) : "_") << "  ";
            cout << (peg[TMP].size() > 0 ? to_string(peg[TMP].back()) : "_") << "  ";
            cout << (peg[DST].size() > 0 ? to_string(peg[DST].back()) : "_") << "  " << endl;
        }

        if (k > peg[a].size()) return false;

        //find SRC, DST, or TMP, set c to that which neither a nor b is
        //if a == b or none of the above, return false
        int c = -1;
        switch (a) {
            case SRC:
                switch (b) {
                    case SRC:
                        return false;
                    case DST:
                        c = TMP;
                        break;
                    case TMP:
                        c = DST;
                        break;
                    default: return false;
                }
                break;
            case DST:
                switch (b) {
                    case SRC:
                        c = TMP;
                        break;
                    case DST:
                        return false;
                    case TMP:
                        c = SRC;
                        break;
                    default: return false;
                }
                break;
            case TMP:
                switch (b) {
                    case SRC:
                        c = DST;
                        break;
                    case DST:
                        c = SRC;
                        break;
                    case TMP:
                        return false;
                    default: return false;
                }
                break;
            default: return false;
        }
        
        //two cases
        if (k == 1) {
            //simple case
            if (!move(a, b)) return false;
        } else {
            //recursive case
            if (!move(a, c, k-1)) return false;
            if (!move(a, b, 1)) return false;
            if (!move(c, b, k-1)) return false;
        }
        return true;
    }
};

#define N 5

int main(/*int argc, char *argv[]*/) {
    Towers t(N);
    cout << "FLAG RESULT: " << t.move (SRC, DST, N) << endl;
}
