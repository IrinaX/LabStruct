#include <stdio.h>
#include <stdlib.h>
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

unsigned int getAmountOfPeople();

int getInputData(char *name, char *surname, int age, char *gender, char *telNumber);

void getPeopleData(unsigned int amountOfPeople, person *notebook);

void printNotebook(unsigned int amountOfPeople, person *notebook);

void printMenu();

int getCorrectValue(char *string, int length, int switcher);

int getCorrectIntValue();

void getCorrectStringValue(char *string, int length);

unsigned int getNumberOfMatches(int age, person *notebook, unsigned int amountOfPeople);

void findPeopleByAge(int age, person *notebook, unsigned int amountOfPeople, person *foundPeople);

void sortBySurname(unsigned int amountOfPeople, person *notebook);

void showPerson(person *notebook, int number);

person *addNewPerson(unsigned int *amountOfPeople, person *notebook);

person *removePerson(unsigned int *amountOfPeople, person *notebook, int index);

void saveNotebook(unsigned int amountOfPeople, person *notebook, char *fileName);

void getCorrectFileName(char *fileName);

person *loadNotebook(person *notebook, char *fileName, unsigned int *amountOfPeople);

int checkInputString(const char *string, int length, char *errorMessage);

int checkInputString4Numbers(const char *string, int length, char *errorMessage);

void deleteFile(char *fileName);

unsigned int removeAllInfo(person *notebook);

int main() {
    person *notebook = NULL;
    unsigned int amountOfPeople = 0;
    int variant = 0;
    int maxVariant = 12;
    while (variant != maxVariant) {
        printMenu();
        variant = getCorrectIntValue(maxVariant);
        switch (variant) {
            case 1: { //Create new notebook
                amountOfPeople = getAmountOfPeople();
                notebook = malloc(amountOfPeople * sizeof(person));
                if (NULL == notebook) {
                    printf("Allocation error.");
                    exit(0);
                }
                getPeopleData(amountOfPeople, notebook);
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 2: { //Sort list by surname
                if (amountOfPeople > 0) {
                    sortBySurname(amountOfPeople, notebook);
                    printNotebook(amountOfPeople, notebook);
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNotebook is empty.\n");
                }
                break;
            }
            case 3: { //Searching people by age
                if (amountOfPeople > 0) {
                    printf("Enter age: ");
                    int age = getCorrectIntValue(150);
                    unsigned int numberOfMatches = getNumberOfMatches(age, notebook, amountOfPeople);
                    if (numberOfMatches != 0) {
                        printf("Search result:\n");
                        person foundPeople[numberOfMatches];
                        findPeopleByAge(age, notebook, amountOfPeople, foundPeople);
                        printNotebook(numberOfMatches, foundPeople);
                    }
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNotebook is empty.\n");
                }
                break;
            }
            case 4: { //Show notebook
                if (amountOfPeople > 0) {
                    printf("Notebook:\n");
                    printNotebook(amountOfPeople, notebook);
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNotebook is empty.\n");
                }
                break;
            }
            case 5: { //Show person info by his number in notebook
                if (amountOfPeople > 0) {
                    printf("Enter the person's number: ");
                    int number = getCorrectIntValue((int) amountOfPeople);
                    showPerson(notebook, number);
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNotebook is empty.\n");
                }
                break;
            }
            case 6: { //Add person
                notebook = addNewPerson(&amountOfPeople, notebook);
                printf("\nUpdated notebook:\n");
                printNotebook(amountOfPeople, notebook);
                break;
            }
            case 7: { //Remove person
                if (amountOfPeople > 0) {
                    printf("Enter the person's number: ");
                    int index = getCorrectIntValue((int) amountOfPeople);
                    --index;
                    notebook = removePerson(&amountOfPeople, notebook, index);
                    if (amountOfPeople > 0) {
                        printf("\nPerson was removed. Updated notebook:\n");
                        printNotebook(amountOfPeople, notebook);
                    } else {
                        printf("\nNotebook is empty.\n");
                    }
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNotebook is empty.\n");
                }
                break;
            }
            case 8: { //Save notebook
                if (amountOfPeople > 0) {
                    char fileName[20];
                    getCorrectFileName(fileName);
                    saveNotebook(amountOfPeople, notebook, fileName);
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNo data to save.\n");
                }
                break;
            }
            case 9: { //Load notebook from file
                char fileName[20];
                getCorrectFileName(fileName);
                notebook = loadNotebook(notebook, fileName, &amountOfPeople);
                break;
            }
            case 10: { //Delete file
                char fileName[20];
                getCorrectFileName(fileName);
                deleteFile(fileName);
                break;
            }
            case 11: { //Clear all data
                if (amountOfPeople > 0) {
                    amountOfPeople = removeAllInfo(notebook);
                } else {
                    free(notebook);
                    notebook = NULL;
                    printf("\nNotebook is empty.\n");
                }
                break;
            }
            case 12: { //Exit
                printf("Exit...");
                free(notebook);
                notebook = NULL;
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
    printf("Input name (max 14 symbols):");
    getCorrectStringValue(name, 15);

    printf("Input surname (max 19 symbols):");
    getCorrectStringValue(surname, 20);

    printf("Input age (from 0 to 150):");
    age = getCorrectIntValue(150);

    printf("Input gender (max 6 symbols):");
    getCorrectStringValue(gender, 7);

    printf("Input telNumber (max 11 symbols):");
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

unsigned int getAmountOfPeople() {
    printf("Input amount of people: ");
    unsigned int amountOfPeople = (unsigned int) getCorrectIntValue();
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
    printf("1. Create new notebook\n");
    printf("2. Sort list by surname\n");
    printf("3. Searching people by age\n");
    printf("4. Show notebook\n");
    printf("5. Show person info by his number in notebook\n");
    printf("6. Add person\n");
    printf("7. Remove person\n");
    printf("8. Save notebook\n");
    printf("9. Load notebook from file\n");
    printf("10. Delete file\n");
    printf("11. Clear all data\n");
    printf("12. Exit\n");
    printf(">");
}

int getCorrectIntValue() {
    int result = 0;
    char string[100];
    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (result < 1) {
        result = getCorrectValue(string, 100, 1);
        if (result < 1) {
            printf("Incorrect input. Try again: ");
        }
    }
    return result;
}

int getCorrectValue(char *string, int length, int switcher) {
    int booleanVar = -1;
    int intResult;
    while (booleanVar == -1) {
        scanf("%s", string);
        booleanVar = checkInputString4Numbers(string, length, "Incorrect input. Try again: ");
    }
    if (switcher == 1) {
        sscanf(string, "%d", &intResult);
        return intResult;
    } else {
        return booleanVar;
    }
}

void getCorrectStringValue(char *string, int length) { //array, length of array
    int booleanVar = -1;
    while (booleanVar == -1) {
        scanf("%s", string);
        booleanVar = checkInputString(string, length, "Incorrect input. Try again: ");
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

person *addNewPerson(unsigned int *amountOfPeople, person *notebook) {
    char name[15];
    char surname[20];
    int age = 0;
    char gender[7];
    char telNumber[12];
    age = getInputData(name, surname, age, gender, telNumber); //получаем данные с консоли
    notebook = realloc(notebook,
                       sizeof(person) * (*amountOfPeople + 1)); //выделяем память для нового элемента массива структур
    if (NULL == notebook) {//если ОС не выделила память, выходим из программы
        printf("Allocation error.");
        exit(0);
    }
    notebook[*amountOfPeople] = getNewPerson(name, surname, age, gender, telNumber); //записываем полученные данные
    ++*amountOfPeople; //увеличиваем количество записей в книге на 1
    return notebook; //возвращаем указатель на измененный массив структур
}

person *removePerson(unsigned int *amountOfPeople, person *notebook, int index) {
    --*amountOfPeople;//уменьшаем значение количества записей в книге
    for (int i = 0; i < *amountOfPeople; i++) {
        if (i >= index) {//затираем выбранную запись и переписываем последующие записи до конца книги
            notebook[i] = notebook[i + 1];
        }
    }
    notebook = realloc(notebook,//выделяем память для полученного массива структур, который на 1 меньше предыдущего
                       sizeof(person) * (*amountOfPeople));
    if (NULL == notebook) {//если ОС не выделила память, выходим из программы
        printf("Allocation error.");
        exit(0);
    }
    return notebook;//возвращаем указатель на измененный массив структур
}

void saveNotebook(unsigned int amountOfPeople, person *notebook, char *fileName) {
    FILE *file = fopen(fileName, "w");//открываем файл
    if (file != NULL) {//если файл открылся
        for (int i = 0; i < amountOfPeople; i++) {//записываем информацию в файл через табуляцию
            fprintf(file, "%s\t%s\t%d\t%s\t%s\n",
                    notebook[i].name,
                    notebook[i].surname,
                    notebook[i].age,
                    notebook[i].gender,
                    notebook[i].telNumber);
        }
        printf("\nNotebook was saved in %s\n", fileName);
        fclose(file);//закрываем файл
    } else {// если файл не открылся
        printf("\nSomething went wrong. Try again.\n");
    }
}

void getCorrectFileName(char *fileName) {
    printf("Enter file name: ");
    scanf("%s", fileName);
    if (strstr(fileName, ".txt") == NULL) {// проверка на вхождение ".txt" в введеную строку
        strcat(fileName, ".txt"); // добавляем ".txt"
    }
}

person *loadNotebook(person *notebook, char *fileName, unsigned int *amountOfPeople) {
    char name[15];//переменые куда будут записываться данные из файла
    char surname[20];
    char strAge[20];
    int age;
    char gender[7];
    char telNumber[12];
    FILE *file = fopen(fileName, "r"); //открытие файла
    if (file != NULL) {//если файл открылся
        free(notebook); //освобождаем память для загрузки новых данных
        notebook = NULL; //обнуляем указатель
        *amountOfPeople = 0; //количество записей равно 0 соответственно
        while (1) {
            if (fscanf(file, "%s%s%s%s%s", name, surname, strAge, gender, telNumber) == EOF) {
                //проверка на конец документа и количество людей
                printf("\nFile uploaded successfully.\n");
                break;
            } else {
                if (checkInputString(name, 15, "\nIncorrect name value. Try again.\n") != 0) {
                    //проверка имени
                    free(notebook);//если ошибка то освобождаем память
                    notebook = NULL;
                    break;
                }
                if (checkInputString(surname, 20, "\nIncorrect surname value. Try again.\n") != 0) {
                    //проверка фамилии
                    free(notebook);//если ошибка то освобождаем память
                    notebook = NULL;
                    break;
                }

                if (checkInputString4Numbers(strAge, 20, "\nIncorrect age value. Try again.\n") != 0) {
                    //проверка возраста
                    free(notebook);//если ошибка то освобождаем память
                    notebook = NULL;
                    break;
                } else {
                    if (sscanf(strAge, "%d", &age) < 1 || age > 150) {
                        free(notebook);//если ошибка то освобождаем память
                        notebook = NULL;
                        printf("\nAge out of range. Try again.\n");
                        break;
                    }
                }

                if (checkInputString(gender, 7, "\nIncorrect gender value. Try again.\n") != 0) {
                    //проверка пола
                    free(notebook);//если ошибка то освобождаем память
                    notebook = NULL;
                    break;
                }
                if (checkInputString4Numbers(telNumber, 12, "\nIncorrect phone number value. Try again.\n") == 0) {
                    //проверка номера телефона
                    notebook = realloc(notebook,
                                       sizeof(person) * (*amountOfPeople +
                                                         1));//если ошибки нет, выделяем память для нового элемента массива структур
                    if (NULL == notebook) {
                        printf("Allocation error.");
                        exit(0);
                    }
                    notebook[*amountOfPeople] = getNewPerson(name,
                                                             surname,
                                                             age,
                                                             gender,
                                                             telNumber);//запись данных в массив структур
                    ++*amountOfPeople;//инкремент количества записей
                } else {
                    free(notebook);//если ошибка то освобождаем память
                    notebook = NULL;
                    break;
                }
            }
        }
        fclose(file);//закрытие файла
    } else {//если файл не открылся
        printf("\nSomething went wrong. Try again. Probably, file doesn't exist.\n");
    }
    return notebook; //возвращаем адрес на первый элемент массива в памяти
}

int checkInputString(const char *string, int length, char *errorMessage) {
    int boolVar = 0;
    for (int i = 0; i < length; i++) {
        // проверка каждого символа, если не буква(строчная или заглавная), то проверка на '\0'
        if (!(string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z')) {
            if (string[i] == '\0') {
                boolVar = 0;
            } else {
                printf("%s", errorMessage);
                boolVar = -1;
            }
            break;
        }
    }
    return boolVar;
}

int checkInputString4Numbers(const char *string, int length, char *errorMessage) {
    int boolVar = 0;
    for (int i = 0; i < length; i++) {
        // проверка каждого символа, если не число, то проверка на '\0'
        if (!(string[i] >= '0' && string[i] <= '9')) {
            if (string[i] == '\0') {
                boolVar = 0;
            } else {
                printf("%s", errorMessage);
                boolVar = -1;
            }
            break;
        }
    }
    return boolVar;
}

void deleteFile(char *fileName) {
    if (-1 == remove(fileName)) {
        printf("\nSomething went wrong. Try again.\n");
    } else {
        printf("\nFile was deleted successfully.\n");
    }
}

unsigned int removeAllInfo(person *notebook) {
    free(notebook);
    notebook = NULL;
    printf("\nAll data were deleted successfully.\n");
    return 0;
}




