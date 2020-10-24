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
	Player *p = (Player *)malloc(sizeof(Player));   //开辟一个结构体空间
	p->background = 4;       //
	p->user_score.simple = 0;     // 数据默认化
	p->user_score.common = 0;     // 数据默认化
	p->user_score.hard = 0;     // 数据默认化

	Signin(p);
}


//注册
void Signup(Player *p)
{
	initgraph(400, 240);
	setcaption("注册");
	setbkcolor(EGERGB(0, 255, 255));
	setcolor(BLACK);
	setfont(20, 15, "楷体");

	PIMAGE img;
	img = newimage();
	getimage(img, "background\\head.jpg");

	FILE *fp, *fq;
	Player pla;

	int flag = 0;  //1表示文件打开失败，2表示成功注册，3表示用户名重复

	sys_edit button_name;
	sys_edit button_password;

	//rectangle(120, 99, 334, 119);
	button_name.create(false);    //单行输入
	button_name.move(120, 99);   //位置
	button_name.size(214, 25);    //输入框大小
	button_name.setfont(17, 17, "黑体");   //输入框字体
	button_name.setmaxlen(NameLen);
	button_name.setbgcolor(YELLOW);
	button_name.setcolor(BLACK);
	button_name.visable(true);


	button_password.create(false);
	button_password.move(120, 129);
	button_password.size(214, 25);
	button_password.setfont(17, 17, "黑体");
	button_password.setmaxlen(PasswordLen);
	button_password.setbgcolor(YELLOW);
	button_password.setcolor(BLACK);
	button_password.visable(true);
	rectangle(120, 129, 334, 149);


	//delay_fps(60)  每秒执行60次
	for (; is_run(); delay_fps(60)) {

		cleardevice();
		putimage(170, 30, img);
		outtextxy(49, 99, "用户:");
		outtextxy(49, 129, "密码:");
		setcolor(BLACK);
		outtextxy(169, 179, "注册");
		rectangle(169, 179, 229, 199);

		setfont(10, 7, "楷体");
		outtextxy(344, 219, "登录");
		rectangle(344, 219, 374, 229);
		setfont(20, 15, "楷体");

		if (flag == 1) outtextxy(0, 0, "文件创建失败！请重登一下游戏试试！");
		else if (flag == 2) outtextxy(0, 0, "注册成功！");
		else if (flag == 3) outtextxy(0, 0, "用户名重复！请重新输入！\n");
		else if (flag == 4) { outtextxy(0, 0, "请输入");}
		//获取鼠标消息
		if (mousemsg()) {
			mouse_msg msg = getmouse();
			//注册按钮
			if (msg.x > 160 && msg.x < 229 && msg.y>179 && msg.y < 199 && msg.is_left() && msg.is_down())
			{
				//获取用户输入
				button_name.gettext(NameLen, p->user_name);
				button_password.gettext(PasswordLen, p->user_password);
				//判断用户是否输入
				if (!strlen(p->user_name) || !strlen(p->user_password)) {
					flag = 4;
					continue;
				}
				//判断文件是否建立并打开
				if ((fp = fopen(FilePath, "a+")) == NULL)
				{
					if ((fp = fopen(FilePath, "w")) == NULL)
					{
						flag = 1;   //文件打开失败
						exit;
					}
				}

				//判断重名
				fq = fp;                   //方便重名判断
				fread(&pla, sizeof(Player), 1, fq);
				while (!feof(fq))
				{
					if (strcmp(pla.user_name, p->user_name) == 0)
					{
						flag = 3;   //用户名重复
						fclose(fq);
						break;
					}
					fread(&pla, sizeof(Player), 1, fq);
				}

				//写入用户信息，并进入游戏
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
			//登录按钮
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

//登录
void Signin(Player *p)
{
	initgraph(400, 240);
	setcaption("登录");
	setbkcolor(EGERGB(0, 191, 255));
	setfillcolor(EGERGB(0, 191, 255));
	setcolor(BLACK);
	setfont(20, 15, "楷体");

	PIMAGE img;
	img = newimage();
	getimage(img, "background\\head.jpg");

	FILE *fq;
	Player pla;

	sys_edit button_name;
	sys_edit button_password;

	//rectangle(120, 99, 334, 119);
	button_name.create(false);    //单行输入
	button_name.move(120, 99);   //位置
	button_name.size(214, 25);    //输入框大小
	button_name.setfont(17, 17, "黑体");   //输入框字体
	button_name.setmaxlen(NameLen);
	button_name.setbgcolor(YELLOW);
	button_name.setcolor(BLACK);
	button_name.visable(true);


	button_password.create(false);
	button_password.move(120, 129);
	button_password.size(214, 25);
	button_password.setfont(17, 17, "黑体");
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
		outtextxy(49, 99, "用户:");
		outtextxy(49, 129, "密码:");
		setcolor(BLACK);
		outtextxy(169, 179, "登录");
		rectangle(169, 179, 229, 199);

		setfont(10, 7, "楷体");
		outtextxy(344, 219, "注册");
		rectangle(344, 219, 374, 229);
		setfont(20, 15, "楷体");

		if (flag == 1)
		{
			outtextxy(0, 0, "用户名或密码错误！");
		}
		if (flag == 2)
		{
			outtextxy(0, 0, "登录成功！");
		}
		if (flag == 3)
		{
			outtextxy(0, 0, "请输入用户名和密码!");
		}

		//获取鼠标消息
		if (mousemsg()) {
			mouse_msg msg = getmouse();
			//登录按钮
			if (msg.x > 160 && msg.x < 229 && msg.y>179 && msg.y < 199 && msg.is_left() && msg.is_down())
			{
				button_name.gettext(NameLen, p->user_name);
				button_password.gettext(PasswordLen, p->user_password);

				//判断是否输入数据
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
						fclose(fq);                     //这个出了大问题，之前没写，导致后面保存数据操作出现问题
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
				flag = 1;        //用户名或密码错误
			}

			//注册按钮
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