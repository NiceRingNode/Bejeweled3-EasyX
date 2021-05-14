#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")	//包含播放声音组件的头文件
#pragma comment(lib,"MSIMG32.LIB")	//引用该库才能使用AlphaBlend函数，该函数用来显示透明或半透明像素的位图
using namespace std;

class audiocontrol
{
public:
	audiocontrol() = default;
	virtual ~audiocontrol() = default;//不必作为抽象类，因为没有理由

	void charTowchar(const char* chr, wchar_t* wchar, int size)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, chr, strlen(chr) + 1, wchar, size / sizeof(wchar[0]));
		wchar[len] = '\0';
	}
	/*
	int MultiByteToWideChar( 　　
		UINT CodePage, 　　
		DWORD dwFlags, 　　
		LPCSTR lpMultiByteStr, 　　
		int cchMultiByte, 　　
		LPWSTR lpWideCharStr, 　　
		int cchWideChar 　　
	); 　　
	*/
	void wchartochar(wchar_t* wchar, char* chr, int size)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, wchar, -1, chr, strlen(chr) + 1, NULL, FALSE);
		chr[len] = '\0';
	}
	void adjust_music_volume(int step)//我们直接用music就可以了，不要什么shortpath，0-1000
	{//step是增加的音量，mode是加或者减，1加2减
		wchar_t volume_str[100];
		char volume_str_ANSI[100];
		int volume_int = 0;
		mciSendString(_T("status music volume"), volume_str, sizeof(volume_str), NULL);	//获取音量到volume串中
		wchartochar(volume_str, volume_str_ANSI, 200);
		volume_int = atoi(volume_str_ANSI);
		/*
		减的时候：可能会小于0
		加的时候：可能会大于1000
		*/
		int new_volume_int = 0;
		new_volume_int = volume_int - step;
		if (step > 0 && new_volume_int < 0)//step>0说明是要减的
			new_volume_int = 1;
		if (step < 0 && new_volume_int > 1000)//step<0说明是要加的
			new_volume_int = 999;
		char cmd[100];
		wchar_t wcmd[100];
		sprintf_s(cmd, 100, "setaudio music volume to %d", new_volume_int);//加减一体
		charTowchar(cmd, wcmd, 200);
		mciSendString(wcmd, NULL, 0, NULL);
		present_music_volume = new_volume_int;
	}
	void adjust_sound_volume(int step)	//我们不需要实时改变音量，只要保存就好
	{									//step是增加的音量
		int new_sound_volume = 0;
		new_sound_volume = present_sound_volume -= step;
		if (step > 0 && new_sound_volume < 0)//step>0说明是要减的
			new_sound_volume = 1;
		if (step < 0 && new_sound_volume > 1000)//step<0说明是要加的
			new_sound_volume = 999;
		present_sound_volume = new_sound_volume;
	}
	static int present_music_volume;
	static int present_sound_volume;
};