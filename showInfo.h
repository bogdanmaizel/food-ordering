//
// Created by mbogd on 4/11/2019.
//

#ifndef FOOD_ORDERING_SHOWINFO_H
#define FOOD_ORDERING_SHOWINFO_H

void showFood(int noOfMeals, char **meals);

void showFoodWithPrice(char foodType[], int noOfMeals, char **meals, double prices[]);

void askCutlery();

void printCutleryAndMessage(int cutlery, int info, char infoMsg[]);

void printUser(char username[]);

void printOrder(char item[], char type[], double price);

#endif //FOOD_ORDERING_SHOWINFO_H
