class Map		//�ڳ��߿� �� Ŭ���� ����ؼ� �߰������� �ٸ� �� ����� �ֵ��� ������ ���� 
{	
	private :
		char ground[MAP_X_MAX];				//���� ǥ���� ������ �迭 	
		char mapData[MAP_X_MAX * MAP_Y_MAX];	 //1���� �迭�� ����ũ��MAP_X_MAX * ����ũ�� MAP_Y_MAX�� ǥ��. mapData�� ���������� ��������ν� ���� ������ ����. 
												 //������ : �ܼ�â ũ�⸦ �����ϰ� �迭�� ũ��� �����ϰ� �ؾ߸� ����� �� ������� ���.
	public :
		Map()
		{	
			fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);	//�����ڷ� mapData�迭�� ����' '���� �ʱ�ȭ 
			fillArray(ground, '=', MAP_X_MAX);					//�����ڷ� ground�迭�� '='�� �ʱ�ȭ 
		}
		
		void fillArray(char arr[], char c, int max_value) 		//�迭�� str[0]~str[max_value]�� ���� c�� ä��� �Լ� 
		{	
			for (int i = 0; i < max_value; i++)
				arr[i] = c;
		}
		
		void EditMap(int x, int y, char str) 					//�ܼ�â�� x,y��ǥ�� str�� �����ϴ� �Լ�.
		{
			if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)	 
			mapData[(y - 1) * MAP_X_MAX + x - 1] = str;				//(y-1)*MAP_X_MAX�� �ϸ� �ܼ�â�� y��° ���� ��Ÿ�� �� ����. �ű⿡ x-1�� ���ϸ� (x,y)�� ��Ÿ��. 
																	//�ܼ�â�� (1,1)��ǥ = �ܼ�â�� �����ֻ�� = mapData[0]�� �ǹ�
		}															//ex)  EditMap(1,1,'@')�� �ϸ� �ܼ�â �����ֻ�ܿ� @�� �׸�.
		
		void MakeGround() 		//�� �迭 ground�� mapData�� �ݿ������ν� �� �׸���
		{	
			Drawfigure(1, 22, MAP_X_MAX, 1, ground);
		}
		
		void Drawfigure(int x, int y, int size_x, int size_y, char figure[])	//EditMap�Լ��� for�� ó���ؼ� x,y��ǥ�� ������ �ش� ��ǥ�� �������� size_x,size_yũ���� ���� ����
		{
			for (int i = 0; i < size_y; i++)		//3�� ���� ���� 
			{
				for (int j = 0; j < size_x; j++)		//3�� ���� ����
					EditMap(x + j, y + i, figure[i * size_x + j]);		//i*size_x�� 1��,2��,3���� ǥ��. j�� ���� ǥ��.
			}
		}
		
		void printMap()
		{
			cout<<mapData;		//�� ���		
		}
		
		char* GetMapData(){return mapData;}		//private������ �ִ� mapData[]�� �ּ� ���� 
	
};
