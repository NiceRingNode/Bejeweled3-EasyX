#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
#include"audio_control.hpp"
using namespace std;

class option :public audiocontrol//主菜单的选项，音量、音效
{
public:
	option() = default;
	~option() = default;
	explicit option(int last_music_x, int last_sound_x) :last_music_x_left(last_music_x), last_sound_x_left(last_sound_x) {}
	//构造函数与基类的其他成员不同，不能被派生类继承，因此为了初始化基类中的成员变量，需要在派生类中调用基类的构造函数(即显式调用)，如果派送类没有调用则默认调用基类的无参构造函数(即隐式调用)
	void print_the_options_list()
	{
		//cleardevice();
		BeginBatchDraw();
		IMAGE img;
		loadimage(&img, _T("..\\Images\\1.jpg"));
		auto max_x = getmaxx();
		auto max_y = getmaxy();
		putimage(0, 0, max_x + 1, max_y + 1, &img, 0, 0, SRCCOPY);
		setbkmode(TRANSPARENT);
		COLORREF linecolor = RGB(233, 231, 89);
		COLORREF textcolor1 = RGB(255, 127, 0);
		COLORREF textcolor2 = RGB(255, 25, 112);
		COLORREF fillcolor = RGB(240, 183, 155);//肤色
		COLORREF framecolor = RGB(138, 43, 226);//紫色
		COLORREF buttoncolor = RGB(255, 0, 255);//深粉红
		setlinecolor(linecolor);
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
		setfillcolor(fillcolor);
		fillroundrect(110, 150, 530, 410, 10, 10);//420*260
		setbkmode(TRANSPARENT);//文字背景就不是黑了
		settextstyle(30, 15, _T("Courier New"));
		settextcolor(textcolor1);
		TCHAR option[] = _T("Option");
		outtextxy(275, 180, option);//W:275-365,H:160-190
		settextcolor(textcolor2);
		TCHAR music[] = _T("Music");//音乐
		TCHAR sound[] = _T("Sound");//音效
		TCHAR background[] = _T("Background");
		TCHAR back_out[] = _T("Back");
		outtextxy(135, 250, music);//W:135-210,H:250-280
		outtextxy(135, 290, sound);//W:135-210,H:290-320
		outtextxy(225, 350, background);//W:225-375,H:350-380
		outtextxy(570, 520, back_out);//Help:W:570-630,H:520-550
		setfillcolor(framecolor);
		solidrectangle(230, 255, 510, 275);//W:230-510,H:255-275，音乐框，这三个是框
		solidrectangle(230, 295, 510, 315);//W:230-510,H:295-315，音效框
		solidrectangle(390, 350, 420, 380);//30*30,W:390-420,H:350-380，背景框
		setfillcolor(buttoncolor);
		solidrectangle(last_music_x_left, 252, last_music_x_left + 26, 278);//26*26,W:357-383,H:252-278，音乐
		solidrectangle(last_sound_x_left, 292, last_sound_x_left + 26, 318);//26*26,W:357-383,H:292-318，音效
		EndBatchDraw();
	}
	int is_in_the_click_rect(int x, int y)
	{
		if (230 <= x && x <= 510 && 250 <= y && y <= 280) return 1;//在music那里
		if (230 <= x && x <= 510 && 290 <= y && y <= 320) return 2;//在sound那里，一点即拖
		if (390 <= x && x <= 420 && 350 <= y && y <= 380) return 3;//在background那里
		if (570 <= x && x <= 630 && 520 <= y && y <= 550) return 4;//在back那里，back是返回上一层
		return 0;
	}
	void manipulate_all_options()
	{
		print_the_options_list();
		MOUSEMSG msg;
		while (true)
		{
			int ret = -1;
			msg = GetMouseMsg();
			ret = is_in_the_click_rect(msg.x, msg.y);
			if (ret == 1) manipulate_music();
			if (ret == 2) manipulate_sound();
			if (ret == 4)
			{
				if (msg.uMsg == WM_LBUTTONDOWN)
					break;
			}
		}
	}
	void manipulate_music()//现在鼠标已经在音乐的那个框条那里了
	{
		MOUSEMSG msg;
		int step = 67;//因为它会无端端+1-1
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.x < 230 || msg.x > 510 || msg.y < 250 || msg.y > 280) break;
			if (msg.uMsg == WM_LBUTTONDOWN)//左击了
			{
				COLORREF fillcolor = RGB(240, 183, 155);//肤色
				COLORREF framecolor = RGB(138, 43, 226);//紫色
				COLORREF buttoncolor = RGB(255, 0, 255);//深粉红
				/*while (mousedown == 1 && mouseup == 0)//如果是拖着走，1表示鼠标按下了
				{
					if (msg.uMsg == WM_MOUSEMOVE)
					{
						setfillcolor(BLACK);//先把整个框消除掉，包括那个滑块
						solidrectangle(230, 250, 510, 280);
						setfillcolor(framecolor);
						solidrectangle(230, 255, 510, 275);//框重新打印
						setfillcolor(fillcolor);
						solidrectangle(230, 250, 510, 254);//这个数才是对的
						solidrectangle(230, 276, 510, 280);//因为多消除了，要补齐
						solidrectangle(227, 250, 229, 280);
						solidrectangle(511, 250, 513, 280);
						int temp_x = msg.x;//y 不用看的
						int temp_x_num = (temp_x - 230) / 20;//拿到序号,减了再除
						int temp_x_left = 230 + temp_x_num * 20;//这个是预计中正方形的左边的x坐标
						int button_x_left = temp_x_left - 3;//这个就是滑块的最左边的坐标
						setfillcolor(buttoncolor);
						solidrectangle(button_x_left, 252, button_x_left + 26, 278);//重新打印滑块
					}
					if (msg.uMsg == WM_LBUTTONUP) mouseup = 1;//1表示鼠标弹起了
					if (mouseup == 1) break;
				}*/
				//不拖着走
				setfillcolor(BLACK);//先把整个框消除掉，包括那个滑块
				solidrectangle(230, 250, 510, 280);
				setfillcolor(framecolor);
				solidrectangle(230, 255, 510, 275);//框重新打印
				setfillcolor(fillcolor);
				solidrectangle(230, 250, 510, 254);//这个数才是对的
				solidrectangle(230, 276, 510, 280);//因为多消除了，要补齐
				solidrectangle(227, 250, 229, 280);
				solidrectangle(511, 250, 513, 280);
				int temp_x = msg.x;//y 不用看的
				int temp_x_num = (temp_x - 230) / 20;//拿到序号,减了再除
				if (temp_x == 510) temp_x_num -= 1;//510那里拉胯
				int temp_x_left = 230 + temp_x_num * 20;//这个是预计中正方形的左边的x坐标
				int button_x_left = temp_x_left - 3;//这个就是滑块的最左边的坐标
				setfillcolor(buttoncolor);
				solidrectangle(button_x_left, 252, button_x_left + 26, 278);//重新打印滑块
				int scale = (last_music_x_left - button_x_left) / 20 + 1;//用last减，上面是减
				int tot_step = step * scale;
				adjust_music_volume(tot_step);
				last_music_x_left = button_x_left;
			}
		}
	}
	void manipulate_sound()//现在鼠标已经在音乐的那个框条那里了
	{
		MOUSEMSG msg;
		int step = 67;//因为它会无端端+1-1
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.x < 230 || msg.x > 510 || msg.y < 290 || msg.y > 320) break;
			if (msg.uMsg == WM_LBUTTONDOWN)//左击了
			{
				//其实290和320是大了点的，不过为了效果好点
				COLORREF fillcolor = RGB(240, 183, 155);//肤色
				COLORREF framecolor = RGB(138, 43, 226);//紫色
				COLORREF buttoncolor = RGB(255, 0, 255);//深粉红
				/*while (mousedown == 1 && mouseup == 0)//如果是拖着走，1表示鼠标按下了
				{
					if (msg.uMsg == WM_MOUSEMOVE)
					{
						setfillcolor(BLACK);//先把整个框消除掉，包括那个滑块
						solidrectangle(230, 250, 510, 280);
						setfillcolor(framecolor);
						solidrectangle(230, 255, 510, 275);//框重新打印
						setfillcolor(fillcolor);
						solidrectangle(230, 250, 510, 254);//这个数才是对的
						solidrectangle(230, 276, 510, 280);//因为多消除了，要补齐
						solidrectangle(227, 250, 229, 280);
						solidrectangle(511, 250, 513, 280);
						int temp_x = msg.x;//y 不用看的
						int temp_x_num = (temp_x - 230) / 20;//拿到序号,减了再除
						int temp_x_left = 230 + temp_x_num * 20;//这个是预计中正方形的左边的x坐标
						int button_x_left = temp_x_left - 3;//这个就是滑块的最左边的坐标
						setfillcolor(buttoncolor);
						solidrectangle(button_x_left, 252, button_x_left + 26, 278);//重新打印滑块
					}
					if (msg.uMsg == WM_LBUTTONUP) mouseup = 1;//1表示鼠标弹起了
					if (mouseup == 1) break;
				}*/
				//不拖着走
				setfillcolor(BLACK);//先把整个框消除掉，包括那个滑块
				solidrectangle(230, 290, 510, 320);
				setfillcolor(framecolor);
				solidrectangle(230, 295, 510, 315);//框重新打印
				setfillcolor(fillcolor);
				solidrectangle(230, 290, 510, 294);//这个数才是对的
				solidrectangle(230, 316, 510, 320);//因为多消除了，要补齐
				solidrectangle(227, 290, 229, 320);
				solidrectangle(511, 290, 513, 320);
				int temp_x = msg.x;//y 不用看的
				int temp_x_num = (temp_x - 230) / 20;//拿到序号,减了再除
				if (temp_x == 510) temp_x_num -= 1;//510那里拉胯
				int temp_x_left = 230 + temp_x_num * 20;//这个是预计中正方形的左边的x坐标
				int button_x_left = temp_x_left - 3;//这个就是滑块的最左边的坐标
				setfillcolor(buttoncolor);
				solidrectangle(button_x_left, 292, button_x_left + 26, 318);//重新打印滑块
				int scale = (last_sound_x_left - button_x_left) / 20 + 1;//用last减，上面是减
				int tot_step = step * scale;
				adjust_sound_volume(tot_step);
				last_sound_x_left = button_x_left;
			}
		}
	}
	int last_music_x_left, last_sound_x_left;//没办法，因为要画图，这个是要记下来，不断更新，一开始是357
};