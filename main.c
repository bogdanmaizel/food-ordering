#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "showInfo.h"
#include "userInput.h"
#define LOAD_DATA "Please load the data."
#define MAXLINE 300
#define SIGN_IN	"Sign in"
#define SIGN_UP	"Sign up"
#define SIGN_IN_UP	"Do you want to sign in or sign up?"
#define SUCCESS "Please choose the food you feel like eating today:"
FILE *f;
FILE *users;
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
    int noOfMeals, mealChoice, typeChoice, drinkChoice, cutlery, info = 0, state = -1, orderFinished = 0, nodrinks, loginMethod, hasDrink=1;
    f=fopen("C:\\00SCHOOL\\CP\\food-ordering\\data.txt","r");
    users=fopen("C:\\00SCHOOL\\CP\\food-ordering\\login.txt","a");
    while (!orderFinished) {
        switch (state) {
            case -1: { //load data
                if (f) {
                    printf("FILE FOUND\nLoading data...\n");
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
                        sscanf(line, "%s %d: ", meals[i], &noTypes[i]);
                        //char *j = strchr(line, '('), *k = strchr(line, ')'), *l;
                        //int startType=strchr(line, '(')-line, stopType=strchr(line, ')')-line, midType;
                        char *type=strtok(line,"(");
                        //while (line[k] != '\n') { // going trough specific food types
                        for (int j=0;j<noTypes[i];++j) {
                            type=strtok(NULL, "-");
                            types[i][j] = (char *) malloc(30 * sizeof(char));
                            //sscanf(type, "%[^\0]%s", types[i][j]);
                            strcpy(types[i][j], type);
                                //strncpy(types[i][noTypes[i]++], j, l - i); // building meal type name
                            type=strtok(NULL, "(");
                            sscanf(type, "%lf)", &prices[i][noTypes[i]]); // reading price

                        }
                    }
                    fscanf(f,"%d:\n", &nodrinks);
                    drinks=(char**)malloc(nodrinks* sizeof(char*));
                    drinksPrices = (double *)malloc(nodrinks* sizeof(double));
                    fgets(line,MAXLINE,f);
                    //char *type=strtok(line, "(");
                    char *type=strtok(line,"-");
                    for (int i=0;i<nodrinks;++i) {
                        drinks[i]=(char*)malloc(30* sizeof(char));
                        if (!i) strcpy(drinks[i],type+1);
                        else strcpy(drinks[i], type+2);
                        type=strtok(NULL,",");
                        sscanf(type,"%lf", &drinksPrices[i]);
                        type=strtok(NULL, "-");
                    }
                    fclose(f);
                }
                else {
                    printf("NO FILE FOUND\n%s", LOAD_DATA);
                    fscanf(stdin, "%d:\n", &noOfMeals);
                    noTypes = (int *) malloc(noOfMeals * sizeof(int));
                    types = (char ***) malloc(noOfMeals * sizeof(char **));
                    meals=(char**)malloc(noOfMeals * sizeof(char*));
                    prices=(double**)malloc(noOfMeals * sizeof(double*));
                    char *line = (char *) malloc(MAXLINE * sizeof(char));
                    for (int i = 0; i < noOfMeals; ++i) {// going trough the lines
                        meals[i]=(char*)malloc(30*sizeof(char));
                        types[i] = (char **) malloc(sizeof(char *));
                        prices[i]=(double*)malloc(sizeof(double));
                        fgets(line, MAXLINE, stdin);
                        sscanf(line, "%s %d: ", meals[i], &noTypes[i]);
                        //char *j = strchr(line, '('), *k = strchr(line, ')'), *l;
                        //int startType=strchr(line, '(')-line, stopType=strchr(line, ')')-line, midType;
                        char *type=strtok(line,"(");
                        //while (line[k] != '\n') { // going trough specific food types
                        for (int j=0;j<noTypes[i];++j) {
                            type=strtok(NULL, "-");
                            types[i][j] = (char *) malloc(30 * sizeof(char));
                            //sscanf(type, "%[^\0]%s", types[i][j]);
                            strcpy(types[i][j], type);
                            //strncpy(types[i][noTypes[i]++], j, l - i); // building meal type name
                            type=strtok(NULL, "(");
                            sscanf(type, "%lf)", &prices[i][noTypes[i]]); // reading price

                        }
                    }
                    fscanf(f,"%d:\n", &nodrinks);
                    drinks=(char**)malloc(nodrinks* sizeof(char*));
                    drinksPrices = (double *)malloc(nodrinks* sizeof(double));
                    fgets(line,MAXLINE,stdin);
                    //char *type=strtok(line, "(");
                    char *type=strtok(line,"-");
                    for (int i=0;i<nodrinks;++i) {
                        drinks[i]=(char*)malloc(30* sizeof(char));
                        if (!i) strcpy(drinks[i],type+1);
                        else strcpy(drinks[i], type+2);
                        type=strtok(NULL,",");
                        sscanf(type,"%lf", &drinksPrices[i]);
                        type=strtok(NULL, "-");
                    }
                    state++;
                    break;
                }
            }
            case 0: {//user data, sign in / sign up implemented
                printf("%s\n", SIGN_IN_UP);
                printf("a) %s\nb) %s\n", SIGN_IN, SIGN_UP);
                readOption(&loginMethod);
                int ok = 0;
                if (loginMethod==0)
                {
                    do { ok = attemptLogin(username, password); }
                    while (!ok);
                }
                else
                {
                    ok=tryRegister(username, password);
                }
                if (ok) state=1;
                else state=0;
                /*if (loginMethod) getUserPass(username, password);
                else
                    while (!ok) ok=attemptLogin(username,password);*/

                break;}
            case 1: {// Choose the meal
                printf("%s\n", SUCCESS);
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
