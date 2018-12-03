#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* for sleep() */
#include <curses.h>

int yBlinky(int pacY, int pacX, int currY, int currX){
       int y = 0;
	 if(pacY > currY){
                currY++;
        }
        else if ( pacY > currY){
                currY--;
        }
        else{
                currY;
        }
	return currY;
}
int xBlinky(int pacY, int pacX, int currY, int currX){
	
        if(pacX > currX){
                currX++;
        }
        else if( pacX > currX){
                currX--;
        }
        
	return currX;
}



int yPinky(int pacY, int pacX, int currY, int currX){
	if(pacY < currY){
		currY++;
	}
	else{
		 currY--;
	}
	return currY;
}

int xPinky(int pacY, int pacX, int currY, int currX){
        if(pacY < currY){ 
             if(pacX > currX){
                       currX++;
               }
                else{
                       currX--;
                }
        }
        else{

                 if(pacX > currX){
                       currX--;
                }
                else{
                       currX++;
                }
        }
	return currX;
}

int yInky(int pacY, int pacX, int currY, int currX){
        if( pacY > currY){
		currY--;
	}
	else{
		 currY++;
	}
	return currY;
}

int xInky(int pacY, int pacX, int currY, int currX){
        if(pacX > currX){
                 currX--;
        }
        else{
                 currX++;
        }
	return currX;

}


int yClyde(int currY, int currX){
int nMax = 4;
int nMin = 1;
srand(time(NULL));

int nRandomNumber = rand()%((nMax+1)-nMin) + nMin;

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
	return currY;
}

int xClyde(int currY, int currX){
int nMax = 4;
int nMin = 1;
srand(time(NULL));

int nRandomNumber = rand()%((nMax+1)-nMin) + nMin;

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
	return currX;
}



