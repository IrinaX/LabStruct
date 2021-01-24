#include <stdio.h>
#include <string.h>

/*
 * Implement a notebook that stores personal information (last name, first name, age, gender, phone number).
 * Provide sorting of records by last name and search by age. Max people = 20.
 */

typedef struct {
    char name[15];
    char surname[20];
    int age;
    char gender[7];
    char telNumber[12];
} person;

person getNewPerson(char name[], char surname[], int age, char gender[], char telNumber[]);

unsigned int getAmountOfPeople(int maxVal);

int getInputData(char *name, char *surname, int age, char *gender, char *telNumber);

void getPeopleData(unsigned int amountOfPeople, person *notebook);

void printNotebook(unsigned int amountOfPeople, person *notebook);

void printMenu();

int getCorrectValue(char *string, int length, int switcher);

int getCorrectIntValue(int maxValue);

void getCorrectStringValue(char *string, int length);

unsigned int getNumberOfMatches(int age, person *notebook, unsigned int amountOfPeople);

void findPeopleByAge(int age, person *notebook, unsigned int amountOfPeople, person *foundPeople);

void sortBySurname(unsigned int amountOfPeople, person *notebook);

void showPerson(person *notebook, int number);

unsigned int addNewPerson(unsigned int amountOfPeople, person *notebook);

unsigned int removePerson(unsigned int amountOfPeople, person *notebook, int index);

int main() {
    int maxAmountOfPeople = 20;
    person notebook[maxAmountOfPeople];
    unsigned int amountOfPeople = getAmountOfPeople(maxAmountOfPeople);
    getPeopleData(amountOfPeople, notebook);
    printNotebook(amountOfPeople, notebook);
    int variant = 0;
    int maxVariant = 7;
    while (variant != maxVariant) {
        printMenu();
        variant = getCorrectIntValue(maxVariant);
        switch (variant) {
            case 1: { //Sort list by surname
                sortBySurname(amountOfPeople, notebook);
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 2: { //Searching people by age
                printf("Enter age: ");
                int age = getCorrectIntValue(150);
                unsigned int numberOfMatches = getNumberOfMatches(age, notebook, amountOfPeople);
                if (numberOfMatches != 0) {
                    printf("Search result:\n");
                    person foundPeople[numberOfMatches];
                    findPeopleByAge(age, notebook, amountOfPeople, foundPeople);
                    printNotebook(numberOfMatches, foundPeople);
                }
                break;
            }
            case 3: { //Show notebook
                printf("Notebook:\n");
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 4: { //Show person info by his number in notebook
                printf("Enter the person's number: ");
                int number = getCorrectIntValue((int) amountOfPeople);
                showPerson(notebook, number);
                break;
            }
            case 5: { //Add person
                if (amountOfPeople < maxAmountOfPeople) {
                    amountOfPeople = addNewPerson(amountOfPeople, notebook);
                } else {
                    printf("\nNotebook is full.\n");
                }
                printf("\nUpdated notebook:\n");
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 6: { //todo: Remove person
                if (amountOfPeople > 0) {
                    printf("Enter the person's number: ");
                    int index = getCorrectIntValue((int) amountOfPeople);
                    --index;
                    amountOfPeople = removePerson(amountOfPeople, notebook, index);
                    printf("\nPerson was removed. Updated notebook:\n");
                    printNotebook(amountOfPeople, notebook);
                } else {
                    printf("\nNotebook is empty.\n");
                }

                break;
            }
            case 7: {
                printf("Exit...");
                break;
            }
            default:
                break;
        }
    }
//    system("pause");
    return 0;
}

int getInputData(char *name, char *surname, int age, char *gender, char *telNumber) {
    printf("Input name:");
    getCorrectStringValue(name, 15);

    printf("Input surname:");
    getCorrectStringValue(surname, 20);

    printf("Input age:");
    age = getCorrectIntValue(150);

    printf("Input gender:");
    getCorrectStringValue(gender, 7);

    printf("Input telNumber:");
    getCorrectValue(telNumber, 12, 0);
    return age;
}

void getPeopleData(unsigned int amountOfPeople, person *notebook) {
    char name[15];
    char surname[20];
    int age;
    char gender[7];
    char telNumber[12];
    int numeration;
    for (int i = 0; i < amountOfPeople; ++i) {
        numeration = i + 1;
        printf("%d person.\n", numeration);
        age = getInputData(name, surname, age, gender, telNumber);
        printf("\n");
        notebook[i] = getNewPerson(name, surname, age, gender, telNumber);
    }
}

person getNewPerson(char *name, char *surname, int age, char *gender, char *telNumber) {
    person newPerson;
    strcpy(newPerson.name, name);
    strcpy(newPerson.surname, surname);
    newPerson.age = age;
    strcpy(newPerson.gender, gender);
    strcpy(newPerson.telNumber, telNumber);
    return newPerson;
}

unsigned int getAmountOfPeople(int maxVal) {
    printf("Input amount of people: ");
    unsigned int amountOfPeople = (unsigned int) getCorrectIntValue(maxVal);//max amountOfPeople = 20 (task)
    return amountOfPeople;
}

void printNotebook(unsigned int amountOfPeople, person *notebook) {
    if (amountOfPeople > 0) {
        int numeration;
        for (int i = 0; i < amountOfPeople; ++i) {
            numeration = i + 1;
            printf("%d) name: %s \tsurname: %s \tage: %d \tgender: %s \ttelNumber: %s\n", numeration, notebook[i].name,
                   notebook[i].surname, notebook[i].age, notebook[i].gender, notebook[i].telNumber);
        }
    } else {
        printf("\nNotebook is empty.\n");
    }
}

void printMenu() {
    printf("\nWhat do you want to do?\n");
    printf("1. Sort list by surname\n");
    printf("2. Searching people by age\n");
    printf("3. Show notebook\n");
    printf("4. Show person info by his number in notebook\n");
    printf("5. Add person\n");
    printf("6. Remove person\n");
    printf("7. Exit\n");
    printf(">");
}

int getCorrectIntValue(int maxValue) {
    int result = 0;
    char string[100];
    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (result < 1 || result > maxValue) {
        result = getCorrectValue(string, 100, 1);
        if (result < 1 || result > maxValue) {
            printf("Incorrect input. Try again: ");
        }
    }
    return result;
}

int getCorrectValue(char *string, int length, int switcher) { //array, length of array
    int booleanVar = 0;
    int intResult;
    while (1) {
        scanf("%s", string);
        for (int i = 0; i < length; i++) {
            // проверка каждого символа, если не число, то проверка на '\0'
            if (!(string[i] >= '0' && string[i] <= '9')) {
                if (string[i] == '\0') {
                    booleanVar = 1;
                } else {
                    printf("Incorrect input. Try again: ");
                    booleanVar = 0;
                }
                break;
            }
        }
        if (booleanVar == 1) {
            break;
        }
    }
    if (switcher == 1) {
        sscanf(string, "%d", &intResult);
        return intResult;
    } else {
        return booleanVar;
    }
}

void getCorrectStringValue(char *string, int length) { //array, length of array
    int booleanVar = 0;
    while (1) {
        scanf("%s", string);
        for (int i = 0; i < length; i++) {
            // проверка каждого символа, если не буква(строчная или заглавная), то проверка на '\0'
            if (!(string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z')) {
                if (string[i] == '\0') {
                    booleanVar = 1;
                } else {
                    printf("Incorrect input. Try again: ");
                    booleanVar = 0;
                }
                break;
            }
        }
        if (booleanVar == 1) {
            break;
        }
    }
}

void findPeopleByAge(int age, person *notebook, unsigned int amountOfPeople, person *foundPeople) {
    int j = 0;
    for (int i = 0; i < amountOfPeople; ++i) {
        if (notebook[i].age == age) {
            foundPeople[j] = notebook[i];
            ++j;
        }
    }
}

unsigned int getNumberOfMatches(int age, person *notebook, unsigned int amountOfPeople) {
    int numberOfMatches = 0;
    for (int i = 0; i < amountOfPeople; ++i) {
        if (notebook[i].age == age) {
            ++numberOfMatches;
        }
    }
    if (numberOfMatches == 0) {
        printf("\nNo matches found.\n");
        return 0;
    } else {
        return numberOfMatches;
    }
}

void sortBySurname(unsigned int amountOfPeople, person *notebook) {
    for (int i = (int) amountOfPeople - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (strcmp(notebook[j].surname, notebook[j + 1].surname) > 0) {
                person savedPerson = notebook[j];
                notebook[j] = notebook[j + 1];
                notebook[j + 1] = savedPerson;
            }
        }
    }
}

void showPerson(person *notebook, int number) {
    printf("%d) name: %s \tsurname: %s \tage: %d \tgender: %s \ttelNumber: %s\n", number, notebook[number - 1].name,
           notebook[number - 1].surname, notebook[number - 1].age, notebook[number - 1].gender,
           notebook[number - 1].telNumber);
}

unsigned int addNewPerson(unsigned int amountOfPeople, person *notebook) {
    char name[15];
    char surname[20];
    int age = 0;
    char gender[7];
    char telNumber[12];
    age = getInputData(name, surname, age, gender, telNumber);
    printf("name: %s \tsurname: %s \tage: %d \tgender: %s \ttelNumber: %s\n", name,
           surname, age, gender, telNumber);
    notebook[amountOfPeople] = getNewPerson(name, surname, age, gender, telNumber);
    ++amountOfPeople;
    return amountOfPeople;
}

unsigned int removePerson(unsigned int amountOfPeople, person *notebook, int index) {
    --amountOfPeople;
    for (int i = 0; i < amountOfPeople; i++) {
        if (i >= index) {
            notebook[i] = notebook[i + 1];
        }
    }
    return amountOfPeople;
}



