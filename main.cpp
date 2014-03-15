#include "othello.cpp"
int main()
{
    
    initialize();
    
    int turn=black;
	int flag1=0,flag2=0;
	char chr;
	printf("current DEPTH is %d\n",LIMIT);
	puts("enter 'm' for minimax or 'a' for alpha-beta");
	scanf("%c",&chr);
	
	while(display())
    {
		vector<move> M;
		if(checkMoves())
 		{
			if(flag2==1)
			flag2=0;
			
			int x,y; 			
			
			cout<<"Your Turn"<<endl;
			
 			cin>>x;
 			cin>>y;
 			
 			if(!validMove(x,y,1,2,M))
 			{
				cout<<"   Not a valid move!!!!!!"<<endl;
				cout<<"-------------------------"<<endl;
				continue;//reenter coordinates in cases of invalid move 			
     		}
     		move m;
     		m.x=x;m.y=y;M.push_back(m);
     		fill_board(M,1);
     		cout<<"Move Successful"<<endl;
			display();
		}
		else if(flag2==0)
		{
			flag1=1;
		}
		else if(flag2==1)
		{
		printresult();break;
		}
		
		cout<<"CPU's turn"<<endl;
		vector<move> M1;
		if(!cpuMove(M1,chr))
     	{
     		if(flag1==1)
			{
			printresult();
			break;
			}
			else flag2=1;	
 		}
		else if(flag1==1)
			flag1=0;	
	}
	puts("press any key to exit");
	char ch; cin>>ch;
return 0;	
}
