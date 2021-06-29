#include "scanner.h"
#include <string>
#include <fstream>  
#define POS_ATUAL input[pos]

/*Scanner::Scanner(string* input){

    this->input= *input;
    cout << "Entrada: " << this->input<< endl << "Tamanho: " << this->input.length() << endl;
    pos = 0; 
}*/

//Construtor

Scanner::Scanner(string input, SymbolTable* table){

    pos = 0;
    lin = 1;
    posIni= 0;
    
    st= table;

    ifstream inputFile;

    inputFile.open(input, ios::in);

    string line;

    if(inputFile.is_open()){

        while(getline(inputFile,line)){

            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else{
        cout << "Impossivel abrir arquivo" << endl;
        exit(EXIT_FAILURE); 
    }

}
char Scanner::getInputPos(int i){
    return input.at(i);
}
int Scanner::getPosIni(){
    return posIni;
}
int Scanner::getLin(){
    return lin;
}
Token* Scanner::nextToken(){
    Token* tok;
    for(;;){
    // Pular espaços em branco
    while(isspace(input[pos]) && POS_ATUAL != '\n')
        pos++;
    
    // Fim da cadeia

    if(POS_ATUAL == '\0'){
        tok = new Token(END_OF_FILE);
        break;
    }
    else if(POS_ATUAL == '\n'){
        lin++;
        pos++;
        posIni= pos;
    }
    // Identificadores 
    else if(isalpha(POS_ATUAL) || POS_ATUAL == '_'){

        string s;

        while(isalnum(POS_ATUAL) || POS_ATUAL == '_'){

            s.push_back(POS_ATUAL);
            pos++;
        }

        STEntry* obj= st->get(s);
        
        if(!obj){
            tok= new Token(ID);
            tok->lexeme= s;
        }
        else
            tok= new Token(obj->token->name);
        
        break;
    }
    // Números

    else if(isdigit(POS_ATUAL)){

        while (isdigit(POS_ATUAL))
            pos++;
        
        if(POS_ATUAL == '.') // Linguagem não aceita números racionais
            lexicalError();
        
        tok = new Token(INTEGER_LITERAL);
        break;
    }

    // Operadores
    
    else if(POS_ATUAL == '<'){
        pos++;

        if(POS_ATUAL == '='){
            pos++;

            tok= new Token(RELOP, LE);
        }
        else
            tok = new Token(RELOP, LT);
        break;
    }
    else if (POS_ATUAL == '='){

        pos++;

        if(POS_ATUAL == '='){
            pos++;
            tok = new Token(RELOP, DEQ);
        }
        else{
            tok = new Token(RELOP, EQUAL);

        }
        break;
    }
    else if (POS_ATUAL == '>'){
        pos++;

        if (POS_ATUAL == '='){

            pos++;
            tok = new Token(RELOP, GE);
        }
        else
            tok = new Token(RELOP, GT);

        break;
    }
    else if(POS_ATUAL == '!'){

        pos++;

        if(POS_ATUAL == '='){

            pos++;
            tok= new Token(RELOP, NE);
        }
        else{
            lexicalError();
        }
        break;
    }
    else if(POS_ATUAL == '+'){
        pos++;

        tok= new Token(RELOP, PLUS);
        break;
    }
    else if(POS_ATUAL == '-'){
        pos++;

        tok= new Token(RELOP, MINUS);
        break;
    }

    // Operador de Divisão ou comentários

    else if(POS_ATUAL == '/'){
        pos++;

        if(POS_ATUAL == '/'){
            pos++;
            while(POS_ATUAL != '\0')
                pos++;
        }
        else if(POS_ATUAL == '*'){
            pos++;
            bool iscomment= true;
            
            while(iscomment == true){
                
                while(POS_ATUAL != '*'){
                    if(POS_ATUAL == '\0')
                        lexicalError();
                    pos++;
                }
                pos++;
                if(POS_ATUAL == '/'){
                    iscomment= false;
                    pos++;
                }
            }
        }
        else{

            tok= new Token(RELOP, DIV);
            break;
        }
    }
    else if(POS_ATUAL == '*'){
        pos++;

        tok= new Token(RELOP, MULT);
        break;
    }
    else if(POS_ATUAL == '%'){
        pos++;

        tok= new Token(RELOP, MOD);
        break;
    }

    // Strings 

    else if(POS_ATUAL == '"'){

        pos++;

        while(POS_ATUAL != '"'){
            
            if(POS_ATUAL == '\0')
                lexicalError();
            pos++;
        }
        
        pos++;
        tok = new Token(STRING_LITERAL);
        break;
    }
    // Separadores

    else if(POS_ATUAL == '('){
        pos++;
        tok = new Token(SEP, L_PAREN);
        break;
    }
    else if(POS_ATUAL == ')'){
        pos++;
        tok = new Token(SEP, R_PAREN);
        break;
    }
    else if(POS_ATUAL == '{'){
        pos++;
        tok = new Token(SEP, L_BRACES);
        break;
    }
    else if(POS_ATUAL == '}'){
        pos++;
        tok = new Token(SEP, R_BRACES);
        break;
    }
    else if(POS_ATUAL == '['){
        pos++;
        tok = new Token(SEP, L_BRACKETS);
        break;
    }
    else if(POS_ATUAL == ']'){
        pos++;
        tok = new Token(SEP, R_BRACKETS);
        break;
    }
    else if(POS_ATUAL == ','){
        pos++;
        tok = new Token(SEP, COMMA);
        break;
    }
    else if(POS_ATUAL == ';'){
        pos++;
        tok = new Token(SEP, SEMICOL);
        break;
    }
    else if(POS_ATUAL == '.'){
        pos++;
        tok = new Token(SEP, DOT);
        break;
    }
    else{
        lexicalError();
    }
    }
        return tok;
}
void Scanner::lexicalError(){

    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}