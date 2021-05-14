#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
using namespace std;

class start_page
{
public:
	start_page() = default;
	~start_page() = default;
	void init_the_start_page()//��ͷҳ�棬���⣬ѡ���ʼ����¼
	{
		//cleardevice();
		BeginBatchDraw();
		IMAGE img;
		loadimage(&img, _T("..\\Images\\1.jpg"));
		auto max_x = getmaxx();
		auto max_y = getmaxy();
		putimage(0, 0, max_x + 1, max_y + 1, &img, 0, 0, SRCCOPY);
		setbkmode(TRANSPARENT);
		COLORREF orange = RGB(255, 127, 0);
		settextstyle(55, 30, _T("Courier New"));
		settextcolor(orange);
		TCHAR main_title[] = _T("Bejeweled3");//��Ҫ��stprintf_s
		outtextxy(165, 100, main_title);
		settextstyle(35, 20, _T("Courier New"));//H,W
		settextcolor(WHITE);
		TCHAR option[] = _T("Option");
		TCHAR start[] = _T("Start");
		TCHAR record[] = _T("Record");
		TCHAR help[] = _T("Help");
		TCHAR exit_out[] = _T("Exit");
		outtextxy(70, 270, option);//Option:W:70-190,H:270-305
		outtextxy(270, 300, start);//Start:W:270-370,H:300-335
		outtextxy(450, 270, record);//Record:W:450-570,H:270-305
		outtextxy(10, 520, help);//Help:W:10-90,H:520-555
		outtextxy(550, 520, exit_out);//Exit:W:550-630,H:520-555
		EndBatchDraw();
	}
	int is_in_the_click_rect(int x, int y)//�Ƿ��ڳ�ʼҳ����Ǹ��򣬴����x��y����굱ǰ������
	{
		if (70 <= x && x <= 190 && 270 <= y && y <= 305) return 1;  //1˵����option����
		if (270 <= x && x <= 370 && 300 <= y && y <= 335) return 2; //2˵����start����
		if (450 <= x && x <= 570 && 270 <= y && y <= 305) return 3; //3˵����record����
		if (10 <= x && x <= 30 && 520 <= y && y <= 555) return 4;   //4˵����help����
		if (550 <= x && x <= 630 && 520 <= y && y <= 555) return 5; //5˵����exit����
		return 0;
	}
	int jump_to_the_next_page()//ѡ����һ���࣬��Ϸ������һ���࣬��¼��һ����
	{
		MOUSEMSG msg;
		while (true)
		{
			int ret = -1;
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				ret = is_in_the_click_rect(msg.x, msg.y);
				if (ret > 0) return ret;
			}
		}
		return -1;
	}
};