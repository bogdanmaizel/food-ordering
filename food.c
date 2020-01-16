//
// Created by mbogd on 19/12/2019.
//
#include "food.h"
#include <stdlib.h>

food newFood() {
    food f;
    f.category = (char*)malloc(30* sizeof(char));
    f.name = (char*)malloc(30* sizeof(char));
    f.price = (double*)malloc(sizeof(double));
    return f;
}

drink newDrink() {
    drink d;
    d.name = (char*)malloc(30* sizeof(char));
    d.price = (double*)malloc(sizeof(double));
    return d;
}
