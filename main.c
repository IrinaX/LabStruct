#include <stdio.h>
#include <string.h>
#include <limits.h>

/*
 * Implement a notebook that stores personal information (last name, first name, age, gender, phone number).
 * Provide sorting of records by last name and search by age.
 */

typedef struct {
    char name[15];
    char surname[20];
    int age;
    char gender[7];
    char telNumber[12];
} person;

person addPerson(char name[], char surname[], int age, char gender[], char telNumber[]);

unsigned int getAmountOfPeople();

void getPeopleData(unsigned int amountOfPeople, person *notebook);

void printNotebook(unsigned int amountOfPeople, person *notebook);

void printMenu();

int getCorrectValue(char *string, int length, int switcher);

int getCorrectIntValue(int maxValue);

void getCorrectStringValue(char *string, int length);

int getMenuVariant(int maxVariant);

int getAge(int maxAge);

unsigned int getNumberOfMatches(int age, person *notebook, unsigned int amountOfPeople);

void findPeopleByAge(int age, person *notebook, unsigned int amountOfPeople, person *foundPeople);

void sortBySurname(unsigned int amountOfPeople, person *notebook);

int main() {
    unsigned int amountOfPeople = getAmountOfPeople();
    person notebook[amountOfPeople];
    getPeopleData(amountOfPeople, notebook);
    printNotebook(amountOfPeople, notebook);
    int variant = 0;
    while (variant != 5) {
        printMenu();
        variant = getMenuVariant(5);
        switch (variant) {
            case 1: {
                sortBySurname(amountOfPeople, notebook);
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 2: {
                int age = getAge(150);
                unsigned int numberOfMatches = getNumberOfMatches(age, notebook, amountOfPeople);
                if (numberOfMatches != 0) {
                    person foundPeople[numberOfMatches];
                    findPeopleByAge(age, notebook, amountOfPeople, foundPeople);
                    printNotebook(numberOfMatches, foundPeople);
                }
                break;
            }
            case 3: {
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 4:
                printf("show person's info");
                break;
            case 5:
                printf("exit");
                break;
            default:
                break;
        }
    }
//    system("pause");
    return 0;
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
        printf("%d person. Input name:", numeration);
        getCorrectStringValue(name, 15);

        printf("%d person. Input surname:", numeration);
        getCorrectStringValue(surname, 20);

        printf("%d person. Input age:", numeration);
        age = getCorrectIntValue(150);

        printf("%d person. Input gender:", numeration);
        getCorrectStringValue(gender, 7);

        printf("%d person. Input telNumber:", numeration);
        getCorrectValue(telNumber, 12, 0);

        printf("\n");
        notebook[i] = addPerson(name, surname, age, gender, telNumber);
    }
}

person addPerson(char *name, char *surname, int age, char *gender, char *telNumber) {
    person addedPerson;
    strcpy(addedPerson.name, name);
    strcpy(addedPerson.surname, surname);
    addedPerson.age = age;
    strcpy(addedPerson.gender, gender);
    strcpy(addedPerson.telNumber, telNumber);
    return addedPerson;
}

unsigned int getAmountOfPeople() {
    printf("Input amount of people: ");
    unsigned int amountOfPeople = (unsigned int) getCorrectIntValue(INT_MAX);
    return amountOfPeople;
}

void printNotebook(unsigned int amountOfPeople, person *notebook) {
    int numeration;
    for (int i = 0; i < amountOfPeople; ++i) {
        numeration = i + 1;
        printf("%d) name: %s \tsurname: %s \tage: %d \tgender: %s \ttelNumber: %s\n", numeration, notebook[i].name,
               notebook[i].surname, notebook[i].age, notebook[i].gender, notebook[i].telNumber);
    }
}

void printMenu() {
    printf("\nWhat do you want to do?\n");
    printf("1. Sort list by surname\n");
    printf("2. Searching people by age\n");
    printf("3. Show notebook\n");
    printf("4. Show person info by his number in notebook\n");
    printf("5. Exit\n");
    printf(">");
}

int getCorrectIntValue(int maxValue) {
    int result = 0;
    char string[100];
    // ���� ���� �����������, �������� �� ���� � ������ ��������� ���
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
            // �������� ������� �������, ���� �� �����, �� �������� �� '\0'
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
            // �������� ������� �������, ���� �� �����(�������� ��� ���������), �� �������� �� '\0'
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

int getMenuVariant(int maxVariant) {
    int variant = getCorrectIntValue(maxVariant);
    return variant;
}

int getAge(int maxAge) {
    printf("Enter age: ");
    int age = getCorrectIntValue(maxAge);
    return age;
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





