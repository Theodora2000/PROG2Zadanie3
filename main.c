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
        char* start=strstr(line,param);//pocetka
        if(start==NULL)
        {
            return;
        }
        int position = start-line;
        int positionStart=start-line;
        position=position+strlen(param);


        int i=0;
        int size=strlen(substring);//velina string koji se menja umesto non-option
        int size_line = strlen(line);//velicina linije
        int size_param =  strlen(param);//velicina non-option
        int diff = 0;
        if(strcmp(param, substring)==0){
            return;
        }
        if(size_param>=size){
            diff = size_param-size;
            //smanji memoriju
            int j=0;
            while(j<size)
            {
                start[j]=substring[j];
                j++;
            }
            for(j=position; j<size_line; j++)
            {
                line[j-diff]=line[j];
            }
            line = (char *)realloc(line, strlen(line)-diff);
            line[size_line-diff]='\0';




        }else{
            diff = size-size_param;
            line = (char *)realloc(line, strlen(line)+diff);
            line[size_line+diff]='\0';
            for(int i=size_line-1;i>=position;i--){
                line[i+(diff)] = line[i];
            }
            int i=0;
            int posEnd=strlen(substring);
            while(i<posEnd)
            {
                start[i]=substring[i];
                i++;

            }
            //povecaj memoriju
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
    char* optstring = ":aculr:";
    char *rvalue = NULL;

    char *line = NULL;
    char newLine[10000];
    int parametre[8];
    int param=0;

    int boloU=0;
    int boloL=0;
    int boloR=0;


    while ((opt = getopt(argc, argv, optstring)) != -1) {

        switch (opt) {
            case 'a':
                parametre[param]=1;
                param++;
                break;
            case 'r':
                parametre[param]=5;
                param++;
                rvalue = optarg;
                boloR=1;
                break;
            case 'c':
                parametre[param]=2;
                param++;
                break;
            case 'u':

                boloU=1;
                if(boloL==1){
                    return 3;
                }
                parametre[param]=3;
                param++;
                break;
            case 'l':
                boloL=1;
                if(boloU==1){
                    return 3;
                }
                parametre[param]=4;
                param++;
                break;
            case ':':
                return 2;

            case '?':
                if(isprint(optopt)){
                    return 1;
                }

        }

    }

    if(optind < argc){
        for(int i=optind;i<argc;i++){
            if(boloR){
                break;
            }else {
                parametre[param] = 6;
                param++;
                break;
            }
        }

    }
/*
for(int i=0;i<param;i++){
    printf("%d\n", parametre[i]);
}*/
    for (int i = 0; i < param; i++) {
        for (int j = i+1; j < param; j++) {
            if(parametre[i] > parametre[j]) {
                int temp = parametre[i];
                parametre[i] = parametre[j];
                parametre[j] = temp;
            }
        }
    }
    line = readline();
    int p = 0;
    if(line[p]=='\n'){
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
                        findSubStringMutli(line, rvalue,argv[i]);
                    }
                }
                i++;
                break;
            case 6:
                if(optind < argc){
                    for(int i=optind;i<argc;i++){
                        findSubString(line, argv[i]);

                    }

                }

                i++;
                break;
        }
    }

    printf("%s", line);
    free(line);

    return 0;
}
