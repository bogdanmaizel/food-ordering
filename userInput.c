//
// Created by mbogd on 4/11/2019.
//
#include <stdio.h>

void getUserPass(char username[], char password[]) {
    printf("Welcome to FoodThingies!\n");
    printf("Please sign in to continue.\n");
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);
}

void checkBackOption(int choice, int choiceCheck, int *state) {
    if (choice == 'a' + choiceCheck) {
        *state-=2;
    }
}

