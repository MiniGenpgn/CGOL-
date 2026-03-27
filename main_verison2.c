#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int grid[50][50];
int grid2[50][50];
int gridAge[50][50];
int i,j, Lcount, randomx, randomy, size;

void fill(void);
void print(void);
void change(void);
void rng(void);
void clear(void);
void wait(void);
void reprint(void);
void color(void);

int main()
{
    srand(time(NULL));
    
    fill();
    print();
    rng();

    for(Lcount=0;Lcount<=100;Lcount++)
    {
        change();
        color();
        wait();
        clear();
        reprint();
    }
    
    return 0;
}

void fill(void)
{
    printf("Enter board size: "); // user enters board size (size x size)
    scanf("%i",&size);
    
    for(j=0;j<size;j++) // sets each cell
    {
        for(i=0;i<size;i++)
        {
            grid[j][i]=0; // og grid
            grid2[j][i]=0; // changed grid
            gridAge[j][i]=0; // grid for each cell's age
        }
    }
}

void print(void)
{
    printf("\n\n-----Loop Counter: %i-------\n\n",Lcount);
        
        for(j=0;j<size;j++) // prints 1st board
        {
            for(i=0;i<size;i++)
            {
                printf("%i ",grid[j][i]);
            }
            
            printf("\n");
        }
}

void reprint(void)
{
    printf("\n\n---------Loop Counter: %i-----------\n\n",Lcount);
    
    for(j=0;j<size;j++)
    {
        for(i=0;i<size;i++)
        {
            grid[j][i]=grid2[j][i]; // sets changed board to og board
        }
    }
    
    for(j=0;j<size;j++) // reprints board
    {
        for(i=0;i<size;i++)
        {
            if(grid2[j][i]==0) // if cell is dead
            {
                printf("\e[46m"); // cyan
                printf("⁻ ");
            }
                
            else if(grid2[j][i]==1) // if cell is alive
            {
                if(gridAge[j][i]==1) // if cell age is 1
                {
                    printf("\e[42m"); // green
                    printf("⏺ ");
                }
                
                if(gridAge[j][i]==2) // if cell age is 2
                {
                    printf("\e[43m"); // yellow
                    printf("⏺ ");
                }
                
                if(gridAge[j][i]==3) // if cell age is 3
                {
                    printf("\e[41m"); // red
                    printf("⏺ ");
                }
                
                else // if cell age is greater than that
                {
                    printf("\e[40m"); // black
                    printf("⏺ ");
                }
                
                printf("\e[46m"); // resets colors
            }
        }
        
        printf("\n");
    }
    
    printf("\e[0m"); // resets colors
}

void change(void)
{
    for(j=0;j<size;j++)
    {
        for(i=0;i<size;i++)
        {   
            // checking each cell
            // 0-8 based on how many are live
            
            int neighbors = grid[j-1][i-1]+grid[j-1][i]+grid[j-1][i+1]+grid[j][i-1]+grid[j][i]+grid[j][i+1]+grid[j+1][i-1]+grid[j+1][i]+grid[j+1][i+1];
            // finding # of neighbors per cell
            
            if(neighbors>=4 && grid[j][i]==1) // if more than 4 neighbors and it is alive
                grid2[j][i]=0; // then it dies
                
            else if(neighbors<=1 && grid[j][i]==1) // if less than or equal to 1 neighbor and it is alive
                grid2[j][i]=0; // then it dies
                
            else if(neighbors>=2 && neighbors<=3 && grid[j][i]==1) // if neighbors is 2 or 3 and it is alive
                grid2[j][i]=1; // stay alive
                
            else if(neighbors==3 && grid[j][i]==0) // if neighbors is 3 and it is dead
                grid2[j][i]=1; // come back to life
        }
    }
}

void rng(void)
{
    int z=0;
    
    while(z<size*10) // loop until counter is 40
    {
        randomy = rand()%size; // randomize y and x
        randomx = rand()%size;
        grid[randomy][randomx]=1; // set that specific random cell to alive
        z++; // add 1 to counter
    }
}

void clear(void)
{
    printf("\e[1;1H\e[2J"); // clear console
}

void wait(void)
{
    usleep(120000); // wait
}

void color(void)
{
    for(j=0;j<size;j++)
    {
        for(i=0;i<size;i++)
        {
            if(grid2[j][i]==1) // if the cell is alive
                gridAge[j][i]=gridAge[j][i]+1; // add age to cell in age array
        }
    }
}
