#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "leaderboards.h"   


#define MAX_PARTICIPANTS 100



int loadLeaderboard(struct participants participant[], int max) {
    FILE *fp = fopen("leaderboard.txt", "r");
    if (!fp) return 0;

    int count = 0;
    while (fscanf(fp, "%49[^;];%d;%d\n", participant[count].name,
                  &participant[count].score, &participant[count].attempts) == 3
           && count < max) {
        count++;
    }

    fclose(fp);
    return count;
}

/* Save leaderboard */
void saveLeaderboard(struct participants participant[], int count) {
    FILE *fp = fopen("leaderboard.txt", "w");
    if (!fp) {
        printf("Error: Cannot write leaderboard\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s;%d;%d\n", participant[i].name, participant[i].score, participant[i].attempts);
    }

    fclose(fp);
}

/* Update leaderboard */
void updateLeaderboard(struct participants participant[], int *count, struct participants p) {
    int i;
    for (i = 0; i < *count; i++) {
        if (strcmp(participant[i].name, p.name) == 0) {
            if (participant[i].attempts >= 5) {
                printf("Sorry %s, you have reached the maximum of 5 trials.\n", p.name);
                return;
            }
            participant[i].score = p.score;
            participant[i].attempts++;
            break;
        }
    }

    if (i == *count && *count < MAX_PARTICIPANTS) {
        participant[*count] = p;
        participant[*count].attempts = 1;
        (*count)++;
    }

    // Sort leaderboard by score descending
    for (int j = 0; j < *count - 1; j++) {
        for (int k = j + 1; k < *count; k++) {
            if (participant[j].score < participant[k].score) {
                struct participants temp = participant[j];
                participant[j] = participant[k];
                participant[k] = temp;
            }
        }
    }
}

/* Display leaderboard */
void displayLeaderboard(struct participants participant[], int count) {
    printf("\n===== Leaderboard =====\n");
    printf("%-20s %-10s %-10s\n", "Name", "Score", "Attempts");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10d %-10d\n", participant[i].name, participant[i].score, participant[i].attempts);
    }
    printf("=======================\n");
}
