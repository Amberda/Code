#include <stdio.h>
#include <unistd.h>
#include "keyboard.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>

int FC = 5;
#define BC 7
#define W 10  //地图宽度
#define H 20  //地图高度

struct data{
    int x;  //列
    int y;   //行
};
struct data t={5,0};
int cur=0;

struct shape{
    int s[5][5];
};

int background[H][W]={0}; //地图

struct shape shape_arr[7]={
    {
        0,0,0,0,0,
        0,0,1,0,0,
        0,1,1,1,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,0,0,0,
        0,1,0,0,0,
        0,1,1,1,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,0,0,0,
        0,0,0,1,0,
        0,1,1,1,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,0,0,0,
        0,0,1,1,0,
        0,1,1,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,0,0,0,
        0,1,1,0,0,
        0,0,1,1,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,0,0,0,
        0,1,1,0,0,
        0,1,1,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,0,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,0,0,0
    }
};

void drow_element(int x,int y,int c)
{
    x*=2;                             //x坐标占用两个字符
    x++;
    y++;
    printf("\033[?25l");              //隐藏光标
    printf("\033[%d;%dH",y,x);        //控制光标位置
    printf("\033[3%dm\033[4%dm",c,c); //设置颜色
    printf("[]");                     //输出方块
    fflush(stdout);                   //刷新缓存
    printf("\033[0m");                //关闭设置属性
}

void drow_shape(int x,int y,struct shape p,int c)
{
    int i=0;
    for(;i<5;i++)
    {
        int j=0;
        for(;j<5;j++)
        {
            if(p.s[i][j]!=0)
            {
                drow_element(x+j,y+i,c);
            }
        }
    }
}

void drow_back()
{
    int i=0;
    for(;i<H;i++)
    {
        int j=0;
        for(;j<W;j++)
        {
            if(background[i][j]==0)
                drow_element(j,i,BC);
            else
                drow_element(j,i,FC);
                //drow_element(j,i,background[i][j]);
        }
    }
}

void set_back(struct data *t,struct shape p)
{
    int i=0;
    for(;i<5;i++)
    {
        int j=0;
        for(;j<5;j++)
        {
            if(p.s[i][j]!=0)
            {
                background[t->y+i][t->x+j]=1;//FC;//1;
            }
        }
    }
}

int can_move(int x,int y,struct shape p)
{
    int i=0;
    for(;i<5;i++)
    {
        int j=0;
        for(;j<5;j++)
        {
            if(p.s[i][j]==0)
                continue;
            if(x+j>=W ||x+j<0)
                return 0;
            if(y+i>=H)
                return 0;
            if(background[y+i][x+j]!=0)
                return 0;
        }
    }
    return 1;
}

void mclean_line()
{
    int i=0;
    for(;i<H;i++)
    {
        int total=0;
        int j=0;
        for(;j<W;j++)
        {
            if(background[i][j]!=0)
                total++;
        }
        if(total==W)
        {
            int k=i;
            for(;k>0;k--)
                memcpy(background[k],background[k-1],sizeof(background[k]));
            memset(background[0],0x00,sizeof(background[0]));
        }
    }
}

void tetris_timer(struct data* t)
{
    
    drow_shape(t->x,t->y,shape_arr[cur],BC);
    if(can_move(t->x,t->y+1,shape_arr[cur])==1)
    {
        t->y++;
    }
    else
    {
        set_back(t,shape_arr[cur]);
        mclean_line();
        drow_back();
        do{
            FC=rand()%8;
        }while(FC==BC);
        t->y=0;
        t->x=0;
        cur=rand()%7;
    }
    drow_shape(t->x,t->y,shape_arr[cur],FC);
}

struct shape turn_90(struct shape p)
{
    struct shape t;
    
    int i=0;
    for(;i<5;i++)
    {
        int j=0;
        for(;j<5;j++)
        {
            t.s[i][j]=p.s[4-j][i];
        }
    }
    return t;
}

int tetris(struct data* t)
{
    int ret=0;
    int c=get_key();
    if(is_up(c))
    {
        drow_shape(t->x,t->y,shape_arr[cur],BC);
        shape_arr[cur]=turn_90(shape_arr[cur]);
        if(can_move(t->x,t->y,shape_arr[cur])==0)
        {
            shape_arr[cur]=turn_90(shape_arr[cur]);
            shape_arr[cur]=turn_90(shape_arr[cur]);
            shape_arr[cur]=turn_90(shape_arr[cur]);
        }
        drow_shape(t->x,t->y,shape_arr[cur],FC);
    }
    else if(is_left(c))
    {
        drow_shape(t->x,t->y,shape_arr[cur],BC);
        if(can_move(t->x-1,t->y,shape_arr[cur])==1)
            t->x--;
        drow_shape(t->x,t->y,shape_arr[cur],FC);
    }
    else if(is_right(c))
    {
        drow_shape(t->x,t->y,shape_arr[cur],BC);
        if(can_move(t->x+1,t->y,shape_arr[cur])==1)
            t->x++;
        drow_shape(t->x,t->y,shape_arr[cur],FC);
    }
    else if(is_down(c))
    {
        drow_shape(t->x,t->y,shape_arr[cur],BC);
        if(can_move(t->x,t->y+1,shape_arr[cur]))
            t->y++;
        drow_shape(t->x,t->y,shape_arr[cur],FC);
    }
    else if(is_esc(c))
    {
        ret=1;
    }
    return ret;
}

void handler(int sig)
{
    if(sig==SIGALRM)
        tetris_timer(&t);
    else if(sig=SIGINT)
    {
        printf("\033[0m");
        printf("\033[?25h");
        recover_keyboard();
        exit(0);
    }
}

int main()
{
    init_keyboard();
    drow_back();

    struct sigaction act;
    act.sa_handler=handler;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGALRM,&act,NULL);
    sigaction(SIGINT,&act,NULL);

    struct itimerval it;
    it.it_value.tv_sec=0;
    it.it_value.tv_usec=1;

    it.it_interval.tv_sec=1;
    it.it_interval.tv_usec=0;
    setitimer(ITIMER_REAL,&it,NULL);

    while(1)
    {
        if(tetris(&t)==1)
            break;
    }

    printf("\033[?25h");
    recover_keyboard();
    return 0;
}
