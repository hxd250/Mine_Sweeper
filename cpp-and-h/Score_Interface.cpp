#include<graphics.h>
#include"Mine_Sweeper.h"
#include<stdio.h>

//
void Self_Interface(Player *p)
{
	initgraph(300, 300);
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

	setfont(20, 15, "楷体");

	setfillcolor(EGERGB(0, 191, 255));
	bar(0, 0, 59, 19);
	outtextxy(0, 0, "返回");

	setfillcolor(WHITE);
	bar(44, 69, 227, 89);
	outtextxy(44, 69, "简单(s):");
	xyprintf(164, 69, "%d", p->user_score.simple);
	bar(44, 139, 227, 159);
	outtextxy(44, 139, "普通(s):");
	xyprintf(164, 139, "%d", p->user_score.common);
	bar(44, 219, 227, 239);
	outtextxy(44, 219, "困难(s):");
	xyprintf(164, 219, "%d", p->user_score.hard);

	for (; is_run(); delay_fps(60)) {

		//获取鼠标消息
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//返回
			if (msg.x < 59 && msg.y < 19 && msg.is_left() && msg.is_down())
			{
				closegraph();
				Level_Interface(p);
			}
		}
	}

}

void Ranking_List_Interface(Player *p, int level)
{
	initgraph(300, 300);
	setfont(20, 15, "楷体");
	setbkcolor(EGERGB(255, 245, 238));
	setfillcolor(EGERGB(0, 191, 255));
	bar(0, 0, 59, 19);
	outtextxy(0, 0, "返回");

	FILE *fp;
	Player pla, temp;
	Player b[10];
	int i, n = 0, j, l, x = 0;

	if ((fp = fopen(FilePath, "r")) == NULL) { outtextxy(40, 40, "打开文件失败！"); getch(); }
	else
	{
		fread(&pla, sizeof(Player), 1, fp);
		while (!feof(fp))
		{
			b[n] = pla;
			fread(&pla, sizeof(Player), 1, fp);
			n++;
		}
		fclose(fp);

		if (level == 1)
		{

			for (i = 0; i < n; i++)
			{
				l = i;
				for (j = i; j < n; j++)
				{
					if (b[l].user_score.simple > b[j].user_score.simple) l = j;
				}
				temp = b[l];
				b[l] = b[i];
				b[i] = temp;
			}
			for (i = 0; i < n; i++)
			{
				if (b[i].user_score.simple != 0)
				{
					setcolor(EGERGB(148, 0, 211));
					xyprintf(50, 30 + x * 30, "%d", x + 1);
					xyprintf(90, 30 + x * 30, "%s", b[i].user_name);
					xyprintf(240, 30 + x * 30, "%d", b[i].user_score.simple);
					x++;
				}
				if (x == N) break;
			}
			if (x == 0) outtextxy(100, 140, "暂无榜单");
		}
		else if (level == 2)
		{
			for (i = 0; i < n; i++)
			{
				l = i;
				for (j = i; j < n; j++)
				{
					if (b[l].user_score.common > b[j].user_score.common) l = j;
				}
				temp = b[l];
				b[l] = b[i];
				b[i] = temp;
			}
			for (i = 0; i < n; i++)
			{
				if (b[i].user_score.common != 0)
				{
					setcolor(EGERGB(148, 0, 211));
					xyprintf(50, 30 + x * 30, "%d", x + 1);
					xyprintf(90, 30 + x * 30, "%s", b[i].user_name);
					xyprintf(240, 30 + x * 30, "%d", b[i].user_score.common);
					x++;
				}
				if (x == N) break;
			}
			if (x == 0) outtextxy(100, 140, "暂无榜单");
		}
		else
		{
			for (i = 0; i < n; i++)
			{
				l = i;
				for (j = i; j < n; j++)
				{
					if (b[l].user_score.hard > b[j].user_score.hard) l = j;
				}
				temp = b[l];
				b[l] = b[i];
				b[i] = temp;
			}
			for (i = 0; i < n; i++)
			{
				if (b[i].user_score.hard != 0)
				{
					setcolor(EGERGB(148, 0, 211));
					xyprintf(50, 30 + x * 30, "%d", x + 1);
					xyprintf(90, 30 + x * 30, "%s", b[i].user_name);
					xyprintf(240, 30 + x * 30, "%d", b[i].user_score.hard);
					x++;
				}
				if (x == N) break;
			}
			if (x == 0) outtextxy(100, 150, "暂无榜单");
		}



		for (; is_run(); delay_fps(60))
		{
			while (mousemsg())
			{
				mouse_msg msg = getmouse();
				//返回
				if (msg.x > 0 && msg.x < 59 && msg.y>0 && msg.y < 19 && msg.is_left() && msg.is_down())
				{
					Level_Interface(p);
				}
			}
		}
	}
}
