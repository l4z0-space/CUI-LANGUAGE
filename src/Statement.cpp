

class Statement{ // abstract class

    public:

        Statement(){}

        virtual string type() {
            return "undefined_statement";
        }

        virtual string flow(int lvl) {
            return "undefined_statement";
        }

        virtual void consume() = 0;
        
};

class StatementList: public Statement{

    private:

        vector<Statement*> statements;


    public:

        StatementList(vector<Statement*>_statements){
          this->statements = _statements;
        }

        virtual string type() {
            return "list_statement";
        }

        virtual string flow(int lvl) {
          string res = "";
          for (Statement* stmt : this->statements){
              res += stmt->flow(lvl+1);
          }
          return res;
        }

        virtual void consume(){
            // consume all the statements in the list
            for (Statement* stmt : this->statements){
                stmt->consume();
            }
        }

};

class Print: public Statement{
    
    private:

        Expression* expression;


    public:

        Print(Expression* expression){
            this->expression = expression;
        }

        virtual string type() {
            return "print_statement";
        }

        virtual string flow(int lvl) {
            return "print( " +this->expression->flow() + ")";
        }
    
        virtual void consume(){
            cout << this->expression->get_value() << endl;
        };

};

class If: public Statement{

    private:

        Expression *condition;
        StatementList* then_body;
        Statement* else_body;


    public:

        If(Expression* _condition, StatementList* _then_body, Statement* _else_body){
            this->condition = _condition;
            this->then_body = _then_body;
            this->else_body = _else_body;
        }

        string type() {
            return "if_statement";
        }

        string flow(int lvl) {
            string condition_expression ="condition( " +this->condition->flow() + ")";
            return "if_statement " + condition_expression + ": \n" + tabs(lvl) + this->then_body->flow(lvl+1);
        }

        void consume(){
          string condition_value = this->condition->get_value();
          if (isTruthy(condition_value)){ // execute then_body only if condition is truthy
            this->then_body->consume();
          }
          else if (this->else_body){
            this->else_body->consume();
          }
        }

};

class While: public Statement{

    private:

        Expression *condition;
        StatementList* while_body;


    public:

        While(Expression* condition, StatementList* while_body){
            this->condition = condition;
            this->while_body = while_body;
        }

        string type() {
            return "while_statement";
        }

        string flow(int lvl) {
            string condition_expression ="condition( " +this->condition->flow() + ")";
            return "while_statement " + condition_expression +": \n" + tabs(lvl) + this->while_body->flow(lvl+1);
        }

        void consume(){
            while(isTruthy(this->condition->get_value())){
                this->while_body->consume();
            }
        }
};

class Initialization: public Statement{

    private:

        Expression *initializer;
        Token* name;


    public:

        Initialization(Token* name, Expression* initializer){
            this->name = name;
            this->initializer = initializer;
        }

        string type() {
            return "declaration_statement";
        }

        string flow(int lvl) {
            return "declaration_statement: \n" + tabs(lvl) + this->name->text + " = " + this->initializer->flow();
        }

        void consume(){
            string var = this->name->text;
            string value = this->initializer->get_value();
            if(mapContainsKey(var)){
                cout << "\nRuntime Error: Variable '" << var << "' already initialized!\n\n";
                exit(0);
            }
            var_table[var] = value;
        }
};

class ExpressionStatement: public Statement{

    private:

        Expression* expression;
        Token* variable;


    public:
        
        ExpressionStatement(Token* _variable, Expression* _expression){
            this->expression = _expression;
            this->variable = _variable;
        }

        string type() {
            return "expression_statement";
        }

        string flow(int lvl) {
            return "expression_statement: \n\t" + this->expression->flow();
        }

        void consume(){
          string var = this->variable->text;
          if (!mapContainsKey(var)){
            cout << "\nRuntime error: Variable '" << var << "' is not defined!\n\n";
            exit(0);
          }
          string expression_value = this->expression->get_value();
          var_table[var] = expression_value;
        }
};
