#include <stdio.h>
#include <windows.h>
using namespace std;

char q[110]={"  ����        ��        �����    �����     �����   ��      ��  �����  �����  \n"};
char w[110]={"��             ���      ��  ��  ��   ��          ��      ��   ��    ��   ��        ��     �� \n"};
char e[110]={"��            ��  ��     ��  ��  ��   �����    ��      ��    ��  ��    �����  �����  \n"};
char r[110]={"��    ���   �����    ��  ��  ��   ��          ��      ��     ���     ��        ��     �� \n"};
char t[110]={"  ���  ��  ��      ��   ��  ��  ��   �����     �����       ��      �����  ��      ��\n"};

int main()
{	
	printf("\n");
	for(int i=0;i<110;i++){ 
		printf("%c",q[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",w[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",e[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",r[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",t[i]);
		Sleep(5);
	}

}
