#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

void PrintBoard(int** arrBoard, int x, int y, int round, int boardSize); //함수6개 선언
int CheckBoard(int x, int y, int boardSize);
int CheckPlace(int** arrBoard, int x, int y);
int CheckGomoku(int** arrBoard, int x, int y, int round, int boardSize);
int CheckThreeAndThree(int** arrBoard, int x, int y, int round, int boardSize);
int check22(int** arrBoard, int x, int y, int num1, int num2, int boardSize); //새로 추가한 함수

int main(void)
{
	int** arrBoard;
	int round = 0;
	int x = 0, y = 0;
	char input;
	int boardSize;
	int i, j;

	printf("보드의 크기를 입력해주세요: ");
	scanf("%d", &boardSize);

	system("cls");
	arrBoard = (int**)malloc(sizeof(int*) * boardSize);  
	//boardSize를 입력받아서 그 크기만큼 2차원 배열 arrBoard의 크기를 동적으로 할당해준다.
	for (i = 0; i < boardSize; i++) 
	// 2차원 배열을 전부 한번에 할당할 수 없으므로 for문을 이용해 한번 더 할당해준다
	{
		arrBoard[i] = (int*)malloc(sizeof(int) * boardSize);
	}
	for (i = 0; i < boardSize; i++)
	//for문을 이용해 arrBoard의 값을 2로 초기화시켜준다
	{
		for (j = 0; j < boardSize; j++)
			arrBoard[i][j] = 2;
	}

	do {                                    //비어있지 않으면 반복
		while ((input = _getch()) != '\r' || !CheckPlace(arrBoard, x, y) || CheckThreeAndThree(arrBoard, x, y, round, boardSize))
//엔터를 입력받고 x,y자리에 흑,백돌이 없고, 흑돌이 삼삼이 아니면 while문 탈출
		{
						
			switch (input)
			{//입력받은 input값이 a,w,d,s중 하나이면 밑의 case를 실행
			case 'a':  //a를 입력하면 x를 1 감소시키고 바둑판 밖으로 나가면 다시 1 증가
				x -= 1;
				if (CheckBoard(x, y, boardSize) == 0)
				{
					x += 1;
					break;
				}
				break;
			case 'w': //w를 입력하면 y를 1 감소시키고 바둑판 밖으로 나가면 다시 1 증가
				y -= 1;
				if (CheckBoard(x, y, boardSize) == 0)
				{
					y += 1;
					break;
				}
				break;
			case 'd': //d를 입력하면 x를 1 증가시키고 바둑판 밖으로 나가면 다시 1 감소
				x += 1;
				if (CheckBoard(x, y, boardSize) == 0)
				{
					x -= 1;
					break;
				}
				break;
			case 's': //s를 입력하면 y를 1 증가시키고 바둑판 밖으로 나가면 다시 1 감소
				y += 1;
				if (CheckBoard(x, y, boardSize) == 0)
				{
					y -= 1;
					break;
				}
				break;
			}
			system("cls");
			PrintBoard(arrBoard, x, y, round, boardSize); //while반복할 때마다 계속 실행
		}
		if (round % 2) //round가 짝수이면 흑돌입력, 홀수이면 백돌입력
			arrBoard[y][x] = 1;//백돌
		else
			arrBoard[y][x] = 0;//흑돌

		system("cls");

		PrintBoard(arrBoard, x, y, round, boardSize);

	} while (!CheckGomoku(arrBoard, x, y, round++, boardSize)); //오목이 아니면 계속반복

	system("cls");
	PrintBoard(arrBoard, -1, -1, ++round, boardSize); //x,y를 –1,-1에 놓고 승리한 돌 출력
	printf("승리");

	for (i = 0; i < boardSize; i++) //동적으로 할당해준 것 다시 해제
	{
		free(arrBoard[i]);
	}
	free(arrBoard); //두번에 걸쳐서 해제
	return 0;
}

void PrintBoard(int** arrBoard, int x, int y, int round, int boardSize) {
//바둑판의 형태를 출력해주는 PrintBoard함수 정의
	int itr1, itr2;

	for (itr1 = 0; itr1 < boardSize * 2 + 1; itr1++) 
	{ //itr1 0부터 boardSize*2까지 반복
		if (itr1 % 2) // itr이 홀수이면
		{
			printf("┃");
			for (itr2 = 1; itr2 < boardSize * 2; itr2++) // itr2 1부터 boardSize*2-1까지 반복
			{
				if (itr2 % 2) //itr2가 홀수이면
				{
					if (itr1 / 2 == y && itr2 / 2 == x)
						printf(" ＠"); // x,y좌표랑 일치하면 @출력
					else if (arrBoard[itr1 / 2][itr2 / 2] == 2)
						printf("   "); // 배열값이 2이면 빈공간 출력
					else if (arrBoard[itr1 / 2][itr2 / 2] == 1)
						printf(" ●"); //배열값이 1이면 백돌 출력
					else if (arrBoard[itr1 / 2][itr2 / 2] == 0)
						printf(" ○"); // 배열값이 0이면 흑돌 출력
				}
				else
					printf("┃");
			}
			printf("┃\n");
		}
		else
		{
			if (itr1 == 0) //itr이 0이면
			{
				printf("┏");
				for (itr2 = 1; itr2 < boardSize * 2; itr2++)//itr2를 홀짝 나누어서
				{
					if (itr2 % 2) //itr2가 홀수이면
						printf("━━━");
					else//짝수이면
						printf("┳");
				}
				printf("┓\n");
			}
			else if (itr1 == boardSize * 2) //itr1이 마지막이면
			{
				printf("┗");
				for (itr2 = 1; itr2 < boardSize * 2; itr2++)
				{
					if (itr2 % 2)//itr2가 홀수이면
						printf("━━━");
					else//짝수이면
						printf("┻");
				}
				printf("┛\n");
			}
			else { //itr1이 처음과 마지막이 아닌경우
				printf("┃");
				for (itr2 = 1; itr2 < boardSize * 2; itr2++)
				{
					if (itr2 % 2)//itr2가 홀수이면
						printf("━━━");
					else//짝수이면
						printf("╋");
				}
				printf("┃\n");
			}
		}

	}
	if (round % 2) //round가 홀수이면 백돌출력
		printf("●");
	else //round가 짝수이면 흑돌출력
		printf("○");
}

int CheckBoard(int x, int y, int boardSize) { 
// x,y가 0보다 작거나 boardSize보다 크다면 0 반환, 이외에는 1반환
	int check = 1;
	if (x < 0 || x >= boardSize || y < 0 || y >= boardSize)
		check = 0;
	return check;
}

int CheckPlace(int** arrBoard, int x, int y) { //바둑판에 흑돌과 흰돌이 없으면 1 반환, 있으면 0반환
	if (arrBoard[y][x] == 2)
		return 1;
	else
		return 0;
}

int CheckGomoku(int** arrBoard, int x, int y, int round, int boardSize) 
{//오목이 완성되면1, 아니면 0 반환

	int i, j, count;
	for (i = 0, j = -1, count = 1; j >= -4; j--) //x,y기준으로 세로(0,-1)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0) //x+i,y+j좌표가 바둑판 밖이면 break
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x]) 
//x+i,y+j좌표가 x,y좌표와 같으면 count 1증가
			count += 1;
		else
			break;
	}
	for (i = 0, j = 1; j <= 4; j++)
	{//x,y기준으로 세로(0,1)방향을 검사하는 for문
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	if (count == 5) //count가 5이면 1반환 
		return 1;

	for (i = -1, j = 0, count = 1; i >= -4; i--) //x,y기준으로 가로(-1,0)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	for (i = 1, j = 0; i <= 4; i++) //x,y기준으로 가로(1,0)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	if (count == 5) //count가 5이면 1반환 
		return 1;



	for (i = -1, j = -1, count = 1; j >= -4; i--, j--) //x,y기준으로 대각선(-1,-1)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	for (i = 1, j = 1; j <= 4; i++, j++) //x,y기준으로 대각선(1,1)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	if (count == 5) //count가 5이면 1반환 
		return 1;


	for (i = -1, j = 1, count = 1; j <= 4; i--, j++) //x,y기준으로 대각선(-1,1)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	for (i = 1, j = -1; j >= -4; i++, j--)//x,y기준으로 대각선(1,-1)방향을 검사하는 for문
	{
		if (CheckBoard(x + i, y + j, boardSize) == 0)
			break;
		else if (arrBoard[y + j][x + i] == arrBoard[y][x])
			count += 1;
		else
			break;
	}
	if (count == 5)//count가 5이면 1반환 아니면 0반환
		return 1;
	else
		return 0;
}

int CheckThreeAndThree(int** arrBoard, int x, int y, int round, int boardSize) 
// 흑돌이 33되면 1, 아니면 0, 백돌은 0반환
{	
	if (round % 2) //백돌이면 0반환	
		return 0;
	

	else
	{
		if (y == 0 || x == 0 || y == boardSize - 1 || x == boardSize – 1)
//x,y좌표가 바둑판 가장자리에 있으면 벽이랑 만나므로 삼삼 허용해서 0반환
			return 0;
		if (check22(arrBoard, x, y, -1, 0, boardSize) && check22(arrBoard, x, y, -1, 1, boardSize))
//x,y좌표에서 –1,0방향과 –1,1방향의 서로 1이면 삼삼이므로 1반환
			return 1;
		if (check22(arrBoard, x, y, -1, 0, boardSize) && check22(arrBoard, x, y, 0, 1, boardSize))
//x,y좌표에서 –1,0방향과 0,1방향의 서로 1이면 삼삼이므로 1반환
			return 1;
		if (check22(arrBoard, x, y, -1, 0, boardSize) && check22(arrBoard, x, y, 1, 1, boardSize))
//x,y좌표에서 –1,0방향과 1,1방향의 서로 1이면 삼삼이므로 1반환
			return 1;
		if (check22(arrBoard, x, y, -1, 1, boardSize) && check22(arrBoard, x, y, 0, 1, boardSize))
//x,y좌표에서 –1,1방향과 0,1방향의 서로 1이면 삼삼이므로 1반환
			return 1;
		if (check22(arrBoard, x, y, -1, 1, boardSize) && check22(arrBoard, x, y, 1, 1, boardSize))
//x,y좌표에서 –1,1방향과 1,1방향의 서로 1이면 삼삼이므로 1반환
			return 1;
		if (check22(arrBoard, x, y, 0, 1, boardSize) && check22(arrBoard, x, y, 1, 1, boardSize))
//x,y좌표에서 0,1방향과 1,1방향의 서로 1이면 삼삼이므로 1반환
			return 1;
		else
//위 조건식이 모두아니면 33이아니므로 0반환
			return 0;
	}

}

int check22(int** arrBoard, int x, int y, int num1, int num2, int boardSize)

{//흑돌이 삼삼인지 아닌지 확인하기 위해 한방향에 흑돌이 두 개있는지 확인하는 함수
	int i, j, k, black = 0;

	for (i = num1, j = num2, k = 0; k < 3; k++)
	{//넘겨받은 num1,num2를 이용하여 그방향의 흑돌의 개수를 확인하고 black 증가
		if (arrBoard[y + j][x + i] == 0)
			black += 1;
		else if (arrBoard[y + j][x + i] == 1 || CheckBoard(y + j, x + i, boardSize) == 0)
			return 0; //흰돌이나 바둑판밖으로 벗어나면 0반환
		else //나머지 빈공간인 경우는 break
			break;

		if (num1 == -1 && num2 == 0)//가로방향인 경우 I--
			i--;
		else if (num1 == -1 && num2 == 1)//대각선방향인 경우 I--,j++
			i--, j++;
		else if (num1 == 0 && num2 == 1)//세로방향인 경우 j++
			j++;
		else if (num1 == 1 && num2 == 1)//대각선방향인 경우 I++,j++
			i++, j++;
	}
	for (i = -num1, j = -num2, k = 0; k < 3; k++)
	{//위의 for문에서 확인했던 방향과 반대방향을 확인하는 반복문
		if (arrBoard[y + j][x + i] == 0)
			black += 1;
		else if (arrBoard[y + j][x + i] == 1 || CheckBoard(y + j, x + i, boardSize) == 0)
			return 0; //흰돌이나 바둑판밖으로 벗어나면 0반환
		else
			break;

		if (num1 == -1 && num2 == 0)//가로방향인 경우 I++
			i++;
		else if (num1 == -1 && num2 == 1)//대각선방향인 경우 I++,j--
			i++, j--;
		else if (num1 == 0 && num2 == 1)//세로방향인 경우 j--
			j--;
		else if (num1 == 1 && num2 == 1)//대각선방향인 경우 I--,j--
			i--, j--;
	}
	if (black == 2) //검은돌이 2개이면 삼삼의 조건을 충족시키므로 1반환
		return 1;
	else //검은돌이 2개가 아닌경우는 삼삼의 조건을 충족하지 못하므로 0반환
		return 0;
}