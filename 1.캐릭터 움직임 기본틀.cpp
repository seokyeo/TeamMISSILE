#include <iostream>
#include <time.h>
#include <windows.h>
#define MAP_X_MAX 49
#define MAP_Y_MAX 17
using namespace std;
 
class Console	//�ܼ�â�� ���� ���� Ŭ���� 
{
	public:
		Console()	//�����ڷ� �ܼ�â �ʱ�ȭ 
		{
			system("title Name");		//Name�� ���߿� ���� ���� �̸� �ֱ� 
		    system("mode con:cols=49 lines=17");	//�� ũ�⸸ŭ �ܼ�â ũ�� ���� 
		    
		    HANDLE hConsole;
		    CONSOLE_CURSOR_INFO ConsoleCursor;
		    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		    
		    ConsoleCursor.bVisible = 0; //Ŀ�� �����  
		    ConsoleCursor.dwSize = 1;
		    
		    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
		    
		    COORD Pos = { 0, 0 };
	    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);	//Ŀ�� ��ġ�� 0,0���� ���� --> 0,0���� mapData[]�� ����ϱ� ���ؼ�  
		}
		static void xy(int x,int y)
		{
			COORD Pos = { x, y };
	    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);	//Ŀ�� ��ġ�� x,y���� ���� --> ���� : Console::xy(0,0) ;
		}
};

class Map
{
	private: char mapData[MAP_Y_MAX][MAP_X_MAX];		//�� ���� --- ȭ��ũ���� ���ڿ� 
			 
	public: 
			Map()	//�� �ʱ�ȭ ������ 
			{	
				for(int i = 0; i<MAP_Y_MAX; i++)
				{
					for(int j=0; j<MAP_X_MAX; j++)
					{
						mapData[i][j] = ' ';
					}
				}
			}
			void EditMap(int x, int y,char ch)	//�ܼ�â (x,y)��ǥ�� ����  str�� ���� 
			{
				if(x>0&& y>0 && x-1<MAP_X_MAX && y-1<MAP_Y_MAX)
				mapData[y-1][x-1] = ch;
			}
			void printMap()
			{	
				for (int i = 0; i < MAP_Y_MAX; i++)
					for(int j=0; j<MAP_X_MAX; j++)
						cout<<mapData[i][j];
			}
};

class character		//���� �̱��� ����. �׽�Ʈ�� 
{
	public: 
		
			char song[4][4]={
							{' ','@','@',' '},
							{'@','@','@','@'},
							{'@','@','@','@'},
							{' ','@','@',' '}
							};
	
};
int main() 
{
    
    Console();	//�ܼ�â ����  
    Map mainMap;	//���θ� ���� (Ⱦ��ũ�� �ϴ� ��) 
 	character s1;
 	
    int characterX = MAP_X_MAX / 2 + 1;
	int characterY = MAP_Y_MAX / 2 + 1;
    
    while(1) 
	{	
		
		
	
		Console::xy(0,0);			//�ٽ� Ŀ���� 0,0���� ����. ---> 0,0���� �ٽ� map�迭�� ����ϱ� ���ؼ�  
		mainMap.EditMap(characterX,characterY,' ');		//x,y�� �������� �ʱ�ȭ  --- �̰� �Ƚ��ָ� �ܻ��� ���ԉ�. 
	
        if(GetAsyncKeyState(0x25) != 0 && characterX > 1)		//https://m.blog.naver.com/power2845/50143021565  --> GetAsyncKeyState �����ڷ� 
            characterX -= 1;	//�� ȭ��ǥ �Է½�  
            
        if(GetAsyncKeyState(0x27) != 0 && characterX < MAP_X_MAX) 
            characterX += 1;
            
        if(GetAsyncKeyState(0x26) != 0 && characterY > 1)
            characterY -= 1;
            
        if(GetAsyncKeyState(0x28) != 0 && characterY < MAP_Y_MAX)
            characterY += 1;
             
		for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						mainMap.EditMap(characterX+j,characterY+i,s1.song[i][j]);	//�ʿ� ĳ���� �׸��� 
        
		mainMap.printMap();
		
		for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						mainMap.EditMap(characterX+j,characterY+i,' ');	//�ʿ� ĳ���� �׸��κ� �������� �ʱ�ȭ�ؼ� �ܻ� �����  
        
        Sleep(50); 		//�Է��� �ʹ� ������ ó���Ǹ� �ȵǹǷ� ������ ��. 
    }
}
//���� main�Լ��� �ִ� ĳ���� �����̴� GetAsyncKeyState�κ��� ���߿� characterŬ���� ���� �� controlcharacter����Լ���  �־��� ����. 
