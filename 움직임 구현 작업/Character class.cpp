//Control Character()�Լ��� �����ϸ� �� 
class Character
{    
    private : 
		int x;		//ĳ���Ͱ� ��µ� x��ǥ
    	int y;		//ĳ���Ͱ� ��µ� y��ǥ
    	int size_x;		//ĳ���͸� ����� 3*3ũ��
		int size_y;
    	char figure[10];	//ĳ���� ����� �迭 (3*3ũ�� ��µ� ����)
    	char name[8];		//ĳ���� ���� �� �̸� 
    	bool direction;		//true=�����̵� , false=�����̵� 
    
	    float t_jump;		//�߷� ������ ���� 
	    
	public :
		Character()		//�����ڷ� �ʱⰪ ���� 
		{
			x = MAP_X_MAX / 2 + 1;
			y = MAP_Y_MAX / 2 + 1;
			size_x = 3;
			size_y = 3;
			
			//�ʱ� ĳ���� ��� (3*3) 
			figure[0] = ' ';
			figure[1] = '0';
			figure[2] = ' ';
			figure[3] = '(';
			figure[4] = '|';
			figure[5] = ')';
			figure[6] = '_';
			figure[7] = '^';
			figure[8] = '_';
			figure[9] = '\0';
			
			name[0] = 'M';
			name[1] = 'r';
			name[2] = '.';
			name[3] = 'S';
			name[4] = 'o';
			name[5] = 'n';
			name[6] = 'g';
			name[7] = '\0';
			direction = TRUE;
			t_jump = 2;
		    leg_m = 1;				
		    t_leg = 0;
		}
		void ControlCharacter()
		{
			bool move = FALSE;
			 
			if (GetAsyncKeyState(VK_LEFT) && x > 1) 
			{											 
				x -= 1;	
				direction = FALSE;
				move = TRUE;
			}
			
			if (GetAsyncKeyState(VK_RIGHT) && x < MAP_X_MAX - 2) 
			{
				x += 1;
				direction = TRUE;
				move = TRUE;
			}
			
		}
		
		//private������ �ִ� ������ ����
		int GetX(){return x;}
		int GetY(){return y;}
		int GetSizeX(){return size_x;}
		int GetSizeY(){return size_y;}
		char* Getfigure(){return figure;}
		char* Getname(){return name;}

};
		

