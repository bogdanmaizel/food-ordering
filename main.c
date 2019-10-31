#include <stdio.h>
#include <string.h>
int main() {
    printf("Welcome to FoodThingies!\n");

    // food data
    int noOfMeals = 3, nrPizza=3, nrPasta=2, nrSalad=4;
    char meals[][10] = {"Pizza","Pasta","Salad"};
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
                printf("Please sign in to continue.\n");
                printf("---Username:\n");
                gets(username);
                printf("---Password:\n");
                gets(password);
                while (strcmp(username, "ranap") || strcmp(password, "bad_password") !=0)
                {   //user & password check
                    printf("Incorrect username or password! Try again.\n");
                    printf("---Username:\n");
                    gets(username);
                    printf("---Password:\n");
                    gets(password);
                }
                state++;
                break;
            }
            case 1: {
                // Choose the meal
                printf("Please choose the meal type:\n");
                for(int i=0;i<noOfMeals;i++) {
                    putchar('a'+i);
                    printf(") %s\n",meals[i]);
                }
                printf("%c) Go back\n",'a'+noOfMeals);
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
                if (mealChoice==0) noOfMeals=3;
                if (mealChoice==1) noOfMeals=2;
                if (mealChoice==2) noOfMeals=4;
                for(int i=0;i<noOfMeals;i++) {
                    putchar('a'+i);
                    printf(") %s (%.2f)\n",types[mealChoice][i], prices[mealChoice][i]);
                }
                printf("%c) Go back\n",'a'+noTypes[mealChoice]);
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
                for(int i=0;i<nodrinks;i++) {
                    putchar('a'+i);
                    printf(") %s (%.2f)\n", drinks[i], drinksPrices[i]);
                }
                printf("%c) Go back\n",'a'+nodrinks);

                //we want to check here for '\n' to allow the user to select 0 additional items
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
                scanf("%s",  infoMsg);
                if (infoMsg[0]=='n' && infoMsg[1]=='o' && infoMsg[2]==NULL) info=1;
                else info=0;
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
                //orderFinished = getchar();
                //altfel imi da eroare ^_^'
                if (orderFinished - 'a' == 0) {
                    state++;
                    orderFinished=1;
                } else {
                    orderFinished=0;
                    state -= 2;
                }

                break;
            }
            default: {printf("Thanks for ordering!");break;}
        }
    }
    return 0;
}