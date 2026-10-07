#include <stdio.h>
#include <string.h>

void startChat(char currentUser[]) {

    FILE *file = fopen("users.txt", "r");

    char username[50];
    char password[50];

    char users[100][50];

    int count = 0;
    int choice;

    if (file == NULL) {
        printf("\nNo users found.\n");
        return;
    }

    while (fscanf(file, "%49s %49s", username, password) == 2) {

        if (strcmp(username, currentUser) != 0) {

            strcpy(users[count], username);
            count++;
        }
    }

    fclose(file);

    if (count == 0) {

        printf("\nNo other users available.\n");
        return;
    }

    printf("\n===== START CHAT =====\n\n");

    for (int i = 0; i < count; i++) {

        printf("%d. %s\n", i + 1, users[i]);
    }

    printf("\n0. Back\n");

    printf("\nChoose: ");
    scanf("%d", &choice);

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice > count) {

        printf("\nInvalid choice!\n");
        return;
    }

    char selectedUser[50];

    strcpy(selectedUser, users[choice - 1]);

    printf("\n========================\n");
    printf("       CHAT WITH %s\n", selectedUser);
    printf("========================\n\n");

    printf("Chat system is ready!\n");
    printf("You are chatting with %s.\n\n", selectedUser);

    printf("You: ");

    char message[500];

    getchar();

    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    printf("\n%s: %s\n", currentUser, message);

    printf("\nChat message received successfully!\n");
}


void showUsers(char currentUser[]) {

    FILE *file = fopen("users.txt", "r");

    char username[50];
    char password[50];

    int number = 1;
    int found = 0;

    if (file == NULL) {

        printf("\nNo users found.\n");
        return;
    }

    printf("\n===== USERS =====\n\n");

    while (fscanf(file, "%49s %49s", username, password) == 2) {

        if (strcmp(username, currentUser) != 0) {

            printf("%d. %s\n", number, username);

            number++;
            found = 1;
        }
    }

    fclose(file);

    if (!found) {

        printf("No other users found.\n");
    }

    printf("\n");
}


void userMenu(char username[]) {

    int choice;

    while (1) {

        printf("\n========================\n");
        printf("       NOVA CHAT\n");
        printf("========================\n");

        printf("Welcome, %s!\n\n", username);

        printf("1. Start Chat\n");
        printf("2. Users\n");
        printf("3. Logout\n");
        printf("4. Exit\n\n");

        printf("Choose: ");

        scanf("%d", &choice);

        if (choice == 1) {

            startChat(username);
        }

        else if (choice == 2) {

            showUsers(username);
        }

        else if (choice == 3) {

            printf("\nLogged out successfully.\n");
            break;
        }

        else if (choice == 4) {

            printf("\nGoodbye!\n");
            break;
        }

        else {

            printf("\nInvalid choice!\n");
        }
    }
}


int main() {

    int choice;

    char username[50];
    char password[50];

    printf("========================\n");
    printf("       NOVA CHAT\n");
    printf("========================\n\n");

    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n\n");

    printf("Choose: ");

    scanf("%d", &choice);


    if (choice == 1) {

        printf("\n===== REGISTER =====\n");

        printf("Username: ");
        scanf("%49s", username);

        printf("Password: ");
        scanf("%49s", password);

        FILE *file = fopen("users.txt", "a");

        if (file == NULL) {

            printf("Error opening file!\n");
            return 1;
        }

        fprintf(file, "%s %s\n", username, password);

        fclose(file);

        printf("\nRegistration successful!\n");
        printf("Welcome %s!\n", username);
    }


    else if (choice == 2) {

        char savedUsername[50];
        char savedPassword[50];

        int loginSuccess = 0;

        printf("\n===== LOGIN =====\n");

        printf("Username: ");
        scanf("%49s", username);

        printf("Password: ");
        scanf("%49s", password);

        FILE *file = fopen("users.txt", "r");

        if (file == NULL) {

            printf("\nNo registered users found!\n");
            return 1;
        }

        while (fscanf(file, "%49s %49s",
                      savedUsername,
                      savedPassword) == 2) {

            if (strcmp(username, savedUsername) == 0 &&
                strcmp(password, savedPassword) == 0) {

                loginSuccess = 1;
                break;
            }
        }

        fclose(file);


        if (loginSuccess) {

            printf("\nLogin successful!\n");
            printf("Welcome back, %s!\n", username);

            userMenu(username);
        }

        else {

            printf("\nWrong username or password!\n");
        }
    }


    else if (choice == 3) {

        printf("\nGoodbye!\n");
    }


    else {

        printf("\nInvalid choice!\n");
    }


    return 0;
}