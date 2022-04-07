
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class State {
public:
    int state[3][3];
    int nodeDepth;
    int Hvalue;
    State* parent;
    vector<State> child;
    State() {};

    void printState() {
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++)
                cout << state[k][i] << " ";
            cout << endl;
        }
    }
    void add_child(State kid) {
        child.push_back(kid);

    }

    State get_child() {
        // loop for testing to get children 
    /*
          for(State k: child){
            cout <<endl;
            k.printState();
          }
          */
        State k = child.back();
        child.pop_back();
        return k;
        //return child.back();
    };

    bool operator<(const State& r) const
    {
        if (Hvalue != r.Hvalue) {
            return Hvalue < r.Hvalue;
        }

        return Hvalue < r.Hvalue;
    }

    bool operator>(const State& r) const
    {
        if (Hvalue != r.Hvalue) {
            return Hvalue > r.Hvalue;
        }

        return Hvalue > r.Hvalue;
    }
};

//function to assign hvalue for number of displaced tiles
void hValueDisplaced(State& state, State goal) {
    int calcHvalue = 0;

    calcHvalue += state.nodeDepth;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.state[i][j] == 0) {
                continue;
            }
            if (state.state[i][j] != goal.state[i][j]) {
                calcHvalue++;
            }
        }
    }

    state.Hvalue = calcHvalue;
}


/////////
void generatekids(State* start) {

    /// find the 0 pos k + i
    int blankRow;
    int blankCol;
    for (int k = 0; k < 3; k++)
        for (int i = 0; i < 3; i++)
            if (start->state[k][i] == 0) {
                blankRow = k;
                blankCol = i;
            }
    //if +1 or -1 works swap 
    if (blankCol + 1 < 3) {
        //cout << "1";

        State child;// = new State();
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow][blankCol + 1];
        child.state[blankRow][blankCol + 1] = 0;
        start->add_child(child);
    }
    if (blankCol - 1 > -1) {
        State child; //= new State();
        //cout << "2";
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow][blankCol - 1];
        child.state[blankRow][blankCol - 1] = 0;
        start->add_child(child);
    }

    if (blankRow + 1 < 3) {
        State child;// = new State();
        //cout << "3";
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow + 1][blankCol];
        child.state[blankRow + 1][blankCol] = 0;
        start->add_child(child);


    }
    if (blankRow - 1 > -1) {
        State child;// = new State();
        //cout << "4";
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow - 1][blankCol];
        child.state[blankRow - 1][blankCol] = 0;
        start->add_child(child);

    }



    // start->add_child(child);
}

bool compareState(State state, State goal) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.state[i][j] != goal.state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool compareHValue(State i1, State i2) {
    return (i1.Hvalue > i2.Hvalue);
}

void propagateOld(State state) {
    if (state.child.size() == 0)
        return;
    for (State k : state.child) {
        k.nodeDepth = state.nodeDepth + 1;
        propagateOld(k);
    }
}

void removeChild(State parent, State child) {
    int i = 0;
    for (State k : parent.child) {
        if(compareState(child, k))
            parent.child.erase(parent.child.begin() + i);
    }
    cout << "unsuccessful remove\n";
}

void viewOPEN(vector<State> open) {
    cout << endl;
    for (State k : open) {
        cout << k.Hvalue << " ";
    }
    cout << endl;
}

void aStar(State initial, State goal) {
    vector<State> OPEN, CLOSED;
    State BESTNODE, SUCCESSOR, OLD;
    bool putOnOpen = true;

    hValueDisplaced(initial, goal);
    OPEN.push_back(initial);

    while (OPEN.size() != 0) {
        BESTNODE = OPEN.back();
        OPEN.pop_back();
        CLOSED.push_back(BESTNODE);
        if (compareState(BESTNODE, goal)) {
            //PRINT TABLE
            cout << "FOUND GOAL\n";
            cout << "DEPTH: " << BESTNODE.nodeDepth;
            return;
        }
        else {
            generatekids(&BESTNODE);
            for (State k : BESTNODE.child) {
                SUCCESSOR = k;
                hValueDisplaced(SUCCESSOR, goal);
                BESTNODE = SUCCESSOR;
                for (State m : OPEN) {
                    if (compareState(m, SUCCESSOR)) {
                        putOnOpen = false;
                        OLD = m;
                        //BESTNODE.child.erase(std::remove(BESTNODE.child.begin(), BESTNODE.child.end(), SUCCESSOR), BESTNODE.child.end());
                        //removeChild(BESTNODE, OLD);
                        BESTNODE.add_child(OLD);
                        if (OLD.nodeDepth > SUCCESSOR.nodeDepth) {
                            OLD.parent = &BESTNODE;
                            OLD.nodeDepth = BESTNODE.nodeDepth + 1;
                            hValueDisplaced(OLD, goal);
                            OPEN.push_back(SUCCESSOR);
                            sort(OPEN.begin(), OPEN.end(), greater<>());
                        }
                    }
                }

                for (State m : CLOSED) {
                    if (compareState(m, SUCCESSOR)) {
                        putOnOpen = false;
                        OLD = m;
                        BESTNODE.add_child(OLD);
                        if (OLD.nodeDepth > SUCCESSOR.nodeDepth) {
                            OLD.parent = &BESTNODE;
                            OLD.nodeDepth = BESTNODE.nodeDepth + 1;
                            hValueDisplaced(OLD, goal);
                            OPEN.push_back(SUCCESSOR);
                            sort(OPEN.begin(), OPEN.end(), greater<>());
                            propagateOld(OLD);
                        }
                    }
                }

                if (putOnOpen) {
                    BESTNODE = SUCCESSOR;
                    OPEN.push_back(BESTNODE);
                    sort(OPEN.begin(), OPEN.end(), greater<>());
                    viewOPEN(OPEN);
                    //BESTNODE.printState();
                    //cin.ignore();
                }
                putOnOpen = true;
            }
        }

    }

    cout << "FAILURE: no solution found\n";
    return;

}

int main() {
    State initial;
    State child;
    State root;
    State goal;
    initial.state[0][0] = 2;
    initial.state[0][1] = 1;
    initial.state[0][2] = 6;
    initial.state[1][0] = 4;
    initial.state[1][1] = 0;
    initial.state[1][2] = 8;
    initial.state[2][0] = 7;
    initial.state[2][1] = 5;
    initial.state[2][2] = 3;
    initial.nodeDepth = 0;
    initial.printState();

    goal.state[0][0] = 1;
    goal.state[0][1] = 2;
    goal.state[0][2] = 3;
    goal.state[1][0] = 8;
    goal.state[1][1] = 0;
    goal.state[1][2] = 4;
    goal.state[2][0] = 7;
    goal.state[2][1] = 6;
    goal.state[2][2] = 5;

    aStar(initial, goal);

}
