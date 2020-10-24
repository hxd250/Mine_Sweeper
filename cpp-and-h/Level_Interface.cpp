#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "Mine_Sweeper.h"


typedef struct check {
	int if_mine;          //�����Ƿ����ף�1��ʾ�ǣ�0��ʾ����
	int around_mine;      //��ΧһȦ��������
	int if_open;          //�Ƿ񱻷�����1��ʾ������0��ʾû�з���
	int n;                //�����ǵڼ���
}Check;

Check *Init_Check(int m, int n, int a_minenum);
void Gread_Map(int m, int n, Player *p);
void Open_Check(int m, int n, int mine_num, Check *a, Player *p,int level);
void Open_Around(Check *a, int i, int m, int num, int x, int y);
void Printf(Check *a, int x, int y, int i);


//��ʼ��������Ϣ
Check *Init_Check(int m, int n, int a_minenum)       //mΪ���������nΪ�������
{
	int num = n*m, i;
	int r_minenum = 0;      //��¼���������
	Check* const a = (Check *)malloc(sizeof(Check)*num);      //�����ڽṹ������

															  //����Ĭ�ϳ�ʼ��
	for (i = 0; i < num; i++)
	{
		a[i].if_mine = 0;
		a[i].around_mine = 0;
		a[i].if_open = 0;
		a[i].n = 0;
	}

	//����
	srand((unsigned)time(NULL));
	while (r_minenum < a_minenum)
	{
		//srand((unsigned)time(0));     //����ÿ��ʹ��rand()������Ҫ�����������
		i = rand() % num;
		if (a[i].if_mine == 1) continue;
		a[i].if_mine = 1;
		r_minenum++;
	}

	//��������Χ���׵���������д��
	for (i = 0; i < num; i++)
	{
		if (a[i].if_mine == 0)
		{

			//���϶���
			if (i == 0)
			{
				a[i].around_mine = a[i + 1].if_mine + a[i + m].if_mine + a[i + m + 1].if_mine;
			}

			//����һ����
			else if (i > 0 && i < m - 1)
			{
				a[i].around_mine = a[i - 1].if_mine + a[i + 1].if_mine + a[i + m - 1].if_mine + a[i + m].if_mine + a[i + m + 1].if_mine;
			}

			//���϶���
			else if (i == m - 1)
			{
				a[i].around_mine = a[i - 1].if_mine + a[i + m - 1].if_mine + a[i + m].if_mine;
			}

			//����һ����(�������)
			else if (i%m == 0 && i != 0 && i != num - m)
			{
				a[i].around_mine = a[i - m].if_mine + a[i - m + 1].if_mine + a[i + 1].if_mine + a[i + m].if_mine + a[i + m + 1].if_mine;
			}

			//����һ����(�������)
			else if ((i + 1) % m == 0 && i != m - 1 && i != num - 1)
			{
				a[i].around_mine = a[i - m - 1].if_mine + a[i - m].if_mine + a[i - 1].if_mine + a[i + m - 1].if_mine + a[i + m].if_mine;
			}

			//���¶���
			else if (i == num - m)
			{
				a[i].around_mine = a[i - m].if_mine + a[i - m + 1].if_mine + a[i + 1].if_mine;
			}

			//����һ����(�������)
			else if (i > num - m && i < num - 1)
			{
				a[i].around_mine = a[i - m - 1].if_mine + a[i - m].if_mine + a[i - m + 1].if_mine + a[i - 1].if_mine + a[i + 1].if_mine;
			}

			//���¶���
			else if (i == num - 1)
			{
				a[i].around_mine = a[i - m - 1].if_mine + a[i - m].if_mine + a[i - 1].if_mine;
			}

			//�ڲ����Ÿ����Ӱ�Χ�ĵĸ���
			else
			{
				a[i].around_mine = a[i - m - 1].if_mine + a[i - m].if_mine + a[i - m + 1].if_mine + a[i - 1].if_mine + a[i + 1].if_mine + a[i + m - 1].if_mine + a[i + m].if_mine + a[i + m + 1].if_mine;
			}
			//printf("��%d��д�����\n",i);
		}     //if

	}        //for
	return a;
}

//������ͼ
void Gread_Map(int m, int n, Player *p)
{
	int i;
	int x1 = 299 - 10 * m, y1 = 329 - 10 * n;
	int x2 = 299 + 10 * m, y2 = 329 - 10 * n;
	int x3 = 299 - 10 * m, y3 = 329 + 10 * n;
	int x4 = 299 + 10 * m, y4 = 329 + 10 * n;
	int x, y;

	if (m > 26 || n > 25)
	{
		//printf("����ĳ��������");
		//system("pause");
		return;
	}
	initgraph(600, 600);

	PIMAGE img;
	//setbkcolor(WHITE);
	img = newimage();        //newiage()������initgraph()֮��
	if (p->background == 1) getimage(img, "Background\\1_600.jpg");
	else if (p->background == 2) getimage(img, "Background\\2_600.jpg");
	else if (p->background == 3) getimage(img, "Background\\3_600.jpg");
	else if (p->background == 4) getimage(img, "Background\\4_600.jpg");
	else if (p->background == 5) getimage(img, "Background\\5_600.jpg");
	else if (p->background == 6) getimage(img, "Background\\6_600.jpg");
	else if (p->background == 7) getimage(img, "Background\\7_600.jpg");
	else if (p->background == 8) getimage(img, "Background\\8_600.jpg");
	putimage(0, 0, img);
	delimage(img);




	setfillcolor(EGERGB(0, 191, 255));
	
	setcolor(BLACK);
	setfont(20, 15, "����");

	//��ť��ʾ




	bar(44, 19, 104, 39);
	outtextxy(44, 19, "����");

	bar(494, 19, 554, 39);
	outtextxy(494, 19, "����");

	bar(164, 19, 284, 39);
	outtextxy(164, 19, "ʱ��");

	bar(329, 19, 434, 39);
	outtextxy(329, 19, "����");

	setfillcolor(WHITE);

	bar(224, 19, 284, 39);
	bar(389, 19, 434, 39);

	line(0, 59, 599, 59);    //��ť�͵�ͼ�ķֽ���
							 //������
	setcolor(WHITE);
	for (i = 0; i <= m; i++)
	{
		line(x1, y1, x1, y3); //x1��x3��ͬ
		x1 += 20;
	}

	//��ԭ��������
	x1 = 299 - 10 * m;

	//������
	for (i = 0; i <= n; i++)
	{
		line(x1, y1, x2, y1);  //y1��y2��ͬ
		y1 += 20;
	}

	y1 = 329 - 10 * n;   //��ԭy1

	setfillcolor(EGERGB(255, 165, 0));
	for (i = 0; i < n*m; i++)
	{
		x = x1 + (i % m) * 20 + 2;
		y = y1 + (i / m) * 20 + 2;
		bar(x, y, x + 17, y + 17);
	}
	setcolor(BLACK);
	//setfillcolor(WHITE);
}

//���յ��������������  ��ʱ��Ҳ�����￪ʼ��¼
void Open_Check(int m, int n, int mine, Check *a, Player *p,int level) //level ��ʾ�ȼ���0��ʾ�Զ���
{
	MUSIC music;
	PIMAGE img;
	img = newimage();
	getimage(img,"background\\��.jpg");

	int x1 = 299 - 10 * m, y1 = 329 - 10 * n;        //����
	int x4 = 299 + 10 * m, y4 = 329 + 10 * n;       //
	int x, y, i = 0;    //(x,y)Ϊ�������Ͻ�,iΪ�������
	int num = n*m, math = 0, flag = mine;   //�ܸ�����  math��¼�����ĵ�Ƥ   flag��ʾʣ���
	int hit = 0;              //����ʱ�俪ʼ��ʱ
	int starttime, curtime, runtime;
	//setcolor(CYAN);

	FILE *fp, *fq;
	Player *pla = (Player *)malloc(sizeof(Player));

	//setfillcolor(WHITE);
	setcolor(RED);
	setfillcolor(WHITE);

	xyprintf(389, 19, "%d", flag);


	for (; is_run(); delay_fps(60))
	{

		if (hit == 1)
		{
			bar(225, 20, 284, 39);
			runtime = time(NULL);
			curtime = runtime - starttime;
			if (hit != 3) xyprintf(224, 19, "%d", curtime);
		}

		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			x = ((msg.x - x1) / 20) * 20 + x1 + 2;
			y = ((msg.y - y1) / 20) * 20 + y1 + 2;
			i = (msg.x - x1) / 20 + ((msg.y - y1) / 20)*m;
			if (msg.is_left() && msg.is_down() && msg.x > x1 && msg.x < x4 &&msg.y > y1 && msg.y < y4 && a[i].if_open == 0)
			{
				setfont(17, 17, "����");
				if (a[i].if_mine == 0)
				{
					Printf(a, x, y, i);
					a[i].if_open = 1;

					//���������Ϊ0ʱ��Χ���Զ�����  
					if (a[i].around_mine == 0)
					{
						Open_Around(a, i, m, num, x - 2, y - 2);

					}
				}
				else
				{
					music.OpenFile("music\\defeat.mp3");
					music.Play(0);
					hit = 3;      //������ʱ
					for (i = 0; i < num; i++)
					{
						if (a[i].if_mine == 1)
						{
							x = x1 + (i % m) * 20 + 2;
							y = y1 + (i / m) * 20 + 2;
							putimage(x, y, img);

						}
					}
					setcolor(EGERGB(220, 20, 60));    //�ɺ�ɫ
					setfont(40, 40, "����");
					outtextxy(140, 70, "defeat!");
					setcolor(BLACK);
					setfont(17, 17, "����");
					//music.Close();
				}

			}

			//�����
			else if (msg.is_right() && msg.is_down() && msg.x > x1 && msg.x<x4 && msg.y>y1 && msg.y < y4)
			{
				if (a[i].if_open == 0 && flag>0)
				{
                    a[i].if_open = 3;         //��ǲ��˺���
					//outtextxy(x, y, "@");
					//
					setfillcolor(RED);
					setcolor(RED);
					int aa[8] = {x+12,y+3,x+3,y+10,x+12,y+10,x + 12,y + 3 };  //�������ǲ���
					fillpoly(3, aa);
					setfillcolor(WHITE);
					bar(x + 12, y + 3, x + 14, y + 15);         //���
					setfillcolor(BLACK);
					bar(x + 6, y + 15, x + 16, y + 17);        //����
					//
					setfillcolor(WHITE);
					bar(390, 20, 433, 37);
					if (flag>0) flag--;
					xyprintf(390, 20, "%d", flag);
				}
				else if (a[i].if_open == 3)
				{
                    a[i].if_open = 0;
					setfillcolor(EGERGB(255, 165, 0));
					bar(x, y, x + 17, y + 17);
					setfillcolor(WHITE);
					bar(390, 20, 433, 37);
					flag++;
					xyprintf(390, 20, "%d", flag);
				}
			}

			//����
			else if (msg.is_left() && msg.is_down() && msg.x > 44 && msg.x < 104 && msg.y>19 && msg.y < 39)
			{
				delimage(img);
				music.Close();
				closegraph();
				Level_Interface(p);
			}

			//����
			else if (msg.is_left() && msg.is_down() && msg.x > 494 && msg.x < 554 && msg.y>19 && msg.y < 39)
			{
				delimage(img);
				music.Close();
				closegraph();
				a = Init_Check(m, n, mine);
				Gread_Map(m, n, p);
				Open_Check(m, n, mine, a, p,level);
			}

			if (msg.x > x1 && msg.x<x4 && msg.y>y1 && msg.y < y4 && hit == 0 && msg.is_left() && msg.is_down())
			{
				starttime = time(NULL);
				hit = 1;
			}

			if (hit == 1)
			{
				bar(225, 20, 284, 39);
				runtime = time(NULL);
				curtime = runtime - starttime;
				if (hit != 3) xyprintf(224, 19, "%d", curtime);
			}

			//ʤ�����
			for (i = 0; i < num; i++)
			{
				if (hit != 3 && a[i].if_open == 1) math++;
			}
			if (math == num - mine)
			{
				music.OpenFile("music\\win.mp3");
				hit = 3;
				setcolor(EGERGB(220, 20, 60));
				setfont(40, 40, "����");
				outtextxy(140, 70, "victory!");
				music.Play(0);

				//�������ݵ�Ӳ��
				if (level != 0)
				{
					if ((fp = fopen(FilePath, "r")) == NULL || (fq = fopen(NewFilePath, "w")) == NULL)
					{
						outtextxy(144, 359, "��������ʧ�ܣ�");
						return;
					}
					//fwrite(p, sizeof(Player), 1, fq);          //�޸ĺ����Ϣд��
					fread(pla, sizeof(Player), 1, fp);
					while (!feof(fp))
					{
						if (strcmp(pla->user_name, p->user_name) != 0)
						{
							fwrite(pla, sizeof(Player), 1, fq);        //��ԭ�ļ�����Ϣд��
						}
						else
						{
							if (level == 1)
							{
								if (pla->user_score.simple > curtime || pla->user_score.simple == 0) p->user_score.simple = curtime;
								fwrite(p, sizeof(Player), 1, fq);
							}
							else if (level == 2)
							{
								if (pla->user_score.common > curtime || pla->user_score.common == 0) p->user_score.common = curtime;
								fwrite(p, sizeof(Player), 1, fq);
							}
							else if (level == 3)
							{
								if (pla->user_score.hard > curtime || pla->user_score.hard == 0) p->user_score.hard = curtime;
								fwrite(p, sizeof(Player), 1, fq);

							}
						}
						fread(pla, sizeof(Player), 1, fp);
					}
					fclose(fp);
					fclose(fq);
					_unlink("data\\mine_sweeper.dat");                 //ɾ���ļ�
					rename("data\\temp.dat", "data\\mine_sweeper.dat");      //�޸��ļ���
					//system("DEL mine_sweeper.dat");                   //���ֶ���
				    //system("RENAME temp.dat mine_sweeper.dat");
				}
			}
			math = 0;


		}
	}
}

void Level_Interface(Player *p)
{
	int self = 0;          //self���ڱ�ʾ�Զ��尴ť�Ƿ񱻰�
	int m = 6, n = 6, mine = 6;
	initgraph(300, 300);

	PIMAGE img;
	img = newimage();        //newiage()������initgraph()֮��
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

	int fla = 0;           //���а�ʱ�õ�
	setfont(20, 15, "����");
	setcolor(BLACK);
	setfillcolor(EGERGB(0, 191, 255));

	bar(0, 0, 59, 19);
	outtextxy(0, 0, "����");

	bar(119, 19, 179, 39);
	outtextxy(119, 19, "��");

	bar(119, 74, 179, 94);
	outtextxy(119, 74, "��ͨ");

	bar(119, 129, 179, 149);
	outtextxy(119, 129, "����");

	bar(109, 184, 199, 204);
	outtextxy(109, 184, "�Զ���");

	setfont(15, 12, "����");
	bar(207, 0, 299, 15);
	outtextxy(207, 0, "���˳ɼ�");
	bar(230,20,299,35);
	outtextxy(230, 20, "�����");
	setfont(20, 15, "����");

	Check *a;

	

	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())
			{

				//��
				if (msg.x > 119 && msg.x < 179 && msg.y>19 && msg.y < 39)
				{
					closegraph();
					a = Init_Check(7, 8, 8);
					Gread_Map(7, 8, p);
					Open_Check(7, 8, 8, a, p, 1);
				}

				//����
				else if (msg.x > 0 && msg.x < 60 && msg.y>0 && msg.y < 20)
				{
					closegraph();
					Main_Interface(p);
				}

				//��ͨ
				else if (msg.x > 119 && msg.x < 179 && msg.y>74 && msg.y < 94)
				{
					closegraph();
					a = Init_Check(10, 10, 20);
					Gread_Map(10, 10, p);
					Open_Check(10, 10, 20, a, p, 2);
				}

				//����
				else if (msg.x > 119 && msg.x < 179 && msg.y>129 && msg.y < 149)
				{
					closegraph();
					a = Init_Check(15, 15, 60);
					Gread_Map(15, 15, p);
					Open_Check(15, 15, 60, a, p, 3);
					//closegraph();
				}

				//�Զ���
				else if (msg.x > 109 && msg.x < 199 && msg.y>184 && msg.y < 204 && self == 0)
				{
					self = 1;

					outtextxy(7, 242, "����");
					bar(67,222,82,242);
					bar(67, 262, 82, 282);
					outtextxy(67, 222, "+");
					outtextxy(67, 262, "-");

					outtextxy(104, 242, "����");
					bar(164, 222, 179, 242);
					bar(164, 262, 179, 282);
					outtextxy(164, 222, "+");
					outtextxy(164, 262, "-");
					
					outtextxy(200, 242, "����");
					bar(260,222,275,242);
					bar(260, 262, 275, 282);
					outtextxy(260, 222, "+");
					outtextxy(260, 262, "-");

					bar(110, 185, 198, 203);
					outtextxy(119, 184, "ȷ��");

					setfillcolor(WHITE);

					bar(67, 242, 98, 262);
					xyprintf(68, 243, "%d", n);
					bar(165, 243, 195, 261);
					xyprintf(165, 242, "%d", m);
					bar(261, 243, 291, 261);
					xyprintf(261, 243, "%d", mine);
				}
				else if (msg.x > 110 && msg.x < 198 && msg.y>185 && msg.y < 203 && self == 1)
				{
					closegraph();
					a = Init_Check(m, n, mine);
					Gread_Map(m, n, p);
					Open_Check(m, n, mine, a, p, 0);
				}
				//����+
				else if (self == 1 && msg.x > 67 && msg.x < 82 && msg.y>222 && msg.y < 242)
				{
					bar(67, 242, 98, 262);
					if (n < 25)n++;
					xyprintf(68, 243, "%d", n);

				}
				//����-
				else if (self == 1 && msg.x > 67 && msg.x < 82 && msg.y>262 && msg.y < 282)
				{
					bar(67, 242, 98, 262);
					if (n >= 4) n--;
					xyprintf(68, 243, "%d", n);
				}
				//����+
				else if (self == 1 && msg.x > 164 && msg.x < 179 && msg.y > 222 && msg.y < 242)
				{
					bar(165, 243, 195, 261);
					if (m < 26) m++;
					xyprintf(165, 243, "%d", m);
				}
				//����-
				else if (self == 1 && msg.x > 164 && msg.x < 179 && msg.y > 262 && msg.y < 282)
				{
					bar(165, 243, 195, 261);
					if (m > 4) m--;
					xyprintf(165, 243, "%d", m);
				}
				//����+
				else if (self == 1 && msg.x > 260 && msg.x < 275 && msg.y > 222 && msg.y < 242)
				{
					bar(261, 243, 291, 261);
					if (mine < m*n) mine++;
					xyprintf(261, 243, "%d", mine);
				}
				//����-
				else if (self == 1 && msg.x > 260 && msg.x < 275 && msg.y > 262 && msg.y < 282)
				{
					bar(261, 243, 291, 261);
					if (mine > 1) mine--;
					xyprintf(261, 243, "%d", mine);
				}
				//���˳ɼ���Ϣ
				else if (msg.x > 209 && msg.x < 299 && msg.y>0 && msg.y < 15)
				{
					closegraph();
					Self_Interface(p);
				}
				else if (msg.x > 230 && msg.x < 299 && msg.y>20 && msg.y < 35)
				{
					setfont(15, 12, "����");
					bar(254, 36, 299, 51);
					outtextxy(254, 36, "��");
					bar(254, 52, 299, 67);
					outtextxy(254, 52, "��ͨ");
					bar(254, 68, 299, 83);
					outtextxy(254, 68, "����");
					setfont(20, 15, "����");
					fla = 1;
				}
				else if (msg.x > 254 && msg.x < 299 && msg.y>36 && msg.y < 51 && fla == 1) { closegraph(); Ranking_List_Interface(p, 1); }
				else if (msg.x > 254 && msg.x < 299 && msg.y>52 && msg.y < 67 && fla == 1) { closegraph(); Ranking_List_Interface(p, 2); }
				else if (msg.x > 254 && msg.x < 299 && msg.y>68 && msg.y < 83 && fla == 1) { closegraph(); Ranking_List_Interface(p, 3); }
			}
		}
	}
	//closegraph();
}

//������Ϊ0ʱ����Χ�ĸ����Զ�����
void Open_Around(Check *a, int i, int m, int num, int x, int y)
{
	a[i].n = 1;                      //��ʾ�Ѿ�ִ�й�Open_Around()
	 //���϶���							
	if (i == 0)
	{
		Printf(a ,x + 22, y + 2, i + 1);//��
		Printf(a, x + 2, y + 22, i + m);;//��
		Printf(a, x + 22, y + 22, i + m + 1);//����
		a[i + 1].if_open = 1;
		a[i + m].if_open = 1;
		a[i + m + 1].if_open = 1;
		if (a[i + 1].around_mine == 0 && a[i + 1].n == 0) Open_Around(a, i + 1, m, num, x + 20, y);
		if (a[i + m].around_mine == 0 && a[i + m].n == 0) Open_Around(a, i + m, m, num, x, y + 20);
		if (a[i + m + 1].around_mine == 0 && a[i + m + 1].n == 0) Open_Around(a, i + m + 1, m, num, x + 20, y + 20);
	}

	//����һ����
	else if (i > 0 && i < m - 1)
	{
		Printf(a, x - 18, y + 2, i - 1);//��
		Printf(a, x + 22, y + 2, i + 1); //��
		Printf(a, x - 18, y + 22, i + m - 1);//����
		Printf(a, x + 2, y + 22, i + m);//��
		Printf(a, x + 22, y + 22, i + m + 1);//����
		a[i - 1].if_open = 1;
		a[i + 1].if_open = 1;
		a[i + m - 1].if_open = 1;
		a[i + m].if_open = 1;
		a[i + m + 1].if_open = 1;
		if (a[i - 1].around_mine == 0 && a[i - 1].n == 0) Open_Around(a, i - 1, m, num, x - 20, y);
		if (a[i + 1].around_mine == 0 && a[i + 1].n == 0) Open_Around(a, i + 1, m, num, x + 20, y);
		if (a[i + m - 1].around_mine == 0 && a[i + m - 1].n == 0) Open_Around(a, i + m - 1, m, num, x - 20, y + 20);
		if (a[i + m].around_mine == 0 && a[i + m].n == 0) Open_Around(a, i + m, m, num, x, y + 20);
		if (a[i + m + 1].around_mine == 0 && a[i + m + 1].n == 0) Open_Around(a, i + m + 1, m, num, x + 20, y + 20);
	}

	//���϶���
	else if (i == m - 1)
	{
		Printf(a, x - 18, y + 2, i - 1);//��
		Printf(a, x - 18, y + 22, i + m - 1); //����
		Printf(a, x + 2, y + 22, i + m); //��
		a[i - 1].if_open = 1;
		a[i + m - 1].if_open = 1;
		a[i + m].if_open = 1;
		if (a[i - 1].around_mine == 0 && a[i - 1].n == 0) Open_Around(a, i - 1, m, num, x - 20, y);
		if (a[i + m - 1].around_mine == 0 && a[i + m - 1].n == 0) Open_Around(a, i + m - 1, m, num, x - 20, y + 20);
		if (a[i + m].around_mine == 0 && a[i + m].n == 0) Open_Around(a, i + m, m, num, x, y + 20);
	}

	//����һ����(�������)
	else if (i%m == 0 && i != 0 && i != num - m)
	{
		Printf(a, x + 2, y - 18, i - m); //��
		Printf(a, x + 22, y - 18, i - m + 1); //����
		Printf(a, x + 22, y + 2, i + 1);  //��
		Printf(a, x + 2, y + 22, i + m);//��
		Printf(a, x + 22, y + 22, i + m + 1); //����
		a[i - m].if_open = 1;
		a[i - m + 1].if_open = 1;
		a[i + 1].if_open = 1;
		a[i + m].if_open = 1;
		a[i + m + 1].if_open = 1;
		if (a[i - m].around_mine == 0 && a[i - m].n == 0) Open_Around(a, i - m, m, num, x, y - 20);
		if (a[i - m + 1].around_mine == 0 && a[i - m + 1].n == 0) Open_Around(a, i - m + 1, m, num, x + 20, y - 20);
		if (a[i + 1].around_mine == 0 && a[i + 1].n == 0) Open_Around(a, i + 1, m, num, x + 20, y);
		if (a[i + m].around_mine == 0 && a[i + m].n == 0) Open_Around(a, i + m, m, num, x, y + 20);
		if (a[i + m + 1].around_mine == 0 && a[i + m + 1].n == 0) Open_Around(a, i + m + 1, m, num, x + 20, y + 20);

	}

	//����һ����(�������)
	else if ((i + 1) % m == 0 && i != m - 1 && i != num - 1)
	{
		Printf(a, x - 18, y - 18, i - m - 1);//����
		Printf(a, x + 2, y - 18, i - m); //��
		Printf(a, x - 18, y + 2, i - 1); //��
		Printf(a, x - 18, y + 22, i + m - 1);//����
		Printf(a, x + 2, y + 22, i + m); //��
		a[i - m - 1].if_open = 1;
		a[i - m].if_open = 1;
		a[i - 1].if_open = 1;
		a[i + m - 1].if_open = 1;
		a[i + m].if_open = 1;
		if (a[i - m - 1].around_mine == 0 && a[i - m - 1].n == 0) Open_Around(a, i - m - 1, m, num, x - 20, y - 20);
		if (a[i - m].around_mine == 0 && a[i - m].n == 0) Open_Around(a, i - m, m, num, x, y - 20);
		if (a[i - 1].around_mine == 0 && a[i - 1].n == 0) Open_Around(a, i - 1, m, num, x - 20, y);
		if (a[i + m - 1].around_mine == 0 && a[i + m - 1].n == 0) Open_Around(a, i + m - 1, m, num, x - 20, y + 20);
		if (a[i + m].around_mine == 0 && a[i + m].n == 0) Open_Around(a, i + m, m, num, x, y + 20);
	}

	//���¶���
	else if (i == num - m)
	{
		Printf(a, x + 2, y - 18, i - m);//��
		Printf(a, x + 22, y - 18, i - m + 1); //����
		Printf(a, x + 22, y + 2, i + 1); //��
		a[i - m].if_open = 1;
		a[i - m + 1].if_open = 1;
		a[i + 1].if_open = 1;
		if (a[i - m].around_mine == 0 && a[i - m].n == 0) Open_Around(a, i - m, m, num, x, y - 20);
		if (a[i - m + 1].around_mine == 0 && a[i - m + 1].n == 0) Open_Around(a, i - m + 1, m, num, x + 20, y - 20);
		if (a[i + 1].around_mine == 0 && a[i + 1].n == 0) Open_Around(a, i + 1, m, num, x + 20, y);
	}

	//����һ����(�������)
	else if (i > num - m && i < num - 1)
	{ 
		Printf(a, x - 18, y - 18, i - m - 1);//����
		Printf(a, x + 2, y - 18, i - m);//��
		Printf(a, x + 22, y - 18, i - m + 1); //����
		Printf(a, x - 18, y + 2, i - 1);//��
		Printf(a, x + 22, y + 2, i + 1);   //��
		a[i - m - 1].if_open = 1;
		a[i - m].if_open = 1;
		a[i - m + 1].if_open = 1;
		a[i - 1].if_open = 1;
		a[i + 1].if_open = 1;
		if (a[i - m - 1].around_mine == 0 && a[i - m - 1].n == 0) Open_Around(a, i - m - 1, m, num, x - 20, y - 20);
		if (a[i - m].around_mine == 0 && a[i - m].n == 0) Open_Around(a, i - m, m, num, x, y - 20);
		if (a[i - m + 1].around_mine == 0 && a[i - m + 1].n == 0) Open_Around(a, i - m + 1, m, num, x + 20, y - 20);
		if (a[i - 1].around_mine == 0 && a[i - 1].n == 0) Open_Around(a, i - 1, m, num, x - 20, y);
		if (a[i + 1].around_mine == 0 && a[i + 1].n == 0) Open_Around(a, i + 1, m, num, x + 20, y);
	}

	//���¶���
	else if (i == num - 1)
	{
		Printf(a, x - 18, y - 18, i - m - 1);
		Printf(a, x + 2, y - 18, i - m);
		Printf(a, x - 18, y + 2, i - 1);
		a[i - m - 1].if_open = 1;
		a[i - m].if_open = 1;
		a[i - 1].if_open = 1;
		if (a[i - m - 1].around_mine == 0 && a[i - m - 1].n == 0) Open_Around(a, i - m - 1, m, num, x - 20, y - 20);
		if (a[i - m].around_mine == 0 && a[i - m].n == 0) Open_Around(a, i - m, m, num, x, y - 20);
		if (a[i - 1].around_mine == 0 && a[i - 1].n == 0) Open_Around(a, i - 1, m, num, x - 20, y);
	}

	//�ڲ����Ÿ����Ӱ�Χ�ĵĸ���
	else
	{
		Printf(a, x - 18, y - 18, i - m - 1);
		Printf(a, x + 2, y - 18, i - m);
		Printf(a, x + 22, y - 18, i - m + 1);
		Printf(a, x - 18, y + 2, i - 1);
		Printf(a, x + 22, y + 2, i + 1);
		Printf(a, x - 18, y + 22, i + m - 1);
		Printf(a, x + 2, y + 22, i + m);
		Printf(a, x + 22, y + 22, i + m + 1);
		a[i - m - 1].if_open = 1;
		a[i - m].if_open = 1;
		a[i - m + 1].if_open = 1;
		a[i - 1].if_open = 1;
		a[i + 1].if_open = 1;
		a[i + m - 1].if_open = 1;
		a[i + m].if_open = 1;
		a[i + m + 1].if_open = 1;
		if (a[i - m - 1].around_mine == 0 && a[i - m - 1].n == 0) Open_Around(a, i - m - 1, m, num, x - 20, y - 20);
		if (a[i - m].around_mine == 0 && a[i - m].n == 0) Open_Around(a, i - m, m, num, x, y - 20);
		if (a[i - m + 1].around_mine == 0 && a[i - m + 1].n == 0) Open_Around(a, i - m + 1, m, num, x + 20, y - 20);
		if (a[i - 1].around_mine == 0 && a[i - 1].n == 0) Open_Around(a, i - 1, m, num, x - 20, y);
		if (a[i + 1].around_mine == 0 && a[i + 1].n == 0) Open_Around(a, i + 1, m, num, x + 20, y);
		if (a[i + m - 1].around_mine == 0 && a[i + m - 1].n == 0) Open_Around(a, i + m - 1, m, num, x - 20, y + 20);
		if (a[i + m].around_mine == 0 && a[i + m].n == 0) Open_Around(a, i + m, m, num, x, y + 20);
		if (a[i + m + 1].around_mine == 0 && a[i + m + 1].n == 0) Open_Around(a, i + m + 1, m, num, x + 20, y + 20);
	}


}

//�򿪷���ʱ������ɫ��ʽ���������
void Printf(Check *a,int x, int y, int i)
{
	setfillcolor(WHITE);
	bar(x, y, x + 17, y + 17);
	if (a[i].around_mine == 1) { setcolor(EGERGB(0, 0, 205)); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 2) { setcolor(EGERGB(0, 128, 0)); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 3) { setcolor(EGERGB(165, 42, 42)); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 4) { setcolor(EGERGB(65, 105, 225)); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 5) { setcolor(EGERGB(178, 34, 34)); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 6) { setcolor(EGERGB(72, 209, 204)); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 7) { setcolor(BLACK); xyprintf(x, y, "%d", a[i].around_mine); }
	else if (a[i].around_mine == 8) { setcolor(EGERGB(128, 128, 128)); xyprintf(x, y, "%d", a[i].around_mine); }
	setcolor(RED);
}

