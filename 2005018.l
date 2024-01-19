%option noyywrap

%{
#include<bits/stdc++.h>
#include "2005018.h"
#include"y.tab.h" 
using namespace std;

int line_count = 1,err_count = 0;  

%}

LETTER [a-zA-Z]
DIGIT [0-9]
Newline [\n]
WHITESPACE [ \t\f\r\v]+
special_chars [\<\!\@\#\$\%\^\&\*\_\-\+\>\,\.\/\?\~\`\:\;\"\(\)\[\]\{\}]
character_literal ({LETTER}|\\n|\\t|\\\|\\'|\\a|\\f|\\r|\\b|\\v|\\0|{special_chars})
const_float -?({DIGIT}*)([.]{DIGIT}+)?([eE][+-]?{DIGIT}*)?
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

"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"do" {return DO;}
"int" {return INT;}
"float" {return FLOAT;}
"void" {return VOID;}
"while" {return WHILE;}		
"char" {return CHAR;}
"double" {return DOUBLE;}		
"return" {return RETURN;}
"continue" {return CONTINUE;}	

{ADDOP} {
    string curr(yytext); 
    SymbolInfo *symbol = new SymbolInfo(curr,"ADDOP");
    yylval.symbVal = symbol; 
    return ADDOP;  
}

{MULOP} {
    string curr(yytext); 
    SymbolInfo *symbol = new SymbolInfo(curr,"MULOP"); 
    yylval.symbVal = symbol;
    return MULOP;  
}


{ID} {
    string curr(yytext);
    // cout << curr << "\n";  
    SymbolInfo *id = new SymbolInfo(curr,"ID");
    yylval.symbVal = id; 
    return ID; 
}

-?{DIGIT}+ {
                string curr(yytext); 
                // cout << curr << "\n"; 
			    SymbolInfo *num =new SymbolInfo(curr,"CONST_INT"); 
                yylval.symbVal = num; 
                return CONST_INT;
		}
{const_float} {
                string curr(yytext); 
	            SymbolInfo *num =new SymbolInfo(curr,"CONST_FLOAT"); 
                yylval.symbVal = num; 
                return CONST_FLOAT;
}


"&&"|"||" {
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"LOGICOP");
    return LOGICOP;
}

"<"|">"|"<="|">="|"!=" {
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RELOP");
    return RELOP;
}

"--"|"++" {return INCOP;} 
"=" {return ASSIGNOP;}
"!" {return NOT;}
"(" {return LPAREN;}
")" {return RPAREN;}
"{" {return LCURL;}
"}" {return RCURL;}
"[" {return LTHIRD;}
"]" {return RTHIRD;}
"," {return COMMA;}
";" {return SEMICOLON;}


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
