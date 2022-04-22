using namespace std;

class Scanner{
  private:
    int current_position;
    char current_char;
    string source;

  public:

    Scanner(string source){
      this->source = source;
      this->current_position = -1;
      this->current_char = source[-1];
      this->next_char();
    }

    char peek(){
        if (this->current_position + 1  >= this->source.length())
            return '\0';
        return this->source[this->current_position+1];
    }

    void next_char(){
        this->current_position += 1;
        if (this->current_position  >= this->source.length()){
            this->current_char = '\0';
        }
        else{
            this->current_char = this->source[this->current_position];
        }
        // cout << this->current_char ;
    }

    void skip_whitespaces(){
        while(this->current_char==' ' || this->current_char == '\t' || this->current_char == '\t'){
            this->next_char();
        }
    }

    Token * get_token(){
      // cout << this->current_char << endl;
        Token * token = NULL;
        this->skip_whitespaces();

        // COLON: :
        if (this->current_char == ':'){
            token = new Token(":", COLON);
        }
        // SEMICOLON: ;
        else if (this->current_char == ';'){
            token = new Token(";", SEMICOLON);
        }
        // COMMA: ,
        else if (this->current_char == ','){
            token = new Token(",", COMMA);
        }
        // PLUS: +
        else if (this->current_char == '+'){
            token = new Token("+", PLUS);
        }
        // MINUS: -
        else if (this->current_char == '-'){
            token = new Token("-", MINUS);
        }
        // ASTERIX: *
        else if (this->current_char == '*'){
            token = new Token("*", ASTERIX);
        }
        // DIVIDE: /
        else if (this->current_char == '/'){
            token = new Token("/", DIVIDE);
        }
        // MOD: %
        else if (this->current_char == '%'){
            token = new Token("%", MOD);
        }
        // OPENING BRACKET: )
        else if (this->current_char == '('){
            token = new Token("(", OPEN_BRACKET);
        }
        // OPENING BRACKET: )
        else if (this->current_char == ')'){
            token = new Token(")", CLOSING_BRACKET);
        }
        // OPENING SQUARE BRACKET: )
        else if (this->current_char == '['){
            token = new Token("[", SQUARE_OPEN_BRACKET);
        }
        // CLOSING SQUARE BRACKET: )
        else if (this->current_char == ']'){
            token = new Token("]", SQUARE_CLOSING_BRACKET);
        }
        // EQUAL: )
        else if (this->current_char == '='){
            token = new Token("=", EQUAL);
        }
        // NUMBERS
        // NUMBERS: 124, 12.4123
        else if (isdigit(this->current_char)){
            int start_position = this->current_position;
            if ( isdigit(this->peek()) ){ // IF NEXT CHAR IS ALSO DIGIT
                this->next_char();
                while( isdigit( this->peek() ) ){
                    this->next_char();
                }
            }

            // FLOATING NUMBERS: 124, 12.4123
            if (this->peek() == '.'){
                this->next_char();
                if( !isdigit( this->peek() ) ){
                    cout << "\n\t SCANNING ERROR: ILLEGAL CHAR AT POSITION " << this->current_position << endl;
                    exit(0);
                    token = new Token("INVALID", TERMINATE_TOKEN );
                }
                while( isdigit( this->peek() ) ){
                    this->next_char();
                }
            }
            
            int token_length = this->current_position - start_position +1;
            string number_token = this->source.substr(start_position, token_length);
            token = new Token(number_token, NUMBER);
        }

        // STRINGS
        else if(this->current_char == '"'){
            int start_position = this->current_position + 1;
            while(this->peek()!='"'){
                this->next_char();
            }
            this->next_char();
            int token_length = this->current_position - start_position +1;
            string recognized_token = '"' + this->source.substr(start_position, token_length);
            token = new Token(recognized_token, STRING);
        }
    
        // IDENTIFIERS: Begin with letter or '_' (made of digits or '_')
        else if (isalpha(this->current_char) || this->current_char == '_'  ){
            int start_position = this->current_position;
            while(isdigit(this->peek()) || isalpha(this->peek()) || this->peek() == '_'  ){
                this->next_char();
            }
            int token_length = this->current_position - start_position +1;
            string recognized_token = this->source.substr(start_position, token_length);

            // Check for reserved keywords

            // begin, end
            if (recognized_token == "begin") token = new Token(recognized_token, BEGIN);
            else if (recognized_token == "end") token = new Token(recognized_token, END);

            // and, or
            else if (recognized_token == "and") token = new Token(recognized_token, AND);
            else if (recognized_token == "or") token = new Token(recognized_token, OR);

            // create, print
            else if (recognized_token == "create") token = new Token(recognized_token, CREATE);
            else if (recognized_token == "print") token = new Token(recognized_token, PRINT);

            // if, ifbody, else, do, endif
            else if (recognized_token == "if") token = new Token(recognized_token, IF);
            else if (recognized_token == "endif") token = new Token(recognized_token, ENDIF);
            else if (recognized_token == "ifbody") token = new Token(recognized_token, IFBODY);
            else if (recognized_token == "else") token = new Token(recognized_token, ELSE);
            else if (recognized_token == "do") token = new Token(recognized_token, DO);
            else if (recognized_token == "not") token = new Token(recognized_token, NOT);

            // while, whilebody, endwhile
            else if (recognized_token == "while") token = new Token(recognized_token, WHILE);
            else if (recognized_token == "whilebody") token = new Token(recognized_token, WHILEBODY);
            else if (recognized_token == "endwhile") token = new Token(recognized_token, ENDWHILE);

            // identifiers
            else token = new Token(recognized_token, IDENTIFIER);
        }
        else if(this->current_char == '\0'){
            token = new Token("\0", TERMINATE_TOKEN);
        }
        else {
            cout << " > SCANNING ERROR:\t Unsupported type of char: '" << this->current_char << "'" << endl;
            exit(0);
        }
        this->next_char();
        return token;
    }
};