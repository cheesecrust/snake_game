#include "map.h"

Map::Map(Snake snake, int stage)
{
    srand(time(NULL));
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    resize_term(40, 70);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(6, COLOR_RED, COLOR_RED);
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);

    switch (stage)
    {
    case 1:
        for (int i = 0; i < SIZE; i++)
        { // 변
            arr[i][0] = 1;
            arr[0][i] = 1;
            arr[i][SIZE - 1] = 1;
            arr[SIZE - 1][i] = 1;
        }

        for (int i = 0; i < SIZE; i++)
        { // 변
            arr[i][SIZE] = 1;
            arr[SIZE][i] = 1;
        }

        arr[0][0] = 2; // 모서리
        arr[0][SIZE - 1] = 2;
        arr[SIZE - 1][0] = 2;
        arr[SIZE - 1][SIZE - 1] = 2;

        //초기 위치
        arr[snake.getHeady()][snake.getHeadx()] = 3; // 뱀 머리
        for (int i = 1; i <= 2; i++)
            arr[snake.getHeady()][snake.getHeadx() + 1] = 4; // 뱀 몸통
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    default:
        break;
    }
}

void Map::draw(WINDOW *win1) const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (arr[i][j] >= 1 && arr[i][j] <= 4)
            {
                wattron(win1, COLOR_PAIR(2));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(2));
            }
            else if (arr[i][j] == 0)
            {
                wattron(win1, COLOR_PAIR(1));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(1));
            }
            else if (arr[i][j] == 5)
            {
                wattron(win1, COLOR_PAIR(5));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(5));
            }
            else if (arr[i][j] == 6)
            {
                wattron(win1, COLOR_PAIR(6));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(6));
            }
            else if (arr[i][j] == 7)
            {
                wattron(win1, COLOR_PAIR(7));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(7));
            }
        }
    }
}