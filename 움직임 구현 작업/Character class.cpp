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
		Character();	//private ������ �ʱ�ȭ ���� 
		void ControlCharacter();
		
		//private������ �ִ� ������ ����
		int GetX(){return x;}
		int GetY(){return y;}
		int GetSizeX(){return size_x;}
		int GetSizeY(){return size_y;}
		char* Getfigure(){return figure;}
		char* Getname(){return name;}

};
		

