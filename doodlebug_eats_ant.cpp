/*
The goal for this Project is to create a simple two-dimensional predator-prey simulation. In this simulation the prey are ants and the pred-ators are doodlebugs. These critters live in a world composed of a 20 × 20 grid of cells. Only one critter may occupy a cell at a time. The grid is  enclosed, so a critter is not allowed to move off the edges of the world. Time is simulated in time steps. Each critter performs some action every time step.


The ants behave according to the following model:
Move. Every time step, randomly try to move up, down, left, or right. If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.

Breed. If an ant survives for three time steps, then at the end of the time step (that is; after moving) the ant will breed. This is simulated by creat-ing a new ant in an adjacent (up, down, left, or right) cell that is empty. If there is no empty cell available, then no breeding occurs. Once an off-spring is produced, an ant cannot produce an offspring until three more time steps have elapsed.


The doodlebugs behave according to the following model:
Move. Every time step, if there is an adjacent ant (up, down, left, or right), then the doodlebug will move to that cell and eat the ant. Otherwise, the doodlebug moves according to the same rules as the ant. Note that a doodlebug cannot eat other doodlebugs.

Breed. If a doodlebug survives for eight time steps, then at the end of the time step it will spawn off a new doodlebug in the same manner as the ant.

Starve. If a doodlebug has not eaten an ant within the last three time steps, then at the end of the third time step it will starve and die. The doodlebug should then be removed from the grid of cells.

During one turn, all the doodlebugs should move before the ants do.

Write a program to implement this simulation and draw the world using ASCII characters of “o” for an ant and “X” for a doodlebug or "-" for an empty space. Create a class named Organism that encapsulates basic data common to both ants and doodlebugs. This class should have a virtual function named move that is defined in the derived classes of Ant and Doodlebug. You may need additional data structures to keep track of which critters have moved.

Initialize the world with 5 doodlebugs and 100 ants. After each time step, prompt the user to press Enter to move to the next time step. You should see a cyclical pattern between the population of predators and prey, although random perturbations may lead to the elimination of one or both species.
 */


#include <iostream>

#include <vector>
using namespace std;

class Organism {
public:
    Organism();
    ~Organism();
    Organism(int xx, int yy);
    virtual void Move(int dir, vector<vector<char>>& map) = 0;
    virtual int Breed(vector<vector<char>>& map) = 0;
    int x, y, round;

protected:
    const int direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
};

class Bug: public Organism {
public:
    Bug();
    Bug(int xx, int yy);
    ~Bug();
    Bug& operator=(const Bug& a);
    void Move(int dir, vector<vector<char>>& map);
    bool Starve();
    void EatAnt();
    int Breed(vector<vector<char>>& map);
    void Next();
private:
    int starveRound;
};

class Ant : public Organism {
public:
    Ant();
    Ant(int xx, int yy);
    ~Ant();
    Ant& operator=(const Ant& a);
    void Move(int dir, vector<vector<char>>& map);
    int Breed(vector<vector<char>>& map);
    void Next();
};


class Game {
public:
    Game();
    void Next();
    void Print();

private:
    void shuffle();
    int findAntIndex(int x, int y);
    int findBugIndex(int x, int y);
    bool bugFindAnt(int i);
    int bugTryMove(int i);
    int antTryMove(int i);
    void bugsBreed();
    void antsBreed();
    const int MAXSIZE = 20;
    int round;
    vector<Ant> ants;
    vector<Bug> bugs;
    const int direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<int> randDirArr();
    vector<vector<char>> map;
};





int main() {
    Game game;
    game.Print();
    while (cin.ignore()) {
        game.Next();
        game.Print();
    }
    return 0;
}







Organism::Organism() {
    x = -1;
    y = -1;
}

Organism::~Organism() {
}

Organism::Organism(int xx, int yy) {
    x = xx;
    y = yy;
    round = 0;
}
Bug::Bug() : Organism() {
    starveRound = 0;
}

Bug::Bug(int xx, int yy) : Organism(xx, yy) {
    starveRound = 0;
}

Bug::~Bug() {

}

Bug& Bug::operator=(const Bug& a) {
    x = a.x;
    y = a.y;
    round = a.round;
    starveRound = a.starveRound;
    return *this;
}

void Bug::Move(int dir, vector<vector<char>>& map) {
    map[x][y] = '-';
    x += direction[dir][0];
    y += direction[dir][1];
    map[x][y] = 'X';
    starveRound++;
}

void Bug::EatAnt() {
    starveRound = 0;
}

bool Bug::Starve() {
    return starveRound >= 3;
}

void Bug::Next() {
    round++;
}

int Bug::Breed(vector<vector<char>>& map) {
    if (round >= 8) {
        for (int i = 0; i < 4; i++) {
            int newx = x + direction[i][0], newy = y + direction[i][1];
            if (newx >= 0 && newx < 20 && newy >= 0 && newy < 20 && map[newx][newy] == '-') {
                map[newx][newy] = 'X';
                round = 0;
                return i;
            }
        }
    }
    return -1;
}
Ant::Ant() : Organism() {
}

Ant::Ant(int xx, int yy) : Organism(xx, yy) {
}

Ant::~Ant() {

}

Ant& Ant::operator=(const Ant& a) {
    x = a.x;
    y = a.y;
    round = a.round;
    return *this;
}

void Ant::Next() {
    round++;
}

void Ant::Move(int dir, vector<vector<char>>& map) {
    map[x][y] = '-';
    x += direction[dir][0];
    y += direction[dir][1];
    map[x][y] = 'o';
}

int Ant::Breed(vector<vector<char>>& map) {
    if (round >= 3) {
        for (int i = 0; i < 4; i++) {
            int newx = x + direction[i][0], newy = y + direction[i][1];
            if (newx >= 0 && newx < 20 && newy >= 0 && newy < 20 && map[newx][newy] == '-') {
                round = 0;
                map[newx][newy] = 'o';
                return i;
            }
        }
    }
    return -1;
}

Game::Game() : round(0) {
    for (int i = 0; i < 100; i++)
        ants.push_back(Ant(i / MAXSIZE, i % MAXSIZE));
    for (int i = 0; i < 5; i++)
        bugs.push_back(Bug(MAXSIZE - 1, MAXSIZE - i - 1));
    shuffle();
    for (int x = 0; x < MAXSIZE; x++) {
        vector<char> mapRow;
        for (int y = 0; y < MAXSIZE; y++) {
            if (findAntIndex(x, y) != -1)
                mapRow.push_back('o');
            else if (findBugIndex(x, y) != -1)
                mapRow.push_back('X');
            else
                mapRow.push_back('-');
        }
        map.push_back(mapRow);
    }
}

void Game::shuffle() {
    srand(time(NULL));
    int x1, x2, y1, y2, indexa1, indexa2, indexb1, indexb2;
    for (int i = 0; i < 10000; i++) {
        x1 = rand() % 20;
        x2 = rand() % 20;
        y1 = rand() % 20;
        y2 = rand() % 20;
        indexa1 = findAntIndex(x1, y1);
        indexb1 = findBugIndex(x1, y1);
        indexa2 = findAntIndex(x2, y2);
        indexb2 = findBugIndex(x2, y2);
        if (indexa1 != -1) {
            ants[indexa1].x = x2;
            ants[indexa1].y = y2;
        }
        if (indexb1 != -1) {
            bugs[indexb1].x = x2;
            bugs[indexb1].y = y2;
        }
        if (indexa2 != -1) {
            ants[indexa2].x = x1;
            ants[indexa2].y = y1;
        }
        if (indexb2 != -1) {
            bugs[indexb2].x = x1;
            bugs[indexb2].y = y1;
        }
    }
}

bool Game::bugFindAnt(int i) {
    for (int diri = 0; diri < 4; diri++) {
        int newx = bugs[i].x + direction[diri][0], newy = bugs[i].y + direction[diri][1];
        if (newx >= 0 && newx < MAXSIZE && newy >= 0 && newy < MAXSIZE) {
            int antind = findAntIndex(newx, newy);
            if (antind != -1) {
                ants.erase(ants.begin() + antind);
                bugs[i].Move(diri, map);
                bugs[i].EatAnt();
                return true;
            }
        }
    }
    return false;
}

vector<int> Game::randDirArr() {
    vector<int> arr;
    for (int i = 0; i < 4; i++)
        arr.push_back(i);
    for (int i = 0; i < 10; i++) {
        int i1 = rand() % 4, i2 = rand() % 4;
        int tmp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = tmp;
    }
    return arr;
}

int Game::bugTryMove(int i) {
    vector<int> randarr = randDirArr();
    for (int diri = 0; diri < 4; diri++) {
        int newx = bugs[i].x + direction[randarr[diri]][0], newy = bugs[i].y + direction[randarr[diri]][1];
        if (newx >= 0 && newx < MAXSIZE && newy >= 0 && newy < MAXSIZE && map[newx][newy] == '-')
            return randarr[diri];
    }
    return -1;
}

int Game::antTryMove(int i) {
    vector<int> randarr = randDirArr();
    for (int diri = 0; diri < 4; diri++) {
        int newx = ants[i].x + direction[randarr[diri]][0], newy = ants[i].y + direction[randarr[diri]][1];
        if (newx >= 0 && newx < MAXSIZE && newy >= 0 && newy < MAXSIZE && map[newx][newy] == '-')
            return randarr[diri];
    }
    return -1;
}

void Game::bugsBreed() {
    int numOfBugs = bugs.size(), i = 0;
    while (i < numOfBugs) {
        int breeddir = bugs[i].Breed(map);
        if (breeddir >= 0) {
            Bug newBug(bugs[i].x + direction[breeddir][0], bugs[i].y + direction[breeddir][1]);
//            cout << "bug[" << i << "].Breed to " << newBug.x << " " << newBug.y << endl;
            bugs.push_back(newBug);
        }
        i++;
    }
}

void Game::antsBreed() {
    int numOfAnts = ants.size(), i = 0;
    while (i < numOfAnts) {
        int breeddir = ants[i].Breed(map);
        if (breeddir >= 0) {
            Ant newAnt(ants[i].x + direction[breeddir][0], ants[i].y + direction[breeddir][1]);
//            cout << "ant[" << i << "].Breed to " << newAnt.x << " " << newAnt.y << endl;
            ants.push_back(newAnt);
        }
        i++;
    }
}
void Game::Next() {
    for (int i = 0; i < bugs.size(); i++) {
        if (!bugFindAnt(i)) {
            int movedir = bugTryMove(i);
            if (movedir >= 0)
                bugs[i].Move(movedir, map);
        }
    }
    int i = 0;
    while (i < bugs.size()) {
        if (bugs[i].Starve()) {
            map[bugs[i].x][bugs[i].y] = '-';
            bugs.erase(bugs.begin() + i);
        } else
            i++;
    }
    bugsBreed();

    for (int i = 0; i < ants.size(); i++) {
        int movedir = antTryMove(i);
        if (movedir >= 0)
            ants[i].Move(movedir, map);
    }

    antsBreed();
    for (int i = 0; i < ants.size(); i++)
        ants[i].Next();
    for (int i = 0; i < bugs.size(); i++)
        bugs[i].Next();
    round++;
}

int Game::findAntIndex(int x, int y) {
    for (int i = 0; i < ants.size(); i++)
        if (ants[i].x == x && ants[i].y == y)
            return i;
    return -1;
}

int Game::findBugIndex(int x, int y) {
    for (int i = 0; i < bugs.size(); i++)
        if (bugs[i].x == x && bugs[i].y == y)
            return i;
    return -1;
}

void Game::Print() {
//    cout << "Num of Bugs:" << bugs.size() << endl;
//    cout << "Num of Ants:" << ants.size() << endl;
    for (int i = 0; i < MAXSIZE; i++) {
        for (int j = 0; j < MAXSIZE; j++)
            cout << map[i][j] << ' ';
        cout << endl;
    }
    cout << "--------------------\t" << "round:" << round << "\t--------------------";
}