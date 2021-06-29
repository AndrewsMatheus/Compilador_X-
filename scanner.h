#include "symboltable.h"
class Scanner {
    
    private:
        SymbolTable* st; 
        string input;//Armazena o texto de entrada
        int posIni;//Posição inicial da linha
        int lin; // quantidade de linhas do texto de entrada
        int pos; // posicao atual

    public:
    //Construtor
        Scanner(string input, SymbolTable*);
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void lexicalError();
        
        char getInputPos(int);

        int getLin();

        int getPosIni();
};
