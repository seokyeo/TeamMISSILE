
#include <iostream>
#include <math.h>
#include <windows.h>

#define MAP_X_MAX 130
#define MAP_Y_MAX 32
#define FALSE 0
#define TRUE 1

using namespace std;

class ConsoleSet		//콘솔창 설정 클래스. Console::SetCon 
{
	public : 
		ConsoleSet() //생성자를 통해 콘솔창 설정 
		{			
			system("mode con:cols=130 lines=32");	//콘솔창의 가로 세로 크기를 맵과 동일하게 설정 
			system("title Team Missile");
				
			HANDLE hConsole;
		    CONSOLE_CURSOR_INFO ConsoleCursor;
		    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			    
		    ConsoleCursor.bVisible = 0;		//커서 안보이게 
		    ConsoleCursor.dwSize = 1;		//커서 백분율 크기 1로 
		    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
		}
		
		static void gotoxy(short m_x, short m_y) 		//ConsloeSet::형식으로 쓸수 있도록 static 함수로 선언 
		{//커서이동함수
        COORD Cur;
        Cur.X = m_x;
        Cur.Y = m_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    	}
};

class Character
{    
    private : 
		int x;		//캐릭터가 출력될 x좌표
    	int y;		//캐릭터가 출력될 y좌표
    	int size_x;		//캐릭터를 출력할 3*3크기 
		int size_y;
    	char figure[10];		//캐릭터 생김새 배열 (3*3크기 출력될 예정) 
    
    	bool direction;			//true=우측이동 , false=좌측이동 
    
	    float t_jump;
	    int leg_m;				//leg motion
	    unsigned int t_leg;
	
	public :
		Character()		//생성자로 초기값 설정 
		{
			x = MAP_X_MAX / 2 + 1;
			y = MAP_Y_MAX / 2 + 1;
			size_x = 3;
			size_y = 3;
			
			//초기 캐릭터 모양 (3*3) 
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
			 
			if (GetAsyncKeyState(VK_LEFT) && x > 1) 		//kbhit하고 switch문으로도 해봤지만 뭔가 느림 
			{												//키가 안눌렸을 때만  GetAsyncKeyState 0을 리턴. 
				x -= 1;		//캐릭터의 출력 x좌표를 1 줄임 
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
					t_jump += 0.3;
					
				y += floor(t_jump);		//floor는 내림함수 
				
				if (y > 19)
					y = 19;
			} 
			else 
			{
				
				t_jump = 0;
				y = 19;
			}
		
			if (direction == TRUE) 		//캐릭터가 우측방향을 보고있으면 
			{	
				figure[3] = '('; figure[5] = 'o';		//몸통부분 돌리기  	
			} 
			else 					//캐릭터가 왼쪽방향을 보고있으면 
			{	
				figure[3] = 'o'; figure[5] = ')';	 	//몸통부분 돌리기 
			}
			
		}
		
		//private영역에 있는 변수들 리턴 
		int GetX(){return x;}
		int GetY(){return y;}
		int GetSizeX(){return size_x;}
		int GetSizeY(){return size_y;}
		char* Getfigure(){return figure;}
};

class Map
{	
	private :
		char ground[MAP_X_MAX];						//땅을 표현할 일차원 배열 
		char mapData[MAP_X_MAX * MAP_Y_MAX];		//1차원 배열을 가로크기MAP_X_MAX * 세로크기 MAP_Y_MAX로 표현. mapData를 지속적으로 출력함으로써 게임 움직임 구현. 
				//주의점 : 콘송창 크기를 동일하게 배열의 크기와 동일하게 해야만 제대로 된 모양으로 출력됌. 
	public :
		Map()
		{	
			fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);		//생성자로 mapData배열을 공백' '으로 초기화 
			fillArray(ground, '=', MAP_X_MAX);			//생성자로 ground배열을 '='로 초기화 
		}
		
		void fillArray(char arr[], char c, int max_value) 	//배열의 str[0]~str[max_value]을 문자 c로 채우는 함수 
		{	
			for (int i = 0; i < max_value; i++)
				arr[i] = c;
		}
		
		void EditMap(int x, int y, char str) 		//콘솔창의 x,y좌표를 str로 수정하는 함수.  콘솔창의 좌측최상단이 (1,1)임. 
		{
			if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)		//mapData는 (MAP_X_MAX*MAP_Y_MAX)사이즈 
			mapData[(y - 1) * MAP_X_MAX + x - 1] = str;						//(y-1)*MAP_X_MAX를 하면 콘솔창의 y번째 열을 나타낼 수 있음. 거기에 x-1를 더하면 (x,y)를 나타냄. 
																			//콘솔창의 (1,1)좌표 = 콘솔창의 좌측최상단 = mapData[0]을 의미
																			//ex)  EditMap(1,1,'@')를 하면 콘솔창 좌측최상단에 @를 그림.
		}
		
		void MakeGround() //땅 배열 ground를 mapData에 반영함으로써 땅 그리기 
		{	
			//땅 
			Drawfigure(1, 22, MAP_X_MAX, 1, ground);
			//상점 병원(네모박스) 
			Drawfigure(1,10, 40, 1, ground); 
			Drawfigure(20, 10, 1, 12, ground); 
			Drawfigure(40, 10, 1, 12, ground);
			DrawMap(94,32, "IT정보공학과 미사일 팀 <교수의 모험>");
			//조작법 
			DrawMap(1,24,  "조작법"); 
    		DrawMap(10, 25, "   △    : Jump           Space : 대화");     
    		DrawMap(10, 27, "◁    ▷ : Left / Right");     
       		DrawMap(10, 29, "   ▽    : Next");
       		//구름
       		DrawMap(1, 5, "   · · · ·                · · · ·           · · · ·              · · · ·            · · ·"); 
			DrawMap(1, 6, " · · · · · ·          · · · · ·        · · · · · ·        · · · · ·         · · · ·");  
			DrawMap(1, 7, "   · · · ·                · ·  · ·          · · · ·              · · · ·            · · ·");
			//골드 
			DrawMap(116, 2, "Gold: ");
			//가방
			DrawMap(120, 5, "가방: Tab"); 
			//21줄 횡스크
			DrawMap(1, 11, "상점");
			DrawMap(21, 11, "병원"); 
			DrawMap(70, 21, "꽃     ▦▦▦(보물상자)     나무        ?쓰러진 행인"); //겹칩 따라서 캐릭터 모션부분은 따로 롤 
		}
		
		void DrawMap(int x, int y, char str[])
		{
			for(int i=0; i<strlen(str); i++)
			EditMap(x+i, y, str[i]);	
		}
		
		void Drawfigure(int x, int y, int size_x, int size_y, char figure[])	//EditMap함수를 for문 처리해서 x,y좌표를 넣으면 해당 좌표를 기준으로 size_x,size_y크기의 맵을 수정 
		{														//캐릭터 크기가 size_x,size_y임. 
			for (int i = 0; i < size_y; i++)	//size_y개 열을 수정 
			{
				for (int j = 0; j < size_x; j++)	//size_x개 행을 수정 
					EditMap(x + j, y + i, figure[i * size_x + j]);		//i*size_x는 1행,2행,3행을 표현. j는 열을 표현. 
			}
		}
		
		char* GetMapData(){return mapData;}		//private영역의 변수 리턴. 
		
		void printMap()
		{
			cout<<mapData;				//맵 출력 
		}
};

class GamePlay
{
	public : 
		GamePlay()
		{	
			Character Song;
			Map m1;
			
			while(TRUE)
			{
			ConsoleSet::gotoxy(0,0);
			m1.fillArray(m1.GetMapData(), ' ', MAP_X_MAX * MAP_Y_MAX);	//맵을 공백으로 초기화 시켜줌  
			Song.ControlCharacter();		//캐릭터 움직임 
			m1.Drawfigure(Song.GetX(), Song.GetY(), Song.GetSizeX(), Song.GetSizeY(),Song.Getfigure());		//맵에 Song캐릭터 그리기 
			m1.MakeGround();		//땅 다시 맵에 반영해주기. 왜냐하면 위에서 반복적으로 맵 전체를 공백으로 초기화 하므로!
			m1.printMap();
			
			Sleep(33);	//움직임이 너무 빨라서 딜레이 주기.
			}
		}
};

int main() {

	ConsoleSet();	//콘솔창 설정 생성자 호출 
	GamePlay();
	
	return 0;
}

