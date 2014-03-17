#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);i++)
#define V 8
#define black 1
#define white 2
#define LIMIT 17 // this is the DEPTH upto which computer looks before making the move
const float W=.5;  // this is the weight of the each of heuristic

vector<vector<int> > board(V,vector<int>(V));

class move
{
	public:
	int x;
	int y;
	move(){}	
	move(int x1,int y1){x=x1;y=y1;}
	
};

// following are the declarations of the functions used

void initialize();//intialize the board with 0s,1s,2s
int display();//display the board
int switch_turn(int);//switches turn b/w black and white
bool validMove(int,int,int,int,vector<move>& m);//checks for valid move given input coordinates
bool validMoveUtil(int,int,string,vector<move>& m);//helper function for validMove
int cpuMove(vector<move>& m);//chooses a random move from a set of valid moves
void fill_board(vector<move>& m,int player);//fills the board with valid move
float minmax(int,int,int,vector<move>&,bool);
float a_b(int,int,int,vector<move>&,bool,float,float);
float a_b(int,int,int,vector<move>&,bool,float,float);
float disc_count(int);
float weighted_disc_count(int);
int checkMoves();
void printresult();

void printresult()
{
	int black_count=0,white_count=0;
	
	
	REP(i,V)
	{
	REP(j,V)
	{
		if(board[i][j]==black)
		black_count++;
		else if(board[i][j]==white)
		white_count++;			
	}	
	}
   if(black_count>white_count)
	cout<<"You win"<<endl;
	else
	cout<<"Computer wins"<<endl;
	
}
int checkMoves()
{
        int flag=0;
	REP(i,V)
	REP(j,V)
	{
		vector<move> MM;
        move mm(i,j);
		
		if(validMove(i,j,black,white,MM))
		{
		cout<<"("<<i<<","<<j<<") ";
		flag=1;
		}
	}
	cout<<endl;
	if(flag==0)
	 {
	 return 0;
	}
	return 1;
}
void initialize()
{

	REP(i,V)
	REP(j,V)
	board[i][j]=0;
	
	int center=(V-1)/2;
	board[center][center]=black;
	board[center+1][center+1]=black;
	
	board[center][center+1]=white;
	board[center+1][center]=white;
	
}
int display()
{
	int black_count=0,white_count=0,zero_count=0;
	cout<<"   ";
	REP(i,V)
	cout<<i<<"  ";
	cout<<endl<<endl;

	REP(i,V)
	{
	REP(j,V)
	{
		if(board[i][j]==black)
		black_count++;
		else if(board[i][j]==white)
		white_count++;
		else
		zero_count++;			
	}	
	}	
	
	REP(i,V)
	{
	cout<<i<<"  ";
	REP(j,V)
	{
		if(board[i][j]==0)
		cout<<"-  ";
		else if(board[i][j]==1)
		cout<<"B"<<"  ";
		else if(board[i][j]==2)
		cout<<"W"<<"  ";
		
	}
	if(i==V/2-1)
	cout<<"   Black->"<<black_count;
	else if(i==(V/2))
	cout<<"   White->"<<white_count;
	
	cout<<endl<<endl;
	}
	
	cout<<"  "<<endl;
	cout<<"---------------------------"<<endl;

	if(zero_count==0)
	{
		if(black_count>white_count)
		cout<<"You win"<<endl;
		else
		cout<<"Computer wins"<<endl;
		
	}
	return zero_count;
	
}
int switch_turn(int turn)
{
	if(turn==black)
	return white;
	else if(turn==white)
	return black;
}
bool validMoveUtil(int x,int y,string str,int player,int opposite,vector<move>& M)
// this function basically finds the player on the opposite side of my current move
{
	if(   !(x>=0 && x<V && y>=0 && y<V ) )
	return false;
	move m;
	
	if(board[x][y]==player)
	return true;
	
	if(board[x][y]==0)
	return false;
	
	if(
	(str=="W" && validMoveUtil(x,y-1,"W",player,opposite,M))||	
	
	(str=="E" && validMoveUtil(x,y+1,"E",player,opposite,M) ) ||
	
	(str=="S" && validMoveUtil(x+1,y,"S",player,opposite,M) )	 ||
	
	(str=="N" && validMoveUtil(x-1,y,"N",player,opposite,M)	) ||
	
	(str=="SW" && validMoveUtil(x+1,y-1,"SW",player,opposite,M) )||	
	
	(str=="NW" && validMoveUtil(x-1,y-1,"NW",player,opposite,M) )||	
	
	(str=="SE" && validMoveUtil(x+1,y+1,"SE",player,opposite,M) )||	
	
	(str=="NE"&& validMoveUtil(x-1,y+1,"NE",player,opposite,M) ) )	
	{m.x=x;m.y=y;M.push_back(m);
	return true;}

	return false;
	
}
bool validMove(int x,int y,int player,int opposite,vector<move>& M)
// this function checks for the valid move
// and if there is a valid move that move is recorded in the vector 'M' ie. it records all the positions
// where the discs are to be turned after the move
// NOTE: 'M' is passed to the function.
{

	int X,Y;
	move m;
	
	if(   !(x>=0 && x<V && y>=0 && y<V && board[x][y]==0) )
// here the primary testing is done ie. if the move is already out of the bounds or on the position (x,y)
// already player is present
	return false;
	
	bool result=false;
	X=x-1,Y=y;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
 	// this checks for the bounds and if player just above the (x,y) position is opposite or not
	if(validMoveUtil(X,Y,"N",player,opposite,M) )
	// then if the above condition is true, then it calls the 'util' function with the direction
	// of the move
	// same for other following conditions
	result=true;
	
	X=x,Y=y-1;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if(validMoveUtil(X,Y,"W",player,opposite,M) )	
	result=true;
	
	X=x+1,Y=y;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if(validMoveUtil(X,Y,"S",player,opposite,M) )	
	result=true;
	
	X=x,Y=y+1;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if( validMoveUtil(X,Y,"E",player,opposite,M) )	
	result=true;
	
	X=x-1,Y=y-1;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if( validMoveUtil(X,Y,"NW",player,opposite,M) )	
	result=true;
	
	X=x+1,Y=y-1;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if( validMoveUtil(X,Y,"SW",player,opposite,M) )	
	result=true;
	
	X=x+1,Y=y+1;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if( validMoveUtil(X,Y,"SE",player,opposite,M) )	
	result=true;
	
	X=x-1,Y=y+1;
 	if(   (X>=0 && X<V && Y>=0 && Y<V && board[X][Y]==opposite) )
	if( validMoveUtil(X,Y,"NE",player,opposite,M) )	
	result=true;
	
	return result;		
}
int cpuMove(vector<move>& M,char c)
// this is the function which decides the move for cpu
{		
    int flag=0;
	
	cout<<"Valid Moves for CPU"<<endl;
	REP(i,V)
	REP(j,V)
	{
		vector<move> MM;
        move mm(i,j);
		
		if(validMove(i,j,white,black,MM))
		{
			flag=1;
			cout<<"("<<i<<","<<j<<")"<<" ";
		}
	}
	if(flag==0)
	{
		return 0;
	}
	
	//cout<<"press any key to execute CPU ";\
	char chr; cin>>chr;
	
	//clock_t start_t, end_t, total_t;
	
	//start_t = clock();
	float x;
	if(c=='m')
	x=minmax(white,black,0,M,true);
	else if(c=='a')
	x=a_b(white,black,0,M,true,-1e15,1e15);
	//end_t = clock();
	//total_t = (double)(end_t - start_t);
	//total_t = (end_t - start_t);
	//printf("Total time taken by CPU: %d\n", total_t  );
	printf("\nvalue of func is= %f\n",x);
	printf("\nMove of CPU is (%d,%d)\n",(M.end()-1)->x,(M.end()-1)->y);
	
	assert(!M.empty());
	
	fill_board(M,white);
	return 1;
}
void fill_board(vector<move>& m,int player)
// this function basically makes use of the vector "m", which was populated in "validMove" function
// to turn the discs
{
	vector<move>::iterator it;
	
	for(it=m.begin();it!=m.end();it++)
	{
		board[it->x][it->y]=player;
	}	
}

// now follows the heuristics which decide the degree how good the move is?

float disc_count(int player)
{
	int white_disc=0, black_disc=0;	
	for(int i=0;i<V;++i)
	for(int j=0;j<V;++j)
	{
		if(board[i][j]==white) ++white_disc;		
		else if(board[i][j]==black) ++black_disc;
	}
	
	float result=white_disc-black_disc;
	return result;
}

float weighted_disc_count(int player)
{
	int side_weight=30, corner_weight=50, normal_weight=1;
	int normal_white=0,side_white=0, corner_white=0;
	int normal_black=0,side_black=0, corner_black=0;
	
	for(int i=0;i<V;++i)
		for(int j=0;j<V;++j)
		
			if( (i==0 && j==0) || (i==V-1 && j==V-1) || (i==V-1 && j==0) || (i==0 && j==V-1))
			{
				if(board[i][j]==white) ++corner_white;
				else if(board[i][j]==black) ++corner_black;
			}
			else if(i==0 || j==0 || i==V-1 || j==V-1)
			{
				if(board[i][j]==white) ++side_white;
				else if(board[i][j]==black) ++side_black;											
			}
			else
			{
				if(board[i][j]==white) ++normal_white;
				else if(board[i][j]==black) ++normal_black;
			}
			
	float result=0;
	result=side_weight*(side_white-side_black) + corner_weight*(corner_white-corner_black)+\
	normal_weight*(normal_white-normal_black);	

	return result;
}

#define func1 disc_count
#define func2 weighted_disc_count

float minmax(int player,int opposite,int level,vector<move>& best,bool value)
{
	
	if(level > LIMIT)		
	return W*func1(opposite)+(1-W)*func2(opposite);
	
	// restore is the current state of the board. It's copy has been made because during this function 
	// it is changed and needs to be restored
	// copy is the function of the header file "algorithm". Look for it if you don't understand.
	
	vector<vector<int> > restore(V,vector<int>(V));
	copy(board.begin(),board.end(),restore.begin());
	
	float max_=-1e15, min_=1e15;
	int check=0;
	
	for(int i=0;i<V;++i)
	{
		for(int j=0;j<V;++j)
		{
			vector<move> M;
			// this is vector which records the moves.
	
			if( validMove(i,j,player,opposite,M))
			// here we check if position (i,j) is valid or not?
			{
				
				check=1;
				M.push_back(move(i,j));
				// this step is done because during the population of M, every position is 
				// recorded accept the (i,j).
				
				assert(!M.empty());
				fill_board(M,player);

				float rec=minmax(opposite,player,level+1,best,true);
				// now the call is made to minmax function again but with the following changes:
				// level is increased by 1
				// palyers switched

				if(player == white)
				// here white is MAX player (analogy to MINIMAX algorithm)
				{
					if(max_ <= rec)
					{
						max_ = rec;
						if(!level)
						// this is done just to avoid reduntant copy's 
						// we need to record the move just at the immediate lower level
						// of original call
						// so there level will be 0
						// if you don't get this point try to run it one paper
						// but if even that doesn't help email me and I will try to explain 
						// you
						{
							best.clear();
						
							best.resize(M.size());							
							copy(M.begin(),M.end(),best.begin());
						}
					}
				}
				else if(player == black)
				// here BLACK is MIN player in MINIMAX algorithm.
				{
					if(min_ >= rec)
					{
						min_ = rec;
						if(!level)
						{
							best.clear();

							best.resize(M.size());
							copy(M.begin(),M.end(),best.begin());
						}
					}
				}

				copy(restore.begin(),restore.end(),board.begin());
			}
		}
	}
	
	if(!check)
	// this is the case when a player has no move. Then instead of ending the game, turns are switched and 
	// other player makes the move.
	// if both of them doesn't have the moves then game end's and player having more discs wins.
	
	{
		if(value == false)		
		return W*func1(player)+(1-W)*func2(player);
		
		return minmax(opposite,player,level,best,false);
	}
	
	return (player==white)? max_ : min_;
}
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

float a_b(int player,int opposite,int level,vector<move>& best,bool value,float alpha,float beta)
{
	
	if(level > LIMIT)		
	return W*func1(opposite)+(1-W)*func2(opposite);	
	
	vector<vector<int> > restore(V,vector<int>(V));
	copy(board.begin(),board.end(),restore.begin());
	
	//vector<move> best;
	int flag=0;
	float max_=-1e15, min_=1e15;
	int check=0;
	
	for(int i=0;i<V;++i)
	{
		for(int j=0;j<V;++j)
		{
			vector<move> M;
	
			if( validMove(i,j,player,opposite,M))
			{
				
				check=1;
				M.push_back(move(i,j));
				
				assert(!M.empty());
				fill_board(M,player);

				float rec=a_b(opposite,player,level+1,best,true,alpha,beta);

				if(player == white)
				{
					//alpha-beta pruuning
					alpha=max(alpha,rec);
						
					if(beta<=alpha)
					{
						flag=1;
						copy(restore.begin(),restore.end(),board.begin());
						break;
					}
						
					if(max_ <= rec)
					{
						max_ = rec;
						if(!level)
						{
							best.clear();
						
							best.resize(M.size());							
							copy(M.begin(),M.end(),best.begin());
						}
					}
				}
				else if(player == black)
				{
					beta=min(beta,rec);
					
					if(beta<=alpha)
					{
						flag=1;
						copy(restore.begin(),restore.end(),board.begin());
						break;
					}
						
					if(min_ >= rec)
					{
						min_ = rec;
						
						if(!level)
						{
							best.clear();

							best.resize(M.size());
							copy(M.begin(),M.end(),best.begin());
						}
					}
				}

				copy(restore.begin(),restore.end(),board.begin());
			}
		}
		if(flag==1)
		break;
	}
	
	if(!check) // no valid move
	// switch the turns
	{
		if(value == false)		
		return W*func1(player)+(1-W)*func2(player);
		
		return a_b(opposite,player,level,best,false,alpha,beta);
	}
	
	return (player==white)? max_ : min_;
}
