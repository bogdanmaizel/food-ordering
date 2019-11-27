//
// Created by mbogd on 4/11/2019.
//
#include <stdio.h>
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
#define SUCCESS "Please choose the food you feel like eating today:"

void getUserPass(char username[], char password[]) {
    printf("Welcome to FoodThingies!\n");
    printf("Please sign in to continue.\n");
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

void login(char *user, char *pass) {
    if (strcmp(user,"admin")==0) if (strcmp(pass, "admin")==0) printf("%s\n", SUCCESS);
                                    else printf("%s\n", INCORRECT_PASSWORD);

}

