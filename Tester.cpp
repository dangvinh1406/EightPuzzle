#include "EightPuzzle.h"
#include <conio.h>
#include <iostream>
using namespace std;

void main(){
	int a[9]={0,0,0,0,0,0,0,0,0};
	FILE *infile=NULL;
	infile=fopen("input.txt","r");
	if(infile!=NULL){
		fscanf_s(infile,"%d%d%d%d%d%d%d%d%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8]);
		cout<<"=========================================\n";
		cout<<"A* Algorithm uses h1() heuristic function\n";
		State *start1=new State(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],1);		
		AStar *puzzle1=new AStar(start1,1);
		puzzle1->display();
		cout<<"=========================================\n";
		cout<<"A* Algorithm uses h2() heuristic function\n";
		State *start2=new State(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],2);
		AStar *puzzle2=new AStar(start2,2);
		puzzle2->display();
		cout<<"=========================================\n";
		delete start1;
		delete start2;
		delete puzzle1;
		delete puzzle2;
	}
	else 
		cout<<"Could not open input file.\n";
	getch();
}