#include <iostream>
#include <cassert>
using namespace std;

/* the structure point_t represents a single point */
struct point_t {
    /* we put the three points that this point is connected to in this array
     * of pointers.
     * connections[0] holds the straight part
     * connections[1] and [2] hold the two curved parts
     * I arbitrarily chose that connections[1] is the left side and
     * connections[2] is the right side on the diagram given in the question.
     */
    point_t *connections[3];

    /* the state holds the connection index that the train should go to
     * if it entered in the straight part
     */
    int state;

    /* is this point a flip-flop point? */
    bool flipflop;

};

/* there are 24 points */
point_t points[24];
point_t *curPoint, *nextPoint;

int findConnection(point_t *point, point_t *otherPoint)
{
    for (int i = 0; i < 3; ++i) 
        if (point->connections[i] == otherPoint) return i;

    // we should never get here...
    cout << "Point " << char(point-points+'A')
         << " isn't connected to point " << char(otherPoint-points+'A') << endl;
    assert(false);
}

void doStep() {
    int inConnection = findConnection(nextPoint, curPoint),
        outConnection;
    curPoint = nextPoint;
    if (inConnection == 0) {
        // entering on a straight piece, so exit out of the point state
        outConnection = curPoint->state;
        if (curPoint->flipflop) {
            // flip state
            curPoint->state ^= 3;
        }
    } else {
        // entering on a curved piece, so exit out of straight piece
        outConnection = 0;
        if (!curPoint->flipflop) {
            // lazy, so have to set state
            curPoint->state = inConnection;
        }
    }
    nextPoint = curPoint->connections[outConnection];
}

int main() {
    /* set up our points */

    /* A - D */
    for (int i = 0; i < 4; ++i) {
        /* conveniently i^3 flips the bits so A goes to D, B goes to C etc */
        points[i].connections[0] = &points[i^3];
        points[i].connections[1] = &points[4 + i*2];
        points[i].connections[2] = &points[5 + i*2];
    }
    /* U - X */
    for (int i = 20; i < 24; ++i) {
        /* slightly different bitmask but XOR still works */
        points[i].connections[0] = &points[i^1];
        points[i].connections[1] = &points[12 + (i-20)*2];
        points[i].connections[2] = &points[13 + (i-20)*2];
    }
    /* E - L */
    for (int i = 4; i < 12; ++i) {
        points[i].connections[0] = &points[(i-4)/2];
        points[i].connections[1] = &points[12 + (i-4)];
        points[i].connections[2] = &points[12 + (i-4+1)%8];
    }
    /* M - T */
    for (int i = 12; i < 20; ++i) {
        points[i].connections[0] = &points[20 + (i-12)/2];
        points[i].connections[1] = &points[4 + (i-12+7)%8];
        points[i].connections[2] = &points[4 + (i-12)];
    }

    /* every point starts to the left, as a lazy point */
    for (int i = 0; i < 24; ++i) {
        points[i].state = 1;
        points[i].flipflop = false;
    }
    
    /* which ones are flip flop? */
    for (int i = 0; i < 6; ++i) {
        char ch;
        cin >> ch;
        points[ch-'A'].flipflop = true;
    }
    cin.ignore(99, '\n');

    char chcur, chnext;
    cin >> chcur >> chnext;
    curPoint = &points[chcur-'A'];
    nextPoint = &points[chnext-'A'];

    int nSteps;
    cin >> nSteps;
    while (nSteps--) {
        doStep();
    }

    cout << char(curPoint-points+'A') << char(nextPoint-points+'A') << endl;
    return 0;
}
