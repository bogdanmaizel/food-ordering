//
// Created by mbogd on 4/11/2019.
//

#ifndef FOOD_ORDERING_USERINPUT_H
#define FOOD_ORDERING_USERINPUT_H

typedef struct _account {
    char *username, *password;
} account;

account newAccount();

void getUserPass(account *a, int option);

void checkBackOption(int choice, int choiceCheck, int *state);

void readOption(int *opt);

int attemptLogin(account *a);

int tryRegister(account *a);

#endif //FOOD_ORDERING_USERINPUT_H
