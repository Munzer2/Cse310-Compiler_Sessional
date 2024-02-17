#include <bits/stdc++.h>
#include "2005018.h"

#define pb(x) push_back(x)

vector<string> dataList;
extern ofstream ASM, optASM;
int check_global = 1;
int code_start = 0;
int labelCnt = 0;
string currFunc;

using namespace std;

string newLabel()
{
    string label = "L" + to_string(labelCnt);
    labelCnt++;
    return label;
}

void Peephole_Optimization()
{
    ifstream ASM_code("2005018.asm");
    vector<vector<string>> allCode;
    if (!ASM_code.is_open())
    {
        cout << "No file found!\n";
        return;
    }
    int cnt = 0;
    string inp;
    while (getline(ASM_code, inp))
    {
        vector<string> words;
        string curr_word = "";
        for (int i = 0; i < inp.size(); ++i)
        {
            if (inp[i] == '\n' || inp[i] == '\t' || inp[i] == ';' || inp[i] == ':' || inp[i] == ',' || inp[i] == ' ')
            {
                if (curr_word.size() > 0)
                    words.pb(curr_word);
                curr_word = "";
            }
            else
                curr_word += inp[i];
        }
        if (curr_word.size() > 0)
            words.pb(curr_word);

        // for (int i = 0; i < words.size(); ++i)
        // {
        //     cout << words[i] << " ";
        // }
        // cout << "\n";
        words.pb(inp + '\n');
        allCode.pb(words);
    }
    ASM_code.close();

    int old_size = INT_MAX;
    while (allCode.size() < old_size)
    {
        old_size = allCode.size(); /// Size before optimizing again

        vector<vector<string>> firstPass, secondPass, thirdPass, fourthPass;
        for (int i = 0; i < allCode.size(); ++i)
        {
            if (allCode[i].size() == 0)
                continue;
            if ((allCode[i][0] == "SUB" || allCode[i][0] == "ADD") && (allCode[i][2] == "0"))
            {
                continue;
            }
            if (i + 1 <= allCode.size() - 1 && (allCode[i][0] == "PUSH" && allCode[i + 1][0] == "POP"))
            {
                if (allCode[i][1] != allCode[i + 1][1])
                {
                    firstPass.push_back({"MOV", allCode[i + 1][1], allCode[i][1], "\tMOV " + allCode[i + 1][1] + ", " + allCode[i][1] + "\n"});
                }
                i++; // we dont want the second line.
                continue;
            }
            firstPass.pb(allCode[i]);
        }
        for (int i = 0; i < firstPass.size(); ++i)
        {
            if (i + 1 < firstPass.size() && (firstPass[i][0] == "MOV" && firstPass[i + 1][0] == "MOV" && firstPass[i + 1][2] == firstPass[i][1] && firstPass[i + 1][1] == firstPass[i][2]))
            {
                /// do nothing.
                i++; /// we dont want the second line.
            }
            else
                secondPass.pb(firstPass[i]);
        }

        for (int i = 0; i < secondPass.size(); ++i)
        {
            if (i + 1 < secondPass.size() && (secondPass[i][0] == "MOV" && secondPass[i + 1][0] == "POP" && secondPass[i][1] == secondPass[i + 1][1]))
            {
                /// do nothing else
            }
            else
                thirdPass.pb(secondPass[i]);
        }
        /// Unnecessary jumps.
        for (int i = 0; i < thirdPass.size(); ++i)
        {
            if (i + 1 < thirdPass.size() && (thirdPass[i][0] == "JMP" && thirdPass[i + 1][0] == thirdPass[i][1]))
            {
                /// Do nothing.
            }
            else
                fourthPass.pb(thirdPass[i]);
        }
        // for (int i = 0; i < fourthPass.size(); ++i)
        // {
        //     for (int k = 0; k < fourthPass[i].size(); ++k)
        //     {
        //         cout << fourthPass[i][k] << " ";
        //     }
        // }
        allCode = fourthPass;
    }
    ofstream out("2005018_optcode.asm");
    for (int i = 0; i < allCode.size(); ++i)
    {
        out << allCode[i][allCode[i].size() - 1];
    }
    out.close();
}

void InitiateASM()
{
    string start = "\
.MODEL SMALL\n\
\n\
.STACK 1000H\n\
\n\
.DATA\n\
\n\
CR EQU 0DH\n\
LF EQU 0AH\n\
NUMBER_PRINTLN DB '00000$'\n";
    ASM << start;
}

void global_var(treeNode *curr, string comment)
{
    if (comment != "")
    {
        comment = "\t;" + comment;
    }
    string _global;
    if (curr->isArr.first)
    {
        _global = curr->_name + " DW " + curr->isArr.second + " DUP (0000H)" + comment + "\n";
    }
    else
        _global = curr->_name + " DW 0" + comment + "\n"; /// Initiate value to 0, of word type.
    ASM << _global;
}

void PrintPrintlnProc()
{
    string print_code =
        "PRINT_OUT PROC  ;print the value stored in AX\n\
\tPUSH AX\n\
\tPUSH BX\n\
\tPUSH CX\n\
\tPUSH DX\n\
\tPUSH SI\n\
\tLEA SI,NUMBER_PRINTLN\n\
\tMOV BX,10\n\
\tADD SI,4\n\
\tCMP AX,0\n\
\tJNGE NEGATE\n\
\tPRINT:\n\
\tXOR DX,DX\n\
\tDIV BX\n\
\tMOV [SI],DL\n\
\tADD [SI],'0'\n\
\tDEC SI\n\
\tCMP AX,0\n\
\tJNE PRINT\n\
\tINC SI\n\
\tLEA DX,SI\n\
\tMOV AH,9\n\
\tINT 21H\n\
\tCALL NEWLINE\n\
\tPOP SI\n\
\tPOP DX\n\
\tPOP CX\n\
\tPOP BX\n\
\tPOP AX\n\
\tRET\n\
\tNEGATE:\n\
\tPUSH AX\n\
\tMOV AH,2\n\
\tMOV DL,'-'\n\
\tINT 21H\n\
\tPOP AX\n\
\tNEG AX\n\
\tJMP PRINT\n\
PRINT_OUT ENDP\n\n";
    ASM << print_code;
}

void PrintNewlineProc()
{
    string code = "NEWLINE PROC ;This is for printing newline.\n\
\tPUSH AX\n\
\tPUSH DX\n\
\tMOV AH,2\n\
\tMOV DL,CR\n\
\tINT 21H\n\
\tMOV AH,2\n\
\tMOV DL,LF\n\
\tINT 21H\n\
\tPOP DX\n\
\tPOP AX\n\
\tRET\n\
NEWLINE ENDP\n\n";

    ASM << code;
}

void travDeclList(treeNode *&curr)
{
    if (!curr)
        return;

    for (auto x : curr->children)
    {
        travDeclList(x);
        if (x->stackOff)
            curr->stackOff = x->stackOff;
    }
    if (curr->getRule() == "ID")
    {
        string comment = "Line :" + to_string(curr->getfirstLine());
        if (curr->is_global)
        {
            global_var(curr, comment);
            curr->stackOff = 0;
        }
        else
        {
            if (curr->isArr.first)
            {
                ASM << "\tSUB SP, " << 2 * stoi(curr->isArr.second) << "\t;" + comment + "\n";
            }
            else
            {
                ASM << "\tSUB SP, 2\t;" + comment + "\n";
            }
        }
    }
}

string JumpingCodeRelop(string relop)
{
    string jlab = "";
    if (relop == "<")
    {
        jlab = "\tJL";
    }
    else if (relop == ">")
    {
        jlab = "\tJG";
    }
    else if (relop == ">=")
    {
        jlab = "\tJGE";
    }
    else if (relop == "<=")
    {
        jlab = "\tJLE";
    }
    else if (relop == "==")
    {
        jlab = "\tJE";
    }
    else if (relop == "!=")
    {
        jlab = "\tJNE";
    }
    return jlab;
}

void trav(treeNode *&root)
{
    if (!root)
    {
        return;
    }
    if (root->getRule() == "start : program")
    {
        /// something here maybe.
        trav(root->children[0]);
        PrintNewlineProc();
        PrintPrintlnProc();
        ASM << "END main\n";

        /// Now the merging.
        // ifstream r1("data.asm");
        // ifstream r2("codeSegment.asm");
        // ofstream final("2005018.asm", ios::out | ios::app);
        // final << r1.rdbuf();
        // final << r2.rdbuf();
        // final.close();
        // r1.close();
        // r2.close();
    }
    else if (root->getRule() == "parameter_list : type_specifier")
    {
        trav(root->children[0]);
    }
    else if (root->getRule() == "parameter_list : type_specifier ID")
    {
        trav(root->children[1]);
    }
    else if (root->getRule() == "parameter_list : parameter_list COMMA type_specifier")
    {
        trav(root->children[0]);
    }
    else if (root->getRule() == "parameter_list : parameter_list COMMA type_specifier ID")
    {
        trav(root->children[0]);
    }
    else if (root->getRule() == "var_declaration : type_specifier declaration_list SEMICOLON")
    {
        travDeclList(root->children[1]);
        root->stackOff = root->children[1]->stackOff;
    }
    else if (root->getRule() == "func_definition : type_specifier ID LPAREN RPAREN compound_statement")
    {
        check_global = 0;
        currFunc = root->children[1]->_name;
        if (code_start)
            ;
        else
        {
            code_start = 1;
            ASM << ".CODE\r\n";
        }
        string func_name = root->children[1]->_name;
        ASM << func_name << " PROC\n";
        if (func_name == "main")
        {
            ASM << "\tMOV AX, @DATA\n";
            ASM << "\tMOV DS, AX\n";
        }
        ASM << "\tPUSH BP\n";
        ASM << "\tMOV BP, SP\n";
        for (auto x : root->children)
        {
            trav(x);
        }
        ASM << func_name << "_leaving:\n"; // this is just for checking
        /// Now add the stack offset. added. updated.
        ASM << "\tADD SP," << -root->children[4]->stackOff << "\n";
        ASM << "\tPOP BP\n";
        ////Now the exit function code.
        if (func_name == "main")
        {
            ASM << "\tMOV AX, 4CH\n";
            ASM << "\tINT 21H\n";
            ASM << func_name << " ENDP\n";
        }
        else
        {
            ASM << "\tRET\n";
            ASM << func_name << " ENDP\n";
        }
    }
    else if (root->getRule() == "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement")
    {
        check_global = 0;
        currFunc = root->children[1]->_name;
        if (code_start)
            ;
        else
        {
            code_start = 1;
            ASM << ".CODE\r\n";
        }
        trav(root->children[3]); /// Need to process the parameter list here first.
        string func_name = root->children[1]->_name;
        ASM << func_name << " PROC\n";
        if (func_name == "main")
        {
            ASM << "\tMOV AX, @DATA\n";
            ASM << "\tMOV DS, AX\n";
        }
        ASM << "\tPUSH BP\n";
        ASM << "\tMOV BP, SP\n";
        trav(root->children[5]);
        ASM << func_name << "_leaving:\n";
        if (func_name == "main")
        {
            ASM << "\tMOV AX, 4CH\n";
            ASM << "\tINT 21H\n";
        }
        // cout << "here : " << root->children[5]->stackOff << "\n";
        ASM << "\tADD SP, " << -root->children[5]->stackOff << "\n";
        ASM << "\tPOP BP\n";
        if (func_name != "main")
        {
            ASM << "\tRET\n";
        }
        ASM << func_name << " ENDP\n";
    }
    else if (root->getRule() == "compound_statement : LCURL statements RCURL")
    {
        /// process labels.
        if (root->lEnd.size() == 0)
            root->lEnd = newLabel();

        root->children[1]->lEnd = root->lEnd;
        trav(root->children[1]);
        root->stackOff = root->children[1]->stackOff;
    }
    else if (root->getRule() == "statements : statement")
    {
        root->children[0]->lEnd = root->lEnd;
        trav(root->children[0]);
        root->stackOff = root->children[0]->stackOff;
        ASM << root->lEnd << ":\n";
    }
    else if (root->getRule() == "statements : statements statement")
    {
        root->children[0]->lEnd = newLabel();
        root->children[1]->lEnd = root->lEnd;
        for (auto x : root->children)
        {
            trav(x);
        }
        root->stackOff = min(root->children[1]->stackOff, root->children[0]->stackOff);
        // print the label.
        ASM << root->lEnd << ":\n";
    }
    else if (root->getRule() == "statement : var_declaration")
    {
        trav(root->children[0]);
        root->stackOff = root->children[0]->stackOff;
    }
    else if (root->getRule() == "statement : expression_statement")
    {
        trav(root->children[0]);
        root->stackOff = root->children[0]->stackOff;
    }
    else if (root->getRule() == "statement : compound_statement")
    {
        root->children[0]->lEnd = newLabel();
        trav(root->children[0]);
        root->stackOff = root->children[0]->stackOff;
    }
    else if (root->getRule() == "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement")
    {
        trav(root->children[2]);
        string loopLabel = newLabel();
        ASM << loopLabel << ":\n";
        root->children[3]->is_cond = 1;
        root->children[3]->tlab = newLabel();
        root->children[3]->flab = root->lEnd;
        root->children[6]->lEnd = newLabel(); /// confused.
        // root->children[6]->lEnd = root->lEnd;
        trav(root->children[3]);
        ASM << root->children[3]->tlab << ":\n";
        trav(root->children[6]);
        trav(root->children[4]);
        ASM << "\tJMP " << loopLabel << "\n";
    }
    else if (root->getRule() == "statement : IF LPAREN expression RPAREN statement")
    {
        root->children[2]->is_cond = 1;
        root->children[2]->tlab = newLabel();
        root->children[2]->flab = root->lEnd;
        root->children[4]->lEnd = root->lEnd;
        trav(root->children[2]);
        ASM << root->children[2]->tlab << ":\n";
        trav(root->children[4]);
    }
    else if (root->getRule() == "statement : IF LPAREN expression RPAREN statement ELSE statement")
    {
        root->children[2]->is_cond = 1;
        root->children[2]->tlab = newLabel();
        root->children[2]->flab = newLabel();
        root->children[4]->lEnd = root->children[2]->flab;
        root->children[6]->lEnd = root->lEnd;
        trav(root->children[2]);
        ASM << root->children[2]->tlab << ":\n";
        trav(root->children[4]);
        ASM << "\tJMP " << root->lEnd << "\n";
        ASM << root->children[2]->flab << ":\n";
        trav(root->children[6]);
    }
    else if (root->getRule() == "statement : WHILE LPAREN expression RPAREN statement")
    {
        string loopLabel = newLabel();
        ASM << loopLabel << ":\n";
        root->children[2]->is_cond = 1;
        root->children[2]->tlab = newLabel();
        root->children[2]->flab = root->lEnd;
        root->children[4]->lEnd = root->lEnd;
        trav(root->children[2]);
        ASM << root->children[2]->tlab << ":\n";
        trav(root->children[4]);
        ASM << "\tJMP " << loopLabel << "\n";
    }
    else if (root->getRule() == "statement : PRINTLN LPAREN ID RPAREN SEMICOLON")
    {
        if (root->children[2]->is_global)
        {
            ASM << "\tMOV AX, " << root->children[2]->_name << "\n";
            ASM << "\tCALL PRINT_OUT\n";
            // ASM << "\tCALL NEWLINE\n";
        }
        else
        {
            ASM << "\tPUSH BP\n";
            ASM << "\tMOV BX, " << root->children[2]->stackOff << "\n";
            ASM << "\tADD BP, BX\n";
            ASM << "\tMOV AX, [BP]\n";
            ASM << "\tCALL PRINT_OUT\n";
            // ASM << "\tCALL NEWLINE\n";
            ASM << "\tPOP BP\n";
        }
    }
    else if (root->getRule() == "statement : RETURN expression SEMICOLON")
    {
        trav(root->children[1]);
        ASM << "\tMOV DX,CX\n";
        ASM << "\tJMP " << currFunc << "_leaving\n";
    }
    else if (root->getRule() == "expression_statement : expression SEMICOLON")
    {
        root->children[0]->tlab = root->tlab;
        root->children[0]->flab = root->flab;
        root->children[0]->is_cond = root->is_cond;
        trav(root->children[0]);
    }
    else if (root->getRule() == "expression : variable ASSIGNOP logic_expression")
    {
        /// dont need to propagate conditions anymore
        trav(root->children[2]);
        root->children[0]->is_cond = false;
        root->children[2]->is_cond = false;
        if (root->children[0]->is_global && !root->children[0]->isArr.first) /// basically any global variable
        {
            trav(root->children[0]);
            ASM << "\tMOV " << root->children[0]->_name << ", CX\n";
        }
        else
        {
            ASM << "\tPUSH CX\n";
            trav(root->children[0]);
            root->stackOff = root->children[0]->stackOff;
            ASM << "\tPOP AX\n";
            ASM << "\tPOP CX\n";
            ASM << "\tMOV [BP], CX\n";
            ASM << "\tMOV BP, AX\n";
        }
        if (root->is_cond)
        {
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "expression : logic_expression")
    {
        root->children[0]->is_cond = root->is_cond;
        root->children[0]->flab = root->flab;
        root->children[0]->tlab = root->tlab;
        trav(root->children[0]);
    }
    else if (root->getRule() == "logic_expression : rel_expression")
    {
        root->children[0]->is_cond = root->is_cond;
        root->children[0]->flab = root->flab;
        root->children[0]->tlab = root->tlab;
        trav(root->children[0]);
    }
    else if (root->getRule() == "logic_expression : rel_expression LOGICOP rel_expression")
    {
        string logicOp = root->children[1]->_name;
        root->children[0]->is_cond = root->is_cond;
        root->children[2]->is_cond = root->is_cond;
        if (logicOp == "&&")
        {
            root->children[0]->flab = root->flab;
            root->children[2]->flab = root->flab;
            root->children[0]->tlab = newLabel() + "True_Jump";
            root->children[2]->tlab = root->tlab;
        }
        else if (logicOp == "||")
        {
            root->children[0]->tlab = root->tlab;
            root->children[0]->flab = newLabel() + "False_Jump"; /// to check for more clarity
            root->children[2]->tlab = root->tlab;
            root->children[2]->flab = root->flab;
        }
        trav(root->children[0]);
        if (root->is_cond)
        {
            if (logicOp == "&&")
                ASM << root->children[0]->tlab << ":\n";
            else
                ASM << root->children[0]->flab << ":\n";
        }
        else
            ASM << "\tPUSH CX\n";
        trav(root->children[2]);
        if (!root->is_cond)
        {
            ASM << "\tPOP AX\n";
            if (logicOp == "||")
            {
                string l1 = newLabel();
                string l2 = newLabel();
                string l3 = newLabel();
                string l4 = newLabel();
                ASM << "\tCMP AX, 0\n";
                ASM << "\tJE " << l1 << "\n";
                ASM << "\tJMP " << l2 << "\n";
                ASM << l1 << ":\n";
                ASM << "\tJCXZ " << l3 << "\n";
                ASM << l2 << ":\n";
                ASM << "\tMOV CX, 1\n";
                ASM << "\tJMP " << l4 << "\n";
                ASM << l3 << ":\n";
                ASM << "\tMOV CX, 0\n";
                ASM << l4 << ":\n";
            }
            else if (logicOp == "&&")
            {
                /// here l1 is the false label, l2->true label,l3-> ending label
                string l1 = newLabel();
                string l2 = newLabel();
                string l3 = newLabel();
                ASM << "\tCMP AX, 0\n";
                ASM << "\tJE " << l1 << "\n";
                ASM << "\tJCXZ " << l1 << "\n";
                ASM << "\tJMP " << l2 << "\n";
                ASM << l1 << ":\n";
                ASM << "\tMOV CX, 0\n";
                ASM << "\tJMP " << l3 << "\n";
                ASM << l2 << ":\n";
                ASM << "\tMOV CX, 1\n";
                ASM << l3 << ":\n"; /// ending label.
            }
        }
    }
    else if (root->getRule() == "rel_expression : simple_expression")
    {
        root->children[0]->is_cond = root->is_cond;
        root->children[0]->flab = root->flab;
        root->children[0]->tlab = root->tlab;
        trav(root->children[0]);
    }
    else if (root->getRule() == "rel_expression : simple_expression RELOP simple_expression")
    {
        // No more cond propagation.
        trav(root->children[0]);
        ASM << "\tPUSH CX\n";
        trav(root->children[2]);
        ASM << "\tPOP AX\n";
        ASM << "\tCMP AX, CX\n";
        string relop = root->children[1]->_name;
        if (root->tlab.size() == 0)
            root->tlab = newLabel();
        if (root->flab.size() == 0)
            root->flab = newLabel();
        ASM << JumpingCodeRelop(relop) << " " << root->tlab << "\n";
        ASM << "\tJMP " << root->flab << "\n";
        if (!root->is_cond)
        {
            ASM << root->tlab << ":\n";
            ASM << "\tMOV CX, 1\n";
            string leavingLab = newLabel();
            ASM << "\tJMP " << leavingLab << "\n";
            ASM << root->flab << ":\n";
            ASM << "\tMOV CX, 0\n";
            ASM << leavingLab << ":\n";
        }
    }
    else if (root->getRule() == "simple_expression : term")
    {
        root->children[0]->is_cond = root->is_cond;
        root->children[0]->flab = root->flab;
        root->children[0]->tlab = root->tlab;
        trav(root->children[0]);
    }
    else if (root->getRule() == "simple_expression : simple_expression ADDOP term")
    { /// No cond propagation here as well.
        trav(root->children[0]);
        ASM << "\tPUSH CX\n";
        trav(root->children[2]);
        ASM << "\tPOP AX\n";
        if (root->children[1]->_name == "+")
        {
            ASM << "\tADD CX, AX\n";
        }
        else if (root->children[1]->_name == "-")
        {
            ASM << "\tSUB AX,CX\n";
            ASM << "\tMOV CX,AX\n";
        }
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "term : unary_expression")
    {
        root->children[0]->is_cond = root->is_cond;
        root->children[0]->flab = root->flab;
        root->children[0]->tlab = root->tlab;
        trav(root->children[0]);
    }
    else if (root->getRule() == "term : term MULOP unary_expression")
    {
        /// No need to send cond anymore.
        trav(root->children[0]);
        ASM << "\tPUSH CX\n";
        trav(root->children[2]);
        ASM << "\tPOP AX\n";
        /// first operand is in AX, second operand is in CX.
        if (root->children[1]->_name == "*")
        {
            ASM << "\tIMUL CX\n";
            ASM << "\tMOV CX, AX\n";
        }
        else if (root->children[1]->_name == "/")
        {
            ASM << "\tCWD\n";
            ASM << "\tIDIV CX\n";
            ASM << "\tMOV CX, AX\n";
        }
        else if (root->children[1]->_name == "%")
        {
            ASM << "\tCWD\n";
            ASM << "\tIDIV CX\n";
            ASM << "\tMOV CX, DX\n";
        }

        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "unary_expression : factor")
    {
        root->children[0]->is_cond = root->is_cond;
        root->children[0]->flab = root->flab;
        root->children[0]->tlab = root->tlab;
        trav(root->children[0]);
    }
    else if (root->getRule() == "unary_expression : ADDOP unary_expression")
    {
        root->children[1]->is_cond = root->is_cond;
        root->children[1]->flab = root->flab;
        root->children[1]->tlab = root->tlab;
        trav(root->children[1]);
        if (root->children[0]->_name == "-")
        {
            ASM << "\tNEG CX\n";
        }
    }
    else if (root->getRule() == "unary_expression : NOT unary_expression")
    {
        root->children[1]->is_cond = root->is_cond;
        root->children[1]->flab = root->flab;
        root->children[1]->tlab = root->tlab;
        trav(root->children[1]);
        if (!root->is_cond)
        {
            string l1 = newLabel();
            string l2 = newLabel();
            ASM << "\tJCXZ " << l2 << "\n";
            ASM << "\tMOV CX, 0\n";
            ASM << "\tJMP " << l1 << "\n";
            ASM << l2 << ":\n";
            ASM << "\tMOV CX, 1\n";
            ASM << l1 << ":\n";
        }
    }
    else if (root->getRule() == "factor  : CONST_INT")
    {
        ASM << "\tMOV CX, " << root->_name << "\n";
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "factor  : CONST_FLOAT")
    {
        ASM << "\tMOV CX, " << root->_name << "\n";
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "factor : variable")
    {
        trav(root->children[0]);
        if (root->children[0]->is_global && !root->children[0]->isArr.first)
        {
            ASM << "\tMOV CX, " << root->children[0]->_name << "\n";
        }
        else
        {
            ASM << "\tMOV CX, [BP]\n";
            ASM << "\tPOP BP\n";
        }
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "factor : ID LPAREN argument_list RPAREN")
    {
        trav(root->children[2]);
        ASM << "\tCALL " << root->children[0]->_name << "\n";
        ASM << "\tMOV CX, DX\n";
        ASM << "\tADD SP, " << root->children[2]->stackOff << "\n";
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "factor : LPAREN expression RPAREN")
    {
        trav(root->children[1]);
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "factor  : variable INCOP")
    {
        trav(root->children[0]);
        if (!root->children[0]->isArr.first && root->children[0]->is_global) /// Should array be allowed?No
        {
            ASM << "\tMOV CX, " << root->children[0]->_name << "\n";
        }
        else
            ASM << "\tMOV CX, [BP]\n";
        ASM << "\tMOV AX, CX\n";
        if (root->children[1]->_name == "++")
        {
            ASM << "\tINC CX\n";
        }
        else if (root->children[1]->_name == "--")
        {
            ASM << "\tDEC CX\n";
        }

        if (root->children[0]->is_global)
        {
            ASM << "\tMOV " << root->children[0]->_name << ", CX\n";
        }
        else
        {
            ASM << "\tMOV [BP], CX\n";
            ASM << "\tPOP BP\n";
        }
        ASM << "\tMOV CX, AX\n";
        if (root->is_cond)
        {
            ASM << "\tJCXZ " << root->flab << "\n";
            ASM << "\tJMP " << root->tlab << "\n";
        }
    }
    else if (root->getRule() == "variable : ID")
    {
        if (root->is_global)
            ;
        else
        {
            ASM << "\tPUSH BP\n";
            ASM << "\tMOV BX, " << root->stackOff << "\n";
            ASM << "\tADD BP, BX\n";
        }
    }
    else if (root->getRule() == "variable : ID LTHIRD expression RTHIRD")
    {
        trav(root->children[2]);
        if (root->is_global) /// will test later.
        {
            ASM << "\tLEA SI, " << root->_name << "\n";
            ASM << "\tADD SI, CX\n";
            ASM << "\tADD SI, CX\n";
            ASM << "\tPUSH BP\n";
            ASM << "\tMOV BP, SI\n";
        }
        else
        {
            ASM << "\tPUSH BP\n";
            ASM << "\tMOV BX, CX\n";
            ASM << "\tADD BX, BX\n";
            ASM << "\tADD BX, " << root->stackOff << "\n";
            ASM << "\tADD BP,BX\n";
        }
    }
    else if (root->getRule() == "argument_list : arguments")
    {
        trav(root->children[0]);
        root->stackOff = root->children[0]->stackOff;
    }
    else if (root->getRule() == "arguments : arguments COMMA logic_expression")
    {
        trav(root->children[0]);
        trav(root->children[2]);
        ASM << "\tPUSH CX   ;This is actually function parameter\n";
        root->stackOff = root->children[0]->stackOff + 2;
    }
    else if (root->getRule() == "arguments : logic_expression")
    {
        trav(root->children[0]);
        ASM << "\tPUSH CX ;Another function paramter\n";
        root->stackOff = 2;
    }
    else
    {
        for (auto x : root->children)
        {
            trav(x);
        }
    }
}