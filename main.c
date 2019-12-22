#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "showInfo.h"
#include "userInput.h"
#include "food.h"
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
    char *foodText="Food", *drinkText="Drink";
    double **prices /*=   {{21, 23, 19, 0},
                        {23, 21, 0,  0},
                        {23, 22, 19, 21}}*/;
    double *drinksPrices;// = {5, 5, 5, 4};
    char *infoMsg=(char*)malloc(20* sizeof(char));///user input
    int noOfMeals, mealChoice, typeChoice, drinkChoice, cutlery, info = 0, orderFinished = 0, nodrinks, loginMethod;
    f=fopen("C:\\00SCHOOL\\CP\\food-ordering\\data.txt","r");
    users=fopen("C:\\00SCHOOL\\CP\\food-ordering\\login.txt","a");
    enum State{LOADING_DATA, LOG_IN, CHOOSE_CATEGORY, CHOOSE_TYPE, CHOOSE_DRINK, CHOOSE_CUTLERY, WRITE_NOTE, CONFIRM};
    account a=newAccount();
    food **toEat;
    drink *toDrink;
    order order1 = newOrder();
    int state=0;
    while (state<=CONFIRM || !orderFinished) {
        switch (state) {
            case LOADING_DATA: {
                if (f) {
                    printf("FILE FOUND\nLoading data...\n");
                    fscanf(f, "%d:\n", &noOfMeals);
                    toEat = (food**)malloc(noOfMeals* sizeof(food*));
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
                        toEat[i]=(food*)malloc(noTypes[i]* sizeof(food));
                        //char *j = strchr(line, '('), *k = strchr(line, ')'), *l;
                        //int startType=strchr(line, '(')-line, stopType=strchr(line, ')')-line, midType;
                        char *type=strtok(line,"(");
                        //while (line[k] != '\n') { // going trough specific food types
                        for (int j=0;j<noTypes[i];++j) {
                            toEat[i][j]=newFood();
                            type=strtok(NULL, "-");
                            types[i][j] = (char *) malloc(30 * sizeof(char));
                            //sscanf(type, "%[^\0]%s", types[i][j]);
                            strcpy(types[i][j], type);
                            strcpy(toEat[i][j].name, type);
                            strcpy(toEat[i][j].category, meals[i]);
                                //strncpy(types[i][noTypes[i]++], j, l - i); // building meal type name
                            type=strtok(NULL, "(");
                            sscanf(type, "%lf)", &prices[i][j]);
                            toEat[i][j].price=&prices[i][j];
                        }
                    }
                    fscanf(f,"%d:\n", &nodrinks);
                    drinks=(char**)malloc(nodrinks* sizeof(char*));
                    drinksPrices = (double *)malloc(nodrinks* sizeof(double));
                    toDrink = (food*)malloc(nodrinks* sizeof(food));
                    fgets(line,MAXLINE,f);
                    //char *type=strtok(line, "(");
                    char *type=strtok(line,"-");
                    for (int i=0;i<nodrinks;++i) {
                        toDrink[i]=newDrink();
                        drinks[i]=(char*)malloc(30* sizeof(char));
                        if (!i) {
                            strcpy(drinks[i], type + 1);
                            strcpy(toDrink[i].name, type+1);
                        }
                        else {
                            strcpy(drinks[i], type + 2);
                            strcpy(toDrink[i].name, type+2);
                        }
                        type=strtok(NULL,",");
                        sscanf(type,"%lf", &drinksPrices[i]);
                        toDrink[i].price = &drinksPrices[i];
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
                    fscanf(stdin,"%d:\n", &nodrinks);
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
            case LOG_IN: {//user data, sign in / sign up implemented
                printf("%s\n", SIGN_IN_UP);
                printf("a) %s\nb) %s\n", SIGN_IN, SIGN_UP);
                readOption(&loginMethod);
                int ok = 0;
                if (loginMethod==0)
                {
                    do { ok = attemptLogin(&a); }
                    while (!ok);
                }
                else
                {
                    ok=tryRegister(&a);
                }
                if (ok) state=CHOOSE_CATEGORY;
                else state=LOG_IN;
                /*if (loginMethod) getUserPass(username, password);
                else
                    while (!ok) ok=attemptLogin(username,password);*/

                break;}
            case CHOOSE_CATEGORY: {// Choose the meal
                printf("%s\n", SUCCESS);
                showFood(noOfMeals, meals);
                readOption(&mealChoice);

                checkBackOption(mealChoice, noOfMeals, &state);
                break;}
            case CHOOSE_TYPE: {// Choose the meal type
                showFoodWithPrice(meals[mealChoice], noTypes[mealChoice], types[mealChoice], prices[mealChoice]);
                readOption(&typeChoice);
                checkBackOption(typeChoice, noTypes[mealChoice], &state);
                break;}
            case CHOOSE_DRINK: {// Choose the drink
                showFoodWithPrice(drinkText, nodrinks, drinks, drinksPrices);
                readOption(&drinkChoice);
                checkBackOption(drinkChoice, nodrinks, &state);
                break;
                }
            case CHOOSE_CUTLERY: {//cutlery
                askCutlery();
                readOption(&cutlery);
                checkBackOption(cutlery, 'c'-'a', &state);
                break;
                }
            case WRITE_NOTE: {printf("Any additional info?\n");
                gets(infoMsg);
                info=1,state++;
                if (strcmp(infoMsg, "\n") == 0) info = 0;
                break;
                }
            case CONFIRM: {// Display contract
                printUser(a.username);
                printOrder(f, d);
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
