#include <stdio.h>
#include <string.h>
int main() {
    printf("Welcome to FoodThingies!\n");

    // food data
    int noOfMeals = 3;
    char meals[][10] = {"Pizza","Pasta","Salad"};
    int noModels[] = {3,2,4};
    char models[3][4][30] = {
            {"Pizza Carbonara(21)", "Pizza Diavola(23)", "Pizza Margherita(19)",""},
            {"Chicken Alfredo(23)", "Mac&cheese(21)","",""},
            {"Tuna Salad(23)", "Chicken Salad(22)", "Greek Salad(19)", "Cobb(21)"}
    };
    double prices[3][4] = {
            {21, 23, 19, 0},
            {23, 21, 0, 0},
            {23, 22, 19, 21}
    };
    int noAdditionalItems = 4;
    char additionalItems[][30] = {"Coca-Cola","Fanta","Lipton", "Water"};
    double additionalItemsPrices[] = {5, 5, 5, 4};

    //user input
    char username[20];
    char password[20];
    int choice, brandChoice, modelChoice;
    int noAddItemsChosen = 0;
    int chosenAdditionalItems[3];

    int state =0;
    int contractSigned = 0;
    while(!contractSigned){
        switch (state) {
            case 0: {
                // Input personal data
                printf("Please sign in to continue.\n");
                printf("---Username:\n");
                gets(username);
                printf("---Password\n");
                gets(password);
                while (strcmp(username, "ranap") && strcmp(password, "bad_password") !=0)
                {   //user & password check
                    printf("Incorrect username or password! Try again.");
                    printf("---First name:\n");
                    gets(username);
                    printf("---Password\n");
                    gets(password);
                }
                state++;
                break;
            }
            case 1: {
                // Choose the brand
                printf("Please choose the car brand\n");
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
                brandChoice = choice - 'a';
                state++;
                break;
            }
            case 2: {
                // Choose the car model
                printf("Please choose the car model for brand %s\n",meals[brandChoice]);
                for(int i=0;i<noOfMeals;i++) {
                    putchar('a'+i);
                    printf(") %s (%.2f)\n",models[brandChoice][i], prices[brandChoice][i]);
                }
                printf("%c) Go back\n",'a'+noModels[brandChoice]);
                choice = getchar();
                // consume new line
                getchar();
                if(choice == 'a'+noModels[brandChoice]) {
                    state--;
                    break;
                }
                modelChoice = choice - 'a';
                state++;
                break;
            }
            case 3: {
                // Choose the additional items
                printf("Choose additional items (separated by comma)\n");
                for(int i=0;i<noAdditionalItems;i++) {
                    putchar('a'+i);
                    printf(") %s (%.2f)\n", additionalItems[i], additionalItemsPrices[i]);
                }
                printf("%c) Go back\n",'a'+noAdditionalItems);
                //read additional items

                //we want to check here for '\n' to allow the user to select 0 additional items
                choice = getchar();
                if(choice == 'a'+noAdditionalItems) {
                    state--;
                    //consume new line
                    getchar();
                    break;
                }
                noAddItemsChosen = 0;
                while (choice !='\n') {

                    chosenAdditionalItems[noAddItemsChosen] = choice - 'a';
                    noAddItemsChosen++;
                    //read comma
                    char comma = getchar();
                    if(comma=='\n'){
                        //after the last letter, a new line entered
                        break;
                    }
                    choice = getchar();
                }
                state++;
                break;
            }
            case 4:{
                // Display contract
                printf("Your contract is:\n");
                printf("-------------\n");
                printf("Customer data:\n");
                printf("-name: %s\n", username);
                printf("Car data:\n");
                printf("-car model: %s (%.2f)\n", models[brandChoice][modelChoice], prices[brandChoice][modelChoice]);
                double additionalItemsPrice = 0;
                for(int i=0;i<noAddItemsChosen;i++) {
                    additionalItemsPrice += additionalItemsPrices[chosenAdditionalItems[i]];
                }
                printf("-additional items (%.2f)\n", additionalItemsPrice);
                if(noAddItemsChosen!=0){
                    for(int i=0;i<noAddItemsChosen;i++) {
                        printf("--%s (%.2f)\n", additionalItems[chosenAdditionalItems[i]], additionalItemsPrices[chosenAdditionalItems[i]]);
                    }
                }
                printf("Total price: %.2f\n", prices[brandChoice][modelChoice] + additionalItemsPrice);
                printf("-------------\n");
                printf("a) Sign\n");
                printf("b) Go back\n");
                choice = getchar();
                if(choice=='a') {
                    contractSigned = 1;
                } else {
                    state--;
                }
                // consume new line
                getchar();
                break;
            }
        }
    }
    return 0;
}