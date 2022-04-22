#include <vector>
using namespace std;

enum TokenType  {

    PROGRAM,    //                program
    ENDPROGRAM, //                endprogram

    BEGIN, //                     begin
    END, //                       end

    TERMINATE_TOKEN, 

    COLON, //                     :
    SEMICOLON, //                 ;
    COMMA, //                     ,

    PLUS, //                      + 
    MINUS, //                     -
    ASTERIX, //                   *
    DIVIDE, //                    /  
    MOD, //                       %
    EQUAL, //                     =

    CREATE, //                    create
    PRINT, //                     print

    // Literals
    IDENTIFIER, //                identifiers
    OPEN_BRACKET, //              (
    CLOSING_BRACKET, //           )
    SQUARE_OPEN_BRACKET, //       [ 
    SQUARE_CLOSING_BRACKET, //    ]
    NUMBER, //                    numbers
    STRING, //                    strings

    // KEYWORDS
    IF,   //                      if
    IFBODY,  //                   ifbody
    ELSE,  //                     else
    DO,  //                       do
    ENDIF, //                     endif
    WHILE, //                     while

    WHILEBODY, //                 whilebody
    ENDWHILE, //                  endwhile

    AND, //                       and
    OR, //                        or
    RET, //                       ret
    NOT, //                       not

    END_OF_FILE,

};


vector<string> type_name(1000);
void init_types(){
    type_name[PROGRAM] = "PROGRAM";
    type_name[ENDPROGRAM] = "ENDPROGRAM";
    type_name[BEGIN] = "BEGIN";
    type_name[END] = "END";
    type_name[TERMINATE_TOKEN] = "TERMINATE_TOKEN";
    type_name[COLON] = "COLON";
    type_name[SEMICOLON] = "SEMICOLON";
    type_name[PLUS] = "PLUS";
    type_name[MINUS] = "MINUS";
    type_name[ASTERIX] = "ASTERIX";
    type_name[DIVIDE] = "DIVIDE";
    type_name[MOD] = "MOD";
    type_name[EQUAL] = "EQUAL";
    type_name[IDENTIFIER] = "IDENTIFIER";
    type_name[OPEN_BRACKET] = "OPEN_BRACKET";
    type_name[CLOSING_BRACKET] = "CLOSING_BRACKET";
    type_name[SQUARE_OPEN_BRACKET] = "SQUARE_OPEN_BRACKET";
    type_name[SQUARE_CLOSING_BRACKET] = "SQUARE_CLOSING_BRACKET";

    type_name[CREATE] = "CREATE";
    type_name[PRINT] = "PRINT";

    type_name[NUMBER] = "NUMBER";
    type_name[STRING] = "STRING";

    type_name[IF] = "IF";
    type_name[IFBODY] = "IFBODY";
    type_name[ELSE] = "ELSE";
    type_name[DO] = "DO";
    type_name[ENDIF] = "ENDIF";
    type_name[WHILE] = "WHILE";
    type_name[WHILEBODY] = "WHILEBODY";
    type_name[ENDWHILE] = "ENDWHILE";

    type_name[AND] = "AND";
    type_name[OR] = "OR";
    type_name[RET] = "RET";
    type_name[NOT] = "NOT";
    type_name[END_OF_FILE] = "END_OF_FILE";
}
