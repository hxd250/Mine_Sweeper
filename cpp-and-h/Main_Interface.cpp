#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "Mine_Sweeper.h"


//void Main_Interface(Player *p);

//游戏主界面
void* Main_Interface(void*  q)
{
	Player *p;
	p = (Player *)q;
	initgraph(300, 300);
	setcaption("扫雷小游戏");
	PIMAGE img;
	img = newimage();        //newiage()必须在initgraph()之后
	if (p->background == 1) getimage(img, "Background\\1_300.jpg");
	else if (p->background == 2) getimage(img, "Background\\2_300.jpg");
	else if (p->background == 3) getimage(img, "Background\\3_300.jpg");
	else if (p->background == 4) getimage(img, "Background\\4_300.jpg");
	else if (p->background == 5) getimage(img, "Background\\5_300.jpg");
	else if (p->background == 6) getimage(img, "Background\\6_300.jpg");
	else if (p->background == 7) getimage(img, "Background\\7_300.jpg");
	else if (p->background == 8) getimage(img, "Background\\8_300.jpg");
	putimage(0, 0, img);
	delimage(img);

	setcolor(BLACK);
	setfillcolor(EGERGB(0, 191, 255));

	//显示
	setbkmode(TRANSPARENT);
	setfont(20, 15, "楷体");

	outtextxy(0, 0, p->user_name);
	outtextxy(0, 20, "欢迎您！");

	bar(83, 113, 203, 133);
	outtextxy(83, 113, "开始游戏");
	bar(113, 175, 173, 195);
	outtextxy(113, 175, "帮助");
	bar(113, 237, 173, 257);
	outtextxy(113, 237, "设置");

	//点击
	for (; is_run(); delay_fps(60)) {

		//获取鼠标消息
		while (mousemsg()) {
			mouse_msg msg = getmouse();

			//在消息处理循环中判断点击
			if (msg.is_left() && msg.is_down())
			{
				if (msg.x > 83 && msg.x < 203 && msg.y>113 && msg.y < 133) {closegraph(); Level_Interface(p); }
				else if (msg.x > 113 && msg.x < 173 && msg.y>175 && msg.y < 195) { closegraph(); Help_Interface(p); }
				else if (msg.x > 113 && msg.x < 173 && msg.y>237 && msg.y < 257) {  closegraph(); Setup_Interface(p); }
			}
		}
	}
	return NULL;
}
