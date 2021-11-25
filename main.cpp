#include <ncurses.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "nation.hpp"

#define WIDTH 120
#define HEIGHT 30
using namespace std;

char *title = " ######   #######  ##     ## ##    ## ######## ########  ##    ##         #### ##    ## ########  #######  \n##    ## ##     ## ##     ## ###   ##    ##    ##     ##  ##  ##           ##  ###   ## ##       ##     ## \n##       ##     ## ##     ## ####  ##    ##    ##     ##   ####            ##  ####  ## ##       ##     ## \n##       ##     ## ##     ## ## ## ##    ##    ########     ##    #######  ##  ## ## ## ######   ##     ## \n##       ##     ## ##     ## ##  ####    ##    ##   ##      ##             ##  ##  #### ##       ##     ## \n##    ## ##     ## ##     ## ##   ###    ##    ##    ##     ##             ##  ##   ### ##       ##     ## \n ######   #######   #######  ##    ##    ##    ##     ##    ##            #### ##    ## ##        #######  \n";
char *age[] = {"Europe", "QUIT"};

//nation nationlist[300];
vector<nation> nationlist;

int main()
{
    file_download(nationlist);
    initscr();
    start_color();
    //raw();
    keypad(stdscr, 1);
    noecho();
    //======================================================
    WINDOW *win_menu;
    WINDOW *map;
    WINDOW *submenu;
    WINDOW *keyintro;
    win_menu = newwin(HEIGHT, WIDTH, 0, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    wbkgd(win_menu, COLOR_PAIR(1));
    box(win_menu, 0, 0);
    keypad(win_menu, 1);

    int select = 0;
    bool menubreak = 1;

    while (menubreak)
    {
        print_menu(win_menu, select);
        int c = wgetch(win_menu);
        switch (c)
        {
        case 10:
        case ' ':
            menubreak = 0;
            break;
        case KEY_UP:
            select++;
            break;
        case KEY_DOWN:
            select--;
            break;
        }
    }
    if (select == 1)
    {
        endwin();
        exit(0);
    }
    menubreak = 1;
    wclear(win_menu);
    wrefresh(win_menu);

    map = newwin(30, 100, 0, 0);
    submenu = newwin(30, 30, 0, 100);
    keyintro = newwin(1,100,30,0);
    wbkgd(map, COLOR_PAIR(1));
    wbkgd(submenu, COLOR_PAIR(2));
    wbkgd(keyintro, COLOR_PAIR(4));

    wprintw(keyintro," Space : select nations | z : clear selected nations | q : quit");
    wrefresh(keyintro);
    keypad(win_menu, 0);
    keypad(map, 1);
    int selectnation = 0;
    int cury = 0;
    int curx = 0;
    int c = 0;
    int nation1 = -1;
    int nation2 = -1;
    
    while (menubreak)
    {
        print_map(map, curx, cury);
        set_current_nation(curx, cury, selectnation);
        print_submenu(submenu, c, selectnation, nation1, nation2);
        c = wgetch(map);
        switch (c)
        {
        case 'q':
            menubreak = 0;
            break;
        case KEY_RIGHT:
            curx++;
            if (curx > 99)
                curx = 0;
            break;
        case KEY_LEFT:
            curx--;
            if (curx < 0)
                curx = 99;
            break;
        case KEY_DOWN:
            cury++;
            if (cury > 29)
                cury = 0;
            break;
        case KEY_UP:
            cury--;
            if (cury < 0)
                cury = 29;
            break;
        case ' ':
            if (selectnation != -1)
            {
                if (nation1 == -1)
                    nation1 = selectnation;
                else if (selectnation != nation1)
                    nation2 = selectnation;
            }
            break;
        case 'z':
            nation1 = -1;
            nation2 = -1;
            break;
        }
    }

    //======================================================
    endwin();
}

void print_menu(WINDOW *menu, int &cur)
{
    int x, y;
    getmaxyx(menu, y, x);
    WINDOW *win_title;
    win_title = subwin(menu, y / 3, x * 11 / 12, 5, 7);
    mvwprintw(win_title, 0, 0, "%s", title);

    x /= 2;
    y = 20;

    if (cur >= 2)
        cur = 0;
    if (cur < 0)
        cur = 1;
    for (int i = 0; i < 2; i++)
    {
        if (cur == i)
        {
            wattron(menu, A_BLINK | A_STANDOUT);
            mvwprintw(menu, y, x, "%s", age[i]);
            wattroff(menu, A_BLINK | A_STANDOUT);
        }
        else
            mvwprintw(menu, y, x, "%s", age[i]);
        y += 2;
    }

    refresh();
    wrefresh(menu);
    wrefresh(win_title);
    wmove(menu, 0, 0);
}

void print_submenu(WINDOW *submenu, int input, int n, int n1, int n2)
{
    wclear(submenu);
    if (n != -1)
    {
        wprintw(submenu, "%s\n", nationlist[n].name);
        wprintw(submenu, "Captial: %s\n", nationlist[n].capital);
        wprintw(submenu, "Population: %d\n", nationlist[n].population);
        if (nationlist[n].GDP == 0)
            wprintw(submenu, "GDP: -\n");
        else
            wprintw(submenu, "GDP: $%d(100 Million)\n", nationlist[n].GDP);
        if (nationlist[n].GDPpc == 0)
            wprintw(submenu, "GDP/c: -\n");
        else
            wprintw(submenu, "GDP/c: $%d\n", nationlist[n].GDPpc);
        if (nationlist[n].ideol)
            wprintw(submenu, "UN Recognised\n");
        else
            wprintw(submenu, "NOT RECOGNISED STATE\n");
    }
    else
    {
        for (int i = 0; i < 6; i++)
            wprintw(submenu, "\n");
    }
    wprintw(submenu, "==============================");
    if (n1 != -1)
        wprintw(submenu, "%s\n", nationlist[n1].name);
    if (n2 != -1)
        wprintw(submenu, "%s\n", nationlist[n2].name);
    refresh();
    wrefresh(submenu);
}