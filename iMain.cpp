#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j;
double x = 0, y = 0;
int temp = 1; //to determine the turn player1 or player2
int point1 = 0; //point of player 1
int point2 = 0; //point of player 2
int dtemp = 0; //display flag for menu
int dtemp2 = 0; //display flag for gamepage
int dtemp3 = 0; //display flag for profile
int dtemp4 = 0; //display flag for help
int dtemp5 = 0; //display flag for about
char playername1[10] = "PLAYER1";
char playername2[10] = "PLAYER2";
int strlenp1 = strlen(playername1);
int strlenp2 = strlen(playername2);
char P1[10] = {'0'}; //string to store point
char P2[10] = {'0'};
int count = 0; //to count total number of boxes

struct boxcounter
{
    int counter;
    int turns; //player turns player1 or player2
    int x;
    int y;
    int r; //to determine corresponding player color
    int g;
    int b;
    int pointflag; //flag of corresponding box
    int val;
} box[5][5];

double ix;
double fx;
double iy;
double fy;

int flag1[6][5] = {0}; //flag of vertical rectangle
int flag2[6][5] = {0}; //flag of horizontal rectangle

void setFlag(int x, int y);
void drawrectangle();
void drawbox();
void menu_display(int x, int y);
void game_display();

texture startpage, menu, gamepage, profile, help, about;

void iTextureInit()
{
    startpage.Create("startpage.bmp");
    menu.Create("menu.bmp");
    gamepage.Create("gamepage.bmp");
    profile.Create("profile.bmp");
    help.Create("help.bmp");
    about.Create("about.bmp");
}

void iDraw()
{
    if (dtemp == 0)
        drawTexture(0, 0, startpage);

    menu_display(x,y);

    if (dtemp2 > 0)
        game_display();
    else if (dtemp3 > 0)
    {
        iClear();
        iSetColor(255, 255, 255);
    }
    else if (dtemp4 > 0)
    {
        iClear();
        drawTexture(0, 0, help);
    }
    else if (dtemp5 > 0)
    {
        iClear();
        drawTexture(0, 0, about);
    }
}


void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n",mx,my);
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x = mx;
        y = my;
        setFlag(x,y);
        drawbox();

        if (dtemp2 == 0)
        {
            point1 = 0;
            point2 = 0;
            P1[10] = {'0'};
            P2[10] = {'0'};
            count = 0;
        }
        else if (dtemp2 == 1)
        {
            for(i=0; i<5; i++)
            {
                for(j=0; j<5; j++)
                {
                    if (box[i][j].turns == 1 && box[i][j].pointflag == 0)
                    {
                        point1++;
                        count++;
                        box[i][j].pointflag = 1;
                    }
                }
            }

            sprintf(P1, "%d", point1);

            for(i=0; i<5; i++)
            {
                for(j=0; j<5; j++)
                {
                    if(box[i][j].turns == 2 && box[i][j].pointflag == 0)
                    {
                        point2++;
                        count++;
                        box[i][j].pointflag = 1;
                    }
                }
            }

            sprintf(P2, "%d", point2);
        }

        if (x <= 550 && y <= 550 && dtemp == 0)
            dtemp = 1;
        else if (x >= 250 && x <= 490 && y >= 345 && y <= 385 && dtemp == 1)
            dtemp2 = 1;
        else if (x >= 10 && x <= 75 && y >= 10 && y <= 35)
            dtemp2 = 0;
        else if ((x >= 475 && x <= 540 && y >= 10 && y <= 35 && dtemp2 == 1) || (x >= 255 && x <= 345 && y >= 55 && y < 95 && dtemp == 1))
            exit(0);
        /*else if(x>=250 && x<=410 && y>=275 && y<=310 && dtemp==1 && dtemp2==0)
        {
            dtemp3 = 1;
        }*/
        else if (x >= 255 && x <= 355 && y >= 200 && y <= 240 && dtemp == 1 && dtemp2 == 0 && dtemp3 == 0)
            dtemp4 = 1;
        else if (x >= 455 && x <= 545 && y >= 5 && y <= 40 && dtemp4 == 1)
            dtemp4 = 0;
        else if (x >= 255 && x <= 380 && y >= 125 && y <= 170 && dtemp == 1 && dtemp2 == 0 && dtemp3 == 0 && dtemp4 == 0)
            dtemp5 = 1;
        else if (x >= 455 && x <= 545 && y >= 15 && y <= 45 && dtemp5 == 1)
            dtemp5 = 0;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){}
}

void iKeyboard(unsigned char key)
{
    if (key == 'q')
    {
        exit(0);
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
}

int main()
{
    iInitialize(550, 550, "BRAIN DOTS");
    return 0;
}

void setFlag(int x, int y)
{
    if (dtemp2 == 0)
    {
        for (i = 0; i < 6; ++i)
        {
            for (j = 0; j < 5; ++j)
                flag1[i][j] = 0, flag2[i][j] = 0;
        }
    }
    else
    {
        iy = 96;
        fy = 104;

        for (i = 0; i < 6; ++i)
        {
            ix = 106;

            for (j = 0; j < 5; ++j)
            {
                fx = ix + 58;

                if (x >= ix && x <= fx  && y >= iy && y <= fy && flag1[i][j] == 0 && dtemp2 > 0)
                {
                    flag1[i][j] = 1;

                    if (i > 0)
                        box[i - 1][j].val +=1;

                    box[i][j].val += 1;

                    ++temp;
                }

                ix += 70;
            }

            fy = fy + 70;
            iy = iy + 70;
        }

        ix = 96;
        fx = 104;

        for (i = 0; i < 6; ++i)
        {
            iy = 106;

            for (j = 0; j < 5; ++j)
            {
                fy = iy + 58;

                if(x >= ix && x <= fx  && y >= iy && y <= fy && flag2[i][j] == 0 && dtemp2 > 0)
                {
                    flag2[i][j] = 1;

                    if (i > 0)
                        box[j][i - 1].val +=1;

                    box[j][i].val += 1;

                    ++temp;
                }

                iy += 70;
            }

            fx = fx + 70;
            ix = ix + 70;
        }
    }
}

void drawrectangle()
{
    iy = 98;

    for (i = 0; i < 6; ++i)
    {
        ix = 98;

        for (j = 0; j < 5; ++j)
        {
            if (flag1[i][j] == 1)
                iFilledRectangle(ix, iy, 70, 4);

            ix = ix + 70;
        }
        iy = iy  + 70;
    }

    ix = 98;

    for (i = 0; i < 6; ++i)
    {
        iy = 98;

        for (j = 0; j < 5; ++j)
        {
            if (flag2[i][j] == 1)
                iFilledRectangle(ix, iy, 4, 70);

            iy = iy + 70;
        }

        ix = ix + 70;
    }
}

void drawbox()
{
    if (dtemp2 == 0)
    {
        for (i = 0; i < 5; ++i)
        {
            for (j = 0; j < 5; ++j)
            {
                box[i][j].r = 0;
                box[i][j].b = 0;
            }
        }
    }
    else
    {
        fy = 110;

        for (i=0; i<5; i++)
        {
            fx = 110;

            for (j=0; j<5; j++)
            {
                if(box[i][j].val == 4)
                {
                    if (box[i][j].counter == 0)
                    {
                        box[i][j].counter = 1;
                        box[i][j].turns = (temp % 2) + 1;

                        if (temp % 2)
                            box[i][j].r = 255;
                        else
                            box[i][j].b = 255;

                        box[i][j].x = fx;
                        box[i][j].y = fy;
                        ++temp;
                    }
                }
                fx += 70;
            }
            fy += 70;
        }
    }
}

void menu_display(int x, int y)
{
    if(dtemp > 0)
    {
        iClear();
        drawTexture(0,0,menu);
    }
}

void game_display()
{
    iClear();
    iSetColor(0,255,0);
    iRectangle(70,70,410,410);
    iRectangle(60,60,430,430);
    iSetColor(255*65536,255*256,255);

    for (j = 100; j <= 460; j += 70)
    {
        for(i = 100; i <= 460; i += 70)
            iFilledCircle(i,j,6);
    }

    if (temp % 2 != 0)
    {
        iText(190, 530, "TURN : ", GLUT_BITMAP_HELVETICA_18);
        iText(260, 530, playername1, GLUT_BITMAP_HELVETICA_18);
    }
    else
    {
        iText(190, 530, "TURN : ", GLUT_BITMAP_HELVETICA_18);
        iText(260, 530, playername2, GLUT_BITMAP_HELVETICA_18);
    }

    iText(400, 530, playername2, GLUT_BITMAP_HELVETICA_18);
    iText(410 + strlenp2 * 10, 530, " : ", GLUT_BITMAP_HELVETICA_18);
    iText(430 + strlenp2 * 10, 530, P2, GLUT_BITMAP_HELVETICA_18);
    iText(20, 530, playername1, GLUT_BITMAP_HELVETICA_18);
    iText(30 + strlenp1 * 10, 530, " : ", GLUT_BITMAP_HELVETICA_18);
    iText(50 + strlenp2 * 10, 530, P1, GLUT_BITMAP_HELVETICA_18);
    iRectangle(10, 10, 65, 25);
    iText(16, 15, "BACK", GLUT_BITMAP_HELVETICA_18);
    iRectangle(475, 10, 65, 25);
    iText(486, 15, "QUIT", GLUT_BITMAP_HELVETICA_18);

    drawrectangle();

    for (i = 0; i < 5; ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            if (box[i][j].counter)
            {
                iSetColor(box[i][j].r, box[i][j].g, box[i][j].b);
                iFilledRectangle(box[i][j].x, box[i][j].y, 50, 50);
            }
        }
    }

    if (count == 25)
    {
        iSetColor(255 * 65536, 255 * 256, 255);

        if (point1>point2)
        {
            iText(200, 15, playername1, GLUT_BITMAP_HELVETICA_18);
            iText(290, 15, " win!", GLUT_BITMAP_HELVETICA_18);
        }
        else
        {
            iText(200, 15, playername2, GLUT_BITMAP_HELVETICA_18);
            iText(290, 15, "  win!", GLUT_BITMAP_HELVETICA_18);
        }
    }
}
