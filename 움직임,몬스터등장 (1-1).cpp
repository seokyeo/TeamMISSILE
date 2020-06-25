#include <iostream>
#include <math.h>
#include <ctime>
#include <windows.h>

#define MAP_X_MAX 130
#define MAP_Y_MAX 32
#define FALSE 0
#define TRUE 1

using namespace std;

class ConsoleSet      //�ܼ�â ���� Ŭ����. Console::SetCon 
{
   public : 
      ConsoleSet() //�����ڸ� ���� �ܼ�â ���� 
      {         
         system("mode con:cols=130 lines=32");   //�ܼ�â�� ���� ���� ũ�⸦ �ʰ� �����ϰ� ���� 
         system("title Team Missile");
            
         HANDLE hConsole;
          CONSOLE_CURSOR_INFO ConsoleCursor;
          hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
             
          ConsoleCursor.bVisible = 0;      //Ŀ�� �Ⱥ��̰� 
          ConsoleCursor.dwSize = 1;      //Ŀ�� ����� ũ�� 1�� 
          SetConsoleCursorInfo(hConsole , &ConsoleCursor);
      }
      
      static void gotoxy(short m_x, short m_y)       //ConsloeSet::�������� ���� �ֵ��� static �Լ��� ���� 
      {//Ŀ���̵��Լ�
        COORD Cur;
        Cur.X = m_x;
        Cur.Y = m_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
       }
};

class Character
{    
    private : 
      int x;      //ĳ���Ͱ� ��µ� x��ǥ
       int y;      //ĳ���Ͱ� ��µ� y��ǥ
       int size_x;      //ĳ���͸� ����� 3*3ũ�� 
      int size_y;
       char figure[10];      //ĳ���� ����� �迭 (3*3ũ�� ��µ� ����) 
       char monster[10];
       bool direction;         //true=�����̵� , false=�����̵� 
    
       float t_jump;
       int leg_m;            //leg motion
       unsigned int t_leg;
   
   public :
      Character()      //�����ڷ� �ʱⰪ ���� 
      {
         x = 60;
         y = 19;
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
         direction = TRUE;
         t_jump = 2;
          leg_m = 1;            
          t_leg = 0;

      }

      void ControlCharacter() 
      {   
         bool move = FALSE;
          
         if (GetAsyncKeyState(VK_LEFT) && x > 1)       //kbhit�ϰ� switch�����ε� �غ����� ���� ���� 
         {                                    //Ű�� �ȴ����� ����  GetAsyncKeyState 0�� ����. 
            x -= 1;      //ĳ������ ��� x��ǥ�� 1 ���� 
            direction = FALSE;
            move = TRUE;
         }
         
         if (GetAsyncKeyState(VK_RIGHT) && x < MAP_X_MAX - 2) 
         {
            x += 1;
            direction = TRUE;
            move = TRUE;
         }
         
         if (GetAsyncKeyState(VK_UP) && y > 1 && y == 19)
            t_jump = 0;
      
         y -= 2;      
         
         if (y < 19)  
         {
            
            if (t_jump < 4)
               t_jump += 0.4;
               
            y += floor(t_jump);      //floor�� �����Լ� 
            
            if (y > 19)
               y = 19;
         } 
         else 
         {
            t_jump = 0;
            y = 19;
         }
      
         if (direction == TRUE)       //ĳ���Ͱ� ���������� ���������� 
         {   
            figure[3] = '('; figure[5] = 'o';      //����κ� ������     
         } 
         else                //ĳ���Ͱ� ���ʹ����� ���������� 
         {   
            figure[3] = 'o'; figure[5] = ')';       //����κ� ������ 
         }
      }
    
   
      
      //private������ �ִ� ������ ���� 
      int GetX(){return x;}
      int GetY(){return y;}
      int GetSizeX(){return size_x;}
      int GetSizeY(){return size_y;}
      char* Getfigure(){return figure;}
};



class Monster {
    private : 
      int x;      //ĳ���Ͱ� ��µ� x��ǥ
       int y;      //ĳ���Ͱ� ��µ� y��ǥ
       int size_x;      //ĳ���͸� ����� 3*3ũ�� 
      int size_y;      //ĳ���� ����� �迭 (3*3ũ�� ��µ� ����) 
       char monster[10];
       
       float t_jump;
   
   public :
      Monster()      //�����ڷ� �ʱⰪ ���� 
      {
         x = 1;
         y = 17;
                  
         t_jump = 4;         

         size_x = 4;
         size_y = 4;
         
         //�ʱ� ĳ���� ��� (3*3) 
			monster[0] = '@';
			monster[1] = '-';
			monster[2] = '-';
			monster[3] = '@';
			monster[4] = '|';
			monster[5] = ' ';
			monster[6] = ' ';
			monster[7] = '|';
			monster[8] = '|';
			monster[9] = '|';
			monster[10] = '|';
			monster[11] = '|';
			monster[12] = '_';
			monster[13] = '_';
			monster[14] = '_';
			monster[15] = '_';   
      }

      void Monster_Move() {   
            int num = rand()%3;
            if (num == 0 && x > 3)       //kbhit�ϰ� switch�����ε� �غ����� ���� ���� 
            {                                 //Ű�� �ȴ����� ����  GetAsyncKeyState 0�� ����. 
                    x -= 2;      //ĳ������ ��� x��ǥ�� 1 ���� 
                } 
            if (num == 1 && x < MAP_X_MAX - 3) {
                x += 2;
            }
            if (num == 2 && y > 17) 
                t_jump = 4;
		 	y -= 4;  
            if (y <17)  //ĳ���� �׷��ִ� y��ġ�� 19~22��. �ű⿡ y�� 19�� �� �� ���� t_jump�� ����.(�߷�)  && ��ȭ��ǥ ������ t_jump�� 0���� ������༭ ĳ���Ͱ� y��ǥ 16�� ������ ��ġ�ϰ� ��� 
            { 	
               if (t_jump <= 4)
				t_jump += 4;		                 
            	y += floor(t_jump); 
            	y=17; 	            
            }
   	}
   
      int GetX(){return x;}
      int GetY(){return y;}
      int GetSizeX(){return size_x;}
      int GetSizeY(){return size_y;}
      char* GetMonster(){return monster;}         
};

class Map
{   
   private :
      char ground[MAP_X_MAX];                  //���� ǥ���� ������ �迭 
      char mapData[MAP_X_MAX * MAP_Y_MAX];      //1���� �迭�� ����ũ��MAP_X_MAX * ����ũ�� MAP_Y_MAX�� ǥ��. mapData�� ���������� ��������ν� ���� ������ ����. 
            //������ : �ܼ�â ũ�⸦ �����ϰ� �迭�� ũ��� �����ϰ� �ؾ߸� ����� �� ������� ���. 
   public :
      Character * Song;
      Monster * newMon[100];
      
      Map()
      {   
         Song = new Character();
         fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);      //�����ڷ� mapData�迭�� ����' '���� �ʱ�ȭ 
         fillArray(ground, '=', MAP_X_MAX);         //�����ڷ� ground�迭�� '='�� �ʱ�ȭ 
      }
      

      void fillArray(char arr[], char c, int max_value)    //�迭�� str[0]~str[max_value]�� ���� c�� ä��� �Լ� 
      {   
         for (int i = 0; i < max_value; i++)
            arr[i] = c;
      }
      
      void EditMap(int x, int y, char str)       //�ܼ�â�� x,y��ǥ�� str�� �����ϴ� �Լ�.  �ܼ�â�� �����ֻ���� (1,1)��. 
      {
         if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)      //mapData�� (MAP_X_MAX*MAP_Y_MAX)������ 
         mapData[(y - 1) * MAP_X_MAX + x - 1] = str;                  //(y-1)*MAP_X_MAX�� �ϸ� �ܼ�â�� y��° ���� ��Ÿ�� �� ����. �ű⿡ x-1�� ���ϸ� (x,y)�� ��Ÿ��. 
                                                         //�ܼ�â�� (1,1)��ǥ = �ܼ�â�� �����ֻ�� = mapData[0]�� �ǹ�
                                                         //ex)  EditMap(1,1,'@')�� �ϸ� �ܼ�â �����ֻ�ܿ� @�� �׸�.
      }
      
      void MakeGround() //�� �迭 ground�� mapData�� �ݿ������ν� �� �׸��� 
      {   
         //�� 
         DrawMap(1, 22, "================================================================================================================================");
         //���� ����(�׸�ڽ�) 
      }
      
      void DrawMap(int x, int y, char str[])
      {
         for(int i=0; i<strlen(str); i++)
         EditMap(x+i, y, str[i]);   
      }
      
      void Drawfigure(int x, int y, int size_x, int size_y, char figure[])   //EditMap�Լ��� for�� ó���ؼ� x,y��ǥ�� ������ �ش� ��ǥ�� �������� size_x,size_yũ���� ���� ���� 
      {                                          //ĳ���� ũ�Ⱑ size_x,size_y��. 
         for (int i = 0; i < size_y; i++)   //size_y�� ���� ���� 
         {
            for (int j = 0; j < size_x; j++)   //size_x�� ���� ���� 
               EditMap(x + j, y + i, figure[i * size_x + j]);      //i*size_x�� 1��,2��,3���� ǥ��. j�� ���� ǥ��. 
         }
      }
      void CreateMonster()
      {
         
         for(int i=0; i<5; i++) {
            newMon[i] = new Monster;
            
         }
      }      
      char* GetMapData(){return mapData;}      //private������ ���� ����. 
      
      void printMap()
      {
         cout<<mapData;            //�� ��� 
      }
};

class GamePlay
{
   public :
      Monster * m;
   int i; 
      GamePlay()
      {   
         
         Map m1;
         clock_t start, end;
         start = clock();   //������������
         
        m1.CreateMonster();
    
         while(TRUE) {

         end = clock();   //�ð�������
         float time = ((float)(end - start) / CLOCKS_PER_SEC);
         
         
         ConsoleSet::gotoxy(0,0);
         m1.fillArray(m1.GetMapData(), ' ', MAP_X_MAX * MAP_Y_MAX);   //���� �������� �ʱ�ȭ ������  
         m1.Song->ControlCharacter();      //ĳ���� ������
         
         for(int i=0; i<3; i++) {
            m1.Drawfigure(m1.newMon[i]->GetX()+(i*12),m1.newMon[i]->GetY(),4,4,m1.newMon[i]->GetMonster());
         }
 		 for(int i=3; i<5; i++) {
            m1.Drawfigure(m1.newMon[i]->GetX()+120-(i*12),m1.newMon[i]->GetY(),4,4,m1.newMon[i]->GetMonster());
         }

         if (time >= 0.1)   
         {   
			for(int i=0; i<5; i++)
            m1.newMon[i]->Monster_Move();
            start = clock();
         }          
		m1.MakeGround();      //�� �ٽ� �ʿ� �ݿ����ֱ�. �ֳ��ϸ� ������ �ݺ������� �� ��ü�� �������� �ʱ�ȭ �ϹǷ�! 
         m1.Drawfigure(m1.Song->GetX(),m1.Song->GetY(), 3, 3,m1.Song->Getfigure());      //�ʿ� Songĳ���� �׸��� 
                                 
    
         m1.printMap();
         
         Sleep(33);   //�������� �ʹ� ���� ������ �ֱ�.
         }
      }
};

int main() {

   ConsoleSet();   //�ܼ�â ���� ������ ȣ�� 
   GamePlay();
   
   return 0;
}

