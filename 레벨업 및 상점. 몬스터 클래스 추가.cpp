#include <iostream>
#include <windows.h>
#include <string>                   // �����̳� �Լ��� ���� ����� ����, ����� �����ư��� ��� ���� ���� �ʿ伺 ����  
#define MAX_SIZE 100 
                                   // �� ����� �ִٴ� ���� �Ͽ� attak, defense, bag, run 
using namespace std;

 bool kill = false;                // ���߿� ���͸� ���̸� kill�� true;�� �ٲ۴�. true�϶� ����ġ�� �÷� ������ �ø��� ���� ���� 
 bool sw = false;                     // ���濡�� �ֹ���  ����ȭ �Ҷ� ��G�ϴ� ���� 
class professor_state    
{
 		 
 public:
	int level;           // ����
	int EX_VA;  
 	int experince_value[EX_VA];   // ����ġ�� �ϴ� 5�� ���� ���߿� ����ؼ� ���� 
	string bag[MAX_SIZE];             // �⺻ �������̳�, �������� �� ������ ����� ���� 
    string skill[MAX_SIZE];       // �⺻ ��ų�̳�, �������� �� ��ų ����� ���� 
	void levelup()
	{
		level++;
	} 
};

class store
{
	public:
		int item;
		int potion;
}

class Monster
{
	public: 
	     int level;
	     int giving_experince;
};

void experincevalueup(professor_state a, Monster b )                           // ���� ���� �� ������ ����ġ �Լ� 
{
		while(kill){ 
		  	  for(int i= 1; i<= b.giving_experince ; i++){          // ������ giving experince ��, ���͸� ������ �ִ� ����ġ�� 3�̶� �Ҷ� ����ġ�� 5 ���� 3���� ��.  
		  	  	     a.experince_value[i]  = 1;                     // giving experince ��  
				} 
			  for(int i = 1; i <= a.EX_VA; i++){               // ����ġ �� 5������ ��� 1�� �ɽ� ������  
			  	if(a.experince_value[i] = 1){
			  		a.levelup();
				    int next = a.EX_VA *2;              // ������ �ҽ�  ����ġ �� 2��Ǳ�� �ϴ� �س� �̰͵� ���߿� ����� ���� 
					a[next];		
				  }
			  }	
			  
				
		  }
		 kill = False;	               
}

void attack();              // ����  : 1�� ������ 1. ��ų1 2. ��ų2 3. ��ų3 �̷������� ���� �ִ� ��ų �����ְ� 1.2.3�� �ϳ� ����  
void defense();             // ����  : ����Ͽ� 2���� ������ ����ó�� ��ų��� ���� ������ ���ҽ�Ű�� 
void bag();                 // ���� : 3�� ������ ���濡 ����� ������ ��� ���� 
void run();                 // ����  : ���� 

void menu();

int main()
{
 professor_state Song;             // ���ΰ��� ������ �� �� 
 Song.skill[0] = "basic attack";       // �⺻ ���ݰ� �⺻��ų ���� ���߿� ��ġ ���ؾ�� 
 Song.skill[1] = "basic skill";
 Song.level  = 0;           // ����
 Song.EX_VA = 5;
 
 Monster jang;
 jang.giving_experince = 3;
 int selMenu;


 while(1)
 {
  system("cls");
  menu();
  cout << "�����ϼ���  "; 
  cin >> selMenu;
  fflush(stdin);
  system("cls");
  switch(selMenu)
  {
  case 1:
   attack();
   break;
  case 2:
   defense(); 
   break;
  case 3:
   bag();
   break;
  case 4:
   run();
   break;
  case 5:
   cout << "�̰���ϴ�." << endl;  // if ���޾Ƽ� ������ �̰����� ��� 
   kill = true;
   experincevalueup(Song, jang);   
   cout << "�׾����ϴ�. " << endl; // if ���޾Ƽ� �������� ��?? ��� 

   return 0;                       // �׸��� ����  

   } 
  system("pause");
 }
 return 0;
}

void menu()
{
    cout <<"������������������������������" << endl;
    cout <<"��          ��   ��!!!      ��" << endl;
    cout <<"��       1. ��   ��         ��" << endl;
    cout <<"��       2. ��   ��         ��" << endl;
    cout <<"��       3. ��   ��         ��" << endl;
    cout <<"��       4. ��   ��         ��" << endl;
    cout <<"��                          ��" << endl; 
    cout <<"������������������������������" << endl;

}

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
			basic skill1(); 
			break;
		case 3:
		    cout << "�⺻ ��ų2 (������: 15)"  << endl; 
		    basic skill2();
		    break;
	}
}

void basic attack( )                        //������ ������ ����â���� �̵� ���߿�  
{
	Monster_Hp = Monster_Hp - 5;
	if(sw){
		Monster_Hp = Monster_Hp - 15;
		sw = false;
	}
}

void basic skill1()                             //������ ������ ����â���� �̵� ���߿� 
{ 
	Monster_Hp = Monster_Hp - 10;
	if(sw){
		Monster_Hp = Monster_Hp - 20;
	    sw = false; 
	}
}

void basic skill2()                              //������ ������ ����â���� �̵� ���߿� 
{
	Monster_Hp = Monster_Hp - 15;
	if(sw){
		Monster_Hp = Monster_Hp - 25;
	    sw = false; 
	}
}

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

void heal()             // ���߿� ������ ������ ����â�� �Űܾ���. 
{
	int hp_up = 10;
	Song_ hp = Song_ hp +10;
	
}

void strup()            //���߿� ������ ������ ����â�� �Űܾ���. 
{
	sw = true;     // ���߿� ������ ������ ����â���� ���������� �����ҵ�, �׸��� ��ȭ�� ���¿��� ��Ÿ�� ��ų������ ������� ���ƿ�. 
	int str_up = 10;
	cout << "��� ���ݰ� ��ų�� ���ݷ� 10�� �پ����ϴ�." << endl;
}

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
