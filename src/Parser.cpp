


class Parser{

  private:
    vector<Token*> tokens;
    vector<Statement*> all_statements;
    int current_pos = 0;

  public:
    Parser(vector< Token*> tokens){
      this->tokens = tokens;
    }

    vector<Statement*> get_statements(){
      return this->all_statements;
    };

    Token * curr_token(){
      return this->tokens[this->current_pos];
    }

    Token * prev_token(){
      return this->tokens[this->current_pos-1];
    }

    Token * peek_token(){
      if (this->current_pos >= this->tokens.size()-1){
        return NULL;
      }
      return this->tokens[this->current_pos+1];
    }

    bool is_end(){
      return this->curr_token()->type == TERMINATE_TOKEN;
    }

    void next_token(){
      if (!is_end()) this->current_pos += 1;
    }

    int token_length(){ return tokens.size();}

    vector<Token*> get_tokens(){
      return tokens;
    }

    void program(){
      this->compoundstmt();
    }

    // compoundstmt ->  begin  stmtlist  end
    void compoundstmt(){
      this->consume({BEGIN}, "Expected 'begin' in the beggining of compound statement! ");
      vector<Statement*> all_statements = this->stmtlist();
      this->all_statements = all_statements;
      this->consume({END}, "Expected 'end' in the end of compound statement! ");
    }

    // stmtlist  -> stmt  {  ;  stmt  }* 
    vector<Statement*>  stmtlist(){
      vector<Statement*> all_statements;

      all_statements.push_back(this->stmt());
      while(this->check(SEMICOLON)){
        this->consume({SEMICOLON}, "Expected semicolon");
        all_statements.push_back(this->stmt());
      }
      return all_statements;
    }


    //   stmt ->  variable   =  expression
    //          |  if  (  expression )  ifbody  stmtlist  endif
    //          |  if  (  expression )  ifbody  stmtlist  else  stmtlist  endif
    //          |  while  ( expression )  whilebody  stmtlist  endwhile
    Statement* stmt(){
      Statement* to_return = NULL;
      if(this->check(PRINT)) to_return = this->printstmt();
      if(this->check(IF)) to_return = this->ifstmt();
      if(this->check(WHILE)) to_return = this->whilestmt();
      if(this->check(IDENTIFIER)) to_return = this->expressionstmt();
      if(this->check(CREATE)) to_return = this->declaration();

      return to_return;
    }

    Statement* expressionstmt(){
        Token* var = this->variable();
        this->consume({EQUAL}, "Expect '=' after variable!");
        Expression* expr = this->term();
        return new ExpressionStatement(var, expr);
    }

    /* PRINTSTMT  */
    Statement* printstmt(){
        this->next_token();
        this->consume({OPEN_BRACKET}, "Expect '(' before expression!");

        Expression* expression = this->term();

        this->consume({CLOSING_BRACKET}, "Expect ')' after expression!");

        return new Print(expression);
    }

    /* IFSTMT -> if (expression) ifbody STAT {;  STAT}* endif */
    Statement* ifstmt(){
      this->next_token();
      this->consume({OPEN_BRACKET}, "Expect '(' before expression!");

      Expression* if_condition = this->term();

      this->consume({CLOSING_BRACKET}, "Expect ')' after expression!");
      this->consume({IFBODY}, "Expect 'ifbody' after conditional expression!");

    //   this->stmtlist();
      StatementList* then_body = new StatementList(this->stmtlist());
      Statement* else_body = NULL;
      // either Endif or Else 
      if (this->check(ELSE)){
        if(this->check(ELSE)){
          this->consume({ELSE}, "Expected else");
          this->consume({DO}, "Expected 'do' after else");
          else_body = this->stmt();
        }
      }
      this->consume({ENDIF}, "Expect endif in the end of IF statement");

      If* if_stmt = new If(if_condition, then_body, else_body);
      return if_stmt;
    }

    Statement* whilestmt(){
      this->next_token();

      this->consume({OPEN_BRACKET}, "Expect '(' before while expression!");

      Expression* condition = this->term();
      this->consume({CLOSING_BRACKET}, "Expect ')' after while expression!");

      this->consume({WHILEBODY}, "Expect 'whilebody' after while statement declaration!");
    //   this->stmtlist(); // stmtlist
      StatementList* while_body = new StatementList(this->stmtlist());
      this->consume({ENDWHILE}, "Expect 'endwhile' in the end of while statement");

      While* while_stmt = new While(condition, while_body);
      return while_stmt;
    }

    //  EXPR -> TERM { ( '+' | '-' ) TERM}*
    Expression* term(){
      // string first_operator = this->term();
      Expression* expr = this->factor();
      TokenType op;

      while (this->check(PLUS) || this->check(MINUS)){
        if(this->check(PLUS)){
          op = PLUS;
        }
        else if(this->check(MINUS)){
          op = MINUS;
        }
        this->next_token();
        Expression* right = this->factor();
        expr = new Binary(expr, op, right);
      }

      return expr;
    }

    // FACTOR -> UNARY { ( '/' | '*' | '%' ) UNARY}*
    Expression* factor(){
      auto prev_token = this->curr_token();
    //   this->consume({IDENTIFIER, NUMBER}, "Expect identifier or number in term!");

      TokenType op;
      Expression* expr = this->unary();

      while (this->check(ASTERIX) || this->check(DIVIDE) || this->check(MOD)){
        if(this->check(ASTERIX)){
          op = ASTERIX;
        }
        else if(this->check(DIVIDE)){
          op = DIVIDE;
        }
        else if(this->check(MOD)){
          op = MOD;
        }
        this->next_token();

        // this->consume({IDENTIFIER, NUMBER}, "Expect identifier or number after operator!");

        auto right = this->unary();
        expr = new Binary(expr, op, right);
      }
      return expr;
    }

    Expression* unary(){
        if(this->check(MINUS)){
            TokenType op= MINUS;
            this->consume({MINUS}, "Expected -");
            Expression* right = this->unary();
            return new Unary(op, right);
        }
        else if(this->check(NOT)){
          // cout << "NOT\n";
            TokenType op= NOT;
            this->consume({NOT}, "Expected not");
            Expression* right = this->unary();
            return new Unary(op, right);
        }
        return this->literal();
    }

    Expression* literal(){
        Literal * literal;
        if (this->check(NUMBER) || this->check(IDENTIFIER) || this->check(STRING)){
            literal =  new Literal(this->curr_token());
            // cout << literal->value->text << endl;
        }
        this->consume({IDENTIFIER, NUMBER, STRING}, "Expect literal or identifier!");
        return literal;
    }

    Statement* declaration(){
      this->consume({CREATE}, "Expected 'create' when creating variable!");
      Token* variable_name = this->variable();

      Expression* initializer = new Expression();
      if (this->check(EQUAL)){
          this->consume({EQUAL}, "Expect '=' in variable declaration!");
          initializer = term();
      }

      return new Initialization(variable_name, initializer);
    }

    // variable  ->  id  
    Token* variable(){
      this->consume({IDENTIFIER}, "Expect identifier in variable");
      return this->prev_token();
    }

    bool consume(vector<TokenType> to_consume, string error_message){
      /* 
        Consumes: check if curr token is of expected token
        and if not throw the error with message: error_message
      */
      for (TokenType token_type: to_consume ){
        if (this->curr_token()->type == token_type){
          this->next_token();
          return 1;
        }
      }
      cout << " > PARSING ERROR:\t" << error_message << " Got '" << this->curr_token()->text << "'" << endl;
      exit(0);
    }

    bool check(TokenType type){
      return this->curr_token()->type == type;
    }
};
