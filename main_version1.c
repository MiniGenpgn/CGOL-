#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int grid[50][50];
int grid2[50][50];
int i,j, Lcount, Ncount, randomx, randomy, size;

void fill(void);
void print(void);
void countNeighbors(void);
void change(void);
void rng(void);
void clear(void);
void wait(void);

int main()
{
    srand(time(NULL));
    
    fill();

    for(Lcount=0;Lcount<100;Lcount++)
    {
        print();
        countNeighbors();
        change();
        rng();
        wait();
        clear();
    }
    
    print();
    
    return 0;
}

void fill(void)
{
    printf("Enter board size: "); // user enters board size (size x size)
    scanf("%i",&size);
    
    for(j=0;j<size;j++)
    {
        for(i=0;i<size;i++)
        {
            grid[j][i]=0;
        }
    }
}

void print(void)
{
    printf("\n\n-----Loop Counter: %i-------\n\n",Lcount);
    printf("\n---random pos--- %i %i\n\n",randomx,randomy);
    printf("\n---neighbor count-- %i\n\n",Ncount);
        
        for(j=0;j<size;j++) // reprints board
        {
            for(i=0;i<size;i++)
            {
                printf("%i ",grid[j][i]);
            }
            
            printf("\n");
        }
}

void countNeighbors(void)
{
    Ncount=0;
    
    for(j=0;j<3;j++)
    {
        for(i=0;i<3;i++)
        {
            if (grid[j-1][i-1]==1)
                Ncount++;
                
            if (grid[j-1][i]==1)
                Ncount++;
                
            if (grid[j-1][i+1]==1)
                Ncount++;
                
            if (grid[j][i-1]==1)
                Ncount++;
                
            if (grid[j][i]==1)
                Ncount++;
                
            if (grid[j][i+1]==1)
                Ncount++;
                
            if (grid[j-1][i-1]==1)
                Ncount++;
        }
        printf("\n");
    }
}

void change(void)
{
    if(Ncount>=4 && grid[j][i]==1)
        grid2[j][i]=0;
        
    else if(Ncount<=1 && grid[j][i]==1)
        grid2[j][i]=0;
        
    else if(Ncount>=2 && Ncount<=3 && grid[j][i]==1)
        grid2[j][i]=1;
        
    else if(Ncount==3 && grid[j][i]==0)
        grid2[j][i]=1;
}

void rng(void)
{
    int seed=0;

    randomy = rand()%size;
    randomx = rand()%size;
    grid[randomy][randomx]=1;
}

void clear(void)
{
    printf("\e[1;1H\e[2J"); // clear console
}

void wait(void)
{
    usleep(100000); // wait
}
