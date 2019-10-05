#pragma GCC optimize "Ofast,unroll-loops,omit-frame-pointer,inline"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <queue>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <chrono>
using namespace std;

#define LOGS_INPUT true

#define INF 1000000000
#define INF2 2000000000
const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 15;

//TODO: Replace rand with https://e...content-available-to-author-only...e.com/w/cpp/numeric/random/uniform_int_distribution

static int turn = 0;


#define Now() chrono::high_resolution_clock::now()

static struct Stopwatch {
	chrono::high_resolution_clock::time_point c_time, c_timeout;

	void setTimeout(int us) { c_timeout = c_time + chrono::microseconds(us); }

	void Start(int timeOutMilliSeconds) { c_time = Now(); setTimeout(timeOutMilliSeconds * 1000); }

	inline bool Timeout() { return Now() > c_timeout; }

	long long EllapsedMilliseconds() { return chrono::duration_cast<chrono::milliseconds>(Now() - c_time).count(); }
} stopwatch;


class Solution;
class Move;

class Point {
public:
	int x;
	int y;
	Point() {
		x = -1;
		y = -1;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Point(const Point &other) {
		this->x = other.x;
		this->y = other.y;
	}

	Point operator = (const Point &other) {
		x = other.x;
		y = other.y;
		return *(this);
	}

	Point operator + (Point &other) {
		return Point(x + other.x, y + other.y);
	}

	bool operator == (Point &other) {
		return x == other.x && y == other.y;
	}

	bool operator != (Point &other) {
		return !(*this == other);
	}

	int manhattan(Point &other) {
		return abs(x - other.x) + abs(y - other.y);
	}


	bool isValid() {
		return x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT;
	}
};

bool operator < (const Point &A, const Point &B) {
	if (A.x != B.x) {
		return A.x < B.x;
	}
	return A.y < B.y;
}

Point dir[5] = { Point(0,1), Point(1,0), Point(0,-1), Point(-1,0), Point(0,0) };

class Player {
public:
	

	Player() {
	}
};

class GameState {
public:

	Player players[2];
	int ores[BOARD_WIDTH][BOARD_HEIGHT];
	bool isHole[BOARD_WIDTH][BOARD_HEIGHT];

	GameState() {
	}

	void initialize();
	void startTurn();
	void cloneTo(GameState *gameState);
	void getBestMove(Solution &solution);

	void getRandomSolution(Solution &solution);

	void getScore(Solution &solution);
	void endTurn(Solution &solution);
};

void GameState::cloneTo(GameState *gameState) {
	for (int p = 0; p < 2; p++) {
		//gameState->players[p].headquarters = players[p].headquarters;
		
	}
	/*for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			gameState->board[i][j] = board[i][j];
		}
	}*/
}

void GameState::initialize() {
	stringstream input;
	int width, height;

	cin >> width >> height;
	input << width <<" "<< height << endl;
	
	if (LOGS_INPUT) {
		cerr << input.str();
	}
}


void GameState::startTurn() {
	stringstream input;


	if (LOGS_INPUT) {
		cerr << input.str();
	}
}


class Move {
public:

	string move;
	string item;
	Point pos;

	Move() {
		move = "";
		item = "";
		pos = Point(-1, -1);
	}

	Move(string m) {
		this->move = m;
	}

	Move(string m, string item) {
		this->move = m;
		this->item = item;
	}

	Move(string m, Point p) {
		this->move = m;
		this->pos = p;
	}
};

class Solution {
public:
	Move moves[5];
	int score;

	Solution() {
		score = -INF;
	}

	void cloneTo(Solution *newSolution) {
		newSolution->score = score;
		for (int i = 0; i < 5; i++) {
			newSolution->moves[i] = moves[i];
		}
	}
};


void GameState::getScore(Solution &solution) {
	solution.score = 0;
}


void GameState::getRandomSolution(Solution &randomSolution) {

	randomSolution.score = -INF;

	
}


GameState backup;
Solution tempSolution;


void GameState::getBestMove(Solution &bestSolution) {
	bestSolution.score = -INF;
	stopwatch.Start(45);
	int sims = 0;
	cloneTo(&backup);

	while (!stopwatch.Timeout()) {
		
		getRandomSolution(tempSolution);
	

		

		backup.cloneTo(this);
		sims++;
	}
	cerr << "sims " << sims << endl;
}


void GameState::endTurn(Solution &solution) {

	for (int i = 0; i < 5; i++) {
		if (solution.moves[i].move == "WAIT") {
			cout << solution.moves[i].move;
		}
		else if (solution.moves[i].move == "REQUEST") {
			cout << solution.moves[i].move<<" "<<solution.moves[i].item;
		}
		else {
			cout << solution.moves[i].move << " " << solution.moves[i].pos.x<<" "<<solution.moves[i].pos.y;
		}

		cout << endl;
	}

}



FILE *f1;
int main()
{
	//freopen_s(&f1, "input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	GameState state;
	state.initialize();
	Solution solution;

	while (1) {
		state.startTurn();
		state.getBestMove(solution);
		state.endTurn(solution);
		turn++;
	}
}

