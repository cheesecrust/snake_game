#include "snake.h"
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

class Map
{
  private:
    int success;
    int nowstage;

  public:
    int arr[SIZE + 1][SIZE + 1];

    Map(Snake snake, int stage);
    void draw(WINDOW *win1, Snake snake, int t) const;

    int getSuccess() const;
};