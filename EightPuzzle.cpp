#include "EightPuzzle.h"
#define LIMIT 100 

State::State(){
	for(int i=0;i<9;i++)
		board[i]=0;
	numOfSons=0;
	cost=exCost=0;
	father=NULL;
	son=NULL;
}
State::State(State *s,int ch){
	for(int i=0;i<9;i++)
		board[i]=0;
	numOfSons=0;
	cost=exCost=0;
	father=NULL;
	son=NULL;
	if(s!=NULL){
		for(int i=0;i<9;i++)
			board[i]=s->board[i];
		this->findCost(ch);
	}
}
State::State(int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int ch){
	numOfSons=0;
	board[0]=p0;
	board[1]=p1;
	board[2]=p2;
	board[3]=p3;
	board[4]=p4;
	board[5]=p5;
	board[6]=p6;
	board[7]=p7;
	board[8]=p8;
	exCost=0;
	cost=0;
	father=NULL;
	son=NULL;
	this->findCost(ch);
}
State::~State(){
	father=NULL;
	if(son!=NULL)
		delete []son;
}
int State::h1(){
	int sumOfTaxicab=0;
	for(int i=0;i<9;i++){
		if(board[i]!=0){
			int p1=i/3;
			int p2=i%3;
			int q1=board[i]/3;
			int q2=board[i]%3;
			sumOfTaxicab += abs(p1-q1)+abs(p2-q2);
		}
	}
	return sumOfTaxicab;
}
int State::h2(){
	int numOfMisplacedTiles=0;
	for(int i=0;i<9;i++)
		if(board[i]!=i&&board[i]!=0)
			numOfMisplacedTiles++;
	return numOfMisplacedTiles;
}
void State::setFather(State *s){
	father=s;
}
int State::getNumOfSons(){
	return numOfSons;
}
State *State::getSon(int index){
	if(index>=0&&index<numOfSons)
		return &son[index];
	return NULL;
}
State *State::getFather(){
	return father;
}
int State::getCost(){
	return cost;
}
int State::getExCost(){
	return exCost;
}
void State::swapValue(int i,int j){
	if((i>=0&&i<9)&&(j>=0&&j<9)){
		int temp=board[i];
		board[i]=board[j];
		board[j]=temp;
	}
}
void State::copy(State *s){
	for(int i=0;i<9;i++)
		board[i]=s->board[i];
}
void State::expand(int ch){
	int index=0;
	int fidx=-1;
	for(int i=0;i<9;i++)
		if(board[i]==0)
			index=i;
	State *f=father;
	if(f!=NULL){
		for(int i=0;i<9;i++)
			if(f->board[i]==0)
				fidx=i;
	}
	int *con=NULL;
	if(index==0){
		numOfSons=2;
		con=new int[numOfSons];
		con[0]=1;con[1]=3;
	}
	else if(index==1){
		numOfSons=3;
		con=new int[numOfSons];
		con[0]=0;con[1]=2;con[2]=4;
	
	}
	else if(index==2){
		numOfSons=2;
		con=new int[numOfSons];
		con[0]=1;con[1]=5;
	}
	else if(index==3){
		numOfSons=3;
		con=new int[numOfSons];
		con[0]=0;con[1]=4;con[2]=6;	
	}
	else if(index==4){
		numOfSons=4;
		con=new int[numOfSons];
		con[0]=1;con[1]=3;con[2]=5;con[3]=7;
	}
	else if(index==5){
		numOfSons=3;
		con=new int[numOfSons];
		con[0]=2;con[1]=4;con[2]=8;
	}
	else if(index==6){
		numOfSons=2;
		con=new int[numOfSons];
		con[0]=3;con[1]=7;
	}
	else if(index==7){
		numOfSons=3;
		con=new int[numOfSons];
		con[0]=4;con[1]=6;con[2]=8;
	}
	else if(index==8){
		numOfSons=2;
		con=new int[numOfSons];
		con[0]=5;con[1]=7;
	}
	if(fidx!=-1){
		numOfSons--;
		for(int i=0;i<numOfSons;i++)
			if(con[i]==fidx)
				con[i]=con[numOfSons];
	}
	son=new State[numOfSons];
	for(int i=0;i<numOfSons;i++){
		son[i].setFather(this);
		son[i].copy(this);
		son[i].swapValue(index,con[i]);
		son[i].findCost(ch);
	}
}
bool State::isGoal(){
	for(int i=0;i<9;i++)
		if(board[i]!=i)
			return false;
	return true;
}
void State::findCost(int ch){
	if(father!=NULL)
		exCost=father->getExCost()+1;
	if(ch<=1)
		cost=h1()+exCost;
	else
		cost=h2()+exCost;
}
bool State::isLike(State *s){
	for(int i=0;i<9;i++)
		if(board[i]!=s->board[i])
			return false;
	return true;
}

Node::Node(){
	next=NULL;
	data=NULL;
}
Node::~Node(){
	next=NULL;
	data=NULL;
}

Queue::Queue(){
	head=NULL;
	tail=NULL;
}
Queue::~Queue(){
	head=NULL;
	tail=NULL;
}
void Queue::order(){
	Node *temp1=head;
	Node *temp2=NULL;
	while(temp1!=NULL){
		temp2=temp1->next;
		while(temp2!=NULL){
			if(!temp1->data->isLike(temp2->data)){
				if(temp1->data->getCost()>temp2->data->getCost()){
					Node *t1=head;
					Node *t2=head;
					while(t1->next!=temp1){
						t1=t1->next;
						if(t1==NULL)
							break;
					}
					while(t2->next!=temp2)
						t2=t2->next;
					Node *t=NULL;
					if(temp1==head)
						head=temp2;
					else
						t1->next=temp2;
					if(temp2==tail)
						tail=temp1;
					t=temp2->next;
					if(temp1->next==temp2)
						temp2->next=temp1;
					else
						temp2->next=temp1->next;
					temp1->next=t;
					if(t2!=temp1)
						t2->next=temp1;
					t=temp1;
					temp1=temp2;
					temp2=t;
					t1=t2=t=NULL;
					delete t1,t2,t;
				}
			}
			else{
				Node *t=NULL;
				if(temp1->data->getCost()<=temp2->data->getCost())
					t=temp2;
				else
					t=temp1;
				Node *t2=head;
				while(t2->next!=t){
					t2=t2->next;
					if(t2==NULL)
						break;
				}
				if(t==head){
					cout<<"error\n";
					head=head->next;
					t->next=NULL;
				}
				else if(t==tail){
					tail=t2;
					t2->next=NULL;
				}
				else{
					t2->next=t->next;
					temp2=t2;
					t->next=NULL;
				}
				t=t2=NULL;
				delete t,t2;
			}
			temp2=temp2->next;
		}
		temp2=NULL;
		temp1=temp1->next;
	}
	temp1=NULL;
}
bool Queue::isEmpty(){
	if(head==NULL)
		return true;
	return false;
}
bool Queue::isInQueue(State *s){
	Node *temp=head;
	while(temp!=NULL){
		if(temp->data->isLike(s))
			return true;
		temp=temp->next;
	}
	return false;
}
void Queue::push(State *s){
	Node *n=new Node();
	n->data=s;
	if(isEmpty())
		head=tail=n;
	else{
		tail->next=n;
		tail=n;
	}
	this->order();
}
State* Queue::pop(){
	Node *temp=head;
	head=head->next;
	return temp->data;
}

AStar::AStar(){
	queue=NULL;
	path=NULL;
	result=NULL;
	step=space=expanded=0;
	found=false;
}
AStar::AStar(State *start,int ch){
	found=false;
	queue=new Queue();
	Queue *closed=new Queue();
	path=NULL;
	step=0;
	space=expanded=1;
	queue->push(start);
	State *node=NULL;
	State *goal=new State(0,1,2,3,4,5,6,7,8,ch);
	result=NULL;
	int loop=0;
	while((!queue->isEmpty())&&(loop<=LIMIT)){
		node=queue->pop();
		closed->push(node);
		if(node->isLike(goal)){
			found=true;
			result=node;
			step=result->getExCost()+1;
			path=new State*[step];
			for(int i=0;i<step;i++)
				path[i]=NULL;
			for(int i=step-1;i>=0;i--){
				if(node==NULL)
					break;
				path[i]=node;
				node=node->getFather();	
			}
			break;
		}
		else{
			node->expand(ch);
			expanded++;
			for(int i=0;i<node->getNumOfSons();i++){
				space++;
				if(!closed->isInQueue(node->getSon(i)))
					queue->push(node->getSon(i));
			}
			queue->order();
		}
		loop++;
	}
	if(!found){
		int c=0;
		State *temp=NULL;
		closed->pop();
		result=closed->pop();
		c=result->getCost();
		while(!closed->isEmpty()){
			temp=closed->pop();
			if(temp->getCost()-temp->getExCost()<c){
				c=temp->getCost()-temp->getExCost();
				result=temp;
			}
		}
	}
	delete goal;
	delete closed;
}
AStar::~AStar(){
	delete queue;
	if(path!=NULL)
		delete []path;
}
State **AStar::getPath(){
	return path;
}
State *AStar::getResult(){
	return result;
}
bool AStar::wasFound(){
	return found;
}