#include<iostream>
#include<string>
#include<vector>
#include"fns.C"
using namespace std;
int a[8][8];
int w[8][8];
int main()
{
	int select_player;
	int level=0;
	message("return 1 for two player mode and 2 for playing with computer");
	message("if computer mode then u will be getting first chance");
	cin>>select_player;
	// assigning weights to the board
	initialise_weight(w);
	// assigning initial configuration to the board
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if((i==3 && j==3) || (i==4 && j==4))
				a[i][j]=1;
			else if((i==3 && j==4) || (i==4 && j==3))
				a[i][j]=-1;
			else
				a[i][j]=0;
		}
	}
	message("intial configuration of the board is as follows:");
	display(a);
	message("keep in mind that positions are started from 0 and input the cell in the format x y");
	// let's start the game
	if(select_player == 1)
		two_player_mode(a);
	else if(select_player == 2){
		message("return 1 for basic level 2 for intermediate level and 3 for high level");
		cin>>level;
		while(!(level>=1 && level<=3)){
			message("enter valid level");
			cin>>level;
		}
		computer_player_mode(a,w,level);
	}
	int count1=0,count2=0;
	counter(a,count1,count2);
	if(count1>count2){
		message("Player 1 has won the match with a score of ",to_string(count1-count2));
	}
	else if(count1<count2){
		if(select_player == 1)
			message("Player 2 has won the match with a score of ",to_string(count2-count1));
		else
			message("Computer has won the match with a score of ",to_string(count2-count1));
	}
	else
		message("match has been a tie");
	return 0;
}