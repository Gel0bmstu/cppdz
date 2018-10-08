/* Задача A-6. Задача о приведении строк к нижнему регистру символов
Time limit: 14 s
Memory limit:   64 M
Составить программу построчной обработки текста. Суть обработки - приведение каждого символа в каждой строке к нижнему регистру.

Программа считывает входные данные со стандартного ввода, и печатает результат в стандартный вывод.

Процедура приведения к нижнему регистру должна быть оформлена в виде отдельной функции, которой на вход подается массив строк (который необходимо обработать), количество переданных строк, а также указатель на переменную, в которой необходимо разместить результат - массив уже обработанных строк. 
В качестве возвращаемого значения функция должна возвращать количество строк, содержащихся в результирующем массиве. 

Программа должна уметь обрабатывать ошибки - такие как неверные входные данные(отсутствие входных строк) или ошибки выделения памяти и т.п. 
В случае возникновения ошибки нужно выводить об этом сообщение "[error]" и завершать выполнение программы. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_ERROR_PF {printf("%s","[error]"); return 0;}

int foo(char** str_arr, int str_kol, char** res);

int main()
{
    char** arr_of_str = NULL;
    char** result = NULL;

    char c;
    int str_counter = 0;
    int str_len_counter = 0;

    arr_of_str = (char**)malloc(sizeof(char**));
    result = (char**)malloc(sizeof(char*));

    arr_of_str[str_counter] = (char*)malloc(sizeof(char*));

    if(!arr_of_str || !arr_of_str[str_counter] || !result)
        STD_ERROR_PF

    // Формирование массива строк

    while ((c = getchar()) != EOF)
    {
        if (c != '\n')
        {
            str_len_counter++;
            arr_of_str[str_counter] = (char*)realloc(arr_of_str[str_counter], (str_len_counter+2)*sizeof(char));
            if (!arr_of_str[str_counter])
            {
                for (int i = 0; i < str_counter + 1; i++)
                    free (arr_of_str[i]);
                free (arr_of_str);
                STD_ERROR_PF
            }
            arr_of_str[str_counter][str_len_counter-1] = c;
            arr_of_str[str_counter][str_len_counter] = '\n';
            arr_of_str[str_counter][str_len_counter+1] = '\0';
        }
        else
        {
            if(strlen(arr_of_str[str_counter]) == 0)
                STD_ERROR_PF
            str_counter++;
            arr_of_str = (char**)realloc(arr_of_str, (str_counter+1)*sizeof(char*));
            arr_of_str[str_counter] = (char*)malloc(sizeof(char));
            if(!arr_of_str || !arr_of_str[str_counter])
            {
                for (int i = 0; i < str_counter + 1; i++)
                    free (arr_of_str[i]);
                free (arr_of_str);
                STD_ERROR_PF
            }
            str_len_counter = 0;
        }
    }

    if (str_len_counter == 0)
        STD_ERROR_PF

    str_counter++;

    foo(arr_of_str, str_counter, result);

    for (int i = 0; i < str_counter; i++)
    {
        free(arr_of_str[i]);
    }

    free(arr_of_str);

    return 0;
}

int foo(char** str_arr, int str_kol, char** res)
{
    res = (char**)realloc(res, (str_kol)*sizeof(char*));

    if (!res)
        STD_ERROR_PF

    int len;

    for (int i = 0; i < str_kol; i++)
    {
        len = strlen(str_arr[i]) + 2;
        res[i] = (char*)malloc(len*sizeof(char));
        if (!res[i])
            {
                for (int j = 0; j < i; j++)
                    free (res[j]);
                STD_ERROR_PF
            }
        strcpy(res[i], str_arr[i]);
    }

    int arr_size = 0;

    for (int i = 0; i < str_kol; i++)
    {
        for (int j = 0; j < strlen(res[i]); j++)
        {
            if (res[i][j] >= 'A' && res[i][j] <= 'Z')
                res[i][j] += 'a'-'A';
        }
        arr_size++;
    }

    for (int i = 0; i < str_kol; i++)
    {
        printf("%s", res[i]);
        free(res[i]);
    }

    free(res);

    return arr_size;
}
