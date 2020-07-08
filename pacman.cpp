#include "TXLib.h"
const int NumberSmallPacMans = 5;

//-----------------------------------------------------------------------------

struct PacMan {
    double x, y, r, speed, alfa;
    COLORREF color;
    boolean visible;
    void keyRead ();
    void hunter (PacMan target);
    void draw (int t);
    void move ();
    void randomMove();
};

//-----------------------------------------------------------------------------

bool pacmansIntersect(PacMan pac1, PacMan pac2, int d);

//-----------------------------------------------------------------------------

int main() {
    txCreateWindow (800, 600);

    PacMan pacman =      {200,          300,          100, 10,            0,            RGB (255, 255, 0),  true};
    PacMan pacmanBig =   {600,          300,          200, 3,             rand() % 360, RGB (0, 0, 255),    true};

    PacMan pacmanSmalls [NumberSmallPacMans];
    for (int i = 0; i < NumberSmallPacMans; i++)
        pacmanSmalls [i] = {rand() % 800, rand() % 600, 40,  rand() % 10+5, rand() % 360, RGB (100, 255, 100), true};


    int t = 0;
    while (true) {
          pacman.keyRead();
          for (int i = 0; i < NumberSmallPacMans; i++)
               pacmanSmalls[i].randomMove();
          //pacmanSmall.randomMove();
          pacmanBig.hunter(pacman);
          //pacmanBig2.hunter(pacman);

          pacman.move();
          for (int i = 0; i < NumberSmallPacMans; i++)
                pacmanSmalls [i].move();
          pacmanBig.move();
          //pacmanBig2.move();

          for (int i = 0; i < NumberSmallPacMans; i++)
                if (pacmansIntersect(pacman, pacmanSmalls[i], 50))
                        //pacmanSmalls[i].x = rand() % 800;
                        pacmanSmalls[i].visible = false;
          txSetFillColor (TX_BLACK);
          txSleep(100);
          txClear();

          pacman.draw(t);
          for (int i = 0; i<NumberSmallPacMans; i++)
                pacmanSmalls [i].draw(t);
          pacmanBig.draw(t);
          //pacmanBig2.draw(t);

          t += 1;
    }
    return 0;
}

//-----------------------------------------------------------------------------

void PacMan::draw (int t) {
    if (visible) {
        txSetColor (TX_GREEN);
        txSetFillColor (color);
        txPie (x - r/2, y - r/2, x + r/2, y + r/2, alfa + 25 + 20*sin(0.9*t), 360- 40 - 40*sin(0.9*t));
    }
}

void PacMan::keyRead () {
    if (txGetAsyncKeyState (VK_RIGHT)) alfa -= 15;
    if (txGetAsyncKeyState (VK_LEFT))  alfa += 15;
    if (txGetAsyncKeyState (VK_UP))  speed += 2;
    if (txGetAsyncKeyState (VK_DOWN))  speed -= 2;
}

void PacMan::move () {
    x = x + cos (alfa*txPI/180) * speed;
    y = y - sin (alfa*txPI/180) * speed;

    if (x > 800 + r) x = -r/2;
    if (x < - r) x = 800 + r/2;

    if (y > 600 + r) y = -r/2;
    if (y < - r) y = 600 + r/2;
}

void PacMan::randomMove () {
    //alfa = alfa + rand()%11-5;
    if (rand() % 10 == 0 )
         alfa = alfa + 60 *(rand()%3 - 1);

    x = x + cos (alfa*txPI/180) * speed;
    y = y - sin (alfa*txPI/180) * speed;

    if (x > 800 + r/2) x = -r/2;
    if (x < - r/2) x = 800 + r/2;

    if (y > 600 + r/2) y = -r/2;
    if (y < - r/2) y = 600 + r/2;
}

void PacMan::hunter (PacMan target) {
     double dx = target.x - x;
     double dy = y - target.y;

     if (dx > 0 && dy >= 0) alfa = atan (dy/dx);
     if (dx > 0 && dy < 0)  alfa = atan (dy/dx) + 2 * txPI;
     if (dx < 0)            alfa = atan (dy/dx) + txPI;
     if (dx == 0 && dy>0)   alfa = txPI / 2;
     if (dx == 0 && dy<0)   alfa = 3*txPI / 2;

     alfa = alfa * 180 / txPI;
}


bool pacmansIntersect(PacMan pac1, PacMan pac2, int dist){
    if ((pac1.x - pac2.x) * (pac1.x - pac2.x) + (pac1.y - pac2.y) * (pac1.y - pac2.y) < dist*dist)
        return true;
    return false;
}
