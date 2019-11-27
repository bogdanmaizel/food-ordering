#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "showInfo.h"
#include "userInput.h"
#define LOAD_DATA "Please load the data"
#define MAXLINE 300
FILE *f;
int main() {
    int *noTypes; ///food data
    char **meals;// = {"Pizza", "Pasta", "Salad"};
    char ***types; /*= {{"Pizza Carbonara", "Pizza Diavola", "Pizza Margherita", ""},
                            {"Chicken Alfredo", "Mac&cheese", "", ""},
                            {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"}};*/
    char **drinks;// = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    char *food="Food", *drink="Drink";
    double **prices /*=   {{21, 23, 19, 0},
                        {23, 21, 0,  0},
                        {23, 22, 19, 21}}*/;
    double *drinksPrices;// = {5, 5, 5, 4};
    char *username= (char*)malloc(20* sizeof(char)), *password=(char*)malloc(20* sizeof(char)), *infoMsg=(char*)malloc(20* sizeof(char));///user input
    int noOfMeals = 3, mealChoice, typeChoice, drinkChoice, cutlery, info = 0, state = -1, orderFinished = 0, nodrinks = 4, loginMethod, hasDrink=1;
    f=fopen("C:\\00SCHOOL\\CP\\food-ordering\\data.txt","r");
    while (!orderFinished) {
        switch (state) {
            case -1: { //load data
                printf("%s\n", LOAD_DATA);
                if (f) {
                    printf("FILE FOUND\n");
                    fscanf(f,"%d:\n", noOfMeals);
                    noTypes=(int*)malloc(noOfMeals* sizeof(int));
                    for (int i=0;i<noOfMeals;++i) { // going trough the lines
                        char *line=(char*)malloc(MAXLINE*sizeof(char));
                        gets(line);
                        sscanf(line, "%s: ", meals[i]);
                        noTypes[i]=0;
                        int j=strchr(line, '(')-line,k=strchr(line,')')-line,l;
                        while (line[k]!='\n') { // going trough specific food types
                            l=strstr(line+j, " - ")-line;
                            strncat(types[i][noTypes[i]++],line+i+1,l-i); // building meal type name
                            sscanf(line+l+3, "%lf)", prices[i][noTypes[i]]); // reading price
                            j=strchr(line+j+1, '(');
                            k=strchr(line+k+1, ')');
                        }
                    }
                }
                else {
                    printf("NO FILE FOUND\n");
                /*    int noOfFoods;
    printf("Please input number of food types\n");
    scanf("%d", &noOfFoods);
    getchar();
    //read foods
    char **foods;
    foods = (char **) malloc(noOfFoods * sizeof(char *));
    printf("Please input the food types (each on a new line, may contain spaces)\n");
    for (int i = 0; i < noOfFoods; i++) {
        // read each FOOD
        foods[i] = (char *) malloc(MAX_FOOD_NAME * sizeof(char));
        scanf("%s", foods[i]);
        getchar();
    }

    int *noOfmeals = (int *) malloc(noOfFoods * sizeof(int));
    char ***meals = (char ***) malloc(noOfFoods * sizeof(char **));
    double **prices = (double **) malloc(noOfFoods * sizeof(double *));
    for (int i = 0; i < noOfFoods; i++) {
            // read no of meals
            printf("Please input no of speciffic foods for food %s\n",foods[i]);
            scanf("%d", &noOfmeals[i]);
            getchar();
            //read meals & prices
            meals[i] = (char**)malloc(noOfmeals[i]* sizeof(char*));
            prices[i] = (double*)malloc(noOfmeals[i]* sizeof(double));

            printf("Please input %s speciffic foods &prices: each line in the format <speciffic food> (price):\n", foods[i]);
            for(int j=0;j<noOfmeals[i];j++){
                meals[i][j] = (char*)malloc(MAX_MEAL_NAME* sizeof(char));
                char line[MAX_LINE];
                gets(line);
                sscanf(line, "%s (%lf)\n", meals[i][j], &prices[i][j]);
            }

        }
    //read drinks
    int noOfDrinks;
    printf("Please input number of drinks.\n");
    scanf("%d", &noOfDrinks);
    char **drinks=(char**)malloc(noOfDrinks*sizeof(char*));
    double *drinksPrices=(double*)malloc(noOfDrinks* sizeof(double));
    getchar();
    printf("Please input the drinks: each line in the format <drink> (price):\n");
    for (int i=0;i<noOfDrinks;++i) {
        char line[MAX_LINE];
        gets(line);
        drinks[i]=(char*)malloc(MAX_FOOD_NAME* sizeof(char));
        sscanf(line, "%s (%lf)\n", drinks[i], &drinksPrices[i]);
    }


    // display data
    printf("The data is:\n");
    for(int i=0;i<noOfFoods;i++) {
        // display FOOD
        printf("%s: ", foods[i]);
        for(int j=0;j<noOfmeals[i];j++) {
            printf("(%s - %.2lf) ",meals[i][j],prices[i][j]);
        }
        printf("\n");
    }
    printf("Drink data is:\n");
    printf("Drinks: ");
    for (int i=0;i<noOfDrinks;++i) {
        // display drinks
        printf("%s, ", drinks[i]);
    }
    printf("\nPrices: ");
    for (int i=0;i<noOfDrinks;++i) {
        printf("%.2lf, ", drinksPrices[i]);
    }

    // free memory
    for(int i=0;i<noOfFoods;i++) {
        for(int j=0;j<noOfmeals;j++) {
            free(meals[i][j]);
        }
        free(meals[i]);
        free(prices[i]);
        free(foods[i]);
    }
    free(meals);
    free(prices);
    free(foods);
    free(noOfmeals);
    for (int i=0;i<noOfDrinks;++i)
        free(drinks[i]);
    free(drinks);
    free(drinksPrices);
    return 0;
}*/
                }
                state++;
                break;
            }
            case 0: {//user data, sign in / sign up implemented
                printf("welcome to FoodThingies!\nDo you want to sign in or sign up?\n");
                printf("a) Sign in\nb)Sign up\n");
                readOption(&loginMethod);
                if (loginMethod) getUserPass(username, password);
                else login(username,password);
                state++;
                break;}
            case 1: {// Choose the meal
                showFood(noOfMeals, meals);
                readOption(&mealChoice);
                checkBackOption(mealChoice, noOfMeals, &state);
                break;}
            case 2: {// Choose the meal type
                showFoodWithPrice(meals[mealChoice], noTypes[mealChoice], types[mealChoice], prices[mealChoice]);
                readOption(&typeChoice);
                checkBackOption(typeChoice, noTypes[mealChoice], &state);
                break;}
            case 3: {// Choose the drink
                showFoodWithPrice(drink, nodrinks, drinks, drinksPrices);
                readOption(&drinkChoice);
                if (drinkChoice==nodrinks) {
                    hasDrink=0;
                }
                checkBackOption(drinkChoice, nodrinks+1, &state);
                break;
                }
            case 4: {//cutlery
                askCutlery();
                readOption(&cutlery);
                checkBackOption(cutlery, 'c'-'a', &state);
                break;
                }
            case 5: {printf("Any additional info?\n");
                gets(infoMsg);
                info=1,state++;
                if (strcmp(infoMsg, "\n") == 0) info = 0;
                break;
                }
            case 6: {// Display contract
                printUser(username);
                printOrder(food, types[mealChoice][typeChoice], prices[mealChoice][typeChoice]);
                if (hasDrink) printOrder(drink, drinks[drinkChoice], drinksPrices[drinkChoice]);
                printCutleryAndMessage(cutlery, info, infoMsg);
                printf("Total price: %.2f\n", prices[mealChoice][typeChoice] + drinksPrices[drinkChoice]);
                readOption(&orderFinished);
                int stateCopy=state;
                checkBackOption(orderFinished, 'b'-'a', &state);
                if (orderFinished==0) orderFinished=1;
                if (stateCopy == state+2) orderFinished=0;
                break;
                }
        }
    }
    return 0;
}
