using namespace std;

class Token{

  public:
    string text;
    TokenType type;
    int line;
  
    Token(string text, TokenType type, int line = -1){
        this->text = text;
        this->line = line;
        this->type = type;
    }

    string get_type_text(){
        return type_name[this->type];
    }

    int get_type_enum(){
        return this->type;
    }

};