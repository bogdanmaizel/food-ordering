#include <stdio.h>
#include <string.h>
#include "showInfo.h"
#include "userInput.h"
int main() {
    int noTypes[] = {3, 2, 4}; ///food data
    char types[3][4][30] = {{"Pizza Carbonara",     "Pizza Diavola",  "Pizza Margherita", ""},
                            {"Chicken Alfredo(23)", "Mac&cheese(21)", "",                 ""},
                            {"Tuna Salad",          "Chicken Salad",  "Greek Salad",      "Cobb"}},
            drinks[][30] = {"Coca-Cola", "Fanta", "Lipton", "Water"},
            username[20], password[20], infoMsg[30],
            meals[][30] = {"Pizza", "Pasta", "Salad"},
            item1[]="Food:", item2[]="Drink:";
    double prices[3][4] = {{21, 23, 19, 0},
                           {23, 21, 0,  0},
                           {23, 22, 19, 21}}, drinksPrices[] = {5, 5, 5, 4};
    int noOfMeals = 3, choice, mealChoice, typeChoice, drinkChoice, cutlery, info = 0, state = 0, orderFinished = 0, nodrinks = 4;///user input
    while (!orderFinished) {
        switch (state) {
            case 0: {getUserPass(username, password);    state++;    break;}///user data
            case 1: {// Choose the meal
                showFood(noOfMeals, meals);
                choice=getchar();   getchar();
                checkBackOption(choice, noOfMeals, &state);
                mealChoice = choice - 'a';  ++state;    break;}
            case 2: {// Choose the meal type
                printf("Please choose the preferred %s:\n", meals[mealChoice]);
                showFoodWithPrice(noTypes[mealChoice], types[mealChoice], prices[mealChoice]);
                choice=getchar();   getchar();
                checkBackOption(choice, noTypes[mealChoice], &state);
                typeChoice = choice - 'a'; state++; break;}
            case 3: {// Choose the drink
                printf("Choose your drink:\n");
                showFoodWithPrice(nodrinks, drinks, drinksPrices);
                drinkChoice=getchar();  getchar();
                checkBackOption(drinkChoice, nodrinks, &state);
                drinkChoice = drinkChoice - 'a'; state++; break;}
            case 4: {//cutlery
                askCutlery();
                cutlery=getchar()-'a';  getchar();
                checkBackOption(cutlery+'a', 'c'-'a', &state);
                state++; break;}
            case 5: {printf("Any additional info?\n");
                gets(infoMsg); state++;
                if (strcmp(infoMsg, "\n") == 0) info = 0;   else info = 1;}
            case 6: {// Display contract
                printUser(username);
                printOrder(item1, types[mealChoice][typeChoice], prices[mealChoice][typeChoice]);   printOrder(item2, drinks[drinkChoice], drinksPrices[drinkChoice]);
                printCutleryAndMessage(cutlery, info, infoMsg);
                printf("Total price: %.2f\n", prices[mealChoice][typeChoice] + drinksPrices[drinkChoice]);
                orderFinished = getchar(); getchar(); int stateCopy=state;
                checkBackOption(orderFinished, 'b'-'a', &state);
                if (stateCopy !=state) orderFinished=0; break;}
        }
    }return 0;
}
