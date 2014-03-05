
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
  int r;
  int c;
} square;

char *repeatStr(char *partial, int times){
  int partialSize = strlen(partial);
  int i, j;
  int c = 0;
  char *newstring = (char *)malloc(partialSize*times+1);
  for(i=0; i<times; i++){
	for(j=0; j<partialSize; j++){
	  newstring[c] = partial[j];
	  c++;
	}
  }
  newstring[i*j+1] = '\0';
  return newstring;
}

char *printRow(int row[], int size){
  char *rowStr = (char *)malloc(size*4+3);
  /* Plus 3 for |,  \n,  and \0 characters */
  int i;
  for(i=0; i<size; i++){
	if(i % 3 == 0)
	  rowStr[i*4] = '|';
	else
	  rowStr[i*4] = ':';
	rowStr[i*4+1] = ' ';
	if (row[i] > 0)
	  rowStr[i*4+2] = '0'+row[i];
	else
	  rowStr[i*4+2] = ' ';
	rowStr[i*4+3] = ' ';
	
  }
  rowStr[size*4] = '|';
  rowStr[size*4+1] = '\n';
  rowStr[size*4+2] = '\0';
  return rowStr;
}

void printSudoku(int **board){
  int r;
  char strboard[19*38+1];
  char *majorborder = repeatStr("+===", 9);
  char *minorborder = repeatStr("+---", 9);
  for(r=0; r<9; r++){
	if (r%3==0){
	  printf ("%s+\n",majorborder);
	}else{
	  printf ("%s+\n",minorborder);
	}
	printf ("%s",printRow(board[r], 9));
  }
  printf ("%s+\n",majorborder);
}

int *cparray(int *a, int size){
  int i;
  int *newarray = (int *)malloc(sizeof(int)*size);
  for(i=0; i<size; i++){
	newarray[i] = a[i];
  }
  return newarray;
}

int *d1(int s){
  return (int *)malloc(sizeof(int)*s);
}

int **d2(int s){
  /* Does almost the same thing as d1, but int * is 8 bytes and int is just 4 */
  return (int **) malloc(sizeof(int *)*s);
}

int **cpsudoku(int **board){
  int **newboard = d2(9);
  int r, c;
  for(r=0; r<9; r++){
	newboard[r] = (int *)malloc(sizeof(int)*9);
	for(c=0; c<9; c++){
	  newboard[r][c] = board[r][c];
	}
  }
  return newboard;
}

int **boardFromS(char *boardStr){
  int r, c, i;
  int **board = d2(9);
  for(r=0, i=0; r<9; r++){
	board[r] = d1(9);
	for(c=0; c<9; c++, i++){
	  board[r][c] = boardStr[i] - '0';
	}
	i++;						/* to skip the newline char */
  }
  return board;
}

int **boardFromF(char *fname){
  /* Read sudoku board from a text file!!!!!! */
  FILE *fp = fopen(fname, "r");
  fseek(fp, 0, SEEK_END);
  int s = ftell(fp);
  rewind(fp);
  char *sboard = (char *)malloc(sizeof(char) * s);
  fread(sboard, sizeof(char), s, fp);
  return boardFromS(sboard);
}

int inary(int *ary, int size, int el){
  int i;
  for(i=0; i<size; i++){
	if (el == ary[i])
	  return 1;
  }
  return 0;
}

int *fillAry(int el, int size){
  int *a = d1(size);
  int i;
  for(i=0; i<size; i++){
	a[i] = el;
  }
  return a;
}

int colIsValid(int **board, int col, int size){
  int i;
  int colary[size];
  for(i=0; i<size; i++){
	colary[i] = board[i][col];
  }
  return rowIsValid(colary, size);
}
int rowIsValid(int *row, int size){
  int i, c=0;
  int *alreadyThere = fillAry(-1, size);
  for(i=0; i<size; i++){
	if (inary(alreadyThere, size, row[i]))
	  return 0;
	else if(row[i] > 0){
	  alreadyThere[c] = row[i];
	  c++;
	}
  }
  return 1;
}

int boxIsValid(int **board, int r, int c){
  int rcorner = r - r%3;
  int ccorner = c - c%3;
  int i, j, count;
  int boxary[9];
  for(i=0, count=0; i<3; i++){
	for(j=0; j<3; j++, count++){
	  boxary[count] = board[rcorner+i][ccorner+j];
	}
  }
  return rowIsValid(boxary, 9);
}

int validAtSquare(int **board, square sq){
  int r = sq.r;
  int c = sq.c;
  return colIsValid(board, c, 9) && rowIsValid(board[r], 9) && boxIsValid(board, r, c);
}

int getSq(int **board, square sq){
  return board[sq.r][sq.c];
}

int **setSq(int **board, square sq, int val){
  /* Mutates the board but also returns it... fake functional */
  board[sq.r][sq.c] = val;
  return board;
}

int sqe(square sq, int r, int c){
  return sq.r == r && sq.c == c;
}

square newSq(int r, int c){
  square sq;
  sq.r=r;
  sq.c=c;
  return sq;
}

square nxtSqXXX(square sq){
  if (sq.c == 8)
	return newSq(sq.r+1, 0);
  return newSq(sq.r, sq.c+1);
}

square nxtSq(int **board, square sq){
  if (sqe(sq, 8, 8) || getSq(board, sq) == 0)
	return sq;
  if (sq.c == 8)
	return nxtSq(board, newSq(sq.r+1, 0));
  return nxtSq(board, newSq(sq.r, sq.c+1));
	  
}

int **solveSudoku(int **board, square sq, int numtabs){
  sq = nxtSq(board, sq);
  if (sqe(sq, 8, 8) && getSq(board, sq) > 0)
	return board;
  int i;
  for(i=1; i<10; i++){
	if(validAtSquare(setSq(board, sq, i), sq)){
	  square nsq = nxtSq(board, sq);
	  int **nxtboard = solveSudoku(cpsudoku(board), nsq, numtabs+1);
	  if (getSq(nxtboard, nsq) != -1)
		return nxtboard;
	}
  }
  return setSq(board, sq, -1);
}

int **readBoard(){
  int **board = d2(9);
  int i=0, j=0;
  char c;
  for(i=0; i<9; i++){
	board[i] = d1(9);
	for(j=0; j<10; j++){
	  c = getchar() - '0';
	  if (j<9)
		board[i][j] = c;
	}
  }
  return board;
}

int main(int argc, char **argv){
  int **board = readBoard();
  printSudoku(board);
  printSudoku(solveSudoku(board, newSq(0,0), 0));
}
