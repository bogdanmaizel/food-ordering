//
// Created by mbogd on 4/11/2019.
//

#ifndef FOOD_ORDERING_USERINPUT_H
#define FOOD_ORDERING_USERINPUT_H

void getUserPass(char username[], char password[]);

void checkBackOption(int choice, int choiceCheck, int *state);

void readOption(int *opt);

int attemptLogin(char user[], char pass[]);

#endif //FOOD_ORDERING_USERINPUT_H
