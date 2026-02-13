#include <stdio.h>
int getUserAnswer() {
    int answer;
    while (1) {
        printf("Your answer (1-4): ");
        if (scanf("%d", &answer) != 1) {
            while (getchar() != '\n');  // clear buffer
            printf("Invalid input. Enter 1-4.\n");
            continue;
        }
        if (answer >= 1 && answer <= 4)
            return answer;
        printf("Enter a number between 1 and 4.\n");
    }
}