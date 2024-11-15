#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define max_teams 5       // Max no.of teams that can be enrolled
#define max_players 5    // Max no.of players in a team
#define current_year 2024  // Current year for age calculation

// Storing individual player information
struct Player {
    char name[50];      // Player's name
    int kit_number;     // Unique kit number(1-99)
    char dob[50];       // Date of birth (DD/MM/YYYY format)
    char position[50];  // Player's position
};

// Storing team information
struct Team {
    char team_name[20]; // Team name
    struct Player players[max_players]; // Array for no.of players in the team
    int num_players;    // Current no.of players in the team
};

struct Team teams[max_teams];      // Array with enrolled teams
int enrolled_teams_count = 0;      // Tracks the no.of enrolled teams

// Function prototypes
void enroll_team(); // Enrolls a new team
void add_player(); // Adds a player to a team
void search_update_player(); // Searches for a player and update details
void display_data(); // Displays team data
int age(const char* dob); // Detects "year" from date of birth 
void invalid_input(); // Handles any invalid user input
int select_team(); // Selects a team from the list
int kit_validation(int team_index, int kit_number); // Validates the kit number
int name_validation(int team_index, char* name); // Validates the player name
void player_info_updation(int team_index, int player_index); // Updates player details

//Main Function
int main() {
    int user_choice;

    // Initializes every team to have 0 players
    for (int i = 0; i < max_teams; i++) {
        teams[i].num_players = 0;
    }

    // Allows user to choose from the menu until they exit
    while (1) {
        // League App Menu
        printf("\n\n****  MENU  ****\n");
        printf("1. Enroll a New Team\n");
        printf("2. Add a Player to a Team\n");
        printf("3. Search and Update Player Details\n");
        printf("4. Display Team Statistics\n");
        printf("5. Exit Application\n");
        printf("\nEnter operation from menu (1/2/3/4/5): ");
        scanf("%d", &user_choice);
        getchar(); // Deletes newline character that is left by scanf

        // Calls appropriate functions based on user choice
        switch (user_choice) {
            case 1:
                enroll_team();
                break;
            case 2:
                add_player();
                break;
            case 3:
                search_update_player();
                break;
            case 4:
                display_data();
                break;
            case 5:
                printf("Thank you for using the League Team Application!\nGood Bye!!\n");
                return 0;
            default:
                invalid_input();
        }
    }
}

// Enroll a new team Function
void enroll_team() {
    if (enrolled_teams_count >= max_teams) { // Checks if max no.of teams is reached
        printf("\nSorry!\nThe enrolled no.of teams has reached maximum limit.\n");
        return; // Exits function if the limit is max
    }
    char team_name[20]; 
    printf("Enter Team Name: ");
    if (fgets(team_name, sizeof(team_name), stdin) == NULL) {
        printf("\nError: Team Name not read.\n");
        return; // Exits function if an error occurs
    }
    team_name[strcspn(team_name, "\n")] = '\0'; // Removes newline character
    if (strlen(team_name) == 0) { // Checks if team name is empty
        printf("Error: Team name cannot be empty.\n");
        return; // Exits the function if the team name is empty
    }
    // Checks if a team with this name already exists
    for (int i = 0; i < enrolled_teams_count; i++) {
        if (strcasecmp(teams[i].team_name, team_name) == 0) {
            printf("A team with this name already exists!\n");
            return;
        }
    }
    // Adds new team if no duplicates are found
    strcpy(teams[enrolled_teams_count].team_name, team_name); // Copies team name to the team structure
    teams[enrolled_teams_count].num_players = 0; // Initializes the no.of players to 0
    enrolled_teams_count++; // Increments enrolled teams count
    printf("Team %s enrolled successfully!\n", team_name);
}

// Add Player Function
void add_player() {
    if (enrolled_teams_count == 0) { 
        printf("No teams enrolled yet.\nPlease enroll a team first.\n");
        return; // Exits function if no teams are enrolled
    }

    int team_choice = select_team(); // Lets user choose a team
    if (team_choice == -1) return;   // Exits if invalid selection

    // Checks max no.of players
    if (teams[team_choice].num_players >= max_players) { 
        printf("This team already has the maximum no.of players (%d).\n", max_players);
        return; // Exits if max no.of players is reached
    }

    struct Player new_player; // Temporary player struct to hold input details
    int valid_input = 0; // valid inpput check

    while (!valid_input) { 
        printf("Enter player name (max 50 characters): ");
        if (fgets(new_player.name, sizeof(new_player.name), stdin) == NULL) { 
            printf("Error reading player name.\n");
            return; 
        }
        new_player.name[strcspn(new_player.name, "\n")] = '\0'; // Removes newline character

        // Checks for duplicate player name
        if (name_validation(team_choice, new_player.name)) {
            printf("A player with name %s already exists in this team.\n", new_player.name);
            printf("The following players are already enrolled in the team\n");
            for (int i = 0; i < teams[team_choice].num_players; i++) {
                printf("Player %d: %s\n", i + 1, teams[team_choice].players[i].name);
            }
            continue; // Re-prompts for valid player name
        }

        printf("Enter kit number (1-99): ");
        scanf("%d", &new_player.kit_number);
        getchar();  // Clears newline left by scanf

        // Validates kit number and checks for duplicates
        // Kit number check
        if (!kit_validation(team_choice, new_player.kit_number)) { 
            printf("Enter a unique kit number between 1 and 99.\n");
            printf("The following kit numbers are already enrolled in the team\n");
            //Displaying existing player details
            for (int i = 0; i < teams[team_choice].num_players; i++) {
                printf("Player %d: %d\n", i + 1, teams[team_choice].players[i].kit_number);
            }
            continue;
        }

        printf("Enter date of birth (DD/MM/YYYY): ");
        if (fgets(new_player.dob, sizeof(new_player.dob), stdin) == NULL) { // Reads DOB
            printf("Error reading date of birth.\n");
            return;
        }
        new_player.dob[strcspn(new_player.dob, "\n")] = '\0'; // Removes newline character

        printf("Enter player position: ");
        if (fgets(new_player.position, sizeof(new_player.position), stdin) == NULL) { // Reads position
            printf("Error reading position.\n");
            return;
        }
        new_player.position[strcspn(new_player.position, "\n")] = '\0'; // Removes '\n'
        valid_input = 1; // Loop breaks if all input is valid and adds player
    }

    // Adds player to the selected team
    // Adds the new_player to the respective array at the position indicated by num_players 
    // Increments it for the team.
    teams[team_choice].players[teams[team_choice].num_players++] = new_player;
    printf("Player %s has been successfully added to team %s.\n", new_player.name, teams[team_choice].team_name);
}

// Selecting team function
int select_team() {
    printf("Select a team:\n");
    for (int i = 0; i < enrolled_teams_count; i++) {
        printf("%d. %s\n", i + 1, teams[i].team_name); // Displays teams with 1-based index
    }

    int team_choice;
    scanf("%d", &team_choice);
    getchar();

    if (team_choice < 1 || team_choice > enrolled_teams_count) { // Validates choice
        invalid_input();
        return -1;
    }
    return team_choice - 1; // Converts to 0-based index
}

// Validates that the kit number is unique within the team and within the valid range (1-99).
int kit_validation(int team_index, int kit_number) {
    if (kit_number < 1 || kit_number > 99) { // Checks valid range
        printf("Invalid kit number. Please enter a number between 1 and 99.\n");
        return 0;
    }

    // Checks for duplicate kit number
    for (int i = 0; i < teams[team_index].num_players; i++) {
        if (teams[team_index].players[i].kit_number == kit_number) {
            printf("A player with kit number %d already exists in this team.\n", kit_number);
            return 0;
        }
    }
    return 1; // Kit number is valid
}

// Validates if the player name is unique within the team.
int name_validation(int team_index, char* name) {
    for (int i = 0; i < teams[team_index].num_players; i++) {
        if (strcasecmp(teams[team_index].players[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

// Searches for a player in a team based on either kit number or name, then updates details if found.
void search_update_player() {
    if (enrolled_teams_count == 0) {
        printf("No teams have been enrolled yet.\n");
        return;
    }

    // Asks user for search option (kit number or name)
    int search_option;
    printf("Player Search Options:\n1. Kit Number\n2. Name\n");
    scanf("%d", &search_option);
    getchar();

    int found = 0; // Tracks if player is found
    if (search_option == 1) {
        int kit_number;
        printf("Enter kit number: ");
        scanf("%d", &kit_number);
        getchar();

        for (int i = 0; i < enrolled_teams_count && !found; i++) { // Loops through all teams
            for (int j = 0; j < teams[i].num_players; j++) { // Loops through players in each team
                if (teams[i].players[j].kit_number == kit_number) { // Checks for matching kit number
                    // Displays player details and ask for update
                    printf("Player found in team %s:\n", teams[i].team_name);
                    printf("Player Name: %s\n", teams[i].players[j].name);
                    printf("Kit Number: %d\n", teams[i].players[j].kit_number);
                    printf("DOB: %s\n", teams[i].players[j].dob);
                    printf("Position: %s\n", teams[i].players[j].position);
                    printf("Do you want to update player details? (1 (Yes) / 0 (No)): ");
                    int update_choice;
                    scanf("%d", &update_choice);
                    getchar();
                    if (update_choice == 1) {
                        player_info_updation(i, j);
                    }
                    found = 1;
                    break;
                }
            }
        }
    } else if (search_option == 2) {
        char player_name[50];
        printf("Enter the Player name: ");
        if (fgets(player_name, sizeof(player_name), stdin) == NULL) { // Read player name
            printf("Error reading player name.\n");
            return;
        }
        player_name[strcspn(player_name, "\n")] = '\0'; // Removes newline character
        for (int i = 0; i < enrolled_teams_count && !found; i++) { // Loops through all teams
            for (int j = 0; j < teams[i].num_players; j++) { // Loops through players in each team
                if (strcasecmp(teams[i].players[j].name, player_name) == 0) { // Checks for matching name
                    // Display player details and asks for update
                    printf("Player found in team %s:\n", teams[i].team_name);
                    printf("Player Name: %s\n", teams[i].players[j].name);
                    printf("Kit Number: %d\n", teams[i].players[j].kit_number);
                    printf("DOB: %s\n", teams[i].players[j].dob);
                    printf("Position: %s\n", teams[i].players[j].position);
                    printf("Do you want to update player details? (1 (Yes) / 0 (No): ");
                    int update_choice; // Asks for update choice
                    scanf("%d", &update_choice);
                    getchar(); // Clear newline left by scanf
                    if (update_choice == 1) {
                        player_info_updation(i, j);
                    }
                    found = 1;
                    break;
                }
            }
        }
    } else {
        invalid_input(); 
        return;
    }

    if (!found) printf("Player not found!\n"); // Notify if player is not found
}

// Displays all teams' statistics, including player details.
void display_data() {
    if (enrolled_teams_count == 0) { // Checks if teams are enrolled
        printf("No teams have been enrolled yet.\n");
        return;
    }
    for (int i = 0; i < enrolled_teams_count; i++) { // Loops through all teams
        printf("\nTeam: %s\n", teams[i].team_name);
        printf("Number of players: %d\n", teams[i].num_players); // Displays no.of players
        if (teams[i].num_players == 0) { // Checks if team has players
            printf("No players in this team.\n");
            continue;
        }
        int total_age = 0; // Initializes total age for calculating average
        for (int j = 0; j < teams[i].num_players; j++) { // Loops through players in the team
            int birth_year = age(teams[i].players[j].dob); // Extracts year from DOB
            int age = current_year - birth_year; // Calculates age
            total_age += age; // Adds to total age for average calculation

            printf("    Player %d:\n      Name: %s\n      Kit Number: %d\n      DOB: %s\n      Position: %s\n      Age: %d\n",
                   j + 1, teams[i].players[j].name,
                   teams[i].players[j].kit_number,
                   teams[i].players[j].dob,
                   teams[i].players[j].position,
                   age); // Displays player details
        }
        double average_age = (double)total_age / teams[i].num_players; // Calculates average age
        printf("Average age of players in this team: %.2f years\n", average_age); // Displays average age
    }
}

// Extracts the year from a date string in the format DD/MM/YYYY.
int age(const char* dob) {
    int year;
    sscanf(dob, "%*d/%*d/%d", &year); // Extracts the year from the DOB string
    return year;
}

// Updates a player's details based on user's choice (name, kit number, DOB, or position).
void player_info_updation(int team_index, int player_index) { 
    int choice;
    printf("1. Update Name\n2. Update Kit Number\n3. Update DOB\n4. Update Position\n");
    printf("Enter your choice(1/2/3/4): ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            if (fgets(teams[team_index].players[player_index].name, sizeof(teams[team_index].players[player_index].name), stdin) == NULL) { // Read new name
                printf("Error reading name.\n");
                return;
            }
            teams[team_index].players[player_index].name[strcspn(teams[team_index].players[player_index].name, "\n")] = '\0'; // Remove newline character
            if (name_validation(team_index, teams[team_index].players[player_index].name)) { // Check for duplicate name
                printf("A player with the name %s exists in this team.\n", teams[team_index].players[player_index].name);
            return; // Exit if duplicate name
            }
            printf("Player name updated successfully!\n");
            break;
        case 2:
            printf("Enter new kit number: ");
            int new_kit;
            scanf("%d", &new_kit);
            getchar();
            if (!kit_validation(team_index, new_kit)) {
                printf("Invalid or duplicate kit number!\n");
                return; // Exits if invalid or duplicate kit number
            }
            teams[team_index].players[player_index].kit_number = new_kit; // Update kit number
            printf("Kit number updated successfully!\n");
            break;
        case 3:
            printf("Enter new DOB (DD/MM/YYYY): ");
            if (fgets(teams[team_index].players[player_index].dob, sizeof(teams[team_index].players[player_index].dob), stdin) == NULL) { // Read new DOB
                printf("Error reading DOB!\n");
                return;
            }
            teams[team_index].players[player_index].dob[strcspn(teams[team_index].players[player_index].dob, "\n")] = '\0'; // Remove newline character
            printf("DOB updated successfully!\n");
            break;
        case 4:
            printf("Enter new position: ");
            if (fgets(teams[team_index].players[player_index].position, sizeof(teams[team_index].players[player_index].position), stdin) == NULL) { // Read new position
                printf("Error reading position!\n");
                return;
            }
            teams[team_index].players[player_index].position[strcspn(teams[team_index].players[player_index].position, "\n")] = '\0'; // Remove newline character
            printf("Position updated successfully!\n");
            break;
        default:
            invalid_input();
            break;
    }
}

//Function to display a message for invalid inputs.
void invalid_input() {
    printf("Invalid input. Please try again!\n");
}