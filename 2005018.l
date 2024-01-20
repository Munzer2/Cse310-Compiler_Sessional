%option noyywrap

%{
#include<bits/stdc++.h>
#include "2005018.h"
#include"y.tab.h" 
using namespace std;

int line_count = 1,err_count = 0;  
extern ofstream logfile; 

%}

LETTER [a-zA-Z]
DIGIT [0-9]
Newline [\n]
WHITESPACE [ \t\f\r\v]+
special_chars [\<\!\@\#\$\%\^\&\*\_\-\+\>\,\.\/\?\~\`\:\;\"\(\)\[\]\{\}]
character_literal ({LETTER}|\\n|\\t|\\\|\\'|\\a|\\f|\\r|\\b|\\v|\\0|{special_chars})
const_float ({DIGIT}*)([.]{DIGIT}+)?([eE][+-]?{DIGIT}*)?
ID [a-zA-Z_][a-zA-Z_0-9]*
ADDOP [+-]
MULOP [*/%] 
IllFormedNum {const_float}\.{DIGIT}*
MultiCharConst '[^\'\n][^\'\n]+' 
UnfinishedChar '([^'\n]|(\\\')) 
Invalid_suffixID_Prenum (-?{DIGIT}+|-?{DIGIT}*\.{DIGIT}*){ID}
RedundantDec ({DIGIT}?\.)+{const_float}

%%


{WHITESPACE} {}
{Newline} {
	line_count++; 
}

"if" {
    logfile << "Line# " << line_count << ": Token <IF> Lexeme " << yytext << " found\n";
    return IF;
    }
"else" {
    logfile << "Line# " << line_count << ": Token <ELSE> Lexeme " << yytext << " found\n";
    return ELSE;
    }
"for" {
    logfile << "Line# " << line_count << ": Token <FOR> Lexeme " << yytext << " found\n";
    return FOR;
    }
"do" {
    logfile << "Line# " << line_count << ": Token <DO> Lexeme " << yytext << " found\n";
    return DO;
    }
"int" {
    logfile << "Line# " << line_count << ": Token <INT> Lexeme " << yytext << " found\n";
    return INT;
    }
"float" {
    logfile << "Line# " << line_count << ": Token <FLOAT> Lexeme " << yytext << " found\n";
    return FLOAT;
    }
"void" {
    logfile << "Line# " << line_count << ": Token <VOID> Lexeme " << yytext << " found\n";
    return VOID;
    }
"while" {
    logfile << "Line# " << line_count << ": Token <WHILE> Lexeme " << yytext << " found\n";
    return WHILE;
    }		
"char" {
    logfile << "Line# " << line_count << ": Token <CHAR> Lexeme " << yytext << " found\n";
    return CHAR;
    }
"double" {
    logfile << "Line# " << line_count << ": Token <DOUBLE> Lexeme " << yytext << " found\n";
    return DOUBLE;
    }		
"return" {
    logfile << "Line# " << line_count << ": Token <RETURN> Lexeme " << yytext << " found\n";
    return RETURN;
    }
"continue" {
    logfile << "Line# " << line_count << ": Token <CONTINUE> Lexeme " << yytext << " found\n";
    return CONTINUE;
    }	

{ADDOP} {
    string curr(yytext); 
    SymbolInfo *symbol = new SymbolInfo(curr,"ADDOP");
    logfile << "Line# " << line_count << ": Token <ADDOP> Lexeme " << yytext << " found\n";
    yylval.symbVal = symbol; 
    return ADDOP;  
}

{MULOP} {
    string curr(yytext); 
    SymbolInfo *symbol = new SymbolInfo(curr,"MULOP");
    logfile << "Line# " << line_count << ": Token <MULOP> Lexeme " << yytext << " found\n"; 
    yylval.symbVal = symbol;
    return MULOP;  
}


{ID} {
    string curr(yytext);
    // cout << curr << "\n";  
    SymbolInfo *id = new SymbolInfo(curr,"ID");
    yylval.symbVal = id; 
    logfile << "Line# " << line_count << ": Token <ID> Lexeme " << curr << " found\n";
    return ID; 
}

{DIGIT}+ {
                string curr(yytext); 
                // cout << curr << "\n"; 
			    SymbolInfo *num =new SymbolInfo(curr,"CONST_INT"); 
                yylval.symbVal = num; 
                logfile << "Line# " << line_count << ": Token <CONST_INT> Lexeme " << yytext << " found\n";
                return CONST_INT;
		}
{const_float} {
                string curr(yytext); 
	            SymbolInfo *num =new SymbolInfo(curr,"CONST_FLOAT"); 
                yylval.symbVal = num; 
                logfile << "Line# " << line_count << ": Token <CONST_FLOAT> Lexeme " << yytext << " found\n";
                return CONST_FLOAT;
}


"&&"|"||" {
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"LOGICOP");
    logfile << "Line# " << line_count << ": Token <LOGICOP> Lexeme " << yytext << " found\n";
    return LOGICOP;
}

"<"|">"|"<="|">="|"!=" {
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RELOP");
    logfile << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
    return RELOP;
}

"--"|"++" {
    logfile << "Line# " << line_count << ": Token <INCOP> Lexeme " << yytext << " found\n";
    return INCOP;
    } 
"=" {
    logfile << "Line# " << line_count << ": Token <ASSIGNOP> Lexeme " << yytext << " found\n";
    return ASSIGNOP;
    }
"!" {
    logfile << "Line# " << line_count << ": Token <NOT> Lexeme " << yytext << " found\n";
    return NOT;
    }
"(" {
    logfile << "Line# " << line_count << ": Token <LPAREN> Lexeme " << yytext << " found\n";
    return LPAREN;
    }
")" {
    logfile << "Line# " << line_count << ": Token <RPAREN> Lexeme " << yytext << " found\n";
    return RPAREN;
    }
"{" {
    logfile << "Line# " << line_count << ": Token <LCURL> Lexeme " << yytext << " found\n";
    return LCURL;
    }
"}" {
    logfile << "Line# " << line_count << ": Token <RCURL> Lexeme " << yytext << " found\n";
    return RCURL;
    }
"[" {
    logfile << "Line# " << line_count << ": Token <LTHIRD> Lexeme " << yytext << " found\n";
    return LTHIRD;
    }
"]" {
    logfile << "Line# " << line_count << ": Token <RTHIRD> Lexeme " << yytext << " found\n";
    return RTHIRD;
    }
"," {
    logfile << "Line# " << line_count << ": Token <COMMA> Lexeme " << yytext << " found\n";
    return COMMA;
    }
";" {
    logfile << "Line# " << line_count << ": Token <SEMICOLON> Lexeme " << yytext << " found\n";
    return SEMICOLON;
    }


'' {
    err_count++; 
}

{RedundantDec} {
    err_count++;  
}

{IllFormedNum} {
    err_count++; 
}

{MultiCharConst} {
    err_count++; 
}

{UnfinishedChar} {
    err_count++; 
}

{Invalid_suffixID_Prenum} {
    err_count++; 
}

. {
    err_count++; 
}

<<EOF>> { 
	exit(0); 
}

%%
