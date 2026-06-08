#include <stdio.h>
#include <math.h>

#define VLINE 179  // │
#define HLINE 196  // ─
#define BL    192  // └
#define UP_ARROW    24   // ↑
#define DOWN_ARROW 25 // ↓
#define RIGHT_ARROW 26
#define LEFT_ARROW  27
#define RIGHT 26   // →


void Plane(int rows, int cols){
	if(rows <= 0 || cols <= 0){
		printf("Values are Invalid");
		return;
	}

	int x_neg = cols / 2;
	int x_pos = x_neg;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < x_neg; j++){
			printf("  ");
		}
		if(i == 0){
			/* y-axis label */
			printf("Y\n");
		}else{
			/* Y-axis arrow */
			printf("%c\n", UP_ARROW);
		}
	}

	for(int i = 0; i < x_neg; i++){
		for(int j = 0; j < x_neg; j++){
			printf("  ");
		}
		printf("%c\n", VLINE);

	}

	printf("X%c", LEFT_ARROW);

	for(int i = 0; i < rows; i++)
		printf("%c", HLINE);

	printf("%c", 197);   // intersection

	for(int i = 0; i < rows; i++)
		printf("%c", HLINE);

	printf("%c X", RIGHT_ARROW);

	for(int i = 0; i < x_pos; i++){
		for(int j = 0; j < x_pos; j++){
			printf("  ");
		}
		printf("%c\n", VLINE);
	}

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < x_neg; j++){
			printf("  ");
		}
		if(i == 1){
			/* y-axis label */
			printf("Y\n");
		}else{
			/* Y-axis arrow */
			printf("%c\n", DOWN_ARROW);
		}
	}
}

int main(){

	int row, col;

	printf("Enter row: ");
	scanf("%d", &row);

	printf("Enter col: ");
	scanf("%d", &col);

	Plane(row,col);

	return 0;
}
