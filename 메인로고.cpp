#include <iostream>
#include <math.h>
#include <ctime>
#include <windows.h>
using namespace std;
class Logo{
	public:
		void PrintLogo(char listN[]);
		
	private:
		char a[111]={"   ���������            ��                ���      ��           ��������         ���        ��\n"};
		char b[111]={"                 ��          ��  ��            ��    ��    ��           ��          ��     �������    ��\n"};
		char c[111]={"                 ��        ��      ��        ��        ��  ��           ��          ��       ��    ��      ��\n"};
		char d[111]={"                 ��      ��          ��      ��        ��  ��           ��          ��       ��    ��  ����\n"};
		char e[111]={"       ��    ��                                ��    ��    ��           ��������         ���        ��\n"};
		char f[111]={"       ��    ��        ����������        ���      ��                 ��                   ������\n"};
		char g[111]={"       ��    ��                ��                          ��                 ��                   ��      ��\n"};
		char h[111]={" �����������          ��          ����������         ����������           ������\n"};
};
void PrintLogo(char listN[])
{
	for(int i=0;i<111;i++){
		cout<<listN[i];
		Sleep(10);
	}
}
int main()
{
	system("mode con:cols=130 lines=32");
	
	cout<<"   ���������            ��                ���      ��           ��������         ���        ��\n";Sleep(500);
	cout<<"                 ��          ��  ��            ��    ��    ��           ��          ��     �������    ��\n";Sleep(500);
	cout<<"                 ��        ��      ��        ��        ��  ��           ��          ��       ��    ��      ��\n";Sleep(500);
	cout<<"                 ��      ��          ��      ��        ��  ��           ��          ��       ��    ��  ����\n";Sleep(500);
	cout<<"       ��    ��                                ��    ��    ��           ��������         ���        ��\n";Sleep(500);
	cout<<"       ��    ��        ����������        ���      ��                 ��                   ������\n";Sleep(500);
	cout<<"       ��    ��                ��                          ��                 ��                   ��      ��\n";Sleep(500);
	cout<<" �����������          ��          ����������         ����������           ������\n";Sleep(500);
	
	cout<<"\n\n\n";
	
	char a[]={"   ���������            ��                ���      ��           ��������         ���        ��\n"};
	char b[]={"                 ��          ��  ��            ��    ��    ��           ��          ��     �������    ��\n"};
	char c[]={"                 ��        ��      ��        ��        ��  ��           ��          ��       ��    ��      ��\n"};
	char d[]={"                 ��      ��          ��      ��        ��  ��           ��          ��       ��    ��  ����\n"};
	char e[]={"       ��    ��                                ��    ��    ��           ��������         ���        ��\n"};
	char f[]={"       ��    ��        ����������        ���      ��                 ��                   ������\n"};
	char g[]={"       ��    ��                ��                          ��                 ��                   ��      ��\n"};
	char h[]={" �����������          ��          ����������         ����������           ������\n"};
	
	for(int i=0;i<111;i++){
		cout<<a[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<b[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<c[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<d[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<e[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<f[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<g[i];
		Sleep(10);
	}
	for(int i=0;i<111;i++){
		cout<<h[i];
		Sleep(10);
	}
	PrintLogo(char a[]);
}
