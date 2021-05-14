#pragma once
#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<utility>
#include<graphics.h>
#include<conio.h>
#include"music_and_sound.hpp"
using namespace std;

class bejewled_board
{
public:
	bejewled_board() = default;
	explicit bejewled_board(double level = 1.0, double score = 0, double tot_score = 0, int bonus = 1) :level(level), present_score(score), tot_score(tot_score), bonus(bonus)
	{
		memset(board, 0, sizeof(board));
	}
	~bejewled_board() = default;

	void update_level()
	{
		level++;
	}
	void set_present_score()
	{
		present_score = 0;
	}
	void update_bonus()
	{
		bonus++;
	}
	void set_bonus()
	{
		bonus = 0;
	}
	void create_or_erase_circle(int x, int y, int r, bool is_create)
	{
		if (is_create)
		{
			setfillcolor(WHITE);
			solidcircle(x, y, r);
		}
		else clearcircle(x, y, r);
	}
	void create_or_erase_square(int x, int y, int r, bool is_create)
	{
		if (is_create)
		{
			setfillcolor(LIGHTRED);
			solidroundrect(x, y, x + 30, y + 30, r, r);
		}
		else clearroundrect(x, y, x + 30, y + 30, r, r);
	}
	void create_or_erase_triangle(int x, int y, bool is_create)//��������ߵײ�������
	{
		if (is_create)
		{
			setfillcolor(MAGENTA);
			POINT polygon_3_points[] = { {x,y},{x + 15,y - 30},{x + 30,y} };
			solidpolygon(polygon_3_points, 3);
		}
		else
		{
			POINT polygon_3_points[] = { {x,y},{x + 15,y - 30},{x + 30,y} };
			clearpolygon(polygon_3_points, 3);
		}
	}
	void create_or_erase_rhombus(int x, int y, bool is_create)//�����е�����
	{
		if (is_create)
		{
			setfillcolor(YELLOW);
			POINT polygon_4_points[] = { {x,y},{x + 15,y - 15},{x + 30,y},{x + 15,y + 15} };
			solidpolygon(polygon_4_points, 4);
		}
		else
		{
			POINT polygon_4_points[] = { {x,y},{x + 15,y - 15},{x + 30,y},{x + 15,y + 15} };
			clearpolygon(polygon_4_points, 4);
		}
	}
	void create_or_erase_diamond(int x, int y, bool is_create)//��ʯ�����ͻ���ĵ�
	{
		if (is_create)
		{
			setfillcolor(BLUE);
			POINT polygon_5_points[] = { {x,y},{x + 7,y - 10},{x + 23,y - 10},{x + 30,y},{x + 15,y + 20} };
			solidpolygon(polygon_5_points, 5);
		}
		else
		{
			POINT polygon_5_points[] = { {x,y},{x + 7,y - 10},{x + 23,y - 10},{x + 30,y},{x + 15,y + 20} };
			clearpolygon(polygon_5_points, 5);
		}
	}
	void create_or_erase_hexagon(int x, int y, bool is_create)//���������Ͻǵĵ�
	{
		if (is_create)
		{
			setfillcolor(BROWN);
			POINT polygon_6_points[] = { {x,y},{x + 15,y - 7},{x + 30,y},{x + 30,y + 16},{x + 15,y + 23},{x,y + 16} };
			solidpolygon(polygon_6_points, 6);
		}
		else
		{
			POINT polygon_6_points[] = { {x,y},{x + 15,y - 7},{x + 30,y},{x + 30,y + 16},{x + 15,y + 23},{x,y + 16} };
			clearpolygon(polygon_6_points, 6);
		}
	}
	void create_or_erase_octagon(int x, int y, bool is_create)//�˱�������ߵ��м��
	{
		if (is_create)
		{
			setfillcolor(GREEN);
			POINT polygon_8_points[] = { {x,y},{x + 5,y - 10},{x + 15,y - 15},{x + 25,y - 10},{x + 30,y},{x + 25,y + 10},{x + 15,y + 15},{x + 5,y + 10} };
			solidpolygon(polygon_8_points, 8);
		}
		else
		{
			POINT polygon_8_points[] = { {x,y},{x + 5,y - 10},{x + 15,y - 15},{x + 25,y - 10},{x + 30,y},{x + 25,y + 10},{x + 15,y + 15},{x + 5,y + 10} };
			clearpolygon(polygon_8_points, 8);
		}
	}
	void print_or_erase_one(int x, int y, int num, bool is_print)//�����x��y�����е㣬print_one��print_one_row���Ǵ����е�
	{                                                         //���������x��y����ʵ���к��У�Ҫע��
		if (num == 1)create_or_erase_circle(x + 15, y, 15, is_print);
		else if (num == 2)create_or_erase_square(x, y - 15, 10, is_print);
		else if (num == 3)create_or_erase_triangle(x, y + 15, is_print);
		else if (num == 4)create_or_erase_rhombus(x, y, is_print);
		else if (num == 5)create_or_erase_diamond(x, y - 5, is_print);
		else if (num == 6)create_or_erase_hexagon(x, y - 8, is_print);
		else if (num == 7)create_or_erase_octagon(x, y, is_print);
	}
	void init_the_score()
	{
		settextstyle(25, 15, _T("Consolas"));
		settextcolor(WHITE);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("��ǰ����");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//������tot_score��ע��
		outtextxy(25, 50, lev_string);//W:25-115,H:50-75
		outtextxy(120, 50, lev_num);//W:120-...,H:50-75
		outtextxy(23, 80, score_string);//W:23-143,H:80-105
		outtextxy(55, 110, score_num);//�����ӡ�����ܷ�������Ϊÿһ�ض�Ҫ���´�ӡ�������
	}
	void print_the_buttons()
	{
		settextstyle(25, 15, _T("Courier New"));
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		TCHAR tips[] = _T("TIPS");
		TCHAR menu[] = _T("Menu");
		TCHAR reset[] = _T("Reset");
		TCHAR exit_out[] = _T("Exit");
		outtextxy(55, 330, tips);//W:55-115,H:330-355
		outtextxy(15, 370, menu);//W:15-75,H:370-395
		outtextxy(90, 370, reset);//W:90-165,H:370-395
		outtextxy(570, 535, exit_out);//W:570-630,H:535-550
	}
	bool scan_the_board_for_availability()//������û�пɽ����ģ��оͷ���true�����ص��x��y���꣬û�о�false���ڲ��ӿ�
	{
		int direct_in_hor[] = { -1,0,1,0 }, direct_in_ver[] = { 0,-1,0,1 };
		bool is_available = false;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)//ÿһ���㶼����
			{
				///bfsѰ�Ҳ��֣��ĸ��㶼�ң�map����Ϊ�˴���������������ɫ��ͬ��״��
				map<int, vector<int>>stor;//key����ɫ��k�Ƿ���0��1��2��3��
				for (int k = 0; k < 4; k++)
				{
					auto temp_x = j + direct_in_hor[k];
					auto temp_y = i + direct_in_ver[k];
					if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
					int present_jeweled = board[temp_y][temp_x];
					if (stor.find(present_jeweled) == stor.end())//�ⶫ��������
					{
						vector<int>temp = {};
						temp.emplace_back(k);
						stor[present_jeweled] = temp;
					}
					else //�ⶫ���Ѿ�����
					{
						stor[present_jeweled].emplace_back(k);
					}
				}
				///�жϲ���+dfs����
				for (auto& val : stor)
				{
					int cnt = 0;//cnt�͹��ˣ����÷ַ�����Ϊ���ƽϷ���
					if (val.second.size() == 2)//val�Ǹ����������Ǹ�pair�������������2 3 4��2����ֻ������������ͬɫ
					{
						int present_jeweled = val.first;
						for (auto direct : val.second)
						{
							cnt++;
							int step = 2;//step=2������
							if (direct == 0)//0��
							{
								auto temp_x = j - step;
								auto temp_y = i;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)//���ֻʣһ���ˣ��ͱ�������
										auto it_next = val.second.erase(it);
								}
							}
							if (direct == 1)//1��
							{
								auto temp_x = j;
								auto temp_y = i - step;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)
										auto it_next = val.second.erase(it);//it_nextû�õ�
								}
							}
							if (direct == 2)//2��
							{
								auto temp_x = j + step;
								auto temp_y = i;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)
										auto it_next = val.second.erase(it);//it_nextû�õ�
								}
							}
							if (direct == 3)//3��
							{
								auto temp_x = j;
								auto temp_y = i + step;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)
										auto it_next = val.second.erase(it);//it_nextû�õ�
								}
							}
						}
						if (cnt >= 3)
						{
							is_available = true;
							if (!val.second.empty())//���ʱ������ֻ��һ����
							{
								auto direct = val.second.back();
								val.second.pop_back();
								int temp_x = j + direct_in_hor[direct];
								int temp_y = i + direct_in_ver[direct];
								jeweled_tips.emplace(make_pair(temp_x, temp_y));
							}
						}
					}
					else if (val.second.size() == 3)//3��������������ͬɫ
					{
						is_available = true;
						if (find(val.second.cbegin(), val.second.cend(), 0) != val.second.end() && find(val.second.cbegin(), val.second.cend(), 2) != val.second.end())//ˮƽ�����ң�������
						{
							for (auto v : val.second)
							{
								if (v == 0 || v == 2) continue;//ˮƽ�Ĳ�Ҫ�����Ǽ�¼��ֱ����
								auto direct = v;
								if (direct == 1)//1��
								{
									auto temp_x = j;
									auto temp_y = i - 1;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
								else if (direct == 3)//3��
								{
									auto temp_x = j;
									auto temp_y = i + 1;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
							}
						}
						else if (find(val.second.cbegin(), val.second.cend(), 1) != val.second.end() && find(val.second.cbegin(), val.second.cend(), 3) != val.second.end())//��ֱ�����£�������
						{
							for (auto v : val.second)
							{
								if (v == 1 || v == 3) continue;//��ֱ�Ĳ�Ҫ�����Ǽ�¼ˮƽ����
								auto direct = v;
								if (direct == 0)//0��
								{
									auto temp_x = j - 1;
									auto temp_y = i;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
								else if (direct == 2)//2��
								{
									auto temp_x = j + 1;
									auto temp_y = i;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
							}
						}
					}
					else if (val.second.size() == 4)//4�������������Χ������һ����ȥ�������ǽ�������Ǹ����ȥ
					{
						is_available = true;
						auto temp_x = j + 1;
						auto temp_y = i;
						if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
						jeweled_tips.emplace(make_pair(temp_x, temp_y));
					}
				}
			}
		}
		if (is_available) return true;
		return false;
	}
	bool fix_the_board()///��ΪҪ������Ǳ�����������Ҳ���ܳ�״������������������һ����ȥ�滻���������
	{//�ӵ�һ����ʼ���������±����������������ظ��ľͽ����ȥ��Ȼ������һ���������������
		bool is_confiction = false;
		for (int i = 0; i < 8; i++)//ÿһ��������ִ��
		{
			for (int j = 0; j < 8; j++)
			{
				vector<pair<int, int>>hor = {}, ver = {};
				int present_jeweled = board[i][j], flag = 0;
				for (int step = 1; step <= 2; step++)//��鲿��
				{
					if (step > 1 && flag == 0) break;//��Ϊ���step>1�ˣ�flag����0Ҳ����˵���Աߵĸ�����һ������ֱ������
					int hor_coord = j + step, ver_coord = i + step;
					if (hor_coord <= 7 && present_jeweled == board[i][hor_coord])///ˮƽ��飬��������
					{
						hor.emplace_back(make_pair(i, hor_coord));
						flag++;//��֦�������һ����û�ˣ��Ǿ�����
					}
					if (ver_coord <= 7 && present_jeweled == board[ver_coord][j])///��ֱ��飬��������
					{
						ver.emplace_back(make_pair(ver_coord, j));
						flag++;
					}
				}
				if (flag == 0)///��֦������
				{
					continue;
				}
				//�滻����
				if (hor.size() >= 2)//ˮƽ���֣�ȡ��β�ĵ�
				{
					is_confiction = true;//���˵��>=2�ģ��ͱ�true��
					pair<int, int>temp = hor.back();
					int now_x = 200 + 50 * temp.second, now_y = 65 + 50 * temp.first;///���ˣ����ǳ�i��j
					int num = (rand() % 8 + 200) % 7 + 1;
					while (num == present_jeweled) num = (rand() % 8 + 200) % 7 + 1;
					board[temp.first][temp.second] = num;
					//��������һ����һ����
				}
				if (ver.size() >= 2)//ˮƽ���֣�ȡ��β�ĵ�
				{
					is_confiction = true;
					pair<int, int>temp = ver.back();
					int now_x = 200 + 50 * temp.second, now_y = 65 + 50 * temp.first;//���ǳ�i��j��
					int num = (rand() % 8 + 200) % 7 + 1;
					while (num == present_jeweled) num = (rand() % 8 + 200) % 7 + 1;
					board[temp.first][temp.second] = num;
					//��������һ����һ����
				}
			}
		}
		if (is_confiction) return true;
		return false;
	}
	void print_the_board(music_and_sound_play& ms)
	{
		settextstyle(20, 15, _T("Courier New"));
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int num = (rand() % 8 + 200) % 7 + 1;
				board[i][j] = num;
			}
		}
		while (fix_the_board());//������ֱ��������̸�������Ҫ����Ϊֹ
		BeginBatchDraw();
		//cleardevice();
		IMAGE img;
		loadimage(&img, _T("..\\Images\\1.jpg"));
		auto max_x = getmaxx();
		auto max_y = getmaxy();
		putimage(0, 0, max_x + 1, max_y + 1, &img, 0, 0, SRCCOPY);
		setbkmode(TRANSPARENT);
		int x = 200, y = 65;//��֤�˴��붼���е㣬+50i��+50j��Щֻ����λ
		setlinecolor(RED);
		setlinestyle(PS_DASHDOT | PS_JOIN_ROUND, 6);//6���ؿ����Ӵ�ΪԲ�ǵĵ㻮��
		roundrect(180, 30, 600, 450, 10, 10);
		bool is_create = true;
		for (int i = 0; i < 8; i++)//j,iҪ��0��ʼ����Ϊ����Ҫ��j��i
		{
			for (int j = 0; j < 8; j++)
			{
				int num = board[i][j];
				if (num == 1)create_or_erase_circle(x + 15 + 50 * j, y + 50 * i, 15, is_create);
				else if (num == 2)create_or_erase_square(x + 50 * j, y - 15 + 50 * i, 10, is_create);
				else if (num == 3)create_or_erase_triangle(x + 50 * j, y + 15 + 50 * i, is_create);
				else if (num == 4)create_or_erase_rhombus(x + 50 * j, y + 50 * i, is_create);
				else if (num == 5)create_or_erase_diamond(x + 50 * j, y - 5 + 50 * i, is_create);
				else if (num == 6)create_or_erase_hexagon(x + 50 * j, y - 8 + 50 * i, is_create);
				else if (num == 7)create_or_erase_octagon(x + 50 * j, y + 50 * i, is_create);
				FlushBatchDraw();
			}
		}
		init_the_score();//�����ӡ�����ܷ�������Ϊÿһ�ض�Ҫ���´�ӡ�������
		print_the_buttons();
		print_the_progress_bar_frame();
		EndBatchDraw();
	}
	void check_for_availability(music_and_sound_play& ms)//�ⲿ�ӿڣ��Ƿ��пɽ�����
	{
		while (!scan_the_board_for_availability())
		{
			print_the_board(ms);
			fix_the_board();
			jeweled_tips.clear();//�ǵ����
		}
		jeweled_tips.clear();
	}
	bool is_in_the_jeweled_rect(int x, int y)//�������ʵʱ��������꣬�ж�����Ƿ��ڿ��ڣ��Ƿ�����ͼ�飩
	{
		bool in_x = (0 <= (x % 50) && (x % 50) <= 30) && x >= 200 && x <= 600;
		bool in_y = (0 <= (y % 50) && (y % 50) <= 30) && y >= 50 && y <= 450;
		if (in_x && in_y) return true;
		else return false;
	}
	bool is_nearby(int last_x, int last_y, int now_x, int now_y)//�жϵڶ������ǲ����ڵ�һ���򸽽���ԭ���ǣ���lastΪ���Ľ����ж�
	{                                                        //���������һ����͵�ǰ����������
		int delta_last_x = last_x - (last_x / 50) * 50;//�Ȱ����ǵ�λ��ͳһ�����������ϽǵĶ���
		int delta_last_y = last_y - (last_y / 50) * 50;
		int last_x_left = last_x - delta_last_x;
		int last_y_top = last_y - delta_last_y;
		int delta_now_x = now_x - (now_x / 50) * 50;
		int delta_now_y = now_y - (now_y / 50) * 50;
		int now_x_left = now_x - delta_now_x;
		int now_y_top = now_y - delta_now_y;
		bool is_onleft = ((last_x_left - 50) == now_x_left && (last_y_top == now_y_top));//�Ƿ�����������
		bool is_onright = ((last_x_left + 50) == now_x_left && (last_y_top == now_y_top));
		bool is_ontop = ((last_y_top - 50) == now_y_top && (last_x_left == now_x_left));///on_top��-����+���������ˣ�
		bool is_onbottom = ((last_y_top + 50) == now_y_top && (last_x_left == now_x_left));
		//�������ж�ȫ��
		if (last_x_left == 200)//�жϱ߽�
		{
			if (last_y_top == 50)//last �����Ͻ�
			{
				if (is_onright || is_onbottom) return true;
			}
			else if (last_y_top == 400)//last �����½�
			{
				if (is_onright || is_ontop) return true;
			}
			else//last �����Ե�����������£�
			{
				if (is_ontop || is_onright || is_onbottom) return true;
			}
		}
		else if (last_x_left == 550)
		{
			if (last_y_top == 50)//last �����Ͻ�
			{
				if (is_onleft || is_onbottom) return true;
			}
			else if (last_y_top == 400)//last �����½�
			{
				if (is_onleft || is_ontop) return true;
			}
			else//last ���ұ�Ե�����������£�
			{
				if (is_ontop || is_onleft || is_onbottom) return true;
			}
		}
		else if (last_y_top == 50)//last ���ϱ߽磨�����������ϣ�
		{
			if (is_onleft || is_onbottom || is_onright) return true;
		}
		else if (last_y_top == 400)//last ���±߽磨�����������£�
		{
			if (is_onleft || is_ontop || is_onright) return true;
		}
		else
		{
			if (is_onleft || is_ontop || is_onright || is_onbottom) return true;
		}
		return false;//��������ڣ����ߵ����Լ�����
	}
	bool print_or_erase_frame(int x, int y, bool is_print)//print�������ʵʱ���������,erase���������һ�ε��������
	{
		int delta_x = x - (x / 50) * 50;
		int delta_y = y - (y / 50) * 50;
		int x_left = x - delta_x;//������Ͻǵĵ�
		int y_top = y - delta_y;
		if (is_print) setlinecolor(YELLOW);
		else setlinecolor(BLACK);
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
		line(x_left - 5, y_top - 5, x_left + 7, y_top - 5);
		line(x_left - 5, y_top - 5, x_left - 5, y_top + 7);
		line(x_left + 35, y_top - 5, x_left + 23, y_top - 5);
		line(x_left + 35, y_top - 5, x_left + 35, y_top + 7);
		line(x_left - 5, y_top + 35, x_left - 5, y_top + 23);
		line(x_left - 5, y_top + 35, x_left + 7, y_top + 35);
		line(x_left + 35, y_top + 35, x_left + 35, y_top + 23);
		line(x_left + 35, y_top + 35, x_left + 23, y_top + 35);
		return true;
	}
	bool swap_jeweled(int now_x, int now_y, int last_x, int last_y)//���������һ����͵�ǰ����������
	{
		int now_x_num = now_x / 50 - 4;             //�������������������
		int now_y_num = now_y / 50 - 1;             ///���ǣ�-1��������-4��
		int last_x_num = last_x / 50 - 4;
		int last_y_num = last_y / 50 - 1;
		int delta_now_x = now_x - (now_x / 50) * 50;
		int delta_now_y = now_y - (now_y / 50) * 50;
		int now_x_mid = now_x - delta_now_x;        ///�������в��裬Ŀ���ǽ�x��y������е�
		int now_y_mid = now_y - delta_now_y + 15;
		int delta_last_x = last_x - (last_x / 50) * 50;
		int delta_last_y = last_y - (last_y / 50) * 50;
		int last_x_mid = last_x - delta_last_x;
		int last_y_mid = last_y - delta_last_y + 15;
		print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], false);///��ס��x���У�y���У���Ҫ���ˣ�
		print_or_erase_one(last_x_mid, last_y_mid, board[last_y_num][last_x_num], false);//��Ĩ��
		swap(board[now_y_num][now_x_num], board[last_y_num][last_x_num]);//��0 0��ʼ��
		print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], true);
		print_or_erase_one(last_x_mid, last_y_mid, board[last_y_num][last_x_num], true);
		return true;
	}
	void vanish_the_score()//���ɾ����Ҳ���ܷ�������Ϊÿһ�ر��������������
	{
		settextstyle(25, 15, _T("Consolas"));
		settextcolor(BLACK);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("��ǰ����");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//������tot_score��ע��
		outtextxy(25, 50, lev_string);//W:25-115,H:50-75
		outtextxy(120, 50, lev_num);//W:120-...,H:50-75
		outtextxy(23, 80, score_string);//W:23-143,H:80-105
		outtextxy(55, 110, score_num);//���ɾ�������ܷ�������Ϊÿһ�ض�Ҫ���´�ӡ�������
	}
	void update_and_refresh_the_score(int vanish_cnt, double level, int bonus)//bonus:�������������������Ǿ��Ǽ�
	{
		if (vanish_cnt >= 5)
		{
			tot_score += 50.0 * (2 + level) * bonus;
			present_score += 50.0 * (2 + level) * bonus;
		}
		else if (vanish_cnt == 4)
		{
			tot_score += 50.0 * (1 + level) * bonus;
			present_score += 50.0 * (1 + level) * bonus;
		}
		else if (vanish_cnt == 3)
		{
			tot_score += 50.0 * level * bonus;
			present_score += 50.0 * level * bonus;///���ҲҪ���£�ֻ������������
		}
		settextstyle(25, 15, _T("Consolas"));
		settextcolor(WHITE);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("��ǰ����");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//������tot_score��ע��
		outtextxy(25, 50, lev_string);//W:25-115,H:50-75
		outtextxy(120, 50, lev_num);//W:120-...,H:50-75
		outtextxy(23, 80, score_string);//W:23-143,H:80-105
		outtextxy(55, 110, score_num);//�����ӡ�����ܷ�������Ϊÿһ�ض�Ҫ���´�ӡ�������
	}
	void print_the_progress_bar_frame()
	{
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
		rectangle(158, 458, 622, 502);//�м�Ŀ���460*40���߿���2
	}
	void vanish_the_progress_bar()//����֮��Ҫ����
	{
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
		setfillcolor(BLACK);
		fillrectangle(158, 458, 622, 502);
	}
	void update_and_refresh_the_progress_bar(double present_score, double base_level_score)
		//level_score�ǵ�ǰ�ؿ����ܷ���
	{//�ܳ�460�����ձ��������д�ӡ
		double tot_len = 460.0;///ע�⣬�����present_score��ÿһ�صķ�����ÿһ�صķ�����Ҫ����ģ�
		double present_level_score = base_level_score * (1 + level * 0.1);
		double add_len = present_score / present_level_score * tot_len;
		if (present_score >= present_level_score) add_len = 1.0 * tot_len;
		setfillcolor(WHITE);
		solidrectangle(160, 460, 160 + static_cast<int>(add_len), 500);
	}
	bool is_the_progress_bar_filled(double base_level_score)
	{
		if (present_score >= base_level_score * (1 + level * 0.1))
			return true;
		return false;
	}
	bool jeweled_vanish(int now_x, int now_y, music_and_sound_play& ms)//�����㷨�����now_x��now_y��swap��һ��
	{													//����Ҫ�жϳ������Ƿ�Ӧ�����������Ҫ������Ҫ����Щ��������
		setbkmode(TRANSPARENT);
		int now_x_num = now_x / 50 - 4;                 //��ά������к�
		int now_y_num = now_y / 50 - 1;                 //��ά������к�
		int now_x_mid = 200 + 50 * now_x_num;			//�е�x������
		int now_y_mid = 65 + 50 * now_y_num;			//�е�y������    
		int direct_in_ver[] = { -1,0,1,0 };             //�������飬bfs��,ver->y,hor->x
		int direct_in_hor[] = { 0,1,0,-1 };
		int horizontal_cnt = 0, vertical_cnt = 0;       //�����¼��������ٸ��������ٸ�
		int present_jeweled = board[now_y_num][now_x_num];//��ǰ��ʯ�ı��
		queue<pair<int, int>>q_for_bfs;
		vector<pair<int, int>>v_for_horizontal_storage, v_for_vertical_storage;//��¼�¾����Ǻ�������������������

		///��Ѱ���жϲ���
		for (int i = 0; i < 4; i++)//bfs
		{
			auto temp_x = now_x_num + direct_in_hor[i];
			auto temp_y = now_y_num + direct_in_ver[i];//temp_y��һ����������temp_x��һ���������������ƶ��������
			if (0 <= temp_x && temp_x <= 7 && 0 <= temp_y && temp_y <= 7 && board[temp_y][temp_x] == present_jeweled)///Ҫ��⣬���ܳ��߽磬����˳����磬Ҫ�ȿ�Խ��û��
			{
				q_for_bfs.emplace(make_pair(temp_y, temp_x));//������ڣ������
				if (direct_in_ver[i] == 1 || direct_in_ver[i] == -1)//direct_in_ver�Ǵ�ֱ�ģ�����record[1]++
				{
					vertical_cnt++;                 //��ֱ����ͬ����++
					v_for_vertical_storage.emplace_back(make_pair(temp_y, temp_x));//��¼��������Ȼ��֪�������Ǻỹ����
				}///����һ��ʼ��ֱ��ˮƽ��ת��
				else
				{
					horizontal_cnt++;               //�������ͬ����++
					v_for_horizontal_storage.emplace_back(make_pair(temp_y, temp_x));//��ӵ�ʱ����y��x�����к���
				}
			}
		}
		while (!q_for_bfs.empty())//dfs������
		{
			pair<int, int>nearby_jeweled = q_for_bfs.front();
			q_for_bfs.pop();
			int step = 1;//�����ߣ�2ֻ�Ǳ���
			if (nearby_jeweled.first + 1 == now_y_num && nearby_jeweled.second == now_x_num)//���Ϸ�
			{///����Ӽ�step���ǿ��ܳ��磬��Ϊ������ܻ�Խ�磬Խ����������룬Ȼ��ǡ����ȣ�����Ҫ���ж�
				while (true)
				{
					if (step >= 2) break;///����д����Ϊ�˼ȿ��Ա�֤���Խ�磬�ֿ��Ա�֤���ϲ�
					if (nearby_jeweled.first - step > 7 || nearby_jeweled.first - step < 0) break;
					if (board[nearby_jeweled.first - step][now_x_num] == present_jeweled)//������
					{
						vertical_cnt++;
						v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first - step, now_x_num));
						step++;
					}
					else break;//������ֱ�ӹ������ϲ���
				}
			}
			if (nearby_jeweled.first - 1 == now_y_num && nearby_jeweled.second == now_x_num)//���·�
			{
				while (true)
				{
					if (step >= 2) break;///����д����Ϊ�˼ȿ��Ա�֤���Խ�磬�ֿ��Ա�֤���ϲ�
					if (nearby_jeweled.first + step > 7 || nearby_jeweled.first + step < 0) break;
					if (board[nearby_jeweled.first + step][now_x_num] == present_jeweled && step <= 2)//������
					{
						vertical_cnt++;
						v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first + step, now_x_num));
						step++;
					}
					else break;//������ֱ�ӹ������ϲ���
				}
			}
			if (nearby_jeweled.second + 1 == now_x_num && nearby_jeweled.first == now_y_num)//����
			{
				while (true)
				{
					if (step >= 2) break;///����д����Ϊ�˼ȿ��Ա�֤���Խ�磬�ֿ��Ա�֤���ϲ�
					if (nearby_jeweled.second - step > 7 || nearby_jeweled.second - step < 0) break;
					if (board[now_y_num][nearby_jeweled.second - step] == present_jeweled && step <= 2)//������
					{
						horizontal_cnt++;
						v_for_horizontal_storage.emplace_back(make_pair(now_y_num, nearby_jeweled.second - step));//�ֱ�Ѻ����ĵ㶼������
						step++;///stepλ�ò��ԣ���Ȼ���2
					}
					else break;//������ֱ�ӹ������ϲ���
				}
			}
			if (nearby_jeweled.second - 1 == now_x_num && nearby_jeweled.first == now_y_num)//���ҷ�
			{
				while (true)
				{
					if (step >= 2) break;///����д����Ϊ�˼ȿ��Ա�֤���Խ�磬�ֿ��Ա�֤���ϲ�
					if (nearby_jeweled.second + step > 7 || nearby_jeweled.second + step < 0) break;
					if (board[now_y_num][nearby_jeweled.second + step] == present_jeweled && step <= 2)//������
					{
						horizontal_cnt++;
						v_for_horizontal_storage.emplace_back(make_pair(now_y_num, nearby_jeweled.second + step));//������������֪����˭�Ĺ���
						step++;
					}
					else break;//������ֱ�ӹ������ϲ���
				}
			}
		}

		///��������
		//1.�����ͬ���ϣ������ǺἸ��������
		if (horizontal_cnt >= 2 && vertical_cnt >= 2)
		{
			Sleep(300);
			int hor_min = 1000, hor_max = -1;
			int ver_min = 1000, ver_max = -1;//������¼�ᣨ�������������С���꣬�����½�
			int vanish_cnt = 0;
			while (!v_for_horizontal_storage.empty())
			{
				pair<int, int>temp = v_for_horizontal_storage.back();
				v_for_horizontal_storage.pop_back();
				hor_max = max(hor_max, temp.second);//ˮƽ�Ķ�Ӧsecond
				hor_min = min(hor_min, temp.second);
				auto temp_x_mid = 50 * (temp.second + 4);
				auto temp_y_mid = 50 * (temp.first + 1) + 15;//print_or_erase_one�õ�����������ֵ�������������±�ֵ������Ҫ����е�
				print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//ע�⣬�����second��x��first��y�������ڶ�boardȡֵ�Ͷ�x��yȡֵ��ʱ��һ��
				board[temp.first][temp.second] = 0;//��ʵû��Ӱ��
				vanish_cnt++;
			}
			while (!v_for_vertical_storage.empty())
			{
				pair<int, int>temp = v_for_vertical_storage.back();
				v_for_vertical_storage.pop_back();
				ver_max = max(ver_max, temp.first);
				ver_min = min(ver_min, temp.first);///���ˣ�һ��ʼд����first
				auto temp_x_mid = 50 * (temp.second + 4);
				auto temp_y_mid = 50 * (temp.first + 1) + 15;
				print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);
				board[temp.first][temp.second] = 0;
				vanish_cnt++;
			}
			hor_max = max(hor_max, now_x_num);
			hor_min = min(hor_min, now_x_num);
			ver_max = max(ver_max, now_y_num);
			ver_min = min(ver_min, now_y_num);
			print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], false);
			board[now_y_num][now_x_num] = 0;
			vanish_cnt++;
			ms.stop_sound();
			ms.close_sound();
			ms.play_sound("C:\\Users\\T_Heap\\source\\repos\\��ʯ����\\��ʯ����3����\\lightning��Ч.wav");
			if (!is_the_progress_bar_filled(2000.0))
			{
				update_bonus();
				vanish_the_score();
				update_and_refresh_the_score(vanish_cnt, level, bonus);
				double base_level_score = 2000.0;
				update_and_refresh_the_progress_bar(present_score, base_level_score);
			}

			/* �����½����֣��ȱ�����ֱ������������ȰѺ�����������½��ˣ����룻���½���ֱ�ģ��ٲ���*/
			///����Ĳ������ֿ�
			{
				///�½�����1--�����½�
				auto now_hor_num = now_y_num;//��������
				while (now_hor_num >= 1)//����>=0
				{
					for (int i = hor_min; i <= hor_max; i++)
					{
						if (i == now_x_num) continue;//�����������ˮƽ�����У������˸���ֱ������ͬ���Ǹ�����������ʵ�Ͷ�����һ�䣬������һ�о���ȫ������
						auto temp_x_mid = 50 * (i + 4);//�����Ǹ��ĺ����꣨ˮƽ���꣩
						auto temp_y_mid_above = 50 * (now_hor_num)+15;//�����Ǹ��������꣨��ֱ���꣩
						print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][i], false);//�Ȱ������Ǹ����������������ӡ����
						board[now_hor_num][i] = board[now_hor_num - 1][i];
						auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//������һ���ĺ����꣨�����Ǹ����������꣨x���꣩��һ����
						print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][i], true);
					}
					now_hor_num--;
				}

				///���벿��1--������
				for (int j = hor_min; j <= hor_max; j++)//���ʱ�����Ѿ����0��
				{
					if (j == now_x_num) continue;
					auto num = (rand() % 8 + 200) % 7 + 1;
					auto temp_x_mid = 50 * (j + 4);//ˮƽ����
					auto temp_y_mid = 50 * (0 + 1) + 15;
					board[0][j] = num;
					print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
				}
			}

			///��ֱ�Ĳ���
			{
				///�½�����2--��ֱ�½�
				auto now_ver_num = now_x_num;//�������ţ�����ǲ�����
				auto delta = ver_max - ver_min + 1;//���������������˶��ٸ�
				auto ver_min_above_num = ver_min - 1;//�����y������С�������Ǹ���Ȼ�󲻶�--�Ϳ���
				while (ver_min_above_num >= 0)
				{
					//x���겻��䣬����now_x_mid
					auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
					print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//��ȥԭ��λ�õ�ͼ�� 
					auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//�������Ӧ���½�����λ�õ�����������
					auto ver_min_below_num = ver_min_above_num + delta;//�������Ӧ���½�����λ�õĶ�ά�����������
					board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta�Ƕ�λ����ĺ����꣨�У�
					print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//��ͬ����ͼ
					ver_min_above_num--;
				}

				///���벿��2--��ֱ����
				for (int j = 0; j < delta; j++)//delta������ʧ�ĸ�������ʧ�˶��ٲ�����
				{
					auto num = (rand() % 8 + 200) % 7 + 1;
					auto temp_y_mid = 50 * (j + 1) + 15;///��ֱ�������now_x_mid�����Բ�����x������+1
					board[j][now_ver_num] = num;
					print_or_erase_one(now_x_mid, temp_y_mid, num, true);
				}
			}
			return true;
		}

		//2.ֻ��ˮƽ������ȥ����ȥ��������
		else if (horizontal_cnt >= 2 && vertical_cnt < 2)
		{
			Sleep(300);
			int hor_min = 1000, hor_max = -1;//������¼�ᣨ�������������С���꣬�����½�
			int vanish_cnt = 0;
			while (!v_for_horizontal_storage.empty())
			{
				pair<int, int>temp = v_for_horizontal_storage.back();
				v_for_horizontal_storage.pop_back();
				hor_max = max(hor_max, temp.second);//ˮƽ�Ķ�Ӧsecond
				hor_min = min(hor_min, temp.second);
				auto temp_x_mid = 50 * (temp.second + 4);
				auto temp_y_mid = 50 * (temp.first + 1) + 15;
				print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//ע�⣬�����second��x��first��y�������ڶ�boardȡֵ�Ͷ�x��yȡֵ��ʱ��һ��
				board[temp.first][temp.second] = 0;
				vanish_cnt++;
			}
			hor_max = max(hor_max, now_x_num);
			hor_min = min(hor_min, now_x_num);
			print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], false);
			board[now_y_num][now_x_num] = 0;
			vanish_cnt++;
			if (vanish_cnt == 4)//ֻ��4��
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("..\\Musics\\bomb��Ч.wav");
			}
			else if (vanish_cnt >= 5)//�п��ܾ�����һ�й�ȥ��5��������
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("..\\Musics\\lightning��Ч.wav");
			}
			if (!is_the_progress_bar_filled(2000.0))
			{
				update_bonus();
				vanish_the_score();
				update_and_refresh_the_score(vanish_cnt, level, bonus);
				double base_level_score = 2000.0;
				update_and_refresh_the_progress_bar(present_score, base_level_score);
			}

			///�½�����
			auto now_hor_num = now_y_num;//�������ţ�Ҳ���������Ķ������ڵ��Ǹ��к�
			while (now_hor_num >= 1)//����>=0
			{
				for (int i = hor_min; i <= hor_max; i++)
				{
					auto temp_x_mid = 50 * (i + 4);//�����Ǹ��ĺ����꣨ˮƽ���꣩
					auto temp_y_mid_above = 50 * (now_hor_num)+15;//�����Ǹ��������꣨��ֱ���꣩
					print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][i], false);//�Ȱ������Ǹ����������������ӡ����
					board[now_hor_num][i] = board[now_hor_num - 1][i];
					auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//������һ���ĺ����꣨�����Ǹ����������꣨x���꣩��һ����
					print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][i], true);
				}
				now_hor_num--;///����--�Ŷԣ�
			}

			///�����
			for (int j = hor_min; j <= hor_max; j++)//���ʱ�����Ѿ����0��
			{
				auto num = (rand() % 8 + 200) % 7 + 1;
				auto temp_x_mid = 50 * (j + 4);//ˮƽ����
				auto temp_y_mid = 50 * (0 + 1) + 15;///����+1��
				board[0][j] = num;
				print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
			}
			return true;
		}

		//3.ֻ�д�ֱ������ȥ
		else if (vertical_cnt >= 2 && horizontal_cnt < 2)
		{
			Sleep(300);
			int ver_min = 1000, ver_max = -1;//������¼�ᣨ�������������С���꣬�����½�
			int vanish_cnt = 0;
			while (!v_for_vertical_storage.empty())
			{
				pair<int, int>temp = v_for_vertical_storage.back();
				v_for_vertical_storage.pop_back();
				ver_max = max(ver_max, temp.first);
				ver_min = min(ver_min, temp.first);
				auto temp_x_mid = 50 * (temp.second + 4);
				auto temp_y_mid = 50 * (temp.first + 1) + 15;
				print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);
				board[temp.first][temp.second] = 0;
				vanish_cnt++;
			}
			ver_max = max(ver_max, now_y_num);
			ver_min = min(ver_min, now_y_num);
			print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], false);
			board[now_y_num][now_x_num] = 0;
			vanish_cnt++;
			if (vanish_cnt == 4)//ֻ��4��
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("..\\Musics\\bomb��Ч.wav");
			}
			else if (vanish_cnt >= 5)//�п��ܾ�����һ�й�ȥ��5��������
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("D:\\C++\\Bejewels\\Musics\\lightning��Ч.wav");
			}
			if (!is_the_progress_bar_filled(2000.0))//������ˣ��������������Ƿ����Ͳ�Ҫ����
			{
				update_bonus();
				vanish_the_score();
				update_and_refresh_the_score(vanish_cnt, level, bonus);
				double base_level_score = 2000.0;
				update_and_refresh_the_progress_bar(present_score, base_level_score);
			}
			///�½�����
			auto now_ver_num = now_x_num;//��������
			auto delta = ver_max - ver_min + 1;//���������������˶��ٸ�
			auto ver_min_above_num = ver_min - 1;//�����y������С�������Ǹ���Ȼ�󲻶�--�Ϳ���
			while (ver_min_above_num >= 0)
			{
				//x���겻��䣬����now_x_mid
				auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
				print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//��ȥԭ��λ�õ�ͼ�� 
				auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//�������Ӧ���½�����λ�õ�����������
				auto ver_min_below_num = ver_min_above_num + delta;//�������Ӧ���½�����λ�õĶ�ά�����������
				board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta�Ƕ�λ����ĺ����꣨�У�
				print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//��ͬ����ͼ
				ver_min_above_num--;
			}

			///�����
			for (int j = 0; j < delta; j++)//delta������ʧ�ĸ�������ʧ�˶��ٲ�����
			{
				auto num = (rand() % 8 + 200) % 7 + 1;
				auto temp_y_mid = 50 * (j + 1) + 15;//��ֱ�������now_x_mid�����Բ�����x������j+1
				board[j][now_ver_num] = num;
				print_or_erase_one(now_x_mid, temp_y_mid, num, true);
			}
			return true;
		}
		return false;
	}
	bool fix_the_board_after_vanish(music_and_sound_play& ms)///��ΪҪ������Ǳ�����������Ҳ���ܳ�״������������������һ����ȥ�滻���������
	{
		setbkmode(TRANSPARENT);
		int direct_in_ver[] = { -1,0,1,0 };             //�������飬bfs��,ver->y,hor->x
		int direct_in_hor[] = { 0,1,0,-1 };
		bool confliction = false;//����������һ������true���Ǿ�˵��û�г�ͻ��
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int horizontal_cnt = 0, vertical_cnt = 0;       //�����¼��������ٸ��������ٸ�
				queue<pair<int, int>>q_for_bfs;
				vector<pair<int, int>>v_for_horizontal_storage, v_for_vertical_storage;
				//��¼�¾����Ǻ�������������������
				int present_jeweled = board[i][j];
				int now_x_mid = 200 + 50 * j;
				int now_y_mid = 65 + 50 * i;
				//��Ѱ����
				for (int k = 0; k < 4; k++)///��Ѱ���жϲ��֣�bfs
				{
					auto temp_x = j + direct_in_hor[k];
					auto temp_y = i + direct_in_ver[k];
					if (0 <= temp_x && temp_x <= 7 && 0 <= temp_y && temp_y <= 7 && board[temp_y][temp_x] == present_jeweled)
						///Ҫ��⣬���ܳ��߽磬����˳����磬Ҫ�ȿ�Խ��û��
					{
						q_for_bfs.emplace(make_pair(temp_y, temp_x));//������ڣ������
						if (direct_in_ver[k] == 1 || direct_in_ver[k] == -1)
						{
							vertical_cnt++;                 //��ֱ����ͬ����++
							v_for_vertical_storage.emplace_back(make_pair(temp_y, temp_x));
						}///����һ��ʼ��ֱ��ˮƽ��ת��
						else
						{
							horizontal_cnt++;               //�������ͬ����++
							v_for_horizontal_storage.emplace_back(make_pair(temp_y, temp_x));//��ӵ�ʱ����y��x�����к���
						}
					}
				}
				while (!q_for_bfs.empty())///������Ѱ��dfs������
				{
					pair<int, int>nearby_jeweled = q_for_bfs.front();
					q_for_bfs.pop();
					int step = 1;//step��Ϊ2ֻ�Ǳ���
					if (nearby_jeweled.first + 1 == i && nearby_jeweled.second == j)//���Ϸ�
					{
						while (true)
						{
							if (step >= 3) break;///����д����Ϊ�˼ȿ��Ա�֤���Խ�磬�ֿ��Ա�֤���ϲ�
							if (nearby_jeweled.first - step > 7 || nearby_jeweled.first - step < 0) break;
							if (board[nearby_jeweled.first - step][j] == present_jeweled)//������
							{
								vertical_cnt++;
								v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first - step, j));
								step++;
							}
							else break;//������ֱ�ӹ������ϲ���
						}
					}
					if (nearby_jeweled.first - 1 == i && nearby_jeweled.second == j)//���·�
					{
						while (true)
						{
							if (step >= 3) break;//3����Ϊ����һ����������һ�й���5��
							if (nearby_jeweled.first + step > 7 || nearby_jeweled.first + step < 0) break;
							if (board[nearby_jeweled.first + step][j] == present_jeweled)//������
							{
								vertical_cnt++;
								v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first + step, j));
								step++;
							}
							else break;//������ֱ�ӹ������ϲ���
						}
					}
					if (nearby_jeweled.second + 1 == j && nearby_jeweled.first == i)//����
					{
						while (true)
						{
							if (step >= 3) break;
							if (nearby_jeweled.second - step > 7 || nearby_jeweled.second - step < 0) break;
							if (board[i][nearby_jeweled.second - step] == present_jeweled)//������
							{
								horizontal_cnt++;//���������жϣ���ֹԽ��
								v_for_horizontal_storage.emplace_back(make_pair(i, nearby_jeweled.second - step));//�ֱ�Ѻ����ĵ㶼������
								step++;///�Ĺ���stepλ�ò���
							}
							else break;//������ֱ�ӹ������ϲ���
						}
					}
					if (nearby_jeweled.second - 1 == j && nearby_jeweled.first == i)//���ҷ�
					{
						while (true)
						{
							if (step >= 3) break;
							if (nearby_jeweled.second + step > 7 || nearby_jeweled.second + step < 0) break;
							if (board[i][nearby_jeweled.second + step] == present_jeweled)//������
							{
								horizontal_cnt++;
								v_for_horizontal_storage.emplace_back(make_pair(i, nearby_jeweled.second + step));//������������֪����˭�Ĺ���
								step++;
							}
							else break;//������ֱ�ӹ������ϲ���
						}
					}
				}
				///��֦����������ʹ�������˴����Ĺ��ܣ�ֻ��64������ȫ���ж���û�����⣬�������û��ͻ
				if (vertical_cnt <= 1 && horizontal_cnt <= 1) continue;
				//�����������������
				else//2+1 2+2�������������
				{
					confliction = true;
					///��������
					//1.�����ͬ���ϣ������ǺἸ��������
					if (horizontal_cnt >= 2 && vertical_cnt >= 2)
					{
						int hor_min = 1000, hor_max = -1;
						int ver_min = 1000, ver_max = -1;//������¼�ᣨ�������������С���꣬�����½�
						int vanish_cnt = 0;
						Sleep(300);
						while (!v_for_horizontal_storage.empty())
						{
							pair<int, int>temp = v_for_horizontal_storage.back();
							v_for_horizontal_storage.pop_back();
							hor_max = max(hor_max, temp.second);//ˮƽ�Ķ�Ӧsecond
							hor_min = min(hor_min, temp.second);
							auto temp_x_mid = 50 * (temp.second + 4);
							auto temp_y_mid = 50 * (temp.first + 1) + 15;//print_or_erase_one�õ�����������ֵ�������������±�ֵ������Ҫ����е�
							print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//ע�⣬�����second��x��first��y�������ڶ�boardȡֵ�Ͷ�x��yȡֵ��ʱ��һ��
							vanish_cnt++;
						}
						while (!v_for_vertical_storage.empty())
						{
							pair<int, int>temp = v_for_vertical_storage.back();
							v_for_vertical_storage.pop_back();
							ver_max = max(ver_max, temp.first);
							ver_min = min(ver_min, temp.first);///���ˣ�һ��ʼд����first
							auto temp_x_mid = 50 * (temp.second + 4);
							auto temp_y_mid = 50 * (temp.first + 1) + 15;
							print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);
							vanish_cnt++;
						}
						hor_max = max(hor_max, j);
						hor_min = min(hor_min, j);
						ver_max = max(ver_max, i);
						ver_min = min(ver_min, i);
						print_or_erase_one(now_x_mid, now_y_mid, board[i][j], false);
						ms.stop_sound();
						ms.close_sound();
						ms.play_sound("..\\Musics\\lightning��Ч.wav");
						vanish_cnt++;
						if (!is_the_progress_bar_filled(2000.0))
						{
							update_bonus();
							vanish_the_score();
							update_and_refresh_the_score(vanish_cnt, level, bonus);
							double base_level_score = 2000.0;
							update_and_refresh_the_progress_bar(present_score, base_level_score);
						}

						/* �����½����֣��ȱ�����ֱ������������ȰѺ�����������½��ˣ����룻���½���ֱ�ģ��ٲ���*/
						///����Ĳ������ֿ�
						{
							///�½�����1--�����½�
							auto now_hor_num = i;//��������
							while (now_hor_num >= 1)//����>=0
							{
								for (int h = hor_min; h <= hor_max; h++)
								{
									if (h == j) continue;//�����������ˮƽ�����У������˸���ֱ������ͬ���Ǹ�����������ʵ�Ͷ�����һ�䣬������һ�о���ȫ������
									auto temp_x_mid = 50 * (h + 4);//�����Ǹ��ĺ����꣨ˮƽ���꣩
									auto temp_y_mid_above = 50 * (now_hor_num)+15;//�����Ǹ��������꣨��ֱ���꣩
									print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][h], false);//�Ȱ������Ǹ����������������ӡ����
									board[now_hor_num][h] = board[now_hor_num - 1][h];
									auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//������һ���ĺ����꣨�����Ǹ����������꣨x���꣩��һ����
									print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][h], true);
								}
								now_hor_num--;
							}

							///���벿��1--������
							for (int u = hor_min; u <= hor_max; u++)//���ʱ�����Ѿ����0��
							{
								if (u == j) continue;
								auto num = (rand() % 8 + 200) % 7 + 1;
								auto temp_x_mid = 50 * (u + 4);//ˮƽ����
								auto temp_y_mid = 50 * (0 + 1) + 15;
								board[0][u] = num;
								print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
							}
						}

						///��ֱ�Ĳ���
						{
							///�½�����2--��ֱ�½�
							auto now_ver_num = j;//�������ţ�����ǲ�����
							auto delta = ver_max - ver_min + 1;//���������������˶��ٸ�
							auto ver_min_above_num = ver_min - 1;//�����y������С�������Ǹ���Ȼ�󲻶�--�Ϳ���
							while (ver_min_above_num >= 0)
							{
								//x���겻��䣬����now_x_mid
								auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
								print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//��ȥԭ��λ�õ�ͼ�� 
								auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//�������Ӧ���½�����λ�õ�����������
								auto ver_min_below_num = ver_min_above_num + delta;//�������Ӧ���½�����λ�õĶ�ά�����������
								board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta�Ƕ�λ����ĺ����꣨�У�
								print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//��ͬ����ͼ
								ver_min_above_num--;
							}

							///���벿��2--��ֱ����
							for (int u = 0; u < delta; u++)//delta������ʧ�ĸ�������ʧ�˶��ٲ�����
							{
								auto num = (rand() % 8 + 200) % 7 + 1;
								auto temp_y_mid = 50 * (u + 1) + 15;///��ֱ�������now_x_mid�����Բ�����x������+1
								board[u][now_ver_num] = num;
								print_or_erase_one(now_x_mid, temp_y_mid, num, true);
							}
						}
					}

					//2.ֻ��ˮƽ������ȥ����ȥ��������
					else if (horizontal_cnt >= 2 && vertical_cnt < 2)
					{
						int hor_min = 1000, hor_max = -1;//������¼�ᣨ�������������С���꣬�����½�
						int vanish_cnt = 0;
						Sleep(300);
						while (!v_for_horizontal_storage.empty())
						{
							pair<int, int>temp = v_for_horizontal_storage.back();
							v_for_horizontal_storage.pop_back();
							hor_max = max(hor_max, temp.second);//ˮƽ�Ķ�Ӧsecond
							hor_min = min(hor_min, temp.second);
							auto temp_x_mid = 50 * (temp.second + 4);
							auto temp_y_mid = 50 * (temp.first + 1) + 15;
							print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//ע�⣬�����second��x��first��y�������ڶ�boardȡֵ�Ͷ�x��yȡֵ��ʱ��һ��
							//board[temp.first][temp.second] = 0;
							vanish_cnt++;
						}
						hor_max = max(hor_max, j);
						hor_min = min(hor_min, j);
						print_or_erase_one(now_x_mid, now_y_mid, board[i][j], false);
						vanish_cnt++;
						if (vanish_cnt == 4)//ֻ��4��
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("..\\Musics\\bomb��Ч.wav");
						}
						else if (vanish_cnt >= 5)//�п��ܾ�����һ�й�ȥ��5��������
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("D:\\C++\\Bejewels\\Musics\\lightning��Ч.wav");
						}
						if (!is_the_progress_bar_filled(2000.0))
						{
							update_bonus();
							vanish_the_score();
							update_and_refresh_the_score(vanish_cnt, level, bonus);
							double base_level_score = 2000.0;
							update_and_refresh_the_progress_bar(present_score, base_level_score);
						}

						///�½�����
						auto now_hor_num = i;//�������ţ�Ҳ���������Ķ������ڵ��Ǹ��к�
						while (now_hor_num >= 1)//����>=0
						{
							for (int h = hor_min; h <= hor_max; h++)
							{
								auto temp_x_mid = 50 * (h + 4);//�����Ǹ��ĺ����꣨ˮƽ���꣩
								auto temp_y_mid_above = 50 * (now_hor_num)+15;//�����Ǹ��������꣨��ֱ���꣩
								print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][h], false);//�Ȱ������Ǹ����������������ӡ����
								board[now_hor_num][h] = board[now_hor_num - 1][h];
								auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//������һ���ĺ����꣨�����Ǹ����������꣨x���꣩��һ����
								print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][h], true);
							}
							now_hor_num--;///����--�Ŷԣ�
						}

						///�����
						for (int u = hor_min; u <= hor_max; u++)//���ʱ�����Ѿ����0��
						{
							auto num = (rand() % 8 + 200) % 7 + 1;
							auto temp_x_mid = 50 * (u + 4);//ˮƽ����
							auto temp_y_mid = 50 * (0 + 1) + 15;///����+1��
							board[0][u] = num;
							print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
						}
					}

					//3.ֻ�д�ֱ������ȥ
					else if (vertical_cnt >= 2 && horizontal_cnt < 2)
					{
						int ver_min = 1000, ver_max = -1;//������¼�ᣨ�������������С���꣬�����½�
						int vanish_cnt = 0;
						Sleep(300);
						while (!v_for_vertical_storage.empty())
						{
							pair<int, int>temp = v_for_vertical_storage.back();
							v_for_vertical_storage.pop_back();
							ver_max = max(ver_max, temp.first);
							ver_min = min(ver_min, temp.first);
							auto temp_x_mid = 50 * (temp.second + 4);
							auto temp_y_mid = 50 * (temp.first + 1) + 15;
							print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);
							//board[temp.first][temp.second] = 0;
							vanish_cnt++;
						}
						ver_max = max(ver_max, i);
						ver_min = min(ver_min, i);
						print_or_erase_one(now_x_mid, now_y_mid, board[i][j], false);
						vanish_cnt++;
						if (vanish_cnt == 4)//ֻ��4��
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("C:\\Users\\T_Heap\\source\\repos\\��ʯ����\\��ʯ����3����\\bomb��Ч.wav");
						}
						else if (vanish_cnt >= 5)//�п��ܾ�����һ�й�ȥ��5��������
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("C:\\Users\\T_Heap\\source\\repos\\��ʯ����\\��ʯ����3����\\lightning��Ч.wav");
						}
						if (!is_the_progress_bar_filled(2000.0))
						{
							update_bonus();
							vanish_the_score();
							update_and_refresh_the_score(vanish_cnt, level, bonus);
							double base_level_score = 2000.0;
							update_and_refresh_the_progress_bar(present_score, base_level_score);
						}

						///�½�����
						auto now_ver_num = j;//��������
						auto delta = ver_max - ver_min + 1;//���������������˶��ٸ�
						auto ver_min_above_num = ver_min - 1;//�����y������С�������Ǹ���Ȼ�󲻶�--�Ϳ���
						while (ver_min_above_num >= 0)
						{
							//x���겻��䣬����now_x_mid
							auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
							print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//��ȥԭ��λ�õ�ͼ�� 
							auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//�������Ӧ���½�����λ�õ���������
							auto ver_min_below_num = ver_min_above_num + delta;//�������Ӧ���½�����λ�õĶ�ά�����������
							board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta�Ƕ�λ����ĺ����꣨�У�
							print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//��ͬ����ͼ
							ver_min_above_num--;
						}

						///�����
						for (int u = 0; u < delta; u++)//delta������ʧ�ĸ�������ʧ�˶��ٲ�����
						{
							auto num = (rand() % 8 + 200) % 7 + 1;
							auto temp_y_mid = 50 * (u + 1) + 15;//��ֱ�������now_x_mid�����Բ�����x������j+1
							board[u][now_ver_num] = num;
							print_or_erase_one(now_x_mid, temp_y_mid, num, true);
						}
					}
				}
			}
		}
		if (confliction == false) return false;
		return true;//֤�������г�ͻ�ģ�Ҫ����ɨ��
	}
	void check_for_confliction(music_and_sound_play& ms)
	{
		while (fix_the_board_after_vanish(ms));//���һֱ�У���һֱ��
		set_bonus();//����Ҫbonus��0���㶨���г�ͻ֮����ܹ�0
	}
	void abort_the_game()//��ʾ�޷��ƶ�
	{
		COLORREF textcolor = RGB(0, 238, 0);
		settextstyle(90, 40, _T("Courier New"));
		settextcolor(textcolor);
		setbkmode(TRANSPARENT);
		TCHAR con[] = _T("�� �� �� ��");
		outtextxy(90, 230, con);//W:90-530,H:230-320
		Sleep(1000);
	}
	void game_over()//��ӡҳ�沢�˳�
	{
		cleardevice();
		IMAGE img;
		loadimage(&img, _T("..\\Images\\1.jpg"));
		auto max_x = getmaxx();
		auto max_y = getmaxy();
		putimage(0, 0, max_x + 1, max_y + 1, &img, 0, 0, SRCCOPY);
		setbkmode(TRANSPARENT);
		settextstyle(90, 40, _T("Courier New"));
		settextcolor(BROWN);
		TCHAR over[] = _T("��Ϸ����");
		outtextxy(150, 80, over);//W:150-470,H:80-170
		COLORREF textcolor = RGB(153, 50, 204);
		settextstyle(50, 25, _T("Courier New"));
		settextcolor(textcolor);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("Score:");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//������tot_score��ע��
		outtextxy(220, 200, lev_string);//W:220-370,H:200-250
		outtextxy(370, 200, lev_num);//W:370-...,H:200-250
		outtextxy(180, 260, score_string);//W:180-330,H:260-310
		outtextxy(340, 260, score_num);//�����ӡ�����ܷ�������Ϊÿһ�ض�Ҫ���´�ӡ�������
		settextstyle(30, 15, _T("Courier New"));
		TCHAR go_back[] = _T("------�������λ���˳�------");
		MOUSEMSG msg;
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) break;
			else
			{
				settextcolor(WHITE);
				outtextxy(110, 420, go_back);
				Sleep(500);
				settextcolor(BLACK);
				outtextxy(110, 420, go_back);
				Sleep(500);
			}
		}
	}
	bool is_in_the_menu_rect(int x, int y)//W:15-75,H:370-395
	{//menu������ͣ������
		if (15 <= x && x <= 75 && 370 <= y && y <= 395) return true;
		return false;
	}
	int is_in_the_pause_rect(int x, int y)
	{
		if (245 <= x && x <= 395 && 330 <= y && y <= 360) return 1;//˵����"�������˵�"�Ŀ���
		if (260 <= x && x <= 380 && 290 <= y && y <= 320) return 2;//˵����"������Ϸ"�Ŀ���
		return 0;
	}
	void reload_the_board(music_and_sound_play& ms)//�����Ϸ��ͣ�����¿�ʼ����Ҫ���������ټ����������֣������´�ӡͼ��
	{
		ms.resume_music();
		//cleardevice();///�ǵ�����
		BeginBatchDraw();
		IMAGE img;
		loadimage(&img, _T("..\\Images\\1.jpg"));
		auto max_x = getmaxx();
		auto max_y = getmaxy();
		putimage(0, 0, max_x + 1, max_y + 1, &img, 0, 0, SRCCOPY);
		setbkmode(TRANSPARENT);
		int x = 200, y = 65;
		double base_level_score = 2000.0;
		bool is_create = true;
		setlinecolor(RED);
		setlinestyle(PS_DASHDOT | PS_JOIN_ROUND, 6);//6���ؿ����Ӵ�ΪԲ�ǵĵ㻮��
		roundrect(180, 30, 600, 450, 10, 10);//��ӡ��
		for (int i = 0; i < 8; i++)//��ӡͼ��
		{
			for (int j = 0; j < 8; j++)
			{
				int num = this->board[i][j];//i��j�������������ǵ�������
				if (num == 1)create_or_erase_circle(x + 15 + 50 * j, y + 50 * i, 15, is_create);
				else if (num == 2)create_or_erase_square(x + 50 * j, y - 15 + 50 * i, 10, is_create);
				else if (num == 3)create_or_erase_triangle(x + 50 * j, y + 15 + 50 * i, is_create);
				else if (num == 4)create_or_erase_rhombus(x + 50 * j, y + 50 * i, is_create);
				else if (num == 5)create_or_erase_diamond(x + 50 * j, y - 5 + 50 * i, is_create);
				else if (num == 6)create_or_erase_hexagon(x + 50 * j, y - 8 + 50 * i, is_create);
				else if (num == 7)create_or_erase_octagon(x + 50 * j, y + 50 * i, is_create);
				FlushBatchDraw();
			}
		}
		init_the_score();//��ӡ���������������Ȼ��init������Ч��һ��
		print_the_progress_bar_frame();//��ӡ������
		update_and_refresh_the_progress_bar(present_score, base_level_score);
		print_the_buttons();
		EndBatchDraw();
	}
	int game_pause(music_and_sound_play& ms)//����1���������Ϸ������2���������˵�
	{
		ms.pause_music();
		COLORREF linecolor = RGB(129, 231, 89);
		COLORREF textcolor = RGB(212, 122, 111);
		setlinecolor(linecolor);
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
		setfillcolor(YELLOW);
		fillroundrect(170, 180, 470, 380, 10, 10);
		settextstyle(30, 15, _T("Courier New"));
		settextcolor(textcolor);
		setbkmode(TRANSPARENT);
		TCHAR con[] = _T("������Ϸ");
		TCHAR return_main_menu[] = _T("�������˵�");
		outtextxy(260, 290, con);//W:260-380,H:290-320
		outtextxy(245, 330, return_main_menu);//W:245-395,H:330-360
		MOUSEMSG msg;
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (is_in_the_pause_rect(msg.x, msg.y) == 1) return 1;//�������˵�
				if (is_in_the_pause_rect(msg.x, msg.y) == 2)//������Ϸ
				{
					reload_the_board(ms);
					return 2;
				}
			}
		}
	}
	bool is_in_the_reset_rect(int x, int y)//W:90-165,H:370-395
	{
		if (90 <= x && x <= 165 && 370 <= y && y <= 395) return true;
		return false;
	}
	void reset_the_board(music_and_sound_play& ms)//���¿�ʼ
	{
		level = 1.0;//level������0
		present_score = 0.0;
		tot_score = 0.0;
		print_the_board(ms);
	}
	bool is_in_the_tips_rect(int x, int y)//W:55-115,H:330-355
	{
		if (55 <= x && x <= 115 && 330 <= y && y <= 355) return true;
		return false;
	}
	void print_or_erase_tips_frame(int x_num, int y_num, bool is_print)
	{
		int x_left = 200 + 50 * x_num;
		int y_top = 50 + 50 * y_num;
		if (is_print)
		{
			COLORREF framecolor = RGB(204, 255, 255);
			setlinecolor(framecolor);
			setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
			roundrect(x_left - 5, y_top - 5, x_left + 35, y_top + 35, 3, 3);
		}
		else
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
			roundrect(x_left - 5, y_top - 5, x_left + 35, y_top + 35, 3, 3);
		}
	}
	void give_tips(music_and_sound_play& ms)
	{
		jeweled_tips.clear();
		if (scan_the_board_for_availability())
		{
			if (!jeweled_tips.empty())
			{
				pair<int, int>temp = *jeweled_tips.begin();//set.begin()�Ǹ�������
				print_or_erase_tips_frame(temp.first, temp.second, true);
				Sleep(300);
				reload_the_board(ms);
				Sleep(300);
				print_or_erase_tips_frame(temp.first, temp.second, true);
				Sleep(300);
				reload_the_board(ms);
			}
		}
		jeweled_tips.clear();
	}
	bool is_in_the_exit_rect(int x, int y)////W:570-630,H:535-550
	{
		if (570 <= x && x <= 630 && 535 <= y && y <= 550) return true;
		return false;
	}
	int game_cycle_inner(music_and_sound_play& ms)
	{
		print_the_board(ms);//�����ͽ���������������
		check_for_availability(ms);
		MOUSEMSG msg;
		bool click_flag = false, swap_flag = false, to_next_level = false;
		int last_x = 0, last_y = 0;
		double base_level_score = 2000.0;
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				swap_flag = false;
				if (click_flag)///click_flag==true˵���Ѿ��ж�����ѡ���ˣ�����
				{
					print_or_erase_frame(last_x, last_y, false);
					reload_the_board(ms);
					if (is_in_the_jeweled_rect(msg.x, msg.y) && is_nearby(last_x, last_y, msg.x, msg.y))//���4 �� ���2
					{
						Sleep(300);
						swap_flag = swap_jeweled(msg.x, msg.y, last_x, last_y);//swap_flag���true
						bool Did_present_disappear = jeweled_vanish(msg.x, msg.y, ms);
						bool Did_last_disappear = jeweled_vanish(last_x, last_y, ms);
						if (Did_present_disappear || Did_last_disappear)
						{
							check_for_confliction(ms);///���������⣬��ô������������̾�ţ����ˣ�
							reload_the_board(ms);
						}
						if (!Did_present_disappear && !Did_last_disappear)//�Ȼ�˭���У�����ֻ��������ʧ���ˣ������»���
						{
							Sleep(300);
							swap_jeweled(msg.x, msg.y, last_x, last_y);
							reload_the_board(ms);
						}
					}
					click_flag = false;///��ʱ���൱�����4�����2�����ˣ��ص����1�����ֻ�������棬��ô2֮��Ͳ����0
				}
				if (is_in_the_jeweled_rect(msg.x, msg.y) && !swap_flag)//flag==false˵����ǰû�п�ѡ�У�����Ҫ���п�ȡ��������Լ�����1�����3����Ϊswap_flagÿ�ζ���0
				{
					click_flag = print_or_erase_frame(msg.x, msg.y, true);//click_flag����true
				}
				if (is_in_the_menu_rect(msg.x, msg.y))
				{
					int ret = game_pause(ms);
					if (ret == 1) return 1;//1���������˵�
				}
				if (is_in_the_reset_rect(msg.x, msg.y))
				{
					reset_the_board(ms);
				}
				if (is_in_the_tips_rect(msg.x, msg.y))
				{
					give_tips(ms);
				}
				if (is_in_the_exit_rect(msg.x, msg.y))
				{
					exit(0);
				}
				last_x = msg.x;//��¼��ǰ���꣬����һ����ʹ��
				last_y = msg.y;
			}
			if (!scan_the_board_for_availability())//����ģʽ ����
			{
				abort_the_game();
				game_over();
				jeweled_tips.clear();
				return 1;//��ʾǿ�з������˵�
			}
			to_next_level = is_the_progress_bar_filled(base_level_score);
			if (to_next_level == true) return 2;
			to_next_level = false;//��ֹ����
		}
	}
	int game_cycle_outter(music_and_sound_play& ms)//���ó�������Ϊ������Ҳ�ܼ��ӵ����
	{
		int ret = -1;
		ms.stop_music();
		ms.close_music();
		ms.play_music("..\\Musics\\����.mp3");
		while (true)
		{
			ret = game_cycle_inner(ms);
			if (ret == 1) return 1;//�����ѡ���˷��أ��ͷ��������棬��2�Ͳ��ù�
			if (ret == 2)
			{
				update_level();
				set_present_score();
				continue;
			}
		}
	}

private:
	int board[9][9];
	double level;
	int bonus;
	double present_score;				//present_score�ǵ�ǰ�ؿ��ķ�����Ҫ����
	double tot_score;					//tot_score���ܷ�������Ҫ����
	set<pair<int, int>>jeweled_tips;	//������ʾ�����꣬�ǵ����㣬��set��Ϊ�˲��ظ�
};