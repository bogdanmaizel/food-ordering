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
    int noOfMeals, mealChoice, typeChoice, drinkChoice, cutlery, info = 0, state = -1, orderFinished = 0, nodrinks = 4, loginMethod, hasDrink=1;
    f=fopen("C:\\00SCHOOL\\CP\\food-ordering\\data.txt","r");
    while (!orderFinished) {
        switch (state) {
            case -1: { //load data
                printf("%s\n", LOAD_DATA);
                if (f) {
                    printf("FILE FOUND\nLoading data...");
                    fscanf(f, "%d:\n", &noOfMeals);
                    noTypes = (int *) malloc(noOfMeals * sizeof(int));
                    types = (char ***) malloc(noOfMeals * sizeof(char **));
                    meals=(char**)malloc(noOfMeals * sizeof(char*));
                    prices=(double**)malloc(noOfMeals * sizeof(double*));
                    char *line = (char *) malloc(MAXLINE * sizeof(char));
                    for (int i = 0; i < noOfMeals; ++i) {// going trough the lines
                        meals[i]=(char*)malloc(30*sizeof(char));
                        types[i] = (char **) malloc(sizeof(char *));
                        prices[i]=(double*)malloc(sizeof(double));
                        fgets(line, MAXLINE, f);
                        sscanf(line, "%[^:]%s: ", meals[i]);
                        noTypes[i] = 0;
                        char *j = strchr(line, '('), *k = strchr(line, ')'), *l;
                        while (line[k-line] != '\n') { // going trough specific food types
                            l = strstr(line, " - ");
                                types[i][noTypes[i]] = (char *) malloc(l-i+1 * sizeof(char));
                                sscanf(j+1, "%[^-]%s - ", types[i][noTypes[i]]);
                                //strncpy(types[i][noTypes[i]++], j, l - i); // building meal type name
                                char *readPrice= (char*)malloc(10* sizeof(char));
                            sscanf(&l, "%[^)]%s)", readPrice); // reading price
                            prices[i][noTypes[i]]=strtold(l+2, k);
                            j = strstr(k, "(");
                            k = strstr(k+1, ")");
                            types[i] = (char **) realloc(types[i], noTypes[i]);
                            prices[i]=(double*)realloc(prices[i],noTypes[i]);
                        }
                    }
                }
                else {
                    printf("FILE FOUND\nLoading data...");
                    fscanf(f, "%d:\n", &noOfMeals);
                    noTypes = (int *) malloc(noOfMeals * sizeof(int));
                    types = (char ***) malloc(noOfMeals * sizeof(char **));
                    meals=(char**)malloc(noOfMeals * sizeof(char*));
                    prices=(double**)malloc(noOfMeals * sizeof(double*));
                    char *line = (char *) malloc(MAXLINE * sizeof(char));
                    for (int i = 0; i < noOfMeals; ++i) {// going trough the lines
                        meals[i]=(char*)malloc(30*sizeof(char));
                        types[i] = (char **) malloc(sizeof(char *));
                        prices[i]=(double*)malloc(sizeof(double));
                        fgets(line, MAXLINE, f);
                        sscanf(line, "%[^:]%s: ", meals[i]);
                        noTypes[i] = 0;
                        char *j = strchr(line, '('), *k = strchr(line, ')'), *l;
                        while (line[k-line] != '\n') { // going trough specific food types
                            l = strstr(line, " - ");
                            types[i][noTypes[i]] = (char *) malloc(l-i+1 * sizeof(char));
                            sscanf(j+1, "%[^-]%s - ", types[i][noTypes[i]]);
                            //strncpy(types[i][noTypes[i]++], j, l - i); // building meal type name
                            char *readPrice= (char*)malloc(10* sizeof(char));
                            sscanf(&l, "%[^)]%s)", readPrice); // reading price
                            prices[i][noTypes[i]]=strtold(l+2, k);
                            j = strstr(k, "(");
                            k = strstr(k+1, ")");
                            types[i] = (char **) realloc(types[i], noTypes[i]);
                            prices[i]=(double*)realloc(prices[i],noTypes[i]);
                        }
                    }
                    state++;
                    break;
                }
            }
            case 0: {//user data, sign in / sign up to be implemented
                printf("welcome to FoodThingies!\nDo you want to sign in or sign up?\n");
                printf("a) Sign in\nb)Sign up\n");
                readOption(&loginMethod);
                int ok=0;
                if (loginMethod) getUserPass(username, password);
                else
                    while (!ok) ok=attemptLogin(username,password);
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
