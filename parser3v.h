#include "scanner.h"

class Parser{

    private:

        Scanner* scanner;
        Token* lToken;
        SymbolTable* globalST;
        SymbolTable* currentST;
        bool hasError= false;

        void advance();
        void match(int);
        void errorSemantic();
        void errorSyntatic();
        void initSymbolTable();
        void returnST();
        void showLine();


        void program();
        void classList();
        void classList_Linha();
        void classDecl();
        void classBody();
        void varDeclListOpt();
        void VarDeclList_Linha();
        void varDecl();
        void varDeclOpt();
        void type();
        void constructDeclListOpt();
        void ConstructDeclList_Linha();
        void constructDecl();
        void methodDeclListOpt();
        void methodDeclList_Linha();
        void methodDecl();
        void methodBody();
        void paramListOpt();
        void paramList();
        void paramList_Linha();
        void param();
        void statementsOpt();
        void statements_Linha();
        void statement();
        void atribStat();
        void atribStat_Linha();
        void printStat();
        void readStat();
        void returnStat();
        void superStat();
        void ifStat();
        void ifStat_Linha();
        void forStat();
        void atribStatOpt();
        void atribStatOpt_Linha();
        void expressionOpt();
        void lValue();
        void lValueComp();
        void expression();
        void expression_Linha();
        void allocExpression();
        void numExpression();
        void numExpression_Linha();
        void term();
        void term_Linha();
        void unaryExpression();
        void factor();
        void argListOpt();
        void argList();
        void argList_Linha();

    public:

        Parser(string);
        void run();
};