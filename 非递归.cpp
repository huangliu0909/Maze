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

int nextpos(int *i,int *j,int di)//i,j为迷宫坐标，di为下一步的方向
{
    switch(di)
    {
        case 1:*i=*i-1;*j=*j-1;break;
        case 2:*i=*i-1;*j=*j;break;
        case 3:*i=*i-1;*j=*j+1;break;
        case 4:*i=*i;*j=*j+1;break;
        case 5:*i=*i+1;*j=*j+1;break;
        case 6:*i=*i+1;*j=*j;break;
        case 7:*i=*i+1;*j=*j-1;break;
        case 8:*i=*i;*j=*j-1;break;
    }
    return 1;
}

mazestack *stackmaze(int i1,int j1,int i2,int j2,int a[][7])
{
    int i=i1,j=j1;
    int k;
    mazestack *p;
    p = create();
    do{
        if(a[i][j]==1)
        {
            a[i][j]=9;
            p=push(p,i,j,a[i][j]);
            if(i==i2&&j==j2)
            {
                for(i=0;i<7;i++)
                {
                    for(j=0;j<7;j++)
                    {
                        if(a[i][j]>1)
                        {
                            a[i][j]=9;
                            printf(" %d ",a[i][j]);
                        }
                        else printf(" %d ",a[i][j]);
                    }
                    printf("\n");
                }
                return p;
            }
            nextpos(&i,&j,1);
        }else{
            if(!empty(p))
            {
                p=pop(p,&i,&j,&k);
                a[i][j]=k;
                while(a[i][j]==8&&!empty(p))
                {
                    a[i][j]=1;
                    p=pop(p,&i,&j,&k);
                    a[i][j]=k;
                }
                if(a[i][j]<8)
                {
                    a[i][j]++;
                    p=push(p,i,j,a[i][j]);
                    nextpos(&i,&j,a[i][j]);
                }
                else if(a[i][j]>8)
                {
                    a[i][j]=2;
                    p=push(p,i,j,a[i][j]);
                    nextpos(&i,&j,a[i][j]);
                }
                //printf("(%d,%d)-> ",i,j);
            }
        }
    }while(!empty(p));
    printf("\n");
    return NULL;
}


int main()
{
start:
    printf("0:wall，1:path\n");
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
    ma = stackmaze(1,1,5,5,a);
    if(ma==NULL)
        printf("no reasonable path\n");
    else
    {
        printf("inverted order of the path: ");
        while(!empty(ma))
        {
            printf("(%d %d) ",ma->a,ma->b);
            ma=pop(ma,&ma->a,&ma->b,&ma->direction);
        }
    }


    return 0;
}
