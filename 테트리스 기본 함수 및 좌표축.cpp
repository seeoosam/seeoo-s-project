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
};