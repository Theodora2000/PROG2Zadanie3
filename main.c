#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
            line[i]=" ";
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
        }

        i++;
    }
    newLine[j]='\0';
}

void LowerToUpper(char *line){

    int i=0;
    while (line[i]) {
        if (islower(line[i])) {

            line[i] = toupper(line[i]);
            i++;
        } else {

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

            continue;
        }
    }

}

void ParamR(char *line, char *rvalue, int optind, int argc, char * argv){
    if(optind < argc){
        for(int i=optind;i<argc;i++){
            while(line[i]!=0){
                if(line[i]==argv[i]){
                    line[i]=rvalue;
                    i++;
                }
                else{
                    i++;
                    continue;
                }
            }

        }
    }

}

void NonR(char *line,int optind, int argc, char * argv){
    if(optind < argc){
        for(int i=optind;i<argc;i++){
            while(line[i]!=0){
                if(line[i]==argv[i]){
                    line[i]='*';
                    i++;
                }
                else{
                    i++;
                    continue;
                }
            }

        }
    }

}

int main(int argc, char * argv[]) {

    int opt;
    char* optstring = ":aculr:";
    char *rvalue = NULL;


    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'a':

                printf("Prepinac -a\n");
                break;
            case 'r':
                rvalue=optarg;

                printf("Prepinac -r a jeho povinny parameter %s\n",rvalue);
                break;
            case 'c':
                printf("Prepinac -c\n");
                break;
            case 'u':
                printf("Prepinac -u\n");
                break;
            case 'l':
                printf("Prepinac -l\n");
                break;

            case '?':
                if(optopt=='r'){
                    printf("Prepinac -r vyzaduje povinny parameter\n");
                    return 2;
                }else if(isprint(optopt)){
                    printf("Neplatny prepinac -%c", optopt);
                    return 1;
                }

        }
    }
    if(optind < argc){
        for(int i=optind;i<argc;i++){
            printf("Non-option CMD argument: %s\n",argv[i]);
        }
    }
/*
    char *line = NULL;


    // Nacitavaci cyklus bezi pokial nedojde
    // ku chybe alebo natrafeniu na EOF.
    // Pozn. Na ukoncenie citania riadkov si viete
    // napisat aj vlastnu podmienku.
    while ((line = readline()) != NULL ) {
        // Pozn. vrateny retazec 'line'
        // je ukonceny znakom '\n'.

        //printf("%s",line); // vypis retazca
        if((line = readline())=='\n'){
            printf("%s",line);
            break;
        }
        free(line); // uvolnenie pamate
    }
*/

    return 0;
}
