void attack(){
	int num;
	cout << "���� ������ �ұ��?" << endl;
	cin >> num;
	switch(num){
		case 1:
			cout << "�⺻ ����(������: 5) " << endl;
			Monster_Hp = Monster_Hp - 5;
			break; 
		case 2:
			cout << "�⺻ ��ų1(������: 10)" << endl;
			Monster_Hp = Monster_Hp - 10;
			break;
		case 3:
		    cout << "�⺻ ��ų2 (������: 15)"  << endl; 
		    Monster_Hp = Monster_Hp - 15;
		    break;
	}
}
