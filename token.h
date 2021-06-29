#include <iostream>
#include <ctype.h>
#include <string>

using namespace std;

enum Names{

    UNDEF,//0
    ID,//1
    OP,//2
    EQUAL,//3
    DEQ,//4
    NE,//5
    GT,//6
    GE,//7
    LT,//8
    LE,//9
    MULT,//10
    DIV,//11
    PLUS,//12
    MINUS,//13
    MOD,//14
    L_PAREN,//15
    R_PAREN,//16
    L_BRACKETS,//17
    R_BRACKETS,//18
    L_BRACES,//19
    R_BRACES,//20
    COMMA,//21
    SEMICOL,//22
    DOT,//23
    INTEGER_LITERAL,//24
    STRING_LITERAL,//25
    END_OF_FILE,//26
    NUMBER,//27
    RELOP, //28
    CLASS, //29
    EXTENDS,//30
    CONSTRUCTOR,//31
    PRINT,//32
    READ,//33
    RETURN,//34
    SUPER,//35
    IF,//36
    ELSE,//37
    FOR,//38
    BREAK,//39
    NEW,//40
    SEP,//41
    NOTYPE
};
class Token{

    public:
        int name;
        int attribute;
        string lexeme;
        int type;

        Token(int name){

            this->name= name;
            attribute = UNDEF;
        }
        Token(int name, int attr){

            this->name = name;
            attribute = attr;
        }
};