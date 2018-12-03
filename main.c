#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* for sleep() */
#include <curses.h>
#include  "player.h"
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

void init_win_params(PAC *p_win);
void print_win_params(PAC *p_win);
void makeBoard();
void Movement(PAC win, int ch);
void nextSquare(PAC *win, int y, int x);

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
	init_win_params(&win);

	//Printing the board
	makeBoard();

	refresh();

	Movement(win, ch);
	ghostBehavior(win, g1);

	endwin(); /* End curses mode */
	return 0;
}

void makeBoard(){
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
}

void Movement(PAC win, int ch){
	mvaddch(win.starty, win.startx, playerToken);
        move(win.starty, win.startx);
        while((ch = getch()) != KEY_BACKSPACE)
        {
	mvaddstr(1,1,"1");
                mvaddch(win.starty, win.startx, ' ');
                switch(ch)
                {
                        case KEY_LEFT:
				nextSquare(&win, 0, -1);
				break;
                        case KEY_RIGHT:
                               nextSquare(&win, 0, 1);
                                break;
                        case KEY_UP:
				nextSquare(&win, -1, 0);
                                break;
                        case KEY_DOWN:
				nextSquare(&win, 1, 0);
                                break;
                }
                mvaddch(win.starty, win.startx, playerToken);
                move(win.starty, win.startx);
		//board[win.starty][win.startx] = 0; this line breaks the left corner
	}
}

void nextSquare(PAC *win, int y, int x){
	mvaddstr(1, 1, "a");
	char next = mvinch(win->starty + y, win->startx + x) & A_CHARTEXT;
	mvaddstr(1, 1, "b");

	switch(next){
		case 'X':
			break;
		case '#':
			score += 40;

		case '*':
			score += 10;

		case ' ':

			win->starty += y;
	mvaddstr(1,1,"c");
			win->startx += x;
	mvaddstr(1,1,"d");
			char points[6];
			sprintf(points, "%d", score);
			mvaddstr(0, 7, points);
	mvaddstr(1,1,"e");
			break;
		default:
			break;
	}
}

void init_win_params(PAC *p_win) {
	p_win->starty = 21;	//<------------------ this is how you determine where it starts
	p_win->startx = 13;
}

void ghostBehavior(GHOST *g, PAC *win){
	if (g->ghostNum == 1){
		blinky(win->starty, win->startx, g->y, g->x);
		char next = mvinch(g->y,g->x) & A_CHARTEXT;
		wmove(win, g->y, g->x);
	}
	else if(g->ghostNum == 2){
		pinky(win->starty, win->startx, g->y, g->x);
		char next = mvinch(g->y,g->x) & A_CHARTEXT;
	}
	else if(g->ghostNum == 3){
		 inky(win->starty, win->startx, g->y, g->x);
		char next = mvinch(g->y, g->x) & A_CHARTEXT;

	}
	else {
		clyde( g->y, g->x);
		char next = mvinch(g->y, g->x) & A_CHARTEXT;

	}
	
}

