#include <ncurses.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "nation.hpp"

#define WIDTH 120
#define HEIGHT 30
using namespace std;

char *title = " ######   #######  ##     ## ##    ## ######## ########  ##    ##         #### ##    ## ########  #######  \n##    ## ##     ## ##     ## ###   ##    ##    ##     ##  ##  ##           ##  ###   ## ##       ##     ## \n##       ##     ## ##     ## ####  ##    ##    ##     ##   ####            ##  ####  ## ##       ##     ## \n##       ##     ## ##     ## ## ## ##    ##    ########     ##    #######  ##  ## ## ## ######   ##     ## \n##       ##     ## ##     ## ##  ####    ##    ##   ##      ##             ##  ##  #### ##       ##     ## \n##    ## ##     ## ##     ## ##   ###    ##    ##    ##     ##             ##  ##   ### ##       ##     ## \n ######   #######   #######  ##    ##    ##    ##     ##    ##            #### ##    ## ##        #######  \n";
char *age[] = {"2021", "QUIT"};

nation nationlist[300];

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
    win_menu = newwin(HEIGHT, WIDTH, 0, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_RED);
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
    submenu = newwin(30, 25, 0, 100);
    wbkgd(map, COLOR_PAIR(1));
    wbkgd(submenu, COLOR_PAIR(2));

    keypad(win_menu, 0);
    keypad(map, 1);
    int selectnation = 0;
    int cury=0;
    int curx=0;
    int c = 0;
    while (menubreak)
    {
        print_map(map, curx, cury);
        set_current_nation(curx,cury,selectnation);
        print_submenu(submenu, c, selectnation);
        c = wgetch(map);
        switch (c)
        {
        case 'q':
            menubreak = 0;
            break;
        case 10:
        case ' ':
            break;
        case KEY_RIGHT:
            curx++;
            if(curx>100) curx=0;
            break;
        case KEY_LEFT:
            curx--;
            if(curx<0) curx=99;
            break;
        case KEY_DOWN:
            cury++;
            if(cury>30) cury=0;
            break;
        case KEY_UP:
            cury--;
            if(cury<0) cury=29;
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

void print_submenu(WINDOW *submenu, int input, int n)
{
    wclear(submenu);
    wprintw(submenu,"%s\n",nationlist[n].name);
    wprintw(submenu,"Captial: %s\n",nationlist[n].capital);
    wprintw(submenu,"Population: %d\n",nationlist[n].population);
    wprintw(submenu,"GDP: $%d Billion\n",nationlist[n].GDP);
    wprintw(submenu,"GDP/p: $%d\n",nationlist[n].GDPpc);
    wprintw(submenu,"Government: %s\n",ideol(nationlist[n].ideol).c_str());
    refresh();
    wrefresh(submenu);
}