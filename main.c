#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <stdint.h>

typedef struct part{
    char id[9];
    char *name;
    size_t amount;
}part;

void help(int menu, int mod);
char *readline_();

part *input_(part *mas, size_t *n, int *flag);
part *treat(part *mas, size_t *n, int *flag);
part *timing_menu(part *mas, size_t n, int *flag);
int output(part *mas, size_t n);
part read_part(char *s);
char *freadline_(FILE *file);
void copy_part(part *dst, part *src);
void free_(part *mas, size_t *n);
int check_natural(const char *s);
part gen_part();
char gen_char();
part *sort_menu(part *mas, size_t n, int *flag);
void swap(part *one, part *two);
void quick_sort(void *base, size_t n, int (*compare) (const void *, const void *));
void pair_sort(void *base, size_t n, int (*compare) (const void *, const void *));
void radix_sort(void *base, size_t n, int (*compare) (const void *, const void *));
int compare_id(const void *a, const void *b);
int compare_name(const void *a, const void *b);
int compare_amount(const void *a, const void *b);


int main(){
    int *flag [3] = {0};
    srand(time(NULL));
    part *data = NULL;
    size_t n = 0;
    help(0, 0);
    while (1){
        char *input = readline_();
        if (input && (strlen(input) == 1)){
            switch (input[0]) {
                case '0':
                    free(input);
                    if(data)
                        free_(data, &n);
                    printf("Program end.\n");
                    return 0;
                case '1':
                    if (data)
                        help(0, 1);
                    else
                        help(0, 0);
                    free(input);
                    break;
                case '2':
                    data = input_(data, &n, (int *) flag);
                    free(input);
                    break;
                case '3':
                    output(data, n);
                    free(input);
                    break;
                case '4':
                    if (data)
                        data = treat(data, &n, (int *) flag);
                    else
                        help(0,-1);
                    free(input);
                    break;
                case '5':
                    if (data)
                        data = timing_menu(data, n, (int *) flag);
                    else
                        help(0,-1);
                    free(input);
                    break;
                default:
                    help(0, -1);
                    free(input);
            }
        } else{
            help(0, -1);
            free(input);
        }
    }
}

void help(int menu, int mod){
    switch (menu) {
        case 0:
            switch (mod) {
                case 0:
                    printf("0. Close program.\n"
                           "1. Help.\n"
                           "2. Input data.\n");
                    break;
                case 1:
                    printf("0. Close program.\n"
                           "1. Help.\n"
                           "2. Input data.\n"
                           "3. Output data\n"
                           "4. Manipulate with data.\n"
                           "5. Timing.\n");
                    break;
                default:
                    printf("Wrong command, try again. Enter \"1\" for help\n");
            }
            break;
        case 1:
            printf("0. Back.\n"
                   "1. Help.\n"
                   "2. Input from keyboard.\n"
                   "3. Input from file.\n"
                   "4. Random generate of input data.\n");
            break;
        case 2:
            printf("0. Back.\n"
                   "1. Help.\n"
                   "2. Index insert.\n"
                   "3. Insert to sort data.\n"
                   "4. Sort.\n");
            break;
        case 3:
            if(!mod)
                printf("0. Back.\n"
                       "1. Help.\n"
                       "2. Quick sort.\n"
                       "3. Pair insertion sort.\n"
                       "4. Radix sort.\n");
            else
                printf("0. id.\n"
                       "1. name.\n"
                       "2. amount.\n");
            break;
        case 4:
            printf("0. Back.\n"
                   "1. Help.\n"
                   "2. Output to console.\n"
                   "3. Output to file.\n");
            break;
        case 5:
            printf("0. Back.\n"
                   "1. Help.\n"
                   "2. Timing quick sort.\n"
                   "3. Timing pair insertion sort.\n"
                   "4. Timing radix sort.\n");
            break;
        default:
            printf("Wrong command, try again. Enter \"1\" for help\n");
    }
}

char *readline_() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

char *freadline_(FILE *file){
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(file, "%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}


part *input_(part *mas, size_t *n, int *flag){
    help(1, 0);
    while(1) {
        char *input = readline_();
        if (input && (strlen(input) == 1)) {
            switch (input[0]) {
                case '0':
                    if(mas)
                        help(0,1);
                    else
                        help(0, 0);
                    free(input);
                    return mas;
                case '1':
                    help(1,0);
                    free(input);
                    break;
                case '2':
                    free(input);
                    printf("Use Ctrl+D to stop input data.\n");
                    input = readline_();
                    while(input){
                        part temp;
                        temp = read_part(input);
                        if(temp.name) {
                            *n += 1;
                            mas = realloc(mas, (*n) * sizeof(part));
                            copy_part(mas + (*n - 1), &temp);
                        } else
                            printf("Try again.\n");
                        free(input);
                        free(temp.name);
                        input = readline_();
                    }
                    help(0, 1);
                    flag[0] = 0;
                    flag[1] = 0;
                    flag[2] = 0;
                    return mas;
                case '3':
                    free(input);
                    printf("Enter path to file:\n");
                    input = readline_();
                    FILE *file = fopen(input, "r");
                    free(input);
                    if(file){
                        input = freadline_(file);
                        while (input){
                            part temp;
                            temp = read_part(input);
                            if(temp.name) {
                                *n += 1;
                                mas = realloc(mas, (*n) * sizeof(part));
                                copy_part(mas + (*n - 1), &temp);
                                free(temp.name);
                            } else{
                                free(input);
                                free_(mas, n);
                                mas = NULL;
                                break;
                            }
                            free(input);
                            input = freadline_(file);
                        }
                        if (!mas){
                            //free(input);
                            flag[0] = 0;
                            flag[1] = 0;
                            flag[2] = 0;
                        }
                        fclose(file);
                        help(0, 1);
                        return mas;
                    } else{
                        printf("File can't open.\n");
                        help(1, 0);
                        break;
                    }
                case '4':
                    free(input);
                    printf("Enter amount of elements data:\n");
                    input = readline_();
                    size_t n_temp = check_natural(input);
                    free(input);
                    if(n_temp){
                        free_(mas, n);
                        *n = n_temp;
                        mas = calloc(*n, sizeof(part));
                        for(int i = 0; i < *n; i++)
                            mas[i] = gen_part();
                        flag[0] = 0;
                        flag[1] = 0;
                        flag[2] = 0;
                    } else{
                        printf("Wrong format of argument \"amount of elements data\".\n");
                    }
                    help(0, 1);
                    return mas;
                default:
                    help(-1, -1);
                    free(input);
            }
        } else {
            help(-1, -1);
            free(input);
        }
    }
}

part gen_part(){
    part temp;
    for(int i = 0; i < 8; i++)
        temp.id[i] = gen_char();
    temp.id[8] = '\0';
    int n = rand() % 100 + 1;
    temp.name = calloc(n + 1, sizeof(char));
    for(int i = 0; i < n; i++)
        temp.name[i] = gen_char();
    temp.amount = rand() % 10000000 + 1;
    return temp;
}

char gen_char(){
    return (char) (rand() % 2 ? rand() % 26 + 97 : rand() % 26 + 65);
}

part *treat(part *mas, size_t *n, int *flag){
    help(2, 0);
    while(1) {
        char *input = readline_();
        if (input && (strlen(input) == 1)) {
            switch (input[0]) {
                case '0':
                    help(0,1);
                    free(input);
                    return mas;
                case '1':
                    help(2,0);
                    free(input);
                    break;
                case '2':
                    free(input);
                    printf("Enter index to insert:\n");
                    input = readline_();
                    int index = check_natural(input);
                    free(input);
                    if ((0 <= index) && (index <= (*n + 1))) {
                        printf("Enter new element:\n");
                        input = readline_();
                        part temp = read_part(input);
                        free(input);
                        if(temp.name){
                            mas = realloc(mas, (*n + 1) * sizeof(part));
                            for (size_t i = *n; i > index; i--){
                                copy_part(mas + i, mas + (i - 1));
                                free(mas[i-1].name);
                            }
                            copy_part(mas + index, &temp);
                            *n += 1;
                            flag[0] = 0;
                            flag[1] = 0;
                            flag[2] = 0;
                            free(temp.name);
                            printf("Element inserted.\n");
                            break;
                        } else {
                            help(2, 0);
                            break;
                        }
                    } else {
                        printf("Wrong index.\n");
                        help(2, 0);
                        break;
                    }
                case '3':
                    printf("Don't available now.\n");
                    //printf("Enter new element.\n");
                    //reading part
                    //insert element
                    break;
                case '4':
                    mas = sort_menu(mas, *n, flag);
                    free(input);
                    break;
                default:
                    help(-1, -1);
                    free(input);
            }
        } else {
            help(-1, -1);
            free(input);
        }
    }
}

void free_(part *mas, size_t *n){
    for(int i = 0; i < *n; i++){
        free(mas[i].name);
    }
    free(mas);
    *n = 0;
}

part *sort_menu(part *mas, size_t n, int *flag){
    help(3, 0);
    while(1) {
        char *input = readline_();
        if (input && (strlen(input) == 1)) {
            switch (input[0]) {
                case '0':
                    help(2,0);
                    free(input);
                    return mas;
                case '1':
                    help(3,0);
                    free(input);
                    break;
                case '2':
                    free(input);
                    printf("Choose field to sort.\n");
                    help(3, 1);
                    input = readline_();
                    if (input && (strlen(input) == 1)) {
                        switch (input[0]) {
                            case '0':
                                quick_sort(mas, n, compare_id);
                                printf("Sorted by \"id\" field.\n");
                                flag[0] = 1;
                                flag[1] = 0;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '1':
                                quick_sort(mas, n, compare_name);
                                printf("Sorted by \"name\" field.\n");
                                flag[0] = 0;
                                flag[1] = 1;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '2':
                                quick_sort(mas, n, compare_amount);
                                printf("Sorted by \"amount\" field.\n");
                                flag[0] = 0;
                                flag[1] = 0;
                                flag[2] = 1;
                                free(input);
                                help(3, 0);
                                break;
                            default:
                                help(-1, -1);
                                free(input);
                        }
                    } else{
                        help(-1, -1);
                        free(input);
                    }
                    break;
                case '3':
                    free(input);
                    printf("Choose field to sort.\n");
                    help(3, 1);
                    input = readline_();
                    if (input && (strlen(input) == 1)) {
                        switch (input[0]) {
                            case '0':
                                pair_sort(mas, n, compare_id);
                                printf("Sorted by \"id\" field.\n");
                                flag[0] = 1;
                                flag[1] = 0;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '1':
                                pair_sort(mas, n, compare_name);
                                printf("Sorted by \"name\" field.\n");
                                flag[0] = 0;
                                flag[1] = 1;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '2':
                                pair_sort(mas, n, compare_amount);
                                printf("Sorted by \"amount\" field.\n");
                                flag[0] = 0;
                                flag[1] = 0;
                                flag[2] = 1;
                                free(input);
                                help(3, 0);
                                break;
                            default:
                                help(-1, -1);
                                free(input);
                        }
                    } else{
                        help(-1, -1);
                        free(input);
                    }
                    break;
                case '4':
                    free(input);
                    printf("Choose field to sort.\n");
                    help(3, 1);
                    input = readline_();
                    if (input && (strlen(input) == 1)) {
                        switch (input[0]) {
                            case '0':
                                radix_sort(mas, n, compare_id);
                                printf("Sorted by \"id\" field.\n");
                                flag[0] = 1;
                                flag[1] = 0;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '1':
                                radix_sort(mas, n, compare_name);
                                printf("Sorted by \"name\" field.\n");
                                flag[0] = 0;
                                flag[1] = 1;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '2':
                                radix_sort(mas, n, compare_amount);
                                printf("Sorted by \"amount\" field.\n");
                                flag[0] = 0;
                                flag[1] = 0;
                                flag[2] = 1;
                                free(input);
                                help(3, 0);
                                break;
                            default:
                                help(-1, -1);
                                free(input);
                        }
                    } else{
                        help(-1, -1);
                        free(input);
                    }
                    break;
                default:
                    help(-1, -1);
                    free(input);
            }
        } else{
            help(-1, -1);
            free(input);
        }
    }
}

int check_natural(const char *s){
    int ans = 0;
    if(*s == '0')
        return 0;
    while(*s){
        if(*s >= 48 && *s <= 57){
            ans = ans * 10 + ((int) *s - 48);
            s += 1;
        } else {
            return 0;
        }
    }
    return ans;
}

part read_part(char *s){
    char *id = strtok(s, " \t");
    char *name = strtok(NULL, " \t");
    char *amount = strtok(NULL, " \t");
    char *next = strtok(NULL, " \t");
    size_t amount_i;
    part temp;

    if (id && name && amount && !next){
        if(strlen(id) == 8){
            amount_i = check_natural(amount);
            if(!amount_i){
                temp.name = NULL;
                printf("Wrong format of argument \"amount\".\n");
                return temp;
            }
            size_t i = 0;
            while(name[i]){
                if((name[i] >= 91 || name[i] <= 64) && (name[i] >= 123 || name[i] <= 96)){
                    temp.name = NULL;
                    printf("Wrong format of argument \"name\".\n");
                    return temp;
                }
                i += 1;
            }
            for(i = 0; i < 8; i++){
                if((*id >= 91 || *id <= 64) && (*id >= 123 || *id <= 96)){
                    temp.name = NULL;
                    printf("Wrong format of argument \"id\".\n");
                    return temp;
                }
                temp.id[i] = id[i];
            }
            temp.id[8] = '\0';
            size_t len = strlen(name);
            temp.name = calloc(len + 1, sizeof(char));
            memmove(temp.name, name, len*sizeof(char));
            temp.name[len] = '\0';
            temp.amount = amount_i;
            return temp;
        } else {
            temp.name = NULL;
            printf("Wrong length of id.\n");
            return temp;
        }
    } else {
        temp.name = NULL;
        printf("Wrong amount of arguments for one part.\n");
        return temp;
    }
}

void copy_part(part *dst, part *src){
    for(int i = 0; i < 8; i++)
        (*dst).id[i] = (*src).id[i];
    (*dst).id[8] = '\0';
    size_t len = strlen((*src).name);
    (*dst).name = calloc(len + 1, sizeof(char));
    memmove((*dst).name, (*src).name, len*sizeof(char));
    (*dst).name[len] = '\0';
    (*dst).amount = (*src).amount;
}

part *timing_menu(part *mas, size_t n, int *flag){
    help(5, 0);
    clock_t start, end;
    while(1) {
        char *input = readline_();
        if (input && (strlen(input) == 1)) {
            switch (input[0]) {
                case '0':
                    help(2,0);
                    free(input);
                    return mas;
                case '1':
                    help(5,0);
                    free(input);
                    break;
                case '2':
                    free(input);
                    printf("Choose field to sort.\n");
                    help(3, 1);
                    input = readline_();
                    if (input && (strlen(input) == 1)) {
                        switch (input[0]) {
                            case '0':
                                start = clock();
                                quick_sort(mas, n, compare_id);
                                end = clock();
                                printf("Sorted by \"id\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 1;
                                flag[1] = 0;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '1':
                                start = clock();
                                quick_sort(mas, n, compare_name);
                                end = clock();
                                printf("Sorted by \"name\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 0;
                                flag[1] = 1;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '2':
                                start = clock();
                                quick_sort(mas, n, compare_amount);
                                end = clock();
                                printf("Sorted by \"amount\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 0;
                                flag[1] = 0;
                                flag[2] = 1;
                                free(input);
                                help(3, 0);
                                break;
                            default:
                                help(-1, -1);
                                free(input);
                        }
                    } else{
                        help(-1, -1);
                        free(input);
                    }
                    break;
                case '3':
                    free(input);
                    printf("Choose field to sort.\n");
                    help(3, 1);
                    input = readline_();
                    if (input && (strlen(input) == 1)) {
                        switch (input[0]) {
                            case '0':
                                start = clock();
                                pair_sort(mas, n, compare_id);
                                end = clock();
                                printf("Sorted by \"id\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 1;
                                flag[1] = 0;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '1':
                                start = clock();
                                pair_sort(mas, n, compare_name);
                                end = clock();
                                printf("Sorted by \"name\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 0;
                                flag[1] = 1;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '2':
                                start = clock();
                                pair_sort(mas, n, compare_amount);
                                end = clock();
                                printf("Sorted by \"amount\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 0;
                                flag[1] = 0;
                                flag[2] = 1;
                                free(input);
                                help(3, 0);
                                break;
                            default:
                                help(-1, -1);
                                free(input);
                        }
                    } else{
                        help(-1, -1);
                        free(input);
                    }
                    break;
                case '4':
                    free(input);
                    printf("Choose field to sort.\n");
                    help(3, 1);
                    input = readline_();
                    if (input && (strlen(input) == 1)) {
                        switch (input[0]) {
                            case '0':
                                start = clock();
                                radix_sort(mas, n, compare_id);
                                end = clock();
                                printf("Sorted by \"id\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 1;
                                flag[1] = 0;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '1':
                                start = clock();
                                radix_sort(mas, n, compare_name);
                                end = clock();
                                printf("Sorted by \"name\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 0;
                                flag[1] = 1;
                                flag[2] = 0;
                                free(input);
                                help(3, 0);
                                break;
                            case '2':
                                start = clock();
                                radix_sort(mas, n, compare_amount);
                                end = clock();
                                printf("Sorted by \"amount\" field, %d time spent in sec.\n", (int) ((end - start) / CLOCKS_PER_SEC));
                                flag[0] = 0;
                                flag[1] = 0;
                                flag[2] = 1;
                                free(input);
                                help(3, 0);
                                break;
                            default:
                                help(-1, -1);
                                free(input);
                        }
                    } else{
                        help(-1, -1);
                        free(input);
                    }
                    break;
                default:
                    help(-1, -1);
                    free(input);
            }
        } else{
            help(-1, -1);
            free(input);
        }
    }
}

int output(part *mas, size_t n){
    help(4, 0);
    while(1) {
        char *input = readline_();
        if (input && (strlen(input) == 1)) {
            switch (input[0]) {
                case '0':
                    help(0,1);
                    free(input);
                    return 0;
                case '1':
                    help(4,0);
                    free(input);
                    break;
                case '2':
                    for (int i = 0; i < n; i++)
                        printf("id: %s, name: %s, amount: %d.\n", mas[i].id, mas[i].name, (int) mas[i].amount);
                    free(input);
                    help(4, 0);
                    break;
                case '3':
                    free(input);
                    printf("Enter path to file:\n");
                    input = readline_();
                    FILE *file = fopen(input, "w");
                    free(input);
                    if(file){
                        for (int i = 0; i < n; i++)
                            fprintf(file, "%s %s %d\n", mas[i].id, mas[i].name, (int) mas[i].amount);
                        fclose(file);
                        help(4, 0);
                    } else{
                        printf("File can't open or make.\n");
                        help(4, 0);
                    }
                    break;
                default:
                    help(-1, -1);
                    free(input);
            }
        } else {
            help(-1, -1);
            free(input);
        }
    }
}

void swap(part *one, part *two){
    part temp;

    if((*one).name)
        copy_part(&temp, one);

    free((*one).name);
    (*one).name = NULL;

    if((*two).name)
        copy_part(one, two);

    free((*two).name);
    copy_part(two, &temp);
    free(temp.name);
}

void qs(part *items, size_t left, size_t right, int (*compare) (const void *, const void *)){
    int64_t i, j;
    part x;

    i = (int64_t) left;
    j = (int64_t) right;
    copy_part(&x, &items[(left + right) / 2]);

    do{
        while((i < (int64_t) right) && (compare(&items[i], &x) < 0))
            i++;

        while((j > (int64_t) left) && (compare(&x, &items[j]) < 0))
            j--;

        if (i <= j){
            swap(&items[i], &items[j]);
            i++;
            j--;
        }
    } while(i <= j);

    if((int64_t) left < j)
        qs(items, left, j, compare);

    if(i < right)
        qs(items, i, right, compare);

    free(x.name);
}

void quick_sort(void *base, size_t n, int (*compare) (const void *, const void *)){
    qs((part *) base, 0, n - 1, compare);
}

void pair_sort(void *base, size_t n, int (*compare) (const void *, const void *)){
    for(size_t i = 1; i < n; i = i + 2){
        part max_, min_;
        int64_t j;

        if(compare(((part *) base) + (i - 1), ((part *) base) + i) < 0){
            copy_part(&max_,((part *) base) + i);
            copy_part(&min_, ((part *) base) + (i - 1));
        } else {
            copy_part(&min_,((part *) base) + i);
            copy_part(&max_, ((part *) base) + (i - 1));
        }

        j = i - 2;

        while((j >= 0) && (compare(&max_,((part *) base) + j) < 0)){
            free((*((part *) base + (j + 2))).name);
            copy_part(((part *) base + (j + 2)), ((part *) base) + j);
            j--;
        }

        j++;
        free((*(((part *) base) + (j + 1))).name);
        copy_part(((part *) base) + (j + 1), &max_);

        while((j >= 0) && (compare(&min_,((part *) base) + j) < 0)){
            free((*((part *) base + (j + 1))).name);
            copy_part(((part *) base + (j + 1)), ((part *) base) + j);
            j--;
        }

        free((*(((part *) base) + (j + 1))).name);
        copy_part(((part *) base) + (j + 1), &min_);
    }

    part last;
    int64_t i = n - 2;

    copy_part(&last, ((part *) base) + (n - 1));

    while((i >= 0) && (compare(&last,((part *) base) + i) < 0)){
        free((*((part *) base + (i + 1))).name);
        copy_part(((part *) base + (i + 1)), ((part *) base) + i);
        i--;
    }
}

void radix_sort(void *base, size_t n, int (*compare) (const void *, const void *)){
    printf("Not available.\n");
}

int compare_id(const void *a, const void *b){
    return strcmp((*(part *) a).id, (*(part *) b).id);
}

int compare_name(const void *a, const void *b){
    return strcmp((*(part *) a).name, (*(part *) b).name);
}

int compare_amount(const void *a, const void *b){
    if ((*(part *) a).amount < (*(part *) b).amount)
        return -1;
    else if ((*(part *) a).amount > (*(part *) b).amount)
        return 1;
    else
        return 0;
}