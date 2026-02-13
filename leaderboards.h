#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H

#define MAX_PARTICIPANTS 100

struct participants {
    char name[50];
    int score;
    int attempts;
};

// Function prototypes
int loadLeaderboard(struct participants participant[], int max);
void saveLeaderboard(struct participants participant[], int count);
void updateLeaderboard(struct participants participant[], int *count, struct participants p);
void displayLeaderboard(struct participants participant[], int count);

#endif
