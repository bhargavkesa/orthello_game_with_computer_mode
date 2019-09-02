#include<iostream>
#include<vector>
using namespace std;
void copy(int (&arr)[8][8],int (&a)[8][8]);
int coins_turned(int (&a)[8][8],int &x,int &y);
int weight_changed(int (&a)[8][8],int (&w)[8][8],int &x,int &y,int player_code);
void two_player_mode(int (&a)[8][8]);
void computer_move(int (&a)[8][8],int (&w)[8][8],int &x,int &y,int level,int count);
void computer_player_mode(int (&a)[8][8],int (&w)[8][8],int level);
void first_level(int (&a)[8][8],int &x,int &y);
void second_level(int (&a)[8][8],int (&w)[8][8],int &x,int &y);
void third_level(int (&a)[8][8],int (&w)[8][8],int &x,int &y,int x1,int y1,int player_code,int depth,int count,int &value,int &max);
void initialise_weight(int (&w)[8][8]);
void display(int a[8][8]);
void message(string s);
void message(string s,string val);
void message(string s,string x,string y);
vector<int> check_right(int a[8][8],int player_code,int x,int y);
vector<int> check_left(int a[8][8],int player_code,int x,int y);
vector<int> check_top(int a[8][8],int player_code,int x,int y);
vector<int> check_down(int a[8][8],int player_code,int x,int y);
vector<int> check_right_top(int a[8][8],int player_code,int x,int y);
vector<int> check_right_down(int a[8][8],int player_code,int x,int y);
vector<int> check_left_top(int a[8][8],int player_code,int x,int y);
vector<int> check_left_down(int a[8][8],int player_code,int x,int y);
vector<int> calculate_possible_moves(int a[8][8],int player_code);
void print_valid_moves(int a[8][8],int player_code);
bool check_valid_move(int a[8][8],int player_code,int x,int y);
void place_move(int (&a)[8][8],int player_code,int x,int y);

void copy(int (&arr)[8][8],int (&a)[8][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			arr[i][j]=a[i][j];
		}
	}
}

void counter(int a[8][8],int &count1,int &count2);void read_input(int &x,int &y){
	string str1="",str2=""; // used for taking input to avoid invalid characters while placing a move
	while(!(str1.length()==1 && str2.length()==1 && str1[0]-'0'>=0 && str1[0]-'0'<=7 && str2[0]-'0'>=0 && str2[0]-'0'<=7)){
		message("enter valid position or characters");
		cin>>str1>>str2;
	}
	x=str1[0]-'0';
	y=str2[0]-'0';
}
void two_player_mode(int (&a)[8][8]){
	int x,y;
	int count=4;
	int game_incompletion=0;
	vector<int> game_check;
	while(count<64 && game_incompletion < 2){
		game_check=calculate_possible_moves(a,1);
		if(game_check.size()==0){
			game_incompletion++;
			message("no possible moves for player 1");
		}
		else{
			game_incompletion=0;
			message("player 1 can make a move");
			read_input(x,y);
			while(!check_valid_move(a,1,x,y)){
				print_valid_moves(a,1);
				message("player 1 can make a move");
				read_input(x,y);
			}
			place_move(a,1,x,y);
			count++;
			display(a);
			game_check.clear();
		}
		game_check=calculate_possible_moves(a,-1);
		if(game_check.size()==0){
			game_incompletion++;
			message("no possible moves for player 2");
		}
		else{
			game_incompletion=0;
			message("player 2 can make a move");
			read_input(x,y);
			// cin>>x>>y;
			while(!check_valid_move(a,-1,x,y)){
				print_valid_moves(a,-1);
				message("player 2 can make a move");
				read_input(x,y);
				// cin>>x>>y;
			}
			place_move(a,-1,x,y);
			count++;
			display(a);
			game_check.clear();
		}
	}
}
int coins_turned(int (&a)[8][8],int &x,int &y){
	int count=0;
	for(int i=y+1;i<8;i++){
		if(a[x][i]==1)
			count++;
		else
			break;
	}
	for(int i=y-1;i>=0;i--){
		if(a[x][i]==1)
			count++;
		else
			break;
	}
	for(int i=x+1;i<8;i++){
		if(a[i][y]==1)
			count++;
		else
			break;
	}
	for(int i=x-1;i>=0;i--){
		if(a[i][y]==1)
			count++;
		else
			break;
	}
	for(int i=1;x-i>=0 && y-i>=0;i++){
		if(a[x-i][y-i]==1)
			count++;
		else
			break;
	}
	for(int i=1;x-i>=0 && y+i<8 ;i++){
		if(a[x-i][y+i]==1)
			count++;
		else
			break;
	}
	for(int i=1;x+i<8 && y-i>=0;i++){
		if(a[x+i][y-i]==1)
			count++;
		else
			break;
	}
	for(int i=1;x+i<8 && y+i<8;i++){
		if(a[x+i][y+i]==1)
			count++;
		else
			break;
	}
	return count;
}

int weight_changed(int (&a)[8][8],int (&w)[8][8],int &x,int &y,int player_code){
	int count=w[x][y];
	for(int i=y+1;i<8;i++){
		if(a[x][i]==-player_code)
			count+=w[x][i];
		else
			break;
	}
	for(int i=y-1;i>=0;i--){
		if(a[x][i]==-player_code)
			count+=w[x][i];
		else
			break;
	}
	for(int i=x+1;i<8;i++){
		if(a[i][y]==-player_code)
			count+=w[i][y];
		else
			break;
	}
	for(int i=x-1;i>=0;i--){
		if(a[i][y]==-player_code)
			count+=w[i][y];
		else
			break;
	}
	for(int i=1;x-i>=0 && y-i>=0;i++){
		if(a[x-i][y-i]==-player_code)
			count+=w[x-i][y-i];
		else
			break;
	}
	for(int i=1;x-i>=0 && y+i<8 ;i++){
		if(a[x-i][y+i]==-player_code)
			count+=w[x-i][y+i];
		else
			break;
	}
	for(int i=1;x+i<8 && y-i>=0;i++){
		if(a[x+i][y-i]==-player_code)
			count+=w[x+i][y-i];
		else
			break;
	}
	for(int i=1;x+i<8 && y+i<8;i++){
		if(a[x+i][y+i]==-player_code)
			count+=w[x+i][y+i];
		else
			break;
	}
	return count;	
}

void computer_move(int (&a)[8][8],int (&w)[8][8],int &x,int &y,int level,int count){
	if(level == 1)
		first_level(a,x,y);
	else if(level == 2)
		second_level(a,w,x,y);
	else if(level == 3){
		int p=-999;
		int q=0;
		third_level(a,w,x,y,p,p,-1,0,count,q,p);
	}
}
void first_level(int (&a)[8][8],int &x,int &y){
	vector<int> game_check = calculate_possible_moves(a,-1);
	int count=-1;
	int temp;
	for(int i=0;i<game_check.size();i++){
		temp=coins_turned(a,game_check[i],game_check[i+1]);
		if(count<temp){
			count=temp;
			x=game_check[i];
			y=game_check[i+1];
		}
		i++;
	}
}
void second_level(int (&a)[8][8],int (&w)[8][8],int &x,int &y){
	vector<int> game_check = calculate_possible_moves(a,-1);
	int count=-10000;
	int temp;
	for(int i=0;i<game_check.size();i++){
		temp = weight_changed(a,w,game_check[i],game_check[i+1],-1);
		if(count<temp){
			count = temp;
			x=game_check[i];
			y=game_check[i+1];
		}
		i++;
	}
}

void third_level(int (&a)[8][8],int (&w)[8][8],int &x,int &y,int x1,int y1,int player_code,int depth,int count,int &value,int &max){
	vector<int> game_check = calculate_possible_moves(a,player_code);
	if(count+5-depth<64 && game_check.size()!=0){
		int arr[8][8];
		int val;
		for(int i=0;i<game_check.size();i++){
			val=value;
			// for looking 5 steps ahead
			if(depth==0){
				x1=game_check[i];
				y1=game_check[i+1];
			}
			if(depth<4){ 
				copy(arr,a);
				val+=(weight_changed(a,w,game_check[i],game_check[i+1],player_code)*(-player_code));
				place_move(arr,player_code,game_check[i],game_check[i+1]);
				third_level(arr,w,x,y,x1,y1,-player_code,depth+1,count,val,max);
			} else if(depth==4){
				val+=weight_changed(a,w,game_check[i],game_check[i+1],player_code);
				if(max<val){
					x=x1;
					y=y1;
					max=val;
				}
			}
			i++;
		}
	} else{
		int count=-10000;
		int temp;
		for(int i=0;i<game_check.size();i++){
			temp = weight_changed(a,w,game_check[i],game_check[i+1],player_code);
			if(count<temp){
				count = temp;
				x=game_check[i];
				y=game_check[i+1];
			}
			i++;
 		}		
	}
	if(count+5-depth<64 && game_check.size()==0){
		if(max<value){
			x=x1;
			y=y1;
			max=value;
		}
	}
}

void computer_player_mode(int (&a)[8][8],int (&w)[8][8],int level){
	initialise_weight(w);
	int x,y;
	int count=4;
	int game_incompletion=0;
	vector<int> game_check;
	while(count<64 && game_incompletion<2){
		game_check=calculate_possible_moves(a,1);
		if(game_check.size()==0){
			game_incompletion++;
			message("no possible moves for player 1");
		}
		else{
			game_incompletion=0;
			message("player 1 can make a move");
			read_input(x,y);
			while(!check_valid_move(a,1,x,y)){
				print_valid_moves(a,1);
				message("player 1 can make a move");
				read_input(x,y);
			}
			place_move(a,1,x,y);
			count++;
			display(a);
			game_check.clear();
		}
		if(game_incompletion!=2){
			game_check=calculate_possible_moves(a,-1);
			if(game_check.size()==0){
				game_incompletion++;
				message("no possible moves for player 2");
			}
			else{
				game_incompletion=0;
				count++;
				computer_move(a,w,x,y,level,count);
				place_move(a,-1,x,y);
				message("after computer placing the move at",to_string(x),to_string(y));
				display(a);
				game_check.clear();
			}
		}
	}
}

void initialise_weight(int (&w)[8][8]){ // used to initialise the weights of the board
	// weights are not following any particular order so needed to initialise each and every element
	w[0][0]=120,w[0][1]=-20,w[0][2]=20,w[0][3]=5,w[0][4]=5,w[0][5]=20,w[0][6]=-20,w[0][7]=120;
	w[1][0]=-20,w[1][1]=-40,w[1][2]=-5,w[1][3]=-5,w[1][4]=-5,w[1][5]=-5,w[1][6]=-40,w[1][7]=-20;
	w[2][0]=20,w[2][1]=-5,w[2][2]=15,w[2][3]=3,w[2][4]=3,w[2][5]=15,w[2][6]=-5,w[2][7]=20;
	w[3][0]=5,w[3][1]=-5,w[3][2]=3,w[3][3]=3,w[3][4]=3,w[3][5]=3,w[3][6]=-5,w[3][7]=5;
	w[4][0]=5,w[4][1]=-5,w[4][2]=3,w[4][3]=3,w[4][4]=3,w[4][5]=3,w[4][6]=-5,w[4][7]=5;
	w[5][0]=20,w[5][1]=-5,w[5][2]=15,w[5][3]=3,w[5][4]=3,w[5][5]=15,w[5][6]=-5,w[5][7]=20;
	w[6][0]=-20,w[6][1]=-40,w[6][2]=-5,w[6][3]=-5,w[6][4]=-5,w[6][5]=-5,w[6][6]=-40,w[6][7]=-20;
	w[7][0]=120,w[7][1]=-20,w[7][2]=20,w[7][3]=5,w[7][4]=5,w[7][5]=20,w[7][6]=-20,w[7][7]=120;
}
void display(int a[8][8]){
	cout<<"\n";
	for(int i=0;i<8;i++){
		for(int j=0;j<60;j++)
			cout<<" ";
		// cout<<i<<" < - ";
		for(int j=0;j<8;j++){
			if(a[i][j] == -1)
				cout<<2<<"   ";
			else
				cout<<a[i][j]<<"   ";
		}
		cout<<"\n\n";
	}
	cout<<"\n";
}

void message(string s){
	for(int i=0;i<55;i++)
		cout<<" ";
	cout<<s;
	cout<<"\n";
}

void message(string s,string val){
	for(int i=0;i<55;i++){
		cout<<" ";
	}
	cout<<s<<" "<<val<<"\n";
}

void message(string s,string x,string y){
	for(int i=0;i<55;i++)
		cout<<" ";
	cout<<s<<" ("<<x<<","<<y<<")";
	cout<<"\n";	
}

vector<int> check_right(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=y+1;k<8;k++){
		if(a[x][k]==-player_code){
			count++;
		} else if(a[x][k] == 0 && count>0){
			ans.push_back(x);
			ans.push_back(k);
			break;
		} else{
			break;
		}
	}
	return ans;
}
vector<int> check_left(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=y-1;k>=0;k--){
		if(a[x][k]==-player_code){
			count++;
		} else if(a[x][k] == 0 && count>0){
			ans.push_back(x);
			ans.push_back(k);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> check_top(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=x-1;k>=0;k--){
		if(a[k][y]==-player_code){
			count++;
		} else if(a[k][y] == 0 && count>0){
			ans.push_back(k);
			ans.push_back(y);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> check_down(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=x+1;k<8;k++){
		if(a[k][y]==-player_code){
			count++;
		} else if(a[k][y] == 0 && count>0){
			ans.push_back(k);
			ans.push_back(y);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> check_right_top(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=1;y+k<8 && x-k>=0;k++){
		if(a[x-k][y+k]==-player_code){
			count++;
		} else if(a[x-k][y+k] == 0 && count>0){
			ans.push_back(x-k);
			ans.push_back(y+k);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> check_right_down(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=1;x+k<8 && y+k<8;k++){
		if(a[x+k][y+k]==-player_code){
			count++;
		} else if(a[x+k][y+k] == 0 && count>0){
			ans.push_back(x+k);
			ans.push_back(y+k);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> check_left_top(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=1;x-k>=0 && y-k>=0;k++){
		if(a[x-k][y-k]==-player_code){
			count++;
		} else if(a[x-k][y-k] == 0 && count>0){
			ans.push_back(x-k);
			ans.push_back(y-k);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> check_left_down(int a[8][8],int player_code,int x,int y){
	int count=0;
	vector<int> ans;
	for(int k=1;x+k<8 && y-k>=0;k++){
		if(a[x+k][y-k]==-player_code){
			count++;
		} else if(a[x+k][y-k] == 0 && count>0){
			ans.push_back(x+k);
			ans.push_back(y-k);
			break;
		} else{
			break;
		}
	}
	return ans;
}

vector<int> calculate_possible_moves(int a[8][8],int player_code){
	int flag;
	vector<int> ans;
	vector<int> temp;
	int count;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(a[i][j] == player_code){
				// for moving left top
				temp=check_left_top(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving top
				temp=check_top(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving right top
				temp=check_right_top(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving left
				temp=check_left(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving right
				temp=check_right(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving left down
				temp=check_left_down(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving down
				temp=check_down(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
				// for moving right down
				temp=check_right_down(a,player_code,i,j);
				if(temp.size()==2){
					flag=0;
					for(int i=0;i<ans.size();i++){
						if(ans[i]==temp[0] && ans[i+1]==temp[1])
							flag=1;
						i++;
					}
					if(flag!=1){
						ans.push_back(temp[0]);
						ans.push_back(temp[1]);
					}
					temp.clear();
				}
			}
		}
	}
	return ans;
}

void print_valid_moves(int a[8][8],int player_code){
	message("valid moves are:");
	vector<int> ans = calculate_possible_moves(a,player_code);
	for(int i=0;i<ans.size();i++){
		cout<<"("<<ans[i]<<","<<ans[i+1]<<")\n";
		i++;
	}
}

bool check_valid_move(int a[8][8],int player_code,int x,int y){
	vector<int> ans=calculate_possible_moves(a,player_code);
	for(int i=0;i<ans.size();i++){
		i++;
	}
	for(int i=0;i<ans.size();i++){
		if(ans[i]==x && ans[i+1]==y){
			return true;
		}
		i++;
	}
	return false;
}

void place_move(int (&a)[8][8],int player_code,int x,int y){
	int count;
	int flag=0;
	// placing move for right side
	for(int i=y+1,count=0;i<8;i++){
		if(a[x][i]==-player_code){
			count++;
		} else if(a[x][i] == player_code && count>0){
			for(int j=y+1;j<i;j++){
				a[x][j]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	// placing move for left side
	for(int i=y-1,count=0;i>=0;i--){
		if(a[x][i]==-player_code){
			count++;
		} else if(a[x][i] == player_code && count>0){
			for(int j=y-1;j>i;j--){
				a[x][j]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	// placing move for top side 
	for(int i=x+1,count=0;i<8;i++){
		if(a[i][y]==-player_code){
			count++;
		} else if(a[i][y] == player_code && count>0){
			for(int j=x+1;j<i;j++){
				a[j][y]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	// placing move for down side
	for(int i=x-1,count=0;i>=0;i--){
		if(a[i][y]==-player_code){
			count++;
		} else if(a[i][y] == player_code && count>0){
			for(int j=x-1;j>i;j--){
				a[j][y]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	// placing move for right_top
	for(int i=1,count=0;y+i<8 && x-i>=0;i++){
		if(a[x-i][y+i]==-player_code){
			count++;

		} else if(a[x-i][y+i] == player_code && count>0){
			for(int j=1;j<=i;j++){
				a[x-j][y+j]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	// placing a move for right down
	for(int i=1,count=0; x+i<8 && y+i<8;i++){
		if(a[x+i][y+i]==-player_code){
			count++;
		} else if(a[x+i][y+i] == player_code && count>0){
			for(int j=1;j<=i;j++){
				a[x+j][y+j]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	// placing a move for left top
	for(int i=1,count=0;y-i>=0 && x-i>=0;i++){
		if(a[x-i][y-i]==-player_code){
			count++;
		} else if(a[x-i][y-i] ==player_code && count>0){
			for(int j=1;j<=i;j++){
				a[x-j][y-j]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	//placing a move for left down
	for(int i=1,count=0;y-i>=0 && x+i<8;i++){
		if(a[x+i][y-i]==-player_code){
			count++;
		} else if(a[x+i][y-i] == player_code && count>0){
			for(int j=1;j<=i;j++){
				a[x+j][y-j]=player_code;
			}
			flag=1;
			break;
		} else{
			break;
		}
	}
	if(flag==1)
		a[x][y]=player_code;
}
void counter(int a[8][8],int &count1,int &count2){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(a[i][j]==-1)
				count2++;
			else if(a[i][j]==1)
				count1++;
		}
	}
}
