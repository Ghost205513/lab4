#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

typedef struct part{
    char id[9];
    char *name;
    size_t amount;
}part;

void help(int menu, int mod);
char *readline_();

part *input_(part *mas, size_t *n);
part *str_treat(char *str);
part *treat(part *mas, size_t *n);
part *timing(part *mas, size_t n);
void output(part *mas, size_t n);
part read_part(char *s);
char *freadline_(FILE *file);
void copy_part(part *dst, part *src);
void free_(part *mas, size_t *n);
int check_natural(char *s);
part gen_part();
char gen_char();


int main(){
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
                    data = input_(data, &n);
                    for (int i = 0; i < n; i++){
                        printf("id: %s, name: %s, amount: %d.\n", data[i].id, data[i].name, (int) data[i].amount);
                    }
                    free(input);
                    break;
                case '3':
                    output(data, n);
                    free(input);
                    break;
                case '4':
                    if (data)
                        data = treat(data, &n);
                    else
                        help(0,-1);
                    free(input);
                    break;
                case '5':
                    if (data)
                        data = timing(data, n);
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
            printf("0. Back.\n"
                   "1. Help.\n"
                   "2. Quick sort.\n"
                   "3. Pair insertion sort.\n"
                   "4. Radix sort.\n");
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


part *input_(part *mas, size_t *n){
    help(1, 0);
    char *str;
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
                    printf("Use Ctrl+D to stop input data.\n");
                    str = readline_();
                    while(str){
                        part temp;
                        temp = read_part(str);
                        if(temp.name) {
                            *n += 1;
                            mas = realloc(mas, (*n) * sizeof(part));
                            copy_part(mas + (*n - 1), &temp);
                        } else
                            printf("Try again.\n");
                        free(str);
                        free(temp.name);
                        str = readline_();
                    }
                    free(input);
                    help(0, 1);
                    return mas;
                case '3':
                    printf("Enter path to file:\n");
                    str = readline_();
                    FILE *file = fopen(str, "r");
                    free(str);
                    if(file){
                        str = freadline_(file);
                        while (str){
                            part temp;
                            temp = read_part(str);
                            if(temp.name) {
                                *n += 1;
                                mas = realloc(mas, (*n) * sizeof(part));
                                copy_part(mas + (*n - 1), &temp);
                                free(temp.name);
                            } else{
                                free(str);
                                free_(mas, n);
                                mas = NULL;
                                break;
                            }
                            free(str);
                            str = freadline_(file);
                        }
                        if (mas)
                            free(str);
                        free(input);
                        fclose(file);
                        help(0, 1);
                        return mas;
                    } else{
                        printf("File can't open.\n");
                        help(1, 0);
                        free(input);
                        break;
                    }
                case '4':
                    printf("Enter amount of elements data.\n");
                    str = readline_();
                    *n = check_natural(str);
                    if(*n){
                        mas = calloc(*n, sizeof(part));
                        for(int i = 0; i < *n; i++)
                            mas[i] = gen_part();
                    } else{
                        printf("Wrong format of argument \"amount of elements data\".\n");
                    }
                    free(input);
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

part *treat(part *mas, size_t *n){
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
                    printf("Enter index to insert:\n");
                    size_t index;
                    scanf("%d\n", &index);
                    if (0 < index && (index <= *n + 1)) {
                        mas = realloc(mas, (*n + 1) * sizeof(part));
                        for (size_t i = *n; i > index; i--)
                            mas[i] = mas[i - 1];
                        printf("Enter new element:\n");
                        //insert part
                        *n += 1;
                    }
                    free(input);
                    return mas;
                case '3':
                    printf("Enter new element.\n");
                    //reading part
                    //insert element
                    free(input);
                    return mas;
                case '4':

                    //random generation of data
                    free(input);
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

void free_(part *mas, size_t *n){
    for(int i = 0; i < *n; i++){
        free(mas[i].name);
    }
    free(mas);
    *n = 0;
}

part *sort_menu(part *mas, size_t n){
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
                    //start quick sort
                    free(input);
                    return mas;
                case '3':
                    //start pair insertion sort
                    free(input);
                    return mas;
                case '4':
                    //radix sort
                    free(input);
                    return mas;
                default:
                    help(1, -1);
                    free(input);
            }
        } else{
            help(-1, -1);
            free(input);
        }
    }
}

int check_natural(char *s){
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
    size_t amount_i = 0;
    part temp;

    if (id && name && amount && !next){
        if(strlen(id) == 8){
            if(*amount == '0'){
                temp.name = NULL;
                printf("Wrong format of argument \"amount\".\n");
                return temp;
            }
            while(*amount){
                if(*amount >= 48 && *amount <= 57){
                    amount_i = amount_i * 10 + ((int) *amount - 48);
                    amount += 1;
                } else {
                    temp.name = NULL;
                    printf("Wrong format of argument \"amount\".\n");
                    return temp;
                }
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
    for(int i = 0; i < 9; i++){
        (*dst).id[i] = (*src).id[i];
    }
    size_t len = strlen((*src).name);
    (*dst).name = calloc(len + 1, sizeof(char));
    memmove((*dst).name, (*src).name, len*sizeof(char));
    (*dst).name[len] = '\0';
    (*dst).amount = (*src).amount;
}

part *timing(part *mas, size_t n){
    return &mas[0];
}
void output(part *mas, size_t n){

}
//read_part - checked
//readline_ - checked