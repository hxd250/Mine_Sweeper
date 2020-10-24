#include<graphics.h>
#include"Mine_Sweeper.h"

void Help_Interface(Player *p)
{
	initgraph(500, 500);
	PIMAGE img;
	img = newimage();        //newiage()必须在initgraph()之后
	if (p->background == 1) getimage(img, "Background\\1_500.jpg");
	else if (p->background == 2) getimage(img, "Background\\2_500.jpg");
	else if (p->background == 3) getimage(img, "Background\\3_500.jpg");
	else if (p->background == 4) getimage(img, "Background\\4_500.jpg");
	else if (p->background == 5) getimage(img, "Background\\5_500.jpg");
	else if (p->background == 6) getimage(img, "Background\\6_500.jpg");
	else if (p->background == 7) getimage(img, "Background\\7_500.jpg");
	else if (p->background == 8) getimage(img, "Background\\8_500.jpg");
	putimage(0, 0, img);
	delimage(img);

	setfont(20, 15, "楷体");
	bar(0, 0, 60, 20);
	outtextxy(0, 0, "返回");
	outtextxy(190, 60, "玩法介绍");
	outtextxy(0, 100, "(1)左键翻开这一格子,右键标记地雷,");
	outtextxy(45, 120, "第二次按则为消除标记。");
	outtextxy(0, 140, "(2)翻开格子所显示的数字表示周围的");
	outtextxy(45, 160, "地雷数量,没有数字则表示无。");
	outtextxy(0, 180, "(3)当全部非地雷格子被翻开,此时就");
	outtextxy(45, 200, "表示赢了。");
	for (; is_run(); delay_fps(60)) {

		//获取鼠标消息
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down() && msg.x>0 && msg.y>0 && msg.x <60 && msg.y<20)
			{
				closegraph();
				Main_Interface(p);
			}
		}
	}
}