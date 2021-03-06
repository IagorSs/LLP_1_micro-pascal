#include <iostream>

#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/Command.h"

void lexicalTest(char *filename){
    // O código a seguir é usado apenas para testar o analisador léxico.
    // TODO: depois de pronto, comentar o código abaixo.
    LexicalAnalysis l(filename);
    Lexeme lex;

    while ((lex = l.nextToken()).type > TKN_END_OF_FILE) {
        printf("%s, %d\n", lex.token.c_str(), lex.type);
    }

    switch (lex.type) {
        case TKN_INVALID_TOKEN:
            printf("%02d: Lexema inválido [%s]\n", l.line(), lex.token.c_str());
            break;
        case TKN_UNEXPECTED_EOF:
            printf("%02d: Fim de arquivo inesperado\n", l.line());
            break;
        default:
            printf("(\"%s\", %d)\n", lex.token.c_str(), lex.type);
            break;
    }

}

void syntaticTest(char *filename){
    LexicalAnalysis l(filename);
    Lexeme lex;
    SyntaticAnalysis s(l);

    s.start();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [miniPascal file]\n", argv[0]);
        return 1;
    }

    try {
        char *filename = argv[1];

        // char *filename = "./examples/write.mpas";

        // lexicalTest(filename);
        // syntaticTest(filename);

        // O código a seguir é dado para testar o interpretador.
        // TODO: descomentar depois que o analisador léxico estiver OK.
        LexicalAnalysis l(filename);
        SyntaticAnalysis s(l);
        Command* c = s.start();
        c->execute();
        delete c;
    } catch (std::string msg) {
        fprintf(stderr, "Internal error: %s\n", msg.c_str());
        return 2;
    }

    return 0;
}
