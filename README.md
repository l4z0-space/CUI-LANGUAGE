# CUI-LANGUAGE
Simple programming language implemented (handmade :p) in C++

<div style="display:flex;">
<img src="logolight.png" width="200" height="200">
<img src="logodark.png" width="200" height="200">
</div>

> This language is open to extensions and adding more features. The goal is to make a dead-simple programming language comprehensible for those new to programming.


To run the language
1. Go to the same directory as main.cpp
2. <code> g++ -std=c++11 main.cpp -o exe.out && ./exe.out 'example_programs/filename.cui' </code>


Or

1. Go to the same directory as main.cpp
2. <code> ./cui.sh 'example_programs/filename.cui'</code>


Features
1. Variable declarations
2. Conditional statements (if-else)
4. Loops (while)
5. Data types: strings and floats
6. Prompt input directly from user interactively
7. Global State


Other
1. Recursive Descent Parsing Algorithm
2. Context Free Grammar translation scheme in <code> Parser.py </code>


## Main Components

### Scanner: Lexical Analysis
* Reads the input file char by char and forms the tokens
* Reads the input file char by char and forms the tokens
  
  
### Parser: Syntax Analysis
* Gets the tokens generated from the Scanner, and forms the <b> Syntax Tree </b>

### Syntax tree: Semantic Analysis
* Semantic checks are done after successful Parsing.
* Excetuion of he statements and expressions is made while Syntax Tree traversal.



## Language Grammar

<code>

  STATEMENT -> EXPRESSION_STATEMENT
  | IF_STATEMENT
  | WHILE_STATEMENT
  | PRINT_STATEMENT
  | INITIALIZATION_STATEMENT

  EXPRESSION_STATEMENT -> IDENTIFIER "=" TERM;

  IF_STATEMENT -> "if" (TERM) "ifbody" STATEMENT_LIST "else" "do" TERM "endif" ;
  | "if" (TERM) "ifbody" STATEMENT_LIST "endif" ;

  WHILE_STATEMENT -> "while" (TERM) "whilebody" STATEMENT_LIST "endwhile" ;

  PRINT_STATEMENT -> "print(TERM)" ;

  INITIALIZATION_STATEMENT -> "create" IDENTIFIER "=" TERM ;

  TERM -> FACTOR ( ( "+" | "-" ) FACTOR )* ;

  FACTOR -> UNARY ( ( "*" | "/" | "%" ) UNARY )* ;

  UNARY -> ( "not" | "-" ) LITERAL ;

  LITERAL -> NUMBER | STRING  ;

  VALID_CHAR -> "a" ... "z" | "A" ... "Z" | "_" ;

  DIGIT -> "0" ... "9" ;

  NUMBER -> DIGIT + ( "." (DIGIT)+ )? ;

  STRING -> "\"" <any char> "\"" // Any chars except '\' surroundedby ";

  IDENTIFIER -> VALID_CHAR | (VALID_CHAR | DIGIT) * ;

</code>

  
