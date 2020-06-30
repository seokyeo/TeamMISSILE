#include <stdio.h>
#include <stdlib.h>
#include <memory.h>	//memset
#include <time.h>
#include <windows.h>
#define FALSE 0
#define TRUE 1
#define MAP_X_MAX 116
#define MAP_Y_MAX 36
#define FLOOR_Y 32
#define OBJECT_MAX 100
#define SPAWN_TIME 15000

typedef struct _Character {
    int position[2], size[2];	//position[0]�� x��ǥ, position[1]�� y��ǥ ,  size[0]�� size_x, size[1]�� size_y 
    float accel[2], flyTime;	//accel[0]: �뽬�� ���ӵ�  accel[1]: ������ ���ӵ�  and flotation time
    bool direction;				//true=�����ʹ��� , false=���ʹ��� 
    //status 
    char name[16];
    int lv, exp[2], score, hp[2], mp[2];	//[0]=�ִ밪 , [1]=���簪 
    int power, weapon;
    //animation control
    bool attack;				//Ű���� z�� ������ attack = TRUE, �ƴϸ� FALSE 
    bool skill_attack1;			//Ű���� x�� ������ ������ ��ų  
	bool skill_attack2;			//Ű���� a�� ������ ������ ��ų  
	int tick[4];				//tick : ������(�ð�����) ����  [0]: ���� tick [1]: ���� tick, [2] : �뽬 tick, [3] : �ǰݽ� ���� tick
}Character;

typedef struct _Object {	//enemies, projectiles, particles, etc.
    int position[2], size[2];
    float accel[2], flyTime;
    bool direction;
	
    int kind;	//1~99: items, 100~199: enemies, 200~: projectiles, particles
    int hp[2], exp;	//hp: this value is used randomly for item or particle object
    int motion[3];	//motion
    int tick[4];	//0: hpshow time(enemy) or active time(projecticles, particles)
}Object;

Character character = {{MAP_X_MAX / 2, MAP_Y_MAX / 2}, {3, 3}, {0, 0}, 0, TRUE, "", 1, {100, 0}, 0, {100, 100}, {100, 100}, 10, 0, FALSE,FALSE,FALSE,{0, 1, 0, 0}};
Object **objects;

int tick = 0;							//tick 
int spon_tick = 0;						//���� ������ tick 
int boss_tick = 0;						//���� �ѹ��� ��ȯ�ǰ� �� tick 
char figure_floor[MAP_X_MAX];			//����� �迭 
char mapData[MAP_X_MAX * MAP_Y_MAX];	//�ܼ�â ũ���� �迭 

//ĳ���� ��� �迭 (3*3) 
const char figure_character[10] = " 0  | a^a";

//����ִ� ���� ��� 
const char figure_weapon[2][3][4] = 
{{"---", "--+", "<=+"},
 {"---", "+--", "+=>"}};

//����â �ڽ��� ������ 
const char figure_invenWeapon[3][11] = {"   /   /  ", "   /  '*. ", "  |   \"+\" "};  

//���� ��� 
const char figure_enemy1[2][13] = {" __ (**)----", " __ [  ]\'--\'"};
//���� �Ź� ��� 
char figure_spider[] ="|                | |      ##      |  --    {  }    --    |  {    }  |      |-{  --  }-|        { ---- }     |  --{ ---- }--  | -/  {  --  }  \\-     / {    } \\       / { 0000 } \\     -   { 00 }   -   |  /{      }\\  | |  |  \\()()/  |  ||  |   ||||   |  || /    \\/\\/    \\ || |            | |  |            |    |            |  ";


void StartGame();	//�ʱ� ���� 
void SetConsole();	//�ܼ�â ����  
void UpdateGame();   //�������� mapData ������Ʈ �� ���(��ü���� ���� ���� ��Ȳ ������Ʈ) 
void ExitGame();   //objects �����޸� ����  
void Draw_Figure(int x, int y, int size_x, int size_y, const char spr[]);	//(x,y)�� �������� size_x*size_yũ��� spr[]�� �׸� 
void FillMap(char str[], char ch, int max);	//str�迭�� ���� str_s�� max_value��ŭ ä�� 
void EditMap(int x, int y, char ch);	//(x,y)�� ����str�� ���� 
void Draw_Box(int x, int y, int size_x, int size_y);	//����â�� ���� �׸��� �Լ� (x,y)�� size_x*size_yũ���� ���� �׸�
void Draw_Number(int x, int y, int num);	//(x,y)��  char������ ��ȯ�� ���ڸ� �׸�
int NumLen(int num);	//num�� �ڸ����� �����ϴ� �Լ� (Draw_Number�Ҷ� �ʿ�)
void Control_UI();  //��� : ���׸���, ���ʻ�� ����â �׸��� �� ����
void Control_Character();	//��� : ĳ������ ������,��ų,�ǰ� �� ����  
bool CheckCollision(int position1[], int position2[], int size1[], int size2[]);	//�浹 üũ �Լ� : position1[]�� size1[]ũ�Ⱑ position2[]�� size2[]ũ��� �浹�� ���� TRUE  
void MovementControl(int position[], float accel[], int size[], float *flyTime);	//���ӵ� �Լ� 
bool EnemyPosition(int x, int size_x);   //ĳ������ ��ġ�� ������ ��ġ�� ��.  ĳ���Ͱ� ���ʿ� ������ FALSE, �����ʿ� ������ TRUE 
void Create_Object(int x, int y, int kind);      //x,y��ǥ�� kind���� ���� ������Ʈ ���� (1~99: ������, 100~199: ����, 200~299: ����, 400~500:���� 500~:���� ��ų)
void Control_Item(int index);
void Control_Enemy(int index);
void Control_Particle(int index);
void Control_Object();   //��� ������Ʈ ��Ʈ�� �Լ�
void Remove_Object(int index);      //object[index] �޸� ���� �� NULL�� �ʱ�ȭ : �ٸ� ������Ʈ�� ���� ũ�� ����� ���� 
void textcolor(int foreground, int background);   //�ؽ�Ʈ�÷�

int main()
{
	StartGame();

   while (TRUE) {
      if (tick +30 < GetTickCount()) {   //30ms�� �ѹ��� updategame�ǵ��� ����   
         tick = GetTickCount();         //��ǻ�� ���� �� ����� �ð��� ms�� ��ȯ. ���� tick�� 1�ʿ� 1000�� ������ 
         
         UpdateGame();

         if (tick == 0)               //character�� hp[1]�� 1�̸��� �Ǹ� tick = 0 
            break;
        
        if (character.lv > 500)			//�Ƽ��� ���� ������ lv500 �̻� �ǰ��ؼ� ���� 
        	break;
      }
   }
   
   ExitGame();
   return 0;
}

void StartGame() {
	SetConsole();			//�ܼ�â ���� ���� ũ�� ����, Ŀ�� �Ⱥ��̰� ���� 
	srand((int)time(NULL));
	
	printf("�̸��� �Է��ϼ��� : ");
	scanf("%s", character.name);
	
	FillMap(figure_floor, '=', MAP_X_MAX);	//���迭�� '=' ä��� 
	
	objects = (Object **)malloc(sizeof(Object *) * OBJECT_MAX);		//OBJECT_MAX���� object������ ���� �Ҵ�  
	memset(objects, 0, sizeof(Object *) * OBJECT_MAX); 				//objects�� ����Ű�� ���� sizeof(object*)*OBJECT_MAX ũ�⸸ŭ 0���� �ʱ�ȭ 
}

void SetConsole() {
	system("mode con:cols=116 lines=36");
	system("title ������ ����");
	
	HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

void UpdateGame() {
   FillMap(mapData, ' ', MAP_X_MAX * MAP_Y_MAX);   //���� �������� �ʱ�ȭ 
   
   Control_Character();   //mapData�� ĳ���� ���� ������Ʈ 
   Control_Object();   //mapData�� ��,����,������ �� ������Ʈ
   Control_UI();      //���迭 �� ����â ������Ʈ  
   
   if (spon_tick + 5000 < tick) {      //15�ʸ��� ���� ���� 
      spon_tick = tick;
      Create_Object(rand() % 90, 5, 100);      //(x: 0~90 , y:5) kind = 100 : ����    
      Create_Object(rand() % 90, 5, 100);
      Create_Object(rand() % 90, 5, 100);
   }
   
   if(character.score >= 1800 && character.score <= 2400 && boss_tick < tick)      //���ھ� 1800�̻� �Ǹ� ù���� ���� ���� kind 400 
   {
      Create_Object(MAP_X_MAX-22 ,9,400);
      boss_tick += 100000000;
   }
   
   if(character.score >= 6500 && character.score <= 8000 && boss_tick2 < tick)      //���ھ� 6500�̻� �Ǹ� �ι��� ���� ���� kind 401 
   {
      Create_Object(MAP_X_MAX-31 ,3,401);
      boss_tick2 += 100000000;
   }
   
   printf("%s",mapData);   //draw mapData
}

void ExitGame() {   //objects �����޸� ����  
    for (int i = 0; i < OBJECT_MAX; i++) {
        if (objects[i])
            free(objects[i]);
    }
    
    free(objects);
}

void Draw_Figure(int x, int y, int size_x, int size_y, const char spr[]) {	//(x,y)�� �������� size_x*size_yũ��� spr[]�� �׸� 
	for (int i = 0; i < size_y; i++) {
		for (int n = 0; n < size_x; n++)
			EditMap(x + n, y + i, spr[i * size_x + n]);
	}
}

void FillMap(char str[], char ch, int max) {	//str�迭�� ���� ch�� max��ŭ ä�� 
	for (int i = 0; i < max; i++)
		str[i] = ch;
}

void EditMap(int x, int y, char ch) {	//(x,y)�� ����ch�� ���� 
	if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)
		mapData[(y - 1) * MAP_X_MAX + x - 1] = ch;
}

void Draw_Box(int x, int y, int size_x, int size_y) {		//����â�� ���� �׸��� �Լ� (x,y)�� size_x*size_yũ���� ���� �׸� 
	EditMap(x, y, '.'); EditMap(x + size_x - 1, y, '.');
	EditMap(x, y + size_y - 1, '\''); EditMap(x + size_x - 1, y + size_y - 1, '\'');
	
	for (int i = 1; i < size_x - 1; i++) {
		EditMap(x + i, y, '-'); EditMap(x + i, y + size_y - 1, '-');
	}
	for (int i = 1; i < size_y - 1; i++) {
		EditMap(x, y + i, '|'); EditMap(x + size_x - 1, y + i, '|');
	}
}

void Draw_Number(int x, int y, int num) {		//(x,y)��  char������ ��ȯ�� ���ڸ� �׸� 
	int tmp = num, len = NumLen(tmp), index = len;
    char str[len];		//���� �ڸ���+1 ũ���� ���� �迭 (1�ڸ��� �ι���) 
    
    do {
        index--;
        str[index] = (char)(tmp % 10 + 48);
        tmp /= 10;
    } while(tmp != 0);
    
    Draw_Figure(x, y, len, 1, str);
}

int NumLen(int num) {		//num�� �ڸ����� �����ϴ� �Լ� (Draw_Number�Ҷ� �ʿ�) 
	int tmp = num, len = 0;
	
	if (num == 0) {
		return 1;
	} else {
		while(tmp != 0) {
        	tmp /= 10;
        	len++;
    	}
	}
	
    return len;
} 

void Control_UI() 	//��� : ���׸���, ���ʻ�� ����â �׸��� �� ���� 
{
	int expPer = (character.exp[1] * 100 / character.exp[0]);		//exp[1]�� ���� exp, exp[0]�� �ִ�exp(������) 
	int len;	//length of previous sprite
	
	Draw_Figure(1, FLOOR_Y, MAP_X_MAX, 1, figure_floor);	//draw floor
	
	Draw_Box(1, 2, 35, 8); Draw_Box(27, 5, 7, 4);	//draw weaponinven
	Draw_Figure(28, 6, 5, 2, figure_invenWeapon[character.weapon]);		//character.weapon�� 0,1,2�� ���� ���� ��� �迭 ��Ÿ�� 
	Draw_Figure(28, 4, 6, 1, "Weapon");
	
	EditMap(3, 3, '\"');	//draw name, lv, exp
	Draw_Figure(4, 3, strlen(character.name), 1, character.name);	len = 4 + strlen(character.name);//len�� x��ǥ�� ��Ÿ��. �� ���ڿ� ���̸�ŭ len++��Ű�鼭 ���ڿ��� �˸��� ��ġ�� ��� 
	Draw_Figure(len, 3, 7, 1, "\" LV.");	len += 5;
	Draw_Number(len, 3, character.lv);	len += NumLen(character.lv);
	Draw_Figure(len, 3, 2, 1, " (");	len += 2;
	
	if (!expPer) {	//����ġ 0%�� 
		EditMap(len, 3, '0');	len ++;		 
	} else {
		Draw_Number(len, 3, expPer);	len += NumLen(expPer);
	}
	Draw_Figure(len, 3, 2, 1, "%)");
	
	Draw_Figure(MAP_X_MAX - NumLen(character.score) - 7, 3, 6, 1, "SCORE:");	//draw score
	Draw_Number(MAP_X_MAX - NumLen(character.score), 3, character.score);
	
	Draw_Figure(4, 5, 3, 1, "HP:");	//draw HP
	Draw_Number(8, 5, character.hp[1]);
	EditMap(9 + NumLen(character.hp[1]), 5, '/');
	Draw_Number(11 + NumLen(character.hp[1]), 5, character.hp[0]);
	
	Draw_Figure(4, 6, 3, 1, "MP:");	//draw MP
	Draw_Number(8, 6, character.mp[1]);
	EditMap(9 + NumLen(character.mp[1]), 6, '/');
	Draw_Number(11 + NumLen(character.mp[1]), 6, character.mp[0]);
	
	Draw_Figure(4, 8, 6, 1, "Power:");	//draw power
	Draw_Number(11, 8, character.power);
}

void Control_Character()
{	
	character.attack = FALSE;	//���ݺ����� �ʱ�ȭ (���� �� ���ݸ�ǿ��� �ȵ��ƿ�)
	character.skill_attack1 = FALSE;
	character.skill_attack2 = FALSE;
	 
	//LV up				exp[1]�� ���� exp, exp[0]�� Max exp 
	if (character.exp[1] >= character.exp[0]) {
		character.lv += character.exp[1] / character.exp[0];	//���� ������ lv�� ���� �ǵ��� ���� 
		character.hp[0] = 100 + character.lv * 5 ; character.mp[0] = 100 + character.lv * 3; 
		character.exp[1] = 0; character.exp[0] += character.lv * 10;
		character.power = 10+(character.lv * 2);
	}
	//hp,mp gen & control			0.9�ʸ��� ��ȸ��  
	if (character.tick[0] + 900 < tick) { 
		character.tick[0] = tick;
		character.hp[1] += 1;		//
		character.mp[1] += 3;
	}
	if (character.hp[1] > character.hp[0])		//�ִ� hp,mp�� �ʰ��Ϸ��ϸ� �ִ밪���� ����  
		character.hp[1] = character.hp[0];
	if (character.mp[1] > character.mp[0])
		character.mp[1] = character.mp[0];

	//���� ���� ���� 	
	if (character.hp[1] < 1)
		tick = 0;			//tick = 0�̵Ǹ� main�Լ����� while���� Ż���ؼ� ���� ������ �Ǿ����� 
 
 	//������ 
	if (character.tick[3] > 0)		//���Ϳ� �浹�� ���� character.tick[3] = 100�� ��. 
	{
		textcolor(15,4); //�ǰݽ� ������
		character.tick[3] -= 1;
	}
	else 
	{
		textcolor(0,15); 
	}
	
	//���� ������ 
	if (GetAsyncKeyState(0x5A) && character.tick[1] + 150 <= tick ) {	// 0x5A�� Z�� �ƽ�Ű�ڵ尪    ���ݵ����� 250ms 
		character.tick[1] = tick;
		character.attack = TRUE;
	}

	//��ų����1 ������ 
	if (GetAsyncKeyState(0x58) && character.mp[1] > 1 && character.tick[1]+ 30<= tick) {	// 0x5A�� x�� �ƽ�Ű�ڵ尪    
		character.tick[1] = tick;
		character.skill_attack1 = TRUE;
		character.mp[1] -= 1;
	}
	//��ų����2 ������	 
	if (GetAsyncKeyState(0x41) && character.mp[1] > 2 && character.tick[1]+ 30<= tick) {	// 0x5A�� x�� �ƽ�Ű�ڵ尪     
		character.tick[1] = tick;
		character.skill_attack2 = TRUE;
		character.mp[1] -= 2;
	}

	//�����ӱ����� 
	if (GetAsyncKeyState(VK_LEFT) && character.position[0] > 1) {	//���� ȭ��ǥ ������ x>1�̸� �����̵� 
			character.position[0]--;
			character.direction = FALSE;	//�������� 
		}
		
	if (GetAsyncKeyState(VK_RIGHT) && character.position[0] < MAP_X_MAX - 2) {	//������ ȭ��ǥ ������ x�� �ʿ���������-2�������� ������ 
			character.position[0]++;
			character.direction = TRUE;		//�������� 
		}
		
	if (GetAsyncKeyState(0x43) && character.tick[2] + 1200 <= tick) {	//dash		0x58�� X�� �ƽ�Ű�ڵ尪 	1.2�ʿ� �ѹ� ��� ���� 
			character.accel[0] = character.direction * 6 - 3;	//character.accel[0]�� ���ʹ��� �뽬��  -9, ������ ���� �뽬��  +3  
			character.tick[2] = tick;
		}
		
	if (GetAsyncKeyState(VK_UP) && character.position[1] + 3 == FLOOR_Y)	//jump
			character.accel[1] = -1.75;
	
	MovementControl(character.position, character.accel, character.size, &character.flyTime);	// control character movement  �߷±��� 
	
	//ĳ���� �׸��� �κ� 
	if (character.tick[3] % 2 == 0) {		//����tick�� ¦���� (����tick�� 100���� 1�� ��� �پ��. ���� ĳ���Ͱ� �����̰� ��)
		Draw_Figure(character.position[0], character.position[1], character.size[0], character.size[1], figure_character);	//ĳ���� �׸� 
		
		
		if (character.direction) {//�����ʹ����̸� ���� ���������� 
			EditMap(character.position[0], character.position[1] + 1, '(');
		} else {				  //���ʹ����̸�  ���� �������� 
			EditMap(character.position[0] + 2, character.position[1] + 1, ')');
		}
		
		if (character.accel[0] > 1)  //xŰ�� ������(dash) ������ ������ �����ִ� ���- ĳ���� ���ʿ� ������ȿ��   
			Draw_Figure(character.position[0] - 2, character.position[1], 1, 3, "===");
		if (character.accel[0] < -1) //xŰ�� ������(dash) ���� ������ �����ִ� ��� - ĳ���� �����ʿ� ������ȿ�� 
			Draw_Figure(character.position[0] + 4, character.position[1], 1, 3, "===");
		
		//���ݸ�� �׸��� �κ�  
		if (character.attack==TRUE ) {
					EditMap(character.position[0] - 2 + 6 * character.direction, character.position[1] + 1, 'o');
					Draw_Figure(character.position[0] - 5 + 10 * character.direction, character.position[1] + 1, 3, 1, figure_weapon[character.direction][character.weapon]);
				} 
		else {
					EditMap(character.position[0] + 2 * character.direction, character.position[1] + 1, 'o');
					Draw_Figure(character.position[0] - 3 + 6 * character.direction, character.position[1] + 1, 3, 1, figure_weapon[character.direction][character.weapon]);
				}
		
		//��ų���1 �׸��� �κ� 
		if (character.skill_attack1 == TRUE && character.direction == TRUE)		//��ų ����,  ������ ���� 
		{	
			int i;
			for(i=0; i<MAP_X_MAX - character.position[0]-4; i++);
			
			Draw_Figure(character.position[0] +4 ,character.position[1]+0 ,i+3, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			Draw_Figure(character.position[0] +4 ,character.position[1]+1 ,i+3, 1, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			Draw_Figure(character.position[0] +4 ,character.position[1]+2 ,i+3, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			}
		}
		if (character.skill_attack1 == TRUE && character.direction == FALSE)		//��ų ����,  ,���� ���� 
		{	
			int i;
			for(i=0; i<MAP_X_MAX - character.position[0]-4; i++);
			Draw_Figure(0,character.position[1]+0 ,character.position[0]-1, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			Draw_Figure(0,character.position[1]+1 ,character.position[0]-1, 1, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			Draw_Figure(0,character.position[1]+2 ,character.position[0]-1, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		}
		//��ų���2 �׸��� �κ� 
		if (character.skill_attack2 == TRUE)
		{
			Draw_Figure(107,27,10,5,"|\\_/|\"    |q p|   /}( 0 )\"\"\"\\ |\"^\"`    |||_/=\\\\__|");		//������ ���
			Draw_Figure(0,28,106,2,"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		} 
			
}


void MovementControl(int position[], float accel[], int size[], float *flyTime) {
	float y_value = accel[1];
	
	if (position[1] + size[1] == FLOOR_Y) {
		*flyTime = 0;		//���� ��������� flyTime = 0 
	} else {				//������ ������ flyTime += 0.05 
		*flyTime += 0.05;
		accel[1] += *flyTime; 
	}
	
	if (y_value != 0) {
		if (position[1] + size[1] + y_value > FLOOR_Y)		//������ ������ �߶��ϴ°� ����  
			y_value = FLOOR_Y - position[1] - size[1];
	}

	position[0] += accel[0] + 0.5; position[1] += y_value + 0.5;	  
	
	//accel�� 0�̵Ǹ� �Ʒ� ������� ������ �ȉ�. 
	if (accel[0] > 0) accel[0] -= 0.2; if (accel[0] < 0) accel[0] += 0.2;
	if (accel[1] > 0) accel[1] -= 0.1; if (accel[1] < 0) accel[1] += 0.1;
}

bool EnemyPosition(int x, int size_x) {      //ĳ������ �߾���  ������ �߾Ӻ��� �����̸� FALSE
   if (character.position[0] + 1 < x + size_x / 2)
      return FALSE;
   else
      return TRUE;
}

bool CheckCollision(int position1[], int position2[], int size1[], int size2[]) {	//�浿 üũ �Լ� 
	if (position1[0] > position2[0] - size1[0] && position1[0] < position2[0] + size2[0]	//position2[0]-size1[0] = ���� ��������-ĳ���� ����ũ�� , position2[0]+size2[0] = ������ ���� ��
	    && position1[1] > position2[1] - size1[1] && position1[1] < position2[1] + size2[1])	//y�� �浹 
		{
			return TRUE;
		}
	else
	{
		return FALSE;
	}
}

void Create_Object(int x, int y, int kind) {      //x,y��ǥ�� kind���� ���� ������Ʈ ���� (1~99: ������, 100~199: ����, 200~299: ����, 400:�Ź̺��� 401:�Ƽ��󺸽� 500~: ���� ��ų��)
   int index = 0;
   Object *obj = 0;
   
   while(TRUE) {
      if (! objects[index])
         break;
         
      if (index == OBJECT_MAX)
         return;

       index ++;
   }
   
    obj = (Object *)malloc(sizeof(Object));    //obj�� ���ο� object�� ����Ŵ  
    objects[index] = obj;                    //���������� �迭 objects�� obj�� ����Ű�� �ּҸ� ����Ŵ  
    memset(obj, 0, sizeof(Object));          //object�� 0���� �ʱ�ȭ 
    
    obj->kind = kind;                     //object������ kind ���� 
    obj->position[0] = x; obj->position[1] = y;
    obj->tick[0] = 0;
    
    if (kind <400 && (kind < 100 || kind > 199)) {      //0~100,200~399 -->  ���;ƴ�  
      obj->tick[1] = 0;   //���� ���ӵ� ������ 
   }
   
    if (kind >= 100 && kind < 200) {      //kind�� 100~199  -->  ����  
       obj->hp[0] = 150;      //���͸� �ϴ� kind100�� ���������� �س��� 
      obj->hp[1] = obj->hp[0];
       obj->exp = 30;
       obj->size[0] = 4;
      obj->size[1] = 3;
       obj->tick[1] = 0;
       obj->tick[2] = 1000;
       obj->tick[3] = 0;
   }
   
   //�Ź� ���� 
   if(kind == 400) //spider ������ kind 400 
   {
      obj->hp[0] = 500;      
      obj->hp[1] = obj->hp[0];
      obj->exp = 300; 
      obj->size[0] = 18;
      obj->size[1] = 18;
   }
   
   //�Ƽ��� ���� 
   if(kind == 401) // �Ƽ��� ������ kind 401 
   {
      	obj->hp[0] = 1000;      
      	obj->hp[1] = obj->hp[0];
      	obj->exp = 100000; 
       	obj->size[0] = 30;
      	obj->size[1] = 30;
   }
}

void Control_Item(int index) {
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int item_position[2] = {x, y - 2};
   int item_size[2] = {5, 2};
   
   if (CheckCollision(item_position, character.position, item_size, character.size)) {      //�����۰� ĳ���Ͱ� �浹�� ���� 
      Draw_Figure(x + 1, y - 5, 3, 1, "[E]");      //������ ���� [E] ǥ��  
      
      if (GetAsyncKeyState(0x45)) {      //EŰ�� ������ 
         character.weapon = objects[index]->kind;   //character.weapon = �����ȣ(kind��) 
      
         Remove_Object(index);
         return;
      }   
   }
   
   Draw_Figure(x, y - 2, 5, 2, figure_invenWeapon[objects[index]->kind]);

   
   MovementControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void Control_Enemy(int index) {
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int attack_position[2] = {character.position[0] - 5 + 8 * character.direction, character.position[1]}, attack_size[2] = {5, 3};      //ĳ���� �⺻ ���� ���� : ĳ���� �պκп��� 5*3ũ�� 
   //��ų ���� 
   int skill1_left_position[2] = {0,character.position[1]};
   int skill1_right_position[2] = {character.position[0]+2,character.position[1]};
   int skill1_left_size[2] = {character.position[0]-2,3};
   int skill1_right_size[2] = {MAP_X_MAX - character.position[0]-2,3};
   int skill2_position[2] = {0,28};
   int skill2_size[2]   = {106,3}; 
   
   int item_code = rand() % 100;

   if (objects[index]->hp[1] < 1) {   //���Ͱ� ������ 
      for (int i = 0; i < 3; i++)      //���� 3�� ������ 
         Create_Object(x + objects[index]->size[0] / 2, y + objects[index]->size[1] / 2, 200); 
         
      //item_code�� 90�̻��̰ų� 3�����̸� ������ ��������   
      if (item_code >= 90)
         Create_Object(x + objects[index]->size[0] / 2 - 2, y, 1);   //1������ 
      if (item_code <= 3)
         Create_Object(x + objects[index]->size[0] / 2 - 2, y, 2);   //2������  
      
      
      character.exp[1] += objects[index]->exp;
      
      Remove_Object(index);
      return;
      }
   
   if (objects[index]->tick[0] + 2000 > tick) //���Ͱ� ���ݹ��� �� 2�ʵ���  
      Draw_Number(x + objects[index]->size[0] / 2 - NumLen(objects[index]->hp[1]) / 2, y - 1, objects[index]->hp[1]);   //���� �Ӹ����� hp�߰��� 
   
   if (character.attack == TRUE && CheckCollision(objects[index]->position, attack_position, objects[index]->size, attack_size)) {      //ĳ���Ͱ� ������ && ������ġ�� ĳ���� ���ݹ����� �浹���� 
      objects[index]->tick[0] = tick;      //���� hp tick�� tick�� �������Ƿ� 2�ʵ��� �Ӹ����� hp�� 
      objects[index]->hp[1] -= character.power;
      objects[index]->accel[1] = - 0.55;      //y���ӵ� : ���߿� ���� �� 
      
      //x ���ӵ� : ������ ���� �з���  
      if (EnemyPosition(x,  objects[index]->size[0]))      //���Ͱ� ������ ��ġ��  
         objects[index]->accel[0] = -0.75;      
      else                                    //���� ������ ��ġ�� 
         objects[index]->accel[0] = 0.75;
   }
   //���� ��ų1 ���� �ǰ� ���� 
   if (character.skill_attack1 == TRUE && character.direction == FALSE && CheckCollision(objects[index]->position, skill1_left_position, objects[index]->size, skill1_left_size))
   {
      objects[index]->tick[0] = tick;
      objects[index]->hp[1] -= 5;
      //���� �ణ �� 
      objects[index]->accel[1] = - 0.55;
      //���� �ణ �з��� 
      objects[index]->accel[0] = -0.75;
   }
   //������ ��ų1 ���� �ǰ� ����
   if (character.skill_attack1 == TRUE && character.direction == TRUE && CheckCollision(objects[index]->position, skill1_right_position, objects[index]->size, skill1_right_size))
   {
      objects[index]->tick[0] = tick;
      objects[index]->hp[1] -= 10;
      
      objects[index]->accel[1] = - 0.55;
      objects[index]->accel[0] = 0.75;
   }
   //������ ��ų ���� �ǰ� ���� 
   if (character.skill_attack2 == TRUE && CheckCollision(objects[index]->position, skill2_position, objects[index]->size, skill2_size))
   {
      objects[index]->tick[0] = tick;
      objects[index]->hp[1] -= 20;
      
      objects[index]->accel[1] = - 0.55;
      objects[index]->accel[0] = -0.75;
   
   }
   //kind == 100 : ������
   if (objects[index]->kind == 100) {
      
      //��ǰ��� ���� ������ ��� �ٸ��� �׸��� ���ؼ� 
      if (y + objects[index]->size[1] == FLOOR_Y)
         objects[index]->isJumping = 0;   //�������� ���� �پ������� isJumping = 0 
      else 
         objects[index]->isJumping = 1;

      //������ ������ ���� 
      if (objects[index]->tick[1] + objects[index]->tick[2] < tick) {
         objects[index]->tick[1] = tick;
         objects[index]->tick[2] = 1000 + rand()%2000;   //if���� 1��+(0~2��)�� �ѹ��� ����. ���� �� �������� 0~3�ʿ� �ѹ��� ������ 
         
         //������ y���ӵ� ����(����) 
         objects[index]->accel[1] = - 0.75;
         //������ x���ӵ� ����(x�� �̵�) 
         if (EnemyPosition(x,  objects[index]->size[0]))
            objects[index]->accel[0] = 1.5;
         else
            objects[index]->accel[0] = -1.5;
      }
      
      //�����Ӱ� ĳ���� �浹 
      if (character.tick[3] == 0 && CheckCollision(objects[index]->position,character.position, objects[index]->size, character.size)) { //ĳ������ �ǰݽ� ���� tick ==0 �̰� ���Ϳ� �浹�� ���� 
         character.tick[3] = 100;   //ĳ������ �ǰݽ� ���� tick = 100    (100���� 1�� �پ��. 0���� �ٽ� �پ���� �ٽ� �ǰ����� ����)
         character.hp[1] -= 10;
      }
      
      Draw_Figure(x, y, objects[index]->size[0], objects[index]->size[1], figure_enemy1[objects[index]->isJumping]);
      MovementControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
   }
   
   //�Ź̺��� : kind 400    (���⿡ ��ų�� ������Ʈ �Ҵ��ϸ� �ɵ�)
   if(objects[index] -> kind == 400)
   {
      if (character.tick[3] == 0 && CheckCollision(objects[index]->position,character.position, objects[index]->size, character.size)) { //ĳ������ �ǰݽ� ���� tick ==0 �̰� ���Ϳ� �浹�� ���� 
         character.tick[3] = 100;   //ĳ������ �ǰݽ� ���� tick = 100    (100���� 1�� �پ��. 0���� �ٽ� �پ���� �ٽ� �ǰ����� ����)
         character.hp[1] -= 30;
      }
    //�Ź��� �� �Ź̺��� �׸��� 
	Draw_Figure(45, 1, 1, 20, "||||||||||||||||||||||||||||||");
    Draw_Figure(47, 1, 1, 19, "|||||||||||||||||||||||||||||");
    Draw_Figure(46, 20, 1, 1, "/");
    Draw_Figure(7, 9, 1, 14, "|||||||||||||||||||");
    Draw_Figure(9, 9, 1, 13, "||||||||||||||||||");
    Draw_Figure(8, 22, 1, 1, "/");
	Draw_Figure(22, 9, 1, 18, "||||||||||||||||||||||||||||");
	Draw_Figure(23, 26, 2, 1, "__"); 				    
	Draw_Figure(24, 9, 1, 18, "||||||||||||||||||||||||||||");      
    Draw_Figure(x,y,objects[index]->size[0],objects[index]->size[1],figure_spider);
   }
   
   //�Ƽ��󺸽� : kind 401    (���⿡ ��ų�� ������Ʈ �Ҵ��ϸ� �ɵ�)
    if(objects[index] -> kind == 401)
   {
   	
    if (character.tick[3] == 0 && CheckCollision(objects[index]->position,character.position, objects[index]->size, character.size)) { //ĳ������ �ǰݽ� ���� tick ==0 �̰� ���Ϳ� �浹�� ���� 
         character.tick[3] = 100;   //ĳ������ �ǰݽ� ���� tick = 100    (100���� 1�� �پ��. 0���� �ٽ� �پ���� �ٽ� �ǰ����� ����)
         character.hp[1] -= 50;
      	}
	
    Draw_Figure(x,y,objects[index]->size[0],objects[index]->size[1],figure_asura);
   } 
   
}

void Control_Particle(int index) {    
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int money_size[2] = {2, 2};
   int money_position[2] = {x, y - 1};
   int number = rand() % 3;
   
   
   //���� 
   if (objects[index]->kind == 200) { 
      if (objects[index]->tick[1] < tick) {
         objects[index]->tick[1] = tick * 2;      //if���� ��� ����Ǹ� ���ӵ����� ��� �ʱ�ȭ �ǹǷ� ������ ������ �ϰԉ�... ���� �ٽ� ���� �ȵǵ��� tick�� ���� 
         objects[index]->accel[0] =  number;   //���� �ߴ� x��ġ ���ݾ� �����ϰ� 
         objects[index]->accel[1] =  -3;         //������ ���� ���ٰ� ���������� 
      }
      
      if (CheckCollision(money_position, character.position, money_size, character.size)) {
         character.score += 100; 
         
         Remove_Object(index);
         return;
      }
      
      EditMap(x, y - 1, '@');
   }
   //���� �߷� 
   MovementControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void Control_Object() {   //��� ������Ʈ ��Ʈ�� �Լ� 
   for(int i = 0; i < OBJECT_MAX; i++) {
      if (objects[i]) {
         if (objects[i]->kind < 100)   //0~99�� ������ 
            Control_Item(i);
         else if (objects[i]->kind == 200)   //200�� ���� 
            Control_Particle(i);
         else
            Control_Enemy(i);      //�������� ��(������,����,������ų������Ʈ)
      }
   }
}

void Remove_Object(int index) {      //object[index] �޸� ���� �� NULL�� �ʱ�ȭ : �ٸ� ������Ʈ�� ���� ũ�� ����� ���� 
   free(objects[index]);
    objects[index] = 0;
}

void textcolor(int foreground, int background) { 
   int color=foreground+background*16; 
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}
