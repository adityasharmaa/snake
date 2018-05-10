
                                    // ADITYA SHARMA ,Dated:30/09/2017

#include<stdio.h>
#include<graphics.h>
#include"circle.h"
#include<time.h>
int fx=200,fy=300;
void food()//initial food disappear and new appears
{
    int i;
    for(i=-2;i<=2;i++)
    putpixel(fx,fy+i,15);
    for(i=-2;i<=2;i++)
    putpixel(fx+i,fy,15);

    srand(rand()%time('\0'));
    fx=rand()%634;
    srand(rand()%time('\0'));
    fy=rand()%474;

    if(fx<7)
    fx+=7;
    if(fy<22)
    fy+=22;

    for(i=-2;i<=2;i++)
    putpixel(fx,fy+i,4);
    for(i=-2;i<=2;i++)
    putpixel(fx+i,fy,4);
}
int main()
{
    int gd=DETECT,gm,x,pin=1,qin=0,y=240,xin=1,yin=0,ch,p,q,i,row,col,k=0,cnt=8,exiter,score=0;
    char a[5],b[7];
    static int buff[30][4];
    initgraph(&gd,&gm,"");
    setbkcolor(15);
    floodfill(0,0,15);
    setcolor(3);
    // initial message
    while(!kbhit())
    {
        outtextxy(200,80,"WELCOME TO SNAKE XENSIA 2.1.5");
        outtextxy(100,120,"Here are rules to play the game:");
        outtextxy(100,140,"1.Use arrow keys to control snake.");
        outtextxy(100,160,"2.You will get 8 seconds to feed snake each time, failing which game overs.");
        outtextxy(100,180,"3.Also keep snake inside the frame visible on screen, failing which game overs.");
        outtextxy(100,200,"4.Score advances as per time required for each feeding.");
        outtextxy(100,220,"5.Press 'Q' anytime to quit the game.");
        outtextxy(100,240,"SPECIAL FEATURE: Snake can turn 180 degree if you want.");
        outtextxy(200,280,"PRESS 'RIGHT ARROW KEY' TO PLAY");
    }
    cleardevice();
    // frame
    rectangle(5,20,635,475);
    rectangle(6,21,634,474);

    //initial food
    food();
    //initial snake
    for(x=270;x<=370;x++)
    putpixel(x,240,2);

    p=x-101;
    q=y;
    i=0;
    outtextxy(495,1,"TIME REMAINING:");
    outtextxy(6,1,"SCORE:");
    while(1)
    {
        sprintf(a,"%d   ",cnt);//timer
        outtextxy(625,1,a);

        sprintf(b,"%d",score);
        outtextxy(70,1,b);

        putpixel(x,y,2);//snake front
        putpixel(p,q,15);//snake rear

        //food found
        if(((x==fx)||(x==fx-1)||(x==fx+1)||(x==fx-2)||(x==fx+2)) && ((y==fy)||(y==fy-1)||(y==fy+1)||(y==fy-2)||(y==fy+2)))
        {
            if(pin==0)//snake length inc
            q+=-qin*5;
            if(qin==0)
            p+=-pin*5;

            score+=cnt*50;
            food();
            cnt=8;
            k=0;
        }
        if(kbhit())//snake controller
        {
            ch=getch();
            buff[i][0]=x; buff[i][1]=y;
            switch(ch)
            {
                case 72: buff[i][2]=xin=0;
                         buff[i][3]=yin=-1;
                         i++;
                         break;
                case 75: buff[i][3]=yin=0;
                         buff[i][2]=xin=-1;
                         i++;
                         break;
                case 77: buff[i][3]=yin=0;
                         buff[i][2]=xin=1;
                         i++;
                         break;
                case 80: buff[i][2]=xin=0;
                         buff[i][3]=yin=1;
                         i++;
                         break;
                case 81:
                case 113:exiter=2;
                         goto quit;
            }
        }
        if(p==buff[0][0] && q==buff[0][1])
        {
            pin=buff[0][2];
            qin=buff[0][3];
            row=0;
            while(buff[row+1][0]!=0)
            {
                for(col=0;col<4;col++)
                {
                    buff[row][col]=buff[row+1][col];
                }
                row++;
            }
            i--;
        }

        if(x==6 || x==634 || y==21 || y==474)//collision condition
        {exiter=0;break;}

        if(k==105)//unit time over
        {cnt--;k=0;}

        if(cnt==0)//starvation
        {exiter=1;break;}

        p+=pin;
        q+=qin;
        x+=xin;
        y+=yin;
        k++;
        delay(10);
    }

    setcolor(3);

    quit:
    cleardevice();
    setlinestyle(0,0,3);
    drawcircle(320,150,60,3);
    drawcircle(320,150,59,3);
    pieslice(300,130,0,360,4);
    pieslice(340,130,0,360,4);
    arc(320,200,60,120,30);
    settextstyle(9,HORIZ_DIR,1);
    outtextxy(235,305,"YOU SCORED");
    sprintf(b,"%d",score);
    outtextxy(315,340,b);

    if(exiter==2)
    outtextxy(190,240,"YOU LEFT THE GAME");

    if(exiter==0)
    outtextxy(135,240,"YOUR SNAKE BROKE HIS HEAD!");

    if(exiter==1)
    outtextxy(110,240,"YOUR SNAKE DIED OF STARVATION!");

    getch();
    closegraph();
    return 0;
}
