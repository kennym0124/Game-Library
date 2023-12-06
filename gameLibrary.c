#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

//macros
#define record_limit 10
#define str_size 100


//structure
struct videoGames {
	unsigned int deletedRec : 1;
	unsigned int entryID;
	char title[str_size];
	char gamePlatform[str_size];
	char gameGenre[str_size];
	char gameCondition[str_size];
};

//prototypes
void printMenu(int* selection);
void displayRecs(const int recordNumber, struct videoGames* ownedGames);
void deleteRec(int* recordNumber, struct videoGames* ownedGames);
void modifyRecs(const int recordNumber, struct videoGames* ownedGames, char* title, char* gamePlatform, char* gameGenre, char* gameCondition);
void inputs(const int recordNumber, char* title, char* gamePlatform, char* gameGenre, char* gameCondition);
void gameArray(struct videoGames ownedGames[]);
void entryProperties(char* title, char* gamePlatform, char* gameGenre, char* gameCondition);
int addRec(struct videoGames* ownedGames, const int newRecord, const int id, const char* title, const char* gamePlatform, const char* gameGenre, const char* gameCondition);
int availableEntrySpot(const struct videoGames ownedGames[]);

//custom functions
void printMenu(int* selection) {
	int garbageInput = 0;

	puts("---------------------------------------------------------------------------------------------------");
	puts("Welcome to the Video Game Collection Database Application.\nPlease choose an option to get started.");
	puts("DISCLAIMER: IF USING SPACES IN INPUTS, USE UNDERSCORES, NOT SPACES. THANK YOU.\n(Ex: Super Mario --> Super_Mario)");
	puts("---------------------------------------------------------------------------------------------------");
	puts("Select an option below:");
	printf("1. Display\n2. Add\n3. Delete\n4. Modify\n5. Exit\n6. Clear Screen (make it readable :D)\n");

	if (scanf("%d", selection) != 1) {
		while (garbageInput = getchar() != '\n' && garbageInput != EOF) {}
	}
}

void displayRecs(const int recordNumber, struct videoGames* ownedGames) {
	if (recordNumber > 0) {
		puts("Entry ID | Title          | Platform         | Genre         | Game Condition ");
		puts("---------------------------------------------------------------------------------------------------");
		for (int i = 0; i < record_limit; i++) {
			if (ownedGames[i].deletedRec != 1) {
				printf("%-11d%-17s%-19s%-16s%-10s\n", ownedGames[i].entryID, ownedGames[i].title, ownedGames[i].gameGenre, ownedGames[i].gameCondition, ownedGames[i].gamePlatform);
			}
		}
	}
	else { puts("There are currently no records to display. Please add an entry before selecting this option again."); }
}
int addRec(struct videoGames* ownedGames, const int newRecord, const int id, const char* title, const char* gamePlatform, const char* gameGenre, const char* gameCondition) {
	int incorrect = 0;
	int ret = 0;

	ownedGames[newRecord].deletedRec = 0;
	ownedGames[newRecord].entryID = id;
	if (title[0] > 0) {
		incorrect = strcpy_s(ownedGames[newRecord].title, sizeof(ownedGames[newRecord].title), title);
		ret = ret + incorrect;
	}
	else {
		ret++;
	}
	if (gamePlatform[0] > 0) {
		incorrect = strcpy_s(ownedGames[newRecord].gamePlatform, sizeof(ownedGames[newRecord].gamePlatform), gamePlatform);
		ret = ret + incorrect;
	}
	else {
		ret++;
	}
	if (gameGenre[0] != '\0') {
		incorrect = strcpy_s(ownedGames[newRecord].gameGenre, sizeof(ownedGames[newRecord].gameGenre), gameGenre);
		ret = ret + incorrect;
	}
	if (gameCondition[0] > '\0') {
		incorrect = strcpy_s(ownedGames[newRecord].gameCondition, sizeof(ownedGames[newRecord].gameCondition), gameCondition);
		ret = ret + incorrect;
	}
	else {
		ret++;
	}
	return ret;
}

void deleteRec(int* recordNumber, struct videoGames* ownedGames) {
	unsigned int id = 0, incorrect = 0, returnCode = 0;

	if (*recordNumber > 0) {
		puts("\nPlease enter the ID of the entry you wish to delete: ");
		returnCode = scanf("%d", &id);
		for (int i = 0; i < record_limit; i++) {
			if (ownedGames[i].entryID == id) {
				ownedGames[i].deletedRec = 1;
				ownedGames[i].entryID = 0;

				for (int j = 0; j < str_size; j++) {
					ownedGames[i].title[j] = '\0';
					ownedGames[i].gamePlatform[j] = '\0';
					ownedGames[i].gameGenre[j] = '\0';
					ownedGames[i].gameCondition[j] = '\0';
				}
				--* recordNumber;
				break;
			}
			else {
				if (i == (record_limit - 1)) {

					puts("\nThat is not a valid record. Please verify the ID you wish to input and try again.\n");
				}
			}
		}
	}
	else { puts("There are no entries that are available for deletion."); }

}
void modifyRecs(const int recordNumber, struct videoGames* ownedGames, char* title, char* gamePlatform, char* gameGenre, char* gameCondition) {
	unsigned int gameID = 0;
	int garbage = 0;
	int	incorrect = 1;
	int	index = -1;
	int newProperty = 0;
	int	choice = 0;
	int	validInput = -1;
	if (recordNumber > 0) {
		while (incorrect != 0) {
			puts("Please enter an entry ID for the record you would like to modify: ");
			if (scanf("%u", &gameID) != 1) {
				while (garbage = getchar() != '\n' && garbage != EOF) {}
				puts("\nThat is not a valid record. Please verify the ID you wish to input and try again.\n");
			}
			else {
				for (int i = 0; i < record_limit; i++) {
					if (ownedGames[i].entryID == gameID) {
						index = i;
						break;
					}
				}
				if (index != -1) {
					while (validInput == -1) {
						puts("Would you like to enter a different Title?\n1. YES 2. NO");
						if (scanf("%u", &choice) != 1) {
							while (garbage = getchar() != '\n' && garbage != EOF) {}
							puts("Please enter a valid option.");
						}
						else {
							if (choice == 1) {
								puts("Please enter a new title. (up to 60 characters): ");
								newProperty = scanf("%s", title);
								strcpy_s(ownedGames[index].title, sizeof(ownedGames[index].title), title);
							}
							validInput = 0;
						}
					}
					validInput = -1;
					while (validInput == -1) {
						puts("Would you like to enter a different platform?\n1. YES 2. NO ");
						if (scanf("%u", &choice) != 1) {
							while (garbage = getchar() != '\n' && garbage != EOF) {}
							puts("Please enter a valid option.");
						}
						else {
							if (choice == 1) {
								puts("Please enter a new platform. (up to 60 characters): ");
								newProperty = scanf("%s", gamePlatform);
								strcpy_s(ownedGames[index].gamePlatform, sizeof(ownedGames[index].gamePlatform), gamePlatform);
							}
							validInput = 0;
						}
					}
					validInput = -1;
					while (validInput == -1) {
						puts("Would you like to change the genre?\n1. YES 2. NO");
						if (scanf("%d", &choice) != 1) {
							while (garbage = getchar() != '\n' && garbage != EOF) {}
							puts("Please enter a valid option.");
						}
						else {
							if (choice == 1) {
								puts("Enter a new genre. (up to 60 characters): ");
								newProperty = scanf("%s", gameGenre);
								strcpy_s(ownedGames[index].gameGenre, sizeof(ownedGames[index].gameGenre), gameGenre);
							}
							validInput = 0;
						}
					}

					validInput = -1;

					while (validInput == -1) {
						puts("Would you like to change the game's condition?\n1. YES 2. NO");
						if (scanf("%u", &choice) != 1) {
							while (garbage = getchar() != '\n' && garbage != EOF) {}
							puts("Please enter a valid option.");
						}
						else {
							if (choice == 1) {
								puts("Please enter the game's new condition. (up to 60 characters)");
								newProperty = scanf("%s", gameCondition);
								strcpy_s(ownedGames[index].gameCondition, sizeof(ownedGames[index].gameCondition), gameCondition);
							}
							validInput = 0;
						}
					}

				}
				else {
					puts("That entry ID does not exist.");
				}
				incorrect = 0;
			}
		}
	}
	else { puts("\nThere are currently no valid records to modify. Please add one before selecting this option again.\n"); }
}

void inputs(const int recordNumber, char* title, char* gamePlatform, char* gameGenre, char* gameCondition) {
	int entryProperty = 0;
	int	selection = 0;
	int	garbage = 0;
	if (recordNumber >= record_limit) {
		puts("The current record array is completely full and no longer has any open space for new entries.\n Please consider deleting an entry before adding a new one.");
	}
	else {

		puts("---------------------------------------------------------------------------------------------------");
		puts("Please input a Title. (Up to 60 characters)");
		entryProperty = scanf("%s", title);
		puts("---------------------------------------------------------------------------------------------------");
		puts("Please input a Platform. (Up to 60 characters)");
		entryProperty = scanf("%s", gamePlatform);
		puts("---------------------------------------------------------------------------------------------------");
		puts("Please input a Genre. (Up to 60 characters)");
		entryProperty = scanf("%s", gameGenre);
		puts("---------------------------------------------------------------------------------------------------");
		puts("Please input the game's condition. (Up to 60 characters)");
		entryProperty = scanf("%s", gameCondition);
	}
	system("cls");
}

void gameArray(struct videoGames ownedGames[]) {
	for (int i = 0; i < record_limit; i++) {
		ownedGames[i].deletedRec = 1;
		ownedGames[i].entryID = 0;

		for (int j = 0; j < str_size; j++) {
			ownedGames[i].title[j] = '\0';
			ownedGames[i].gamePlatform[j] = '\0';
			ownedGames[i].gameGenre[j] = '\0';
			ownedGames[i].gameCondition[j] = '\0';
		}
	}
}
void entryProperties(char* title, char* gamePlatform, char* gameGenre, char* gameCondition) {
	for (int j = 0; j < str_size; j++) {
		title[j] = '\0';
		gamePlatform[j] = '\0';
		gameGenre[j] = '\0';
		gameCondition[j] = '\0';
	}
}
int availableEntrySpot(const struct videoGames ownedGames[]) {
	int ret = -1;

	for (int i = 0; i < record_limit; i++) {
		if (ownedGames[i].deletedRec == 1) {
			ret = i;
			break;
		}
	}
	return ret;
}

//main function (duh)
int main() {
	//variables
	int selection = 0;
	int recordNumber = 0;
	int next = 0;
	int keyStore = 1;
	int incorrect = 0;
	struct videoGames ownedGames[record_limit];
	char title[str_size];
	char gamePlatform[str_size];
	char gameGenre[str_size];
	char gameCondition[str_size];

	//menu
	enum options { Display = 1, Add = 2, Delete = 3, Modify = 4, Exit = 5, ClearScreen= 6 };

	gameArray(ownedGames);

	while (selection != Exit)
	{
		entryProperties(title, gamePlatform, gameGenre, gameCondition);
		printMenu(&selection);

		if(selection == Display) { displayRecs(recordNumber, ownedGames); }
		else if(selection == Add) {
			next = availableEntrySpot(ownedGames);
			inputs(recordNumber, title, gamePlatform, gameGenre, gameCondition);
			incorrect = addRec(ownedGames, next, keyStore, title, gameCondition, gamePlatform, gameGenre);
			recordNumber++;
			keyStore++;
		}
		else if(selection == Modify) {
			modifyRecs(recordNumber, ownedGames, title, gameCondition, gameGenre, gamePlatform);
		}
		else if(selection == Delete) {
			deleteRec(&recordNumber, ownedGames);
		}
		else if(selection == Exit) { puts("You have chosen to exit the application. Exiting..."); }
		else if (selection == ClearScreen) { system("cls"); }
		else { puts("That is not an option. Please enter a valid option."); }
	}

	return 0;

}
