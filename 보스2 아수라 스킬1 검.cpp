

char sprite_sword[] ={"      =             =            ===          #####       ---------       |   |         | # |         | # |         | # |         | # |         | # |         | # |         | # |          | |            |       "};


void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]) {   //(x,y)�� �������� size_x*size_yũ��� spr[]�� �׸� 
   for (int i = 0; i < size_y; i++) {
      for (int n = 0; n < size_x; n++)
         EditMap(x + n, y + i, spr[i * size_x + n]);
   }
}

DrawSprite(60, 2, 14,  15, sprite_sword);
