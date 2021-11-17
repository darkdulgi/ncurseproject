#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <string>
using namespace std;

struct nation
{
    char name[50];
    char capital[50];
    unsigned int population;
    int locx; int locy;
    int GDP;
    int GDPpc;
    int ideol;
};

void file_download(nation[]);
void print_map(WINDOW *,int,int);
void print_menu(WINDOW *, int &);
void print_submenu(WINDOW *, int, int);
string ideol(int);