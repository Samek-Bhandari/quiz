//function to keep the records
void records(char *filename)
{
    char name[100];
    FILE *fp =fopen (filename,"a");
    printf ("Enter the name of the Participant");
    gets (name);
    while(1){
        char str[100]
        gets(str);
        if (strcmp(str,name)=0)
        {
            fputs (name,fp);
        }
if (participants.attempt>4)
{
    printf("Maximum of 5 attempts completed ");
   break;
}


}
}