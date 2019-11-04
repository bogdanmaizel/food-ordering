//
// Created by mbogd on 4/11/2019.
//
#include <stdio.h>

void getUserPass(char username[], char password[]) {
    printf("Please sign in to continue.\n");
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);
}
