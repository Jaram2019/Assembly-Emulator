#include <stdio.h>
#include <gb/gb.h>
#include <gb/drawing.h>


unsigned char menu = 0;
unsigned char menucursor = 0;
unsigned char cursorx = 0;
unsigned char cursory = 0;
unsigned char current[40][36];
unsigned char next[40][36];

void clear(){
	box(0, 0, 159, 143, 3);
}

void startmenu(){
	gotogxy(4,3);
	gprintf("Conway's");
	gotogxy(4,4);
	gprintf("Game of Life");
	gotogxy(6,10);
	gprintf("Draw Map");
	gotogxy(6,11);
	gprintf("Start");
	if(!menucursor){
		gotogxy(5,11);
		gprintf(" ");
		box(40,82,43,85,1);
	}
	else{
		gotogxy(5,10);
		gprintf(" ");
		box(40,90,43,93,0);
	}
	menu = 0;
}

void clearcurrent(){
	int i=0,j=0;
	while(i<40){
		while(j<36){
			current[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
}

void clearnext(){
	int i=0,j=0;
	while(i<40){
		while(j<36){
			next[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
}

void grid(){
	int i=0,j=0;
	while(i<41){
		line(i*4,0,i*4,143);
		i++;
	}
	while(j<37){
		line(0,j*4,159,j*4);
		j++;
	}
}

void printmap(){
	int i=0,j=0;
	while(i<40){
		while(j<36){
			if(current[i][j]){
				color(RGB_WHITE,RGB_WHITE,0);
				box(i*4,j*4,i*4+4,j*4+4, 3);
				color(RGB_WHITE,RGB_BLACK,0);
			}
			else{
				box(i*4,j*4,i*4+4,j*4+4, 3);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void drawmenu(){
	line(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4);
	line(cursorx*4+4,cursory*4,cursorx*4,cursory*4+4);
}
void update(){
	int i=0,j=0;
	while(i<40){
		while(j<36){
			if(current[i][j]){
				if(i>0){
					next[i-1][j]++;
					if(j>0){
						next[i-1][j-1]++;
					}
					if(j<35){
						next[i-1][j+1]++;
					}
				}
				if(j>0){
					next[i][j-1]++;
					if(i<39){
						next[i+1][j-1]++;
					}
				}
				if(j<35){
					next[i][j+1]++;
					if(i<39){
						next[i+1][j+1]++;
					}
				}
				if(i<39){
					next[i+1][j]++;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	i=0,j=0;
	while(i<40){
		while(j<36){
			if(current[i][j]){
				if(next[i][j]<2 || next[i][j] > 3){
					current[i][j] = 0;
				}
			}
			else{
				if(next[i][j] == 3){
					current[i][j] = 1;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int main()
{
	clear();
	clearcurrent();
	clearnext();
	//startmenu();
	while(1){
		if(menu == 0){
			startmenu();
			if (joypad() == J_DOWN && menucursor == 0)
				menucursor = 1;
			else if (joypad() == J_UP && menucursor == 1)
				menucursor = 0;
			else if (joypad() == J_A){
				if(menucursor){
					menu = 2;
				}
				else{
					menu = 1;
				}
				clear();
				grid();
				printmap();
			}
		}
		else if(menu == 1){
			drawmenu();
			if (joypad() == J_DOWN && cursory <36){
				if(current[cursorx][cursory] == 1){
					color(RGB_WHITE,RGB_WHITE,0);
				}
				else{
					color(RGB_WHITE,RGB_BLACK,0);
				}
				box(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4,3);
				cursory++;
				waitpadup();
			}
			else if (joypad() == J_UP && cursory > 0){
				if(current[cursorx][cursory] == 1){
					color(RGB_WHITE,RGB_WHITE,0);
				}
				else{
					color(RGB_WHITE,RGB_BLACK,0);
				}
				box(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4,3);
				cursory--;
				waitpadup();
			}
			else if (joypad() == J_LEFT && cursorx > 0){
				if(current[cursorx][cursory] == 1){
					color(RGB_WHITE,RGB_WHITE,0);
				}
				else{
					color(RGB_WHITE,RGB_BLACK,0);
				}
				box(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4,3);
				cursorx--;
				waitpadup();
			}
			else if (joypad() == J_RIGHT && cursorx <40){
				if(current[cursorx][cursory] == 1){
					color(RGB_WHITE,RGB_WHITE,0);
				}
				else{
					color(RGB_WHITE,RGB_BLACK,0);
				}
				box(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4,3);
				cursorx++;
				waitpadup();
			}
			else if (joypad() == J_START){
				menu = 0;
				clear();
			}
			else if (joypad() == J_A){
				current[cursorx][cursory] = 1;
				color(RGB_BLACK,RGB_BLACK,0);
				box(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4, 3);
				color(RGB_WHITE,RGB_BLACK,0);
			}
			else if (joypad() == J_B){
				current[cursorx][cursory] = 0;
				box(cursorx*4,cursory*4,cursorx*4+4,cursory*4+4, 3);
			}
			else if (joypad() == J_SELECT){
				clearcurrent();
				cursorx = 0;
				cursory = 0;
				grid();
			}
		}
		else if(menu == 2){
			if (joypad() == J_START){
				menu = 0;
				clear();
			}
			else{
				clearnext();
				update();
				printmap();
				delay(1);
			}
		}
	}
	return 0;
}
