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
		
		static void gotoxy(short m_x, short m_y) 		//ConsloeSet::gotoxy �������� ���� �ֵ��� static �Լ��� ���� 
		{//Ŀ���̵��Լ�
        COORD Cur;
        Cur.X = m_x;
        Cur.Y = m_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    	}
};
