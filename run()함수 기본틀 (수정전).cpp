void run(){
	int num; 
	int num_2;
	cout << "�������ðڽ��ϱ�? " << endl;      
	cout << "1. �� �������ڽ��ϴ�." << endl;
	cout << "2. �ƴϿ�." << endl;
	cin >> num;
	switch(num){
		case 1:
			selMenu = 5;
		case 2:
			cout<<"1.�����Ͻðڽ��ϱ�?" << endl;
			cout<<"2.������ ���ðڽ��ϱ�?" << endl;
			cin >> num_2;
			if(num_2 == 1){
				attach();
			}
			if(num_2 == 2){
				bag();
			}
	}	
}

