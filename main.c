#include <stdio.h>
#include <string.h>
#include "showInfo.h"
#include "userInput.h"
int main() {
    int noTypes[] = {3, 2, 4}; ///food data
    char meals[][30] = {"Pizza", "Pasta", "Salad"};
    char types[3][4][30] = {{"Pizza Carbonara", "Pizza Diavola", "Pizza Margherita", ""},
                            {"Chicken Alfredo(23)", "Mac&cheese(21)", "", ""},
                            {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"}};
    char drinks[][30] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    char food[]="Food", drink[]="Drink";
    double prices[3][4] = {{21, 23, 19, 0},
                           {23, 21, 0,  0},
                           {23, 22, 19, 21}};
    double drinksPrices[] = {5, 5, 5, 4};
    char username[20]="", password[20]="", infoMsg[30]="";///user input
    int noOfMeals = 3, mealChoice, typeChoice, drinkChoice, cutlery, info = 0, state = 0, orderFinished = 0, nodrinks = 4;
    while (!orderFinished) {
        switch (state) {
            case 0: {//user data
                getUserPass(username, password);
                state++;
                break;}
            case 1: {// Choose the meal
                showFood(noOfMeals, meals);
                readOption(&mealChoice);
                checkBackOption(mealChoice+'a', noOfMeals, &state);
                break;}
            case 2: {// Choose the meal type
                showFoodWithPrice(meals[mealChoice], noTypes[mealChoice], types[mealChoice], prices[mealChoice]);
                readOption(&typeChoice);
                checkBackOption(typeChoice+'a', noTypes[mealChoice], &state);
                break;}
            case 3: {// Choose the drink
                showFoodWithPrice(drink, nodrinks, drinks, drinksPrices);
                readOption(&drinkChoice);
                checkBackOption(drinkChoice+'a', nodrinks, &state);
                break;}
            case 4: {//cutlery
                askCutlery();
                readOption(&cutlery);
                checkBackOption(cutlery+'a', 'c'-'a', &state);
                break;}
            case 5: {printf("Any additional info?\n");
                gets(infoMsg);
                info=1,state++;
                if (strcmp(infoMsg, "\n") == 0) info = 0;
                break;}
            case 6: {// Display contract
                printUser(username);
                printOrder(food, types[mealChoice][typeChoice], prices[mealChoice][typeChoice]);
                printOrder(drink, drinks[drinkChoice], drinksPrices[drinkChoice]);
                printCutleryAndMessage(cutlery, info, infoMsg);
                printf("Total price: %.2f\n", prices[mealChoice][typeChoice] + drinksPrices[drinkChoice]);
                readOption(&orderFinished);
                int stateCopy=state;
                checkBackOption(orderFinished+'a', 'b'-'a', &state);
                if (orderFinished==0) orderFinished=1;
                if (stateCopy ==state-2) orderFinished=0;
                break;}
        }
    }
    return 0;
}
