void attack(){
	int num;
	cout << "���� ������ �ұ��?" << endl;
	cin >> num;
	switch(num){
		case 1:
			cout << "�⺻ ����(������: 5) " << endl;
			basic attack();
			break; 
		case 2:
			cout << "�⺻ ��ų1(������: 10)" << endl;
			skill1(); 
			break;
		case 3:
		    cout << "�⺻ ��ų2 (������: 15)"  << endl; 
		    skill2();
		    break;
	}
}

void basic attack()                        //������ ������ ����â���� �̵� ���߿�  
{
	Monster_Hp = Monster_Hp - 5;
}

void skill1()                             //������ ������ ����â���� �̵� ���߿� 
{ 
	Monster_Hp = Monster_Hp - 10;
}

void skill2()                              //������ ������ ����â���� �̵� ���߿� 
{
	Monster_Hp = Monster_Hp - 15;
}
