#include<graphics.h>
#include"Mine_Sweeper.h"

void Help_Interface(Player *p)
{
	initgraph(500, 500);
	PIMAGE img;
	img = newimage();        //newiage()������initgraph()֮��
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

	setfont(20, 15, "����");
	bar(0, 0, 60, 20);
	outtextxy(0, 0, "����");
	outtextxy(190, 60, "�淨����");
	outtextxy(0, 100, "(1)���������һ����,�Ҽ���ǵ���,");
	outtextxy(45, 120, "�ڶ��ΰ���Ϊ������ǡ�");
	outtextxy(0, 140, "(2)������������ʾ�����ֱ�ʾ��Χ��");
	outtextxy(45, 160, "��������,û���������ʾ�ޡ�");
	outtextxy(0, 180, "(3)��ȫ���ǵ��׸��ӱ�����,��ʱ��");
	outtextxy(45, 200, "��ʾӮ�ˡ�");
	for (; is_run(); delay_fps(60)) {

		//��ȡ�����Ϣ
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