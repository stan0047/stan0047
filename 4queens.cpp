// 4 Queens problem solving using BFS Algorithm in C++
#include <iostream>
#include <queue>
using namespace std;

// Structure to represent a state in the problem
struct State {
    int board[4][4];

    State() {
        // Initialize the board with all cells set to 0 (empty)
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                board[i][j] = 0;
            }
        }
    }
};

// Check if a state is a valid state
bool isValidState(State state) {
    // Check if no two queens are attacking each other

    // Check rows and columns
    for (int i = 0; i < 4; ++i) {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < 4; ++j) {
            rowSum += state.board[i][j];
            colSum += state.board[j][i];
        }
        if (rowSum > 1 || colSum > 1) {
            return false;
        }
    }

    // Check diagonals
    for (int i = 0; i < 4; ++i) {
        int sum1 = 0;
        int sum2 = 0;
        for (int j = 0; j < 4; ++j) {
            if (i + j < 4) {
                sum1 += state.board[j][i + j];
                sum2 += state.board[j][3 - i - j];
            }
        }
        if (sum1 > 1 || sum2 > 1) {
            return false;
        }
    }

    return true;
}

// Check if a state is the goal state
bool isGoalState(State state) {
    // Count the number of queens on the board
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (state.board[i][j] == 1) {
                count++;
            }
        }
    }
    // The goal state is when there are 4 queens on the board
    return count == 4;
}

// Generate next possible valid states from the current state
queue<State> generateNextStates(State currentState) {
    queue<State> nextStates;

    // Find the next row to place a queen
    int nextRow = -1;
    for (int i = 0; i < 4; ++i) {
        bool rowHasQueen = false;
        for (int j = 0; j < 4; ++j) {
            if (currentState.board[i][j] == 1) {
                rowHasQueen = true;
                break;
            }
        }
        if (!rowHasQueen) {
            nextRow = i;
            break;
        }
    }

    // Place a queen in the next row in all possible columns
    if (nextRow != -1) {
        for (int j = 0; j < 4; ++j) {
            State nextState = currentState;
            nextState.board[nextRow][j] = 1;
            if (isValidState(nextState)) {
                nextStates.push(nextState);
            }
        }
    }

    return nextStates;
}

// Perform BFS to find the solution and display the states expanded level by level
bool bfs() {
    queue<State> stateQueue; 
	int level=0; // To track the levels in the BFS Tree
    State initialState;
    stateQueue.push(initialState);

    while (!stateQueue.empty()) {
    	
    	cout << "Level:  " << level << "\t"<< "In the format of 4 x 4 Grid" <<"\n";
		int levelSize = stateQueue.size();
        for (int i = 0; i < levelSize ; i++) {
		    State current = stateQueue.front();
            stateQueue.pop();
            // Display the state
            for (int i = 0; i < 4; ++i) {
           	 for (int j = 0; j < 4; ++j) {
                cout << current.board[i][j] << " ";
           	 }
            	cout << endl;
       		}
        	cout << endl; 
            cout << "--------------\n";
            // Check if the current state is the goal state
            if (isGoalState(current)) {
                cout << "Goal state reached!\n";
                return true;
            }
            queue<State> nextStates = generateNextStates(current);
        	while (!nextStates.empty()) {
            	State nextState = nextStates.front();
            	nextStates.pop();
            	if (isValidState(nextState))
                	stateQueue.push(nextState);
        	} 
        }
        cout << "***************************************\n";
        level++;
    	
    }

    cout << "No solution found." << endl;
    return false;
}

int main() {
    if (bfs()) {
        cout << "Solution exists!" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}

