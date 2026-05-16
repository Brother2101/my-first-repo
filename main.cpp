#include "curses.h"
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

struct Point {
    int x;
    int y;
};


class SnakeGame {
private:
    vector<Point> snake;
    Point food;

    int dx;
    int dy;

    bool gameOver;
    bool win;

    int score;

public:
    SnakeGame() {
        snake.push_back({WIDTH / 2, HEIGHT / 2});

        dx = 1;
        dy = 0;

        gameOver = false;
        win = false;

        score = 0;

        spawnFood();
    }

    void spawnFood() {
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    }

    void input() {
        int ch = getch();

        switch (ch) {
            case KEY_UP:
                if (dy != 1) {
                    dx = 0;
                    dy = -1;
                }
                break;

            case KEY_DOWN:
                if (dy != -1) {
                    dx = 0;
                    dy = 1;
                }
                break;

            case KEY_LEFT:
                if (dx != 1) {
                    dx = -1;
                    dy = 0;
                }
                break;

            case KEY_RIGHT:
                if (dx != -1) {
                    dx = 1;
                    dy = 0;
                }
                break;

            case 'q':
            case 'Q':
                gameOver = true;
                break;
        }
    }

    void update() {
        Point newHead;
        newHead.x = snake[0].x + dx;
        newHead.y = snake[0].y + dy;

        if (newHead.x <= 0 || newHead.x >= WIDTH - 1 ||
            newHead.y <= 0 || newHead.y >= HEIGHT - 1) {
            gameOver = true;
            return;
        }

        for (size_t i = 0; i < snake.size(); i++) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                gameOver = true;
                return;
            }
        }


        snake.insert(snake.begin(), newHead);
        int maxCells = (WIDTH - 2) * (HEIGHT - 2);

        if ((int)snake.size() == maxCells) {
            win = true;
            gameOver = true;
            return;
        }

        if (newHead.x == food.x && newHead.y == food.y) {
            score++;
            spawnFood();
        } else {
            snake.pop_back();
        }
    }

    void draw() {
        clear();

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                    mvaddch(y, x, '#');
                }
            }
        }

        mvaddch(food.y, food.x, '*');

        for (size_t i = 0; i < snake.size(); i++) {
            if (i == 0) {
                mvaddch(snake[i].y, snake[i].x, 'O');
            } else {
                mvaddch(snake[i].y, snake[i].x, 'o');
            }
        }

        mvprintw(HEIGHT + 1, 0, "Score: %d", score);
        mvprintw(HEIGHT + 2, 0, "Use arrows to move. Press Q to quit.");

        refresh();
    }

    bool isGameOver() const {
        return gameOver;
    }

    bool isWin() const {
        return win;
    }

    int getScore() const {
        return score;
    }
};


int main() {
    srand(time(0));

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    SnakeGame game;

    while (!game.isGameOver()) {
        game.input();
        game.update();
        game.draw();
        napms(120);
    }

    nodelay(stdscr, FALSE);

    clear();

    if (game.isWin()) {
        mvprintw(5, 10, "YOU WIN!");
    }
    else {
        mvprintw(5, 10, "GAME OVER!");
    }

    mvprintw(6, 10, "Final score: %d", game.getScore());

    mvprintw(8, 10, "Press any key to exit...");

    refresh();

    getch();
    endwin();

    return 0;   
}