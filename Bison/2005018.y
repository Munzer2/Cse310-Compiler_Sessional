%{
#include<bits/stdc++.h>
#include "2005018.h"
// #include <ParseTree>
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

ofstream logfile,errf,parsefile;

vector<SymbolInfo*> params;
vector<string>function_arg_types; 
int args_ID_cnt = 0;   


void yyerror(const char *s){
    cout << "Error: " << s << "\n"; 
    // cout << line_count << "\n";  
}
%}

%union{
    SymbolInfo* symbVal;
}


%token <symbVal> CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP ID IF ELSE FOR WHILE DO CONTINUE INT FLOAT CHAR DOUBLE VOID RETURN INCOP DECOP ASSIGNOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD SEMICOLON COMMA NOT PRINTLN

%type <symbVal> start program unit var_declaration func_declaration func_definition type_specifier parameter_list compound_statement
%type <symbVal> statements declaration_list statement expression_statement expression variable logic_expression rel_expression simple_expression
%type <symbVal> term unary_expression factor argument_list arguments 


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* For errors checking */
%error-verbose


%%

start: program
		{
            $$ = new SymbolInfo("start", "grammar");
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"start: program","NULL");
            $$->node->addChild($1->node); 
			logfile << "start : program\n"; 
            
            logfile << "Total Lines: " << line_count << "\n"; 
            logfile << "Total Errors: " << err_sem << "\n"; 

            $$->node->printParseTree($$->node,0,parsefile); 
            ///This is the actual node found from parsing the input. Now I want to generate the corresponding assembly code from this root node.
		}
		;

program : program unit
{ 
    $$ = new SymbolInfo("program", "grammar");
    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"program : program unit","NULL");
    $$->node->addChild($1->node);
    $$->node->addChild($2->node);
    logfile << "program : program unit\n"; 
    // $$->node->printParseTree($$->node,0,parsefile);
    // vector< treeNode* > vect = $$->node->getChildren(); 
    // for(auto node: vect){
    //     cout << node->getRule() << "\n";  
    // 
}
| unit
{  
    $$ = new SymbolInfo("program", "grammar");
    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"program : unit","NULL");
    $$->node->addChild($1->node);
    logfile << "program : unit\n";
}
;
unit : var_declaration
        {
            $$ = new SymbolInfo("unit", "grammar"); 
            logfile << "unit  : var_declaration\n"; 
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"unit  : var_declaration","NULL");
            $$->node->addChild($1->node);   
            // for( auto x : $$->node->children){
            // cout << x->getRule() << " " << x->getChildrenSize() << "\n";  
            // }
        }
        | func_declaration
        {
            $$ = new SymbolInfo("unit", "grammar"); 
            logfile << "unit : func_declaration\n";
            // cout << $1->node->getChildrenSize() << "\n" ;  
            vector< treeNode* > vect = $$->node->getChildren(); 
            for(auto node: vect){
                 cout << node->getRule() << "\n";}  
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"unit : func_declaration","NULL");
            $$->node->addChild($1->node); 
        }
        | func_definition
        {
            $$ = new SymbolInfo("unit", "grammar"); 
            logfile << "unit : func_definition\n";
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"unit : func_definition","NULL");
            $$->node->addChild($1->node);
        }
        ;
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
                    {
                        $$ = new SymbolInfo("func_declaration", "grammar"); 
                        $$->node = new treeNode(line_count,$1->node->getfirstLine(),"func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON","NULL");
                        $$->node->addChild($1->node); 
                        $$->node->addChild($2->node); 
                        $$->node->addChild($3->node); 
                        $$->node->addChild($4->node); 
                        $$->node->addChild($5->node); 
                        $$->node->addChild($6->node); 

                        logfile << "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n";
                        string nameID = $2->getname();
                        string IDtype = "FUNC";     
                        SymbolInfo *check = table.LookUp2(nameID,IDtype);
                        if(check){
                            errf << "Line# " << line_count << ": Function '"<< nameID <<"' already declared\n"; 
                            err_sem++; 
                            cout << "here\n"; 
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
                        $$ = new SymbolInfo("func_declaration", "grammar"); 
                        $$->node = new treeNode(line_count,$1->node->getfirstLine(),"func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON","NULL");
                        $$->node->addChild($1->node); 
                        $$->node->addChild($2->node); 
                        $$->node->addChild($3->node); 
                        $$->node->addChild($4->node); 
                        $$->node->addChild($5->node); 
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
                    $$ = new SymbolInfo("func_definition", "grammar"); 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node); 
                    $$->node->addChild($4->node); 
                    $$->node->addChild($5->node);
                    $$->node->addChild($6->node);

                    logfile << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n";
                    string nameID = $2->getname(), IDtype = "FUNC";
                    string typeOfFunc = $1->getVarType();   

                    SymbolInfo *curr = table.LookUp2(nameID, IDtype); 
                    if(curr){
                        err_sem++; 
                        errf << "Line# "<<  line_count << " : Redefinition of function " << nameID << "\n" ;
                    }
                    else{
                        // SymbolInfo *newSymb = new SymbolInfo(nameID, "ID");
                        $2->setFuncDefined(); 
                        $2->setIDType("FUNC");
                        $2->setFuncRet(typeOfFunc); 
                        for(int i =0; i <  function_arg_types.size(); ++i){
                            $2->push_params(function_arg_types[i]);
                        }
                        table.Insert($2);
                    } 
                    args_ID_cnt =0;
                    function_arg_types.clear(); 
                }
                | type_specifier ID LPAREN RPAREN compound_statement
                {
                    $$ = new SymbolInfo("func_definition", "grammar"); 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"func_definition : type_specifier ID LPAREN RPAREN compound_statement","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($2->node); 
                    $$->node->addChild($3->node); 
                    $$->node->addChild($4->node); 
                    $$->node->addChild($5->node);
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
                | error
                {
                    // cout << "here\n"; 
                    err_sem++; 
                    errf << "Line# " << line_count << " : Syntax error at parameter list of function definition\n"; 
                }
                ;
parameter_list : parameter_list COMMA type_specifier ID
                {
                    $$ = new SymbolInfo("parameter_list", "grammar"); 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"parameter_list : parameter_list COMMA type_specifier ID","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($2->node); 
                    $$->node->addChild($3->node); 
                    $$->node->addChild($4->node); 
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
                    $$ = new SymbolInfo("parameter_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"parameter_list : parameter_list COMMA type_specifier","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($2->node); 
                    $$->node->addChild($3->node); 
                    logfile << "parameter_list  : parameter_list COMMA type_specifier\n";
                    function_arg_types.pb($3->getVarType()); 
                }
                | type_specifier ID
                {
                    $$ = new SymbolInfo("parameter_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"parameter_list : type_specifier ID","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($2->node); 
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
                    $$ = new SymbolInfo("parameter_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"parameter_list : type_specifier","NULL");
                    $$->node->addChild($1->node); 
                    logfile << "parameter_list  : type_specifier\n";
                    function_arg_types.pb(var_type);
                }
                ;
compound_statement : LCURL
                {
                    table.EnterScope(); 
                    for(int i =0 ; i < params.size(); ++i) table.Insert(params[i]);
                    params.clear(); 
                } statements RCURL
                {
                    logfile << "compound_statement : LCURL statements RCURL\n";
                    $$ = new SymbolInfo("compound_statement", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"compound_statement : LCURL statements RCURL","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($3->node);
                    $$->node->addChild($4->node);   
                    // for(auto c : $2->node->children){
                    //     cout << c->getRule() << "\n"; 
                    // }
                    table.PrintAllScopeTables(logfile);
                    table.ExitScope();    
                }
                | LCURL RCURL
                {
                    $$ = new SymbolInfo("compound_statement", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"compound_statement : LCURL RCURL","NULL");
                    $$->node->addChild($1->node); 
                    $$->node->addChild($2->node);
                    logfile << "compound_statement : LCURL RCURL\n";
                }
                ;
var_declaration : type_specifier declaration_list SEMICOLON
                { 
                    $$ = new SymbolInfo("var_declaration","grammar"); 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"var_declaration : type_specifier declaration_list SEMICOLON","NULL");  
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    // for(auto x : $$->node->children){
                    //     cout << x->getRule() << "\n"; 
                    // } 
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
                    symb->node = new treeNode(line_count, line_count,"type_specifier  : INT","NULL");
                    $$ = symb;
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"type_specifier : INT","NULL");
                    $$->node->addChild($1->node);  
                }
                | FLOAT
                {
                    logfile << "type_specifier  : FLOAT\n";
                    var_type = "FLOAT";
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    symb->node = new treeNode(line_count, line_count,"type_specifier  : FLOAT","NULL");
                    $$ = symb;
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"type_specifier : FLOAT","NULL");
                    $$->node->addChild($1->node); 
                }
                | VOID
                {
                    logfile << "type_specifier  : VOID\n";
                    var_type = "VOID"; 
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    symb->node = new treeNode(line_count, line_count,"type_specifier  : VOID","NULL");
                    $$ = symb;
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"type_specifier : VOID","NULL");
                    $$->node->addChild($1->node);
                }
                ;
declaration_list : declaration_list COMMA ID
                {
                    $$ = new SymbolInfo("declaration_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"declaration_list : declaration_list COMMA ID","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    treeNode *comma_node = new treeNode(line_count, line_count, "COMMA","NULL");
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
                    $$ = new SymbolInfo("declaration_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    $$->node->addChild($4->node);
                    $$->node->addChild($5->node);
                    $$->node->addChild($6->node);
                    logfile << "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n";
                    string nameID = $3->getname(), arr_sz_str = $5->getname();  
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": array type cannot be void\n"; 
                    }
                    else{
                        int array_sz = stoi(arr_sz_str); 
                        SymbolInfo *arrID = new SymbolInfo(nameID,"ID"); 
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
                    $$ = new SymbolInfo("declaration_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"declaration_list : ID","NULL");
                    $$->node->addChild($1->node);
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
                    $$ = new SymbolInfo("declaration_list", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"declaration_list : ID LTHIRD CONST_INT RTHIRD","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    $$->node->addChild($4->node);
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
                $$ = new SymbolInfo("statements", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statements : statement","NULL");
                $$->node->addChild($1->node);
                // for(auto c : $1->node->children){
                //     cout << c-.getRule() << "\n"; 
                // }
                logfile << "statements : statement\n";
            }
            | statements statement
            {
                $$ = new SymbolInfo("statements", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statements : statements statement","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                logfile << "statements : statements statement\n";
            }
            ;
statement : var_declaration
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : var_declaration","NULL");
                $$->node->addChild($1->node);
                logfile << "statement : var declaration\n";
            }
            | expression_statement
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : expression_statement","NULL");
                $$->node->addChild($1->node);
                logfile << "statement : expression_satement\n";
            }
            | compound_statement
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : compound_statement","NULL");
                $$->node->addChild($1->node);
                logfile << "statement : compound_satement\n";
            }
            | FOR LPAREN expression_statement expression_statement expression RPAREN statement
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
                $$->node->addChild($4->node);
                $$->node->addChild($5->node);
                $$->node->addChild($6->node);
                $$->node->addChild($7->node);
                logfile << "statement : FOR LPAREN expression statement expression statement expression RPAREN statement\n";
            }
            | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE 
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : IF LPAREN expression RPAREN statement","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
                $$->node->addChild($4->node);
                $$->node->addChild($5->node);
                logfile << "statement : IF LPAREN expression RPAREN statement\n";
            }
            | IF LPAREN expression RPAREN statement ELSE statement
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : IF LPAREN expression RPAREN statement ELSE statement","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
                $$->node->addChild($4->node);
                $$->node->addChild($5->node);
                $$->node->addChild($6->node);
                $$->node->addChild($7->node);
                logfile << "statement : IF LPAREN expression RPAREN statement ELSE statement\n";
            }
            | WHILE LPAREN expression RPAREN statement
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : WHILE LPAREN expression RPAREN statement","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
                $$->node->addChild($4->node);
                $$->node->addChild($5->node);
                logfile << "statement : WHILE LPAREN expression RPAREN statement\n";
            }
            | PRINTLN LPAREN ID RPAREN SEMICOLON
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : PRINTLN LPAREN ID RPAREN SEMICOLON","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
                $$->node->addChild($4->node);
                $$->node->addChild($5->node);
                logfile << "statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n";
            }
            | RETURN expression SEMICOLON
            {
                $$ = new SymbolInfo("statement", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"statement : RETURN expression SEMICOLON","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
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
                    $$ = new SymbolInfo("expresion_statement", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"expression_statement : SEMICOLON","NULL");
                    $$->node->addChild($1->node);
                    logfile << "expression_statement : SEMICOLON\n";
                }
                | expression SEMICOLON
                {
                    $$ = new SymbolInfo("expresion_statement", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"expression_statement : expression SEMICOLON","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    // for( auto c : $1->node->children){
                    //     cout << c->getRule() << "\n"; 
                    // }
                    logfile << "expression_statement : expression SEMICOLON\n";
                }
                | error
                {
                    err_sem++; 
                    // cout << "here\n"; 
                    errf << "Line# "<< line_count << ": Syntax error at expression of expression statement\n"; 
                }
                ;
variable : ID
        {
            ///////---------------------------------------------------------------------------------------------------------------------
            $$ = new SymbolInfo("variable", "grammar");
            logfile << "variable : ID\n";
            string nameID = $1->getname();
            SymbolInfo *id = table.LookUp(nameID);
            treeNode *curr = $1->node; 
            // cout << $1->node->getRule( ) << "\n"; 
            if(id){ 
            }
            else{
                err_sem++; 
                errf << "Line# "<< line_count << ": Undeclared variable'" << nameID << "'\n";   
            }
            //will also take undeclared variable in the parse tree.
            $$ = $1; 
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"variable : ID","NULL");
            $$->node->addChild(curr);
        }
        | ID LTHIRD expression RTHIRD
        {
            logfile << "variable : ID LTHIRD expression RTHIRD\n";
            string nameID = $1->getname(), IDtype = "ARA";  
            SymbolInfo *curr = table.LookUp2(nameID,IDtype); 
            if(curr){
                if(curr->getAraySize() <= $3->all_ints[0]){
                    ///Array Index out of bounds error. 
                    err_sem++; 
                    errf << "Line# " << line_count << " : " << nameID << " array index out of bound\n";
                    $$ = new SymbolInfo("Error_variable", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    $$->node->addChild($4->node); 
                }
                else if( $3->getVarType() == "FLOAT"){
                    err_sem++; 
                    errf << "Line# " << line_count << " : " << nameID << " array index cannot be float\n";
                    $$ = new SymbolInfo("Error_variable", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    $$->node->addChild($4->node);
                }
                else {
                    curr->setArrayInd($3->all_ints[0]);
                    if(curr->getVarType() == "INT"){
                        while( curr->all_ints.size() <= curr->getAraIndex()) curr->all_ints.pb(0); 
                     }
                    else if( curr->getVarType() == "FLOAT"){
                        while( curr->all_floats.size() <= curr->getAraIndex()) curr->all_floats.pb(0);
                    }
                    treeNode *curr = $1->node; 
                    $$ = $1;  
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                    $$->node->addChild(curr);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                    $$->node->addChild($4->node); 
                }
            } 
            else{
                err_sem++; 
                errf << "Line# " << line_count << " : variable " << nameID << " undeclared.\n";  
                $$ = new SymbolInfo("Error_variable", "grammar");
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                $$->node->addChild($1->node);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
                $$->node->addChild($4->node);
            }
        }
        ;
expression : logic_expression
            {
                treeNode *curr = $1->node;
                logfile << "expression  : logic_expression\n";
                $1->all_floats.pb(0); 
                $1->all_ints.pb(0);
                $$ = $1; 
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"expression : logic_expression","NULL");
                $$->node->addChild(curr);
            }
            | variable ASSIGNOP logic_expression
            {
                logfile << "expression  : variable ASSIGNOP logic_expression\n";
                // cout << $1->node->getRule() << "\n"; 
                treeNode *curr = $1->node; 
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
                            errf << "Line# " << line_count <<" : warning: possible loss of data in assignment of FLOAT to INT\n"; 
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
                            errf << "Line# " << line_count <<" : Assigning integer value to float\n"; 
                        }
                    }
                    else if(IDtype == "ARA"){
                        int ind = $1->getAraIndex(); 
                        if(varType2 == "FLOAT"){
                            if(IDtype2 == "VAR") 
                            {
                                $1->all_floats[ind] = $3->all_floats[0];
                            } 
                            else $1->all_floats[ind] = $3->all_floats[ $3->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning integer value to float\n"; 
                        }
                    } 
                }
                $$ = $1;
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"expression : variable ASSIGNOP logic_expression","NULL");
                $$->node->addChild(curr);
                $$->node->addChild($2->node);
                $$->node->addChild($3->node);
            }
            ;
logic_expression : rel_expression
                {
                    treeNode *curr = $1->node; 
                    logfile << "logic_expression : rel_expression\n";
					$1->all_ints.pb(0);
					$1->all_floats.pb(0);
                    $$ = $1; 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"logic_expression : rel_expression","NULL");
                    $$->node->addChild(curr);
                }
                | rel_expression LOGICOP rel_expression
                {
                    $$ = new SymbolInfo("logic_expression", "grammar");
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
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"logic_expression : rel_expression LOGICOP rel_expression","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                }
                ;
rel_expression : simple_expression
                {
                    logfile << "rel_expression  : simple_expression\n";
                    treeNode* curr = $1->node; 
                    $1->all_floats.pb(0);
                    $1->all_ints.pb(0); 
                    $$ = $1;
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"rel_expression : simple_expression","NULL");
                    $$->node->addChild(curr);
                }
                | simple_expression RELOP simple_expression
                {
                    // $$ = new SymbolInfo("simple_expression", "grammar");
                    logfile << "rel_expression : simple_expression RELOP simple_expression\n";
                    SymbolInfo *curr = new SymbolInfo("INT"); 
                    string varType1 = $1->getVarType(), varType2 = $3->getVarType(); 
                    string relOp = $2->getname(); 
                        if(relOp == "=="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] == $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] == $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == "!="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] != $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] != $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == ">"){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] > $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] > $3->all_ints[0] ? 1: 0 );
                            }
                        }   
                        else if(relOp == "<"){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] < $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] < $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == ">="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] >= $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] >= $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == "<="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  $1->all_floats[0] <= $3->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  $1->all_ints[0] <= $3->all_ints[0] ? 1: 0 );
                            }
                        }
                        $$ = curr; 
                        $$->node = new treeNode(line_count,$1->node->getfirstLine(),"rel_expression : simple_expression RELOP simple_expression","NULL");
                        $$->node->addChild($1->node);
                        $$->node->addChild($2->node);
                        $$->node->addChild($3->node);
                }
                ;
simple_expression : term
                {
                    treeNode *curr = $1->node; 
                    logfile << "simple_expression : term\n"; 
                    $1->all_ints.pb(0); $1->all_floats.pb(0);
                    $$ = $1;
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"simple_expression : term","NULL");
                    $$->node->addChild(curr);
                }
                | simple_expression ADDOP term
                {
                    // $$ = new SymbolInfo("simple_expression", "grammar");  
                    string addop = $2->getname(); 
                    logfile << "simple_expression : simple_expression ADDOP term\n";
                    string ID1 = $1->getIDType(), ID2 = $3->getIDType(); 
                    // cout << $3->getVarType() << "\n";  
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
                            else {
                                curr->all_ints[0] = $3->all_ints[0] + $1->all_ints[ind];
                                // cout << " here1 " << $3->all_ints[0] << " " << $1->all_ints[ind]  << "\n";    
                            } 
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
                    // cout << curr->getVarType() << "\n" ; 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"simple_expression ADDOP term","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                }
                ;
term : unary_expression
                {
                    logfile << "term :  unary_expression\n"; 
                    treeNode *curr = $1->node; 
                    $1->all_ints.pb(0); 
                    $1->all_floats.pb(0);
                    $$ = $1; 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"term : unary_expression","NULL");
                    $$->node->addChild(curr);
                }
                | term MULOP unary_expression
                {
                    logfile << "term : term MULOP unary_expression\n";
                    string mulop_type = $2->getname();
                    string first_T = $1->getIDType(), second_T  = $3->getIDType(); 
                    string first_var = $1->getVarType(), second_var = $3->getVarType();     
                    string final_var = "";                  
                    SymbolInfo *curr = new SymbolInfo("INT"); ///random type. will change later.
                    curr->all_floats.pb(0); 
                    curr->all_ints.pb(0);  
                    if(mulop_type == "*"){
                        if(first_T == "VAR"){
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") {   curr->all_floats[0] = $1->all_floats[0] * $3->all_ints[0]; } 
                                    else curr->all_floats[0] = $1->all_floats[0] * $3->all_floats[0];  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT";  
                                        curr->all_floats[0] = $1->all_ints[0] * $3->all_floats[0];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT";  
                                        curr->all_ints[0] = $1->all_ints[0] * $3->all_ints[0];
                                        // $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[0] * $3->all_ints[ind2]; 
                                    else curr->all_floats[0] = $1->all_floats[0] * $3->all_floats[ind2];
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT"; 
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                        curr->all_floats[0] = $1->all_ints[0] * $3->all_floats[ind2];
                                        // $$ = curr; 
                                    }
                                    else{
                                        final_var = "INT" ; 
                                        // SymbolInfo *curr = new SymbolInfo("INT"); 
                                        curr->all_ints[0] = $1->all_ints[0] * $3->all_ints[ind2];
                                        // $$ = curr; 
                                    }
                                }
                            }
                        }
                        else if( first_T == "ARA"){
                            int ind1 = $1->getAraIndex();
                            if( second_T == "VAR"){ 
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[ind1] * $3->all_ints[0]; 
                                    else curr->all_floats[0] = $1->all_floats[ind1] * $3->all_floats[0];
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT";  
                                        curr->all_floats[0] = $1->all_ints[ind1] * $3->all_floats[0];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT";  
                                        curr->all_ints[0] = $1->all_ints[ind1] * $3->all_ints[0];
                                        // $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") curr->all_floats[0] = $1->all_floats[ind1] * $3->all_ints[ind2]; 
                                    else curr->all_floats[0] = $1->all_floats[ind1] * $3->all_floats[ind2];
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT";  
                                        curr->all_floats[0] = $1->all_ints[ind1] * $3->all_floats[ind2];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT";  
                                        curr->all_ints[0] = $1->all_ints[ind1] * $3->all_ints[ind2];
                                        // $$ = curr; 
                                    }
                                }
                            }
                        }
                    }
                    else if(mulop_type == "/"){
                        if(first_T == "VAR"){
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") {
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << " : Divide by zero\n"; 
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
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT";  
                                        if($3->all_floats[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[0] / $3->all_floats[0];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT"; 
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[0] / $3->all_ints[0];
                                        // $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT"); 
                                    final_var = "FLOAT"; 
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
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT"; 
                                        if($3->all_floats[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[0] / $3->all_floats[ind2];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT"; 
                                        if($3->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[0] / $3->all_ints[ind2];
                                        // $$ = curr; 
                                    }
                                }
                            }
                        }
                        else if( first_T == "ARA"){
                            int ind1= $1->getAraIndex(); 
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                    final_var = "FLOAT"; 
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
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT"; 
                                        if($3->all_floats[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[ind1] / $3->all_floats[0];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT"; 
                                        if($3->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[ind1] / $3->all_ints[0];
                                        // $$ = curr; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = $3->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                    final_var = "FLOAT"; 
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
                                    // $$ = curr;  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        // SymbolInfo *curr = new SymbolInfo("FLOAT");
                                        final_var = "FLOAT"; 
                                        if($3->all_floats[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = $1->all_ints[ind1] / $3->all_floats[ind2];
                                        // $$ = curr; 
                                    }
                                    else{
                                        // SymbolInfo *curr = new SymbolInfo("INT");
                                        final_var = "INT"; 
                                        if($3->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = $1->all_ints[ind1] / $3->all_ints[ind2];
                                        // $$ = curr; 
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
                            // SymbolInfo *curr = new SymbolInfo("INT");
                            int check = $3->all_ints[0] ; 
                            if(check == 0){
                                err_sem++; 
                                errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                // $$ = new SymbolInfo("error", "grammar");
                                final_var = "error";  
                            } 
                            else {
                                final_var = "INT";
                                 if(first_T == "VAR"){
                                if(second_T == "VAR") curr->all_ints[0] = $1->all_ints[0] % $3->all_ints[0]; 
                                else curr->all_ints[0] = $1->all_ints[0] % $3->all_ints[ $3->getAraIndex() ];
                            }
                            else{
                                int ind1= $1->getAraIndex(); 
                                if(second_T == "VAR") curr->all_ints[0] = $1->all_ints[ind1] % $3->all_ints[0]; 
                                else curr->all_ints[0] = $1->all_ints[ind1] % $3->all_ints[ $3->getAraIndex() ];
                            }
                            // $$ = curr;
                            } 
                        }
                    } 
                    $$ = curr; 
                    $$->setIDType("VAR");
                    $$->setVarType(final_var); 
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"term : term MULOP unary_expression","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                }
                ;
unary_expression : ADDOP unary_expression
                    {
                        // $$ = new SymbolInfo("unary_expression", "grammar");
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
                        $$->node = new treeNode(line_count,$1->node->getfirstLine(),"unary_expression : ADDOP unary_expression","NULL");
                        $$->node->addChild($1->node);
                        $$->node->addChild($2->node);
                    }
                    | NOT unary_expression
                    {
                        // $$ = new SymbolInfo("unary_expression", "grammar");
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
                        $$->node = new treeNode(line_count,$1->node->getfirstLine(),"unary_expression : NOT unary_expression","NULL");
                        $$->node->addChild($1->node);
                        $$->node->addChild($2->node);
                    }
                    | factor
                    {
                        treeNode *curr = $1->node; 
                        logfile << "unary_expression : factor\n";
                        $1->all_ints.pb(0);
                        $1->all_floats.pb(0);
                        $$ = $1;
                        $$->node = new treeNode(line_count,$1->node->getfirstLine(),"unary_expression : factor","NULL");
                        $$->node->addChild(curr); 
                    }
                    ;
factor : variable
        {
            treeNode *curr = $1->node; 
            logfile << "factor  : variable\n"; 
            $$ = $1; 
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor : variable","NULL");
            $$->node->addChild(curr);
        }
        | ID LPAREN argument_list RPAREN
        {
            logfile << "factor : ID LPAREN argument_list RPAREN\n";
            string funcName = $1->getname(); 
            string IDType = "FUNC";
            if(!table.LookUp2(funcName,IDType)){
                errf << "Line# " << line_count << ": Undeclared function'" << funcName <<  "'\n";
                err_sem++; 
                $$ = new SymbolInfo("Error", "grammar"); 
                $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor : ID LPAREN argument_list RPAREN","NULL");
            } 
            else{
                string name = $1->getname(), type = "FUNC"; 
                SymbolInfo *curr1 = table.LookUp2(name, type);
                string getReturn = curr1->getFuncRet(); 
                if(getReturn == "VOID"){
                    err_sem++; 
                    errf << "Line# " << line_count << ": Void cannot be used in expression\n";
                    $$ = new SymbolInfo("Error", "grammar");
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor : ID LPAREN argument_list RPAREN","NULL");
                }
                else{
                    SymbolInfo *curr = new SymbolInfo(getReturn);
					if($1->getVarType() == "INT")curr->all_ints[0] = 0;
					else if($1->getVarType() == "FLOAT")curr->all_floats[0] = 0;
					$$ = curr;
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor : ID LPAREN argument_list RPAREN","NULL");
                }
            }
            $$->node->addChild($1->node);
            $$->node->addChild($2->node);
            $$->node->addChild($3->node);
            $$->node->addChild($4->node);
        }
        | LPAREN expression RPAREN
        {
            logfile << "factor : LPAREN expression RPAREN\n";
            treeNode *second_node = $2->node; 
            $$ = $2;
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor : LPAREN expression RPAREN","NULL");
            $$->node->addChild($1->node);
            $$->node->addChild(second_node);
            $$->node->addChild($3->node);
        }
        | CONST_INT
        {
            logfile << "factor  : CONST_INT\n";
            treeNode *curr = $1->node; 
            $$ = $1;
            $$->setVarType("INT");
            $$->setIDType("VAR");
			$$->all_ints[0]= stoi($1->getname());
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor  : CONST_INT","NULL");
            $$->node->addChild(curr);
        }
        | CONST_FLOAT
        {
            logfile << "factor : CONST_FLOAT\n";
            treeNode *curr = $1->node; 
			$$ = $1;
            $$->setVarType("FLOAT");
            $$->setIDType("VAR"); 
			$$->all_floats[0]= stof($1->getname());
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor  : CONST_FLOAT","NULL");
            $$->node->addChild(curr);
        }
        | variable INCOP
        {
            // $$ = new SymbolInfo("expression", "grammar");
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
            treeNode *first_node = $1->node; 
            $$ = $1;
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor  : variable INCOP","NULL");
            $$->node->addChild(first_node);
            $$->node->addChild($2->node);
        }
        | variable DECOP
        {
            // $$ = new SymbolInfo("expression", "grammar");
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
            treeNode *first_node = $1->node; 
            $$ = $1;
            $$->node = new treeNode(line_count,$1->node->getfirstLine(),"factor  : variable DECOP","NULL");
            $$->node->addChild(first_node);
            $$->node->addChild($2->node);
        }
        ;
argument_list : arguments
                {
                    $$ = new SymbolInfo("arguments_list", "grammar");
                    logfile << "argument_list : arguments\n";
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"argument_list : arguments","NULL");
                    $$->node->addChild($1->node);
                }
                |
                {
                    $$ = new SymbolInfo("arguments_list","grammar");
                }
                ;
arguments : arguments COMMA logic_expression
                {
                    $$ = new SymbolInfo("arguments", "grammar");
                    logfile << "arguments : arguments COMMA logic_expression\n";
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"arguments : arguments COMMA logic_expression","NULL");
                    $$->node->addChild($1->node);
                    $$->node->addChild($2->node);
                    $$->node->addChild($3->node);
                }
                | logic_expression
                {
                    $$ = new SymbolInfo("arguments", "grammar");
                    logfile << "arguments : logic_expression\n";
                    $$->node = new treeNode(line_count,$1->node->getfirstLine(),"arguments : logic_expression","NULL");
                    $$->node->addChild($1->node);
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
    parsefile.open("2005018_parsetree.txt"); 
    table.EnterScope();  
	yyparse(); 
    parsefile.close(); 
    logfile.close(); 
    errf.close();  
	return 0;
}
