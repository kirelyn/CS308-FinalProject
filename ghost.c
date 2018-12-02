#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* for sleep() */
#include <curses.h>

int * blinky(int pacY, int pacX, int currY, int currX){
        int y = 0;
        int x = 0;
        int yx[3];
        if(pacY > currY){
                y = currY++;
        }
        else if ( pacY > currY){
                y = currY--;
        }
        else{
                y = currY;
        }
        if(pacX > currX){
                x = currX++;
        }
        else if( pacX > currX){
                x = currX--;
        }
        else{
                x = currX;
        }
       yx[0] = y;
       yx[1] = x;
	return yx;
}



int * pinky(int pacY, int pacX, int currY, int currX){
	int y = 0;
	int x = 0;
	int yx[3];
	if(pacY < currY){
		y = currY++;
		if(pacX > currX){
			x = currX++;
		}
		else{
			x = currX --;
		}
	}
	else{
		y = currY--;
		 if(pacX > currX){
                        x = currX--;
                }
                else{
                        x = currX ++;
                }
	}
	yx[0] = y;
	yx[1] = x;
	return yx;
}


int * inky(int pacY, int pacX, int currY, int currX){
        int y = 0;
        int x = 0;
        int yx[3];
	if( pacY > currY){
		y = currY--;
	}
	if(pacY <= currY){
		y = currY++;
	}
	if(pacX > currX){
		x = currX--;
	}
	if( pacX <= currX){
		x = currX++;
	}
	yx[0] = y;
        yx[1] = x;
        return yx;
}

int * clyde(int currY, int currX){
int nMax = 4;
int nMin = 1;
int yx[3];
srand(time(NULL));

int nRandomNumber = rand()%((nMax+1)-nMin) + nMin;
printf("%d\n",nRandomNumber);
if(nRandomNumber == 1){
	currY++;
	currX++;
}
else if(nRandomNumber == 2){
	currY--;
	currX--;
}
else if(nRandomNumber == 3){
	currY++;
	currX--;
}
else{
	currY--;
	currX--;
}
yx[0] = currY;
yx[1] = currX;
return yx;
}

