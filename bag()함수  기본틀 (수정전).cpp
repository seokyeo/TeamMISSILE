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
				strup();  // �ֹ����� ���� ���ݷ� ��ȭ        ���߿� �ؿ� �Լ� ��������. 
				
		}
		
	} 
}
