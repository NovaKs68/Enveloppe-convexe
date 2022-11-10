// argument_definitions.cpp
// compile with: /EHsc
#include <iostream>
#include <string.h>
#include <time.h>
#include "polygone.h"
#include "point.h"
#include "enveloppe.h"
#include "graphics.h"



using namespace std;
int main(int argc, char* argv[], char* envp[])
{
    cout << "HELLO WORLD" << "\n";
    Polygone P = Polygone();
    vector<Point> swarm;

    srand(time(0));

    const int screenSize = 400;

    for (int i = 0; i < 300; i++) {
        swarm.push_back(Point(rand() % screenSize, rand() % screenSize));
    }

    //swarm.push_back(Point(10, 10));
    //swarm.push_back(Point(20, 50));
    //swarm.push_back(Point(40, 20));
    //swarm.push_back(Point(50, 60));
    //swarm.push_back(Point(60, 10));
    //swarm.push_back(Point(70, 40));
    //swarm.push_back(Point(90, 30));
    //swarm.push_back(Point(90, 70));
    //swarm.push_back(Point(90, 20));
    

    opengraphsize(500, 500);

    for (auto point : swarm)
    {
        plot(point.x(), point.y());
    }

    enveloppe(swarm, P);

    getch();
    closegraph();
}