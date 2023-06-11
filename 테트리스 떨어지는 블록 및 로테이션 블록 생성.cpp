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
	void RotateBlock(void)
	{
		switch (blockShape)
		{
		case 0:
			if (numRot % 4 == 0)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY + 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY;
				p3_X = rotAxisX; p3_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY;
				p4_X = rotAxisX; p4_Y = rotAxisY + 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 4 == 2)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY - 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				p3_X = rotAxisX; p3_Y = rotAxisY + 1;
				++numRot;
			}
			else if (numRot % 4 == 3)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY;
				p4_X = rotAxisX; p4_Y = rotAxisY - 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY;
				++numRot;
			}
			break;
		case 1:
			if (numRot % 2 == 0)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY - 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY + 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 2 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY + 1;
				p3_X = rotAxisX; p3_Y = rotAxisY + 1;
				++numRot;
			}
			break;
		case 2:
			if (numRot % 2 == 0)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
				{
					break;
				}
				p2_X = rotAxisX; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 2 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX; p4_Y = rotAxisY + 1;
				++numRot;
			}
			break;
		case 3:
			if (numRot % 4 == 0)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY + 1;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY + 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX; p3_Y = rotAxisY - 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 2)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY - 1;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY + 1;
				++numRot;
			}
			else if (numRot % 4 == 3)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY + 1;
				p3_X = rotAxisX; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY + 1;
				++numRot;
			}
			break;
		case 4:
			if (numRot % 4 == 0)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY + 1;
				p2_X = rotAxisX + 1; p2_Y = rotAxisY;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY - 1;
				p4_X = rotAxisX; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 4 == 1)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2))
					break;
				p1_X = rotAxisX + 1; p1_Y = rotAxisY - 1;
				p2_X = rotAxisX; p2_Y = rotAxisY - 1;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY - 1;
				p4_X = rotAxisX - 1; p4_Y = rotAxisY;
				++numRot;
			}
			else if (numRot % 4 == 2)
			{
				if (!(gameMap[rotAxisY - 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY - 1;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY;
				p3_X = rotAxisX - 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX; p4_Y = rotAxisY + 1;
				++numRot;
			}
			else if (numRot % 4 == 3)
			{
				if (!(gameMap[rotAxisY + 1][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX + 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 1; p1_Y = rotAxisY + 1;
				p2_X = rotAxisX; p2_Y = rotAxisY + 1;
				p3_X = rotAxisX + 1; p3_Y = rotAxisY + 1;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				++numRot;
			}
			break;
		case 5:
			if (numRot % 2 == 0)
			{
				if (!(gameMap[rotAxisY + 2][rotAxisX] < 2 &&
					gameMap[rotAxisY + 1][rotAxisX] < 2 &&
					gameMap[rotAxisY - 1][rotAxisX] < 2))
					break;
				p1_X = rotAxisX; p1_Y = rotAxisY + 2;
				p2_X = rotAxisX; p2_Y = rotAxisY + 1;
				p4_X = rotAxisX; p4_Y = rotAxisY - 1;
				++numRot;
			}
			else if (numRot % 2 == 1)
			{
				if (!(gameMap[rotAxisY][rotAxisX - 2] < 2 &&
					gameMap[rotAxisY][rotAxisX - 1] < 2 &&
					gameMap[rotAxisY][rotAxisX + 1] < 2))
					break;
				p1_X = rotAxisX - 2; p1_Y = rotAxisY;
				p2_X = rotAxisX - 1; p2_Y = rotAxisY;
				p4_X = rotAxisX + 1; p4_Y = rotAxisY;
				++numRot;
			}
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	bool DropBlock(void)			//블록이 바닥에 떨어질 시 true 반환
	{
		gameMap[p1_Y][p1_X] = 0;
		gameMap[p2_Y][p2_X] = 0;
		gameMap[p3_Y][p3_X] = 0;
		gameMap[p4_Y][p4_X] = 0;

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
		gameMap[p1_Y][p1_X] = 3;		//새로운위치에 블록 출력
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
		return false;
	}
};