#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leaderboards.h"
#include "getanswer.h"

#define MAX_QUESTIONS 10
#define MAX_PARTICIPANTS 100

// Structure to store questions
struct Question {
    char ques[100];
    char options[4][100];
    int correct;
};

// Remove newline from strings
void removenewline(char *line) {
    line[strcspn(line, "\n")] = '\0';
}

// Load questions from a file
int loadQuestions(const char *filename, struct Question q[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open file: %s\n", filename);
        return 0;
    }

    char line[512];
    int count = 0;

    while (fgets(line, sizeof(line), fp) && count < max) {
        removenewline(line);
        int valid = 1;

        char *token = strtok(line, "-");
        if (!token) continue;

        strncpy(q[count].ques, token, sizeof(q[count].ques)-1);
        q[count].ques[sizeof(q[count].ques)-1] = '\0';

        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, "-");
            if (!token) { valid = 0; break; }
            strncpy(q[count].options[i], token, sizeof(q[count].options[i])-1);
            q[count].options[i][sizeof(q[count].options[i])-1] = '\0';
        }

        token = strtok(NULL, "-");
        if (!token) valid = 0;

        if (valid) {
            q[count].correct = atoi(token);
            if (q[count].correct < 1 || q[count].correct > 4)
                valid = 0;
        }

        if (valid) count++;
    }

    fclose(fp);
    return count;
}

// Shuffle questions array
void shuffleQuestions(struct Question q[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        struct Question temp = q[i];
        q[i] = q[j];
        q[j] = temp;
    }
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

    shuffleQuestions(easy, easyCount);
    shuffleQuestions(medium, mediumCount);
    shuffleQuestions(hard, hardCount);

    struct participants participant[MAX_PARTICIPANTS];
    int participantCount = loadLeaderboard(participant, MAX_PARTICIPANTS);

    struct participants player;
    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';  // remove newline

    int found = 0;
    for (int i = 0; i < participantCount; i++) {
        if (strcmp(participant[i].name, player.name) == 0) {
            if (participant[i].attempts >= 5) {
                printf("You have reached the maximum of 5 trials.\n");
                displayLeaderboard(participant, participantCount);
                return 0;
            }
            found = 1;
            break;
        }
    }

    int difficulty = 0;  // 0=easy, 1=medium, 2=hard
    int score = 0;

    for (int round = 0; round < 10; round++) {
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

        // Pick non-repeating question by round number
        struct Question q = currentSet[round % currentCount];

        printf("\nQuestion %d:\n", round + 1);
        printf("%s\n", q.ques);
        for (int i = 0; i < 4; i++)
            printf("%d. %s\n", i + 1, q.options[i]);

        int answer = getUserAnswer();

        if (answer == q.correct) {
            printf("Correct!\n");
            score++;
            if (difficulty < 2) difficulty++;  // increase difficulty
        } else {
            printf("Wrong! Correct answer: %d\n", q.correct);
            if (difficulty > 0) difficulty--;  // decrease difficulty
        }
    }

    printf("\nYour score: %d / 10\n", score);

    player.score = score;
    updateLeaderboard(participant, &participantCount, player);
    saveLeaderboard(participant, participantCount);
    displayLeaderboard(participant, participantCount);

    return 0;
}
