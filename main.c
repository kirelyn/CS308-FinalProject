#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* for sleep() */
#include <curses.h>
#include "player.h"
#include "pacman.h"

//make it into an enumeration with three options
char playerToken = '<';

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
void print_win_params(PAC *p_win);
void makeBoard();
void Movement(PAC win, int ch);
void nextSquare(PAC *win, int y, int x);
void startScreen();
void endScreen();
void scoreScreen(char c[]);
void debug();

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
	init_pac(&win);

	//Printing the board
	makeBoard();

	refresh();

	Movement(win, ch);

	//print score- will be once they've eaten all the dots
	endScreen();

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
        while((ch = getch()) != KEY_BACKSPACE && score != 2750) //2750 will be the max score possible
        {
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

void startScreen(){
	system("clear");

}

void endScreen(){
	//clears the screen
	system("clear");

	move(0,0);
	printw("Please enter your initials: ");
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
	file = fopen("Test.txt", "a");
	fprintf(file, "%s %d\n", c, score);
	fclose(file);

	char n[3];
	int points;
	PLAYER p[50];

	file = fopen("Test.txt", "r");
	int counter = 0;

	while(fscanf(file, "%s %d", n, &points) != EOF){
		p[counter].name = n;
		p[counter].score = points;
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
		printw("%d. %s \t %d\n", rank, p[i].name, p[i].score);
	}
debug();
}

void init_pac(PAC *p_win) {
	p_win->starty = 21;
	p_win->startx = 13;
}

void debug(){
	while(getch() != KEY_BACKSPACE){

	}
}
