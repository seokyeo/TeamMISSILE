#include <iostream>
#include <math.h>
#include <ctime>
#include <windows.h>
#define MAP_X_MAX 130
#define MAP_Y_MAX 32
#define FALSE 0
#define TRUE 1

using namespace std;

class ConsoleSet {      //�ܼ�â ���� Ŭ����. Console::SetCon 
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
    char name[32];
    int lv;
    int hp,hpm;
    int exp,expi;
    int power;
    int wepon;         //���� ����     
    float t_jump;


public :
    char* figure_invenWeapon;
    char rightweaponFigure[4];
    bool attack;
    int weaponX;
    int weaponY;
    bool direction;         //true=�����̵� , false=�����̵�

    Character()      //�����ڷ� �ʱⰪ ���� 
    {
        x = 60;
        y = 19;
        size_x = 3;
        size_y = 3;
        lv = 1;
        hpm = 100;
        hp = hpm;
        exp = 0;
        expi = 100;
        power = 10;
        wepon = 0;
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

        name[0] = 'M';
        name[1] = 'r';
        name[2] = '.';
        name[3] = 'S';
        name[4] = 'o';
        name[5] = 'n';
        name[6] = 'g';
        name[7] = '\0';
        direction = TRUE;
        t_jump = 2;

        attack = FALSE;   
        //�κ��丮 �� ���� ��� 
        figure_invenWeapon= " ����>";

        //ĳ���Ͱ� ��� �ִ� ���� ���    
        rightweaponFigure[0] = 'o';
        rightweaponFigure[1] = '-';
        rightweaponFigure[2] = '-';   
        rightweaponFigure[3] = '-';     
    }

    void ControlCharacter() {   
        bool move = FALSE;
        weaponX = x+2;
        weaponY = y+1;
         //���� ��� ��ġ 
        if (GetAsyncKeyState(0x5A))    //����Ű ������ 
            attack = TRUE;

        if (GetAsyncKeyState(VK_LEFT) && x > 1) {     //kbhit�ϰ� switch�����ε� �غ����� ���� ����                                //Ű�� �ȴ����� ����  GetAsyncKeyState 0�� ����. 
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
        if (y < 19) { //ĳ���� �׷��ִ� y��ġ�� 16��. �ű⿡ y�� 19�� �� �� ���� t_jump�� ����.(�߷�)  && ��ȭ��ǥ ������ t_jump�� 0���� ������༭ ĳ���Ͱ� y��ǥ 16�� ������ ��ġ�ϰ� ��� 
            if (t_jump < 3)
               t_jump += 0.5;
            y += floor(t_jump);      //floor�� �����Լ� 
            if (y > 19)
               y = 19;
        } 
        else {
           t_jump = 0;
            y = 19;
        }
        if (direction == TRUE) {     //ĳ���Ͱ� ���������� ����������    
           figure[3] = '('; figure[5] = 'o';      //����κ� ������     
            rightweaponFigure[0] = 'o';
            rightweaponFigure[3] = '-';
        } 
        else {              //ĳ���Ͱ� ���ʹ����� ����������  
            figure[3] = 'o'; figure[5] = ')';       //����κ� ������ 
            rightweaponFigure[0] = '-';
            rightweaponFigure[3] = 'o';
            weaponX = x-3;
            weaponY = y+1;
        }
      }
      //private������ �ִ� ������ ���� 
      int GetX(){return x;}
      int GetY(){return y;}
      int GetSizeX(){return size_x;}
      int GetSizeY(){return size_y;}
      char* Getfigure(){return figure;}
      char* Getname(){return name;}
      int GetHp(){return hp;}
      int GetHpm(){return hpm;}
      int GetLv(){return lv;}
      int GetExp(){return exp;}
      int GetExpi(){return expi;}
      int GetPower(){return power;}
};



class Monster {
    private : 
       int x;      //ĳ���Ͱ� ��µ� x��ǥ
        int y;      //ĳ���Ͱ� ��µ� y��ǥ
        int size_x;      //ĳ���͸� ����� 3*3ũ�� 
        int size_y;      //ĳ���� ����� �迭 (3*3ũ�� ��µ� ����) 
        char monster[16];
        float t_jump;
        
		int boss_x;
        int boss_y;
        int boss_size_x;
        int boss_size_y;
        char boss[36];
      

   public :
      Monster()      //�����ڷ� �ʱⰪ ���� 
      {
         x = 3;
         y = 2;

         t_jump = 4;         

         size_x = 4;
         size_y = 4;

         //�ʱ� ĳ���� ��� (3*3) 
         monster[0] = ' ';
         monster[1] = '_';
         monster[2] = '_';
         monster[3] = ' ';
         monster[4] = '(';
         monster[5] = '*';
         monster[6] = '*';
         monster[7] = ')';
         monster[8] = '-';
         monster[9] = '-';
         monster[10] = '-';
         monster[11] = '-';
         monster[12] = ' ';
         monster[13] = ' ';
         monster[14] = ' ';
         monster[15] = ' ';   
      }

      void Monster_Move() {   
            int num = rand()%3;
            if (num == 0 && x >= 3)
                x -= 2; 
            if (num == 1 && x < MAP_X_MAX - 3)
                x += 2;
            if (y < 19) {
                t_jump = 2;
            y=y-2; 
          }

            if (y <19)  //ĳ���� �׷��ִ� y��ġ�� 19~22��. �ű⿡ y�� 19�� �� �� ���� t_jump�� ����.(�߷�)  && ��ȭ��ǥ ������ t_jump�� 0���� ������༭ ĳ���Ͱ� y��ǥ 16�� ������ ��ġ�ϰ� ��� 
            {    
               if (t_jump < 3)
            t_jump += 1;                       
               y += floor(t_jump); 
            if(y>=19) {
               t_jump=0;
               y=19;
            }                 
            }
            else {
               t_jump=0;
               y=19;
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
            //������ : �ܼ�â ũ�⸦ �����ϰ� �迭�� ũ��� �����ϰ� �ؾ߸� ����� �� ������� ���? . 
    public :
       Character * Song;
       Monster * newMon[100];

       Map() {   
        Song = new Character();
        fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);      //�����ڷ� mapData�迭�� ����' '���� �ʱ�ȭ 
        fillArray(ground, '=', MAP_X_MAX);         //�����ڷ� ground�迭�� '='�� �ʱ�ȭ 
        }


    void fillArray(char arr[], char c, int max_value) {   //�迭�� str[0]~str[max_value]�� ���� c�� ä��� �Լ�    
        for (int i = 0; i < max_value; i++)
           arr[i] = c;
    }

    void EditMap(int x, int y, char str) {       //�ܼ�â�� x,y��ǥ�� str�� �����ϴ� �Լ�.  �ܼ�â�� �����ֻ���� (1,1)��. 
         if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)      //mapData�� (MAP_X_MAX*MAP_Y_MAX)������ 
         mapData[(y - 1) * MAP_X_MAX + x - 1] = str;                  //(y-1)*MAP_X_MAX�� �ϸ� �ܼ�â�� y��° ���� ��Ÿ�� �� ����. �ű⿡ x-1�� ���ϸ� (x,y)�� ��Ÿ��. 
                                                         //�ܼ�â�� (1,1)��ǥ = �ܼ�â�� �����ֻ�� = mapData[0]�� �ǹ�
                                                         //ex)  EditMap(1,1,'@')�� �ϸ� �ܼ�â �����ֻ�ܿ� @�� �׸�.
    }

    void MakeGround() { //�� �迭 ground�� mapData�� �ݿ������ν� �� �׸���   
        //��
        Drawfigure(1, 22, 130,1, ground); 
    }

    void DrawMap(int x, int y, char str[]) {
        for(int i=0; i<strlen(str); i++)
        EditMap(x+i, y, str[i]);   
    }

    void Drawfigure(int x, int y, int size_x, int size_y, char figure[]) {  //EditMap�Լ��� for�� ó���ؼ� x,y��ǥ�� ������ �ش� ��ǥ�� �������� size_x,size_yũ���� ���� ����                                          //ĳ���� ũ�Ⱑ size_x,size_y��. 
        for (int i = 0; i < size_y; i++) {  //size_y�� ���� ���� 
            for (int j = 0; j < size_x; j++)   //size_x�� ���� ���� 
               EditMap(x + j, y + i, figure[i * size_x + j]);      //i*size_x�� 1��,2��,3���� ǥ��. j�� ���� ǥ��. 
        }
    }
    
    void CreateMonster() {
        for(int i=0; i<10; i++)
            newMon[i] = new Monster;
    }      
      
    char* GetMapData(){return mapData;}      //private������ ���� ����. 

    void printMap() {
         cout<<mapData;            //�� ��� 
    }
    
    void printName(int x, int y, char name[]) {
        Drawfigure(x-2,y-2,7,1,name);   //7�� �̸� ���� 
    }

    void DrawNumber(int x, int y, int num) {//x,y��ǥ�� ���ڸ� �Է� ������  �ش� ��ġ�� ���� ���� �������� ���ڸ� ȭ�鿡 �׸�
       int tmp = num;
       short len = NumLen(tmp), cnt = len;
      char str[len];
       do {
           cnt--;
           str[cnt] = (char)(tmp % 10 + 48);
           tmp /= 10;
       } while(tmp != 0); 
       Drawfigure(x, y,len,1,str);
    }

    int NumLen(int num) {
        int tmp = num;
        short len = 0;
        while(tmp != 0) {
            tmp /= 10;
            len++;
        }
        return len;
    }
    
    void ShowStatus() {
        Drawfigure(2,1,35,1,"-------------------------------------");
        Drawfigure(2,9,35,1,"--------------------------------------");
        for(int i=0; i<9; i++) {
           EditMap(1,1+i,'|');
            EditMap(37,1+i,'|');
        }
        Drawfigure(4,2,14,1,"\"Mr.Song\"  LV.");
        DrawNumber(18,2,Song->GetLv());

        Drawfigure(27,2,6,1,"Weapon");
        Drawfigure(25,3,10,1,"------------");
        for(int i=0; i<4; i++) {
            EditMap(25,4+i,'I');
            EditMap(35,4+i,'l');
        }
        Drawfigure(25,8,10,1,"------------");

        Drawfigure(4,5,3,1,"HP:");
        DrawNumber(8,5,Song->GetHp());
        EditMap(12,5,'/');
        DrawNumber(14,5,Song->GetHpm());

        Drawfigure(4,7,6,1,"Power:");
        DrawNumber(11,7,Song->GetPower());

        DrawMap(27, 5, Song->figure_invenWeapon);
    }
    
    void DrawWeapon() {
        Drawfigure(Song->weaponX,Song->weaponY,4,1,Song->rightweaponFigure);
    }
    void DrawAttack() {
        if(Song->direction == TRUE && Song->attack == TRUE) {
           Song->weaponX++;
            DrawWeapon();
            Song->weaponX--;
            Song->rightweaponFigure[3] = ' ';
            Song->rightweaponFigure[4] = ' ';
            DrawWeapon();
        }
        if(Song->direction == FALSE && Song->attack == TRUE) {
            Song->weaponX--;
            DrawWeapon();
            Song->weaponX++;
            DrawWeapon();
        }
    }       
};

class GamePlay
{
    public :
    Monster * m;
    int i; 
    GamePlay() {           
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
        for(int i=0; i<10; i++)
            m1.Drawfigure(m1.newMon[i]->GetX()+(i*12),m1.newMon[i]->GetY(),4,4,m1.newMon[i]->GetMonster());
        if (time >= 0.1) {   
         for(int i=0; i<5; i++)
               m1.newMon[i]->Monster_Move();
         start = clock();
        }
       if(time>= 0.5) {
         for(int i=5; i<10; i++)             
               m1.newMon[i]->Monster_Move();
        } 
      m1.MakeGround();      //�� �ٽ� �ʿ� �ݿ����ֱ�. �ֳ��ϸ� ������ �ݺ������� �� ��ü�� �������� �ʱ�ȭ �ϹǷ�! 
        m1.Drawfigure(m1.Song->GetX(),m1.Song->GetY(), 3, 3,m1.Song->Getfigure());      //�ʿ� Songĳ���� �׸��� 
        m1.printName((m1.Song)->GetX(),(m1.Song)->GetY(),(m1.Song)->Getname());
        m1.ShowStatus();                                
        m1.DrawWeapon();
        m1.DrawAttack();   
        m1.printMap();
        Sleep(30);   //�������� �ʹ� ���� ������ �ֱ�.
        }
    }
};

int main() {

   ConsoleSet();   //�ܼ�â ���� ������ ȣ�� 
   GamePlay();

   return 0;
}
