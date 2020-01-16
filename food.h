//
// Created by mbogd on 19/12/2019.
//

#ifndef FOOD_ORDERING_FOOD_H
#define FOOD_ORDERING_FOOD_H

typedef struct _food {
    char *category;
    char *name;
    double *price;
} food;

typedef struct _drink {
    char *name;
    double *price;
} drink;

food newFood();

drink newDrink();

#endif //FOOD_ORDERING_FOOD_H
