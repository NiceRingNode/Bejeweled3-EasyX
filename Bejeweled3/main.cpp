#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include"start_page.hpp"
#include"audio_control.hpp"
#include"music_and_sound.hpp"
#include"option_list.hpp"
#include"exit_control.hpp"
#include"bejewled_board.hpp"
using namespace std;

int audiocontrol::present_music_volume = 500;
int audiocontrol::present_sound_volume = 500;//静态成员类外初始化
int main()
{
	initgraph(640, 560);
	cleardevice();
	srand((unsigned int)time(NULL));
	option all_options(357, 357);
	music_and_sound_play music_sound;
	while (true)
	{
		music_sound.stop_music();
		music_sound.close_music();
		music_sound.play_music("..\\Musics\\主菜单.mp3");
		start_page start;
		start.init_the_start_page();
		int ret = 0;
		ret = start.jump_to_the_next_page();
		if (ret == 1)//进入选项，控制音量等
		{
			music_sound.stop_music();
			music_sound.close_music();
			music_sound.play_music("..\\Musics\\询问2.mp3");
			all_options.manipulate_all_options();
		}
		else if (ret == 2)//进入游戏主体
		{
			int ret_for_game = 0;
			bejewled_board game(1.0, 0, 0, 1);
			ret_for_game = game.game_cycle_outter(music_sound);
			if (ret_for_game == 1) continue;
		}
		else if (ret == 5)
		{
			exit_out exit_all;
			exit_all.print_is_or_not();
			int ret = exit_all.exit_or_not();
			if (ret == 1) exit(0);
			else if (ret == 2) continue;
		}
	}
	_getch();
	closegraph();
	return 0;
}