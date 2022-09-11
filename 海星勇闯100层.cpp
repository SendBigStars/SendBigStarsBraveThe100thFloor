#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

#define Max_quantity 15
#define Max_x 600
#define Max_y 600
#define Max_space 60


struct SendBigStars {

	int x;
	int y;
	int vy;
	int r;
	int score;
	COLORREF color;

}SendBigStars;

struct Broad {

	int x;
	int y;
	int len;
	COLORREF color;

}Broad[Max_quantity];

void GameInit() {

	srand(GetTickCount());
	
	for (int i = 1; i <=Max_quantity; i++) {

		Broad[i].len = rand() % 50 + 75;
		Broad[i].x = rand() % (Max_x - Broad[i].len);
		Broad[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);

		if (i == 1) {
			Broad[i].y = rand() % 100 + 250;
		}
		else {
			Broad[i].y = Broad[i - 1].y +Max_space;
		}

	}
	SendBigStars.x = Broad[1].x + rand() % Broad[1].len;
	SendBigStars.r = 8;
	SendBigStars.y = Broad[1].y - SendBigStars.r;
	SendBigStars.score = 0;
	SendBigStars.color = RGB(0,255,255);
	SendBigStars.vy = 3;
}

void GameBegin() {

	cleardevice();

	for (int i = 1; i <= Max_quantity; i++) {

		setfillcolor(Broad[i].color);
		solidrectangle(Broad[i].x, Broad[i].y, Broad[i].x + Broad[i].len, Broad[i].y + 4);

	}
	setfillcolor(SendBigStars.color);
	solidcircle(SendBigStars.x, SendBigStars.y, SendBigStars.r);

	char tempscore[30] = "";
	sprintf(tempscore, "分数：%d", SendBigStars.score);
	outtextxy(10, 10, tempscore);

	if (SendBigStars.score == 100) {
		sprintf(tempscore, "wo爱酱酱");
		outtextxy(275, 300, tempscore);
	}
}

void GameMove() {

	for (int i = 1; i <= Max_quantity; i++) {
		Broad[i].y --;

		if (Broad[i].y < 0) {
			Broad[i].y = Max_quantity * Max_space;
			Broad[i].len = rand() % 50 + 75 ;
			Broad[i].x = rand() % (Max_x - Broad[i].len);
			Broad[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		
		}
	}
}

int check() {
	for (int i = 1; i <= Max_quantity; i++) {

		if (SendBigStars.y + SendBigStars.r > Broad[i].y) continue;
		
		if (SendBigStars.x > Broad[i].x && SendBigStars.x < Broad[i].x + Broad[i].len &&
			SendBigStars.y + SendBigStars.r + SendBigStars.vy + 1 >= Broad[i].y) {  
			return i;
		}

		if (SendBigStars.y >= Max_y) return 0;
	}
	return -1;
}

void SendBigStarsMove(int step) {

	if (GetAsyncKeyState(VK_LEFT)) {
		if (SendBigStars.x - SendBigStars.r > 1) SendBigStars.x -= step;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		if(SendBigStars.x + SendBigStars.r < Max_x - 1)SendBigStars.x += step;  
	}
	
	if (check() >0) {
		SendBigStars.y--;
		SendBigStars.vy = 3;
		SendBigStars.score++;
	}
	else {
		SendBigStars.y += SendBigStars.vy;
		SendBigStars.y++;
	}

}

void SendBigStarsOut() {

	GameInit();
	while (1) {
		if (check() == 0) break;
		GameBegin();
		FlushBatchDraw();
		SendBigStarsMove(5);
		GameMove();
		Sleep(10);
	}
	char tempscore[30] = "";
	sprintf(tempscore, "游戏结束");
	outtextxy(275, 300, tempscore);
}

int main() {

	initgraph(Max_x, Max_y);
	BeginBatchDraw();

	SendBigStarsOut();

	EndBatchDraw();
	system("pause");
	return 0;
}
