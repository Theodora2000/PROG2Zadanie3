#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char *readline() {
    const size_t BSIZE = 100;
    char *line = NULL;
    size_t capacity = 0;

    do {
        // Priprav dostatok pamate.
        capacity += BSIZE;

        // Alokuj miesto na capacity + '\0'.
        line = (char *) realloc(line, (capacity + 1) * sizeof(char));
        if (line == NULL)
            return line;

        // Nacitaj zo vstupu riadok (resp. jeho zvysok).
        if (fgets(line + capacity - BSIZE, BSIZE + 1, stdin) == NULL) {
            free(line);
            return NULL; // doslo k chybe citania alebo sme narazili na EOF
        }
        // Opakuj, pokym sa nenacita cely riadok.
        // Indikacia, ze zostal zvysok riadku:
        //   1. je naplnena cela BSIZE
        //   2. na konci nie je '\n'
    } while (strlen(line + capacity - BSIZE) >= BSIZE
             && line[capacity - 1] != '\n');
    // nacitany riadok obsahuje na konci znak '\n'
    return line;
}

//0             48      57          65          91          97          123
//'\0'          '0'     '9'         'A'         'Z'         'a'          'z'

void RemoveNonLetters(char* line)
{
    int i=0;
    while(line[i]!=0)
    {
        if(!isalpha(line[i]))
        {
            line[i]=' ';
            i++;
        }
        else{
            i++;
            continue;
        }

    }
}

void CompresionText(char *line,char* newLine)
{
    int i=0;
    int j=0;

    while(line[i]!=0)
    {
        if(isalpha(line[i]))
        {
            newLine[j]=line[i];
            j++;
            i++;
        }else{
            i++;
            continue;
        }


    }
    newLine[j]='\0';
    int k;
    for( k=0; k< newLine[k]!='\0'; k++)
    {
        line[k]=newLine[k];
    }
    line[k]='\0';

}

void LowerToUpper(char *line){

    int i=0;
    while (line[i]) {
        if (islower(line[i])) {

            line[i] = toupper(line[i]);
            i++;
        } else {
            i++;
            continue;
        }
    }
}


void UpperToLower(char *line){
    int i=0;
    while (line[i]) {
        if (isupper(line[i])) {

            line[i] = tolower(line[i]);
            i++;
        } else {
            i++;
            continue;
        }
    }

}

void findSubStringMutli(char line[],char substring[], char* param){


    while(1>0)
    {
        char* start=strstr(line,substring);
        int position = start-line;
        printf("%d\n", position);
        if(start==NULL)
        {
            return;
        }

        int i=0;
        int size=strlen(substring);
        int size_line = strlen(line);
        int size_param =  strlen(param);
        int diff = size_param-size;
        if(size<size_param){

            line = (char *)realloc(line, strlen(line)+(diff-1));
        }

        for(int i=size_line-1;i>=position;i--){
            line[i+(diff-1)] = line[i];
        }

        while(i<size_param)
        {
            start[i]=substring[i];
            i++;

        }
    }
}

void findSubString(char line[],char substring[])
{

    while(1>0)
    {
        char* start=strstr(line,substring);
        if(start==NULL)
        {
            return;
        }
        int i=0;
        int size=strlen(substring);
        while(i<size)
        {
            start[i]='*';
            i++;

        }
    }
}

int main(int argc, char * argv[]) {

    int opt;
    char* optstring = "aculr:";
    char *rvalue = NULL;

    char *line = NULL;
    char newLine[10000];
    int parametre[8];
    char string[100];
    int str =0;
    int param=0;

    int boloU=0;
    int boloL=0;


    while ((opt = getopt(argc, argv, optstring)) != -1) {

        switch (opt) {
            case 'a':
                parametre[param]=1;
                param++;
                //printf("Prepinac -a\n");
                //RemoveNonLetters(line);
                break;
            case 'r':
                parametre[param]=5;
                param++;
                rvalue = optarg;

                //printf("Prepinac -r a jeho povinny parameter %s\n",rvalue);
/*
                if(optind < argc){
                    for(int i=optind;i<argc;i++){
                        findSubStringMutli(line,argv[i], rvalue );
                    }

                }*/
                break;
            case 'c':
                parametre[param]=2;
                param++;
                //printf("Prepinac -c\n");

                //CompresionText(line, newLine);
                break;
            case 'u':

                boloU=1;
                if(boloL==1){
                    return 3;
                }
                parametre[param]=3;
                param++;
                //printf("Prepinac -u\n");
                //LowerToUpper(line);
                break;
            case 'l':
                boloL=1;
                if(boloU==1){
                    return 3;
                }
                parametre[param]=4;
                param++;
                //printf("Prepinac -l\n");
                //UpperToLower(line);
                break;

            case '?':
                if(optopt=='r'){
                    //printf("Prepinac -r vyzaduje povinny parameter\n");
                    return 2;
                }else if(isprint(optopt)){
                    //printf("Neplatny prepinac -%c", optopt);
                    return 1;
                }

        }

    }

    if(optind < argc){
        for(int i=optind;i<argc;i++){
            //printf("%s ", argv[i]);
            //string[str]=argv[i];
            strcpy(string[str], argv[i]);
            str++;

        }

    }
    str = strlen(string);
    for(int i=0;i<str;i++){
        printf("%s\n", string[str]);
    }

    line = readline();
    int p = 0;
    if(line[p]=='\n'){
        //printf("Zadal iba novy riadok");
        free(line);
        return 0;
    }
    int i=0;
    while(i<param){
        switch (parametre[i]) {
            case 1:
                RemoveNonLetters(line);
                i++;
                break;
            case 2:
                CompresionText(line, newLine);
                i++;
                break;
            case 3:
                LowerToUpper(line);
                i++;
                break;
            case 4:
                UpperToLower(line);
                i++;
                break;
            case 5:
                if(optind < argc){
                    for(int i=optind;i<argc;i++){
                        findSubStringMutli(line,argv[i], rvalue );
                    }
                }
                i++;
                break;
            default:
                for(int i=0;i<str;i++){
                        findSubString(line, string[i]);
                    }

                i++;
                break;
        }
    }




    printf("%s", line);
    free(line);

    return 0;
}
