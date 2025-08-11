%option noyywrap
%x string_state
%x first_line
%x multi_state1
%x multi_state2
%x multi_state_new
%x multi_state_new2

%x comment1
%x comment2
%x comment3
%x comment4
%x comment5

%x INDENT

%{
#include<bits/stdc++.h>
#include "2005018.h"
using namespace std;

int line_count = 1 ;
int error_count = 0;
int tabs = 0; 
int warning = 0;  

ofstream logout;
ofstream tokenout;
FILE *fin = NULL; 
SymbolTable table(10); 
string ans = ""; 
string log_ans= "";
string log_comm = ""; 

%}

LETTER [a-zA-Z]
DIGIT [0-9]
Newline [\n]
WHITESPACE [ \t\f\r\v]+
special_chars [\<\!\@\#\$\%\^\&\*\_\-\+\>\,\.\/\?\~\`\:\;\"\(\)\[\]\{\}]
character_literal ({LETTER}|\\n|\\t|\\\|\\'|\\a|\\f|\\r|\\b|\\v|\\0|{special_chars})
const_float -?({DIGIT}*)([.]{DIGIT}+)?([eE][+-]?{DIGIT}*)?
ID [a-zA-Z_][a-zA-Z0-9]*


%%



{Newline} {
	line_count++;
	BEGIN INDENT; 
}

^[\t]* {
	if(yyleng != 0){
		warning++; 
		logout << "Line# " << line_count << ": warning, " << tabs << " of tabs needed but got " << yyleng <<  " tabs.\n";
	}
}

^[\t ]* {
	logout << "Line# " << line_count << ": Warning, tab requrired but got space.\n";
	warning++; 
}

<INDENT>^[\t]* {
	string curr(yytext);
	if(tabs != curr.size()){
		logout << "Line# " << line_count << ": warning, " << tabs << " of tabs needed but got "<< curr.size()<<" tabs.\n"; 
		warning++; 
	} 
	BEGIN INITIAL; 
}

<INDENT>^[\t ]* {
	cout << "here"; 
	logout << "Line# " << line_count << ": Warning, tab requrired but got space.\n"; 
	warning++;  
	BEGIN INITIAL;
}

<INDENT>[^\t\n ] {
	if(yytext[0] == '}') {
		if(tabs) tabs--; 
	}
	unput(yytext[yyleng-1]);
	if(tabs != 0){
		logout << "Line# " << line_count << ": warning, " << tabs << " of tabs needed but got 0 tabs.\n";
		warning++; 
	} 
	BEGIN INITIAL; 
}

<INDENT>\n {
	line_count++; 
	BEGIN INDENT; 
}


"if"    {
            tokenout << "<IF, if>\n";
            logout << "Line# " << line_count << ": Token <IF> Lexeme " << yytext << " found\n";
        }

"else"  {
            tokenout << "<ELSE, else>\n";
            logout << "Line# " << line_count << ": Token <ELSE> Lexeme " << yytext << " found\n";
        }

"+"     |

"-"     {
            tokenout << "<ADDOP, " << yytext << ">\n";
            logout << "Line# " << line_count << ": Token <ADDOP> Lexeme " << yytext << " found\n";
        }


"for"	{
			tokenout << "<FOR, for>\n";
			logout << "Line# " << line_count << ": Token <FOR> Lexeme " << yytext << " found\n"; 
		}

"do"	{
			tokenout << "<DO, do>\n";
			logout << "Line# " << line_count << ": Token <DO> Lexeme " << yytext << " found\n"; 
		}

"int"	{
			tokenout << "<INT, int>\n";
			logout << "Line# " << line_count << ": Token <INT> Lexeme " << yytext << " found\n"; 
		}

"float"	{
			tokenout << "<FLOAT, float>\n";
			logout << "Line# " << line_count << ": Token <FLOAT> Lexeme " << yytext << " found\n"; 
		}

"void"	{
			tokenout << "<VOID, void>\n";
			logout << "Line# " << line_count << ": Token <VOID> Lexeme " << yytext << " found\n"; 
		}
"switch" {
			tokenout << "<SWITCH, switch>\n";
			logout << "Line# " << line_count << ": Token <SWITCH> Lexeme " << yytext << " found\n"; 
		}
"default"	{
			tokenout << "<DEFAULT, default>\n";
			logout << "Line# " << line_count << ": Token <DEFAULT> Lexeme " << yytext << " found\n"; 
		}
"while"	{
			tokenout << "<WHILE, while>\n";
			logout << "Line# " << line_count << ": Token <WHILE> Lexeme " << yytext << " found\n"; 
		}		
"break"	{
			tokenout << "<BREAK, break>\n";
			logout << "Line# " << line_count << ": Token <BREAK> Lexeme " << yytext << " found\n"; 
		}
"char"	{
			tokenout << "<CHAR, char>\n";
			logout << "Line# " << line_count << ": Token <CHAR> Lexeme " << yytext << " found\n"; 
		}
"double"	{
			tokenout << "<DOUBLE, double>\n";
			logout << "Line# " << line_count << ": Token <DOUBLE> Lexeme " << yytext << " found\n"; 
		}		
"return"	{
			tokenout << "<RETURN, return>\n";
			logout << "Line# " << line_count << ": Token <RETURN> Lexeme " << yytext << " found\n"; 
		}
"case"	{
			tokenout << "<CASE, case>\n";
			logout << "Line# " << line_count << ": Token <CASE> Lexeme " << yytext << " found\n"; 
		}
"continue"	{
			tokenout << "<CONTINUE, continue>\n";
			logout << "Line# " << line_count << ": Token <CONTINUE> Lexeme " << yytext << " found\n"; 
		}		


-?{DIGIT}+	{
			    tokenout << "<CONST_INT, " << yytext << ">\n";
                logout << "Line# " << line_count << ": Token <CONST_INT> Lexeme " << yytext << " found\n";
                // insert in symbol table and print symbol table content (only non-empty buckets)
		}	
{const_float} {
	tokenout << "<CONST_FLOAT, " << yytext << ">\n";
	logout << "Line# " << line_count << ": Token <CONST_FLOAT> Lexeme " << yytext << " found\n";
}

'{character_literal}' {
	string temp(yytext);
	char c ;
	if(temp[1] == '\\'){
		if(temp[2] == 't') c =  '\t'; 
		else if(temp[2] == 'n') c = '\n'; 
		else if(temp[2] == 'r') c = '\r'; 
		else if(temp[2] == 'b') c = '\b';
		else if(temp[2] == 'a') c = '\a';
		else if(temp[2] == 'v') c = '\v';
		else if(temp[2] == 'f') c = '\f';
		else if(temp[2] == '\'') c = '\'';
		else if(temp[2] == '\\') c = '\\';
	}  
	else c = temp[1];
	tokenout << "<CONST_CHAR, " << c << ">\n"; 
	logout << "Line# " << line_count << ": Token <CONST_CHAR> Lexeme " << c << " found\n";  
}
'' {
	logout << "Error at line# " << line_count << ": EMPTY_CONST_CHAR " << yytext << "\n";
	error_count++; 
}


[*/%] {
	tokenout << "<MULOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <MULOP> Lexeme " << yytext << " found\n"; 
}

"--" |

"++" {
	tokenout << "<INCOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <INCOP> Lexeme " << yytext << " found\n";
} 

"=" {
	tokenout << "<ASSIGNOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <ASSIGNOP> Lexeme " << yytext << " found\n";
}

"&&" | 
"||" {
	tokenout << "<LOGICOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <LOGICOP> Lexeme " << yytext << " found\n";
}

"!" {
	tokenout << "<NOT, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <NOT> Lexeme " << yytext << " found\n";
}

"(" {
	tokenout << "<LPAREN, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <LPAREN> Lexeme " << yytext << " found\n";
}

")" {
	tokenout << "<RPAREN, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RPAREN> Lexeme " << yytext << " found\n";
}

"{" {
	tokenout << "<LCURL, " << yytext << ">\n"; 
	table.EnterScope();
	tabs++; 
	logout << "Line# " << line_count << ": Token <LCURL> Lexeme " << yytext << " found\n";
}
"}" {
	tokenout << "<RCURL, " << yytext << ">\n";
	if(tabs) tabs--; 
	table.ExitScope(); 
	logout << "Line# " << line_count << ": Token <RCURL> Lexeme " << yytext << " found\n"; 
}
"[" {
	tokenout << "<LSQUARE, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <LSQUARE> Lexeme " << yytext << " found\n";
}

"]" {
	tokenout << "<RSQUARE, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RSQUARE> Lexeme " << yytext << " found\n";
}

"," {
	tokenout << "<COMMA, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <COMMA> Lexeme " << yytext << " found\n";
}

";" {
	tokenout << "<SEMICOLON, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <SEMICOLON> Lexeme " << yytext << " found\n";
}

"<<" {
	tokenout << "<BITOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <BITOP> Lexeme " << yytext << " found\n";
}

">>" {
	tokenout << "<BITOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <BITOP> Lexeme " << yytext << " found\n";
}

"^" {
	tokenout << "<BITOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <BITOP> Lexeme " << yytext << " found\n";
}

"<" {
	tokenout << "<RELOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
}
">" {
	tokenout << "<RELOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
}
"<=" {
	tokenout << "<RELOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
}
">=" {
	tokenout << "<RELOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
}
"!=" {
	tokenout << "<RELOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
}
"==" {
	tokenout << "<RELOP, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <RELOP> Lexeme " << yytext << " found\n";
}


{ID} {
	SymbolInfo *a = new SymbolInfo(yytext,"ID");
	int cnt = 0; 
	int ind; 
	int ok = table.Insert(a,cnt,ind);
	tokenout << "<ID, " << yytext << ">\n"; 
	logout << "Line# " << line_count << ": Token <ID> Lexeme " << yytext << " found\n";
	if(ok) table.PrintAllScopeTables(logout);
	else{
		logout << "	" << yytext << " already exists in the current ScopeTable\n"; 
	}
}


\" {
	string curr(yytext);
	log_ans += curr;
	ans += curr;  
	BEGIN string_state;
}

<string_state>([^\n\\\"]|(\\t))* {
	string curr(yytext); 
	ans += curr;
	log_ans += curr; 
	BEGIN first_line;
}

<string_state>[\\]+ {
	string curr(yytext); 
	log_ans += curr; 
	BEGIN multi_state_new;
}

<string_state>\" {
	cout << "Single lined string.\n"; 
	tokenout << "<SINGLE LINE STRING, ";
	for(int i =0 ; i < ans.size();){
		if(ans[i] == '\\' && ans[i+1] == 't') { tokenout << "	"; i+=2; } 
		else { tokenout << ans[i]; ++i; } 
	}
	tokenout << ">\n"; 
	log_ans += '"';
	logout << "Line# " << line_count << ": Token <SINGLE LINE STRING> Lexeme " << log_ans << " found\n"; 
	ans = "";
	log_ans = ""; 
	BEGIN INITIAL;
}

<string_state><<EOF>> {
	cout << "Unfinished string.\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = ""; 
	line_count++; 
	error_count++; 
	BEGIN INITIAL;
}

<first_line>[\\]+ {
	string curr(yytext); 
	log_ans += curr; 
	BEGIN multi_state_new; 
}

<first_line>\" {
	cout << "Single lined string.\n"; 
	tokenout << "<SINGLE LINE STRING, ";
	for(int i =0 ; i < ans.size();){
		if(ans[i] == '\\' && ans[i+1] == 't') { tokenout << "	"; i+=2; } 
		else { tokenout << ans[i]; ++i; } 
	}
	tokenout << ">\n"; 
	log_ans += '"';
	logout << "Line# " << line_count << ": Token <SINGLE LINE STRING> Lexeme " << log_ans << " found\n"; 
	ans = "";  
	log_ans = ""; 
	BEGIN INITIAL;
}

<first_line>\n {
	cout << "Unfinished string.\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = ""; 
	line_count++;  
	error_count++; 
	BEGIN INDENT;
}

<first_line><<EOF>> {
	cout << "Unfinished string.\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = ""; 
	line_count++; 
	error_count++; 
	BEGIN INITIAL;
}


<multi_state_new>\n { 
	line_count++;
	log_ans += '\n'; 
	BEGIN multi_state1; 
}

<multi_state_new><<EOF>> {
	cout << "Unfinished string.\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = ""; 
	line_count++; 
	error_count++; 
	BEGIN INITIAL;
}

<multi_state_new2>\n {
	line_count++;
	log_ans += '\n'; 
	BEGIN multi_state1; 
}

<multi_state_new2><<EOF>> {
	cout << "Unfinished string.\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = ""; 
	line_count++; 
	error_count++; 
	BEGIN INITIAL;
}

<multi_state1>([^\n\\\"]|(\\t))* {
	string curr(yytext); 
	ans += curr;
	log_ans+= curr;   
	BEGIN multi_state2;
}

<multi_state2>[\\]+ {
	string curr(yytext); 
	log_ans += curr;  
	BEGIN multi_state_new2;
}

<multi_state2>\n {
	cout << "Unfinished string.\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = ""; 
	line_count++; 
	error_count++;  
	BEGIN INDENT;
}

<multi_state2>\" {   
	cout << ans << "\n"; 
	cout << log_ans << "\n";
	log_ans += '"'; 
	int tot_new = 0;
	for(auto ch: log_ans){
		if(ch == '\n' ) tot_new++ ; 
	}
	tokenout<< "<MULTI LINE STRING, " << ans << ">\n";  
	logout << "Line# " << line_count - tot_new << ": Token <MULTI LINE STRING> Lexeme " << log_ans << " found\n";
	ans = ""; 
	log_ans = "";
	BEGIN INITIAL; 
}

<multi_state2><<EOF>> {
	cout << "Unfinished String.\n";
	ans = "";
	log_ans = "";
	logout << "Error at line# " << line_count << ": UNFINISHED_STRING " << log_ans << "\n"; 
	log_ans = ""; 
	ans = "";
	error_count++; 
	BEGIN INITIAL;
}

\/\*([^\/])*\*\/ { 
	cout << "A multiline comment found.\n";
	cout << yytext << "\n";  
	logout << "Line# " << line_count << ": Token <MULTI LINE COMMENT> Lexeme " << yytext << " found\n";
	for(int i =0 ; yytext[i] != '\0'; ++i ){
		if(yytext[i] == '\n') line_count++; 
	}
}

\/\*([^\/])* {
	cout << "Unfinished comment. Asterisk version.\n"; 
	cout << yytext << "\n"; 
	for(int i =0 ; yytext[i] != '\0'; ++i ){
		if(yytext[i] == '\n') line_count++; 
	}
	logout << "Error at line# " << line_count << ": UNFINISHED_COMMENT " << yytext << "\n";
	error_count++; 
}

\/\/ {
	string curr(yytext); 
	log_comm += curr;   
	BEGIN comment1; 
}  

<comment1>([^\n\\]|(\\t))* {
	string curr(yytext); 
	log_comm += curr;
	BEGIN comment2;
}

<comment2>\n {
	cout << log_comm << "\n";
	if(log_comm.size() != 0 ) log_comm.pop_back();  
	logout << "Line# " << line_count << ": Token <SINGLE LINE COMMENT> Lexeme " << log_comm << " found\n";
	line_count++; 
	log_comm = "";
	BEGIN INDENT; 
}

<comment2><<EOF>> {
	if(log_comm.size() != 0 ) log_comm.pop_back();
	logout << "Line# " << line_count << ": Token <SINGLE LINE COMMENT> Lexeme " << log_comm << " found\n"; 
	log_comm = "";  
	BEGIN INITIAL; 
}


<comment2>\\ {
	log_comm += '\\';  
	BEGIN comment3;
}

<comment3>\n {
	log_comm += '\n';
	line_count++; 
	BEGIN comment4;
}

<comment4>([^\n\\]|(\\t))* {
	string curr(yytext);
	log_comm += curr; 
	BEGIN comment5;
}

<comment5>\\ {
	log_comm += '\\'; 
	BEGIN comment3;
}

<comment5><<EOF>> {
	if(log_comm.size() != 0 ) log_comm.pop_back(); 
	logout << "Line# " << line_count << ": Token <SINGLE LINE COMMENT> Lexeme " << log_comm << " found" << endl;
	log_comm = "" ;
	BEGIN INITIAL; 
}

<comment5>\n {
	if(log_comm.size() != 0 ) log_comm.pop_back();
	int tot_new = 0; 
	for(auto ch : log_comm){
		if( ch == '\n') tot_new++; 
	} 
	logout << "Line# " << line_count - tot_new << ": Token <SINGLE LINE COMMENT> Lexeme " << log_comm << " found" << endl ;
	line_count++; 
	log_comm = ""; 
	BEGIN INDENT;
}

({DIGIT}+\.) {
	string curr(yytext);
	curr.pop_back(); 
	tokenout << "<CONST_INT, " << curr << ">\n";
	logout << "Line# " << line_count << ": Token <CONST_INT> Lexeme " << curr << " found\n";
}


({DIGIT}?\.)+{const_float} {
	cout << "Redundant decimal points.\n"; 
	cout << yytext << "\n"; 
	logout << "Error at line# " << line_count << ": TOO_MANY_DECIMAL_POINTS " << yytext << "\n";
	error_count++;  
}

{const_float}\.{DIGIT}* {
	cout << "Ill-formed number: ";
	cout << yytext << "\n"; 
	logout << "Error at line# " << line_count << ": ILLFORMED_NUMBER " << yytext << "\n";
	error_count++; 
}


'[^\'\n][^\'\n]+' {
	cout << "Multiple characters in character literal.\n";
	cout << yytext << "\n";  
	logout << "Error at line# " << line_count << ": MULTICHAR_CONST_CHAR " << yytext << "\n";
	error_count++; 
}

'([^'\n]*|(\\\')) {
	cout << "Unfinished character literal.\n";
	cout << yytext << "\n"; 
	logout << "Error at line# " << line_count << ": UNFINISHED_CONST_CHAR " << yytext << "\n";
	error_count++; 
	cout << "err " << error_count << "Line : " << line_count << "\n" ;
}

"\\" {
	cout << "Unrecognized character literal.\n"; 
	logout << "Error at line# " << line_count << ": UNRECOGNIZED_CHAR " << yytext << "\n";
	error_count++; 
}

"@" {
	cout << "Unrecognized character literal.\n"; 
	logout << "Error at line# " << line_count << ": UNRECOGNIZED_CHAR " << yytext << "\n";
	error_count++; 
}

"#" {
	cout << "Unrecognized character literal.\n"; 
	logout << "Error at line# " << line_count << ": UNRECOGNIZED_CHAR " << yytext << "\n";
	error_count++; 
}

"$" {
	cout << "Unrecognized character literal.\n"; 
	logout << "Error at line# " << line_count << ": UNRECOGNIZED_CHAR " << yytext << "\n";
	error_count++; 
}

(-?{DIGIT}+|-?{DIGIT}*\.{DIGIT}*){ID} {
	logout << "Error at line# " << line_count << ": INVALID_ID_SUFFIX_NUM_PREFIX " << yytext << "\n";
	error_count++; 
}


<<EOF>> {
	table.PrintAllScopeTables(logout);
	logout << "Total lines: " << line_count << "\n"; 
	logout << "Total errors: " << error_count << "\n"; 
	logout << "Total warnings: " << warning << "\n"; 
	exit(0); 
}


%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout.open("2005018_log.txt");
	tokenout.open("2005018_token.txt");
	table.EnterScope(); 
	yyin= fin;
	yylex();
	fclose(yyin); 
	logout.close(); 
	tokenout.close(); 
	return 0;
}
