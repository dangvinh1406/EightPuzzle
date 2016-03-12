/* 
	Vinh Dang
	Trong Chuong Hoang
	Bao Tran Thieu 
*/
#include <conio.h>
#include <math.h>
#include <iostream>
using namespace std;

class State{
private:
	int board[9];
	int numOfSons;
	int cost;
	int exCost;
	State *son;
	State *father;
private:
	void setFather(State *);
	int h1();//city block distance (Manhattan distance or taxicab geometry)
	int h2();//number of misplace tiles ( 0 is not a tile )
	void findCost(int );
public:
	State();
	State(State *,int );
	State(int ,int ,int ,int ,int ,int ,int ,int ,int ,int );
	~State();
	State *getFather();
	int getNumOfSons();
	int getCost();
	int getExCost();
	State *getSon(int );
	void copy(State *);
	void swapValue(int ,int );
	void expand(int );
	bool isGoal();
	bool isLike(State *);

	void display(){
		cout<<"   -----------"<<endl;
		cout<<"   |"<<board[0]<<"   "<<board[1]<<"   "<<board[2]<<'|'<<endl;
		cout<<"   |"<<board[3]<<"   "<<board[4]<<"   "<<board[5]<<'|'<<endl;
		cout<<"   |"<<board[6]<<"   "<<board[7]<<"   "<<board[8]<<'|'<<endl;
		cout<<"   -----------"<<endl<<endl;
	}
};

class Node{
public:
	State *data;
	Node *next;
	Node();
	~Node();
};

class Queue{
private:
	Node *head;
	Node *tail;
public:
	Queue();
	~Queue();
	void order();
	bool isEmpty();
	bool isInQueue(State *);
	void push(State *);
	State* pop();
};

class AStar{
private:
	Queue *queue;
	State **path;
	State *result;
	int step;
	int space;
	int expanded;
	bool found;
public:
	AStar();
	AStar(State *,int );
	~AStar();
	State **getPath();
	State *getResult();
	bool wasFound();

	void display(){
		cout<<"Space: "<<space<<"   Expanded: "<<expanded<<endl;
		if(found){
			cout<<"Steps:\n";
			for(int i=0;i<step;i++)
				path[i]->display();
		}
		else{
			cout<<"Could not find solution.\n";
			cout<<"Best result tile:\n";
			result->display();
		}
	};
};