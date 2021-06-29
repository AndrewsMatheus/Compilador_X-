#include "parser3v.h"

void Parser::program(){
    
    if(lToken->name == CLASS){
        classList();
    }
    else if(lToken->name == END_OF_FILE){
        
    }
    else{
        errorSyntatic();
    }
    
}
void Parser::classList(){
   
    classDecl();
    classList_Linha();
}
void Parser::classList_Linha(){
    
    if(lToken->name == CLASS){
        classList();
    }
}
void Parser::classDecl(){
    

    match(CLASS);
    match(ID);

    if(lToken->name == EXTENDS){
        advance();
        match(ID);
    }

    classBody();
}
void Parser::classBody(){
    
    if(lToken->attribute == L_BRACES){
        advance();

        currentST= new SymbolTable(currentST);

        varDeclListOpt();
        constructDeclListOpt();
        methodDeclListOpt();
        match(R_BRACES);
        returnST();
    }
    else{
        errorSyntatic();
    }
}
void Parser::varDeclListOpt(){
    
    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID){
        VarDeclList_Linha();
    }
}
void Parser::VarDeclList_Linha(){

    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID){
        
        varDecl();
        VarDeclList_Linha();
    }
}
void Parser::varDecl(){
    
    type();

    if(lToken->attribute == L_BRACKETS){
        advance();
        match(R_BRACKETS);
    }

    match(ID);
    varDeclOpt();
    match(SEMICOL);

}
void Parser::varDeclOpt(){
    
    if(lToken->attribute == COMMA){
        advance();
        match(ID);
        varDeclOpt();
    }
}
void Parser::type(){
    
    if(lToken->name == INTEGER_LITERAL){
        advance();
    }
    else if(lToken->name == STRING_LITERAL){
        advance();
    }
    else if(lToken->name == ID){
        advance();
    }
    else 
        errorSyntatic();
}
void Parser::constructDeclListOpt(){
    
    if(lToken->name == CONSTRUCTOR){
        ConstructDeclList_Linha();
    }
}
void Parser::ConstructDeclList_Linha(){
    
    if(lToken->name == CONSTRUCTOR){
        constructDecl();
        ConstructDeclList_Linha();
    }
}
void Parser::constructDecl(){
    
    match(CONSTRUCTOR);
    methodBody();
}
void Parser::methodDeclListOpt(){
    
    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID)
        methodDeclList_Linha();
}
void Parser::methodDeclList_Linha(){

    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID){
        methodDecl();
        methodDeclList_Linha();
    }

}
void Parser::methodDecl(){

    type();

    if(lToken->attribute == L_BRACKETS){
        advance();
        match(R_BRACKETS);
    }
    match(ID);
    methodBody();
}
void Parser::methodBody(){


    currentST= new SymbolTable(currentST);

    match(L_PAREN);
    paramListOpt();
    match(R_PAREN);
    match(L_BRACES);
    statementsOpt();

    match(R_BRACES);
    returnST();
}
void Parser::paramListOpt(){

    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID)
        paramList();
    
}
void Parser::paramList(){

    param();
    paramList_Linha();
}
void Parser::paramList_Linha(){

    if(lToken->attribute == COMMA){
        advance();
        param();
        paramList_Linha();
    }
}
void Parser::param(){

    type();

    if(lToken->attribute == L_BRACKETS){
        advance();
        match(R_BRACKETS);
    }
    match(ID);
}
void Parser::statementsOpt(){
   
    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID || lToken->name == PRINT || lToken->name == READ ||lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOL){
        statements_Linha();
    }
}
void Parser::statements_Linha(){
    
    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID || lToken->name == PRINT || lToken->name == READ ||lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOL){
        statement();
        statements_Linha();
    }
}
void Parser::statement(){
    
    if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID){ // (gambiarra que toma uma decisão entre varDecl e atribStat :D )

        if(lToken->name == ID){ // atribStat e varDecl para ID

            STEntry* p= currentST->get(lToken->lexeme);

            if(p == 0){
                    errorSemantic();
                    cout << "[Aviso] " << "O ID "<< lToken->lexeme << " nao foi declarado neste e em nenhum escopo." << endl;
                }
            advance();

            if(lToken->attribute == L_BRACKETS){
                advance();

                if(lToken->attribute == PLUS || lToken->attribute == MINUS){
                    expression();
                }

                match(R_BRACKETS);
            }
            if(lToken->attribute == EQUAL || lToken->attribute == DOT){ //atribstat
            
                if(lToken->attribute == L_BRACKETS){
                    advance();
                    expression();
                    match(R_BRACKETS);
                }
                if(lToken->attribute == DOT)
                    lValueComp();
                
                atribStat();
            }
            else{ // varDecl
            
                if(lToken->attribute == L_BRACKETS){
                    advance();
                    match(R_BRACKETS);
                }

                match(ID);
                varDeclOpt();
                match(SEMICOL);
                VarDeclList_Linha();
            }

        }
        else{ // Vardecl para INT E STRING
            varDecl();
            VarDeclList_Linha();
        }
    }
    else if(lToken->name == PRINT){
        printStat();
        match(SEMICOL);
    }
    else if(lToken->name == READ){
        readStat();
        match(SEMICOL);
    }
    else if(lToken->name == RETURN){
        returnStat();
        match(SEMICOL);
    }
    else if(lToken->name == SUPER){
        superStat();
        match(SEMICOL);
    }
    else if(lToken->name == IF){
        ifStat();
    }
    else if(lToken->name == FOR){
        forStat();
    }
    else if(lToken->name == BREAK){
        advance();
        match(SEMICOL);
    }
    else if(lToken->attribute == SEMICOL){
        advance();
    }
}
void Parser::atribStat(){

    match(EQUAL);
    atribStat_Linha();
}
void Parser::atribStat_Linha(){

    if(lToken->attribute == PLUS || lToken->attribute == MINUS){
        expression();
    }
    else if(lToken->name == NEW || lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL ||lToken->name == ID){
        allocExpression();
    }
    else
        errorSyntatic();
}
void Parser::printStat(){

    match(PRINT);
    expression();
}
void Parser::readStat(){

    match(READ);
    lValue();
}
void Parser::returnStat(){

    match(RETURN);
    expression();
}
void Parser::superStat(){

    match(SUPER);
    match(L_PAREN);
    argListOpt();
    match(R_PAREN);
}
void Parser::ifStat(){


    match(IF);
    match(L_PAREN);

    currentST= new SymbolTable(currentST);

    expression();
    match(R_PAREN);
    match(L_BRACES);
    statements_Linha();

    match(R_BRACES);
    ifStat_Linha();

    returnST();
}
void Parser::ifStat_Linha(){

    if(lToken->name == ELSE){
        
        advance();
        match(L_BRACES);

        currentST= new SymbolTable(currentST);
        statements_Linha();
        returnST();
        match(R_BRACES);
    }
}
void Parser::forStat(){

    match(FOR);
    match(L_PAREN);

    currentST= new SymbolTable(currentST);

    atribStatOpt();
    match(SEMICOL);
    expressionOpt();
    match(SEMICOL);
    atribStatOpt();
    match(R_PAREN);
    match(L_BRACES);
    statements_Linha();
    returnST();
    match(R_BRACES);
}
void Parser::atribStatOpt(){

    if(lToken->name == ID){
        lValue();
        match(EQUAL);
        atribStatOpt_Linha(); 
    }
}
void Parser::atribStatOpt_Linha(){

    if(lToken->attribute == PLUS || lToken->attribute == MINUS){
        expression();
    }
    else if(lToken->name == NEW || lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL || lToken->name == ID){
        allocExpression();
    }
    else
        errorSyntatic();
}
void Parser::expressionOpt(){

    if(lToken->attribute == PLUS || lToken->attribute == MINUS){
        expression();
    }
}
void Parser::lValue(){

    
    if(lToken->name == ID){

        STEntry* p= currentST->get(lToken->lexeme);

        if(p == 0){
            errorSemantic();
            cout << "[Aviso] " << "O ID "<< lToken->lexeme << " nao foi declarado neste e em nenhum escopo." << endl;
        }
    
        advance();
    }
    else
        errorSyntatic();

    if(lToken->attribute == L_BRACKETS){
        advance();
        expression();
        match(R_BRACKETS);
    }
    lValueComp();
}
void Parser::lValueComp(){

    if(lToken->attribute == DOT){

       advance();

       if(lToken->name == ID){

        STEntry* p= currentST->get(lToken->lexeme);

        if(p == 0){
            errorSemantic();
            cout << "[Aviso] " << "O ID "<< lToken->lexeme << " nao foi declarado neste e em nenhum escopo." << endl;
        }
    
        advance();
    }
    else
        errorSyntatic();

    if(lToken->attribute == L_BRACKETS){
        advance();
        expression();
        match(R_BRACKETS);
    }
        lValueComp();
    }
}
void Parser::expression(){

    numExpression();
    expression_Linha();
}
void Parser::expression_Linha(){

    if(lToken->name == RELOP){
        advance();
        numExpression();
    }

}
void Parser::allocExpression(){

    if(lToken->name == NEW){
        advance();
        match(ID);
        match(L_PAREN);
        argListOpt();
        match(R_PAREN);
    }
    else if(lToken->name == INTEGER_LITERAL){
        advance();
        match(ID);
        match(L_BRACKETS);
        expression();
        match(R_BRACKETS);

    }
    else if(lToken->name == STRING_LITERAL){
        advance();
        match(ID);
        match(L_BRACKETS);
        expression();
        match(R_BRACKETS);
    }
    else if(lToken->name == ID){
        match(ID);
        match(L_BRACKETS);
        expression();
        match(R_BRACKETS);
    }
    else
        errorSyntatic();
}
void Parser::numExpression(){

    term();
    numExpression_Linha();
}
void Parser::numExpression_Linha(){

    if(lToken->attribute == PLUS || lToken->attribute == MINUS){
        advance();
        term();
    }
}
void Parser::term(){

    unaryExpression();
    term_Linha();
}
void Parser::term_Linha(){

    if(lToken->attribute == DIV || lToken->attribute == MULT || lToken->attribute == MOD){
        advance();
        unaryExpression();
    }
}
void Parser::unaryExpression(){

    if(lToken->attribute == PLUS || lToken->attribute == MINUS){
        advance();
        factor();
    }
    else
        errorSyntatic();
}
void Parser::factor(){

    if(lToken->name == INTEGER_LITERAL){
        advance();
    }
    else if(lToken->name == STRING_LITERAL){
        advance();
    }
    else if(lToken->name == ID){
        lValue();
    }
    else if(lToken->attribute == L_PAREN){
        advance();
        expression();
        match(R_PAREN);
    }
}
void Parser::argListOpt(){

    if(lToken->attribute == PLUS || lToken->attribute == MINUS){     
        argList();
    }
}
void Parser::argList(){

    numExpression();
    argList_Linha();
}
void Parser::argList_Linha(){

    if(lToken->attribute == COMMA){
        advance();
        expression();
        argList_Linha();
    }
    else if(lToken->name == RELOP){
        advance();
        numExpression();
        argList_Linha();
    }
}
Parser::Parser(string input){

    currentST= globalST = new SymbolTable();

    initSymbolTable();
    
    scanner = new Scanner(input, globalST);
}
void Parser::advance(){
    
    lToken= scanner->nextToken();
}
void Parser::match(int t){

    if(lToken->name == t || lToken->attribute == t){

        if(lToken->name == ID){
            STEntry* entry= new STEntry(lToken, lToken->lexeme);
            if(currentST->add(entry) == false){
                errorSemantic();
                cout << "[AVISO] O ID " << lToken->lexeme << " ja foi declarado no escopo atual." << endl;
            }
        }
        advance();
    }
    else
        errorSyntatic();
}
void Parser::initSymbolTable(){

    Token* t;

    t= new Token(CLASS);
    globalST->add(new STEntry(t, "class", true));
    t= new Token(IF);
    globalST->add(new STEntry(t, "if", true));
    t= new Token(ELSE);
    globalST->add(new STEntry(t, "else", true));
    t= new Token(EXTENDS);
    globalST->add(new STEntry(t, "extends", true));
    t= new Token(FOR);
    globalST->add(new STEntry(t, "for", true));
    t= new Token(NEW);
    globalST->add(new STEntry(t, "new", true));
    t= new Token(INTEGER_LITERAL);
    globalST->add(new STEntry(t, "int", true));
    t= new Token(STRING_LITERAL);
    globalST->add(new STEntry(t, "string", true));
    t= new Token(PRINT);
    globalST->add(new STEntry(t, "print", true));
    t= new Token(READ);
    globalST->add(new STEntry(t, "read", true));
    t= new Token(RETURN);
    globalST->add(new STEntry(t, "return", true));
    t= new Token(SUPER);
    globalST->add(new STEntry(t, "super", true));
    t= new Token(CONSTRUCTOR);
    globalST->add(new STEntry(t, "constructor", true));
    t= new Token(BREAK);
    globalST->add(new STEntry(t, "break", true));

}
void Parser::run(){

    currentST= new SymbolTable();
    
    advance();
    program();

    if(hasError)
        cout << "Compilacao encerrada!!" << endl;
    else
        cout << "Compilacao encerrada com sucesso!!" << endl;

    returnST();
}
void Parser::returnST(){

    SymbolTable* p= currentST;
    p->clear();
    currentST= currentST->getParent();
    delete p;
}
void Parser::showLine(){

    cout << "Linha: " << scanner->getLin() << " ";
    
    int posFin, i;

    for(i= scanner->getPosIni(); scanner->getInputPos(i) != '\0' && scanner->getInputPos(i) != '\n' ; i++){
    }

    posFin= i;
    i= scanner->getPosIni();
    while(i < posFin){
        cout<< scanner->getInputPos(i);
        i++;
    }
    cout << endl;
}
void Parser::errorSyntatic(){

    cout << "Erro sintatico\n";

    showLine();

    exit(EXIT_FAILURE);
}
void Parser::errorSemantic(){

    cout << "Erro semantico" << endl;

    showLine();

    hasError= true;
}