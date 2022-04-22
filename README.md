# CUI-LANGUAGE
Simple programming laguage implemented in C++

> This language is open to extensions and adding more features. The goal is to make a dead-simple programming language comprehensible for those new to programming.


To run the language
1. Go to the same directory as main.cpp
2. <code> g++ -std=c++11 main.cpp -o exe && ./exe 'filename.cui' </code>


Or

1. Go to the same directory as main.cpp
2. <code> ./cui.sh 'filename.cui'</code>


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




  
