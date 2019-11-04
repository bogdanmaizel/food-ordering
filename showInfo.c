//
// Created by mbogd on 4/11/2019.
//
#include <stdio.h>

void showFood(int noOfMeals, char meals[][30]) {
    for(int i=0;i<noOfMeals;i++) {
        putchar('a'+i);
        printf(") %s\n",meals[i]);
    }
    printf("%c) Go back\n",'a'+noOfMeals);
}

