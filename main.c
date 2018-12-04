#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include "player.h"
#include "pacman.h"
#include "ghost.h"

char playerToken = '<';
char ghostToken = '+';
int score = 0;

typedef enum boardToken{
	Points = 42,
	Powerup = 35,
	Empty = 32,
	Barrier = 45,
	Blinky = 43,
	Inky = 43,
	Pinky = 43,
	Clyde = 43,
	Pacman = 60,
	Wall = 88
}boardToken;

typedef enum State{
	Start,
	Board,
	Play,
	End,
	Quit
}State;

State state = Start;

boardToken board[25][26] = {
         {Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall},
         {Wall,Powerup,Points,Points,Points,Points,Points,Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall,Points,Points,Points,Points,Points,Powerup,Wall},
         {Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall},
         {Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall},
         {Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Points,Points,Points,Points,Points,Points,Wall,Wall,Points,Points,Points,Points,Points,Points,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Points,Points,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Points,Points,Wall},
         {Wall,Points,Points,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Points,Points,Wall},
         {Wall,Wall,Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Barrier,Barrier,Barrier,Barrier,Barrier,Barrier,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Empty,Empty,Inky,Empty,Blinky,Empty,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Points,Points,Points,Wall,Empty,Clyde,Empty,Pinky,Empty,Empty,Wall,Points,Points,Points,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Points,Points,Points,Points,Points,Points,Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall,Points,Points,Points,Points,Points,Points,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall,Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall},
         {Wall,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Pacman,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Wall},
         {Wall,Points,Wall,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Wall,Points,Wall},
         {Wall,Points,Wall,Wall,Wall,Points,Wall,Wall,Points,Points,Points,Points,Wall,Wall,Points,Points,Points,Points,Wall,Wall,Points,Wall,Wall,Wall,Points,Wall},
         {Wall,Points,Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Points,Wall,Wall,Points,Wall,Wall,Wall,Points,Wall},
         {Wall,Powerup,Points ,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Points,Powerup,Wall},
         {Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall},
};

void init_pac(PAC *p_win);
void setGhosts(GHOST *g, int y, int x);
void print_win_params(PAC *p_win);
void makeBoard();
void play(PAC win, int ch, GHOST *g1, GHOST *g2, GHOST *g3, GHOST *g4);
void nextSquare(PAC *win, int y, int x);
int nextGhost(GHOST *g,PAC *win);
void startScreen();

void endScreen();
void scoreScreen(char c[]);
void pauseLoop();

int main(int argc, char *argv[]) {
	PAC win;
	GHOST g1;
	g1.ghostNum = 1;
	GHOST  g2;
	g2.ghostNum = 1;
	GHOST g3;
	g3.ghostNum = 2;
	GHOST g4;
	g4.ghostNum = 3;

	int ch;

	initscr();
	keypad(stdscr, TRUE);
	noecho();

	/* Initialize the window parameters */
	init_pac(&win);

	setGhosts(&g1, 14, 11);
	setGhosts(&g2, 13, 12);
	setGhosts(&g3, 14, 13);
	setGhosts(&g4, 13, 14);

	while(true){
		switch(state){
			case Start:
				startScreen();
				break;
			case Board:
				makeBoard();
				break;
			case Play:
				play(win, ch, &g1, &g2, &g3, &g4);
				break;
			case End:
				endScreen();
				break;
			case Quit:
			default:
				endwin();
				return 0;
				break;
		}
	}
	endwin();
	return 0;
}

void makeBoard(){
	move(0,0);
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	refresh();
	printw("Score: %d\n\n", score);
	for(int i = 0; i < 25; i++){
                for(int j = 0; j < 26; j++){
			boardToken bt = board[i][j];
			switch(bt){
				case Wall:
					addch(bt | COLOR_PAIR(1));
					break;
				case Powerup:
					addch(bt | COLOR_PAIR(2));
					break;
				default:
					addch(bt);
			}
			refresh();
		}
                printw("\n");
        }
	refresh();
	state = Play;
}

void play(PAC win, int ch, GHOST * g1, GHOST *g2, GHOST *g3, GHOST *g4 ){
	mvaddch(g1->y, g1->x, ghostToken);
	mvaddch(g2->y, g2->x, ghostToken);
	mvaddch(g3->y, g3->x, ghostToken);
	mvaddch(g4->y, g4->x, ghostToken);

	score = 0;
        move(win.starty, win.startx);
	int hasLost = 0;
        while((ch = getch()) != KEY_BACKSPACE && score != 2750 && hasLost < 1) //2750 will be the max score possible
        {
                mvaddch(win.starty, win.startx, ' ');
		switch(ch)
                {
                        case KEY_LEFT:
				nextSquare(&win, 0, -1);
				hasLost += nextGhost(g1, &win);
				hasLost += nextGhost(g2, &win);
				hasLost +=nextGhost(g3, &win);
				nextGhost(g4, &win);
				break;
                        case KEY_RIGHT:
                                nextSquare(&win, 0, 1);
				hasLost += nextGhost(g1, &win);
                                hasLost += nextGhost(g2, &win);
				hasLost += nextGhost(g3, &win);
				hasLost += nextGhost(g4, &win);
                                break;
                        case KEY_UP:
				nextSquare(&win, -1, 0);
				hasLost += nextGhost(g1, &win);
                                hasLost += nextGhost(g2, &win);
				hasLost += nextGhost(g3, &win);
				hasLost += nextGhost(g4, &win);
                                break;
                        case KEY_DOWN:
				nextSquare(&win, 1, 0);
				hasLost += nextGhost(g1, &win);
                                hasLost += nextGhost(g2, &win);
				hasLost += nextGhost(g3, &win);
				hasLost += nextGhost(g4, &win);
				break;
                }
                mvaddch(win.starty, win.startx, playerToken);
		mvaddch(g1->y, g1->x, ghostToken);
		mvaddch(g2->y, g2->x, ghostToken);
		mvaddch(g3->y, g3->x, ghostToken);
		mvaddch(g4->y, g4->x, ghostToken);
                move(win.starty, win.startx);
	}
	state = End;
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

int  nextGhost(GHOST *g, PAC *win){ 
	if(abs(g->y - win->starty) == 0 && abs(g->x - win->startx) == 1){
		return 1;
	}
	if(abs(g->y - win->starty) == 1 && abs(g->x - win->startx) == 0){
		return 1;
	}
	int y = 0;
	int x = 0;
	if(g->ghostNum == 1){
		//implement blinky
		if(abs(win->starty - g->y) < abs(win->startx - g->x)){
			//move y
			char next = mvinch(g->y + 1, g->x + x) & A_CHARTEXT;
			if(win->starty >  g->y && next != 'X' ){
				y = 1;
			}
			else{
				y=-1;
			}
		}
		else{
			//move x
			char next = mvinch(g->y + y, g->x + 1) & A_CHARTEXT;
			if(win->startx > g->x && next != 'X'){
				x=1;
			}
			else{
				x=-1;
			}
		}

	}
	else if(g->ghostNum == 2){
		//implement pinky
		 if(abs(win->starty - g->y) < abs(win->startx - g->x)){
                        //move x
			char next = mvinch(g->y + y, g->x + 1) & A_CHARTEXT;
			if(win->startx > g->x && next != 'X'){
                                x=1;
                        }
                        else{
                                x=-1;
                	}

                }
                else{
                        //move y
			 char next = mvinch(g->y + 1, g->x + x) & A_CHARTEXT;
			if(win->starty >  g->y && next != 'X'){
                               y=1;
                        }
                        else{
                               y=-1;
                        }
		}

	}
	else if(g->ghostNum == 3){
		//implement inky
		 if(abs(win->starty - g->y) < abs(win->startx - g->x)){
                        //move y
			 char next = mvinch(g->y + 1, g->x + x) & A_CHARTEXT;
			if(win->starty < 13 && next != 'X'){
                                y=1;
                        }
                        else{
                                y=-1;
                	}

                }
                else{
                        //move x
			char next = mvinch(g->y + y, g->x + 1) & A_CHARTEXT;
			if(win->startx < 13 && next != 'X' ){
                                x=1;
                        }
                        else{
                                x=-1;
               		 }

                }
	}
	else{
		//implement clyde
		if(g->y > win->starty){
			 char next = mvinch(g->y + 1, g->x + x) & A_CHARTEXT;
			if( g->y > win->starty && next != 'X' ){
				y = 1;
			}
			else{
				y=-1;
			}
		}
		else{
			//move x
			 char next = mvinch(g->y + y, g->x + 1) & A_CHARTEXT;
			if(win->startx < g->x && next != 'X' ){
				x=1;
			}
			else{
				x=-1;
			}
		}
	}
	char next = mvinch(g->y + y, g->x + x) & A_CHARTEXT;

        switch(next){
                case 'X':
                        break;
                case '#':
			

                case '*':

		case '-':


                case ' ':
			mvaddch(g->y, g->x, g->lastChar);
			g->lastChar = next;
                        g->y += y;
                        g->x += x;
                        break;
                default:
                        break;
        }
	//mvaddch(g->y, g->x, g);
	return FALSE;
}


void startScreen(){
	system("clear");

	move(0,0);
	printw("Pac-Man \n \n");

	mvaddstr(3, 0, "-Start Game-");
	mvaddstr(4, 0, "-End Game-");
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
		state = Board;
	}
	else{ //user selects End Game
		state = Quit;
	}
}

void endScreen(){
	clear();
	system("clear");
	move(0,0);

	printw("Please enter your initials and press Backspace to continue...  ");
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
	state = Start;
}

void scoreScreen(char c[]){
	move(4,0);
	printw("High-Scores:");
	move(5,0);
	FILE *file;
	file = fopen("PastScores.txt", "a");
	fprintf(file, "%s %d\n", c, score);
	fclose(file);

	int points;
	PLAYER p[50];
	file = fopen("PastScores.txt", "r");
	int counter = 0;

	while(fscanf(file, "%s %d", &p[counter].name, &p[counter].score) != EOF){
		counter++;
	}

	//Putting the array in descending order for easier printing
	for(int i = 0; i < counter; i++){
		for(int j = i + 1; j < counter; j++){
			if(p[i].score < p[j].score){
				char* tempN = p[i].name;
				int tempP = p[i].score;
				p[i].name = p[j].name;
				p[i].score = p[j].score;
				p[j].name = tempN;
				p[j].score = tempP;
			}
		}
	}

	//Print score to screen in order
	for(int i = 0; i < 10 && i < counter; i++){
		int rank = i + 1;
		if(rank == 10){
			printw("%d.  %s    %d\n", rank, &p[i].name, p[i].score);
		}
		else{
			printw("%d.   %s    %d\n", rank, &p[i].name, p[i].score);
		}
	}
	move(20,0);
	printw("Press Backspace to continue...");
	pauseLoop();
}

void pauseLoop(){
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
	g->lastChar = ' ';
}




