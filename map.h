#include "snake.h"
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

class Map
{
  public:
    int arr[SIZE + 1][SIZE + 1];

    Map(Snake snake, int stage);
    void draw(WINDOW *win1) const;
};