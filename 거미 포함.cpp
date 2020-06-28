#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define FALSE 0
#define TRUE 1
#define MAP_X_MAX 116
#define MAP_Y_MAX 36
#define FLOOR_Y 32
#define OBJECT_MAX 32
#define SPAWN_TIME 15000

typedef struct _Character {
    int position[2], size[2];   //position[0]�� x��ǥ, position[1]�� y��ǥ ,  size[0]�� size_x, size[1]�� size_y 
    float accel[2], flyTime;   //accel[0]: �뽬�� ���ӵ�  accel[1]: ������ ���ӵ�  and flotation time
    bool direction;            //true=�����ʹ��� , false=���ʹ��� 
    //status 
    char name[16];
    int lv, exp[2], score, hp[2], mp[2];   //[0]=�ִ밪 , [1]=���簪 
    int power, weapon;
    //animation control
    bool attack;            //Ű���� z�� ������ attack = TRUE, �ƴϸ� FALSE 
    int tick[4];            //tick : ������(�ð�����) ����  [0]: ���� tick [1]: ���� tick, [2] : �뽬 tick, [3] : �ǰݽ� ���� tick
}Character;

typedef struct _Object {   //enemies, projectiles, particles, etc.
    int position[2], size[2];
    float accel[2], flyTime;
    bool direction;

    int kind;   //1~99: items, 100~199: enemies, 200~: projectiles, particles
    int hp[2], exp;   //hp: this value is used randomly for item or particle object
    int dam;
    
    int motion[3];   //motion
    int tick[4];   //0: hpshow time(enemy) or active time(projecticles, particles)
}Object;

Character character = {{MAP_X_MAX / 2, MAP_Y_MAX / 2}, {3, 3}, {0, 0}, 0, TRUE, "", 1, {100, 0}, 0, {100, 100}, {50, 50}, 10, 0, FALSE,{0, 1, 0, 0}};
Object **objects;

int tick = 0;                     //tick 
int spon_tick = 0;                  //���� ������ tick 
char sprite_floor[MAP_X_MAX];         //����� �迭 
char mapData[MAP_X_MAX * MAP_Y_MAX];   //�ܼ�â ũ���� �迭 

//�� �ɷ�ġ hp, exp, size(x y), tick (2 3 4)
const int stat_enemy[2][7] =
 {{150, 30, 4, 3, 0, 1000, 0},   //���� kind�� 100�����ϰ� stat_enemy[kind-100][]�ϸ� �� �ɷ�ġ 
  {300, 50, 5, 5, 0, 500, 0}};   //���� kind�� 101�� �ϰ�  stat_enemy[kind-100][]�ϸ� �� �ɷ�ġ

const int stat_weapon[3] = {5, 10, 15};
//ĳ���� ��� �迭 (3*3) 
const char sprite_character[10] = " 0  | a^a";
const char sprite_normalAttack[2][3][16] = 
{{" .- o          ", " .   (   o \'   ", "         o \'-  "},      //���� ���� 
 {"o -.           ", "   . o   )   \' ", "     o      -\' "}};      //������ ���� 

//����ִ� ���� ��� 
const char sprite_weapon[2][3][4] = 
{{"---", "--+", "<=+"},
 {"---", "+--", "+=>"}};

//����â �ڽ��� ������ 
const char sprite_invenWeapon[3][11] = {"   /   /  ", "   /  '*. ", "  |   \"+\" "};  

//���� ��� 
const char sprite_enemy1[2][13] = {" __ (**)----", " __ [  ]\'--\'"};

void StartGame();   //�ʱ� ���� 
void UpdateGame();   //�������� mapData ������Ʈ �� ��� 
void ExitGame();   //objects �����޸� ����  
void SetConsole();   //�ܼ�â ����  
void ControlUI();  //��� : ���׸���, ���ʻ�� ����â �׸��� �� ����
void ControlCharacter();
void ControlObject();   //��� ������Ʈ ��Ʈ�� �Լ�
void ControlItem(int index);
void ControlEnemy(int index);
void ControlParticle(int index);
void CreateObject(int x, int y, int kind);      //x,y��ǥ�� kind���� ���� ������Ʈ ���� (1~99: ������, 100~199: ����, 200~299: ����)
void RemoveObject(int index);      //object[index] �޸� ���� �� NULL�� �ʱ�ȭ : �ٸ� ������Ʈ�� ���� ũ�� ����� ���� 
bool EnemyPosition(int x, int size_x);   //ĳ������ ��ġ�� ������ ��ġ�� ��.  ĳ���Ͱ� ���ʿ� ������ FALSE, �����ʿ� ������ TRUE  
bool CollisionCheck(int position1[], int position2[], int size1[], int size2[]);   //�浹 üũ �Լ� : position1[]�� size1[]ũ�Ⱑ position2[]�� size2[]ũ��� �浹�� ���� TRUE  
void MoveControl(int position[], float accel[], int size[], float *flyTime);   // motion control
void DrawBox(int x, int y, int size_x, int size_y);   //����â�� ���� �׸��� �Լ� (x,y)�� size_x*size_yũ���� ���� �׸�
void DrawNumber(int x, int y, int num);   //(x,y)��  char������ ��ȯ�� ���ڸ� �׸�
void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]);   //(x,y)�� �������� size_x*size_yũ��� spr[]�� �׸�    //���� // ���� 
void FillMap(char str[], char str_s, int max_value);   //str�迭�� ���� str_s�� max_value��ŭ ä�� 
void EditMap(int x, int y, char str);   //(x,y)�� ����str�� ���� 
int NumLen(int num);   //num�� �ڸ����� �����ϴ� �Լ� (DrawNumber�Ҷ� �ʿ�)

char sprite_spider[] ={"|                | |      ##      |  --    {  }    --    |  {    }  |      |-{  --  }-|        { ---- }     |  --{ ---- }--  | -/  {  --  }  \\-     / {    } \\       / { 0000 } \\     -   { 00 }   -   |  /{      }\\  | |  |  \\()()/  |  |"};

int main() {
   StartGame();
   
   while (TRUE) {
      if (tick +30 < GetTickCount()) {   //30ms�� �ѹ��� updategame�ǵ��� ����   
         tick = GetTickCount();         //��ǻ�� ���� �� ����� �ð��� ms�� ��ȯ. ���� tick�� 1�ʿ� 1000�� ������ 
         
         UpdateGame();
         
         if (tick == 0)               //character�� hp[1]�� 1�̸��� �Ǹ� tick = 0 
            break;
      }
   }
   
   ExitGame();
   return 0;
}

void StartGame() {
   SetConsole();         //�ܼ�â ���� ���� ũ�� ����, Ŀ�� �Ⱥ��̰� ���� 
   srand((int)time(NULL));
   
   printf("�̸��� �Է��ϼ��� : ");
   scanf("%s", character.name);
   
   FillMap(sprite_floor, '=', MAP_X_MAX);   //���迭�� '=' ä��� 
   
   objects = (Object **)malloc(sizeof(Object *) * OBJECT_MAX);      //OBJECT_MAX���� object������ ���� �Ҵ�  
   memset(objects, 0, sizeof(Object *) * OBJECT_MAX);             //objects�� ����Ű�� ���� sizeof(object*)*OBJECT_MAX ũ�⸸ŭ 0���� �ʱ�ȭ 
}

void UpdateGame() {
   FillMap(mapData, ' ', MAP_X_MAX * MAP_Y_MAX);   //���� �������� �ʱ�ȭ 
   
   ControlCharacter();   //mapData�� ĳ���� ���� ������Ʈ 
   ControlObject();   //mapData�� ��,����,������ �� ������Ʈ
   ControlUI();      //���迭 �� ����â ������Ʈ  
   
   if (spon_tick + SPAWN_TIME < tick) {      //15�ʸ��� ���� ���� 
      spon_tick = tick;
      CreateObject(rand() % 90, 5, 100);      //(x: 0~90 , y:5) kind = 100 : ����    
      CreateObject(rand() % 90, 5, 100);
      CreateObject(rand() % 90, 5, 100);
   }
   
   DrawSprite(60, 2, 18,  13, sprite_spider);
   
   printf("%s",mapData);   //draw mapData
}

void ExitGame() {   //objects �����޸� ����  
    for (int i = 0; i < OBJECT_MAX; i++) {
        if (objects[i])
            free(objects[i]);
    }
    
    free(objects);
}

void SetConsole() {
   system("mode con:cols=116 lines=36");
   system("title RPG test");
   
   HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

void ControlUI()    //��� : ���׸���, ���ʻ�� ����â �׸��� �� ���� 
{
   int expPer = roundf(character.exp[1] * 100 / character.exp[0]);      //roundf�� �ݿø��Լ�    exp[1]�� ���� exp, exp[0]�� �ִ�exp(������) 
   int len;   //length of previous sprite
   
   DrawSprite(1, FLOOR_Y, MAP_X_MAX, 1, sprite_floor);   //draw floor
   
   DrawBox(1, 2, 35, 8); DrawBox(27, 5, 7, 4);   //draw weaponinven
   DrawSprite(28, 6, 5, 2, sprite_invenWeapon[character.weapon]);      //character.weapon�� 0,1,2�� ���� ���� ��� �迭 ��Ÿ�� 
   DrawSprite(28, 4, 6, 1, "Weapon");
   
   EditMap(3, 3, '\"');   //draw name, lv, exp
   DrawSprite(4, 3, strlen(character.name), 1, character.name);   len = 4 + strlen(character.name);//len�� x��ǥ�� ��Ÿ��. �� ���ڿ� ���̸�ŭ len++��Ű�鼭 ���ڿ��� �˸��� ��ġ�� ��� 
   DrawSprite(len, 3, 7, 1, "\" LV.");   len += 5;
   DrawNumber(len, 3, character.lv);   len += NumLen(character.lv);
   DrawSprite(len, 3, 2, 1, " (");   len += 2;
   
   if (!expPer) {   //����ġ 0%�� 
      EditMap(len, 3, '0');   len ++;       
   } else {
      DrawNumber(len, 3, expPer);   len += NumLen(expPer);
   }
   DrawSprite(len, 3, 2, 1, "%)");
   
   DrawSprite(MAP_X_MAX - NumLen(character.score) - 7, 3, 6, 1, "SCORE:");   //draw score
   DrawNumber(MAP_X_MAX - NumLen(character.score), 3, character.score);
   
   DrawSprite(4, 5, 3, 1, "HP:");   //draw HP
   DrawNumber(8, 5, character.hp[1]);
   EditMap(9 + NumLen(character.hp[1]), 5, '/');
   DrawNumber(11 + NumLen(character.hp[1]), 5, character.hp[0]);
   
   DrawSprite(4, 6, 3, 1, "MP:");   //draw MP
   DrawNumber(8, 6, character.mp[1]);
   EditMap(9 + NumLen(character.mp[1]), 6, '/');
   DrawNumber(11 + NumLen(character.mp[1]), 6, character.mp[0]);
   
   DrawSprite(4, 8, 6, 1, "Power:");   //draw power
   DrawNumber(11, 8, character.power);
}

void ControlCharacter()
{   
   character.attack = FALSE;   //���ݺ����� �ʱ�ȭ (���� �� ���ݸ�ǿ��� �ȵ��ƿ�)
    
   //LV up            exp[1]�� ���� exp, exp[0]�� Max exp 
   if (character.exp[1] >= character.exp[0]) {
      character.hp[0] += 10; character.mp[0] += 5; character.power ++;
      character.lv ++; character.exp[1] = 0; character.exp[0] += character.lv * 10;
   }
   //hp,mp gen & control         0.9�ʸ��� ��ȸ��  
   if (character.tick[0] + 900 < tick) { 
      character.tick[0] = tick;
      character.hp[1] += 1;      //
      character.mp[1] += 1;
   }
   if (character.hp[1] > character.hp[0])      //�ִ� hp,mp�� �ʰ��Ϸ��ϸ� �ִ밪���� ����  
      character.hp[1] = character.hp[0];
   if (character.mp[1] > character.mp[0])
      character.mp[1] = character.mp[0];

   //���� ���� ����    
   if (character.hp[1] < 1)
      tick = 0;         //tick = 0�̵Ǹ� main�Լ����� while���� Ż���ؼ� ���� ������ �Ǿ����� 
 
    //������ 
   if (character.tick[3] > 0)      //���Ϳ� �浹�� ���� character.tick[3] = 100�� ��. 
      character.tick[3] -= 1;
   
   //���� ������ 
   if (GetAsyncKeyState(0x5A) && character.tick[1] + 150 <= tick ) {   // 0x5A�� Z�� �ƽ�Ű�ڵ尪    ���ݵ����� 250ms 
      character.tick[1] = tick;
      character.attack = TRUE;
   }

   //�����ӱ����� 
   if (GetAsyncKeyState(VK_LEFT) && character.position[0] > 1) {   //���� ȭ��ǥ ������ x>1�̸� �����̵� 
         character.position[0]--;
         character.direction = FALSE;   //�������� 
      }
      
   if (GetAsyncKeyState(VK_RIGHT) && character.position[0] < MAP_X_MAX - 2) {   //������ ȭ��ǥ ������ x�� �ʿ���������-2�������� ������ 
         character.position[0]++;
         character.direction = TRUE;      //�������� 
      }
      
   if (GetAsyncKeyState(0x58) && character.tick[2] + 1200 <= tick) {   //dash      0x58�� X�� �ƽ�Ű�ڵ尪    1.2�ʿ� �ѹ� ��� ���� 
         character.accel[0] = character.direction * 6 - 3;   //character.accel[0]�� ���ʹ��� �뽬��  -9, ������ ���� �뽬��  +3  
         character.tick[2] = tick;
      }
      
   if (GetAsyncKeyState(VK_UP) && character.position[1] + 3 == FLOOR_Y)   //jump
         character.accel[1] = -1.75;
   
   MoveControl(character.position, character.accel, character.size, &character.flyTime);   // control character movement  �߷±��� 
   
   //ĳ���� �׸��� �κ� 
   if (character.tick[3] % 2 == 0) {      //����tick�� ¦���� (����tick�� 100���� 1�� ��� �پ��. ���� ĳ���Ͱ� �����̰� ��)
      DrawSprite(character.position[0], character.position[1], character.size[0], character.size[1], sprite_character);   //ĳ���� �׸� 
      
      
      if (character.direction) {//�����ʹ����̸� ���� ���������� 
         EditMap(character.position[0], character.position[1] + 1, '(');
      } else {              //���ʹ����̸�  ���� �������� 
         EditMap(character.position[0] + 2, character.position[1] + 1, ')');
      }
      
      if (character.accel[0] > 1)  //xŰ�� ������(dash) ������ ������ �����ִ� ���- ĳ���� ���ʿ� ������ȿ��   
         DrawSprite(character.position[0] - 2, character.position[1], 1, 3, "===");
      if (character.accel[0] < -1) //xŰ�� ������(dash) ���� ������ �����ִ� ��� - ĳ���� �����ʿ� ������ȿ�� 
         DrawSprite(character.position[0] + 4, character.position[1], 1, 3, "===");
      
      //���ݸ�� �׸��� �κ�  
      if (character.attack==TRUE ) {
               EditMap(character.position[0] - 2 + 6 * character.direction, character.position[1] + 1, 'o');
               DrawSprite(character.position[0] - 5 + 10 * character.direction, character.position[1] + 1, 3, 1, sprite_weapon[character.direction][character.weapon]);
            } 
      else {
               EditMap(character.position[0] + 2 * character.direction, character.position[1] + 1, 'o');
               DrawSprite(character.position[0] - 3 + 6 * character.direction, character.position[1] + 1, 3, 1, sprite_weapon[character.direction][character.weapon]);
            }
   }      
}

void ControlItem(int index) {
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int item_position[2] = {x, y - 2};
   int item_size[2] = {5, 2};
   
   if (objects[index]->tick[1] < tick) {
      objects[index]->tick[1] = tick * 2;
      objects[index]->accel[0] =  1 - 2 * objects[index]->hp[0] / (float)RAND_MAX;
      objects[index]->accel[1] =  - 2 * objects[index]->hp[1] / (float)RAND_MAX;
   }
   
   if (CollisionCheck(item_position, character.position, item_size, character.size)) {      //�����۰� ĳ���Ͱ� �浹�� ���� 
      DrawSprite(x + 1, y - 5, 3, 1, "[E]");      //�Ӹ� ���� [E] ǥ��  
      
      if (GetAsyncKeyState(0x45)) {      //EŰ�� ������ 
         character.weapon = objects[index]->kind;
      
         RemoveObject(index);
         return;
      }   
   }
   
   DrawSprite(x, y - 2, 5, 2, sprite_invenWeapon[objects[index]->kind]);

   
   MoveControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void ControlEnemy(int index) {
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int attack_position[2] = {character.position[0] - 5 + 8 * character.direction, character.position[1]}, at_size[2] = {5, 3};      //ĳ���� ���� ���� 5*3ũ�� 
   int item_code = rand() % 100;
   
   if (objects[index]->hp[1] < 1) {   //���Ͱ� ������ 
      for (int i = 0; i < 3; i++)      //���� 3�� ������ 
         CreateObject(x + objects[index]->size[0] / 2, y + objects[index]->size[1] / 2, objects[index]->kind + 100);   //���Ϳ��ٸ� kind�� 100~199�̹Ƿ� +100�ϸ� 200�� �Ѿ ���� 
      
      //item_code�� 90�̻��̰ų� 3�����̸� ������ ��������   
      if (item_code >= 90)
         CreateObject(x + objects[index]->size[0] / 2 - 2, y, 1);   //1������ 
         
      if (item_code <= 3)
         CreateObject(x + objects[index]->size[0] / 2 - 2, y, 2);   //2������  
         
      character.exp[1] += objects[index]->exp;
      
      RemoveObject(index);
      return;
   }
   
   if (objects[index]->tick[0] + 2000 > tick) //���Ͱ� ���ݹ��� �� 2�ʵ���  
      DrawNumber(x + objects[index]->size[0] / 2 - NumLen(objects[index]->hp[1]) / 2, y - 1, objects[index]->hp[1]);   //���� �Ӹ����� hp�߰��� 
   
   if (character.attack == TRUE && CollisionCheck(objects[index]->position, attack_position, objects[index]->size, at_size)) {      //ĳ���Ͱ� ������ && ������ġ�� ĳ���� ���ݹ����� �浹���� 
      objects[index]->tick[0] = tick;
      objects[index]->hp[1] -= character.power;
      objects[index]->accel[1] = - 0.55;
      
      if (EnemyPosition(x,  objects[index]->size[0]))      //���� ���ʿ� ĳ���Ͱ� ��ġ�� 
         objects[index]->accel[0] = -0.75;
      else                                    //���� �����ʿ� ĳ���Ͱ� ��ġ�� 
         objects[index]->accel[0] = 0.75;
   }
   //kide100 �����ӿ� ���ؼ� 
   if (objects[index]->kind == 100) {
      if (y + objects[index]->size[1] == FLOOR_Y)
         objects[index]->motion[0] = 0;
      else 
         objects[index]->motion[0] = 1;

      if (objects[index]->tick[1] + objects[index]->tick[2] < tick) {
         objects[index]->tick[1] = tick;
         objects[index]->tick[2] = 1000 + rand() % 1000;
         objects[index]->accel[1] = rand() / (float)RAND_MAX / 2 - 1.2;
         
         if (EnemyPosition(x,  objects[index]->size[0]))
            objects[index]->accel[0] = 2.4 - rand() / (float)RAND_MAX;
         else
            objects[index]->accel[0] = rand() / (float)RAND_MAX - 2.4;
      }
      
      if (character.tick[3] == 0 && CollisionCheck(objects[index]->position,character.position, objects[index]->size, character.size)) { //ĳ������ �ǰݽ� ���� tick ==0 �̰� ���Ϳ� �浹�� ���� 
         character.tick[3] = 100;   //ĳ������ �ǰݽ� ���� tick = 100    (100���� 1�� �پ��. 0���� �ٽ� �پ���� �ٽ� �ǰ����� ����)
         character.hp[1] -= 10;
      }
      
      DrawSprite(x, y, objects[index]->size[0], objects[index]->size[1], sprite_enemy1[objects[index]->motion[0]]);
   }
   
   MoveControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void ControlParticle(int index) {      //������������ �Լ� 
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int money_size[2] = {2, 2};
   int money_position[2] = {x, y - 1};
   
   if (objects[index]->kind == 200) {
      if (objects[index]->tick[1] < tick) {
         objects[index]->tick[1] = tick * 2;
         objects[index]->accel[0] =  2 - 4 * objects[index]->hp[0] / (float)RAND_MAX;
         objects[index]->accel[1] =  - 2 * objects[index]->hp[1] / (float)RAND_MAX;
      }
      
      if (CollisionCheck(money_position, character.position, money_size, character.size)) {
         character.score += 100;
         
         RemoveObject(index);
         return;
      }
      
      EditMap(x, y - 1, '@');
   }
   
   MoveControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void ControlObject() {   //��� ������Ʈ ��Ʈ�� �Լ� 
   for(int i = 0; i < OBJECT_MAX; i++) {
      if (objects[i]) {
         if (objects[i]->kind < 100)
            ControlItem(i);
         else if (objects[i]->kind > 99 && objects[i]->kind < 200)
            ControlEnemy(i);
         else
            ControlParticle(i);
      }
   }
}

void CreateObject(int x, int y, int kind) {      //x,y��ǥ�� kind���� ���� ������Ʈ ���� (1~99: ������, 100~199: ����, 200~299: ����)
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
    
    if (kind < 100 || kind > 199) {      //100�̸� 200�̻�  -->  ���;ƴ�  
       obj->hp[0] = rand();
      obj->hp[1] = rand();
      obj->tick[1] = 0;
       obj->tick[2] = 0;
       obj->tick[3] = 0;
   }
   
    if (kind >= 100 && kind < 200) {      //kind�� 100~199  -->  ����  
       obj->hp[0] = stat_enemy[kind - 100][0];      //���͸� �ϴ� kind100�� ���������� �س��� 
      obj->hp[1] = obj->hp[0];
       obj->exp = stat_enemy[kind - 100][1];
       obj->size[0] = stat_enemy[kind - 100][2];
      obj->size[1] = stat_enemy[kind - 100][3];
       obj->tick[1] = stat_enemy[kind - 100][4];
       obj->tick[2] = stat_enemy[kind - 100][5];
       obj->tick[3] = stat_enemy[kind - 100][6];
   }
}

void RemoveObject(int index) {      //object[index] �޸� ���� �� NULL�� �ʱ�ȭ : �ٸ� ������Ʈ�� ���� ũ�� ����� ���� 
   free(objects[index]);
    objects[index] = 0;
}

bool CollisionCheck(int position1[], int position2[], int size1[], int size2[]) {   //�浿 üũ �Լ� 
   if (position1[0] > position2[0] - size1[0] && position1[0] < position2[0] + size2[0]   //position2[0]-size1[0] = ���� ��������-ĳ���� ����ũ�� , position2[0]+size2[0] = ������ ���� ��
       && position1[1] > position2[1] - size1[1] && position1[1] < position2[1] + size2[1])   //y�� �浹 
      return TRUE;
   else
      return FALSE;
}

bool EnemyPosition(int x, int size_x) {      //ĳ������ �߾���  ������ �߾Ӻ��� �����̸� 
   if (character.position[0] + 1 < x + size_x / 2)
      return FALSE;      //������ ������ ���� 
   else
      return TRUE;      //�ƴ϶�� ������ 
}

//accel[0]�� ĳ���Ͱ� ���ʴ뽬���̸� -9, �����ʴ뽬���̸� 3, accel[1]�� ����Ű ������ -1.75  
void MoveControl(int position[], float accel[], int size[], float *flyTime) {
   float y_value = accel[1];
   
   if (position[1] + size[1] == FLOOR_Y) {
      *flyTime = 0;      //���� ��������� flyTime = 0 
   } else {            //������ ������ flyTime += 0.05 
      *flyTime += 0.05;
      accel[1] += *flyTime; 
   }
   
   if (y_value != 0) {
      if (position[1] + size[1] + y_value > FLOOR_Y)      //������ ������ �߶��ϴ°� ����  
         y_value = FLOOR_Y - position[1] - size[1];
   }

   position[0] += floor(accel[0] + 0.5); position[1] += y_value + 0.5;     
   
   //accel�� 0�̵Ǹ� �Ʒ� ������� ������ �ȉ�. 
   if (accel[0] > 0) accel[0] -= 0.2; if (accel[0] < 0) accel[0] += 0.2;
   if (accel[1] > 0) accel[1] -= 0.1; if (accel[1] < 0) accel[1] += 0.1;
}

void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]) {   //(x,y)�� �������� size_x*size_yũ��� spr[]�� �׸� 
   for (int i = 0; i < size_y; i++) {
      for (int n = 0; n < size_x; n++)
         EditMap(x + n, y + i, spr[i * size_x + n]);
   }
}

void FillMap(char str[], char str_s, int max_value) {   //str�迭�� ���� str_s�� max_value��ŭ ä�� 
   for (int i = 0; i < max_value; i++)
      str[i] = str_s;
}

void EditMap(int x, int y, char str) {   //(x,y)�� ����str�� ���� 
   if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)
      mapData[(y - 1) * MAP_X_MAX + x - 1] = str;
}

int NumLen(int num) {      //num�� �ڸ����� �����ϴ� �Լ� (DrawNumber�Ҷ� �ʿ�) 
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

void DrawNumber(int x, int y, int num) {      //(x,y)��  char������ ��ȯ�� ���ڸ� �׸� 
   int tmp = num, len = NumLen(tmp), index = len;
    char str[len];      //���� �ڸ���+1 ũ���� ���� �迭 (1�ڸ��� �ι���) 
    
    do {
        index--;
        str[index] = (char)(tmp % 10 + 48);
        tmp /= 10;
    } while(tmp != 0);
    
    DrawSprite(x, y, len, 1, str);
}

void DrawBox(int x, int y, int size_x, int size_y) {      //����â�� ���� �׸��� �Լ� (x,y)�� size_x*size_yũ���� ���� �׸� 
   EditMap(x, y, '.'); EditMap(x + size_x - 1, y, '.');
   EditMap(x, y + size_y - 1, '\''); EditMap(x + size_x - 1, y + size_y - 1, '\'');
   
   for (int i = 1; i < size_x - 1; i++) {
      EditMap(x + i, y, '-'); EditMap(x + i, y + size_y - 1, '-');
   }
   for (int i = 1; i < size_y - 1; i++) {
      EditMap(x, y + i, '|'); EditMap(x + size_x - 1, y + i, '|');
   }
}
