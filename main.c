
#include"functions.h"

int main(int argc, char *argv[]){
    char* filepath=argv[1];
    treatJson(filepath,"new.svg");
    return 0;
}
