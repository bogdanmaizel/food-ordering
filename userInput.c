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
enum State{LOADING_DATA, LOG_IN, CHOOSE_CATEGORY, CHOOSE_TYPE, CHOOSE_DRINK, CHOOSE_CUTLERY, WRITE_NOTE, CONFIRM};
account newAccount() {
    account a;
    a.password = (char*)malloc(30* sizeof(char));
    a.username = (char*)malloc(30* sizeof(char));
    return a;
}

void getUserPass(account *a, int option) {
    printf("%s\n", (option ? SIGNING_UP : SIGNING_IN));
    printf("---Username:\n");
    gets((*a).username);
    printf("---Password:\n");
    gets((*a).password);
}

void checkBackOption(int choice, int choiceCheck, int *state) {
    if (choice == choiceCheck) {
        if (*state==CONFIRM)
        *state-=2;
        else *state-=1;
    }
    else *state+=1;
}

void readOption(int *opt) {
    *opt=getchar()-'a';
    getchar();
}

int attemptLogin(account *a) {
    //char readUser[30],readPass[30];
    account aux = newAccount();
    getUserPass(&aux,0);
    if (strcmp(aux.username, a->username)==0 || strcmp(aux.username,"admin")==0)
        if (strcmp(aux.password,a->password)==0 || strcmp(aux.password, "admin")==0) {
            strcpy(a->username, aux.username);
            strcpy(a->password, aux.password);
            return 1;
        }
            else {
            while (strcmp(aux.password, a->password)) {
                printf("%s\n", INCORRECT_PASSWORD);
                getUserPass(&aux, 0);
            }
            strcpy(a->username, aux.username);
            strcpy(a->password, aux.password);
            return 1;
        }
    else {
        printf("%s\n", USER_NOT_FOUND);
        return 0;
    }
}

int tryRegister(account *a) {
    account aux = newAccount();
    getUserPass(&aux, 1);
    if (strcmp(a->username, aux.username)==0) {
        printf("%s\n", DUPLICATE_USER);
        return 0;
    }
    if (strstr(a->username,aux.password)) {
        printf("%s\n", ERROR_PASSWORD_NOT_USERNAME);
        return 0;
    }
    if (strlen(aux.password)<7) {
        printf("%s\n", ERROR_PASSWORD_LONG);
        return 0;
    }
    if (!((strchr(a->password, '0') || strchr(a->password, '1') || strchr(a->password, '2') || strchr(a->password, '3') || strchr(a->password, '4') ||
    strchr(a->password, '5') || strchr(a->password, '6') || strchr(a->password, '7') || strchr(a->password, '8') || strchr(a->password, '9')))) {
        printf("%s\n", ERROR_PASSWORD_DIGITS);
        return 0;
    }
    if (!(strchr(a->password, '_') || strchr(a->password, '.') || strchr(a->password, '!'))) {
        printf("%s\n", ERROR_PASSWORD_SPECIAL_CHAR);
        return 0;
    }
    strcpy(a->username, aux.username);
    strcpy(a->password, aux.password);
    return 1;
}
