#pragma once

//����
#define NameLen 13         //�û�������
#define PasswordLen 13     //���볤��
#define FilePath  "data\\mine_sweeper.dat"
#define NewFilePath "data\\temp.dat"           //��������ΪMine_Sweeping.dat  system()�����ִ�Сд
#define N 6      //���а��ϰ�����

typedef struct {
	int simple;   //��
	int common;   //��ͨ
	int hard;     //����
}Score;

//�û���Ϣ�ṹ��
typedef struct player {
	char user_name[NameLen];           //�û���
	char user_password[PasswordLen];   //�û�����
	//char *user_name;
	//char *user_password;
    Score  user_score;                   //�û���ʱ
	int background;                    //����������Ϣ
}Player;


//����
void Level_Interface(Player *p);
void* Main_Interface(void* q);
void Help_Interface(Player *p);
void Setup_Interface(Player *p);
void Self_Interface(Player *p);
void Ranking_List_Interface(Player *p,int level);

