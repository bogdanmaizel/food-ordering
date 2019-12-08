//
// Created by mbogd on 4/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "userInput.h"
#include <string.h>
#define ERROR_PASSWORD_LONG	"The password must be at least 7 chars long"
#define ERROR_PASSWORD_NOT_USERNAME	"The password must not contain the username"
#define ERROR_PASSWORD_SPECIAL_CHAR	"The password must contain one of the following characters: {'.','_','!'}"
#define ERROR_PASSWORD_DIGITS	"The password must contain digits"
#define SIGN_IN_UP	"Do you want to sign in or sign up?"
#define SIGN_IN	"Sign in"
#define SIGN_UP	"Sign up"
#define SIGNING_IN	"Signing in!"
#define SIGNING_UP	"Signing up!"
#define USER_NOT_FOUND	"Username doesn't exist"
#define DUPLICATE_USER	"Please choose another username!"
#define INCORRECT_PASSWORD	"Incorrect password"


void getUserPass(char username[], char password[], int option) {
    printf("%s\n", (option ? SIGNING_UP : SIGNING_IN));
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);
}

void checkBackOption(int choice, int choiceCheck, int *state) {
    if (choice == choiceCheck) {
        if (*state==6)
        *state-=2;
        else *state-=1;
    }
    else *state+=1;
}

void readOption(int *opt) {
    *opt=getchar()-'a';
    getchar();
}

int attemptLogin(char *user, char *pass) {
    char readUser[30],readPass[30];
    getUserPass(readUser,readPass,0);
    if (strcmp(readUser, user)==0 || strcmp(readUser,"admin")==0)
        if (strcmp(readPass,pass)==0 || strcmp(readPass, "admin")==0) return 1;
            else {
            while (strcmp(readPass, pass)) {
                printf("%s\n", INCORRECT_PASSWORD);
                getUserPass(readUser, readPass, 0);
            }
            return 1;
        }
    else {
        printf("%s\n", USER_NOT_FOUND);
        return 0;
    }
}

int tryRegister(char *user, char *pass) {
    char *username = (char*)malloc(30* sizeof(char)), *password = (char*)malloc(30* sizeof(char));
    getUserPass(username,password, 1);
    if (strcmp(user, username)==0) {
        printf("%s\n", DUPLICATE_USER);
        return 0;
    }
    if (strstr(username,password)) {
        printf("%s\n", ERROR_PASSWORD_NOT_USERNAME);
        return 0;
    }
    if (strlen(password)<7) {
        printf("%s\n", ERROR_PASSWORD_LONG);
        return 0;
    }
    if (!((strchr(password, '0') || strchr(password, '1') || strchr(password, '2') || strchr(password, '3') || strchr(password, '4') ||
    strchr(password, '5') || strchr(password, '6') || strchr(password, '7') || strchr(password, '8') || strchr(password, '9')))) {
        printf("%s\n", ERROR_PASSWORD_DIGITS);
        return 0;
    }
    if (!(strchr(password, '_') || strchr(password, '0') || strchr(password, '0'))) {
        printf("%s\n", ERROR_PASSWORD_SPECIAL_CHAR);
        return 0;
    }
    return 1;
}
