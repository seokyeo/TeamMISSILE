#include <iostream>
#include <windows.h>
#include <string>                   // �����̳� �Լ��� ���� ����� ����, ����� �����ư��� ��� ���� ���� �ʿ伺 ����  
#define MAX_SIZE 100                // �� ����� �ִٴ� ���� �Ͽ� attak, defense, bag, run 
using namespace std;

struct professor_state    
{
 string bag[MAX_SIZE];             // �⺻ �������̳�, �������� �� ������ ����� ���� 
 string skill[MAX_SIZE];           // �⺻ ��ų�̳�, �������� �� ��ų ����� ���� 
 int level;                     // ����  
 int hp;                      // ü�� 
};

void attack();              // ����  : 1�� ������ 1. ��ų1 2. ��ų2 3. ��ų3 �̷������� ���� �ִ� ��ų �����ְ� 1.2.3�� �ϳ� ����  
void defense();             // ����  : ����Ͽ� 2���� ������ ����ó�� ��ų��� ���� ������ ���ҽ�Ű�� 
void bag();                 // ���� : 3�� ������ ���濡 ����� ������ ��� ���� 
void run();                 // ����  : ���� 

void menu();

int main()
{
 professor_state Song, jang, Red;  // ��, ��, ȫ ������ ĳ���� ���� 
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
   cout << "�׾����ϴ�. " << endl; // if ���޾Ƽ� �������� ������ ��� 
                                     
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
	cout << "����" << endl;       // ���� �ð� ���� ���� 
}
void defense(){
	cout << "���� " << endl;   // ���� 
}
void bag(){
	cout << " ���� " << endl;     // ���� 
}
void run(){
	cout << "�� �� " << endl;       // ����  
}

