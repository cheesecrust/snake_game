#include "map.h"

int input(int ch, int directnum) {
    switch (ch) {
        case 68:  // 왼
            if (directnum != 2)
                directnum = 0;
            break;

        case 65:  // 위
            if (directnum != 3)
                directnum = 1;
            break;

        case 67:  // 오른
            if (directnum != 0)
                directnum = 2;
            break;

        case 66:  // 아래
            if (directnum != 1)
                directnum = 3;
            break;
        default:
            break;
    }

    return directnum;
}

void exit(WINDOW *win1) {
    for (int i = 0; i < SIZE + 1; i++) {
        for (int j = 0; j < SIZE + 1; j++) {
            mvwprintw(win1, i, j * 2, "  ");
        }
    }

    mvwprintw(win1, 1, 1, "gameover");
    wrefresh(win1);

    delwin(win1);
    endwin();
}

int main() {
    clock_t start = 0, end = 0;    // move
    clock_t start2 = 0, end2 = 0;  // feed
    clock_t start3 = 0, end3 = 0;  // poison
    clock_t start4 = 0, end4 = 0;  // gate

    Snake snake = Snake();
    Map map = Map(snake, 1);

    WINDOW *win1;

    win1 = newwin(22, 44, 3, 3);
    keypad(win1, true);

    mvwprintw(win1, 0, 7, "Snake Game");
    map.draw(win1);

    int snake_pair[SIZE * SIZE][2] = {
        {0, 0},
    };

    snake_pair[0][0] = 10;
    snake_pair[0][1] = 10;
    snake_pair[1][0] = 10;
    snake_pair[1][1] = 9;
    snake_pair[2][0] = 10;
    snake_pair[2][1] = 8;

    int direct[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};  //  왼, 위, 오른, 아래
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
    int cnt = 0;

    while ((ch = getch()) != KEY_F(1)) {
        directnum = input(ch, directnum);

        end = clock();

        if (feed && (float)(end - start2) / CLOCKS_PER_SEC >= 5) {
            map.arr[feedy][feedx] = 0;
            feed = false;
        }

        if (poison && (float)(end - start3) / CLOCKS_PER_SEC >= 10) {
            map.arr[poisony][poisonx] = 0;
            poison = false;
        }

        if (!snake.getGate() && gate && (float)(end - start4) / CLOCKS_PER_SEC >= 15) {
            map.arr[gate1y][gate1x] = 1;
            map.arr[gate2y][gate2x] = 1;
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
                feedy = rand() % (SIZE - 2) + 1;
                feedx = rand() % (SIZE - 2) + 1;

                if (map.arr[feedy][feedx] == 0) {
                    map.arr[feedy][feedx] = 5;
                    feed = true;
                    break;
                }
            }
        }

        if ((float)(end3 - start3) / CLOCKS_PER_SEC >= 10) {  // posion
            start3 = end3;

            while (true) {
                poisony = rand() % (SIZE - 2) + 1;
                poisonx = rand() % (SIZE - 2) + 1;

                if (map.arr[poisony][poisonx] == 0) {
                    map.arr[poisony][poisonx] = 6;
                    poison = true;
                    break;
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

                if (map.arr[gate1y][gate1x] == 1 && map.arr[gate2y][gate2x] == 1) {
                    map.arr[gate1y][gate1x] = 7;
                    map.arr[gate2y][gate2x] = 7;
                    gate = true;
                    break;
                }
            }
        }

        if ((float)(end - start) / CLOCKS_PER_SEC >= 0.5) {
            if (snake.getGate()) {
                if (cnt > snake.getSize())
                    snake.setGate();
                cnt++;
            }

            start = end;

            int y = snake.getHeady();
            int x = snake.getHeadx();
            int s = snake.getSize();

            map.arr[y][x] = 4;  // 앞으로 가기때문에 현재의 머리를 몸통으로 바꿈

            y += direct[directnum][1];
            x += direct[directnum][0];
            snake.setHeady(y);  // 머리 조정
            snake.setHeadx(x);  // 머리 조정

            if (map.arr[y][x] == 1)  // 벽에 부딫히면 사망
                break;
            else if (map.arr[y][x] == 5) {
                feed = false;
                start = clock();
                map.arr[y][x] = 3;

                snake_pair[snake.getSize()][0] = y;  // snake_pair 배열을 수정
                snake_pair[snake.getSize()][1] = x;
                s++;
                snake.setSize(s);
            } else if (map.arr[y][x] == 6) {
                poison = false;
                start = clock();
                map.arr[y][x] = 3;

                snake_pair[s][0] = y;
                snake_pair[s][1] = x;

                map.arr[snake_pair[0][0]][snake_pair[0][1]] = 0;
                map.arr[snake_pair[1][0]][snake_pair[1][1]] = 0;

                for (int i = 2; i <= s; i++) {
                    snake_pair[i - 2][0] = snake_pair[i][0];
                    snake_pair[i - 2][1] = snake_pair[i][1];
                }

                s--;
                snake.setSize(s);

                if (s < 3)  // 몸길이 3보다 작으면 죽음
                    break;
            } else if (map.arr[y][x] == 4)  // 자신의 몸통에 부딫히면 사망
                break;
            else if (map.arr[y][x] == 7)  // gate 진입
            {
                snake.setGate();
                start = clock();  // 지나는 시점 부터 다시 15초 기다림
                int check = 0;
                if (y == gate1y && x == gate1x) {  // gate1 진입 gate2 로 출력
                    for (int i = -1; i < 3; i++) {
                        check = (directnum + i + 1) % 4;
                        int tx = direct[check][0];
                        int ty = direct[check][1];
                        if (map.arr[gate2y + ty][gate2x + tx] == 0 && (gate2y + ty) >= 0 && (gate2y + tx) >= 0) {
                            y = gate2y + ty;
                            x = gate2x + tx;
                            directnum = check;
                            break;
                        }
                    }
                } else if (x == gate2x && y == gate2y) {  // gate2 진입, gate 2로 출력
                    for (int i = -1; i < 3; i++) {
                        check = (directnum + i) % 4;
                        int tx = direct[check][0];
                        int ty = direct[check][1];
                        if (map.arr[gate1y + ty][gate1x + tx] == 0 && (gate1y + ty) >= 0 && (gate1y + tx) >= 0) {
                            y = gate1y + ty;
                            x = gate1x + tx;
                            directnum = check;
                            break;
                        }
                    }
                }

                snake.setHeady(y);
                snake.setHeadx(x);

                map.arr[snake.getHeady()][snake.getHeadx()] = 3;

                snake_pair[s][0] = snake.getHeady();
                snake_pair[s][1] = snake.getHeadx();

                map.arr[snake_pair[0][0]][snake_pair[0][1]] = 0;

                for (int i = 1; i <= s; i++) {
                    snake_pair[i - 1][0] = snake_pair[i][0];
                    snake_pair[i - 1][1] = snake_pair[i][1];
                }
            } else {
                map.arr[snake.getHeady()][snake.getHeadx()] = 3;

                snake_pair[s][0] = y;
                snake_pair[s][1] = x;

                map.arr[snake_pair[0][0]][snake_pair[0][1]] = 0;

                for (int i = 1; i <= s; i++) {
                    snake_pair[i - 1][0] = snake_pair[i][0];
                    snake_pair[i - 1][1] = snake_pair[i][1];
                }
            }

            map.draw(win1);

            wrefresh(win1);
        }
    }

    exit(win1);

    return 0;
}