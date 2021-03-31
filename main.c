#include <stdio.h>
#include <unistd.h>


int main(int argc, char * argv[]) {
/*
    for(int i=0;i<argc;i++){
        printf("%i: %s\n",i,argv[i]);
    }*/
    int c;
    int opa=0,opb=0,opc=0;
    char* cval=0;
    while((c = getopt(argc,argv,"abc:"))!=-1){
        switch (c) {
            case 'a':
                opa=1;
                break;
            case 'b':
                opb=2;
                break;
            case'c':
                opc=2;
                cval=optarg;
                break;


        }


    }
    printf("%i %i %i %s\n",opa,opb,opc,cval);
    return 0;
}
