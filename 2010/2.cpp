#include <iostream>

using namespace std;

typedef unsigned short *die_t;

typedef unsigned short dir_t;
#define U 0
#define R 1
#define D 2
#define L 3

typedef int coord_t;
#define SIZE 11
#define X(c) ((c)%SIZE)
#define Y(c) ((c)/SIZE)
#define AT(x,y) ((x)+(y)*SIZE)
#define OFF(n) ((n) < 0 || (n) >= SIZE)
short movecodes[][2] = {
    {0,-1},
    {1,0},
    {0,1},
    {-1,0},
};
void coord_move(coord_t &c, dir_t d) {
    coord_t x = X(c) + movecodes[d][0], y = Y(c) + movecodes[d][1];
    while (x < 0) x += SIZE;
    while (x >= SIZE) x -= SIZE;
    while (y < 0) y += SIZE;
    while (y >= SIZE) y -= SIZE;
    c = AT(x,y);
}

die_t die;
coord_t diec;
dir_t dieh;

unsigned short grid[SIZE*SIZE];

unsigned short flipcodes[][6] = {
    {3,2,0,1,4,5},
    {4,5,2,3,1,0},
    {2,3,1,0,4,5},
    {5,4,2,3,0,1}
};

void move() {
    // calc new heading
    grid[diec] += die[0];
    if (grid[diec] > 6) grid[diec] -= 6;
    switch (grid[diec]) {
    case 1: case 6:
        break;
    case 2:
        dieh += 1;
        break;
    case 3: case 4:
        dieh += 2;
        break;
    case 5:
        dieh += 3;
        break;
    }
    dieh %= 4;
    // move coord
    coord_move(diec, dieh);
    // flip die
    die_t newdie = new unsigned short[6];
    for (unsigned i = 0; i < 6; ++i) {
        newdie[i] = die[flipcodes[dieh][i]];
    }
    delete die;
    die = newdie;
}

void out() {
    for (coord_t y = Y(diec) - 1; y <= Y(diec) + 1; ++y) {
        for (coord_t x = X(diec) - 1; x <= X(diec) + 1; ++x) {
            if (OFF(x) || OFF(y)) cout << 'X';
            else cout << grid[AT(x,y)];
        }
        cout << '\n';
    }
    cout << endl;
}

void a() {
    die = new unsigned short[6];
    die[0] = 1;
    die[1] = 6;
    die[2] = 2;
    die[3] = 5;
    die[4] = 3;
    die[5] = 4;
    diec = AT(5,5);
    dieh = U;

    for (coord_t c = 0; c < SIZE*SIZE; ++c) {
        grid[c] = 1;
    }

    for (coord_t y = 4; y <= 6; ++y) {
        for (coord_t x = 4; x <= 6; ++x) {
            cin >> grid[AT(x,y)];
        }
    }

    while (true) {
        unsigned val;
        cin >> val;
        if (val) {
            while (val--) {
                move();
            }
            out();
        } else break;
    }
}

int main() {
    a();
    return 0;
}
