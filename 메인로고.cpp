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
	
	printf("\n\n\n ");
		
	for(int i=0;i<111;i++){ 
		printf("%c",a[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",b[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",c[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",d[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",e[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",f[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",g[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",h[i]);
		Sleep(5);
	}
}
int main()
{
	PrintLogo();
}
