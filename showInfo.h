//
// Created by mbogd on 4/11/2019.
//

#ifndef FOOD_ORDERING_SHOWINFO_H
#define FOOD_ORDERING_SHOWINFO_H

#include "food.h"

typedef struct _order {
    food ordFood;
    drink ordDrink;
} order;

order newOrder();

void showFood(int noOfMeals, char **meals);

void showFoodWithPrice(char foodType[], int noOfMeals, char **meals, double *prices);

void askCutlery();

void printCutleryAndMessage(int cutlery, int info, char infoMsg[]);

void printUser(char username[]);

void printOrder(food f, drink d);

#endif //FOOD_ORDERING_SHOWINFO_H
