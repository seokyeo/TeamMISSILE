#include <windows.h>	//�� ������� �ʿ�! 

class ConsoleSet		//�ܼ�â ���� Ŭ����.
{
	public : 
		ConsoleSet() //�����ڸ� ���� �ܼ�â ���� 
		{			
			system("mode con:cols=130 lines=32");	//�ܼ�â�� ���� ���� ũ�⸦ �ʰ� �����ϰ� ���� 
			system("title Team Missile");
				
			HANDLE hConsole;
		    CONSOLE_CURSOR_INFO ConsoleCursor;
		    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			    
		    ConsoleCursor.bVisible = 0;		//Ŀ�� �Ⱥ��̰� 
		    ConsoleCursor.dwSize = 1;		//Ŀ�� ����� ũ�� 1�� 
		    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
		}
		
		static void gotoxy(short _x, short _y) 		//ConsloeSet::gotoxy �������� ���� �ֵ��� static �Լ��� ����.  _x,_y ��ǥ�� Ŀ�� �̵� 
		{
        COORD Cur;
        Cur.X = _x;
        Cur.Y = _y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    	}
};
