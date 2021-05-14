#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
#include"audio_control.hpp"
using namespace std;

class option :public audiocontrol//���˵���ѡ���������Ч
{
public:
	option() = default;
	~option() = default;
	explicit option(int last_music_x, int last_sound_x) :last_music_x_left(last_music_x), last_sound_x_left(last_sound_x) {}
	//���캯��������������Ա��ͬ�����ܱ�������̳У����Ϊ�˳�ʼ�������еĳ�Ա��������Ҫ���������е��û���Ĺ��캯��(����ʽ����)�����������û�е�����Ĭ�ϵ��û�����޲ι��캯��(����ʽ����)
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
		COLORREF fillcolor = RGB(240, 183, 155);//��ɫ
		COLORREF framecolor = RGB(138, 43, 226);//��ɫ
		COLORREF buttoncolor = RGB(255, 0, 255);//��ۺ�
		setlinecolor(linecolor);
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
		setfillcolor(fillcolor);
		fillroundrect(110, 150, 530, 410, 10, 10);//420*260
		setbkmode(TRANSPARENT);//���ֱ����Ͳ��Ǻ���
		settextstyle(30, 15, _T("Courier New"));
		settextcolor(textcolor1);
		TCHAR option[] = _T("Option");
		outtextxy(275, 180, option);//W:275-365,H:160-190
		settextcolor(textcolor2);
		TCHAR music[] = _T("Music");//����
		TCHAR sound[] = _T("Sound");//��Ч
		TCHAR background[] = _T("Background");
		TCHAR back_out[] = _T("Back");
		outtextxy(135, 250, music);//W:135-210,H:250-280
		outtextxy(135, 290, sound);//W:135-210,H:290-320
		outtextxy(225, 350, background);//W:225-375,H:350-380
		outtextxy(570, 520, back_out);//Help:W:570-630,H:520-550
		setfillcolor(framecolor);
		solidrectangle(230, 255, 510, 275);//W:230-510,H:255-275�����ֿ��������ǿ�
		solidrectangle(230, 295, 510, 315);//W:230-510,H:295-315����Ч��
		solidrectangle(390, 350, 420, 380);//30*30,W:390-420,H:350-380��������
		setfillcolor(buttoncolor);
		solidrectangle(last_music_x_left, 252, last_music_x_left + 26, 278);//26*26,W:357-383,H:252-278������
		solidrectangle(last_sound_x_left, 292, last_sound_x_left + 26, 318);//26*26,W:357-383,H:292-318����Ч
		EndBatchDraw();
	}
	int is_in_the_click_rect(int x, int y)
	{
		if (230 <= x && x <= 510 && 250 <= y && y <= 280) return 1;//��music����
		if (230 <= x && x <= 510 && 290 <= y && y <= 320) return 2;//��sound���һ�㼴��
		if (390 <= x && x <= 420 && 350 <= y && y <= 380) return 3;//��background����
		if (570 <= x && x <= 630 && 520 <= y && y <= 550) return 4;//��back���back�Ƿ�����һ��
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
	void manipulate_music()//��������Ѿ������ֵ��Ǹ�����������
	{
		MOUSEMSG msg;
		int step = 67;//��Ϊ�����޶˶�+1-1
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.x < 230 || msg.x > 510 || msg.y < 250 || msg.y > 280) break;
			if (msg.uMsg == WM_LBUTTONDOWN)//�����
			{
				COLORREF fillcolor = RGB(240, 183, 155);//��ɫ
				COLORREF framecolor = RGB(138, 43, 226);//��ɫ
				COLORREF buttoncolor = RGB(255, 0, 255);//��ۺ�
				/*while (mousedown == 1 && mouseup == 0)//����������ߣ�1��ʾ��갴����
				{
					if (msg.uMsg == WM_MOUSEMOVE)
					{
						setfillcolor(BLACK);//�Ȱ��������������������Ǹ�����
						solidrectangle(230, 250, 510, 280);
						setfillcolor(framecolor);
						solidrectangle(230, 255, 510, 275);//�����´�ӡ
						setfillcolor(fillcolor);
						solidrectangle(230, 250, 510, 254);//��������ǶԵ�
						solidrectangle(230, 276, 510, 280);//��Ϊ�������ˣ�Ҫ����
						solidrectangle(227, 250, 229, 280);
						solidrectangle(511, 250, 513, 280);
						int temp_x = msg.x;//y ���ÿ���
						int temp_x_num = (temp_x - 230) / 20;//�õ����,�����ٳ�
						int temp_x_left = 230 + temp_x_num * 20;//�����Ԥ���������ε���ߵ�x����
						int button_x_left = temp_x_left - 3;//������ǻ��������ߵ�����
						setfillcolor(buttoncolor);
						solidrectangle(button_x_left, 252, button_x_left + 26, 278);//���´�ӡ����
					}
					if (msg.uMsg == WM_LBUTTONUP) mouseup = 1;//1��ʾ��굯����
					if (mouseup == 1) break;
				}*/
				//��������
				setfillcolor(BLACK);//�Ȱ��������������������Ǹ�����
				solidrectangle(230, 250, 510, 280);
				setfillcolor(framecolor);
				solidrectangle(230, 255, 510, 275);//�����´�ӡ
				setfillcolor(fillcolor);
				solidrectangle(230, 250, 510, 254);//��������ǶԵ�
				solidrectangle(230, 276, 510, 280);//��Ϊ�������ˣ�Ҫ����
				solidrectangle(227, 250, 229, 280);
				solidrectangle(511, 250, 513, 280);
				int temp_x = msg.x;//y ���ÿ���
				int temp_x_num = (temp_x - 230) / 20;//�õ����,�����ٳ�
				if (temp_x == 510) temp_x_num -= 1;//510��������
				int temp_x_left = 230 + temp_x_num * 20;//�����Ԥ���������ε���ߵ�x����
				int button_x_left = temp_x_left - 3;//������ǻ��������ߵ�����
				setfillcolor(buttoncolor);
				solidrectangle(button_x_left, 252, button_x_left + 26, 278);//���´�ӡ����
				int scale = (last_music_x_left - button_x_left) / 20 + 1;//��last���������Ǽ�
				int tot_step = step * scale;
				adjust_music_volume(tot_step);
				last_music_x_left = button_x_left;
			}
		}
	}
	void manipulate_sound()//��������Ѿ������ֵ��Ǹ�����������
	{
		MOUSEMSG msg;
		int step = 67;//��Ϊ�����޶˶�+1-1
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.x < 230 || msg.x > 510 || msg.y < 290 || msg.y > 320) break;
			if (msg.uMsg == WM_LBUTTONDOWN)//�����
			{
				//��ʵ290��320�Ǵ��˵�ģ�����Ϊ��Ч���õ�
				COLORREF fillcolor = RGB(240, 183, 155);//��ɫ
				COLORREF framecolor = RGB(138, 43, 226);//��ɫ
				COLORREF buttoncolor = RGB(255, 0, 255);//��ۺ�
				/*while (mousedown == 1 && mouseup == 0)//����������ߣ�1��ʾ��갴����
				{
					if (msg.uMsg == WM_MOUSEMOVE)
					{
						setfillcolor(BLACK);//�Ȱ��������������������Ǹ�����
						solidrectangle(230, 250, 510, 280);
						setfillcolor(framecolor);
						solidrectangle(230, 255, 510, 275);//�����´�ӡ
						setfillcolor(fillcolor);
						solidrectangle(230, 250, 510, 254);//��������ǶԵ�
						solidrectangle(230, 276, 510, 280);//��Ϊ�������ˣ�Ҫ����
						solidrectangle(227, 250, 229, 280);
						solidrectangle(511, 250, 513, 280);
						int temp_x = msg.x;//y ���ÿ���
						int temp_x_num = (temp_x - 230) / 20;//�õ����,�����ٳ�
						int temp_x_left = 230 + temp_x_num * 20;//�����Ԥ���������ε���ߵ�x����
						int button_x_left = temp_x_left - 3;//������ǻ��������ߵ�����
						setfillcolor(buttoncolor);
						solidrectangle(button_x_left, 252, button_x_left + 26, 278);//���´�ӡ����
					}
					if (msg.uMsg == WM_LBUTTONUP) mouseup = 1;//1��ʾ��굯����
					if (mouseup == 1) break;
				}*/
				//��������
				setfillcolor(BLACK);//�Ȱ��������������������Ǹ�����
				solidrectangle(230, 290, 510, 320);
				setfillcolor(framecolor);
				solidrectangle(230, 295, 510, 315);//�����´�ӡ
				setfillcolor(fillcolor);
				solidrectangle(230, 290, 510, 294);//��������ǶԵ�
				solidrectangle(230, 316, 510, 320);//��Ϊ�������ˣ�Ҫ����
				solidrectangle(227, 290, 229, 320);
				solidrectangle(511, 290, 513, 320);
				int temp_x = msg.x;//y ���ÿ���
				int temp_x_num = (temp_x - 230) / 20;//�õ����,�����ٳ�
				if (temp_x == 510) temp_x_num -= 1;//510��������
				int temp_x_left = 230 + temp_x_num * 20;//�����Ԥ���������ε���ߵ�x����
				int button_x_left = temp_x_left - 3;//������ǻ��������ߵ�����
				setfillcolor(buttoncolor);
				solidrectangle(button_x_left, 292, button_x_left + 26, 318);//���´�ӡ����
				int scale = (last_sound_x_left - button_x_left) / 20 + 1;//��last���������Ǽ�
				int tot_step = step * scale;
				adjust_sound_volume(tot_step);
				last_sound_x_left = button_x_left;
			}
		}
	}
	int last_music_x_left, last_sound_x_left;//û�취����ΪҪ��ͼ�������Ҫ�����������ϸ��£�һ��ʼ��357
};