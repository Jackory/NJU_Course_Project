#pragma once
#include<Windows.h>
//�û����������궨λ����ɫ�ı�

//windows APi ������ɫ
#define redFont	244
#define blackFont 240
#define blueFont 241
#define greenFont 242

//���������ƶ��ķ���
#define Up 0
#define Down 1
#define Left 2
#define Right 3

//�����ϵ�������ʵ�ʿ���̨���ڽ����ת��
#define pos_x(i) (1 + i * 10)
#define pos_y(j) (4 + 4 * j)	

//ʵ�ʿ���̨�������������
#define _pos_x(i) (i-1)/10
#define _pos_y(i) (i-4)/4
void gotoXY(int x, int y);    //���궨λ
void setColor(int wAttributes);  //ѡ�����̨������ɫ
bool  IsKeyDown(int key);    //���Ƿ���
void HideCursor();        //���ع��
void ChangeTitle(const char* str);