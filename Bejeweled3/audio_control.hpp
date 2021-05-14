#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")	//�����������������ͷ�ļ�
#pragma comment(lib,"MSIMG32.LIB")	//���øÿ����ʹ��AlphaBlend�������ú���������ʾ͸�����͸�����ص�λͼ
using namespace std;

class audiocontrol
{
public:
	audiocontrol() = default;
	virtual ~audiocontrol() = default;//������Ϊ�����࣬��Ϊû������

	void charTowchar(const char* chr, wchar_t* wchar, int size)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, chr, strlen(chr) + 1, wchar, size / sizeof(wchar[0]));
		wchar[len] = '\0';
	}
	/*
	int MultiByteToWideChar( ����
		UINT CodePage, ����
		DWORD dwFlags, ����
		LPCSTR lpMultiByteStr, ����
		int cchMultiByte, ����
		LPWSTR lpWideCharStr, ����
		int cchWideChar ����
	); ����
	*/
	void wchartochar(wchar_t* wchar, char* chr, int size)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, wchar, -1, chr, strlen(chr) + 1, NULL, FALSE);
		chr[len] = '\0';
	}
	void adjust_music_volume(int step)//����ֱ����music�Ϳ����ˣ���Ҫʲôshortpath��0-1000
	{//step�����ӵ�������mode�Ǽӻ��߼���1��2��
		wchar_t volume_str[100];
		char volume_str_ANSI[100];
		int volume_int = 0;
		mciSendString(_T("status music volume"), volume_str, sizeof(volume_str), NULL);	//��ȡ������volume����
		wchartochar(volume_str, volume_str_ANSI, 200);
		volume_int = atoi(volume_str_ANSI);
		/*
		����ʱ�򣺿��ܻ�С��0
		�ӵ�ʱ�򣺿��ܻ����1000
		*/
		int new_volume_int = 0;
		new_volume_int = volume_int - step;
		if (step > 0 && new_volume_int < 0)//step>0˵����Ҫ����
			new_volume_int = 1;
		if (step < 0 && new_volume_int > 1000)//step<0˵����Ҫ�ӵ�
			new_volume_int = 999;
		char cmd[100];
		wchar_t wcmd[100];
		sprintf_s(cmd, 100, "setaudio music volume to %d", new_volume_int);//�Ӽ�һ��
		charTowchar(cmd, wcmd, 200);
		mciSendString(wcmd, NULL, 0, NULL);
		present_music_volume = new_volume_int;
	}
	void adjust_sound_volume(int step)	//���ǲ���Ҫʵʱ�ı�������ֻҪ����ͺ�
	{									//step�����ӵ�����
		int new_sound_volume = 0;
		new_sound_volume = present_sound_volume -= step;
		if (step > 0 && new_sound_volume < 0)//step>0˵����Ҫ����
			new_sound_volume = 1;
		if (step < 0 && new_sound_volume > 1000)//step<0˵����Ҫ�ӵ�
			new_sound_volume = 999;
		present_sound_volume = new_sound_volume;
	}
	static int present_music_volume;
	static int present_sound_volume;
};