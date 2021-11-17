#include "nation.hpp"

string ideol(int n){
    switch (n)
    {
        case 1:
        return "Democracy";
        case 2:
        return "Authoritarian Democracy";
        case 3:
        return "One-Party Dictatorship";
        case 4:
        return "Absolute Monarchy";
        case 5:
        return "Military Government";
        case 6:
        return "Anarchy";
    }
}

void print_map(WINDOW *win, int x, int y)
{
    wclear(win);
    char c[30][101] = {
        "                         ,77,      .iri:   .                   .                                    ",
        "                     S2Z@MZZ0MMMWW@MMMMMMB:       .Xr;                   .                          ",
        "             S2Sr; SXXS8Wi  ,;r@MMMMMMMMMZ         ,          ;;       raZ8MMBX       ;             ",
        "  SZaXr;, :;XZX0B@;.22;WW2BZ    2MMMMMMWS           ;SaX,.   .S , M28MMMMMMMMMMMMMMZ88MM@aZX:::rrX  ",
        ".aMMMMMMMMMMMMMWW@MWMM00: iMM7  :MMMSi   20:      7MMWMMMZZBMMMMMMMBMMM@@@WW@@@MMMMMMMMMMMMMMMMMM08X",
        " 7MMM8Z0@MMMM@@MMMMMM    :M2.    iW;     ..     iMMM :BWM@MMMMMM@@@M@@WWWWWWWWWWWWW@MMMWWM77B88r.   ",
        "  .i      8MM@WWWWW@MZX, .MMMMS             :0B  :XX S@@@@@@MM@WWWWWWWWWWWWWWWWWWWW@MX    ;M:       ",
        ".          ;MM@WWWWW@MMM80MMMWM@            r;WS2MM@MMMMMMMMMWM@WWWWWWWWWWWWWWWWWW@@MMZ   ri        ",
        "             MMWWWWWWW@@MMMMMr Xi             .MMMMMMMMS77MW  ZMWWWWWWWWWWWWWWW@MMMMMa,,            ",
        "            ,MM@WWWWWWW@@MM7                :MM8  :;ZMW:; XM: 8M@WWWWWWWWWWWWW@@0MMr  S:            ",
        "             0MM@WWW@MMMMM                   W8  ;     Z8MMMM 8M@WWWWWWWWWWWWW@M: 0  8X             ",
        "              ;MMM@MMMMMM                    @@MMM8. r   MMM@MMMMM@WWWWWWWWWWW@M@  7r:              ",
        "               ,8MMM:   S                  iMMM@@MMMMMMM88MMZ.aWMMMM@@@MM@@W@MMM@                   ",
        "                 iMM    ,r.               :MM@WWWW@@M@MM@ WMM0MX  aMMMMWZMMM@WB7                    ",
        "                  XMB0M  ,,;              ;MMWWWWWWWWWW@Ma MMMW    XMMX  aMM0   :.                  ",
        "                     ;8M                  rMMM@MM@WWWWWW@MS77       MS    rWMS  ;7                  ",
        "                       i;:MMMMS            XMMMMMM@WWWWWW@M@M.      72      :    2i                 ",
        "                         ;MMMMMMW           .i,  7M@WWWWW@MMX            .aW  XM  .                 ",
        "                         MM@W@@MMZi               MM@WWW@MW               iM;:MM7i.;Xr              ",
        "                        .MM@WWW@@MMMMr            rM@WWWMM                 :Z:; ;,  .MM@i,..        ",
        "                         7MM@WWWW@MMMi             MMWWWMMi                  ..       i.i  ,        ",
        "                          aMMWWWW@MM;             rMMWW@MM; M:                    aMM 77     .  .   ",
        "                           ,M@W@MMi                0MMMMB  87                 :MMMMMMMMMMX   .      ",
        "                           SM@@MM;                  MMMM                       MMMMMMMMMMM          ",
        "                           BMMMMi                   XZX                        2Z;  ,8MMM,          ",
        "                           MMM2                                                       ;Zr      Z2   ",
        "                          :MM                                                          ..    iW7    ",
        "                          WMS                                                                ::     ",
        "                          :M                                                                        "};
    for (int i = 0; i < 30; i++)
        wprintw(win, c[i]);

    WINDOW *highlight;
    highlight = subwin(win, 1, 1, y, x);
    wbkgd(highlight, COLOR_PAIR(3));
    refresh();
    wrefresh(win);
    wrefresh(highlight);
}

void file_download(nation nationlist[]){
    int fd = open("./nationinfo", O_RDONLY);
    if (fd == -1)
    {
        cout << "nationinfo file error\n";
        exit(1);
    }
    
    for (int i = 0; i < 300; i++)
    {
        char buf;
        char cbuf[20];
        int loc=0;
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                break;
            }
            nationlist[i].name[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                break;
            }
            nationlist[i].capital[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                nationlist[i].population=atoi(cbuf);
                memset(cbuf,0,20);
                break;
            }
            cbuf[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf==' '){
                loc=0;
                nationlist[i].locx=atoi(cbuf);
                memset(cbuf,0,20);
                break;
            }
            cbuf[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                nationlist[i].locy=atoi(cbuf);
                memset(cbuf,0,20);
                break;
            }
            cbuf[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                nationlist[i].GDP=atoi(cbuf);
                memset(cbuf,0,20);
                break;
            }
            cbuf[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                nationlist[i].GDPpc=atoi(cbuf);
                memset(cbuf,0,20);
                break;
            }
            cbuf[loc]=buf;
            loc++;
        }
        while(1){
            read(fd,&buf,1);
            if(buf=='\n'){
                loc=0;
                nationlist[i].ideol=atoi(cbuf);
                memset(cbuf,0,20);
                break;
            }
            cbuf[loc]=buf;
            loc++;
        }
        read(fd,&buf,1);
        read(fd,&buf,1);
        if(read(fd,&buf,1)==0) break;
    }
}

