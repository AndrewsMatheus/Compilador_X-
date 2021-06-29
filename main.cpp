#include "parser3v.h"

int main(int argc, char *argv[]){

    Parser* p= new Parser(argv[1]);

    p->run();

    delete p;
}