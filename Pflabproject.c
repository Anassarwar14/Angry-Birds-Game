#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>


#define rows 24
#define col 80
#define g 9.81

//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y);
void SetColor(int ForgC);

 
void frame();
void GameStart();
void objectGenerate(int flag3, int rand_, int n, int widthTower);
void objectHit(int rand_, int flag3, int flag2, int n, int widthTower, int k);	
void levelUp(int L);
void lives(int chances);

int main(){
	
srand(time(0));
	
float j, x=0, y=0, flag=0, flag2=0, flag4=0, flag5=0, v, Tof, angle, t;
int a, i, chances, m,  r, enemies;
int rand_[10], n[10], widthTower[10], flag3[10], k[10];

int L=2; //Level#1


	GameStart();
	chances=3;
	
do{
	for(r=0; r<10; r++){
	 rand_[r] = 14 + rand() % 63; //random x coordinates of object
	 n[r] = 3+ rand() % 17;	//random maxheight of object coords
	 widthTower[r] = 1+ rand()%4;
	}
	
	levelUp(L);
	
	enemies=L;	
	for(a=0; a<10; a++){
		flag3[a]= 0;
	}
	
	
	do{
		
		flag=0;
		flag2=0;
		for(a=0; a<10; a++){
			if(flag3[a]!=2){ //flag3[a]==2 means object destroyed(dont generate again)
				k[a]= 0;
			}
			
		}
		flag4=0;
		flag5=0;
		
		
		
		system("cls");
		system("Color F6");
		frame();
		lives(chances);
		for(i=0;i<L;i++){
				objectGenerate(flag3[i], rand_[i], n[i], widthTower[i]);
		}
		
		SetColor(4);
		gotoxy(1,22);
		printf("(0)>");
		
		SetColor(1);
		gotoxy(2, 2);
		printf("Enter Velocity & Angle: ");
		scanf("%f %f", &v, &angle);
		
		angle = angle*3.142/180;
		
		Tof = (2*v*sin(angle))/g;
		
		
		//Game Start
		for(t=0; t<=Tof; t+=0.4){
			system("cls");	
			frame();
			system("Color F6");
			
			if(flag5==1){break;}
			
			//objectHit
			for(a=0; a<L; a++){
				if(flag3[a]==1){
				 	k[a]+=3;
				 	if(n[a]-k[a]<0){
						flag3[a]=2;//neither object is constructed nor destroyed
					}
				 	if(n[L-1]-k[L-1]<0 && flag2==1 && enemies==0){ flag5=1; break;}
				 	
				}
				objectHit(rand_[a], flag3[a], flag2, n[a], widthTower[a], k[a]);
				
			}
			
			if(flag5==1){continue;}
				
				
			//object location
			 //level1
			for(i=0;i<L;i++){
				objectGenerate(flag3[i], rand_[i], n[i], widthTower[i]);
			}
		
		
			if(flag2==1){
				Sleep(1000);
				continue;
			}
			
			
			
			//projectile
			if(flag==0){ 
				x = 1 + v*cos(angle)*t;
				y = 22 + -1*(v*sin(angle)*t + 0.5*-g*pow(t, 2));
			}
		
		
			if((v*sin(angle)+g*t)==0 || flag==1){
				x = 1 + v*cos(angle)*t;
				y = 22 + (v*sin(angle)*t + 0.5*-g*pow(t, 2));
				flag=1;
			}
			
			//if object hit
			for(i=0; i<L;i++){
				
				if((x>(rand_[i]-11.0) && x<=(float)rand_[i] && flag3[i]==0)){
					if(y>22-n[i]-3){
						if(!(x<rand_[i]-5.0 && y>20.0)){//special case where bird falls close to tower
							enemies--;
							Tof+=0.4*3;
							flag3[i] =1;
							flag4=1;
							continue;
						}
						
					}
				}
			}
			
	
			//Out  of boundary test
			if(x>77.0 || y>22.0 || y<0.0){
				flag2=1;
				continue;
			}
	
			//Displaying
			SetColor(4);
			gotoxy(x, y);
			if(flag4!=1){
				printf("(0)>");
			}
			else{
				printf("(*)>");
			}
			lives(chances);
			Sleep(1000);
		}
		
		if(enemies==0){
			break;
		}
		
	 chances--;
	}while(chances>0);
	
	if(enemies>0){//Gamelose
		break;
	}
	
	if(enemies==0){
		chances=3;
		L++; //level increase(objects increase)
	}
}while(L<10);

if (L<10){
	system("cls");
	system("Color 56");
	gotoxy(52,15);
	printf("YOU LOST!\n\n\n\n\n\n\n\n\n\n");
	Sleep(2500);
}
else{
	system("cls");
	system("Color 26");
	gotoxy(52,15);
	printf("Woohoo! YOU WON!\n\n\n\n\n\n\n\n\n\n");
	Sleep(2500);
}



	return 0;
}
//citation: https://openstax.org/books/university-physics-volume-1/pages/4-3-projectile-motion#:~:text=h%20%3D%20v%200%20y%202,component%20of%20the%20initial%20velocity.

void frame()
{
	int i, j;

	for (i = 0; i < rows; i++){
		for (j = 0; j < col; j++){
			gotoxy(j, i);
			printf(" ") ;
			
			if(j == 0 || j == col-1){
				gotoxy(j, i);
				printf("|");
			}

			gotoxy(j, i);
			if(i == 0 || i == rows-1){
				printf("-");
			}
		}
	}

}

void GameStart(){
	char startkey;

	system("Color E5");
	do{	
		gotoxy(50,6);
		printf("WELCOME");
		
		gotoxy(52,8);
		printf("TO");
		
		SetColor(4);
		gotoxy(48,10);
		printf("ANGRY");
		
		SetColor(6);
		gotoxy(54,10);
		printf("BIRDS");
		
		SetColor(5);
		gotoxy(46,15);
		printf("Press E to Start\n");

 		startkey = getch();
		
	}while(startkey!='e' && startkey!='E');
}

void objectGenerate(int flag3, int rand_, int n, int widthTower){
int x, y, f, j=0;

	if(flag3==0){
	
		for(f=0;f<n;f++){
			x = rand_; 
			y = 22;
			
			gotoxy(x,y-f);
			printf("#");
		 
			gotoxy(x - widthTower,y-f);
			printf("#");

			if(f==n-1){
				for(j=0; j<=widthTower; j++){
					gotoxy(x-widthTower+j,y-f);
					printf("=");
				}
				
				SetColor(2);
				gotoxy(x-widthTower,y-f-1);
				printf("0.0");
				SetColor(6);
			}	
		}
	}
}

void objectHit(int rand_, int flag3, int flag2, int n, int widthTower, int k){
int i, j, x, y;

	if(flag3==1){
		x = rand_; 
		y = 22;
		
			for(i=0;i<n-k;i++){
			 
				gotoxy(x,y-i);
				printf("#");
			 
				gotoxy(x - widthTower,y-i);
				printf("#");
				
				//smack animation
				gotoxy(x-(widthTower+rand()%3), y-i);
				printf("#");
				gotoxy(x+(widthTower+rand()%3), y-i);
				printf("#");
				gotoxy(x-(widthTower+rand()%3), y-i);
				printf("#");
				
					
				if(i==n-1-k){
					for(j=0; j<=widthTower; j++){
						gotoxy(x-widthTower+j,y-i);
						printf("=");
					}
					
					if(n-k<4){
						SetColor(4);
						gotoxy(x-widthTower, 21);
						printf("X_X");
						SetColor(6);
					}
					else{
						SetColor(3);
						gotoxy(x-widthTower,y-i-1);
						printf("o_o");
						SetColor(6);
					}
				}			
			}			
	}
}

void levelUp(int L){
	system("cls");
	system("Color AF");
	gotoxy(52,15);
	printf("LEVEL #%d", L-1);
	Sleep(2500);

}

void lives(int chances){
 
	switch(chances){
		case 3:
			SetColor(4);
			gotoxy(2,1);
			printf("Lives:  <3 <3 <3");
			SetColor(6);
			break;
			
		case 2:
			SetColor(4);
			gotoxy(2,1);
			printf("Lives:  <3 <3");
			SetColor(6);	
			break;
		
		case 1:
			SetColor(4);
			gotoxy(2,1);
			printf("Lives:  <3");
			SetColor(6);
			break;	
	}
	
}


void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
 
 





