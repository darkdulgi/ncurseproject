#include "nation.hpp"

void set_current_nation(int x, int y, int &nat)
{
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
        "                 CCCCC  AAA                 JJJJJJ        NNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
        "               CCCCCC    AAA            TT   JJJJJ      O  OOONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
        "                      AAAAAA           TT  T T         OOOOOOOOMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
        "                    AAAAAAAAA      F H HHH TT     R   MPPPPPPPQQQQQMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
        "                                FFFHHHHHHHHHHHRRRRRRRRRRPPPPQQQQQQQQMMMMMMMMMMMMMMMMMMMMMMMM        ",
        "                  BBB  B   BDDDDFHHHHHHHHHHHHHRRRRRRRRRRRRQQQQQQQQQSSSSMMMMMMMMMMMMMMMMMMM          ",
        "                    BBBBBBBBBBDDGHHHHHHHHHHHUUURRRRRRRRRRRSSSSSSSSSSSSSSSSSSSSSMMMMMMMMMMM          ",
        "                     BBBBBBBBBBBBBHHHHHHHHUUUUUUURRRRRRRRSSSSSSSSSSSSSSSSSSSSSSSSpMMMMMMMMMMM       ",
        "       yyyyyy       BBBBBBBBBBBBBIIIIIrWWWWWWWWWVVVVVVVVSSSSSSSSSSSSSSSSSSSSSSSSqMMMMMMMMMMMMM      ",
        "      zzzyyyyyyyy  BBBBBBBBBBBBBvvvvvvvvvvv```XXXXXXXXXXYYYYYYYYZ[SSSSSSSSSS   MMMMMMMMMMMMM        ",
        "   zzzzyyyyyyyyyyyyyyyuBBB BBBtvvv vvvs#   ```_____XXXXYYYYYYYYYZZS     SSS   MMMMMMMMMMMMMMMM      ",
        "   zzzyyyyyyyyyyyyyyyyyy            vvvvv   ___aaaa^^^^YYYYYYYYYY                 MMMoMMMnMMMMMM    ",
        "   zzyyyyyyyyyyyyy               B    vwvv      _abbc^^]]]]]]]]]                      jjjjjjjllllll ",
        "      yyyyyyyyyy               vvv       vvvv     eedddffff]]]gg       gggggg     g gggkkkkmllll ll ",
        "                               vv          v v     effff     gggggggggggggggggggggggggggllkk        ",
        "                                       vvv v         ffff     ggggggggggggggggggggggg               ",
        "                                        v             f          ggg   gggg   g                     ",
        "                                            x            fff         hi                             ",
        "                                                                                                    "};
    if(c[y][x]>=65) nat=c[y][x]-65;
    else if(c[y][x]==' ') nat=-1;
}

void print_map(WINDOW *win, int x, int y)
{
    wclear(win);
    char c[31][101] = {
        "                                                                                       ###  ########",
        "                                                                                       #############",
        "                ##                                        #####              ##      ###############",
        "               #######                               ################     ##  ######################",
        "                 ####                              ######################  #########################",
        "                                                 ##################      ###########################",
        "                                               #########    ########     ###########################",
        "                                           ############   ##########################################",
        "                                       #############    ############################################",
        "                        ####           ############     ############################################",
        "                        #####         ##### ########            ####################################",
        "                 #####  ###                 ######        ##########################################",
        "               ######    ###            ##   #####      #  #########################################",
        "                      ######           ##  # #         #############################################",
        "                    #########      # # ### ##     #   ##############################################",
        "                                ############################################################        ",
        "                  ###  #   ###############################################################          ",
        "                    ######################################################################          ",
        "                     ########################################################################       ",
        "       ######       ##########################################################################      ",
        "      ###########  #########################################################   #############        ",
        "   ####################### ####### #####   ########################     ###   ################      ",
        "   #####################            #####   #####################                 ##############    ",
        "   ###############               #    ####      ################                      ############# ",
        "      ##########               ###       ####     ##############       ######     # ############ ## ",
        "                               ##          # #     #####     ###############################        ",
        "                                       ### #         ####     #######################               ",
        "                                        #             #          ###   ####   #                     ",
        "                                            #            ###         ##                             ",
        "                                                                                                    "};
    for (int i = 0; i < 31; i++)
        wprintw(win, c[i]);
    mvwprintw(win, 29, 1, "x:%d,y:%d", x, y);
    WINDOW *highlight;
    highlight = subwin(win, 1, 1, y, x);
    wbkgd(highlight, COLOR_PAIR(3));
    refresh();
    wrefresh(win);
    wrefresh(highlight);
}

//void file_download(nation nationlist[])
void file_download(vector<nation> &nationlist)
{
    int fd = open("./nationinfo", O_RDONLY);

    while(1){
        nation temp={"","",0,0,0,0};
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
