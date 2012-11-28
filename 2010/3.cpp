#include <iostream>
#include <set>
#include <vector>

using namespace std;

unsigned njugs, ounces;
unsigned *jugcaps;

class situation {
public:
    unsigned jugvals[3];

    unsigned serialize() const {
        return ((jugvals[0]) | (jugvals[1] << 8) | (jugvals[2] << 16));
    }

    bool operator<(const situation &b) const {
        return (serialize() < b.serialize());
    }
};

set<situation> sithist;
unsigned iter = 0;

bool iterate(vector<situation> &situations) {
    vector<situation> oldsits(situations);
    situations.clear();

    for (vector<situation>::iterator it = oldsits.begin(); it != oldsits.end(); ++it) {
        set<situation>::iterator ht = sithist.find(*it);
        if (ht != sithist.end()) {
            // give up - we've explored here already
        } else {
            // make our mark
            sithist.insert(*it);

            for (unsigned src = 0; src < njugs; ++src) {
                // check: have we stumbled across gold?
                if (it->jugvals[src] == ounces) {
                    // WHEEEEE
                    return false;
                }

                // fill
                // only fill if src has >0 space left
                if (jugcaps[src] - it->jugvals[src] > 0) {
                    situation sit = *it;
                    sit.jugvals[src] = jugcaps[src];
                    situations.push_back(sit);
                }

                // pour
                for (unsigned dest = 0; dest < njugs; ++dest) {
                    if (dest == src) continue;
                    // only pour if dest has >0 space left AND src has >0 water
                    unsigned destspace = jugcaps[dest] - it->jugvals[dest];
                    unsigned srcwater = it->jugvals[src];
                    if (destspace > 0 && srcwater > 0) {
                        situation sit = *it;
                        // transfer min(dest space, src water)
                        unsigned poured = (destspace<srcwater?destspace:srcwater);
                        sit.jugvals[src] -= poured;
                        sit.jugvals[dest] += poured;
                        situations.push_back(sit);
                    }
                }

                // empty
                // only empty if src has >0 water
                if (it->jugvals[src] > 0) {
                    situation sit = *it;
                    sit.jugvals[src] = 0;
                    situations.push_back(sit);
                }
            }
        }
    }


    return true;
}

void a() {
    cin >> njugs >> ounces;
    jugcaps = new unsigned[njugs];
    for (unsigned i = 0; i < njugs; ++i) {
        cin >> jugcaps[i];
    }

    vector<situation> sits;
    sits.push_back(situation());
    while (iterate(sits)) {
        ++iter;
    }

    cout << iter << endl;
}

bool ccheck() {
    for (ounces = 2; ounces <= 20; ounces += 2) {
        iter = 0;
        sithist.clear();

        vector<situation> sits;
        sits.push_back(situation());
        while (iterate(sits)) {
            if (++iter > 30) {
                return false;
            }
        }
    }
    return true;
}

void c() {
    // 2 jugs
    unsigned sum2 = 0;
    njugs = 2;
    jugcaps = new unsigned[2];
    jugcaps[0] = 20;
    for (jugcaps[1] = 1; jugcaps[1] < 20; ++jugcaps[1]) {
        if (ccheck()) ++sum2;
    }

    unsigned sum3 = 0;
    njugs = 3;
    jugcaps = new unsigned[3];
    jugcaps[0] = 20;
    for (jugcaps[1] = 1; jugcaps[1] < 20; ++jugcaps[1]) {
        for (jugcaps[2] = jugcaps[1] + 1; jugcaps[2] < 20; ++jugcaps[2]) {
            if (ccheck()) ++sum3;
        }
    }

    cout << sum2 << '\n' << sum3 << endl;
}

int main() {
    a();
    return 0;
}
