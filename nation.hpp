#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

struct nation
{
    char name[50];
    char capital[50];
    unsigned int population;
    int GDP;
    int GDPpc;
    bool ideol;
};

void set_current_nation(int, int, int &);
void file_download(vector<nation> &);
void print_map(WINDOW *, int, int, int, int);
void print_menu(WINDOW *, int &);
void print_submenu(WINDOW *, int, int, int, int);