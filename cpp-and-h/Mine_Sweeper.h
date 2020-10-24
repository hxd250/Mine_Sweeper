#pragma once

//常量
#define NameLen 13         //用户名长度
#define PasswordLen 13     //密码长度
#define FilePath  "data\\mine_sweeper.dat"
#define NewFilePath "data\\temp.dat"           //不能设置为Mine_Sweeping.dat  system()不区分大小写
#define N 6      //排行榜上榜人数

typedef struct {
	int simple;   //简单
	int common;   //普通
	int hard;     //困难
}Score;

//用户信息结构体
typedef struct player {
	char user_name[NameLen];           //用户名
	char user_password[PasswordLen];   //用户密码
	//char *user_name;
	//char *user_password;
    Score  user_score;                   //用户用时
	int background;                    //背景设置信息
}Player;


//函数
void Level_Interface(Player *p);
void* Main_Interface(void* q);
void Help_Interface(Player *p);
void Setup_Interface(Player *p);
void Self_Interface(Player *p);
void Ranking_List_Interface(Player *p,int level);

