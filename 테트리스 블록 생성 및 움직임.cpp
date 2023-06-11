#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
const int BOARD_X = 40;
const int BOARD_Y = 28;
const int MAP_X = 12;
const int MAP_Y = 22;
int gameMap[MAP_Y][MAP_X];	//0은 빈칸, 1은 그림자, 2는 쌓인거, 3은 블록, 4는 벽
clock_t startTime = 0, pauseTime = 0;				//게임시간, 일시정지시간 체크
clock_t cntTime = 0;		//DropBlock 실행시키기 위해 시간 재는 변수
clock_t dropTime = 0, raiseTime = 0;
int dropTimeSet = 1000;		//cntTime - dropTime이 몇일때 DropBlock 실행시킬지 조절하는 변수
int raiseTimeSet = 2100000000;		//cntTime - raiseTime이 몇일때 바닥 올라올지 조절하는 변수
bool fallen = false;			//블록이 바닥에 닿아서 턴 끝날시 true로 바뀜
void gotoxy(int x, int y);
class Block
{
private:
	int p1_X; int p1_Y;			//블록좌표
	int p2_X; int p2_Y;
	int p3_X; int p3_Y;
	int p4_X; int p4_Y;
	int rotAxisX; int rotAxisY;	//회전축 좌표
	int numRot;					//회전횟수
	int blockShape;				//블록모양
public:
	void InIt(void)
	{
		p1_X = 0, p1_Y = 0;
		p2_X = 0, p2_Y = 0;
		p3_X = 0, p3_Y = 0;
		p4_X = 0, p4_Y = 0;
		rotAxisX = 0, rotAxisY = 0;
		numRot = 0;
		blockShape = 0;
	}

	bool MakeBlock(void)		//블록생성지점에 블록이 쌓여있을경우 true 반환(게임오버)
	{
		int i, j;
		srand(clock());
		int blockNumber = rand() % 7;
		switch (blockNumber)
		{
		case 0:			//ㅗ모양
			i = 2;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 2; p3_Y = i;
			p4_X = j + 1; p4_Y = i - 1;
			rotAxisX = j + 1; rotAxisY = i;
			numRot = 0;
			blockShape = 0;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 1:			//번개모양
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 1; p3_Y = i + 1;
			p4_X = j + 2; p4_Y = i + 1;
			rotAxisX = j + 1; rotAxisY = i;
			numRot = 0;
			blockShape = 1;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 2:			//번개모양 반대
			i = 1;
			j = 5;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j - 1; p3_Y = i + 1;
			p4_X = j; p4_Y = i + 1;
			rotAxisX = j; rotAxisY = i;
			numRot = 0;
			blockShape = 2;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 3:			//L모양
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j; p2_Y = i + 1;
			p3_X = j + 1; p3_Y = i + 1;
			p4_X = j + 2; p4_Y = i + 1;
			rotAxisX = j + 1; rotAxisY = i;
			numRot = 0;
			blockShape = 3;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 4:			//L모양 반대
			i = 2;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 2; p3_Y = i;
			p4_X = j + 2; p4_Y = i - 1;
			rotAxisX = j + 1; rotAxisY = i - 1;
			numRot = 0;
			blockShape = 4;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 5:			//1모양
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j + 2; p3_Y = i;
			p4_X = j + 3; p4_Y = i;
			rotAxisX = j + 2; rotAxisY = i;
			numRot = 0;
			blockShape = 5;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		case 6:			//ㅁ모양
			i = 1;
			j = 4;
			p1_X = j; p1_Y = i;
			p2_X = j + 1; p2_Y = i;
			p3_X = j; p3_Y = i + 1;
			p4_X = j + 1; p4_Y = i + 1;
			rotAxisX = 0; rotAxisY = 0;
			numRot = 0;
			blockShape = 6;
			if (gameMap[p1_Y][p1_X] == 2 ||
				gameMap[p2_Y][p2_X] == 2 ||
				gameMap[p3_Y][p3_X] == 2 ||
				gameMap[p4_Y][p4_X] == 2)
				return true;
			break;
		}
		gameMap[p1_Y][p1_X] = 3;
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
		return false;
	}
	bool MoveBlock(void)		//블록이 바닥까지 떨어질시 true 반환
	{
		int input;							//방향키 입력받기
		if (_kbhit())
		{
			gameMap[p1_Y][p1_X] = 0;	//입력 들어올시 원래위치의 블록 삭제
			gameMap[p2_Y][p2_X] = 0;
			gameMap[p3_Y][p3_X] = 0;
			gameMap[p4_Y][p4_X] = 0;

			input = _getch();
			if (input == 224)
			{
				input = _getch();
				switch (input)
				{
				case 72:	//위
					RotateBlock();
					break;
				case 80:	//아래
					if (!(gameMap[p1_Y + 1][p1_X] < 2 &&
						gameMap[p2_Y + 1][p2_X] < 2 &&
						gameMap[p3_Y + 1][p3_X] < 2 &&
						gameMap[p4_Y + 1][p4_X] < 2))	//충돌 일어나면
					{
						gameMap[p1_Y][p1_X] = 2;		//블록 떨어진 위치에 쌓음
						gameMap[p2_Y][p2_X] = 2;
						gameMap[p3_Y][p3_X] = 2;
						gameMap[p4_Y][p4_X] = 2;
						return true;
					}
					++p1_Y;
					++p2_Y;
					++p3_Y;
					++p4_Y;
					++rotAxisY;
					break;
				case 75:	//왼쪽
					if (!(gameMap[p1_Y][p1_X - 1] < 2 &&
						gameMap[p2_Y][p2_X - 1] < 2 &&
						gameMap[p3_Y][p3_X - 1] < 2 &&
						gameMap[p4_Y][p4_X - 1] < 2))	//충돌 일어나면
						break;
					--p1_X;
					--p2_X;
					--p3_X;
					--p4_X;
					--rotAxisX;
					break;
				case 77:	//오른쪽
					if (!(gameMap[p1_Y][p1_X + 1] < 2 &&
						gameMap[p2_Y][p2_X + 1] < 2 &&
						gameMap[p3_Y][p3_X + 1] < 2 &&
						gameMap[p4_Y][p4_X + 1] < 2))	//충돌 일어나면
						break;
					++p1_X;
					++p2_X;
					++p3_X;
					++p4_X;
					++rotAxisX;
					break;
				default:
					break;
				}
			}
			else if (input == 32)			//스페이스바 입력
			{
				while (gameMap[p1_Y + 1][p1_X] < 2 &&
					gameMap[p2_Y + 1][p2_X] < 2 &&
					gameMap[p3_Y + 1][p3_X] < 2 &&
					gameMap[p4_Y + 1][p4_X] < 2)	//충돌하는거 아니면 계속
				{
					++p1_Y;
					++p2_Y;
					++p3_Y;
					++p4_Y;
				}
				gameMap[p1_Y][p1_X] = 2;		//블록 떨어진 위치에 쌓음
				gameMap[p2_Y][p2_X] = 2;
				gameMap[p3_Y][p3_X] = 2;
				gameMap[p4_Y][p4_X] = 2;
				return true;
			}
			else if (input == 112 || input == 80)			//p 또는 P 또는 입력 시
			{
				gotoxy(13, 5);
				printf("  Pause");
				clock_t PT1 = clock();
				system("pause>null");						//일시정지
				clock_t PT2 = clock();
				pauseTime += PT2 - PT1;
			}
			gameMap[p1_Y][p1_X] = 3;		//새로운 위치에 블록 쌓음
			gameMap[p2_Y][p2_X] = 3;
			gameMap[p3_Y][p3_X] = 3;
			gameMap[p4_Y][p4_X] = 3;
		}										//방향키 입력받기 끝
		return false;
	}
};