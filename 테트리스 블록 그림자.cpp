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
	void MakeShadow(void)
	{
		int tp1_X = p1_X; int tp1_Y = p1_Y;	//블록 위치 저장할 변수
		int tp2_X = p2_X; int tp2_Y = p2_Y;
		int tp3_X = p3_X; int tp3_Y = p3_Y;
		int tp4_X = p4_X; int tp4_Y = p4_Y;

		gameMap[tp1_Y][tp1_X] = 0;					//블록 위치 0으로 만들고
		gameMap[tp2_Y][tp2_X] = 0;
		gameMap[tp3_Y][tp3_X] = 0;
		gameMap[tp4_Y][tp4_X] = 0;

		while (gameMap[tp1_Y + 1][tp1_X] < 2 &&
			gameMap[tp2_Y + 1][tp2_X] < 2 &&
			gameMap[tp3_Y + 1][tp3_X] < 2 &&
			gameMap[tp4_Y + 1][tp4_X] < 2)	//충돌하는거 아니면 계속
		{
			++tp1_Y;
			++tp2_Y;
			++tp3_Y;
			++tp4_Y;
		}
		gameMap[tp1_Y][tp1_X] = 1;					//블록 떨어진 위치에 그림자 만듦
		gameMap[tp2_Y][tp2_X] = 1;
		gameMap[tp3_Y][tp3_X] = 1;
		gameMap[tp4_Y][tp4_X] = 1;

		gameMap[p1_Y][p1_X] = 3;			//블록 위치는 다시 3
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
	}
	void EraseShadow(void)
	{
		int tp1_X = p1_X; int tp1_Y = p1_Y;	//블록 위치 저장할 변수
		int tp2_X = p2_X; int tp2_Y = p2_Y;
		int tp3_X = p3_X; int tp3_Y = p3_Y;
		int tp4_X = p4_X; int tp4_Y = p4_Y;

		gameMap[tp1_Y][tp1_X] = 0;					//블록 위치 0으로 만들고
		gameMap[tp2_Y][tp2_X] = 0;
		gameMap[tp3_Y][tp3_X] = 0;
		gameMap[tp4_Y][tp4_X] = 0;

		while (gameMap[tp1_Y + 1][tp1_X] < 2 &&
			gameMap[tp2_Y + 1][tp2_X] < 2 &&
			gameMap[tp3_Y + 1][tp3_X] < 2 &&
			gameMap[tp4_Y + 1][tp4_X] < 2)	//충돌하는거 아니면 계속
		{
			++tp1_Y;
			++tp2_Y;
			++tp3_Y;
			++tp4_Y;
		}
		gameMap[tp1_Y][tp1_X] = 0;					//블록 떨어진 위치에 그림자 없앰
		gameMap[tp2_Y][tp2_X] = 0;
		gameMap[tp3_Y][tp3_X] = 0;
		gameMap[tp4_Y][tp4_X] = 0;

		gameMap[p1_Y][p1_X] = 3;			//블록 위치는 다시 3
		gameMap[p2_Y][p2_X] = 3;
		gameMap[p3_Y][p3_X] = 3;
		gameMap[p4_Y][p4_X] = 3;
	}
};