#include <stdio.h>
#include <windows.h>
using namespace std;

char q[110]={" ����        ��        �����    �����     �����   ��      ��  �����  �����   \n"};
char w[110]={"��             ���      ��  ��  ��   ��          ��      ��   ��    ��   ��        ��     �� \n"};
char e[110]={"��            ��  ��     ��  ��  ��   �����    ��      ��    ��  ��    �����  �����  \n"};
char r[110]={"��    ���   �����    ��  ��  ��   ��          ��      ��     ���     ��        ��     �� \n"};
char t[110]={"  ���  ��  ��      ��   ��  ��  ��   �����     �����       ��      �����  ��      ��\n"};

void PrintGO()
{
	for(int i=0;i<110;i++){ 
		printf("%c",q[i]);
	}
	for(int i=0;i<110;i++){
		printf("%c",w[i]);
	}
	for(int i=0;i<110;i++){
		printf("%c",e[i]);
	}
	for(int i=0;i<110;i++){
		printf("%c",r[i]);
	}
	for(int i=0;i<110;i++){
		printf("%c",t[i]);
	}
}
int main()
{	
	printf("\t\t");
	PrintGO();
}
