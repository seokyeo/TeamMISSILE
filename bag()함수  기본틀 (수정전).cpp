void bag(){
	int num ;
	cout << " ������ ���ðڽ��ϱ�? " << endl;     // ����'
    cout << " 1. ��  " << endl;
	cout << " 2. �ƴϿ� " << endl;
	cin >> num;
	if(num = 1){
		cout << " �ֲ����ðڽ��ϱ�? " << endl;
		cout << " 1. ��� " << endl;
		cout << " 2. �ֹ��� " << endl; 
		switch(num){
			case 1:
				heal();    // ����� �԰� �Ǹ� ü�� ��       ���߿� �ؿ� �� �Լ� ��������. 
			case 2: 
				int strup = 10;  // �ֹ����� ���� ���ݷ� ��ȭ        ���߿� �ؿ� �Լ� ��������. 
				cout << "��� ���ݰ� ��ų�� ���ݷ� 10�� �پ����ϴ�." << endl;
		}
		
	} 
}

void heal()             // ���߿� ������ ������ ����â�� �Űܾ���. 
{
	int hp_up = 10;
	Song_ hp = Song_ hp +10;
	
}

