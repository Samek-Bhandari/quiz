#include <stdio.h>
#include <conio.h>

//function to keep the records
void records(char *filename)
{
    FILE *fp =fopen (filename,"a");
    

}

//function to display questions

void readquestion(char *filename )
{
    FILE *fp =fopen(filename,"r");
    if (!fp)
        {
            printf("File could not be opened !!");
         }

}

int main(){
    printf ("Enter the name of the Participant");






}