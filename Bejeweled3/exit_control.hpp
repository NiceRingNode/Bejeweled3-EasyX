#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
using namespace std;

class exit_out
{
public:
	exit_out() = default;
	~exit_out() = default;

	void print_is_or_not()
	{
		COLORREF linecolor = RGB(176, 48, 96);
		COLORREF fillcolor = RGB(255, 160, 122);
		COLORREF textcolor = RGB(255, 52, 179);
		setlinecolor(linecolor);
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
		setfillcolor(fillcolor);
		fillroundrect(140, 180, 510, 380, 10, 10);//W:140-510,H:180-380
		fillroundrect(190, 280, 280, 350, 5, 5);
		fillroundrect(380, 280, 470, 350, 5, 5);
		settextstyle(30, 15, _T("Courier New"));
		settextcolor(textcolor);
		setbkmode(TRANSPARENT);
		TCHAR con[] = _T("Are you sure to exit?");
		TCHAR yes[] = _T("Yes");
		TCHAR no[] = _T("No");
		outtextxy(170, 220, con);//W:170-485,H:220-250
		outtextxy(215, 300, yes);//W:215-260,H:300-330
		outtextxy(410, 300, no);//W:410-440,H:300-330
	}
	bool is_in_yes_rect(int x, int y)
	{
		if (215 <= x && x <= 260 && 300 <= y && y <= 330) return true;
		return false;
	}
	bool is_in_no_rect(int x, int y)
	{
		if (410 <= x && x <= 440 && 300 <= y && y <= 330) return true;
		return false;
	}
	int exit_or_not()
	{
		MOUSEMSG msg;
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (is_in_yes_rect(msg.x, msg.y)) return 1;			//ÍË³ö
				else if (is_in_no_rect(msg.x, msg.y)) return 2;		//²»ÍË³ö
			}
		}
		return -1;
	}
};