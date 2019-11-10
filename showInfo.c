//
// Created by mbogd on 4/11/2019.
//
#include <stdio.h>
#include "showInfo.h"


void showFood(int noOfMeals, char meals[][30]) {
    printf("Please choose the meal type:\n");
    for(int i=0;i<noOfMeals;i++) {
        putchar('a'+i);
        printf(") %s\n",meals[i]);
    }
    printf("%c) Go back\n",'a'+noOfMeals);
}

void showFoodWithPrice(char foodType[], int noOfMeals, char meals[][30], double prices[]) {
    printf("Choose your %s:\n", foodType);
    for(int i=0;i<noOfMeals;i++) {
        putchar('a'+i);
        printf(") %s (%.2f)\n",meals[i], prices[i]);
    }
    printf("%c) Go back\n",'a'+noOfMeals);
}

void askCutlery() {
    printf("Do you want cutlery?\n");
    printf("a) Yes\nb) No\nc) Go back\n");
}

void printCutleryAndMessage(int cutlery, int info, char *infoMsg) {
    printf("Cutlery: ");
    printf(cutlery ? "No\n" : "Yes\n");
    if (info) printf("Note: %s\n", infoMsg);
}

void printUser(char username[]) {
    printf("Your order is:\n");
    printf("a) Confirm\nb) Go back\n\n");
    printf("-username: %s\n", username);
}

void printOrder(char item[], char type[], double price) {
    printf(" %s: %s %.2f\n", item, type, price);
}
