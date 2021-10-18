#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define ROW		10
#define COLUMN	10
#define	MINE	7

void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 獲取標準輸出裝置控制代碼
    SetConsoleCursorPosition(hOut, pos);//兩個引數分別是指定哪個窗體，具體位置
}

void Fill(int x, int y,int block[][COLUMN],int block2[][COLUMN]){
	if(x>ROW-2 || x<1) return;
	if(y>COLUMN-2 || y<1) return;
	if(block2[x][y] == 99) return;
	
	gotoxy(y,x);
	if(block[x][y]>=1 && block[x][y]<=8){
		printf("%d",block[x][y]);
		block2[x][y]=99;
	}
	else if(block[x][y]==0){
		printf("%d",block[x][y]);
		block2[x][y]=99;
		Fill(x,y+1,block,block2);
		Fill(x,y-1,block,block2);
		Fill(x+1,y,block,block2);
		Fill(x-1,y,block,block2);
	}
}

int main(){
	int map[ROW][COLUMN];
	int map2[ROW][COLUMN];
	int map3[ROW][COLUMN];
	int i,j,s;
	int x,y,q,w,t,T,lattice;
	int counter,bomb;
	int ans =0;
	t = MINE;
	T = 0;
	int ch;
	
	counter = bomb = 0;
	
	srand(time(NULL));
	
	
	for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			map[i][j] = 0;
			map2[i][j] = 0;
			map3[i][j] = 0;
		}
	}
	
	for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			if(i==0||i==ROW-1||j==0||j==COLUMN-1)
				map[i][j]=9;
				map2[i][j]=9;
		}
	}
	/*for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			printf("%d",map[i][j]);
		}
		printf("\n");
	}*/
	

	for(i=0;i<MINE;i++){
		do{
			q = rand()%(ROW-2)+1;
			w = rand()%(COLUMN-2)+1;
		}while(map[q][w]==11);
		map[q][w] = 11;
		map2[q][w] = 11;
		
	}
	for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			s=map[i][j];
			switch(s){
				case 0:
					q=i;
					w=j;
					if(map[q+1][w] == 11) bomb++;
					if(map[q-1][w] == 11) bomb++;
					if(map[q][w+1] == 11) bomb++;
					if(map[q][w-1] == 11) bomb++;
					if(map[q+1][w+1] == 11) bomb++;
					if(map[q+1][w-1] == 11) bomb++;
					if(map[q-1][w+1] == 11) bomb++;
					if(map[q-1][w-1] == 11) bomb++;
					map[q][w] = bomb;
					map2[q][w] = 1;
					bomb = 0;
					break;
				case 9:
					break;
				case 11:
					break;
			}
		}

	}
	for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			s=map[i][j];
			switch(s){
				case 0 ... 8:
					printf("-");
					break;
				case 11:
					printf("-");
					break;
				case 9:
					printf(" ");
					break;
				
			}
		}
		printf("\n");
	}
	printf("\n");

	/*for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			s=map[i][j];
			switch(s){
				case 0 ... 8:
					printf("%d",map[i][j]);
					break;
				case 11:
					printf("*");
					break;
				case 9:
					printf(" ");
					break;
				
			}
		}
		printf("\n");
	}
	*/
	printf("\n");
	gotoxy(25,0);
	printf("標出%d個地雷即可獲勝\n",MINE);
	gotoxy(25,1);
	printf("遊戲方式:上下左右控制方向，按F標記地雷，空白鑑翻開格子，祝您幸運!");
	x=3;y=1;
	gotoxy(x,y);
		while((ans!=1) && ( T!=MINE)){
		ch=getch();
		gotoxy(x,y);
		switch(ch){
			case 224:
				switch(ch=getch()){
					case 72:
						if(y-1>0) y=y-1;
						gotoxy(x,y);
						break;
					case 80:
						if(y+1<=COLUMN-2) y=y+1;	
						gotoxy(x,y);
						break;
					case 75:
						if(x-1>0) x=x-1;
						gotoxy(x,y);
						break;
					case 77:
						if(x+1<=ROW-2) x=x+1;
						gotoxy(x,y);
						break;	
				}
				break;
			case 102:
				if(map3[x][y] != 46){
					printf("%c",'F');
					map3[x][y] = 46;
					if(map2[y][x] == 11){
						T++;
					}	
					if(map2[y][x] != 11){
						T--;
					}
				
					gotoxy(x,y);
				}
				else{
					if(map2[y][x] == 11){
						T--;
					}
					printf("-");
					map3[x][y] = 0;
					gotoxy(x,y);
				}
				break;
			case 32:
				if(map[y][x] == 11){
					ans=1;
					gotoxy(x,y);
				}
				else if(map[y][x] == 0){
					Fill(y,x,map,map2);
					gotoxy(x,y);
				}
				else{			
					printf("%d",map[y][x]);
					gotoxy(x,y);
				}
				break;
				
		}
	}


	if(ans == 1){
		
		gotoxy(0,0);
		for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			s=map[i][j];
			switch(s){
				case 0 ... 8:
					printf("%d",map[i][j]);
					break; 
				case 11:
					printf("*");
					break;
				case 9:
					printf(" ");
					break;
				
			}
		}
		printf("\n");
	}
	gotoxy(0,25);
	printf("You Lose The GAME !!! LOSERRRRRR!");
	}
	else if(T == MINE){
		gotoxy(0,65);
		printf("OK! You Win ,It's Your Goooood Luck This Time");
		gotoxy(0,66);
	}
		return 0;
	
} 




