#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include "player.h"
#include "pacman.h"
#include "ghost.h"
//#include "ghost.c"

//make it into an enumeration with three options
char playerToken = '<';
char ghostToken = '+';
int score = 0;

int board[25][26] = {
         {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
         {32, 2, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 2,32},
         {32, 1,32,32,32,32, 1,32, 1,32,32,32,32,32,32,32,32, 1,32, 1,32,32,32,32, 1,32},
         {32, 1,32,32,32,32, 1,32, 1,32,32,32,32,32,32,32,32, 1,32, 1,32,32,32,32, 1,32},
         {32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32},
         {32,32,32, 1,32,32, 1,32,32,32,32, 1,32,32, 1,32,32,32,32, 1,32,32, 1,32,32,32},
         {32,32,32, 1,32,32, 1, 1, 1, 1, 1, 1,32,32, 1, 1, 1, 1, 1, 1,32,32, 1,32,32,32},
         {32, 1, 1, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 1, 1, 1,32},
         {32, 1, 1, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 1, 1, 1,32},
         {32,32,32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32,32,32,32,32,32, 1,32, 1,32,32,32,32, 1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32, 7, 3,15, 3, 3, 3,32, 1,32,32,32,32, 1,32,32,32},
         {32,32,32, 1,32,32, 1, 1, 1,32, 3,11, 3,19, 3, 3,32, 1, 1, 1,32,32, 1,32,32,32},
         {32,32,32, 1,32,32, 1,32, 1,32,32,32,32,32,32,32,32, 1,32, 1,32,32, 1,32,32,32},
         {32, 1, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 1,32},
         {32,32,32, 1,32,32,32,32,32,32,32, 1,32,32, 1,32,32,32,32,32,32,32, 1,32,32,32},
         {32,32,32, 1, 1, 1, 1, 1, 1, 1, 1, 1,32,32, 1, 1, 1, 1, 1, 1, 1, 1, 1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 1,32,32,32},
         {32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32},
         {32, 1,32,32,32, 1,32,32,32,32,32, 1,32,32, 1,32,32,32,32,32, 1,32,32,32, 1,32},
         {32, 1,32,32,32, 1,32,32, 1, 1, 1, 1,32,32, 1, 1, 1, 1,32,32, 1,32,32,32, 1,32},
         {32, 1,32,32,32, 1,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32, 1,32,32,32, 1,32},
         {32, 2, 1 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,32},
         {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
};

void init_pac(PAC *p_win);
void setGhosts(GHOST *g, int y, int x);
void print_win_params(PAC *p_win);
void makeBoard();
void Movement(PAC win, int ch, GHOST *g1, GHOST *g2, GHOST *g3, GHOST *g4);
void nextSquare(PAC *win, int y, int x);
void nextGhost(GHOST *g, int y, int x);
int startScreen();
void endScreen();
void scoreScreen(char c[]);
void debug();

int main(int argc, char *argv[]) {
	PAC win;
	GHOST g1;
	g1.ghostNum = 1;
	GHOST  g2;
	g2.ghostNum = 2;
	GHOST g3;
	g3.ghostNum = 3;
	GHOST g4;
	g4.ghostNum = 4;
	int ch;
	initscr();
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Initialize the window parameters */
	init_pac(&win);

	setGhosts(&g1, 3, 2);
	//setGhosts(&g2, 3, 3);
	//setGhosts(&g3, 3, 4);
	//setGhosts(&g4, 3, 5);

	int keepPlaying = startScreen();
	if(keepPlaying == 1){ //user selected Start Game
		makeBoard();
		Movement(win, ch, &g1, &g2, &g3, &g4);
		endScreen();
	}
	else{ //user selected End Game
		endwin();
		return 0;
	}
}

void makeBoard(){
	move(0,0);
	printw("Score: %d\n\n", score);
	for(int i = 0; i < 25; i++){
                for(int j = 0; j < 26; j++){
                        if(board[i][j] == 32){
                                addch('X');
                        }
                        else if(board[i][j] == 1){
                                addch('*');
                        }
                        else{
                                addch('#');

                        }
                        refresh();
                }
                printw("\n");
        }
	refresh();
}

void Movement(PAC win, int ch, GHOST *g1, GHOST *g2, GHOST *g3, GHOST *g4 ){
	mvaddch(g1->y, g1->x, ghostToken);
	mvaddch(win.starty, win.startx, playerToken);
	//mvaddch(g2->y, g2->x, ghostToken);
	//mvaddch(g3->y, g3->x, ghostToken);
	//mvaddch(g4->y, g4->x, ghostToken);
        //move(&win, g1->y, g1->x);
	move(win.starty, win.startx);
	//wmove(&win, g1->y, g1->x);
        while((ch = getch()) != KEY_BACKSPACE && score != 2750) //2750 will be the max score possible
        {
                mvaddch(win.starty, win.startx, ' ');
		mvaddch(g1->y, g1->x, ' ');
		switch(ch)
                {
                        case KEY_LEFT:
				//nextSquare(&win, 0, -1);
				nextGhost(&g1, 0, -1);
				//mvaddch(g1->y, g1->x, ghostToken);
				break;
                        case KEY_RIGHT:
                                nextSquare(&win, 0, 1);
				nextGhost(&g1, 0, 1);
                                break;
                        case KEY_UP:
				nextSquare(&win, -1, 0);
				nextGhost(&g1, -1, 0);
                                break;
                        case KEY_DOWN:
				nextSquare(&win, 1, 0);
				nextGhost(&g1, 1, 0);
				break;
                }
                mvaddch(win.starty, win.startx, playerToken);
                mvaddch(g1->y, g1->x, ghostToken);
		move(win.starty, win.startx);
		move(g1->y, g1->x);
		/*ghostBehavior(&g1, &win);
		ghostBehavior(&g2, &win);
		ghostBehavior(&g3, &win);
		ghostBehavior(&g4, &win);*/
	}
}

void nextSquare(PAC *win, int y, int x){
	char next = mvinch(win->starty + y, win->startx + x) & A_CHARTEXT;

	switch(next){
		case 'X':
			break;
		case '#':
			score += 40;

		case '*':
			score += 10;

		case ' ':

			win->starty += y;
			win->startx += x;
			char points[6];
			sprintf(points, "%d", score);
			mvaddstr(0, 7, points);
			break;
		default:
			break;
	}
}

void nextGhost(GHOST *g, int y, int x){
        char next = mvinch(g->y + y, g->x + x) & A_CHARTEXT;
        switch(next){
                case 'X':
                        break;
                case '#': 
			//mvprintw(g->y, g->x, ' ');
			//mvprintw(g->y, g->x, '+');
			//mvaddch( g->y, g->x, '#');

                case '*':
			//mvprintw(g->y, g->x, ' ');
			//mvprintw(g->y, g->x, '+');
			//mvaddch(g->y, g->x, '*');
                case ' ':
		       //mvprintw(g->y, g->x, '+');
                       //g->y += y;
                       //g->x += x;
		       break; 
                default:
			g->y += y;
			g->x += x;
                        break;
        }
}


int startScreen(){
	system("clear");

	move(0,0);
	printw("Pac-Man \n \n");

	mvaddstr(3, 1, "Start Game");
	mvaddstr(4, 1, "End Game");
	move(10, 0);
	printw("Created by: Kennedy Griffin and Kassidy Zeiler");

	move(3,0);
	int ch;
	int position = 3;
	while((ch = getch()) != KEY_BACKSPACE){
		switch(ch){
			case KEY_UP:
				if(position != 3){
					position--;
				}
				break;
			case KEY_DOWN:
				if(position != 4){
					position++;
				}
				break;
			default:
				break;
		}
		move(position,0);
	}
	if(position == 3){ //user selects Start Game
		system("clear");
		return 1;
	}
	else{ //user selects End Game
		return 0;
	}
}

void endScreen(){
	system("clear");
	move(0,0);

	printw("Please enter your initials and hit Backspace when finished:  ");
	char letters[3] = {'A', 'A', 'A'};
	int ch;
	int position = 0;

	do{
		switch(ch){
			case KEY_LEFT:
				if(position > 0){
					position--;
				}
				break;
			case KEY_RIGHT:
				if(position < 2){
					position++;
				}
				break;
			case KEY_UP:
				if(letters[position] == 'A'){
					letters[position] = 'Z';
				}
				else{
					letters[position]--;
				}
				break;
			case KEY_DOWN:
				if(letters[position] == 'Z'){
					letters[position] = 'A';
				}
				else{
					letters[position]++;
				}
				break;
			default:
				break;
		}
		mvaddch(1, 7, letters[0]);
		mvaddch(1, 8, letters[1]);
		mvaddch(1, 9, letters[2]);

		move(1, position + 7);
	}while((ch = getch()) != KEY_BACKSPACE);

	scoreScreen(letters);
	startScreen();
}

void scoreScreen(char c[]){
	move(5,0);
	FILE *file;
	file = fopen("PastScores.txt", "a");
	fprintf(file, "%s %d\n", c, score);
	fclose(file);

	char n[3];
	int points;
	PLAYER p[50];
	file = fopen("PastScores.txt", "r");
	int counter = 0;
debug();
	while(fscanf(file, "%s %d", n, &points) != EOF){
		strncpy(p[counter].name, n, 3); // <-----------------need to fix and in the loop below
	//	p[counter].name = n;
		p[counter].score = points;
		counter++;
	}
debug();

	//Putting the array in descending order for easier printing
	for(int i = 0; i < counter; i++){
		for(int j = i + 1; j < counter; j++){
			if(p[i].score < p[j].score){
				char* tempN; // = p[i].name;
			strcpy(tempN, p[i].name);
				int tempP = p[i].score;
			strcpy(p[i].name, p[j].name);
			//	p[i].name = p[j].name;
				p[i].score = p[j].score;
			strcpy(p[j].name, tempN);
			//	p[j].name = &tempN;
				p[j].score = tempP;
			}
		}
	}
debug();
	//Print score to screen in order
	for(int i = 0; i < 10 && i < counter; i++){

		int rank = i + 1;
		printw("%d. %s \t %d\n", rank, p[i].name, p[i].score);
	}
debug();

}

void debug(){ // for testing purposes and will be removed before final code is submitted
	while(getch() != KEY_BACKSPACE){

	}
}

void init_pac(PAC *p_win) {
	p_win->starty = 21;
	p_win->startx = 13;
}

void setGhosts(GHOST *g, int y, int x){
	g->y = y;
	g->x = x;
	
}
void ghostBehavior(GHOST *g, PAC *win){
	int y = 0;
	int x = 0;
	//mvaddch(3, 2, ghostToken);
	if (g->ghostNum == 1){
		y = yBlinky(win->starty, win->startx, g->y, g->x);
		x = xBlinky(win->starty, win->startx, g->y, g->x);
		//wmove(&g, y, x);
		 char next = mvinch(win->starty + y, win->startx + x) & A_CHARTEXT;
	}
	else if(g->ghostNum == 2){
		y = yPinky(win->starty, win->startx, g->y, g->x);
		x = xPinky(win->starty, win->startx, g->y, g->x);
                //wmove(&g, y, x);
		 char next = mvinch(win->starty + y, win->startx + x) & A_CHARTEXT;

	}
	else if(g->ghostNum == 3){
		y = yInky(win->starty, win->startx, g->y, g->x);
                x = xInky(win->starty, win->startx, g->y, g->x);
                //wmove(&g, y, x);
		 char next = mvinch(win->starty + y, win->startx + x) & A_CHARTEXT;
		

	}
	else {
		y = yClyde( g->y, g->x);
		x = xClyde( g->y, g->x);
		//wmove(&g,  y, x);
		 char next = mvinch(win->starty + y, win->startx + x) & A_CHARTEXT; 

		}
	
}



