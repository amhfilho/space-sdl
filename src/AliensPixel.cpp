#include "AlienPixel.h"
class Alien1 : public AlienPixel {
public:
    Alien1() {
        cells.push_back(Cell{0, 2});
        cells.push_back(Cell{0, 8});

        cells.push_back(Cell{1, 3});
        cells.push_back(Cell{1, 7});

        cells.push_back(Cell{2, 2});
        cells.push_back(Cell{2, 3});
        cells.push_back(Cell{2, 4});
        cells.push_back(Cell{2, 5});
        cells.push_back(Cell{2, 6});
        cells.push_back(Cell{2, 7});
        cells.push_back(Cell{2, 8});

        cells.push_back(Cell{3, 1});
        cells.push_back(Cell{3, 2});
        cells.push_back(Cell{3, 4});
        cells.push_back(Cell{3, 5});
        cells.push_back(Cell{3, 6});
        cells.push_back(Cell{3, 8});
        cells.push_back(Cell{3, 9});

        cells.push_back(Cell{4, 0});
        cells.push_back(Cell{4, 1});
        cells.push_back(Cell{4, 2});
        cells.push_back(Cell{4, 3});
        cells.push_back(Cell{4, 4});
        cells.push_back(Cell{4, 5});
        cells.push_back(Cell{4, 6});
        cells.push_back(Cell{4, 7});
        cells.push_back(Cell{4, 8});
        cells.push_back(Cell{4, 9});
        cells.push_back(Cell{4, 10});

        cells.push_back(Cell{5, 0});
        cells.push_back(Cell{5, 2});
        cells.push_back(Cell{5, 3});
        cells.push_back(Cell{5, 4});
        cells.push_back(Cell{5, 5});
        cells.push_back(Cell{5, 6});
        cells.push_back(Cell{5, 7});
        cells.push_back(Cell{5, 8});
        cells.push_back(Cell{5, 10});

        cells.push_back(Cell{6, 0});
        cells.push_back(Cell{6, 2});
        cells.push_back(Cell{6, 8});
        cells.push_back(Cell{6, 10});

        cells.push_back(Cell{7, 3});
        cells.push_back(Cell{7, 4});
        cells.push_back(Cell{7, 6});
        cells.push_back(Cell{7, 7});
    }
};

class Alien2 : public AlienPixel {
public:
    Alien2() {
        cells.push_back(Cell{0, 4});
        cells.push_back(Cell{0, 5});
        cells.push_back(Cell{0, 6});
        cells.push_back(Cell{0, 7});

        cells.push_back(Cell{1, 1});
        cells.push_back(Cell{1, 2});
        cells.push_back(Cell{1, 3});
        cells.push_back(Cell{1, 4});
        cells.push_back(Cell{1, 5});
        cells.push_back(Cell{1, 6});
        cells.push_back(Cell{1, 7});
        cells.push_back(Cell{1, 8});
        cells.push_back(Cell{1, 9});
        cells.push_back(Cell{1, 10});

        cells.push_back(Cell{2, 0});
        cells.push_back(Cell{2, 1});
        cells.push_back(Cell{2, 2});
        cells.push_back(Cell{2, 3});
        cells.push_back(Cell{2, 4});
        cells.push_back(Cell{2, 5});
        cells.push_back(Cell{2, 6});
        cells.push_back(Cell{2, 7});
        cells.push_back(Cell{2, 8});
        cells.push_back(Cell{2, 9});
        cells.push_back(Cell{2, 10});
        cells.push_back(Cell{2, 11});

        cells.push_back(Cell{3, 0});
        cells.push_back(Cell{3, 1});
        cells.push_back(Cell{3, 2});
        cells.push_back(Cell{3, 5});
        cells.push_back(Cell{3, 6});
        cells.push_back(Cell{3, 9});
        cells.push_back(Cell{3, 10});
        cells.push_back(Cell{3, 11});

        cells.push_back(Cell{4, 0});
        cells.push_back(Cell{4, 1});
        cells.push_back(Cell{4, 2});
        cells.push_back(Cell{4, 3});
        cells.push_back(Cell{4, 4});
        cells.push_back(Cell{4, 5});
        cells.push_back(Cell{4, 6});
        cells.push_back(Cell{4, 7});
        cells.push_back(Cell{4, 8});
        cells.push_back(Cell{4, 9});
        cells.push_back(Cell{4, 10});
        cells.push_back(Cell{4, 11});

        cells.push_back(Cell{5, 2});
        cells.push_back(Cell{5, 3});
        cells.push_back(Cell{5, 4});
        cells.push_back(Cell{5, 7});
        cells.push_back(Cell{5, 8});
        cells.push_back(Cell{5, 9});

        cells.push_back(Cell{6, 1});
        cells.push_back(Cell{6, 2});
        cells.push_back(Cell{6, 5});
        cells.push_back(Cell{6, 6});
        cells.push_back(Cell{6, 9});
        cells.push_back(Cell{6, 10});

        cells.push_back(Cell{7, 2});
        cells.push_back(Cell{7, 3});
        cells.push_back(Cell{7, 8});
        cells.push_back(Cell{7, 9});
    }
};

class Alien3 : public AlienPixel {
public:
    Alien3() {
        cells.push_back(Cell{0, 3});
        cells.push_back(Cell{0, 4});

        cells.push_back(Cell{1, 2});
        cells.push_back(Cell{1, 3});
        cells.push_back(Cell{1, 4});
        cells.push_back(Cell{1, 5});

        cells.push_back(Cell{2, 1});
        cells.push_back(Cell{2, 2});
        cells.push_back(Cell{2, 3});
        cells.push_back(Cell{2, 4});
        cells.push_back(Cell{2, 5});
        cells.push_back(Cell{2, 6});

        cells.push_back(Cell{3, 0});
        cells.push_back(Cell{3, 1});
        cells.push_back(Cell{3, 3});
        cells.push_back(Cell{3, 4});
        cells.push_back(Cell{3, 6});
        cells.push_back(Cell{3, 7});

        cells.push_back(Cell{4, 0});
        cells.push_back(Cell{4, 1});
        cells.push_back(Cell{4, 2});
        cells.push_back(Cell{4, 3});
        cells.push_back(Cell{4, 4});
        cells.push_back(Cell{4, 5});
        cells.push_back(Cell{4, 6});
        cells.push_back(Cell{4, 7});

        cells.push_back(Cell{5, 2});
        cells.push_back(Cell{5, 5});

        cells.push_back(Cell{6, 1});
        cells.push_back(Cell{6, 3});
        cells.push_back(Cell{6, 4});
        cells.push_back(Cell{6, 6});

        cells.push_back(Cell{7, 0});
        cells.push_back(Cell{7, 2});
        cells.push_back(Cell{7, 5});
        cells.push_back(Cell{7, 7});
    }
};

class Alien4 : public AlienPixel {
public:
    Alien4() {
        cells.push_back(Cell{0, 5});
        cells.push_back(Cell{0, 6});
        cells.push_back(Cell{0, 7});
        cells.push_back(Cell{0, 8});
        cells.push_back(Cell{0, 9});
        cells.push_back(Cell{0, 10});

        cells.push_back(Cell{1, 3});
        cells.push_back(Cell{1, 4});
        cells.push_back(Cell{1, 5});
        cells.push_back(Cell{1, 6});
        cells.push_back(Cell{1, 7});
        cells.push_back(Cell{1, 8});
        cells.push_back(Cell{1, 9});
        cells.push_back(Cell{1, 10});
        cells.push_back(Cell{1, 11});
        cells.push_back(Cell{1, 12});
        
        cells.push_back(Cell{2, 2});
        cells.push_back(Cell{2, 3});
        cells.push_back(Cell{2, 4});
        cells.push_back(Cell{2, 5});
        cells.push_back(Cell{2, 6});
        cells.push_back(Cell{2, 7});
        cells.push_back(Cell{2, 8});
        cells.push_back(Cell{2, 9});
        cells.push_back(Cell{2, 10});
        cells.push_back(Cell{2, 11});
        cells.push_back(Cell{2, 12});
        cells.push_back(Cell{2, 13});

        cells.push_back(Cell{3, 1});
        cells.push_back(Cell{3, 2});
        cells.push_back(Cell{3, 4});
        cells.push_back(Cell{3, 5});
        cells.push_back(Cell{3, 7});
        cells.push_back(Cell{3, 8});
        cells.push_back(Cell{3, 10});
        cells.push_back(Cell{3, 11});
        cells.push_back(Cell{3, 13});
        cells.push_back(Cell{3, 14});

        cells.push_back(Cell{4, 0});
        cells.push_back(Cell{4, 1});
        cells.push_back(Cell{4, 2});
        cells.push_back(Cell{4, 3});
        cells.push_back(Cell{4, 4});
        cells.push_back(Cell{4, 5});
        cells.push_back(Cell{4, 6});
        cells.push_back(Cell{4, 7});
        cells.push_back(Cell{4, 8});
        cells.push_back(Cell{4, 9});
        cells.push_back(Cell{4, 10});
        cells.push_back(Cell{4, 11});
        cells.push_back(Cell{4, 12});
        cells.push_back(Cell{4, 13});
        cells.push_back(Cell{4, 14});
        cells.push_back(Cell{4, 15});

        cells.push_back(Cell{5, 2});
        cells.push_back(Cell{5, 3});
        cells.push_back(Cell{5, 4});
        cells.push_back(Cell{5, 7});
        cells.push_back(Cell{5, 8});
        cells.push_back(Cell{5, 11});
        cells.push_back(Cell{5, 12});
        cells.push_back(Cell{5, 13});

        cells.push_back(Cell{6, 3});
        cells.push_back(Cell{6, 12});
    }
};