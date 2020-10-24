#include<graphics.h>
#include"Mine_Sweeper.h"
#include<ege\sys_edit.h>
#include<stdio.h>
//#include<pthread.h>
//#pragma comment(lib,"x86/pthreadVC2.lib")

void Signup(Player *p);
void Signin(Player *p);

void main()
{
	Player *p = (Player *)malloc(sizeof(Player));   //����һ���ṹ��ռ�
	p->background = 4;       //
	p->user_score.simple = 0;     // ����Ĭ�ϻ�
	p->user_score.common = 0;     // ����Ĭ�ϻ�
	p->user_score.hard = 0;     // ����Ĭ�ϻ�

	Signin(p);
}


//ע��
void Signup(Player *p)
{
	initgraph(400, 240);
	setcaption("ע��");
	setbkcolor(EGERGB(0, 255, 255));
	setcolor(BLACK);
	setfont(20, 15, "����");

	PIMAGE img;
	img = newimage();
	getimage(img, "background\\head.jpg");

	FILE *fp, *fq;
	Player pla;

	int flag = 0;  //1��ʾ�ļ���ʧ�ܣ�2��ʾ�ɹ�ע�ᣬ3��ʾ�û����ظ�

	sys_edit button_name;
	sys_edit button_password;

	//rectangle(120, 99, 334, 119);
	button_name.create(false);    //��������
	button_name.move(120, 99);   //λ��
	button_name.size(214, 25);    //������С
	button_name.setfont(17, 17, "����");   //���������
	button_name.setmaxlen(NameLen);
	button_name.setbgcolor(YELLOW);
	button_name.setcolor(BLACK);
	button_name.visable(true);


	button_password.create(false);
	button_password.move(120, 129);
	button_password.size(214, 25);
	button_password.setfont(17, 17, "����");
	button_password.setmaxlen(PasswordLen);
	button_password.setbgcolor(YELLOW);
	button_password.setcolor(BLACK);
	button_password.visable(true);
	rectangle(120, 129, 334, 149);


	//delay_fps(60)  ÿ��ִ��60��
	for (; is_run(); delay_fps(60)) {

		cleardevice();
		putimage(170, 30, img);
		outtextxy(49, 99, "�û�:");
		outtextxy(49, 129, "����:");
		setcolor(BLACK);
		outtextxy(169, 179, "ע��");
		rectangle(169, 179, 229, 199);

		setfont(10, 7, "����");
		outtextxy(344, 219, "��¼");
		rectangle(344, 219, 374, 229);
		setfont(20, 15, "����");

		if (flag == 1) outtextxy(0, 0, "�ļ�����ʧ�ܣ����ص�һ����Ϸ���ԣ�");
		else if (flag == 2) outtextxy(0, 0, "ע��ɹ���");
		else if (flag == 3) outtextxy(0, 0, "�û����ظ������������룡\n");
		else if (flag == 4) { outtextxy(0, 0, "������");}
		//��ȡ�����Ϣ
		if (mousemsg()) {
			mouse_msg msg = getmouse();
			//ע�ᰴť
			if (msg.x > 160 && msg.x < 229 && msg.y>179 && msg.y < 199 && msg.is_left() && msg.is_down())
			{
				//��ȡ�û�����
				button_name.gettext(NameLen, p->user_name);
				button_password.gettext(PasswordLen, p->user_password);
				//�ж��û��Ƿ�����
				if (!strlen(p->user_name) || !strlen(p->user_password)) {
					flag = 4;
					continue;
				}
				//�ж��ļ��Ƿ�������
				if ((fp = fopen(FilePath, "a+")) == NULL)
				{
					if ((fp = fopen(FilePath, "w")) == NULL)
					{
						flag = 1;   //�ļ���ʧ��
						exit;
					}
				}

				//�ж�����
				fq = fp;                   //���������ж�
				fread(&pla, sizeof(Player), 1, fq);
				while (!feof(fq))
				{
					if (strcmp(pla.user_name, p->user_name) == 0)
					{
						flag = 3;   //�û����ظ�
						fclose(fq);
						break;
					}
					fread(&pla, sizeof(Player), 1, fq);
				}

				//д���û���Ϣ����������Ϸ
				if (feof(fq) != 0)
				{
					fwrite(p, sizeof(player), 1, fq);
					flag = 2;
					fclose(fp);
					button_name.destory();
					button_password.destory();
                    closegraph();
					delimage(img);
					MUSIC music;
					music.OpenFile("music\\background.mp3");
					music.Play(0);
					Main_Interface(p);
				}

			}
			//��¼��ť
			if (msg.x > 344 && msg.x < 374 && msg.y>219 && msg.y < 229 && msg.is_left() && msg.is_down())
			{
				delimage(img);
				button_name.destory();
				button_password.destory();
				closegraph();
				Signin(p);

			}
		}
	}
}

//��¼
void Signin(Player *p)
{
	initgraph(400, 240);
	setcaption("��¼");
	setbkcolor(EGERGB(0, 191, 255));
	setfillcolor(EGERGB(0, 191, 255));
	setcolor(BLACK);
	setfont(20, 15, "����");

	PIMAGE img;
	img = newimage();
	getimage(img, "background\\head.jpg");

	FILE *fq;
	Player pla;

	sys_edit button_name;
	sys_edit button_password;

	//rectangle(120, 99, 334, 119);
	button_name.create(false);    //��������
	button_name.move(120, 99);   //λ��
	button_name.size(214, 25);    //������С
	button_name.setfont(17, 17, "����");   //���������
	button_name.setmaxlen(NameLen);
	button_name.setbgcolor(YELLOW);
	button_name.setcolor(BLACK);
	button_name.visable(true);


	button_password.create(false);
	button_password.move(120, 129);
	button_password.size(214, 25);
	button_password.setfont(17, 17, "����");
	button_password.setmaxlen(PasswordLen);
	button_password.setbgcolor(YELLOW);
	button_password.setcolor(BLACK);
	button_password.visable(true);
	//rectangle(120, 129, 334, 149);


	int flag = 0;

		

	for (; is_run(); delay_fps(60))
	{
        cleardevice();
		putimage(170, 30, img);
		outtextxy(49, 99, "�û�:");
		outtextxy(49, 129, "����:");
		setcolor(BLACK);
		outtextxy(169, 179, "��¼");
		rectangle(169, 179, 229, 199);

		setfont(10, 7, "����");
		outtextxy(344, 219, "ע��");
		rectangle(344, 219, 374, 229);
		setfont(20, 15, "����");

		if (flag == 1)
		{
			outtextxy(0, 0, "�û������������");
		}
		if (flag == 2)
		{
			outtextxy(0, 0, "��¼�ɹ���");
		}
		if (flag == 3)
		{
			outtextxy(0, 0, "�������û���������!");
		}

		//��ȡ�����Ϣ
		if (mousemsg()) {
			mouse_msg msg = getmouse();
			//��¼��ť
			if (msg.x > 160 && msg.x < 229 && msg.y>179 && msg.y < 199 && msg.is_left() && msg.is_down())
			{
				button_name.gettext(NameLen, p->user_name);
				button_password.gettext(PasswordLen, p->user_password);

				//�ж��Ƿ���������
				if (!strlen(p->user_name) || !strlen(p->user_password)) {
					flag = 3;
					continue;
				}
				//
				if ((fq = fopen(FilePath, "r")) == NULL)
				{
					flag = 1;
					continue;
				}
				fread(&pla, sizeof(player), 1, fq);
				while (!feof(fq))
				{
					if (strcmp(p->user_name, pla.user_name) == 0 && strcmp(p->user_password, pla.user_password) == 0)
					{
						p->user_score = pla.user_score;
						p->background = pla.background;
						fclose(fq);                     //������˴����⣬֮ǰûд�����º��汣�����ݲ�����������
						button_name.destory();
						button_password.destory();
						closegraph();
						delimage(img);
						MUSIC music;
						music.OpenFile("music\\background.mp3");
						music.Play(0);
						Main_Interface(p);
					}
					fread(&pla, sizeof(player), 1, fq);
				}
				fclose(fq);
				flag = 1;        //�û������������
			}

			//ע�ᰴť
			if (msg.x > 344 && msg.x < 374 && msg.y>219 && msg.y < 229 && msg.is_left() && msg.is_down())
			{
				delimage(img);
				button_name.destory();
				button_password.destory();
				closegraph();
				Signup(p);

			}
		}
	}
}