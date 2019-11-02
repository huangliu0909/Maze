#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct maze
{
    int a;
    int b;
    int direction;
    struct maze *next;
}mazestack;

mazestack *create()
{
    mazestack *p;
    p = (mazestack*)malloc(sizeof(mazestack));
    if(!p)
        return NULL;
    p->next = NULL;
    return p;
}

mazestack *push(mazestack *p,int i,int j,int k)
{
    mazestack *q;
    q = (mazestack *)malloc(sizeof(mazestack));
    if(!q)
        return NULL;
    q->a = i;
    q->b = j;
    q->direction = k;
    q->next = p;
    p = q;
    return p;
}

mazestack *pop(mazestack *p,int *i,int *j,int *k)
{
    mazestack *q;
    q = p;
    *i = q->a;
    *j = q->b;
    *k = q->direction;
    p = p->next;
    free(q);
    return p;
}

int empty(mazestack *p)
{
    if(p->next == NULL)
        return 1;
    else
        return 0;
}


bool next(int (*a)[7],int i,int j)
{

    if(j==5&&i==5)
    {
        printf(" (5,5)  Success!");
        return true;
    }
    else if(i>0&&i<6&&j>0&&j<6)
    {
         if(a[i+1][j]==1)
        {
            printf(" (%d,%d) ",i,j);    //输出
            a[i][j]=0;
            next( a,i+1,j);//递归
            return true;
        }
        else if(a[i-1][j]==1)
        {
            printf(" (%d,%d) ",i,j);    //输出
            a[i][j]=0;
            next(a,i-1,j);
            return true;
        }

        else if(a[i][j+1]==1)
        {
            printf(" (%d,%d) ",i,j);    //输出
            a[i][j]=0;
            next(a,i,j+1);
            return true;
        }

        else  if(a[i][j-1]==1)
        {
            printf(" (%d,%d)  ",i,j);    //输出
            a[i][j]=0;
            next(a,i,j-1);
            return true;
        }
        else return false;
    }

    else
        return false;

}

int main()
{
start:
    printf("0为墙，1为路\n");
    mazestack *ma,*mb;
    int i,j,a[7][7] = {0};
    srand( (unsigned)time( NULL ) );
        for(i=1;i<6;i++)
        {
            for(j=1;j<6;j++)
            {
                a[i][j] = rand()%2;
                //printf(" %d",maze[i][j]);
            }
        }
        a[1][1]=1;a[5][5]=1;
        for(i=0;i<7;i++)
        {
            for(j=0;j<7;j++)
            {
                printf(" %d,",a[i][j]);
            }
            printf("\n");
        }
        getchar();
    printf("\n");

    i=1;j=1;
    next(a,1,1);
    printf("     stop");
    return 0;
}
