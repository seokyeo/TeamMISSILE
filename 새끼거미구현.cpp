char sprite_min_spider[] ={"      ---        || |   | ||   | ||00 00|| | | | | 0 0 | | || |  -----  | |  | |() ()| |   |  ||   ||  | |  | |   | |  |  | |     | |  "};
DrawSprite(60, 2, 15,  6, sprite_min_spider);

void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]) {   //(x,y)�� �������� size_x*size_yũ��� spr[]�� �׸� 
   for (int i = 0; i < size_y; i++) {
      for (int n = 0; n < size_x; n++)
         EditMap(x + n, y + i, spr[i * size_x + n]);
   }
}
