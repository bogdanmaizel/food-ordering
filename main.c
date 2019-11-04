#include <stdio.h>
#include <string.h>
#include "showInfo.h"
#include "userInput.h"

int main() {
    printf("Welcome to FoodThingies!\n");
    // food data
    int noOfMeals = 3;
    char meals[][30] = {"Pizza","Pasta","Salad"};
    int noTypes[] = {3,2,4};
    char types[3][4][30] = {
            {"Pizza Carbonara", "Pizza Diavola", "Pizza Margherita",""},
            {"Chicken Alfredo(23)", "Mac&cheese(21)","",""},
            {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"}
    };
    double prices[3][4] = {
            {21, 23, 19, 0},
            {23, 21, 0, 0},
            {23, 22, 19, 21}
    };
    int nodrinks = 4;
    char drinks[][30] = {"Coca-Cola","Fanta","Lipton", "Water"};
    double drinksPrices[] = {5, 5, 5, 4};

    //user input
    char username[20];
    char password[20];
    char infoMsg[30];
    int choice, mealChoice, typeChoice, drinkChoice, cutlery, info=0;

    int state =0;
    int orderFinished = 0;
    while(!orderFinished){
        switch (state) {
            case 0: {
                // Input personal data
                getUserPass(username,password);
                state++;
                break;
            }
            case 1: {
                // Choose the meal
                printf("Please choose the meal type:\n");
                showFood(noOfMeals, meals);
                choice = getchar();
                // consume new line
                getchar();
                if(choice == 'a'+noOfMeals) {
                    state--;
                    break;
                }
                mealChoice = choice - 'a';
                state++;
                noOfMeals=3;
                break;
            }
            case 2: {
                // Choose the meal type
                printf("Please choose the preferred %s:\n",meals[mealChoice]);
                showFoodWithPrice(noTypes[mealChoice], types[mealChoice], prices[mealChoice]);
                choice = getchar();
                // consume new line
                getchar();
                noOfMeals=3;
                if(choice == 'a'+noTypes[mealChoice]) {
                    state--;
                    break;
                }
                typeChoice = choice - 'a';
                state++;
                break;
            }
            case 3: {
                // Choose the drink
                printf("Choose your drink:\n");
                showFoodWithPrice(nodrinks, drinks, drinksPrices);
                drinkChoice = getchar();
                getchar(); //consume new line
                if(drinkChoice == 'a'+nodrinks) {
                    state--;
                    break;
                }
                    drinkChoice = drinkChoice-'a';
                state++;
                break;
            }
            case 4:
            {
                //cutlery
                printf("Do you want cutlery?\n");
                printf("a) Yes\nb) No\nc) Go back\n");
                cutlery=getchar();
                getchar(); //consume new line
                if (cutlery=='c') state--;
                else state++;
                break;
            }
            case 5:
            {
                //Additional Info
                printf("Any additional info? Type 'no' for no message.\n");
                gets(infoMsg);
                if (strcmp(infoMsg,"\n")==0) info=0;
                else info=1;
                state++;
            }
            case 6:{
                // Display contract
                printf("Your order is:\n");
                printf("-------------\n");
                printf("-username: %s\n", username);
                printf("Food: %s (%.2f)\n", types[mealChoice][typeChoice], prices[mealChoice][typeChoice]);
                printf("Drinks: %s (%.2f)\n", drinks[drinkChoice], drinksPrices[drinkChoice]);
                printf("Cutlery: ");
                printf(cutlery ? "No\n" : "Yes\n");
                if (!info) printf("Note: %s\n", infoMsg);
                printf("Total price: %.2f\n", prices[mealChoice][typeChoice] + drinksPrices[drinkChoice]);
                printf("-------------\n");
                printf("a) Confirm\n");
                printf("b) Go back\n");
                getchar();
                orderFinished = getchar();
                    state++;
                if (orderFinished=='b') {
                    orderFinished = 0;
                    state -= 2;
                }

                break;
            }
        }
    }
    return 0;
}