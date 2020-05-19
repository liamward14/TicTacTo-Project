#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>

//Global Variables
COORD coord = {0,0};
char grid[3][3]; //Game grid
char solution[11]; //will hold type of soln
char winner[9]; //Will store who won
char p1,p2; //will hold 'X' or 'O' depending on user entry


void gotoxy(int x, int y); //cursor position prototpye
void display(int ypos); //grid display prototpye
void display_I(); //Instructions display prototype
bool win_check(void); //Win checker prototype

int main()
{
    int x;
    int y; //looping vars
    char input; //enter to go to next stage
    char sinput;

    /*Populate & display array*/
    for(x=0;x<3;x++) // loops through rows
    {
        for(y=0;y<3;y++) // loops through columns for each row
        {
            grid[x][y] = '.';
        }
    }

    /*Play Game:*/
    bool win = false; //default status - changes when a player wins
    int last_y_pos; //stores last y position
    char select; //player selection
    int pos[2];
    char positions[] = {'X','Y'};
    int i; //looping var
    int j; //second loo
    int ptrack; //integer to keep track of which player is playing
    char current_coord; //dynamic selection

    gotoxy(30,4);
    printf("Welcome to Tic Tac Toe!\n");
    gotoxy(30,6);
    printf("Instructions:\n");
    gotoxy(30,7);
    printf("Select 'X' or 'O' to get assigned a placeholder.\n");
    gotoxy(30,8);
    printf("Then, enter the x,y position where you would\n");
    gotoxy(30,9);
    printf("like to place your selection.");
    gotoxy(45,11);
    //printf("Grid");

    //Display Grid
    display(12);
    gotoxy(30,16);
    printf("Player 1, select your value ('X' or 'O'):");
    scanf("%c",&p1);
    system("cls"); //clear screen
    gotoxy(45,11);
    display(12);

    if (toupper(p1)=='X')
    {
        p2 = 'O';
    }
    else if (toupper(p1)=='O')
    {
        p2 = 'X';
    }
    else
    {
        gotoxy(30,16);
        printf("Invalid entry");
        gotoxy(30,17);
        printf("Player 1 has been assigned: 'X'");
        gotoxy(30,18);
        printf("Player 2 has been assigned: 'O'");
        gotoxy(30,19);
        printf("The game will start shortly");
        p1 = 'X';
        p2 = 'O';
        sleep(2.5); //sleep for 2.5 seconds
        system("cls");
        gotoxy(45,11);
        display(12); // put the grid back on the screen
    }

    ptrack = 1; //to track player turns
    int counter = 0; // for user control

    while(win==false) //run game
    {
        if (counter==1)
        {
            char i_select;
            gotoxy(30,4);
            printf("This message will only display once");
            gotoxy(30,5);
            printf("To show the instructions again, press 'I', otherwise press 'Enter': ");
            scanf("%c",&i_select);

            if (i_select=='I')
            {
                display_I();
                input = getchar();
                sinput = getchar();
                system("cls");
                display(12);
            }
            else
            {
                system("cls");
                display(12);
            }

        }
       // scanf("%c",&select);
       if (ptrack==1)
       {
           select = p1;
       }
       else if (ptrack==2)
       {
           select = p2;
       }
       gotoxy(30,16);
       printf("Player %d's turn, using %c",ptrack,select);
       //gotoxy(30,16);



        int xsel; //temporary
        int ysel;
        for (j=0;j<2;j++) // to select x and y positions
        {
            gotoxy(30,17+j);
            current_coord = positions[j];
            printf("Enter the %c position (1,2,3): ",current_coord);
            if(j==0)
            {
                scanf("%d",&xsel);
                int spacex_counter=0;
                while(xsel<0||xsel>3)
                {
                    gotoxy(30,18+j+spacex_counter);
                    printf("Invalid selection, please try again");
                    gotoxy(30,19+j+spacex_counter);
                    printf("Enter the %c position (1,2,3): ",current_coord);
                    scanf("%d",&xsel);
                    spacex_counter = spacex_counter+2;
                }
                system("cls"); //clear screen
                gotoxy(45,11); //reposition
                display(12); //display grid
                gotoxy(30,17+j);
                printf("Enter the %c position (1,2,3):%d",current_coord,xsel);
                pos[j] = xsel-1; //account for array indexing order
            }
            else if (j==1)
            {
                scanf("%d",&ysel);
                int spacey_counter=0;
                while(ysel<0||ysel>3)
                {
                    gotoxy(30,18+j+spacey_counter);
                    printf("Invalid selection, please try again");
                    gotoxy(30,19+j+spacey_counter);
                    printf("Enter the %c position (1,2,3): ",current_coord);
                    scanf("%d",&ysel);
                    spacey_counter = spacey_counter+2;
                }
                system("cls");//clear screen
                gotoxy(45,11);//reposition
                display(12);
                gotoxy(30,16+j);
                printf("Enter the %c position (1,2,3):%d",'X',xsel);
                gotoxy(30,17+j);
                printf("Enter the %c position (1,2,3):%d",current_coord,ysel);
                pos[j] = ysel-1; //account for array indexing order
            }
        }

        //Exit selection loop, update tic tac toe array
        gotoxy(30,19);
        printf("Player %d's selection: %c at position (%d,%d)",ptrack,select,xsel,ysel);

        //Update array
        char select_upper = toupper(select);
        grid[pos[0]][pos[1]] = select_upper;
        //printf("%d",grid[0][0]);
        display(12); //replace grid with update

        if (ptrack==1)
        {
            ptrack=2;
        }
        else
        {
            ptrack = 1;
        }
        //last_y_pos = 20+5*counter;
        gotoxy(30,21);
        printf("To move on to the next turn/or view the results, press the 'Enter' Key: ");
        /*gotoxy(30,21);
        printf("Or, to view the instructions again, press 'I'");
        gotoxy(30,22);
        printf("Selection:");*/

        input = getchar();
        sinput = getchar();
        system("cls"); //clears screen
        display(12); //put grid back on screen
        counter++; //update counter

        if (counter>=1)
        {
            win = win_check();

        }

    }

    char input3;
    char input4;
    gotoxy(30,21);
    printf("We have a winner!");
    gotoxy(30,22);
    printf("%s is the winner!",winner);
    gotoxy(30,23);
    printf("The winning solution is: %s",solution);
    gotoxy(30,24);
    printf("Press 'Enter' twice to exit the game");
    input3 = getchar();
    input4 = getchar();

}

//Function to move to specific point
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void display(int ypos)
{
    //This function displays the updated grid
    gotoxy(45,ypos-1);
    printf("Grid");
    int x;
    int y; //looping vars
    for(x=0;x<3;x++)
    {
        gotoxy(44,ypos+x);
        for(y=0;y<3;y++)
        {
            printf("%c  ",grid[x][y]);
        }
        printf("\n");
    }
}




void display_I(void)
{
    gotoxy(30,6);
    printf("Instructions:\n");
    gotoxy(30,7);
    printf("Select 'X' or 'O' to get assigned a placeholder.\n");
    gotoxy(30,8);
    printf("Then, enter the x,y position where you would\n");
    gotoxy(30,9);
    printf("like to place your selection.");
    gotoxy(30,10);
    printf("Press 'Enter' to confirm that you understand");
}

bool win_check(void)
{
    char solution1[] = {'X','X','X','\0'};
    char solution2[] = {'O','O','O','\0'};
    int x; //looping vars

    //This nested loop check for vertical or horizontal wins
    for(x=0;x<3;x++)
    {
        char hbuffer[4] = {grid[x][0],grid[x][1],grid[x][2],'\0'}; // Holds horizontal solns
        char vbuffer[4] = {grid[0][x],grid[1][x],grid[2][x],'\0'}; // Holds vertical solns
        int comph1,comph2;
        int compv1,compv2;

        comph1 = strcmp(solution1,hbuffer);
        comph2 = strcmp(solution2,hbuffer); // only checks for horizontal wins

        compv1 = strcmp(solution1,vbuffer);
        compv2 = strcmp(solution2,vbuffer); // only checks for vertical wins

        if (comph1==0) //'xxx' solution
        {
            if (p1=='X')
            {
                strcpy(winner,"Player 1");
            }
            else if (p2=='X')
            {
                strcpy(winner,"Player 2");
            }
            strcpy(solution,"Horizontal");
            return(true);//Horizontal Win!
        }
        else if (comph2==0)// 'ooo' solution
        {
            if (p1=='O')
            {
                strcpy(winner,"Player 1");
            }
            else if (p2=='O')
            {
                strcpy(winner,"Player 2");
            }
            strcpy(solution,"Horizontal");
            return(true);//Horizontal Win!
        }
        else if (compv1==0)
        {
            if (p1=='X')
            {
                strcpy(winner,"Player 1");
            }
            else if (p2=='X')
            {
                strcpy(winner,"Player 2");
            }
            strcpy(solution,"Vertical");
            return(true);//Vertical Win!
        }
        else if (compv2==0)
        {
            if (p1=='O')
            {
                strcpy(winner,"Player 1");
            }
            else if (p2=='O')
            {
                strcpy(winner,"Player 2");
            }
            strcpy(solution,"Vertical");
            return(true);//Vertical Win!
        }
    }

    //Check for diagonal wins

    char dbuffer[4] = {grid[0][0],grid[1][1],grid[2][2],'\0'}; //will hold each diagonal temporary check for win
    char dbuffer2[4] = {grid[0][2],grid[1][1],grid[2][0],'\0'}; //will hold each diagonal temporary check for a win (opposite direction)
    int dcmp1,dcmp2,dcmp3,dcmp4;

    dcmp1 = strcmp(solution1,dbuffer);
    dcmp2 = strcmp(solution2,dbuffer);
    dcmp3 = strcmp(solution1,dbuffer2);
    dcmp4 = strcmp(solution2,dbuffer2);

    if (dcmp1==0||dcmp3==0)
    {
        if (p1=='X')
        {
            strcpy(winner,"Player 1");
        }
        else if (p2=='X')
        {
            strcpy(winner,"Player 2");
        }
        strcpy(solution,"Diagonal");
        return(true); //Win! (Diagonal)
    }
    else if (dcmp2==0||dcmp4==0)
    {
        if (p1=='O')
        {
            strcpy(winner,"Player 1");
        }
        else if (p2=='O')
        {
            strcpy(winner,"Player 2");
        }
        strcpy(solution,"Diagonal");
        return(true); //Win! (Diagonal)
    }
    return(false); //if no wins are detecteds
}
