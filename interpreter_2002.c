#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 2002
#define VAR_NAME_MAX 20

// Prints the top of terminal
void print_intro()
{
    printf("----------------------------------------\n");
    printf("|           INTERPRETER 2002           |\n");
    printf("|   Middle East Technical University   |\n");
    printf("|           by Mert Sonmezer           |\n");
    printf("----------------------------------------\n");
}

// Searches str in varNames
int is_in(char *str, int lenVarNames, char **varNames)
{
    int isIn = 0;

    for (int i = 0; i < lenVarNames; i++)
    {
        if (strcmp(varNames[i], str) == 0)
        {
            isIn = 1;
            break;
        }
    }

    return isIn;
}

// Checks whether str is a number or not
int is_number(char *str)
{
    int len = strlen(str);

    int isNumber = 1;
    for (int i = 0; i < len; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            isNumber = 0;
        }
    }

    return isNumber;
}

// Converts char to int
int char_to_int(char *ch)
{
    if (is_number(ch) == 0)
    {
        return -1;
    }

    int result = 0;
    int len = strlen(ch);

    if (len == 1)
    {
        result += ch[0] - '0';
    }

    else if (len == 2)
    {
        result += ch[1] - '0';
        result += 10 * (ch[0] - '0');
    }

    else if (len == 3)
    {
        result += ch[2] - '0';
        result += 10 * (ch[1] - '0');
        result += 100 * (ch[0] - '0');
    }

    else if (len == 4)
    {
        result += ch[3] - '0';
        result += 10 * (ch[2] - '0');
        result += 100 * (ch[1] - '0');
        result += 1000 * (ch[0] - '0');
    }

    else
    {
        printf("Error!\n");
        return 1;
    }

    return result;
}

// Reallocates area to commands
void realloc_commands(int lenCommands, char ****commandsPointer)
{
    if (*commandsPointer == NULL)
    {
        *commandsPointer = (char ***) malloc(sizeof(char **));
    }

    else
    {
        *commandsPointer = (char ***) realloc(*commandsPointer, sizeof(char **) * (lenCommands + 1));
    }
}

// Reallocates area to varNames
void realloc_varNames(int lenVarNames, char ***varNamesPointer)
{
    if (*varNamesPointer == NULL)
    {
        *varNamesPointer = (char **) malloc(sizeof(char *));
    }

    else
    {
        *varNamesPointer = (char **) realloc(*varNamesPointer, sizeof(char *) * (lenVarNames + 1));
    }
}


// Fills arr with the value of zero
void initialize_array(int len, int arr[len])
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = 0;
    }
}

int main()
{
    print_intro();

    char ***commands = NULL;
    int lenCommands = 0;

    char **varNames = NULL;
    int lenVarNames = 0;

    int line_counter = 0;
    while (1)
    {
        printf("[%d] ", line_counter);

        char **line = NULL;

        char *command = (char *) malloc(sizeof(char) * 10);
        scanf(" %s", command);

        if (strcmp(command, "exit") == 0)
        {
            line = (char **) malloc(sizeof(char *));
            line[0] = command;

            realloc_commands(lenCommands, &commands);
            commands[lenCommands] = line;
            lenCommands++;

            break;
        }

        else if (strcmp(command, "add") == 0 ||
                 strcmp(command, "sub") == 0 ||
                 strcmp(command, "mul") == 0 ||
                 strcmp(command, "div") == 0)
        {
            line = (char **) malloc(sizeof(char *) * 3);

            char *str1 = (char *) malloc(sizeof(char) * VAR_NAME_MAX);
            char *str2 = (char *) malloc(sizeof(char) * VAR_NAME_MAX);
            scanf(" %s %s", str1, str2);

            if (strlen(str1) > VAR_NAME_MAX ||
                strlen(str2) > VAR_NAME_MAX)
            {
                printf(">>> Error: Too long variable name!\n");
                return 1;
            }

            line[0] = command;
            line[1] = str1;
            line[2] = str2;

            realloc_commands(lenCommands, &commands);
            commands[lenCommands] = line;
            lenCommands++;

            int isIn1 = is_in(str1, lenVarNames, varNames);
            if (isIn1 == 0)
            {
                realloc_varNames(lenVarNames, &varNames);
                varNames[lenVarNames] = str1;
                lenVarNames++;
            }

            int isIn2 = is_in(str2, lenVarNames, varNames);
            if (isIn2 == 0)
            {
                realloc_varNames(lenVarNames, &varNames);
                varNames[lenVarNames] = str2;
                lenVarNames++;
            }
        }

        else if (strcmp(command, "set") == 0)
        {
            line = (char **) malloc(sizeof(char *) * 3);

            char *str1 = (char *) malloc(sizeof(char) * VAR_NAME_MAX);
            char *str2 = (char *) malloc(sizeof(char) * 4);
            scanf(" %s %s", str1, str2);

            if (strlen(str1) > VAR_NAME_MAX)
            {
                printf(">>> Error: Too long variable name!\n");
                return 1;
            }

            if (strlen(str2) > 4)
            {
                printf(">>> Error: Too big number!\n");
                return 1;
            }

            if (char_to_int(str2) == -1)
            {
                printf(">>> Error: Not a number!\n");
                return 1;
            }

            line[0] = command;
            line[1] = str1;
            line[2] = str2;

            realloc_commands(lenCommands, &commands);
            commands[lenCommands] = line;
            lenCommands++;

            int isIn = is_in(str1, lenVarNames, varNames);
            if (isIn == 0)
            {
                realloc_varNames(lenVarNames, &varNames);
                varNames[lenVarNames] = str1;
                lenVarNames++;
            }
        }

        else if (strcmp(command, "print") == 0)
        {
            line = (char **) malloc(sizeof(char *) * 2);

            char *str = (char *) malloc(sizeof(char) * VAR_NAME_MAX);
            scanf(" %s", str);

            if (strlen(str) > VAR_NAME_MAX)
            {
                printf(">>> Error: Too long variable name!\n");
                return 1;
            }

            line[0] = command;
            line[1] = str;

            realloc_commands(lenCommands, &commands);
            commands[lenCommands] = line;
            lenCommands++;

            int isIn = is_in(str, lenVarNames, varNames);
            if (isIn == 0)
            {
                realloc_varNames(lenVarNames, &varNames);
                varNames[lenVarNames] = str;
                lenVarNames++;
            }
        }

        else if (strcmp(command, "goto") == 0)
        {
            line = (char **) malloc(sizeof(char *) * 4);

            char *str1 = (char *) malloc(sizeof(char) * 4);
            char *str2 = (char *) malloc(sizeof(char) * VAR_NAME_MAX);
            char *str3 = (char *) malloc(sizeof(char) * VAR_NAME_MAX);
            scanf(" %s %s %s", str1, str2, str3);

            if (strlen(str2) > VAR_NAME_MAX ||
                strlen(str3) > VAR_NAME_MAX)
            {
                printf(">>> Error: Too long variable name!\n");
                return 1;
            }

            if (char_to_int(str1) > lenCommands)
            {
                printf(">>> Error: Not enough lines to go back!\n");
                return 1;
            }

            line[0] = command;
            line[1] = str1;
            line[2] = str2;
            line[3] = str3;

            realloc_commands(lenCommands, &commands);
            commands[lenCommands] = line;
            lenCommands++;

            int isIn1 = is_in(str2, lenVarNames, varNames);
            if (isIn1 == 0)
            {
                realloc_varNames(lenVarNames, &varNames);
                varNames[lenVarNames] = str2;
                lenVarNames++;
            }

            int isIn2 = is_in(str3, lenVarNames, varNames);
            if (isIn2 == 0)
            {
                realloc_varNames(lenVarNames, &varNames);
                varNames[lenVarNames] = str3;
                lenVarNames++;
            }
        }

        else
        {
            printf(">>> Error: Unexpected error!\n");
            return 1;
        }

        line_counter++;
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int values[lenVarNames];
    initialize_array(lenVarNames, values);

    int currentLine = 0;
    while (1)
    {
        if (strcmp(commands[currentLine][0], "exit") == 0)
        {
            break;
        }

        else if (strcmp(commands[currentLine][0], "set") == 0)
        {
            int value = char_to_int(commands[currentLine][2]);

            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][1]) == 0)
                {
                    values[i] = value;
                }
            }
            currentLine++;
        }

        else if(strcmp(commands[currentLine][0], "add") == 0)
        {
            int val1, index;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][1]) == 0)
                {
                    val1 = values[i];
                    index = i;
                }
            }

            int val2;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][2]) == 0)
                {
                    val2 = values[i];
                }
            }

            int value = val1 + val2;
            if (value > MAX)
            {
                value = MAX;
            }

            values[index] = value;
            currentLine++;
        }

        else if(strcmp(commands[currentLine][0], "sub") == 0)
        {
            int val1, index;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][1]) == 0)
                {
                    val1 = values[i];
                    index = i;
                }
            }

            int val2;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][2]) == 0)
                {
                    val2 = values[i];
                }
            }

            int value = val1 - val2;
            if (value < 0)
            {
                value = 0;
            }

            values[index] = value;
            currentLine++;
        }

        else if(strcmp(commands[currentLine][0], "mul") == 0)
        {
            int val1, index;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][1]) == 0)
                {
                    val1 = values[i];
                    index = i;
                }
            }

            int val2;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][2]) == 0)
                {
                    val2 = values[i];
                }
            }

            int value = val1 * val2;
            if (value > MAX)
            {
                value = MAX;
            }

            values[index] = value;
            currentLine++;
        }

        else if(strcmp(commands[currentLine][0], "div") == 0)
        {
            int val1, index;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][1]) == 0)
                {
                    val1 = values[i];
                    index = i;
                }
            }

            int val2;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][2]) == 0)
                {
                    val2 = values[i];
                }
            }

            int value = val1 / val2;
            values[index] = value;
            currentLine++;
        }

        else if(strcmp(commands[currentLine][0], "print") == 0)
        {
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][1]) == 0)
                {
                    printf(">>> %s = %d\n", varNames[i], values[i]);
                }
            }

            currentLine++;
        }

        else if(strcmp(commands[currentLine][0], "goto") == 0)
        {
            int val1;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][2]) == 0)
                {
                    val1 = values[i];
                }
            }

            int val2;
            for (int i = 0; i < lenVarNames; i++)
            {
                if (strcmp(varNames[i], commands[currentLine][3]) == 0)
                {
                    val2 = values[i];
                }
            }

            if (val1 < val2)
            {
                currentLine = char_to_int(commands[currentLine][1]);
            }

            else
            {
                currentLine++;
            }
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Took %lf seconds\n", cpu_time_used);

    return 0;
}
