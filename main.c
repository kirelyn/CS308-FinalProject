#include <stdlib.h>
# include <stdio.h> 
#include <unistd.h> /* for sleep() */
#include <curses.h>
#include <player.h>
#include <pacman.h>

char playerToken = '<';


int board[25][26] = {
         {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
         {32, 2, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 
2,32},
         {32, 1,32,32,32,32, 1,32, 1,32,32,32,32,32,32,32,32, 1,32, 1,32,32,32,32, 
1,32},
         {32, 1,32,32,32,32, 1,32, 1,32,32,32,32,32,32,32,32, 1,32, 1,32,32,32,32, 
1,32},
         {32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1,32},
         {32,32,32, 1,32,32, 1,32,32,32,32, 1,32,32, 1,32,32,32,32, 1,32,32, 
1,32,32,32},
         {32,32,32, 1,32,32, 1, 1, 1, 1, 1, 1,32,32, 1, 1, 1, 1, 1, 1,32,32, 
1,32,32,32},
         {32, 1, 1, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 1, 1, 
1,32},
         {32, 1, 1, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 1, 1, 
1,32},
         {32,32,32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32,32,32,32,32,32, 1,32, 1,32,32,32,32, 
1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32, 7, 3,15, 3, 3, 3,32, 1,32,32,32,32, 
1,32,32,32},
         {32,32,32, 1,32,32, 1, 1, 1,32, 3,11, 3,19, 3, 3,32, 1, 1, 1,32,32, 
1,32,32,32},
         {32,32,32, 1,32,32, 1,32, 1,32,32,32,32,32,32,32,32, 1,32, 1,32,32, 
1,32,32,32},
         {32, 1, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,32, 1, 1, 1, 1, 1, 
1,32},
         {32,32,32, 1,32,32,32,32,32,32,32, 1,32,32, 1,32,32,32,32,32,32,32, 
1,32,32,32},
         {32,32,32, 1, 1, 1, 1, 1, 1, 1, 1, 1,32,32, 1, 1, 1, 1, 1, 1, 1, 1, 
1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 
1,32,32,32},
         {32,32,32, 1,32,32,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32,32,32, 
1,32,32,32},
         {32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1,32},
         {32, 1,32,32,32, 1,32,32,32,32,32, 1,32,32, 1,32,32,32,32,32, 1,32,32,32, 
1,32},
         {32, 1,32,32,32, 1,32,32, 1, 1, 1, 1,32,32, 1, 1, 1, 1,32,32, 1,32,32,32, 
1,32},
         {32, 1,32,32,32, 1,32,32, 1,32,32,32,32,32,32,32,32, 1,32,32, 1,32,32,32, 
1,32},
         {32, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
2,32},
         {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
 };
void init_win_params(PAC *p_win); 
void print_win_params(PAC *p_win); 
int main(int argc, char *argv[]) {
	PAC win;
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
	//Movement
	mvaddch(win.starty, win.startx, playerToken);
	move(win.starty, win.startx);
	while((ch = getch()) != KEY_BACKSPACE)
	{
		mvaddch(win.starty, win.startx, ' ');
		switch(ch)
		{
			case KEY_LEFT:
				if(board[win.starty][win.startx - 1] != 32){
					--win.startx;
					//increment score
				}
				break;
			case KEY_RIGHT:
				if(board[win.starty][win.startx + 1] != 32){
					++win.startx;
				}
				break;
			case KEY_UP:
				if(board[win.starty - 1][win.startx] != 32){
					--win.starty;
				}
				break;
			case KEY_DOWN:
				if(board[win.starty + 1][win.startx] != 32){
					++win.starty;
				}
				break;
		}
		mvaddch(win.starty, win.startx, playerToken);
		move(win.starty, win.startx);
		board[win.starty][win.startx] = 0; //<------------------ will be used 
for scoring purposes
	}
	endwin(); /* End curses mode */
	return 0;
}
void init_win_params(PAC *p_win) {
	p_win->starty = 19;	//<------------------ this is how you determine where it starts
	p_win->startx = 13;
}
