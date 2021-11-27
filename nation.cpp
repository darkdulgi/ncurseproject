#include "nation.hpp"

char c[31][101] = {
    "                                                                                       MMM  MMMMMMMM",
    "                                                                                       MMMMMMMMMMMMM",
    "                EE                                        KKKKK              MM      MMMMMMMMMMMMMMM",
    "               EEEEEEE                               KKKKKLKKLMMMMMMM     MM  MMMMMMMMMMMMMMMMMMMMMM",
    "                 EEEE                              KKJJJJJLLLLMMMMMMMMMMM  MMMMMMMMMMMMMMMMMMMMMMMMM",
    "                                                 KKKJJJJJJLLLLLMMMM      MMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                                               KKKJJJJJJ    LLLLMMMM     MMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                                           KKKKKKJJJJJJ   LLLLLLLMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                                       KKKKKKKKJJJJJ    LLLLLLLLMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                        AAAA           KKKKKKKJJJJJ     LLLLLLLMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                        AAAAA         KKKKK KJJJJJJJ            MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                 CCCAA  AAA                 JJJJJJ        NNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "               CCCCCC    AAA            TT   JJJJJ      O  OOONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                      AAAAAA           TT  T T         OOOOOOOOMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                    AAAAAAAAA      F H HHH TT     R   MPPPPPPPQQQQQMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
    "                                FFFHHHHHHHHHHHRRRRRRRRRRPPPPQQQQQQQQMMMMMMMMMMMMMMMMMMMMMMMM        ",
    "                  BBB  B   BDDDDFHHHHHHHHHHHHHRRRRRRRRRRRRQQQQQQQQQSSSSMMMMMMMMMMMMMMMMMMM          ",
    "                    BBBBBBBBBBDDGHHHHHHHHHHHUUURRRRRRRRRRRSSSSSSSSSSSSSSSSSSSSSMMMMMMMMMMM          ",
    "                     BBBBBBBBBBBBBHHHHHHHHUUUUUUURRRRRRRRSSSSSSSSSSSSSSSSSSSSSSSSpMMMMMMMMMMM       ",
    "       yyyyyy       BBBBBBBBBBBBBIIIIIrWWWWWWWWWVVVVVVVVSSSSSSSSSSSSSSSSSSSSSSSSqMMMMMMMMMMMMM      ",
    "      zzzyyyyyyyy  BBBBBBBBBBBBBvvvvvvvvvvv```XXXXXXXXXXYYYYYYYYZ[SSSSSSSSSS   MMMMMMMMMMMMM        ",
    "   zzzzyyyyyyyyyyyyyyyuBBB BBBtvvv vvvsv   ```_____XXXXYYYYYYYYYZZS     SSS   MMMMMMMMMMMMMMMM      ",
    "   zzzyyyyyyyyyyyyyyyyyy            vvvvv   ___aaaa^^^^YYYYYYYYYY                 MMMoMMMnMMMMMM    ",
    "   zzyyyyyyyyyyyyy               B    vwvv      _abbc^^]]]]]]]]]                      jjjjjjjllllll ",
    "      yyyyyyyyyy               vvv       vvvv     eedddffff]]]gg       gggggg     g gggkkkkmllll ll ",
    "                               vv          v v     effff     gggggggggggggggggggggggggggllkk        ",
    "                                       vvv v         ffff     ggggggggggggggggggggggg               ",
    "                                        v             f          ggg   gggg   g                     ",
    "                                            x            fff         hi                             ",
    "                                                                                                    "};

void set_current_nation(int x, int y, int &nat)
{

    if (c[y][x] >= 65)
        nat = c[y][x] - 65;
    else if (c[y][x] == ' ')
        nat = -1;
}

void print_map(WINDOW *win, int x, int y, int n1, int n2)
{
    wclear(win);

    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 101; j++)
        {
            if (i == y && j == x)
                wattron(win, COLOR_PAIR(3));
            if (c[i][j] == ' ')
                wprintw(win, " ");
            else if (c[i][j] != 0)
            {
                if (c[i][j] == n1 + 65 && !(i == y && j == x))
                    wattron(win, COLOR_PAIR(5) | A_BLINK);
                else if(c[i][j] == n2 + 65 && !(i == y && j == x))
                    wattron(win, COLOR_PAIR(6) | A_BLINK);
                wprintw(win, "#");
                if (c[i][j] == n1 + 65 && !(i == y && j == x))
                    wattroff(win, COLOR_PAIR(5) | A_BLINK);
                else if(c[i][j] == n2 + 65 && !(i == y && j == x))
                    wattroff(win, COLOR_PAIR(6) | A_BLINK);
            }
            if (i == y && j == x)
                wattroff(win, COLOR_PAIR(3));
        }
    }
    mvwprintw(win, 29, 1, "x:%d,y:%d", x, y);
    refresh();
    wrefresh(win);
}

void file_download(vector<nation> &nationlist)
{
    int fd = open("./nationinfo", O_RDONLY);

    while (1)
    {
        nation temp = {"", "", 0, 0, 0, 0};
        char buf;
        char cbuf[20];
        int loc = 0;
        while (1)
        {
            read(fd, &buf, 1);
            if (buf == '\n')
            {
                loc = 0;
                break;
            }
            temp.name[loc] = buf;
            loc++;
        }
        while (1)
        {
            read(fd, &buf, 1);
            if (buf == '\n')
            {
                loc = 0;
                break;
            }
            temp.capital[loc] = buf;
            loc++;
        }
        while (1)
        {
            read(fd, &buf, 1);
            if (buf == '\n')
            {
                loc = 0;
                temp.population = atoi(cbuf);
                memset(cbuf, 0, 20);
                break;
            }
            cbuf[loc] = buf;
            loc++;
        }
        while (1)
        {
            read(fd, &buf, 1);
            if (buf == '\n')
            {
                loc = 0;
                temp.GDP = atoi(cbuf);
                memset(cbuf, 0, 20);
                break;
            }
            cbuf[loc] = buf;
            loc++;
        }
        while (1)
        {
            read(fd, &buf, 1);
            if (buf == '\n')
            {
                loc = 0;
                temp.GDPpc = atoi(cbuf);
                memset(cbuf, 0, 20);
                break;
            }
            cbuf[loc] = buf;
            loc++;
        }
        while (1)
        {
            read(fd, &buf, 1);
            if (buf == '\n')
            {
                loc = 0;
                temp.ideol = atoi(cbuf);
                memset(cbuf, 0, 20);
                break;
            }
            cbuf[loc] = buf;
            loc++;
        }
        nationlist.push_back(temp);
        read(fd, &buf, 1);
        read(fd, &buf, 1);
        read(fd, &buf, 1);
        read(fd, &buf, 1);
        if (read(fd, &buf, 1) == 0)
            break;
    }
}
