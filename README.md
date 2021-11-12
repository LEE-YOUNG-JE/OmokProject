# OmokProject

# 구현사항
요구사항에 맞춰 오목 프로그램을 구현

# 요구사항
1. 사용자에게 바둑판의 크기를 입력 받아서 받은 크기로 게임을 진행
2. 두 플레이어가 서로 번갈아가며 흑돌, 백돌을 둠
3. 훅돌의 플레이어(먼저 두는 풀레이어)는 삼삼이 되는 위치에 둘 수 없음
  - 한쪽이 다른 플레이어의 돌이나, 바둑판의 끝에 놓아져 막힌 경우에는 상관 없음
  - 띄어져 있는 경우에는 상관 없음
4. 오목이 아닌 육목, 칠목 등은 오목으로 취급하지 않음

#1 void PrintBoard(int** arrBoard, int x, int y, int round, int boardSize);
 int** arrBoard, int x, int y, int round, int boardSize를 인자로 받아서 바둑판의 형태와 현재위치, 흑돌과 백돌의 위치를 나타내주는 함수이다.

#2 int CheckBoard(int x, int y, int boardSize);
int x, int y, int boardSize를 인자로 받아서 x,y좌표가 바둑판 크기(boardSize)를 벗어 나면 return 0, 바둑판 안에 있으면 return 1로 반환하는 함수이다.

#3 int CheckPlace(int** arrBoard, int x, int y);
int** arrBoard, int x, int y를 인자로 받아서 arrBoard[y][x]자리에 흑돌이나 백돌이 있으면 return 0, 아무것도 없으면 return 1로 반환하는 함수이다.

#4 int CheckGomoku(int** arrBoard, int x, int y, int round, int boardSize);
 int** arrBoard, int x, int y, int round, int boardSize를 인자로 받아서 흑돌이든 백돌이든 상관없이 같은 색깔의 돌이 연속으로 5개가 되면 return 1을 반환하고
오목이 아니거나 육목이상인 경우는 return 0을 반환하는 함수이다

#5 int CheckThreeAndThree(int** arrBoard, int x, int y, int round, int boardSize);
 int** arrBoard, int x, int y, int round, int boardSize를 인자로 받고 흑돌은 삼삼이 되면 안되는데 흑돌을 놓았을 때 삼삼이 되면 return 1, 삼삼이 안되는 경우에는 return 0을 반환한다. 백돌은 바로 return 0을 반환한다.

#6 int check22(int** arrBoard, int x, int y, int num1, int num2, int boardSize);
 int** arrBoard, int x, int y, int num1, int num2, int boardSize를 인자로 받고 CheckThreeAndThree함수에서 좀 더 용이하게 흑돌의 삼삼을 확인하기 위해 방향을 네군데(가로, 왼쪽대각선, 세로, 오른쪽대각선)로 나누고 각 방향별로 두 개의 흑돌이 있는지 확인하는 함수이다.
