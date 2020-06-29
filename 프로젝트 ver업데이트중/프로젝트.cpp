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

