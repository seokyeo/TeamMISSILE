#include <iostream>
#include <windows.h>

using namespace std;

char a[111]={"   ���������            ��                ���      ��           ��������         ���        ��\n"};
char b[111]={"                 ��          ��  ��            ��    ��    ��           ��          ��     �������    ��\n"};
char c[111]={"                 ��        ��      ��        ��        ��  ��           ��          ��       ��    ��      ��\n"};
char d[111]={"                 ��      ��          ��      ��        ��  ��           ��          ��       ��    ��  ����\n"};
char e[111]={"       ��    ��                                ��    ��    ��           ��������         ���        ��\n"};
char f[111]={"       ��    ��        ����������        ���      ��                 ��                   ������\n"};
char g[111]={"       ��    ��                ��                          ��                 ��                   ��      ��\n"};
char h[111]={" �����������          ��          ����������         ����������           ������\n"};

void PrintLogo()
{

	cout<<"\n\n\n ";
		
	for(int i=0;i<111;i++){ 
		cout<<a[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<b[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<c[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<d[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<e[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<f[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<g[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<h[i];
		Sleep(5);
	}
}
int main()
{
	PrintLogo();
}
