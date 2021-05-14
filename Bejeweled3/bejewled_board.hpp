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
	void create_or_erase_triangle(int x, int y, bool is_create)//三角形左边底部点坐标
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
	void create_or_erase_rhombus(int x, int y, bool is_create)//菱形中点坐标
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
	void create_or_erase_diamond(int x, int y, bool is_create)//钻石左边最突出的点
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
	void create_or_erase_hexagon(int x, int y, bool is_create)//六边形左上角的点
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
	void create_or_erase_octagon(int x, int y, bool is_create)//八边形最左边的中间点
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
	void print_or_erase_one(int x, int y, int num, bool is_print)//传入的x和y都是中点，print_one，print_one_row都是传入中点
	{                                                         //但是这里的x和y，其实是列和行，要注意
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
		TCHAR score_string[] = _T("当前分数");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//这里是tot_score，注意
		outtextxy(25, 50, lev_string);//W:25-115,H:50-75
		outtextxy(120, 50, lev_num);//W:120-...,H:50-75
		outtextxy(23, 80, score_string);//W:23-143,H:80-105
		outtextxy(55, 110, score_num);//这个打印的是总分数，因为每一关都要重新打印这个分数
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
	bool scan_the_board_for_availability()//看看有没有可交换的，有就返回true并返回点的x和y坐标，没有就false，内部接口
	{
		int direct_in_hor[] = { -1,0,1,0 }, direct_in_ver[] = { 0,-1,0,1 };
		bool is_available = false;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)//每一个点都搜索
			{
				///bfs寻找部分，四个点都找，map就是为了储存至少两个点颜色相同的状况
				map<int, vector<int>>stor;//key是颜色，k是方向，0左1上2右3下
				for (int k = 0; k < 4; k++)
				{
					auto temp_x = j + direct_in_hor[k];
					auto temp_y = i + direct_in_ver[k];
					if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
					int present_jeweled = board[temp_y][temp_x];
					if (stor.find(present_jeweled) == stor.end())//这东西不存在
					{
						vector<int>temp = {};
						temp.emplace_back(k);
						stor[present_jeweled] = temp;
					}
					else //这东西已经存在
					{
						stor[present_jeweled].emplace_back(k);
					}
				}
				///判断部分+dfs部分
				for (auto& val : stor)
				{
					int cnt = 0;//cnt就够了，不用分方向，因为不计较方向
					if (val.second.size() == 2)//val是个迭代器，是个pair，分三种情况，2 3 4，2代表只有两个方向有同色
					{
						int present_jeweled = val.first;
						for (auto direct : val.second)
						{
							cnt++;
							int step = 2;//step=2走两步
							if (direct == 0)//0左
							{
								auto temp_x = j - step;
								auto temp_y = i;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)//如果只剩一个了，就别消除了
										auto it_next = val.second.erase(it);
								}
							}
							if (direct == 1)//1上
							{
								auto temp_x = j;
								auto temp_y = i - step;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)
										auto it_next = val.second.erase(it);//it_next没用的
								}
							}
							if (direct == 2)//2右
							{
								auto temp_x = j + step;
								auto temp_y = i;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)
										auto it_next = val.second.erase(it);//it_next没用的
								}
							}
							if (direct == 3)//3下
							{
								auto temp_x = j;
								auto temp_y = i + step;
								if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7) continue;
								if (board[temp_y][temp_x] == present_jeweled)
								{
									cnt++;
									auto it = find(val.second.cbegin(), val.second.cend(), direct);
									if (val.second.size() > 1)
										auto it_next = val.second.erase(it);//it_next没用的
								}
							}
						}
						if (cnt >= 3)
						{
							is_available = true;
							if (!val.second.empty())//这个时候里面只有一个了
							{
								auto direct = val.second.back();
								val.second.pop_back();
								int temp_x = j + direct_in_hor[direct];
								int temp_y = i + direct_in_ver[direct];
								jeweled_tips.emplace(make_pair(temp_x, temp_y));
							}
						}
					}
					else if (val.second.size() == 3)//3代表三个方向有同色
					{
						is_available = true;
						if (find(val.second.cbegin(), val.second.cend(), 0) != val.second.end() && find(val.second.cbegin(), val.second.cend(), 2) != val.second.end())//水平（左右）夹上下
						{
							for (auto v : val.second)
							{
								if (v == 0 || v == 2) continue;//水平的不要，就是记录竖直方向
								auto direct = v;
								if (direct == 1)//1上
								{
									auto temp_x = j;
									auto temp_y = i - 1;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
								else if (direct == 3)//3下
								{
									auto temp_x = j;
									auto temp_y = i + 1;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
							}
						}
						else if (find(val.second.cbegin(), val.second.cend(), 1) != val.second.end() && find(val.second.cbegin(), val.second.cend(), 3) != val.second.end())//垂直（上下）夹左右
						{
							for (auto v : val.second)
							{
								if (v == 1 || v == 3) continue;//竖直的不要，就是记录水平方向
								auto direct = v;
								if (direct == 0)//0左
								{
									auto temp_x = j - 1;
									auto temp_y = i;
									if (temp_x < 0 || temp_x > 7 || temp_y < 0 || temp_y > 7)
										continue;
									jeweled_tips.emplace(make_pair(temp_x, temp_y));
								}
								else if (direct == 2)//2右
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
					else if (val.second.size() == 4)//4个，就是四面包围，随便搞一个进去，这里是将下面的那个搞进去
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
	bool fix_the_board()///因为要逐个都是遍历，遍历后也可能出状况，比起先完整遍历一遍再去替换这样会更好
	{//从第一个开始，向右向下遍历，发现有两个重复的就将这个去除然后生成一个不是这个东西的
		bool is_confiction = false;
		for (int i = 0; i < 8; i++)//每一个都这样执行
		{
			for (int j = 0; j < 8; j++)
			{
				vector<pair<int, int>>hor = {}, ver = {};
				int present_jeweled = board[i][j], flag = 0;
				for (int step = 1; step <= 2; step++)//检查部分
				{
					if (step > 1 && flag == 0) break;//因为如果step>1了，flag还是0也就是说最旁边的根本不一样，就直接跳了
					int hor_coord = j + step, ver_coord = i + step;
					if (hor_coord <= 7 && present_jeweled == board[i][hor_coord])///水平检查，改了条件
					{
						hor.emplace_back(make_pair(i, hor_coord));
						flag++;//剪枝，如果第一个就没了，那就算了
					}
					if (ver_coord <= 7 && present_jeweled == board[ver_coord][j])///垂直检查，改了条件
					{
						ver.emplace_back(make_pair(ver_coord, j));
						flag++;
					}
				}
				if (flag == 0)///剪枝，改了
				{
					continue;
				}
				//替换部分
				if (hor.size() >= 2)//水平部分，取最尾的点
				{
					is_confiction = true;//如果说有>=2的，就变true了
					pair<int, int>temp = hor.back();
					int now_x = 200 + 50 * temp.second, now_y = 65 + 50 * temp.first;///改了，不是乘i和j
					int num = (rand() % 8 + 200) % 7 + 1;
					while (num == present_jeweled) num = (rand() % 8 + 200) % 7 + 1;
					board[temp.first][temp.second] = num;
					//重新生成一个不一样的
				}
				if (ver.size() >= 2)//水平部分，取最尾的点
				{
					is_confiction = true;
					pair<int, int>temp = ver.back();
					int now_x = 200 + 50 * temp.second, now_y = 65 + 50 * temp.first;//不是乘i和j啊
					int num = (rand() % 8 + 200) % 7 + 1;
					while (num == present_jeweled) num = (rand() % 8 + 200) % 7 + 1;
					board[temp.first][temp.second] = num;
					//重新生成一个不一样的
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
		while (fix_the_board());//修正，直到这个棋盘根本不需要修正为止
		BeginBatchDraw();
		//cleardevice();
		IMAGE img;
		loadimage(&img, _T("..\\Images\\1.jpg"));
		auto max_x = getmaxx();
		auto max_y = getmaxy();
		putimage(0, 0, max_x + 1, max_y + 1, &img, 0, 0, SRCCOPY);
		setbkmode(TRANSPARENT);
		int x = 200, y = 65;//保证了传入都是中点，+50i和+50j这些只是移位
		setlinecolor(RED);
		setlinestyle(PS_DASHDOT | PS_JOIN_ROUND, 6);//6像素宽，连接处为圆角的点划线
		roundrect(180, 30, 600, 450, 10, 10);
		bool is_create = true;
		for (int i = 0; i < 8; i++)//j,i要从0开始，因为下面要加j和i
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
		init_the_score();//这个打印的是总分数，因为每一关都要重新打印这个分数
		print_the_buttons();
		print_the_progress_bar_frame();
		EndBatchDraw();
	}
	void check_for_availability(music_and_sound_play& ms)//外部接口，是否有可交换的
	{
		while (!scan_the_board_for_availability())
		{
			print_the_board(ms);
			fix_the_board();
			jeweled_tips.clear();//记得清空
		}
		jeweled_tips.clear();
	}
	bool is_in_the_jeweled_rect(int x, int y)//传入的是实时的鼠标坐标，判断鼠标是否在框内（是否点击了图块）
	{
		bool in_x = (0 <= (x % 50) && (x % 50) <= 30) && x >= 200 && x <= 600;
		bool in_y = (0 <= (y % 50) && (y % 50) <= 30) && y >= 50 && y <= 450;
		if (in_x && in_y) return true;
		else return false;
	}
	bool is_nearby(int last_x, int last_y, int now_x, int now_y)//判断第二个框是不是在第一个框附近，原则是，以last为中心进行判断
	{                                                        //传入的是是一个框和当前框的鼠标坐标
		int delta_last_x = last_x - (last_x / 50) * 50;//先把它们的位置统一成正方形左上角的顶点
		int delta_last_y = last_y - (last_y / 50) * 50;
		int last_x_left = last_x - delta_last_x;
		int last_y_top = last_y - delta_last_y;
		int delta_now_x = now_x - (now_x / 50) * 50;
		int delta_now_y = now_y - (now_y / 50) * 50;
		int now_x_left = now_x - delta_now_x;
		int now_y_top = now_y - delta_now_y;
		bool is_onleft = ((last_x_left - 50) == now_x_left && (last_y_top == now_y_top));//是否在上下左右
		bool is_onright = ((last_x_left + 50) == now_x_left && (last_y_top == now_y_top));
		bool is_ontop = ((last_y_top - 50) == now_y_top && (last_x_left == now_x_left));///on_top是-不是+！！！反了！
		bool is_onbottom = ((last_y_top + 50) == now_y_top && (last_x_left == now_x_left));
		//接下来判断全部
		if (last_x_left == 200)//判断边界
		{
			if (last_y_top == 50)//last 在左上角
			{
				if (is_onright || is_onbottom) return true;
			}
			else if (last_y_top == 400)//last 在左下角
			{
				if (is_onright || is_ontop) return true;
			}
			else//last 在左边缘（非左上左下）
			{
				if (is_ontop || is_onright || is_onbottom) return true;
			}
		}
		else if (last_x_left == 550)
		{
			if (last_y_top == 50)//last 在右上角
			{
				if (is_onleft || is_onbottom) return true;
			}
			else if (last_y_top == 400)//last 在右下角
			{
				if (is_onleft || is_ontop) return true;
			}
			else//last 在右边缘（非右上右下）
			{
				if (is_ontop || is_onleft || is_onbottom) return true;
			}
		}
		else if (last_y_top == 50)//last 在上边界（不是左上右上）
		{
			if (is_onleft || is_onbottom || is_onright) return true;
		}
		else if (last_y_top == 400)//last 在下边界（不是左下右下）
		{
			if (is_onleft || is_ontop || is_onright) return true;
		}
		else
		{
			if (is_onleft || is_ontop || is_onright || is_onbottom) return true;
		}
		return false;//如果不相邻，或者点了自己本身
	}
	bool print_or_erase_frame(int x, int y, bool is_print)//print传入的是实时的鼠标坐标,erase传入的是上一次的鼠标坐标
	{
		int delta_x = x - (x / 50) * 50;
		int delta_y = y - (y / 50) * 50;
		int x_left = x - delta_x;//变成左上角的点
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
	bool swap_jeweled(int now_x, int now_y, int last_x, int last_y)//传入的是是一个框和当前框的鼠标坐标
	{
		int now_x_num = now_x / 50 - 4;             //算出来的是在数组的序号
		int now_y_num = now_y / 50 - 1;             ///弱智，-1啊，不是-4啊
		int last_x_num = last_x / 50 - 4;
		int last_y_num = last_y / 50 - 1;
		int delta_now_x = now_x - (now_x / 50) * 50;
		int delta_now_y = now_y - (now_y / 50) * 50;
		int now_x_mid = now_x - delta_now_x;        ///这里所有步骤，目的是将x和y变成左中点
		int now_y_mid = now_y - delta_now_y + 15;
		int delta_last_x = last_x - (last_x / 50) * 50;
		int delta_last_y = last_y - (last_y / 50) * 50;
		int last_x_mid = last_x - delta_last_x;
		int last_y_mid = last_y - delta_last_y + 15;
		print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], false);///记住，x是列，y是行，不要反了！
		print_or_erase_one(last_x_mid, last_y_mid, board[last_y_num][last_x_num], false);//先抹掉
		swap(board[now_y_num][now_x_num], board[last_y_num][last_x_num]);//从0 0开始算
		print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], true);
		print_or_erase_one(last_x_mid, last_y_mid, board[last_y_num][last_x_num], true);
		return true;
	}
	void vanish_the_score()//这个删除的也是总分数，因为每一关保留的是这个分数
	{
		settextstyle(25, 15, _T("Consolas"));
		settextcolor(BLACK);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("当前分数");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//这里是tot_score，注意
		outtextxy(25, 50, lev_string);//W:25-115,H:50-75
		outtextxy(120, 50, lev_num);//W:120-...,H:50-75
		outtextxy(23, 80, score_string);//W:23-143,H:80-105
		outtextxy(55, 110, score_num);//这个删除的是总分数，因为每一关都要重新打印这个分数
	}
	void update_and_refresh_the_score(int vanish_cnt, double level, int bonus)//bonus:倍数，连续几个消除那就是几
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
			present_score += 50.0 * level * bonus;///这个也要更新，只不过它会清零
		}
		settextstyle(25, 15, _T("Consolas"));
		settextcolor(WHITE);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("当前分数");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//这里是tot_score，注意
		outtextxy(25, 50, lev_string);//W:25-115,H:50-75
		outtextxy(120, 50, lev_num);//W:120-...,H:50-75
		outtextxy(23, 80, score_string);//W:23-143,H:80-105
		outtextxy(55, 110, score_num);//这个打印的是总分数，因为每一关都要重新打印这个分数
	}
	void print_the_progress_bar_frame()
	{
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
		rectangle(158, 458, 622, 502);//中间的框是460*40，线宽留2
	}
	void vanish_the_progress_bar()//满了之后要消除
	{
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
		setfillcolor(BLACK);
		fillrectangle(158, 458, 622, 502);
	}
	void update_and_refresh_the_progress_bar(double present_score, double base_level_score)
		//level_score是当前关卡的总分数
	{//总长460，按照比例来进行打印
		double tot_len = 460.0;///注意，这里的present_score是每一关的分数，每一关的分数是要清零的！
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
	bool jeweled_vanish(int now_x, int now_y, music_and_sound_play& ms)//核心算法，这个now_x和now_y和swap的一样
	{													//不仅要判断出来，是否应该消除，如果要，还需要将这些给消除掉
		setbkmode(TRANSPARENT);
		int now_x_num = now_x / 50 - 4;                 //二维数组的列号
		int now_y_num = now_y / 50 - 1;                 //二维数组的行号
		int now_x_mid = 200 + 50 * now_x_num;			//中点x的坐标
		int now_y_mid = 65 + 50 * now_y_num;			//中点y的坐标    
		int direct_in_ver[] = { -1,0,1,0 };             //方向数组，bfs用,ver->y,hor->x
		int direct_in_hor[] = { 0,1,0,-1 };
		int horizontal_cnt = 0, vertical_cnt = 0;       //必须记录下来横多少个，竖多少个
		int present_jeweled = board[now_y_num][now_x_num];//当前宝石的编号
		queue<pair<int, int>>q_for_bfs;
		vector<pair<int, int>>v_for_horizontal_storage, v_for_vertical_storage;//记录下究竟是横向相消还是竖向相消

		///搜寻，判断部分
		for (int i = 0; i < 4; i++)//bfs
		{
			auto temp_x = now_x_num + direct_in_hor[i];
			auto temp_y = now_y_num + direct_in_ver[i];//temp_y（一列下来）和temp_x（一行下来）是左右移动后的坐标
			if (0 <= temp_x && temp_x <= 7 && 0 <= temp_y && temp_y <= 7 && board[temp_y][temp_x] == present_jeweled)///要检测，不能出边界，检测的顺序很早，要先看越界没有
			{
				q_for_bfs.emplace(make_pair(temp_y, temp_x));//如果等于，就入队
				if (direct_in_ver[i] == 1 || direct_in_ver[i] == -1)//direct_in_ver是垂直的，所以record[1]++
				{
					vertical_cnt++;                 //竖直的相同，就++
					v_for_vertical_storage.emplace_back(make_pair(temp_y, temp_x));//记录下来，不然不知道究竟是横还是竖
				}///这里一开始垂直和水平调转了
				else
				{
					horizontal_cnt++;               //横向的相同，就++
					v_for_horizontal_storage.emplace_back(make_pair(temp_y, temp_x));//入队的时候，先y后x即先行后列
				}
			}
		}
		while (!q_for_bfs.empty())//dfs，步长
		{
			pair<int, int>nearby_jeweled = q_for_bfs.front();
			q_for_bfs.pop();
			int step = 1;//向上走，2只是保险
			if (nearby_jeweled.first + 1 == now_y_num && nearby_jeweled.second == now_x_num)//在上方
			{///这个加减step还是可能出界，因为数组可能会越界，越界可能是乱码，然后恰好相等，所以要加判断
				while (true)
				{
					if (step >= 2) break;///这样写，是为了既可以保证检查越界，又可以保证不断层
					if (nearby_jeweled.first - step > 7 || nearby_jeweled.first - step < 0) break;
					if (board[nearby_jeweled.first - step][now_x_num] == present_jeweled)//向上走
					{
						vertical_cnt++;
						v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first - step, now_x_num));
						step++;
					}
					else break;//不等于直接滚啊，断层了
				}
			}
			if (nearby_jeweled.first - 1 == now_y_num && nearby_jeweled.second == now_x_num)//在下方
			{
				while (true)
				{
					if (step >= 2) break;///这样写，是为了既可以保证检查越界，又可以保证不断层
					if (nearby_jeweled.first + step > 7 || nearby_jeweled.first + step < 0) break;
					if (board[nearby_jeweled.first + step][now_x_num] == present_jeweled && step <= 2)//向下走
					{
						vertical_cnt++;
						v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first + step, now_x_num));
						step++;
					}
					else break;//不等于直接滚啊，断层了
				}
			}
			if (nearby_jeweled.second + 1 == now_x_num && nearby_jeweled.first == now_y_num)//在左方
			{
				while (true)
				{
					if (step >= 2) break;///这样写，是为了既可以保证检查越界，又可以保证不断层
					if (nearby_jeweled.second - step > 7 || nearby_jeweled.second - step < 0) break;
					if (board[now_y_num][nearby_jeweled.second - step] == present_jeweled && step <= 2)//向左走
					{
						horizontal_cnt++;
						v_for_horizontal_storage.emplace_back(make_pair(now_y_num, nearby_jeweled.second - step));//分别把横竖的点都记下来
						step++;///step位置不对，不然会变2
					}
					else break;//不等于直接滚啊，断层了
				}
			}
			if (nearby_jeweled.second - 1 == now_x_num && nearby_jeweled.first == now_y_num)//在右方
			{
				while (true)
				{
					if (step >= 2) break;///这样写，是为了既可以保证检查越界，又可以保证不断层
					if (nearby_jeweled.second + step > 7 || nearby_jeweled.second + step < 0) break;
					if (board[now_y_num][nearby_jeweled.second + step] == present_jeweled && step <= 2)//向右走
					{
						horizontal_cnt++;
						v_for_horizontal_storage.emplace_back(make_pair(now_y_num, nearby_jeweled.second + step));//不记下来都不知道是谁的贡献
						step++;
					}
					else break;//不等于直接滚啊，断层了
				}
			}
		}

		///消除部分
		//1.五个相同以上，并且是横几个竖几个
		if (horizontal_cnt >= 2 && vertical_cnt >= 2)
		{
			Sleep(300);
			int hor_min = 1000, hor_max = -1;
			int ver_min = 1000, ver_max = -1;//用来记录横（或竖）的最大最小坐标，用来下降
			int vanish_cnt = 0;
			while (!v_for_horizontal_storage.empty())
			{
				pair<int, int>temp = v_for_horizontal_storage.back();
				v_for_horizontal_storage.pop_back();
				hor_max = max(hor_max, temp.second);//水平的对应second
				hor_min = min(hor_min, temp.second);
				auto temp_x_mid = 50 * (temp.second + 4);
				auto temp_y_mid = 50 * (temp.first + 1) + 15;//print_or_erase_one用的是物理坐标值，而不是数组下标值，所以要算出中点
				print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//注意，这里的second是x，first是y，所以在对board取值和对x和y取值的时候不一样
				board[temp.first][temp.second] = 0;//其实没有影响
				vanish_cnt++;
			}
			while (!v_for_vertical_storage.empty())
			{
				pair<int, int>temp = v_for_vertical_storage.back();
				v_for_vertical_storage.pop_back();
				ver_max = max(ver_max, temp.first);
				ver_min = min(ver_min, temp.first);///错了，一开始写成了first
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
			ms.play_sound("C:\\Users\\T_Heap\\source\\repos\\宝石迷阵\\宝石迷阵3音乐\\lightning音效.wav");
			if (!is_the_progress_bar_filled(2000.0))
			{
				update_bonus();
				vanish_the_score();
				update_and_refresh_the_score(vanish_cnt, level, bonus);
				double base_level_score = 2000.0;
				update_and_refresh_the_progress_bar(present_score, base_level_score);
			}

			/* 对于下降部分，先保留垂直方向的三个，先把横向的两个给下降了，补齐；再下降垂直的，再补齐*/
			///横向的操作，分块
			{
				///下降部分1--横向下降
				auto now_hor_num = now_y_num;//纵向的序号
				while (now_hor_num >= 1)//不能>=0
				{
					for (int i = hor_min; i <= hor_max; i++)
					{
						if (i == now_x_num) continue;//如果在这三个水平坐标中，遇到了跟垂直方向相同的那个就跳过，其实就多了这一句，所以那一列就完全不理了
						auto temp_x_mid = 50 * (i + 4);//上面那个的横坐标（水平坐标）
						auto temp_y_mid_above = 50 * (now_hor_num)+15;//上面那个的纵坐标（竖直坐标）
						print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][i], false);//先把上面那个消掉，再在下面打印出来
						board[now_hor_num][i] = board[now_hor_num - 1][i];
						auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//现在这一个的横坐标（下面那个），纵坐标（x坐标）是一样的
						print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][i], true);
					}
					now_hor_num--;
				}

				///补齐部分1--横向补齐
				for (int j = hor_min; j <= hor_max; j++)//这个时候行已经变成0了
				{
					if (j == now_x_num) continue;
					auto num = (rand() % 8 + 200) % 7 + 1;
					auto temp_x_mid = 50 * (j + 4);//水平坐标
					auto temp_y_mid = 50 * (0 + 1) + 15;
					board[0][j] = num;
					print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
				}
			}

			///垂直的操作
			{
				///下降部分2--竖直下降
				auto now_ver_num = now_x_num;//横向的序号，这个是不会变的
				auto delta = ver_max - ver_min + 1;//最下面和最上面差了多少个
				auto ver_min_above_num = ver_min - 1;//这个是y坐标最小的上面那个，然后不断--就可以
				while (ver_min_above_num >= 0)
				{
					//x坐标不会变，就是now_x_mid
					auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
					print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//消去原来位置的图形 
					auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//这个就是应该下降到的位置的物理坐标了
					auto ver_min_below_num = ver_min_above_num + delta;//这个就是应该下降到的位置的二维数组的行坐标
					board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta是二位数组的横坐标（行）
					print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//画同样的图
					ver_min_above_num--;
				}

				///补齐部分2--竖直补齐
				for (int j = 0; j < delta; j++)//delta就是消失的个数，消失了多少补多少
				{
					auto num = (rand() % 8 + 200) % 7 + 1;
					auto temp_y_mid = 50 * (j + 1) + 15;///竖直坐标就是now_x_mid，所以不用算x，忘了+1
					board[j][now_ver_num] = num;
					print_or_erase_one(now_x_mid, temp_y_mid, num, true);
				}
			}
			return true;
		}

		//2.只有水平可以消去，消去立即补齐
		else if (horizontal_cnt >= 2 && vertical_cnt < 2)
		{
			Sleep(300);
			int hor_min = 1000, hor_max = -1;//用来记录横（或竖）的最大最小坐标，用来下降
			int vanish_cnt = 0;
			while (!v_for_horizontal_storage.empty())
			{
				pair<int, int>temp = v_for_horizontal_storage.back();
				v_for_horizontal_storage.pop_back();
				hor_max = max(hor_max, temp.second);//水平的对应second
				hor_min = min(hor_min, temp.second);
				auto temp_x_mid = 50 * (temp.second + 4);
				auto temp_y_mid = 50 * (temp.first + 1) + 15;
				print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//注意，这里的second是x，first是y，所以在对board取值和对x和y取值的时候不一样
				board[temp.first][temp.second] = 0;
				vanish_cnt++;
			}
			hor_max = max(hor_max, now_x_num);
			hor_min = min(hor_min, now_x_num);
			print_or_erase_one(now_x_mid, now_y_mid, board[now_y_num][now_x_num], false);
			board[now_y_num][now_x_num] = 0;
			vanish_cnt++;
			if (vanish_cnt == 4)//只有4个
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("..\\Musics\\bomb音效.wav");
			}
			else if (vanish_cnt >= 5)//有可能就这样一行过去，5个就闪电
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("..\\Musics\\lightning音效.wav");
			}
			if (!is_the_progress_bar_filled(2000.0))
			{
				update_bonus();
				vanish_the_score();
				update_and_refresh_the_score(vanish_cnt, level, bonus);
				double base_level_score = 2000.0;
				update_and_refresh_the_progress_bar(present_score, base_level_score);
			}

			///下降部分
			auto now_hor_num = now_y_num;//纵向的序号，也就是消除的东西所在的那个行号
			while (now_hor_num >= 1)//不能>=0
			{
				for (int i = hor_min; i <= hor_max; i++)
				{
					auto temp_x_mid = 50 * (i + 4);//上面那个的横坐标（水平坐标）
					auto temp_y_mid_above = 50 * (now_hor_num)+15;//上面那个的纵坐标（竖直坐标）
					print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][i], false);//先把上面那个消掉，再在下面打印出来
					board[now_hor_num][i] = board[now_hor_num - 1][i];
					auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//现在这一个的横坐标（下面那个），纵坐标（x坐标）是一样的
					print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][i], true);
				}
				now_hor_num--;///这里--才对！
			}

			///填补部分
			for (int j = hor_min; j <= hor_max; j++)//这个时候行已经变成0了
			{
				auto num = (rand() % 8 + 200) % 7 + 1;
				auto temp_x_mid = 50 * (j + 4);//水平坐标
				auto temp_y_mid = 50 * (0 + 1) + 15;///忘了+1了
				board[0][j] = num;
				print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
			}
			return true;
		}

		//3.只有垂直可以消去
		else if (vertical_cnt >= 2 && horizontal_cnt < 2)
		{
			Sleep(300);
			int ver_min = 1000, ver_max = -1;//用来记录横（或竖）的最大最小坐标，用来下降
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
			if (vanish_cnt == 4)//只有4个
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("..\\Musics\\bomb音效.wav");
			}
			else if (vanish_cnt >= 5)//有可能就这样一行过去，5个就闪电
			{
				ms.stop_sound();
				ms.close_sound();
				ms.play_sound("D:\\C++\\Bejewels\\Musics\\lightning音效.wav");
			}
			if (!is_the_progress_bar_filled(2000.0))//如果满了，可以消除，但是分数就不要加了
			{
				update_bonus();
				vanish_the_score();
				update_and_refresh_the_score(vanish_cnt, level, bonus);
				double base_level_score = 2000.0;
				update_and_refresh_the_progress_bar(present_score, base_level_score);
			}
			///下降部分
			auto now_ver_num = now_x_num;//纵向的序号
			auto delta = ver_max - ver_min + 1;//最下面和最上面差了多少个
			auto ver_min_above_num = ver_min - 1;//这个是y坐标最小的上面那个，然后不断--就可以
			while (ver_min_above_num >= 0)
			{
				//x坐标不会变，就是now_x_mid
				auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
				print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//消去原来位置的图形 
				auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//这个就是应该下降到的位置的物理坐标了
				auto ver_min_below_num = ver_min_above_num + delta;//这个就是应该下降到的位置的二维数组的行坐标
				board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta是二位数组的横坐标（行）
				print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//画同样的图
				ver_min_above_num--;
			}

			///填补部分
			for (int j = 0; j < delta; j++)//delta就是消失的个数，消失了多少补多少
			{
				auto num = (rand() % 8 + 200) % 7 + 1;
				auto temp_y_mid = 50 * (j + 1) + 15;//竖直坐标就是now_x_mid，所以不用算x，忘了j+1
				board[j][now_ver_num] = num;
				print_or_erase_one(now_x_mid, temp_y_mid, num, true);
			}
			return true;
		}
		return false;
	}
	bool fix_the_board_after_vanish(music_and_sound_play& ms)///因为要逐个都是遍历，遍历后也可能出状况，比起先完整遍历一遍再去替换这样会更好
	{
		setbkmode(TRANSPARENT);
		int direct_in_ver[] = { -1,0,1,0 };             //方向数组，bfs用,ver->y,hor->x
		int direct_in_hor[] = { 0,1,0,-1 };
		bool confliction = false;//如果到了最后一个还是true，那就说明没有冲突了
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int horizontal_cnt = 0, vertical_cnt = 0;       //必须记录下来横多少个，竖多少个
				queue<pair<int, int>>q_for_bfs;
				vector<pair<int, int>>v_for_horizontal_storage, v_for_vertical_storage;
				//记录下究竟是横向相消还是竖向相消
				int present_jeweled = board[i][j];
				int now_x_mid = 200 + 50 * j;
				int now_y_mid = 65 + 50 * i;
				//搜寻部分
				for (int k = 0; k < 4; k++)///搜寻，判断部分，bfs
				{
					auto temp_x = j + direct_in_hor[k];
					auto temp_y = i + direct_in_ver[k];
					if (0 <= temp_x && temp_x <= 7 && 0 <= temp_y && temp_y <= 7 && board[temp_y][temp_x] == present_jeweled)
						///要检测，不能出边界，检测的顺序很早，要先看越界没有
					{
						q_for_bfs.emplace(make_pair(temp_y, temp_x));//如果等于，就入队
						if (direct_in_ver[k] == 1 || direct_in_ver[k] == -1)
						{
							vertical_cnt++;                 //竖直的相同，就++
							v_for_vertical_storage.emplace_back(make_pair(temp_y, temp_x));
						}///这里一开始垂直和水平调转了
						else
						{
							horizontal_cnt++;               //横向的相同，就++
							v_for_horizontal_storage.emplace_back(make_pair(temp_y, temp_x));//入队的时候，先y后x即先行后列
						}
					}
				}
				while (!q_for_bfs.empty())///深入搜寻，dfs，步长
				{
					pair<int, int>nearby_jeweled = q_for_bfs.front();
					q_for_bfs.pop();
					int step = 1;//step设为2只是保险
					if (nearby_jeweled.first + 1 == i && nearby_jeweled.second == j)//在上方
					{
						while (true)
						{
							if (step >= 3) break;///这样写，是为了既可以保证检查越界，又可以保证不断层
							if (nearby_jeweled.first - step > 7 || nearby_jeweled.first - step < 0) break;
							if (board[nearby_jeweled.first - step][j] == present_jeweled)//向上走
							{
								vertical_cnt++;
								v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first - step, j));
								step++;
							}
							else break;//不等于直接滚啊，断层了
						}
					}
					if (nearby_jeweled.first - 1 == i && nearby_jeweled.second == j)//在下方
					{
						while (true)
						{
							if (step >= 3) break;//3是因为可能一列下来或者一列过来5个
							if (nearby_jeweled.first + step > 7 || nearby_jeweled.first + step < 0) break;
							if (board[nearby_jeweled.first + step][j] == present_jeweled)//向下走
							{
								vertical_cnt++;
								v_for_vertical_storage.emplace_back(make_pair(nearby_jeweled.first + step, j));
								step++;
							}
							else break;//不等于直接滚啊，断层了
						}
					}
					if (nearby_jeweled.second + 1 == j && nearby_jeweled.first == i)//在左方
					{
						while (true)
						{
							if (step >= 3) break;
							if (nearby_jeweled.second - step > 7 || nearby_jeweled.second - step < 0) break;
							if (board[i][nearby_jeweled.second - step] == present_jeweled)//向左走
							{
								horizontal_cnt++;//必须做好判断，防止越界
								v_for_horizontal_storage.emplace_back(make_pair(i, nearby_jeweled.second - step));//分别把横竖的点都记下来
								step++;///改过，step位置不对
							}
							else break;//不等于直接滚啊，断层了
						}
					}
					if (nearby_jeweled.second - 1 == j && nearby_jeweled.first == i)//在右方
					{
						while (true)
						{
							if (step >= 3) break;
							if (nearby_jeweled.second + step > 7 || nearby_jeweled.second + step < 0) break;
							if (board[i][nearby_jeweled.second + step] == present_jeweled)//向右走
							{
								horizontal_cnt++;
								v_for_horizontal_storage.emplace_back(make_pair(i, nearby_jeweled.second + step));//不记下来都不知道是谁的贡献
								step++;
							}
							else break;//不等于直接滚啊，断层了
						}
					}
				}
				///剪枝，就是这里使得它有了纯检查的功能，只有64个格子全部判断完没有问题，才是真的没冲突
				if (vertical_cnt <= 1 && horizontal_cnt <= 1) continue;
				//下面是消除和填补部分
				else//2+1 2+2，这里才是消除
				{
					confliction = true;
					///消除部分
					//1.五个相同以上，并且是横几个竖几个
					if (horizontal_cnt >= 2 && vertical_cnt >= 2)
					{
						int hor_min = 1000, hor_max = -1;
						int ver_min = 1000, ver_max = -1;//用来记录横（或竖）的最大最小坐标，用来下降
						int vanish_cnt = 0;
						Sleep(300);
						while (!v_for_horizontal_storage.empty())
						{
							pair<int, int>temp = v_for_horizontal_storage.back();
							v_for_horizontal_storage.pop_back();
							hor_max = max(hor_max, temp.second);//水平的对应second
							hor_min = min(hor_min, temp.second);
							auto temp_x_mid = 50 * (temp.second + 4);
							auto temp_y_mid = 50 * (temp.first + 1) + 15;//print_or_erase_one用的是物理坐标值，而不是数组下标值，所以要算出中点
							print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//注意，这里的second是x，first是y，所以在对board取值和对x和y取值的时候不一样
							vanish_cnt++;
						}
						while (!v_for_vertical_storage.empty())
						{
							pair<int, int>temp = v_for_vertical_storage.back();
							v_for_vertical_storage.pop_back();
							ver_max = max(ver_max, temp.first);
							ver_min = min(ver_min, temp.first);///错了，一开始写成了first
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
						ms.play_sound("..\\Musics\\lightning音效.wav");
						vanish_cnt++;
						if (!is_the_progress_bar_filled(2000.0))
						{
							update_bonus();
							vanish_the_score();
							update_and_refresh_the_score(vanish_cnt, level, bonus);
							double base_level_score = 2000.0;
							update_and_refresh_the_progress_bar(present_score, base_level_score);
						}

						/* 对于下降部分，先保留垂直方向的三个，先把横向的两个给下降了，补齐；再下降垂直的，再补齐*/
						///横向的操作，分块
						{
							///下降部分1--横向下降
							auto now_hor_num = i;//纵向的序号
							while (now_hor_num >= 1)//不能>=0
							{
								for (int h = hor_min; h <= hor_max; h++)
								{
									if (h == j) continue;//如果在这三个水平坐标中，遇到了跟垂直方向相同的那个就跳过，其实就多了这一句，所以那一列就完全不理了
									auto temp_x_mid = 50 * (h + 4);//上面那个的横坐标（水平坐标）
									auto temp_y_mid_above = 50 * (now_hor_num)+15;//上面那个的纵坐标（竖直坐标）
									print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][h], false);//先把上面那个消掉，再在下面打印出来
									board[now_hor_num][h] = board[now_hor_num - 1][h];
									auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//现在这一个的横坐标（下面那个），纵坐标（x坐标）是一样的
									print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][h], true);
								}
								now_hor_num--;
							}

							///补齐部分1--横向补齐
							for (int u = hor_min; u <= hor_max; u++)//这个时候行已经变成0了
							{
								if (u == j) continue;
								auto num = (rand() % 8 + 200) % 7 + 1;
								auto temp_x_mid = 50 * (u + 4);//水平坐标
								auto temp_y_mid = 50 * (0 + 1) + 15;
								board[0][u] = num;
								print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
							}
						}

						///垂直的操作
						{
							///下降部分2--竖直下降
							auto now_ver_num = j;//横向的序号，这个是不会变的
							auto delta = ver_max - ver_min + 1;//最下面和最上面差了多少个
							auto ver_min_above_num = ver_min - 1;//这个是y坐标最小的上面那个，然后不断--就可以
							while (ver_min_above_num >= 0)
							{
								//x坐标不会变，就是now_x_mid
								auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
								print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//消去原来位置的图形 
								auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//这个就是应该下降到的位置的物理坐标了
								auto ver_min_below_num = ver_min_above_num + delta;//这个就是应该下降到的位置的二维数组的行坐标
								board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta是二位数组的横坐标（行）
								print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//画同样的图
								ver_min_above_num--;
							}

							///补齐部分2--竖直补齐
							for (int u = 0; u < delta; u++)//delta就是消失的个数，消失了多少补多少
							{
								auto num = (rand() % 8 + 200) % 7 + 1;
								auto temp_y_mid = 50 * (u + 1) + 15;///竖直坐标就是now_x_mid，所以不用算x，忘了+1
								board[u][now_ver_num] = num;
								print_or_erase_one(now_x_mid, temp_y_mid, num, true);
							}
						}
					}

					//2.只有水平可以消去，消去立即补齐
					else if (horizontal_cnt >= 2 && vertical_cnt < 2)
					{
						int hor_min = 1000, hor_max = -1;//用来记录横（或竖）的最大最小坐标，用来下降
						int vanish_cnt = 0;
						Sleep(300);
						while (!v_for_horizontal_storage.empty())
						{
							pair<int, int>temp = v_for_horizontal_storage.back();
							v_for_horizontal_storage.pop_back();
							hor_max = max(hor_max, temp.second);//水平的对应second
							hor_min = min(hor_min, temp.second);
							auto temp_x_mid = 50 * (temp.second + 4);
							auto temp_y_mid = 50 * (temp.first + 1) + 15;
							print_or_erase_one(temp_x_mid, temp_y_mid, board[temp.first][temp.second], false);//注意，这里的second是x，first是y，所以在对board取值和对x和y取值的时候不一样
							//board[temp.first][temp.second] = 0;
							vanish_cnt++;
						}
						hor_max = max(hor_max, j);
						hor_min = min(hor_min, j);
						print_or_erase_one(now_x_mid, now_y_mid, board[i][j], false);
						vanish_cnt++;
						if (vanish_cnt == 4)//只有4个
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("..\\Musics\\bomb音效.wav");
						}
						else if (vanish_cnt >= 5)//有可能就这样一行过去，5个就闪电
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("D:\\C++\\Bejewels\\Musics\\lightning音效.wav");
						}
						if (!is_the_progress_bar_filled(2000.0))
						{
							update_bonus();
							vanish_the_score();
							update_and_refresh_the_score(vanish_cnt, level, bonus);
							double base_level_score = 2000.0;
							update_and_refresh_the_progress_bar(present_score, base_level_score);
						}

						///下降部分
						auto now_hor_num = i;//纵向的序号，也就是消除的东西所在的那个行号
						while (now_hor_num >= 1)//不能>=0
						{
							for (int h = hor_min; h <= hor_max; h++)
							{
								auto temp_x_mid = 50 * (h + 4);//上面那个的横坐标（水平坐标）
								auto temp_y_mid_above = 50 * (now_hor_num)+15;//上面那个的纵坐标（竖直坐标）
								print_or_erase_one(temp_x_mid, temp_y_mid_above, board[now_hor_num - 1][h], false);//先把上面那个消掉，再在下面打印出来
								board[now_hor_num][h] = board[now_hor_num - 1][h];
								auto temp_y_mid_below = 50 * (now_hor_num + 1) + 15;//现在这一个的横坐标（下面那个），纵坐标（x坐标）是一样的
								print_or_erase_one(temp_x_mid, temp_y_mid_below, board[now_hor_num][h], true);
							}
							now_hor_num--;///这里--才对！
						}

						///填补部分
						for (int u = hor_min; u <= hor_max; u++)//这个时候行已经变成0了
						{
							auto num = (rand() % 8 + 200) % 7 + 1;
							auto temp_x_mid = 50 * (u + 4);//水平坐标
							auto temp_y_mid = 50 * (0 + 1) + 15;///忘了+1了
							board[0][u] = num;
							print_or_erase_one(temp_x_mid, temp_y_mid, num, true);
						}
					}

					//3.只有垂直可以消去
					else if (vertical_cnt >= 2 && horizontal_cnt < 2)
					{
						int ver_min = 1000, ver_max = -1;//用来记录横（或竖）的最大最小坐标，用来下降
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
						if (vanish_cnt == 4)//只有4个
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("C:\\Users\\T_Heap\\source\\repos\\宝石迷阵\\宝石迷阵3音乐\\bomb音效.wav");
						}
						else if (vanish_cnt >= 5)//有可能就这样一行过去，5个就闪电
						{
							ms.stop_sound();
							ms.close_sound();
							ms.play_sound("C:\\Users\\T_Heap\\source\\repos\\宝石迷阵\\宝石迷阵3音乐\\lightning音效.wav");
						}
						if (!is_the_progress_bar_filled(2000.0))
						{
							update_bonus();
							vanish_the_score();
							update_and_refresh_the_score(vanish_cnt, level, bonus);
							double base_level_score = 2000.0;
							update_and_refresh_the_progress_bar(present_score, base_level_score);
						}

						///下降部分
						auto now_ver_num = j;//纵向的序号
						auto delta = ver_max - ver_min + 1;//最下面和最上面差了多少个
						auto ver_min_above_num = ver_min - 1;//这个是y坐标最小的上面那个，然后不断--就可以
						while (ver_min_above_num >= 0)
						{
							//x坐标不会变，就是now_x_mid
							auto temp_y_mid_above = 50 * (ver_min_above_num + 1) + 15;
							print_or_erase_one(now_x_mid, temp_y_mid_above, board[ver_min_above_num][now_ver_num], false);//消去原来位置的图形 
							auto temp_y_mid_below = temp_y_mid_above + 50 * delta;//这个就是应该下降到的位置的物理坐标
							auto ver_min_below_num = ver_min_above_num + delta;//这个就是应该下降到的位置的二维数组的行坐标
							board[ver_min_below_num][now_ver_num] = board[ver_min_above_num][now_ver_num];//ver_min_above_num + delta是二位数组的横坐标（行）
							print_or_erase_one(now_x_mid, temp_y_mid_below, board[ver_min_below_num][now_ver_num], true);//画同样的图
							ver_min_above_num--;
						}

						///填补部分
						for (int u = 0; u < delta; u++)//delta就是消失的个数，消失了多少补多少
						{
							auto num = (rand() % 8 + 200) % 7 + 1;
							auto temp_y_mid = 50 * (u + 1) + 15;//竖直坐标就是now_x_mid，所以不用算x，忘了j+1
							board[u][now_ver_num] = num;
							print_or_erase_one(now_x_mid, temp_y_mid, num, true);
						}
					}
				}
			}
		}
		if (confliction == false) return false;
		return true;//证明还是有冲突的，要重新扫描
	}
	void check_for_confliction(music_and_sound_play& ms)
	{
		while (fix_the_board_after_vanish(ms));//如果一直有，就一直搞
		set_bonus();//必须要bonus归0，搞定所有冲突之后才能归0
	}
	void abort_the_game()//显示无法移动
	{
		COLORREF textcolor = RGB(0, 238, 0);
		settextstyle(90, 40, _T("Courier New"));
		settextcolor(textcolor);
		setbkmode(TRANSPARENT);
		TCHAR con[] = _T("无 法 移 动");
		outtextxy(90, 230, con);//W:90-530,H:230-320
		Sleep(1000);
	}
	void game_over()//打印页面并退出
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
		TCHAR over[] = _T("游戏结束");
		outtextxy(150, 80, over);//W:150-470,H:80-170
		COLORREF textcolor = RGB(153, 50, 204);
		settextstyle(50, 25, _T("Courier New"));
		settextcolor(textcolor);
		TCHAR lev_string[10] = _T("Level:");
		TCHAR lev_num[30];
		TCHAR score_string[] = _T("Score:");
		TCHAR score_num[30];
		_stprintf_s(lev_num, 30, _T("%.0lf"), level);
		_stprintf_s(score_num, 30, _T("%.0lf"), tot_score);//这里是tot_score，注意
		outtextxy(220, 200, lev_string);//W:220-370,H:200-250
		outtextxy(370, 200, lev_num);//W:370-...,H:200-250
		outtextxy(180, 260, score_string);//W:180-330,H:260-310
		outtextxy(340, 260, score_num);//这个打印的是总分数，因为每一关都要重新打印这个分数
		settextstyle(30, 15, _T("Courier New"));
		TCHAR go_back[] = _T("------点击任意位置退出------");
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
	{//menu就是暂停的那里
		if (15 <= x && x <= 75 && 370 <= y && y <= 395) return true;
		return false;
	}
	int is_in_the_pause_rect(int x, int y)
	{
		if (245 <= x && x <= 395 && 330 <= y && y <= 360) return 1;//说明在"返回主菜单"的框内
		if (260 <= x && x <= 380 && 290 <= y && y <= 320) return 2;//说明在"继续游戏"的框内
		return 0;
	}
	void reload_the_board(music_and_sound_play& ms)//如果游戏暂停后重新开始，需要先清屏，再继续播放音乐，再重新打印图像
	{
		ms.resume_music();
		//cleardevice();///记得清屏
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
		setlinestyle(PS_DASHDOT | PS_JOIN_ROUND, 6);//6像素宽，连接处为圆角的点划线
		roundrect(180, 30, 600, 450, 10, 10);//打印框
		for (int i = 0; i < 8; i++)//打印图形
		{
			for (int j = 0; j < 8; j++)
			{
				int num = this->board[i][j];//i和j在这里跟上面的是调过来的
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
		init_the_score();//打印分数，这个函数虽然是init，但是效果一样
		print_the_progress_bar_frame();//打印进度条
		update_and_refresh_the_progress_bar(present_score, base_level_score);
		print_the_buttons();
		EndBatchDraw();
	}
	int game_pause(music_and_sound_play& ms)//返回1代表继续游戏，返回2代表返回主菜单
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
		TCHAR con[] = _T("继续游戏");
		TCHAR return_main_menu[] = _T("返回主菜单");
		outtextxy(260, 290, con);//W:260-380,H:290-320
		outtextxy(245, 330, return_main_menu);//W:245-395,H:330-360
		MOUSEMSG msg;
		while (true)
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (is_in_the_pause_rect(msg.x, msg.y) == 1) return 1;//返回主菜单
				if (is_in_the_pause_rect(msg.x, msg.y) == 2)//继续游戏
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
	void reset_the_board(music_and_sound_play& ms)//重新开始
	{
		level = 1.0;//level不能是0
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
				pair<int, int>temp = *jeweled_tips.begin();//set.begin()是个迭代器
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
		print_the_board(ms);//分数和进度条都在里面了
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
				if (click_flag)///click_flag==true说明已经有东西被选中了，改了
				{
					print_or_erase_frame(last_x, last_y, false);
					reload_the_board(ms);
					if (is_in_the_jeweled_rect(msg.x, msg.y) && is_nearby(last_x, last_y, msg.x, msg.y))//情况4 和 情况2
					{
						Sleep(300);
						swap_flag = swap_jeweled(msg.x, msg.y, last_x, last_y);//swap_flag变成true
						bool Did_present_disappear = jeweled_vanish(msg.x, msg.y, ms);
						bool Did_last_disappear = jeweled_vanish(last_x, last_y, ms);
						if (Did_present_disappear || Did_last_disappear)
						{
							check_for_confliction(ms);///脑子有问题，怎么可能两个都有叹号，改了！
							reload_the_board(ms);
						}
						if (!Did_present_disappear && !Did_last_disappear)//先换谁都行，并且只有两个都失败了，才重新互换
						{
							Sleep(300);
							swap_jeweled(msg.x, msg.y, last_x, last_y);
							reload_the_board(ms);
						}
					}
					click_flag = false;///这时候相当于情况4和情况2结束了，回到情况1，如果只放在里面，那么2之后就不会归0
				}
				if (is_in_the_jeweled_rect(msg.x, msg.y) && !swap_flag)//flag==false说明当前没有框被选中，所以要进行框取，这里可以兼顾情况1和情况3，因为swap_flag每次都置0
				{
					click_flag = print_or_erase_frame(msg.x, msg.y, true);//click_flag会变成true
				}
				if (is_in_the_menu_rect(msg.x, msg.y))
				{
					int ret = game_pause(ms);
					if (ret == 1) return 1;//1代表返回主菜单
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
				last_x = msg.x;//记录当前坐标，在下一次中使用
				last_y = msg.y;
			}
			if (!scan_the_board_for_availability())//经典模式 输了
			{
				abort_the_game();
				game_over();
				jeweled_tips.clear();
				return 1;//表示强行返回主菜单
			}
			to_next_level = is_the_progress_bar_filled(base_level_score);
			if (to_next_level == true) return 2;
			to_next_level = false;//防止意外
		}
	}
	int game_cycle_outter(music_and_sound_play& ms)//设置成引用是为了外面也能监视到情况
	{
		int ret = -1;
		ms.stop_music();
		ms.close_music();
		ms.play_music("..\\Musics\\经典.mp3");
		while (true)
		{
			ret = game_cycle_inner(ms);
			if (ret == 1) return 1;//如果是选择了返回，就返回主界面，是2就不用管
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
	double present_score;				//present_score是当前关卡的分数，要清零
	double tot_score;					//tot_score是总分数，不要清零
	set<pair<int, int>>jeweled_tips;	//储存提示的坐标，记得清零，用set是为了不重复
};