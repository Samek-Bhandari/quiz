#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_QUESTIONS 10
#define MAX_PARTICIPANTS 100

//Structure to print the questions and options
struct Question{
    char ques[100];
    char options [4][100];
    int correct;
};

//structures for participants
struct participants{
    char name[100];
    int score;
    int attempts;
};



//To remove new line 

void removenewline (char *line)
{
    line[strcspn(line,"/n")]='/0';
}

//function to display questions

int readquestion(char *filename, struct Question q[], int max )
{
    FILE *fp =fopen(filename,"r");
    if (!fp)
        {
            printf("File %s could not be opened !!", filename);
            return 0;
         }
         char line[100];
         int count;
         int valid;

         while (fgets(line, sizeof(line),fp) && count < max)
         {
            removenewline (line);
            
            char *token = strtok (line,"-");
            if (!token) {continue;}

            strncpy(q[count].ques, token, sizeof(q[count].ques) - 1);
             q[count].ques[sizeof(q[count].ques) - 1] = '\0';
             int token=1;

             token = strtok(NULL, "-");
                if (!token) {valid = 0;}

                if (valid==1)
                 {
                    q[count].correct = atoi(token);
                    if (q[count].correct >= 1 && q[count].correct <= 4)
                     {
                count++;
                    }
                }
            }

    fclose(fp);
    return count;
}



int main() {
    srand((unsigned int)time(NULL));

    struct Question easy[MAX_QUESTIONS], medium[MAX_QUESTIONS], hard[MAX_QUESTIONS];
    int easyCount = loadQuestions("easy.txt", easy, MAX_QUESTIONS);
    int mediumCount = loadQuestions("medium.txt", medium, MAX_QUESTIONS);
    int hardCount = loadQuestions("hard.txt", hard, MAX_QUESTIONS);

    if (easyCount + mediumCount + hardCount == 0) {
        printf("No questions loaded. Exiting.\n");
        return 1;
    }

    struct participants participant[MAX_PARTICIPANTS];
    int participantCount = loadLeaderboard(participant, MAX_PARTICIPANTS);

     struct participants player;
    printf("Enter your name: ");
    scanf("%49s", player.name);

    int found = 0;
    for (int i = 0; i < participantCount; i++) {
        if (strcmp(participant[i].name, player.name) == 0) {
            if (participant[i].attempts >= 5) {
                printf("You have reached the maximum of 5 trials. Cannot play again.\n");
                displayLeaderboard(participant, participantCount);
                return 0;
            }
            found = 1;
            break;
        }
    }

    int difficulty = 0;  // 0=easy,1=medium,2=hard
    int score = 0;

    for (int round = 0; round < 5; round++) {
        struct Question *currentSet = NULL;
        int currentCount = 0;

        if (difficulty == 0 && easyCount > 0) {
            currentSet = easy;
            currentCount = easyCount;
        } else if (difficulty == 1 && mediumCount > 0) {
            currentSet = medium;
            currentCount = mediumCount;
        } else if (difficulty == 2 && hardCount > 0) {
            currentSet = hard;
            currentCount = hardCount;
        } else {
            printf("No questions available for this difficulty.\n");
            break;
        }

        struct Question q = currentSet[rand() % currentCount];

        printf("\nQuestion %d:\n", round + 1);
        printf("%s\n", q.ques);
        for (int i = 0; i < 4; i++)
            printf("%d. %s\n", i + 1, q.options[i]);

        int answer = getUserAnswer();

        if (answer == q.correct) {
            printf("Correct!\n");
            score++;
            if (difficulty < 2) difficulty++;
        } else {
            printf("Wrong! Correct answer: %d\n", q.correct);
            if (difficulty > 0) difficulty--;
        }
    }

    printf("\nYour score: %d / 5\n", score);

    player.score = score;
    updateLeaderboard(participant, &participantCount, player);
    saveLeaderboard(participant, participantCount);
    displayLeaderboard(participant, participantCount);

    return 0;
}






