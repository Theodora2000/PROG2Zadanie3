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


int main(int argc, char * argv[]) {

    int opt;
    char* optstring = "aculr:";
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


    return 0;
}
