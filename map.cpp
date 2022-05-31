#include "map.h"

Map::Map(Snake snake, int stage)
{
    nowstage = stage;
    srand(time(NULL));
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    resize_term(40, 120);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(6, COLOR_RED, COLOR_RED);
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            arr[i][j] = 0;
        }
    }

    switch (stage)
    {
    case 1:
        success = 6;
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
        success = 10;
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

        for (int i = 0; i < SIZE / 3; i++)
        { // 변
            arr[SIZE / 3 + i][SIZE / 2] = 1;
        }

        arr[0][0] = 2; // 모서리
        arr[0][SIZE - 1] = 2;
        arr[SIZE - 1][0] = 2;
        arr[SIZE - 1][SIZE - 1] = 2;

        //초기 위치
        arr[snake.getHeady()][snake.getHeadx()] = 3; // 뱀 머리
        for (int i = 1; i <= 2; i++)
            arr[snake.getHeady()][snake.getHeadx() + i] = 4; // 뱀 몸통
        break;

    case 3:
        success = 15;
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

        for (int i = 0; i < SIZE / 3; i++)
        { // 변
            arr[SIZE / 3 + i][SIZE / 2] = 1;
        }

        for (int i = 0; i < SIZE / 3; i++)
        { // 변
            if (arr[SIZE / 2 - 1][SIZE / 3 + i] == 1)
                arr[SIZE / 2 - 1][SIZE / 3 + i] = 2;
            else
                arr[SIZE / 2 - 1][SIZE / 3 + i] = 1;
        }

        arr[0][0] = 2; // 모서리
        arr[0][SIZE - 1] = 2;
        arr[SIZE - 1][0] = 2;
        arr[SIZE - 1][SIZE - 1] = 2;

        //초기 위치
        arr[snake.getHeady()][snake.getHeadx()] = 3; // 뱀 머리
        for (int i = 1; i <= 2; i++)
            arr[snake.getHeady()][snake.getHeadx() + i] = 4; // 뱀 몸통
        break;

    case 4:
        success = 20;

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

        for (int i = 1; i <= 3; i++)
        {
            for (int j = 0; j < SIZE / 3; j++)
            { // 변
                arr[SIZE / 4 * i - 1][SIZE / 3 + j] = 1;
            }
        }

        arr[0][0] = 2; // 모서리
        arr[0][SIZE - 1] = 2;
        arr[SIZE - 1][0] = 2;
        arr[SIZE - 1][SIZE - 1] = 2;

        //초기 위치
        arr[snake.getHeady()][snake.getHeadx()] = 3; // 뱀 머리
        for (int i = 1; i <= 2; i++)
            arr[snake.getHeady()][snake.getHeadx() + i] = 4; // 뱀 몸통
        break;
    }
}

void Map::draw(WINDOW *win1, Snake snake, int t) const
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

    wattron(win1, COLOR_PAIR(3));

    char buf[30];
    sprintf(buf, "NowStage:%d", nowstage);
    mvwprintw(win1, 9, 55, buf);
    sprintf(buf, "size:%d/maxsize:%d", snake.getSize(), snake.getMaxsize());
    mvwprintw(win1, 10, 55, buf);
    sprintf(buf, "SuccessSize:%ds", success);
    mvwprintw(win1, 11, 55, buf);
    sprintf(buf, "growth:%d", snake.getGrowth());
    mvwprintw(win1, 12, 55, buf);
    sprintf(buf, "poison:%d", snake.getPoison());
    mvwprintw(win1, 13, 55, buf);
    sprintf(buf, "gate:%d", snake.getGatecnt());
    mvwprintw(win1, 14, 55, buf);
    sprintf(buf, "time:%ds", t);
    mvwprintw(win1, 15, 55, buf);

    wattroff(win1, COLOR_PAIR(3));
}

int Map::getSuccess() const
{
    return success;
}