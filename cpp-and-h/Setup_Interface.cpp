#include<graphics.h>
#include"Mine_Sweeper.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void Setup_Interface(Player *p)
{
	initgraph(500, 400);
	int background = 4;
	int flag = 0;

	MUSIC music;

	Player *pla = (Player *)malloc(sizeof(Player));
	FILE *fp, *fq;

	//����
	PIMAGE img;
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

	PIMAGE p1 = newimage();
	PIMAGE p2 = newimage();
	PIMAGE p3 = newimage();
	PIMAGE p4 = newimage();
	PIMAGE p5 = newimage();
	PIMAGE p6 = newimage();
	PIMAGE p7 = newimage();
	PIMAGE p8 = newimage();
	getimage(p1, "Background\\1_300.jpg");
	getimage(p2, "Background\\2_300.jpg");
	getimage(p3, "Background\\3_300.jpg");
	getimage(p4, "Background\\4_300.jpg");
	getimage(p5, "Background\\5_300.jpg");
	getimage(p6, "Background\\6_300.jpg");
	getimage(p7, "Background\\7_300.jpg");
	getimage(p8, "Background\\8_300.jpg");


	//��ʾ
	bar(0, 0, 59, 19);
	outtextxy(0, 0, "����");
	bar(439, 0, 499, 19);
	outtextxy(439, 0, "����");
	outtextxy(0, 159, "����:");
	bar(80,159,110,179);
	bar(416,159,446,179);
	outtextxy(80, 159, "<-");
	outtextxy(416, 159, "->");

	bar(114, 19, 414, 319);       //ѡ�񱳾� 
	putimage(114, 19, p8);

	//outtextxy(0,359,"����:");
	//outtextxy(80, 359, "<-");
	//outtextxy(416, 359, "->");
	//bar(114, 359, 414, 379);     //����

	//����
	for (; is_run(); delay_fps(60)) {

		//��ȡ�����Ϣ
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//����
			if (msg.x < 59 && msg.y < 19 && msg.is_left() && msg.is_down())
			{
				
				delimage(p1);
				delimage(p2);
				delimage(p3);
				delimage(p4);
				delimage(p5);
				delimage(p6);
				delimage(p7);
				delimage(p8);
				closegraph();
                Main_Interface(p);
			}
			//�����л�ͼƬ
			if (msg.x > 80 && msg.x < 110 && msg.y>159 && msg.y < 179 && msg.is_left() && msg.is_down())
			{
				flag = 1;
				if (background > 1)
				{
					background--;
					setfillcolor(WHITE);
					bar(114, 19, 414, 319);
					if (background == 1) putimage(114, 19, p1);
					else if (background == 2) putimage(114, 19, p2);
					else if (background == 3) putimage(114, 19, p3);
					else if (background == 4) putimage(114, 19, p4);
					else if (background == 5) putimage(114, 19, p5);
					else if (background == 6) putimage(114, 19, p6);
					else if (background == 7) putimage(114, 19, p7);
					else if (background == 8) putimage(114, 19, p8);
				}
			}
			if (msg.x > 416 && msg.x < 446 && msg.y>159 && msg.y < 179 && msg.is_left() && msg.is_down())
			{
				flag = 1;
				if (background < 8)
				{
					background++;
					setfillcolor(WHITE);
					bar(114, 19, 414, 319);
					if (background == 1) putimage(114, 19, p1);
					else if (background == 2) putimage(114, 19, p2);
					else if (background == 3) putimage(114, 19, p3);
					else if (background == 4) putimage(114, 19, p4);
					else if (background == 5) putimage(114, 19, p5);
					else if (background == 6) putimage(114, 19, p6);
					else if (background == 7) putimage(114, 19, p7);
					else if (background == 8) putimage(114, 19, p8);
				}
			}
			if (flag == 1) p->background = background;
			if (msg.x > 439 && msg.x < 499 && msg.y>0 && msg.y < 19 && msg.is_left() && msg.is_down())
			{
				if ((fp = fopen(FilePath, "r")) == NULL || (fq = fopen(NewFilePath, "w")) == NULL)
				{
					outtextxy(144, 359, "��������ʧ�ܣ�");
					break;
				}
				fwrite(p, sizeof(Player), 1, fq);          //�޸ĺ����Ϣд��
				fread(pla, sizeof(Player), 1, fp);
				while (!feof(fp))
				{
					if (strcmp(pla->user_name, p->user_name) != 0)
					{
						fwrite(pla, sizeof(Player), 1, fq);        //��ԭ�ļ�����Ϣд��
					}
					fread(pla, sizeof(Player), 1, fp);
				}
				fclose(fp);
				fclose(fq);
				_unlink("data\\mine_sweeper.dat");                 //ɾ���ļ�
				rename("data\\temp.dat", "data\\mine_sweeper.dat");      //�޸��ļ���
				//system("DEL mine_sweeper.dat");                   //���ֶ���
				//system("RENAME temp.dat mine_sweeper.dat");
				//music.OpenFile("music\\successful.mp3");
				//music.Play();
				outtextxy(144, 359, "����ɹ���");
				//music.Close();
			}
		}
	}
	getch();
	closegraph();
}
