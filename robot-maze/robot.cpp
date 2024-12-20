#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <string>
#include "library.h"

using namespace std;

char maze[24][61] = {};
char retrace[24][61] = {};
char visited[24][61] = {};
char monster_retrace[24][61] = {};
char monster_visited[24][61] = {};
char yellowbrickroad[24][61] = {};

void treasure(const int x, const int y)
{
    set_pen_color(color::brown);
    fill_rectangle(x + 3, y + 20, 14, -8);
    set_pen_color(color::yellow);
    fill_rectangle(x + 4, y + 12, 12, -6);
}

void robot(const int x, const int y)
{
    set_pen_color(color::light_blue);
    set_pen_width(12);
    fill_rectangle(x + 7, y + 2, 5, 6);
    fill_rectangle(x + 5, y + 8, 9, 10);
    set_pen_color(color::black);
    set_pen_width(2);
    draw_point(x + 8, y + 4);
    draw_point(x + 10, y + 4);
}

void monster(const int x, const int y)
{
    set_pen_color(color::purple);
    set_pen_width(12);
    fill_rectangle(x + 7, y + 2, 5, 6);
    fill_rectangle(x + 5, y + 8, 9, 10);
    set_pen_color(color::black);
    set_pen_width(2);
    draw_point(x + 8, y + 4);
    draw_point(x + 10, y + 4);
}

void monster2(const int x, const int y)
{
    set_pen_color(color::cyan);
    set_pen_width(12);
    fill_rectangle(x + 7, y + 2, 5, 6);
    fill_rectangle(x + 5, y + 8, 9, 10);
    set_pen_color(color::black);
    set_pen_width(2);
    draw_point(x + 8, y + 4);
    draw_point(x + 10, y + 4);
}

int monster2(const int startx, const int starty, const int treasurex, const int treasurey, const int monsterx, const int monstery, const int monster2x, const int monster2y, const int Mx2, const int My2)
{
    int x = Mx2;
    int y = My2;
    int ifB = 0;
    int c = -1;
    int b = -1;

    while (true)
    {
        c = rand() % 4;

        if (maze[(y - 20) / 20][x / 20] != '%' && monster_visited[(y - 20) / 20][x / 20] != 'X')
        {
            c = 0;
        }
        else if (maze[y / 20][(x + 20) / 20] != '%' && monster_visited[y / 20][(x + 20) / 20] != 'X')
        {
            c = 1;
        }
        else if (maze[(y + 20) / 20][x / 20] != '%' && monster_visited[(y + 20) / 20][x / 20] != 'X')
        {
            c = 2;
        }
        else if (maze[y / 20][(x - 20) / 20] != '%' && monster_visited[y / 20][(x - 20) / 20] != 'X')
        {
            c = 3;
        }
        else
        {
            char dir = monster_retrace[y / 20][x / 20];
            if (dir == 'w')
                b = 2;
            else if (dir == 'd')
                b = 3;
            else if (dir == 's')
                b = 0;
            else if (dir == 'a')
                b = 1;
        }

        if (c == 0 && maze[(y - 20) / 20][x / 20] != '%' || b == 0 && maze[(y - 20) / 20][x / 20] != '%')
        {
            monster2(x, y - 20);
            if (x == startx && y == starty)
            {
                set_pen_color(color::green);
            }
            else if (x == monsterx && y == monstery)
            {
                set_pen_color(color::red);
            }
            else if (x == monster2x && y == monster2y)
            {
                set_pen_color(color::violet);
            }
            else
            {
                set_pen_color(color::white);
            }
            fill_rectangle(x + 1, y + 1, 18, 18);
            monster_visited[(y - 20) / 20][x / 20] = 'X';
            y = y - 20;
            if (c == 0)
            {
                monster_retrace[(y - 20) / 20][x / 20] = 'w';
                return c;
            }
        }
        else if (c == 1 && maze[y / 20][(x + 20) / 20] != '%' || b == 1 && maze[(y - 20) / 20][x / 20] != '%')
        {
            monster2(x + 20, y);
            if (x == startx && y == starty)
            {
                set_pen_color(color::green);
            }
            else if (x == monsterx && y == monstery)
            {
                set_pen_color(color::red);
            }
            else if (x == monster2x && y == monster2y)
            {
                set_pen_color(color::violet);
            }
            else
            {
                set_pen_color(color::white);
            }
            fill_rectangle(x + 1, y + 1, 18, 18);
            monster_visited[y / 20][(x + 20) / 20] = 'X';
            x = x + 20;
            if (c == 1)
            {
                monster_retrace[y / 20][(x + 20) / 20] = 'd';
                return c;
            }
        }
        else if (c == 2 && maze[(y + 20) / 20][x / 20] != '%' || b == 2 && maze[(y - 20) / 20][x / 20] != '%')
        {
            monster2(x, y + 20);
            if (x == startx && y == starty)
            {
                set_pen_color(color::green);
            }
            else if (x == monsterx && y == monstery)
            {
                set_pen_color(color::red);
            }
            else if (x == monster2x && y == monster2y)
            {
                set_pen_color(color::violet);
            }
            else
            {
                set_pen_color(color::white);
            }
            fill_rectangle(x + 1, y + 1, 18, 18);
            monster_visited[(y + 20) / 20][x / 20] = 'X';
            y = y + 20;
            if (c == 2)
            {
                monster_retrace[(y + 20) / 20][x / 20] = 's';
                return c;
            }
        }
        else if (c == 3 && maze[y / 20][(x - 20) / 20] != '%' || b == 3 && maze[(y - 20) / 20][x / 20] != '%')
        {
            monster2(x - 20, y);
            if (x == startx && y == starty)
            {
                set_pen_color(color::green);
            }
            else if (x == monsterx && y == monstery)
            {
                set_pen_color(color::red);
            }
            else if (x == monster2x && y == monster2y)
            {
                set_pen_color(color::violet);
            }
            else
            {
                set_pen_color(color::white);
            }
            fill_rectangle(x + 1, y + 1, 18, 18);
            monster_visited[y / 20][(x - 20) / 20] = 'X';
            x = x - 20;
            if (c == 3)
            {
                monster_retrace[y / 20][(x - 20) / 20] = 'a';
                return c;
            }
        }
    }
}

int enemy_move(const int startx, const int starty, const int treasurex, const int treasurey, const int monsterx, const int monstery, const int Mx, const int My, int c)
{
    int y = My;
    int x = Mx;

    while (true)
    {
        if (c == 0 && maze[(y - 20) / 20][x / 20] != '%')
        {
            monster(x, y - 20);
            if (x == startx && y == starty)
                set_pen_color(color::green);
            else if (x == monsterx && y == monstery)
                set_pen_color(color::red);
            else if (x == treasurex && y == treasurey)
                set_pen_color(color::yellow);
            else
                set_pen_color(color::white);
            fill_rectangle(x + 1, y + 1, 18, 18);
            return 0;
        }
        else if (c == 1 && maze[y / 20][(x + 20) / 20] != '%')
        {
            monster(x + 20, y);
            if (x == startx && y == starty)
                set_pen_color(color::green);
            else if (x == monsterx && y == monstery)
                set_pen_color(color::red);
            else if (x == treasurex && y == treasurey)
                set_pen_color(color::yellow);
            else
                set_pen_color(color::white);
            fill_rectangle(x + 1, y + 1, 18, 18);
            return 1;
        }
        else if (c == 2 && maze[(y + 20) / 20][x / 20] != '%')
        {
            monster(x, y + 20);
            if (x == startx && y == starty)
                set_pen_color(color::green);
            else if (x == monsterx && y == monstery)
                set_pen_color(color::red);
            else if (x == treasurex && y == treasurey)
                set_pen_color(color::yellow);
            else
                set_pen_color(color::white);
            fill_rectangle(x + 1, y + 1, 18, 18);
            return 2;
        }
        else if (c == 3 && maze[y / 20][(x - 20) / 20] != '%')
        {
            monster(x - 20, y);
            if (x == startx && y == starty)
                set_pen_color(color::green);
            else if (x == monsterx && y == monstery)
                set_pen_color(color::red);
            else if (x == treasurex && y == treasurey)
                set_pen_color(color::yellow);
            else
                set_pen_color(color::white);
            fill_rectangle(x + 1, y + 1, 18, 18);
            return 3;
        }
    }
}

int main()
{
    set_window_size(1200, 600);
    read_maze("maze.txt");

    for (int row = 0; row < 24; row++)
    {
        for (int col = 0; col < 61; col++)
        {
            visited[row][col] = monster_visited[row][col] = retrace[row][col] = yellowbrickroad[row][col] = ' ';
            maze[row][col] = get_maze_symbol(row, col);
        }
    }

    treasure(600, 500);
    robot(100, 200);
    monster(800, 300);

    return 0;
}

