#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#include"audio_control.hpp"
#pragma comment(lib,"winmm.lib")	//�����������������ͷ�ļ�
#pragma comment(lib,"MSIMG32.LIB")	//���øÿ����ʹ��AlphaBlend�������ú���������ʾ͸�����͸�����ص�λͼ
using namespace std;

class music_and_sound_play :public audiocontrol
{
public:
	music_and_sound_play() = default;
	~music_and_sound_play() = default;

	void play_music(const char music_filepath[])
	{
		/*
		MCIERROR mciSendString(
			LPCTSTR lpszCommand, ������	//MCI�����ַ���
			LPTSTR��lpszReturnString,��	//��ŷ�����Ϣ�Ļ�����
			UINT����cchReturn, ��������	//�������ĳ���
			HANDLE��hwndCallback ������	//�ص����ڵľ����һ��ΪNULL
		);							//���ɹ��򷵻�0�����򷵻ش����롣
		*/
		char command[100] = "open ";
		char musicname[] = " alias music";
		strcat_s(command, music_filepath);
		strcat_s(command, musicname);
		wchar_t cmd[100];
		charTowchar(command, cmd, strlen(command) * 2);
		MCIERROR Err_loading, Err_playing;
		Err_loading = mciSendString(cmd, NULL, 0, NULL);//��������
		if (Err_loading != 0)//�Լ��غͲ��ż�����
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_loading);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			//����һ���򣬱����ǵ�����λ�ã������ǵڶ���λ�ã����ĸ�λ����Ĭ�ϲ���
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}

		Err_playing = mciSendString(TEXT("play music repeat"), NULL, 0, NULL);	//��������
		if (Err_playing != 0)
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_playing);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}
	}
	void stop_music()
	{
		mciSendString(TEXT("stop music"), NULL, 0, NULL);						//ֹͣ����
	}
	void close_music()
	{
		mciSendString(TEXT("close music"), NULL, 0, NULL);						//�ر�����
	}
	void pause_music()
	{
		mciSendString(TEXT("pause music"), NULL, 0, NULL);						//��ͣ����
	}
	void resume_music()
	{
		MCIERROR Err_resuming;
		Err_resuming = mciSendString(TEXT("resume music"), NULL, 0, NULL);		//��������
		if (Err_resuming != 0)
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_resuming);
			//_stprintf_s(Err_msg_con,_T("%d"), sizeof(Err_msg_con) + 5);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}
	}
	void play_sound(const char sound_filepath[])//1�����磬2�Ǳ�ը
	{
		char command[100] = "open ";
		char soundname[] = " alias sound";
		strcat_s(command, sound_filepath);
		strcat_s(command, soundname);
		wchar_t cmd[100];
		charTowchar(command, cmd, strlen(command) * 2);
		MCIERROR Err_loading, Err_playing;
		Err_loading = mciSendString(cmd, NULL, 0, NULL);						//��������
		if (Err_loading != 0)//�Լ��غͲ��ż�����
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_loading);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			//����һ���򣬱����ǵ�����λ�ã������ǵڶ���λ�ã����ĸ�λ����Ĭ�ϲ���
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}
		char volume_cmd[100];
		wchar_t volume_wcmd[100];
		sprintf_s(volume_cmd, 100, "setaudio sound volume to %d", present_sound_volume);
		charTowchar(volume_cmd, volume_wcmd, 200);
		mciSendString(volume_wcmd, NULL, 0, NULL);
		Err_playing = mciSendString(_T("play sound"), NULL, 0, NULL);	//��������
		if (Err_playing != 0)
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_playing);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}
	}
	void pause_sound()
	{
		mciSendString(_T("pause sound1"), NULL, 0, NULL);						//��ͣ����
		mciSendString(_T("pause sound2"), NULL, 0, NULL);
	}
	void stop_sound()
	{
		mciSendString(TEXT("stop sound"), NULL, 0, NULL);						//ֹͣ����
	}
	void close_sound()
	{
		mciSendString(TEXT("close sound"), NULL, 0, NULL);						//�ر�����
	}
	void resume_sound()
	{
		MCIERROR Err_resuming1, Err_resuming2;
		Err_resuming1 = mciSendString(_T("resume sound1"), NULL, 0, NULL);		//��������
		if (Err_resuming1 != 0)
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_resuming1);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}
		Err_resuming2 = mciSendString(_T("resume sound2"), NULL, 0, NULL);		//��������
		if (Err_resuming2 != 0)
		{
			wchar_t Err_msg_title[] = L"Error: �������ּ�������ʧ��";
			wchar_t Err_msg_con[] = L"�������ּ�������ʧ�ܣ������޷���ȷ���У�����ȷ��������δ����������ռ�ò���������";
			wchar_t Err_msg_num_title[] = L"������룺";
			wchar_t Err_msg_num_con[5] = {};
			wsprintf(Err_msg_num_con, _T("%d"), Err_resuming2);
			MessageBox(NULL, Err_msg_con, Err_msg_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			MessageBox(NULL, Err_msg_num_con, Err_msg_num_title, MB_OKCANCEL | MB_DEFBUTTON1 | MB_ICONERROR);
			exit(0);
		}
	}
};
