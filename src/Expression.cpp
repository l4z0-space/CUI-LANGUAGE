#include "helpers.cpp"


class Expression{

  public:

    Expression(){}

    virtual string flow(){
        return "undefined_expression";
    }

    virtual string get_value(){
        return "none";
    }
};


class Literal: public Expression{

    private:

        Token* value;


    public:

        Literal(Token* _value){
            this->value = _value;
        }

        string flow(){
            return "Literal(" + this->value->text + ")";
        }

        string get_value(){ //
            string var = this->value->text;
            if (var[0] == '\''){ // if string
                return this->value->text;
            }
            if (isalpha(var[0])){ // variable

                if(var=="input_number"){
                    string tmp;
                    cout << "Input: ";cin>> tmp;
                    static regex const re{R"([0-9]+([\.][0-9]+)?)"};
                    if (!regex_match(tmp, re)){
                        cout << "\nRuntime error: Invalid number!\n";
                        exit(0);
                    }
                    tmp = tmp ;
                    return tmp;
                }
                if(var=="input_string"){
                    string tmp;
                    cout << "Input: ";cin>> tmp;
                    tmp = '"' + tmp + '"' ;
                    return tmp;
                }

                if (mapContainsKey(var)){
                    return var_table[var];
                }
                cout << "\nRuntime Error: undefined variable: '" << var << "'\n\n";
                exit(0);
            }
            return this->value->text;
        }
};


class Binary: public Expression{

    private:

        Expression* left;
        TokenType op;
        Expression* right;


    public:
        
        Binary(Expression* _left, TokenType _op, Expression* _right){
            this->left = _left;
            this->right = _right;
            this->op = _op;
        }

        string flow(){
            return "Binary(" + this->left->flow() + " " + type_name[this->op] + " " + this->right->flow() + ")";
        }

        string get_value(){
            float left_n, right_n;
            string left_s, right_s;
            if (this->left->get_value()[0]!='"' && this->right->get_value()[0]!='"'){ // both numbers
                left_n = stof(this->left->get_value());
                right_n = stof(this->right->get_value());
                switch(op){
                case PLUS:
                    return to_string(left_n + right_n);
                case MINUS:
                    return to_string(left_n - right_n);
                case ASTERIX:
                    return to_string(left_n * right_n);
                case DIVIDE:
                    return to_string(left_n / right_n);
                case MOD:
                    return to_string((int)left_n % (int)right_n);
                default:
                    cout << "\nRuntime Error: Unsupported operator " <<  type_name[op] << " between number and strings!\n\n";
                    exit(0);;
                }
            }

            if (this->left->get_value()[0]=='"' ){ // both strings
                left_s = this->left->get_value();
                right_s = this->right->get_value();
                if (right_s[0]!='"')right_s = '"'+right_s + '"'; // if number being converted to string
                switch(op){
                case PLUS:
                    left_s.pop_back();
                    right_s.erase(0,1);
                    return left_s + right_s;
                default:;
                }
            }
            cout << "\nRuntime Error: Unsupported operator " <<  type_name[op] << " between numbers and strings!\n\n";
            exit(0);
        }
};

class Unary: public Expression{

    private:

        Expression* right;
        TokenType op;


    public:
      
        Unary(TokenType _op, Expression* _right){
            this->op = _op;
            this->right = _right;
        }

        string flow(){
            return "Unary(" + type_name[this->op] + " " + this->right->flow() + ")";
        }

        string get_value(){
            switch(this->op){
            case MINUS:
                return "-"+ this->right->get_value();
            case NOT:
                if (isTruthy(this->right->get_value()))
                return "0";
                return "1";
            default:
                return this->right->get_value();
            }
        }

};


class Variable: public Expression{

    private:

        TokenType name;


    public:

        Variable(TokenType _name){
            this->name = _name;
        }

        string flow(){
          return "Variable: " + type_name[this->name];
        }
};
