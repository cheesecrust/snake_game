#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

class snake {
   private:
    /* data */
   public:
};

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");

    clock_t start = 0, end = 0;    // move
    clock_t start2 = 0, end2 = 0;  // feed
    clock_t start3 = 0, end3 = 0;  // poison
    clock_t start4 = 0, end4 = 0;  // gate

    int size = 3;
    int heady = 10;
    int headx = 8;

    int arr[22][22] = {
        {
            0,
        },
    };

    for (int i = 0; i < 21; i++) {  // 변
        arr[i][0] = 1;
        arr[0][i] = 1;
        arr[i][20] = 1;
        arr[20][i] = 1;
    }

    for (int i = 0; i < 21; i++) {  // 변
        arr[i][21] = 1;
        arr[21][i] = 1;
    }

    arr[0][0] = 2;  // 모서리
    arr[0][20] = 2;
    arr[20][0] = 2;
    arr[20][20] = 2;

    arr[10][8] = 3;  // 뱀 머리
    arr[10][9] = 4;  // 뱀 몸통
    arr[10][10] = 4;

    WINDOW *win1;

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

    win1 = newwin(22, 44, 3, 3);
    mvwprintw(win1, 0, 7, "Snake Game");

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (arr[i][j] >= 1 && arr[i][j] <= 4) {
                wattron(win1, COLOR_PAIR(2));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(2));
            } else {
                wattron(win1, COLOR_PAIR(1));
                mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                wattroff(win1, COLOR_PAIR(1));
            }
        }
    }

    keypad(win1, true);
    int snake[441][2] = {
        {0, 0},
    };
    snake[0][0] = 10;
    snake[0][1] = 10;
    snake[1][0] = 10;
    snake[1][1] = 9;
    snake[2][0] = 10;
    snake[2][1] = 8;

    int direct[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};  // 왼, 오른, 아래, 위
    int directnum = 0;

    int feedx = 0;
    int feedy = 0;  // feed x, y

    int poisonx = 0;
    int poisony = 0;  // poison x, y

    int gate1x = 0;
    int gate1y = 0;  // gate1 x,y

    int gate2x = 0;
    int gate2y = 0;  // gate2 x,y

    bool feed = false;
    bool poison = false;
    bool gate = false;

    start = clock();   // move
    start2 = clock();  // feed
    start3 = clock();  // posion
    start4 = clock();  // gate

    int ch = 0;

    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 68:  // 왼
                if (directnum != 1)
                    directnum = 0;
                break;

            case 65:  // 위
                if (directnum != 2)
                    directnum = 3;
                break;

            case 67:  // 오른
                if (directnum != 0)
                    directnum = 1;
                break;

            case 66:  // 아래
                if (directnum != 3)
                    directnum = 2;
                break;
            default:
                break;
        }

        end = clock();

        if (feed && (float)(end - start2) / CLOCKS_PER_SEC >= 5) {
            arr[feedy][feedx] = 0;
            feed = false;
        }

        if (poison && (float)(end - start3) / CLOCKS_PER_SEC >= 10) {
            arr[poisony][poisonx] = 0;
            poison = false;
        }

        if (gate && (float)(end - start4) / CLOCKS_PER_SEC >= 15) {
            arr[gate1y][gate1x] = 1;
            arr[gate2y][gate2x] = 1;
            gate = false;
        }

        if (!feed)
            end2 = clock();

        if (!poison)
            end3 = clock();

        if (!gate)
            end4 = clock();

        if ((float)(end2 - start2) / CLOCKS_PER_SEC >= 5) {  // feed
            start2 = end2;

            while (true) {
                feedy = rand() % 21;
                feedx = rand() % 21;

                if (arr[feedy][feedx] == 0) {
                    arr[feedy][feedx] = 5;
                    feed = true;
                    break;
                    ;
                }
            }
        }

        if ((float)(end3 - start3) / CLOCKS_PER_SEC >= 10) {  // posion
            start3 = end3;

            while (true) {
                poisony = rand() % 21;
                poisonx = rand() % 21;

                if (arr[poisony][poisonx] == 0) {
                    arr[poisony][poisonx] = 6;
                    poison = true;
                    break;
                    ;
                }
            }
        }

        if ((float)(end4 - start4) / CLOCKS_PER_SEC >= 15) {  // gate
            start4 = end4;

            while (true) {
                gate1y = rand() % 21;
                gate1x = rand() % 21;
                gate2y = rand() % 21;
                gate2x = rand() % 21;

                if (arr[gate1y][gate1x] == 1 && arr[gate2y][gate2x] == 1) {
                    arr[gate1y][gate1x] = 7;
                    arr[gate2y][gate2x] = 7;
                    gate = true;
                    break;
                }
            }
        }

        if ((float)(end - start) / CLOCKS_PER_SEC >= 0.5) {
            start = end;

            arr[heady][headx] = 4;  // 앞으로 가기때문에 현재의 머리를 몸통으로 바꿈

            heady += direct[directnum][1];  // 머리 조정
            headx += direct[directnum][0];  // 머리 조정

            if (arr[heady][headx] == 1)  // 벽에 부딫히면 사망
                break;
            else if (arr[heady][headx] == 5) {
                feed = false;
                start = clock();
                arr[heady][headx] = 3;

                snake[size][0] = heady;  // snake 배열을 수정
                snake[size][1] = headx;
                size++;
            } else if (arr[heady][headx] == 6) {
                poison = false;
                start = clock();
                arr[heady][headx] = 3;

                snake[size][0] = heady;
                snake[size][1] = headx;

                arr[snake[0][0]][snake[0][1]] = 0;
                arr[snake[1][0]][snake[1][1]] = 0;

                for (int i = 2; i <= size; i++) {
                    snake[i - 2][0] = snake[i][0];
                    snake[i - 2][1] = snake[i][1];
                }

                size--;
                if (size < 3) {  // 몸길이 3보다 작으면 죽음
                    break;
                }
            } else if (arr[heady][headx] == 4)  // 자신의 몸통에 부딫히면 사망
                break;
            else if (arr[heady][headx] == 7) {             // gate 진입
                start = clock();                           // 지나는 시점 부터 다시 15초 기다림
                if (heady == gate1y && headx == gate1x) {  // gate1 진입 gate2 로 출력
                    if (arr[gate2y][gate2x + 1] == 0) {    // 오른쪽 진출
                        heady = gate2y;
                        headx = gate2x + 1;
                        directnum = 1;
                    }
                    if (arr[gate2y - 1][gate2x] == 0) {  // 위쪽 진출
                        heady = gate2y - 1;
                        headx = gate2x;
                        directnum = 3;
                    }
                    if (arr[gate2y][gate2x - 1] == 0) {  // 왼쪽 진출
                        heady = gate2y;
                        headx = gate2x - 1;
                        directnum = 0;
                    }
                    if (arr[gate2y + 1][gate2x] == 0) {  // 아래로 진출
                        heady = gate2y + 1;
                        headx = gate2x;
                        directnum = 2;
                    }
                } else if (headx == gate2x && heady == gate2y) {  // gate2 진입, gate 2로 출력
                    if (arr[gate1y][gate1x + 1] == 0) {           // 오른쪽 진출
                        heady = gate1y;
                        headx = gate1x + 1;
                        directnum = 1;
                    }
                    if (arr[gate1y - 1][gate1x] == 0) {  // 위쪽 진출
                        heady = gate1y - 1;
                        headx = gate1x;
                        directnum = 3;
                    }
                    if (arr[gate1y][gate1x - 1] == 0) {  // 왼쪽 진출
                        heady = gate1y;
                        headx = gate1x - 1;
                        directnum = 0;
                    }
                    if (arr[gate1y + 1][gate1x] == 0) {  // 아래로 진출
                        heady = gate1y + 1;
                        headx = gate1x;
                        directnum = 2;
                    }
                }
                arr[heady][headx] = 3;

                snake[size][0] = heady;
                snake[size][1] = headx;

                arr[snake[0][0]][snake[0][1]] = 0;

                for (int i = 1; i <= size; i++) {
                    snake[i - 1][0] = snake[i][0];
                    snake[i - 1][1] = snake[i][1];
                }
            } else {
                arr[heady][headx] = 3;

                snake[size][0] = heady;
                snake[size][1] = headx;

                arr[snake[0][0]][snake[0][1]] = 0;

                for (int i = 1; i <= size; i++) {
                    snake[i - 1][0] = snake[i][0];
                    snake[i - 1][1] = snake[i][1];
                }
            }

            for (int i = 0; i < 21; i++) {
                for (int j = 0; j < 21; j++) {
                    if (arr[i][j] >= 1 && arr[i][j] <= 4) {
                        wattron(win1, COLOR_PAIR(2));
                        mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                        wattroff(win1, COLOR_PAIR(2));
                    } else if (arr[i][j] == 0) {
                        wattron(win1, COLOR_PAIR(1));
                        mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                        wattroff(win1, COLOR_PAIR(1));
                    } else if (arr[i][j] == 5) {
                        wattron(win1, COLOR_PAIR(5));
                        mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                        wattroff(win1, COLOR_PAIR(5));
                    } else if (arr[i][j] == 6) {
                        wattron(win1, COLOR_PAIR(6));
                        mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                        wattroff(win1, COLOR_PAIR(6));
                    } else if (arr[i][j] == 7) {
                        wattron(win1, COLOR_PAIR(7));
                        mvwprintw(win1, i + 1, 2 * j + 1, "ㅁ");
                        wattroff(win1, COLOR_PAIR(7));
                    }
                }
            }

            wrefresh(win1);
        }
    }

    nodelay(stdscr, FALSE);
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 21; j++) {
            mvwprintw(win1, i, j * 2, "  ");
        }
    }
    mvwprintw(win1, 1, 1, "gameover");
    wrefresh(win1);

    getch();
    delwin(win1);
    endwin();

    return 0;
}
