%{
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <limits>
#include "2005018.h"
//#define YYSTYPE SymbolInfo*
#define pb(x) push_back(x)

using namespace std; 

int yyparse(void);  
int yylex(void);

extern FILE *yyin;
extern int line_count; 
int err_sem = 0;

SymbolTable table(11); 

string var_type = "";

ofstream logfile,errf;

vector<SymbolInfo*> params;
vector<string>function_arg_types; 
int args_ID_cnt = 0;   

void yyerror(const char *s){
    cout << "Error: " << s << "\n"; 
    cout << line_count << "\n";  
}
%}

%union{
    SymbolInfo* symbVal;
}

%token IF ELSE FOR WHILE DO CONTINUE INT FLOAT CHAR DOUBLE VOID RETURN INCOP DECOP ASSIGNOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD SEMICOLON COMMA NOT PRINTLN
%token <symbVal> CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP ID
%type <symbVal> term unary_expression factor variable type_specifier expression logic_expression rel_expression simple_expression


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* For errors checking */
%error-verbose


%%

start: program
		{
			logfile << "start : program\n"; 
		}
		;

program : program unit
{
    logfile << "program : program unit\n"; 
    logfile << "start : program\n";
    logfile << "Total lines: " << line_count << "\n"; 
    logfile << "Total Errors: " << err_sem << "\n"; 
}
| unit
{
    logfile << "program : unit\n";
}
;
unit : var_declaration
        {
            logfile << "unit  : var_declaration\n"; 
        }
        | func_declaration
        {
            logfile << "unit : func_declaration\n";
        }
        | func_definition
        {
            logfile << "unit : func_definition\n";
        }
        ;
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
                    {
                        logfile << "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n";
                        string nameID = $2->getname();
                        string IDtype = "FUNC";     
                        SymbolInfo *check = table.LookUp2(nameID,IDtype);
                        if(check){
                            errf << "Line# " << line_count << ": Function '"<< nameID <<"' already declared\n"; 
                            err_sem++; 
                        }
                        else{
                            //This section is for ID which is of type 'FUNC. It has a vector that stores function argtypes. 
                            SymbolInfo *newSymb = new SymbolInfo(nameID,"ID");
                            newSymb->setIDType("FUNC");
                            newSymb->setFuncRet($1->getVarType()); 
                            for(int i =0 ; i < function_arg_types.size(); ++i ){
                                newSymb->push_params(function_arg_types[i]); 
                            }
                            table.Insert(newSymb); 
                            function_arg_types.clear(); 
                        }
                    }
                    | type_specifier ID LPAREN RPAREN SEMICOLON
                    {
                        logfile << "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n";
                        string nameID = $2->getname();
                        string IDtype = "FUNC";     
                        SymbolInfo *check = table.LookUp2(nameID,IDtype);
                        if(check){
                            errf << "Line# " << line_count << ": Function '"<< nameID <<"' already declared\n"; 
                            err_sem++; 
                        }
                        else{
                            //This section is for ID which is of type 'FUNC. It has a vector that stores function argtypes. 
                            SymbolInfo *newSymb = new SymbolInfo(nameID,"ID");
                            newSymb->setIDType("FUNC");
                            newSymb->setFuncRet($1->getVarType()); 
                            table.Insert(newSymb); 
                            function_arg_types.clear(); 
                        }
                    }
                    | type_specifier ID LPAREN error
                    {
                        errf << "Line# " << line_count << ": Syntax error at parameter list of function definition\n"; 
                    }
                    ;
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
                {
                    logfile << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n";
                    string nameID = $2->getname(), IDtype = "FUNC";
                    string typeOfFunc = $1->getVarType();   

                    SymbolInfo *curr = table.LookUp2(nameID, IDtype); 
                    if(curr){
                        if(curr->isFuncDefined()){
                            err_sem++; 
                            cout << "Error at line "<<  line_count << "Function "<< nameID <<" already defined\n";
                        }
                        else if(curr->getFuncRet() != typeOfFunc){
                            err_sem++; 
                            cout << "Error at line "<<  line_count << "Function "<< nameID << " :return type does not match declaration\n";
                        }
                        else if(curr->List_params.size() != function_arg_types.size()){
                            err_sem++; 
                            cout << "Error at line "<<  line_count << "Function " << nameID <<  " :parameter list does not match declaration\n";
                        }
                        else{
                            for(int i = 0; i < curr->List_params.size(); ++i ){
                                if( curr->List_params[i] != function_arg_types[i]){
                                    err_sem++; 
                                    cout << "Error at line " << line_count << "Function "<< nameID << " :argument mismatch\n"; 
                                    break; 
                                }
                            }
                        }
                    }
                    else{
                        SymbolInfo *newSymb = new SymbolInfo(nameID, "ID");
                        newSymb->setFuncDefined(); 
                        newSymb->setIDType("FUNC");
                        newSymb->setFuncRet(typeOfFunc); 
                        for(int i =0; i <  function_arg_types.size(); ++i){
                            newSymb->push_params(function_arg_types[i]);
                        }
                        table.Insert(newSymb);
                    } 
                    args_ID_cnt =0;
                    function_arg_types.clear(); 
                }
                | type_specifier ID LPAREN RPAREN compound_statement
                {
                    logfile << "func_definition : type_specifier ID LPAREN RPAREN compound_statement\n";
                    string nameID = $2->getname(), IDtype = "FUNC";
                    string typeOfFunc = $1->getVarType();   

                    SymbolInfo *curr = table.LookUp2(nameID, IDtype); 
                    if(curr){
                        if(curr->isFuncDefined()){
                            err_sem++; 
                            errf << "Line# "<<  line_count << ": Function '"<< nameID <<"'' already defined\n";
                        }
                        else if(curr->getFuncRet() != typeOfFunc){
                            err_sem++; 
                            cout << "Line# "<<  line_count << ": Function return type does not match declaration\n";
                        }
                        else if(curr->List_params.size() != function_arg_types.size()){
                            err_sem++; 
                            cout << "Line# " <<  line_count << "Function parameter list does not match declaration\n";
                        }
                    }
                    else{
                        SymbolInfo *newSymb = new SymbolInfo(nameID, "ID");
                        newSymb->setFuncDefined(); 
                        newSymb->setIDType("FUNC");
                        newSymb->setFuncRet(typeOfFunc); 
                        table.Insert(newSymb);
                    } 
                    args_ID_cnt =0;
                    function_arg_types.clear();
                }
                ;
parameter_list : parameter_list COMMA type_specifier ID
                {
                    logfile << "parameter_list  : parameter_list COMMA type_specifier ID\n";
                    string nameID = $4->getname(); 
                    //This one is from $3
                    function_arg_types.pb(var_type);
                    args_ID_cnt++; 
                    //also from $3
                    $4->setVarType(var_type);
                    $4->setIDType("VAR");
                    params.push_back($4);                     
                }
                | parameter_list COMMA type_specifier
                { 
                    logfile << "parameter_list  : parameter_list COMMA type_specifier\n";
                    function_arg_types.pb($3->getVarType()); 
                }
                | type_specifier ID
                {
                    logfile << "parameter_list  : type_specifier ID\n";
                    string nameID = $2->getname();
                    string IDtype = "VAR";  

                    function_arg_types.pb(var_type); 
                    args_ID_cnt++; 

                    params.push_back($2);
                    $2->setIDType("VAR");//VAR,FUNC etc. 
                    $2->setVarType(var_type);//This is type of ID. 
                }
                | type_specifier
                {
                    logfile << "parameter_list  : type_specifier\n";
                    function_arg_types.pb(var_type);
                }
                ;
compound_statement : LCURL
                {
                    table.EnterScope(); 
                    for(int i =0 ; i < params.size(); ++i) table.Insert(params[i]);
                    params.clear(); 
                } statements {   } RCURL { }
                {
                    logfile << "compound_statement : LCURL statements RCURL\n";
                    table.PrintAllScopeTables(logfile);
                    table.ExitScope();    
                }
                | LCURL RCURL
                {
                    logfile << "compound_statement : LCURL RCURL\n";
                }
                ;
var_declaration : type_specifier declaration_list SEMICOLON
                {
                    logfile << "var_declaration : type_specifier declaration_list SEMICOLON\n";
                }
                | type_specifier error SEMICOLON
                {
                    errf << "Line# " << line_count << ": Syntax error at declaration list of variable declaration\n"; 
                }
                ;
type_specifier : INT
                {
                    logfile << "type_specifier  : INT\n";
                    var_type = "INT";
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    $$ = symb;  
                }
                | FLOAT
                {
                    logfile << "type_specifier  : FLOAT\n";
                    var_type = "FLOAT";
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    $$ = symb; 
                }
                | VOID
                {
                    logfile << "type_specifier  : VOID\n";
                    var_type = "VOID"; 
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    $$ = symb;
                }
                ;
declaration_list : declaration_list COMMA ID
                {
                    logfile << "declaration_list : declaration_list COMMA ID\n"; 
                    string nameID = $3->getname();
                    string IDtype = "VAR"; 
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": variable cant be void\n"; 
                    }
                    else{
                        if( table.LookUp2(nameID,IDtype) ){
                            err_sem++;
                            errf << "Line# " << line_count << ": variable '" << nameID << "' already declared\n";
                        }
                        else{
                            SymbolInfo *varID = new SymbolInfo(nameID,$3->gettype()); 
                            varID->setIDType("VAR"); 
                            varID->setVarType(var_type); 
                            table.Insert(varID);
                        }
                    }
                }
                | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
                {
                    logfile << "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n";
                    string nameID = $3->getname(), arr_sz_str = $5->getname(); 
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": array type cannot be void\n"; 
                    }
                    else{
                        int array_sz = stoi(arr_sz_str); 
                        SymbolInfo *arrID = new SymbolInfo(nameID,$5->gettype()); 
                        arrID->setIDType("ARA"); 
                        arrID->setVarType(var_type); 
                        arrID->setArraySize(array_sz); 
                        if(var_type == "INT"){
                            for(int i = arrID->all_ints.size(); i < array_sz; ++i ) arrID->all_ints.pb(0);  
                        }
                        else if(var_type == "FLOAT"){
                            for(int i = arrID->all_floats.size() ; i < array_sz; ++i ) arrID->all_floats.pb(0);
                        }
                        table.Insert(arrID); 
                    }
                }
                | ID
                {
                    logfile << "declaration_list : ID\n";
                    string nameID = $1->getname(); 
                    string IDtype =  "VAR"; 
                    if( var_type ==  "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": variable cant be void\n";
                    }
                    else{
                        if( table.LookUp2(nameID,IDtype) ){
                            err_sem++; 
                            errf << "Line# " << line_count << ": variable '" << nameID <<  "' already declared\n";
                        }
                        else{
                            SymbolInfo *varID = new SymbolInfo(nameID,$1->gettype()); 
                            varID->setIDType("VAR"); 
                            varID->setVarType(var_type); 
                            table.Insert(varID);
                        }
                    }
                }
                | ID LTHIRD CONST_INT RTHIRD
                {
                    logfile << "declaration_list : ID LTHIRD CONST_INT RTHIRD\n";
                    string nameID = $1->getname(), arr_sz_str = $3->getname();    
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": array type cannot be void\n";
                    }
                    else{
                        int array_sz = stoi(arr_sz_str); 
                        SymbolInfo *arrID = new SymbolInfo(nameID,$3->gettype()); 
                        arrID->setIDType("ARA"); 
                        arrID->setVarType(var_type); 
                        arrID->setArraySize(array_sz); 
                        if(var_type == "INT"){
                            for(int i = arrID->all_ints.size(); i < array_sz; ++i ) arrID->all_ints.pb(0);  
                        }
                        else if(var_type == "FLOAT"){
                            for(int i = arrID->all_floats.size() ; i < array_sz; ++i ) arrID->all_floats.pb(0);
                        }
                        table.Insert(arrID); 
                    }
                }
                ;
statements : statement
            {
                logfile << "statements : statement\n";
            }
            | statements statement
            {
                logfile << "statements : statements statement\n";
            }
            ;
statement : var_declaration
            {
                logfile << "statement : var declaration\n";
            }
            | expression_statement
            {
                logfile << "statement : expression_satement\n";
            }
            | compound_statement
            {
                logfile << "statement : compound_satement\n";
            }
            | FOR LPAREN expression_statement expression_statement expression RPAREN statement
            {
                logfile << "statement : FOR LPAREN expression statement expression statement expression RPAREN statement\n";
            }
            | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE 
            {
                logfile << "statement : IF LPAREN expression RPAREN statement\n";
            }
            | IF LPAREN expression RPAREN statement ELSE statement
            {
                logfile << "statement : IF LPAREN expression RPAREN statement ELSE statement\n";
            }
            | WHILE LPAREN expression RPAREN statement
            {
                logfile << "statement : WHILE LPAREN expression RPAREN statement\n";
            }
            | PRINTLN LPAREN ID RPAREN SEMICOLON
            {
                logfile << "statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n";
            }
            | RETURN expression SEMICOLON
            {
                logfile << "statement : RETURN expression SEMICOLON\n";
            }
            | PRINTLN LPAREN ID RPAREN error
            {
                errf << "Line# " << line_count << ": semicolon missing\n"; 
                err_sem++; 
            }
            | RETURN expression error
            {
                err_sem++; 
                errf << "Line# " << line_count << ": semicolon missing\n";  
            }
            ;
expression_statement : SEMICOLON
                {
                    logfile << "expression_statement : SEMICOLON\n";
                }
                | expression SEMICOLON
                {
                    logfile << "expression_statement : expression SEMICOLON\n";
                }
                | error
                {
                    err_sem++; 
                    cout << "here\n"; 
                    errf << "Line# "<< line_count << ": Syntax error at expression of expression statement\n"; 
                }
                ;
variable : ID
        {
            logfile << "variable : ID\n";
            string nameID = $1->getname(), IDtype = "VAR"; 
            SymbolInfo *id = table.LookUp2(nameID,IDtype); 
            if(id){
                $$ = id;
            }
            else{
                err_sem++; 
                cout << "Line# "<< line_count << ": Undeclared variable'" << nameID << "'\n";   
            }
        }
        | ID LTHIRD expression RTHIRD
        {
            logfile << "variable : ID LTHIRD expression RTHIRD\n";
            string nameID = $1->getname(), IDtype = "ARA";  
            SymbolInfo *curr = table.LookUp2(nameID,IDtype);
            if(curr){
                if(curr->getAraySize() <= $3->all_ints[0]){
                    ///here third arg is array index.
                    err_sem++; 
                    errf << "Error at line " << line_count << " : " << nameID << " array index out of bound\n"; 
                }
                else curr->setArrayInd($3->all_ints[0]);
                if(curr->getVarType() == "INT"){
                    while( curr->all_ints.size() <= curr->getAraIndex()) curr->all_ints.pb(0); 
                }
                else if( curr->getVarType() == "FLOAT"){
                    while( curr->all_floats.size() <= curr->getAraIndex()) curr->all_floats.pb(0);
                }
            } 
            else{
                err_sem++; 
                cout << "Line# " <<  line_count << ": Undeclared variable '" << nameID << "'\n"; 
            }
        }
        ;
expression : logic_expression
            {
                logfile << "expression  : logic_expression\n";
                $$ = $1;
                $$->all_floats.pb(0); 
                $$->all_ints.pb(0);
                //testing 
                // cout << "Logic epxr" << $$->getname() << "\n"; 
            }
            | variable ASSIGNOP logic_expression
            {
                logfile << "expression  : variable ASSIGNOP logic_expression\n";
                string varType = $1->getVarType();
                string varType2 = $3->getVarType(); 
                string IDtype = $1->getIDType();
                string IDtype2 = $3->getIDType();  
                if(varType == "INT"){
                    $1->all_ints.pb(0);
                    if(IDtype == "VAR"){
                        if(varType2 == "INT"){
                            if(IDtype2 == "VAR") $1->all_ints[0] = $3->all_ints[0]; 
                            else $1->all_ints[0] = $3->all_ints[ $3->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning float value to integer\n"; 
                        }
                    }
                    else if(IDtype == "ARA"){
                        int ind = $1->getAraIndex(); 
                        if(varType2 == "INT"){
                            if(IDtype2 == "VAR") $1->all_ints[ind] = $3->all_ints[0]; 
                            else $1->all_ints[ind] = $3->all_ints[ $3->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning float value to integer\n"; 
                        }
                    } 
                }
                else if(varType == "FLOAT"){
                    $1->all_floats.pb(0);
                    if(IDtype == "VAR"){
                        if(varType2 == "FLOAT"){
                            if(IDtype2 == "VAR") $1->all_floats[0] = $3->all_floats[0]; 
                            else $1->all_floats[0] = $3->all_floats[ $3->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning integer value to float\n"; 
                        }
                    }
                    else if(IDtype == "ARA"){
                        int ind = $1->getAraIndex(); 
                        if(varType2 == "FLOAT"){
                            if(IDtype2 == "VAR") $1->all_floats[ind] = $3->all_floats[0]; 
                            else $1->all_floats[ind] = $3->all_floats[ $3->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning integer value to float\n"; 
                        }
                    } 
                }
                $$ = $1;
            }
            ;
logic_expression : rel_expression
                {
                    logfile << "logic_expression : rel_expression\n";
					$$ = $1;
					$$->all_ints.pb(0);
					$$->all_floats.pb(0);
                }
                | rel_expression LOGICOP rel_expression
                {
                    logfile << "logic_expression : rel_expression LOGICOP rel_expression\n";
                    SymbolInfo *curr = new SymbolInfo("INT");
                    string logicOp = $2->getname(); 
                    string first_var = $1->getVarType(), second_var = $3->getVarType();
                    if(logicOp == "&&"){
                        if(first_var == "FLOAT"){
                            $1->all_floats.pb(0);
                            if($1->all_floats[0] == 0){
                                curr->all_ints[0] = 0; 
                            }
                            else{
                                if(second_var == "INT"){
                                    $3->all_ints.pb(0); 
                                    if($3->all_ints[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0] = 1;
                                } 
                                else{
                                    $3->all_floats.pb(0); 
                                    if($3->all_floats[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0]  = 1; 
                                }
                            }
                        }
                        else if(first_var == "INT"){
                            $1->all_ints.pb(0);
                            if($1->all_ints[0] == 0){
                                curr->all_ints[0] = 0; 
                            }
                            else{
                                if(second_var == "INT"){
                                    $3->all_ints.pb(0); 
                                    if($3->all_ints[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0] = 1;
                                } 
                                else{
                                    $3->all_floats.pb(0); 
                                    if($3->all_floats[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0]  = 1; 
                                }
                            }
                        }
                    } 
                    else if( logicOp == "||"){
                        if(first_var == "FLOAT"){
                            $1->all_floats.pb(0);
                            if($1->all_floats[0] != 0){
                                curr->all_ints[0] = 1; 
                            }
                            else{
                                if(second_var == "INT"){
                                    $3->all_ints.pb(0); 
                                    if($3->all_ints[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0] = 0;
                                } 
                                else{
                                    $3->all_floats.pb(0); 
                                    if($3->all_floats[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0]  = 0; 
                                }
                            }
                        }
                        else if(first_var == "INT"){
                            $1->all_ints.pb(0);
                            if($1->all_ints[0] != 0){
                                curr->all_ints[0] = 1; 
                            }
                            else{
                                if(second_var == "INT"){
                                    $3->all_ints.pb(0); 
                                    if($3->all_ints[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0] = 0;
                                } 
                                else{
                                    $3->all_floats.pb(0); 
                                    if($3->all_floats[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0]  = 0; 
                                }
                            }
                        }
                    }
                    $$ = curr; 
                }
                ;
rel_expression : simple_expression
                {
                    logfile << "rel_expression  : simple_expression\n";
                    $$ = $1;
                    $$->all_floats.pb(0);
                    $$->all_ints.pb(0); 
                }
                | simple_expression RELOP simple_expression
                {
                    logfile << "rel_expression : simple_expression RELOP simple_expression\n";
                    SymbolInfo *curr = new SymbolInfo("INT"); 
                    string varType1 = $1->getVarType(), varType2 = $3->getVarType(); 
                    string relOp = $2->getname(); 
                        if(relOp == "=="){
                            if(varType1 != varType2){
                                errf << "Error at line " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] == $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] == $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == "!="){
                            if(varType1 != varType2){
                                errf << "Error at line " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] != $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] != $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == ">"){
                            if(varType1 != varType2){
                                errf << "Error at line " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] > $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] > $3->all_ints[0] ? 1: 0 );
                            }
                        }   
                        else if(relOp == "<"){
                            if(varType1 != varType2){
                                errf << "Error at line " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] < $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] < $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == ">="){
                            if(varType1 != varType2){
                                errf << "Error at line " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] >= $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] >= $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == "<="){
                            if(varType1 != varType2){
                                errf << "Error at line " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] <= $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] <= $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        $$ = curr; 
                }
                ;
simple_expression : term
                {
                    logfile << "simple_expression : term\n";
                    $$ = $1; 
                    // cout << "Simple exp: term: " <<  $$->getname() << "\n"; 
                    $$->all_ints.pb(0); $$->all_floats.pb(0);
                }
                | simple_expression ADDOP term
                {
                    string addop = $2->getname(); 
                    logfile << "simple_expression : simple_expression ADDOP term\n";
                    string ID1 = $1->getIDType(), ID2 = $3->getIDType(); 
                    string var_1 = $1->getVarType(), var_2 = $3->getVarType(); 
                    SymbolInfo *curr = new SymbolInfo("INT"); //will change accordingly.
                    if(addop == "+"){
                        if(ID1 == "VAR"){
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[0] + (  var_2 == "INT" ? $3->all_ints[0] : $3->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[0] + (  var_1 == "INT" ? $1->all_ints[0]: $1->all_floats[0]);
                            }
                            else curr->all_ints[0] = $3->all_ints[0] + $1->all_ints[0]; 
                        }
                        else if(ID2 == "ARA"){
                            int ind2 = $3->getAraIndex(); 
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[0] + (  var_2 == "INT" ? $3->all_ints[ind2] : $3->all_floats[ind2]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[ind2] + (  var_1 == "INT" ? $1->all_ints[0] : $1->all_floats[0]);
                            }
                            else curr->all_ints[0] = $3->all_ints[ind2] + $1->all_ints[0];
                        }
                    }
                    else if(ID1 == "ARA"){
                        int ind = $1->getAraIndex();
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[ind] + (  var_2 == "INT" ? $3->all_ints[0] : $3->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[0] + (  var_1 == "INT" ? $1->all_ints[ind] : $1->all_floats[ind]);
                                }
                            else curr->all_ints[0] = $3->all_ints[0] + $1->all_ints[ind]; 
                            }
                            else if(ID2 == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[ind] + (  var_2 == "INT" ? $3->all_ints[ind2] : $3->all_floats[ind2]); 
                                }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[ind2] + (  var_1 == "INT" ? $1->all_ints[ind] : $1->all_floats[ind]);
                            }
                            else curr->all_ints[0] = $3->all_ints[ind2] + $1->all_ints[ind];
                            }
                        }   
                    }
                    else if(addop == "-"){
                        if(ID1 == "VAR"){
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[0] - (  var_2 == "INT" ? $3->all_ints[0] : $3->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[0] - (  var_1 == "INT" ? $1->all_ints[0]: $1->all_floats[0]);
                            }
                            else curr->all_ints[0] = $3->all_ints[0] - $1->all_ints[0]; 
                        }
                        else if(ID2 == "ARA"){
                            int ind2 = $3->getAraIndex(); 
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[0] - (  var_2 == "INT" ? $3->all_ints[ind2] : $3->all_floats[ind2]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[ind2] - (  var_1 == "INT" ? $1->all_ints[0] : $1->all_floats[0]);
                            }
                            else curr->all_ints[0] = $3->all_ints[ind2] - $1->all_ints[0];
                        }
                    }
                    else if(ID1 == "ARA"){
                        int ind = $1->getAraIndex();
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[ind] - (  var_2 == "INT" ? $3->all_ints[0] : $3->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[0] - (  var_1 == "INT" ? $1->all_ints[ind] : $1->all_floats[ind]);
                                }
                            else curr->all_ints[0] = $3->all_ints[0]- $1->all_ints[ind]; 
                            }
                            else if(ID2 == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = $1->all_floats[ind] - (  var_2 == "INT" ? $3->all_ints[ind2] : $3->all_floats[ind2]); 
                                }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = $3->all_floats[ind2] - (  var_1 == "INT" ? $1->all_ints[ind] : $1->all_floats[ind]);
                            }
                            else curr->all_ints[0] = $3->all_ints[ind2] - $1->all_ints[ind];
                            }
                        }
                    }
                    $$ = curr; 
                }
                ;
term : unary_expression
                {
                    logfile << "term :  unary_expression\n";
                    $$ = $1; 
                    $$->all_ints.pb(0); 
                    $$->all_floats.pb(0);
                }
                | term MULOP unary_expression
                {
                    logfile << "term : term MULOP unary_expression\n";
                    string mulop_type = $2->getname();
                    string first_T = $1->getIDType(), second_T  = $3->getIDType(); 
                    string first_var = $1->getVarType(), second_var = $3->getVarType(); 
                    
                    if(mulop_type == "*"){
                        if(first_T == "VAR"){
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[0] * $3->all_ints[0]; 
                                    else curr->all_floats[0] = $1->all_floats[0] * $3->all_floats[0];
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        curr->all_floats[0] = $1->all_ints[0] * $3->all_floats[0];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        curr->all_ints[0] = $1->all_ints[0] * $3->all_ints[0];
                                        $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[0] * $3->all_ints[ind2]; 
                                    else curr->all_floats[0] = $1->all_floats[0] * $3->all_floats[ind2];
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        curr->all_floats[0] = $1->all_ints[0] * $3->all_floats[ind2];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        curr->all_ints[0] = $1->all_ints[0] * $3->all_ints[ind2];
                                        $$ = curr; 
                                    }
                                }
                            }
                        }
                        else if( first_T == "ARA"){
                            int ind1 = $1->getAraIndex();
                            if( second_T == "VAR"){ 
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[ind1] * $3->all_ints[0]; 
                                    else curr->all_floats[0] = $1->all_floats[ind1] * $3->all_floats[0];
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        curr->all_floats[0] = $1->all_ints[ind1] * $3->all_floats[0];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        curr->all_ints[0] = $1->all_ints[ind1] * $3->all_ints[0];
                                        $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[ind1] * $3->all_ints[ind2]; 
                                    else curr->all_floats[0] = $1->all_floats[ind1] * $3->all_floats[ind2];
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        curr->all_floats[0] = $1->all_ints[ind1] * $3->all_floats[ind2];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        curr->all_ints[0] = $1->all_ints[ind1] * $3->all_ints[ind2];
                                        $$ = curr; 
                                    }
                                }
                            }
                        }
                    }
                    else if(mulop_type == "/"){
                        if(first_T == "VAR"){
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") {
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Error at line " << line_count << " : Divide by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity(); 
                                        }
                                        else curr->all_floats[0] = $1->all_floats[0] / $3->all_ints[0];
                                    } 
                                    else {
                                        if($3->all_floats[0] == 0 ){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";  
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_floats[0] / $3->all_floats[0];
                                    }
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        if($3->all_floats[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[0] / $3->all_floats[0];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[0] / $3->all_ints[0];
                                        $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") {
                                        if($3->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_floats[0] / $3->all_ints[ind2];
                                    } 
                                    else {
                                        if($3->all_floats[ind2] == 0){ 
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_floats[0] / $3->all_floats[ind2];
                                    }
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        if($3->all_floats[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[0] / $3->all_floats[ind2];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        if($3->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[0] / $3->all_ints[ind2];
                                        $$ = curr; 
                                    }
                                }
                            }
                        }
                        else if( first_T == "ARA"){
                            int ind1= $1->getAraIndex(); 
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") {
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity(); 
                                        }
                                        else curr->all_floats[0] = $1->all_floats[ind1] / $3->all_ints[0];
                                    } 
                                    else {
                                        if($3->all_floats[0] == 0 ){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_floats[ind1] / $3->all_floats[0];
                                    }
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        if($3->all_floats[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[ind1] / $3->all_floats[0];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[ind1] / $3->all_ints[0];
                                        $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    if(second_var == "INT") {
                                        if($3->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_floats[ind1] / $3->all_ints[ind2];
                                    } 
                                    else {
                                        if($3->all_floats[ind2] == 0){ 
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_floats[ind1] / $3->all_floats[ind2];
                                    }
                                    $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        if($3->all_floats[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[ind1] / $3->all_floats[ind2];
                                        $$ = curr; 
                                    }
                                    else{
                                        SymbolInfo *curr = new SymbolInfo("INT"); 
                                        if($3->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[ind1] / $3->all_ints[ind2];
                                        $$ = curr; 
                                    }
                                }
                            }
                        }
                    }
                    else if(mulop_type == "%"){
                        if(first_var == "FLOAT" || second_var == "FLOAT"){
                            errf << "Line# " << line_count << ": Operands of modulus must be integers\n";
                            err_sem++;  
                        }
                        else{
                            SymbolInfo *curr = new SymbolInfo("INT"); 
                            if(first_T == "VAR"){
                                if(second_T == "VAR") curr->all_ints[0] = $1->all_ints[0] % $3->all_ints[0]; 
                                else curr->all_ints[0] = $1->all_ints[0] % $3->all_ints[ $3->getAraIndex() ];
                            }
                            else{
                                int ind1= $1->getAraIndex(); 
                                if(second_T == "VAR") curr->all_ints[0] = $1->all_ints[ind1] % $3->all_ints[0]; 
                                else curr->all_ints[0] = $1->all_ints[ind1] % $3->all_ints[ $3->getAraIndex() ];
                            }
                            $$ = curr; 
                        }
                    }
                    $$->setIDType("VAR");
                }
                ;
unary_expression : ADDOP unary_expression
                    {
                        logfile << "unary_expression : ADDOP unary_expression\n";
					    if($1->getname() == "-"){
						    if($2->getVarType() == "VAR"){
							    $2->all_ints[0] = (-1)*($2->all_ints[0]);
					    	}
						    else if($2->getVarType() == "ARA"){
							    $2->all_ints[$2->getAraIndex()] = (-1)*($2->all_ints[$2->getAraIndex()]);
						    }
					    }
					    $$ = $2;
                    }
                    | NOT unary_expression
                    {
                        logfile << "unary_expression : NOT unary_expression\n";
					    SymbolInfo *var = new SymbolInfo("INT");
                        var->setIDType("VAR");
                        int val; 
					    if($2->getVarType() == "INT"){
						    if($2->getIDType() == "VAR") val = $2->all_ints[0];
						    else if($2->getIDType() == "ARA")val = $2->all_ints[$2->getAraIndex()];
					    }
					    else if($2->getVarType() == "FLOAT"){
						    if($2->getIDType() == "VAR") val = (int)$2->all_floats[0];
						    else if($2->getIDType() == "ARA") val = (int)$2->all_floats[$2->getAraIndex()];
				    	}
                        val ^= 1; 
                        var->all_ints[0] = val; 
					    $$ = var;
                    }
                    | factor
                    {
                        logfile << "unary_expression : factor\n";
                        $$ = $1;
                        $$->all_ints.pb(0);
                        $$->all_floats.pb(0);
                    }
                    ;
factor : variable
        {
            logfile << "factor  : variable\n"; 
        }
        | ID LPAREN argument_list RPAREN
        {
            logfile << "factor : ID LPAREN argument_list RPAREN\n";
            string funcName = $1->getname(); 
            string IDType = "FUNC";
            if(!table.LookUp2(funcName,IDType)){
                errf << "Line#" << line_count << ": Undeclared function'" << funcName <<  "'\n";
                err_sem++; 
            } 
            else{
                string getReturn = $1->getFuncRet(); 
                if(getReturn == "VOID"){
                    err_sem++; 
                    errf << "Line# " << line_count << ": Void cannot be used in expression\n";
                }
                else{
                    SymbolInfo *curr = new SymbolInfo(getReturn);
                    //---------------------------------useless. 
					if($1->getVarType() == "INT")curr->all_ints[0] = 0;
					else if($1->getVarType() == "FLOAT")curr->all_floats[0] = 0;
					$$ = curr;
                    //----------------------------------
                }
            }
        }
        | LPAREN expression RPAREN
        {
            logfile << "factor : LPAREN expression RPAREN\n";
            $$ = $2;
        }
        | CONST_INT
        {
            logfile << "factor  : CONST_INT\n";
			$1->setVarType("INT");
            $1->setIDType("VAR"); 
			$1->all_ints[0]= stoi($1->getname());
			$$ = $1;
        }
        | CONST_FLOAT
        {
            logfile << "factor : CONST_FLOAT\n";
			$1->setVarType("FLOAT");
            $1->setIDType("VAR"); 
			$1->all_floats[0]= stoi($1->getname());
			$$ = $1;
        }
        | variable INCOP
        {
            logfile << "factor : variable INCOP\n";
            if($1->getIDType() == "VAR"){
                if($1->getVarType() == "INT"){
                    $1->all_ints[0]++;
                }
                else if( $1->getVarType() == "FLOAT"){
                    $1->all_floats[0] += 1.0; 
                }
            }
            else if($1->getIDType() == "ARA"){
                int ind = $1->getAraIndex();
                if($1->getVarType() == "INT"){
                    $1->all_ints[ind]++; 
                }
                else if( $1->getVarType() == "FLOAT"){
                    $1->all_floats[ind] += 1.0; 
                }
            }
            $$ = $1;
        }
        | variable DECOP
        {
            logfile << "factor : variable DECOP\n";
            if($1->getIDType() == "VAR"){
                if($1->getVarType() == "INT"){
                    $1->all_ints[0]--;
                }
                else if( $1->getVarType() == "FLOAT"){
                    $1->all_floats[0] -= 1.0; 
                }
            }
            else if($1->getIDType() == "ARA"){
                int ind = $1->getAraIndex();
                if($1->getVarType() == "INT"){
                    $1->all_ints[ind]--; 
                }
                else if( $1->getVarType() == "FLOAT"){
                    $1->all_floats[ind] -= 1.0; 
                }
            }
            $$ = $1;
        }
        ;
argument_list : arguments
                {
                    logfile << "argument_list : arguments\n";
                }
                |
                {
                    // empty transition
                }
                ;
arguments : arguments COMMA logic_expression
                {
                    logfile << "arguments : arguments COMMA logic_expression\n";
                }
                | logic_expression
                {
                    logfile << "arguments : logic_expression\n";
                }
                ;

%%

int main(int argc, char *argv[]){
    if((yyin=fopen(argv[1],"r"))==NULL){
        cout << "Cannot open input file.\n"; 
        exit(1);
    }
    logfile.open("2005018_log.txt");
    errf.open("2005018_errors.txt");
    table.EnterScope();  
	yyparse(); 
    logfile.close(); 
    errf.close();  
	return 0;
}

