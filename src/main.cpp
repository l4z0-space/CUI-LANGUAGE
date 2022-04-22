#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>
#include <unordered_map>
#include <regex>

#include "TokenType.cpp"
#include "Token.cpp"
#include "Scanner.cpp"
#include "Expression.cpp"
#include "Statement.cpp"
#include "Parser.cpp"

using namespace std;

int main(int argc, char** argv) {
    init_types();

    // < Reading the source file
    ifstream sourcefile;
    if(argc < 2){
      cout << "\nPlease enter the name of the file to be executed!\n";
      exit(0);
    }
    
    string file_name = argv[1];
    try{
      sourcefile.open(file_name);
        if(!sourcefile){
          throw 404;
        }
    }
    catch(int error){
      cout << "File " << file_name << " not found in the current directory!\n";
      exit(0);
    }
    string source, nxt;
    while(!sourcefile.eof()){
      getline(sourcefile, nxt);
      source += nxt + " ";
    }
    sourcefile.close();
    // Reading the source file >

    // < Generating the tokens
    Scanner *scanner = new Scanner(source);
    auto token = scanner->get_token();
    vector<Token*> all_tokens;
    while(token->get_type_enum() != TERMINATE_TOKEN){
        all_tokens.push_back(token);
        token = scanner->get_token();
    }
    all_tokens.push_back(token);  
    // Generating the tokens >

    // < Parsing the tokens
    Parser* parser = new Parser(all_tokens);
    parser->program();
    // Parsing the tokens >

    // < Consuming the statements
    for(auto x : parser->get_statements()){
      // cout << x->flow(1) << "\n";  // Uncomment this to print the flow of the execution
      x->consume();
    }
    // Consuming the statements >

    return 0; 
}
