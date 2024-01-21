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
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"IF");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("IF"); 
    yylval.symbVal = ch;
    return IF;
    }
"else" {
    logfile << "Line# " << line_count << ": Token <ELSE> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"ELSE");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("ELSE"); 
    yylval.symbVal = ch;
    return ELSE;
    }
"for" {
    logfile << "Line# " << line_count << ": Token <FOR> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"FOR");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("FOR"); 
    yylval.symbVal = ch;
    return FOR;
    }
"do" {
    logfile << "Line# " << line_count << ": Token <DO> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"DO");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("DO"); 
    yylval.symbVal = ch;
    return DO;
    }
"int" {
    logfile << "Line# " << line_count << ": Token <INT> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"INT");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("INT");  
    yylval.symbVal = ch;
    return INT;
    }
"float" {
    logfile << "Line# " << line_count << ": Token <FLOAT> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"FLOAT");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("FLOAT"); 
    yylval.symbVal = ch;
    return FLOAT;
    }
"void" {
    logfile << "Line# " << line_count << ": Token <VOID> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"VOID");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("VOID"); 
    yylval.symbVal = ch;
    return VOID;
    }
"while" {
    logfile << "Line# " << line_count << ": Token <WHILE> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"WHILE");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("WHILE"); 
    yylval.symbVal = ch;
    return WHILE;
    }		
"char" {
    logfile << "Line# " << line_count << ": Token <CHAR> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"CHAR");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    yylval.symbVal = ch;
    ch->node->setRule("CHAR");
    return CHAR;
    }
"double" {
    logfile << "Line# " << line_count << ": Token <DOUBLE> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"DOUBLE");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("DOUBLE");
    yylval.symbVal = ch;
    return DOUBLE;
    }		
"return" {
    logfile << "Line# " << line_count << ": Token <RETURN> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RETURN");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("RETURN");
    yylval.symbVal = ch;
    return RETURN;
    }
"continue" {
    logfile << "Line# " << line_count << ": Token <CONTINUE> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"CONTINUE");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("CONTINUE");
    yylval.symbVal = ch;
    return CONTINUE;
    }	

{ADDOP} {
    string curr(yytext); 
    SymbolInfo *symbol = new SymbolInfo(curr,"ADDOP");
    logfile << "Line# " << line_count << ": Token <ADDOP> Lexeme " << yytext << " found\n";
    symbol->node->setfirstLine(line_count);
    symbol->node->setlastLine(line_count);
    symbol->node->setRule("ADDOP");
    yylval.symbVal = symbol;  
    return ADDOP;  
}

{MULOP} {
    string curr(yytext); 
    SymbolInfo *symbol = new SymbolInfo(curr,"MULOP");
    logfile << "Line# " << line_count << ": Token <MULOP> Lexeme " << yytext << " found\n";
    symbol->node->setfirstLine(line_count);
    symbol->node->setlastLine(line_count); 
    symbol->node->setRule("MULOP");
    yylval.symbVal = symbol;
    return MULOP;  
}


{ID} {
    string curr(yytext);
    // cout << curr << "\n";  
    SymbolInfo *id = new SymbolInfo(curr,"ID");
    id->node->setfirstLine(line_count);
    id->node->setlastLine(line_count);
    id->node->setRule("ID"); 
    yylval.symbVal = id; 
    logfile << "Line# " << line_count << ": Token <ID> Lexeme " << curr << " found\n";
    return ID; 
}

{DIGIT}+ {
                string curr(yytext); 
                // cout << curr << "\n"; 
			    SymbolInfo *num =new SymbolInfo(curr,"CONST_INT"); 
                num->node->setfirstLine(line_count);
                num->node->setlastLine(line_count);
                num->node->setRule("CONST_INT"); 
                yylval.symbVal = num;  
                logfile << "Line# " << line_count << ": Token <CONST_INT> Lexeme " << yytext << " found\n";
                return CONST_INT;
		}
{const_float} {
                string curr(yytext); 
	            SymbolInfo *num =new SymbolInfo(curr,"CONST_FLOAT");
                num->node->setfirstLine(line_count);
                num->node->setlastLine(line_count); 
                num->node->setRule("CONST_FLOAT");
                yylval.symbVal = num; 
                logfile << "Line# " << line_count << ": Token <CONST_FLOAT> Lexeme " << yytext << " found\n";
                return CONST_FLOAT;
}


"&&"|"||" {
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"LOGICOP");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("LOGICOP");
    yylval.symbVal = ch;
    logfile << "Line# " << line_count << ": Token <LOGICOP> Lexeme " << yytext << " found\n";
    return LOGICOP;
}

"<"|">"|"<="|">="|"!=" {
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RELOP");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("RELOP");
    yylval.symbVal = ch;
    logfile << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
    return RELOP;
}

"--"|"++" {
    logfile << "Line# " << line_count << ": Token <INCOP> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"INCOP");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("INCOP"); 
    yylval.symbVal = ch;
    return INCOP;
    } 
"=" {
    logfile << "Line# " << line_count << ": Token <ASSIGNOP> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"ASSIGNOP");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("ASSIGNOP");
    yylval.symbVal = ch;
    return ASSIGNOP;
    }
"!" {
    logfile << "Line# " << line_count << ": Token <NOT> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"NOT");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("NOT");
    yylval.symbVal = ch;
    return NOT;
    }
"(" {
    logfile << "Line# " << line_count << ": Token <LPAREN> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"LPAREN");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("LPAREN");
    yylval.symbVal = ch;
    return LPAREN;
    }
")" {
    logfile << "Line# " << line_count << ": Token <RPAREN> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RPAREN");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("RPAREN");
    yylval.symbVal = ch;
    return RPAREN;
    }
"{" {
    logfile << "Line# " << line_count << ": Token <LCURL> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"LCURL");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count);
    ch->node->setRule("LCURL"); 
    yylval.symbVal = ch;
    return LCURL;
    }
"}" {
    logfile << "Line# " << line_count << ": Token <RCURL> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RCURL");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("RCURL");
    yylval.symbVal = ch;
    return RCURL;
    }
"[" {
    logfile << "Line# " << line_count << ": Token <LTHIRD> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"LTHIRD");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("LTHIRD");
    yylval.symbVal = ch;
    return LTHIRD;
    }
"]" {
    logfile << "Line# " << line_count << ": Token <RTHIRD> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"RTHIRD");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("RTHIRD");
    yylval.symbVal = ch;
    return RTHIRD;
    }
"," {
    logfile << "Line# " << line_count << ": Token <COMMA> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"COMMA");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("COMMA");
    yylval.symbVal = ch;
    return COMMA;
    }
";" {
    logfile << "Line# " << line_count << ": Token <SEMICOLON> Lexeme " << yytext << " found\n";
    string temp(yytext);
	SymbolInfo *ch = new SymbolInfo(temp, (string)"SEMICOLON");
    ch->node->setfirstLine(line_count);
    ch->node->setlastLine(line_count); 
    ch->node->setRule("SEMICOLON");
    yylval.symbVal = ch;
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
    yyterminate();  
}

%%
