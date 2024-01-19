#include <bits/stdc++.h>
using namespace std;

class SymbolInfo
{
private:
    // IDtype -> VAR,ARA, FUNC
    // var_type -> INT,FLOAT
    // ret_functype -> INT, FLOAT , VOID
    string name, type, ID_type, var_type, ret_functype;
    int arr_ind, arr_sz;
    bool func_defined = false;
    SymbolInfo *next;

public:
    vector<int> all_ints;
    vector<float> all_floats;
    vector<string> List_params; // Stores INT,FLOAT
    SymbolInfo(string just_type)
    {
        var_type = just_type;
        if (var_type == "INT")
            all_ints.push_back(0);
        else if (var_type == "FLOAT")
            all_floats.push_back(0);
    }
    SymbolInfo(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->next = nullptr;
    }

    // modifying offline 3.
    void push_params(string arg) { List_params.push_back(arg); }
    void setVarType(string type)
    {
        var_type = type;
        if (var_type == "INT")
            all_ints.push_back(0);
        else if (var_type == "FLOAT")
            all_floats.push_back(0);
    }
    void setIDType(string type) { ID_type = type; }
    void setArraySize(int sz) { arr_sz = sz; }
    void setArrayInd(int val) { arr_ind = val; }
    void setFuncDefined() { func_defined = true; }
    void setFuncRet(string type) { ret_functype = type; }

    string getIDType() { return ID_type; }
    string getVarType() { return var_type; }
    int getAraySize() { return arr_sz; }
    string getFuncRet() { return ret_functype; }
    bool isFuncDefined() { return func_defined; }
    int getAraIndex() { return arr_ind; }

    // upto here.

    string getname()
    {
        return name;
    }
    string gettype() { return type; }
    void setNext(SymbolInfo *info2)
    {
        next = info2;
    }
    SymbolInfo *getNext() const { return this->next; }
};

class ScopeTable
{
private:
    int outmost_scope = 1;
    string current_ID;
    SymbolInfo **arr;
    ScopeTable *parent;
    int Size;
    int cnt;

public:
    ScopeTable(int sz)
    {
        arr = new SymbolInfo *[sz];
        this->Size = sz;
        for (int i = 0; i < sz; ++i)
        {
            arr[i] = nullptr;
        }
        this->parent = nullptr;
        this->cnt = 1;
    }
    void setCurrentID()
    {
        ScopeTable *par = this->getParentScope();
        if (par)
        {
            this->current_ID = this->getParentScope()->getCurrentID() + "." + to_string(par->getChild());
        }
        else
            this->current_ID = to_string(outmost_scope);
    }
    int getChild() { return this->cnt; }
    void INC_Child() { this->cnt++; }
    string getCurrentID()
    {
        return this->current_ID;
    }
    void setParentScope(ScopeTable *table)
    {
        this->parent = table;
    }
    ScopeTable *getParentScope()
    {
        return this->parent;
    }
    unsigned long long int sdbmhash(string &str)
    {
        unsigned long long int Hashval = 0;
        for (char c : str)
        {
            Hashval = c + (Hashval << 6) + (Hashval << 16) - Hashval;
        }
        return Hashval % Size;
    }
    bool Insert(SymbolInfo *Info)
    {
        string name = Info->getname();
        int index = sdbmhash(name);
        SymbolInfo *curr = arr[index], *par = nullptr;
        if (curr == nullptr)
        {
            arr[index] = Info;
            return true;
        }
        while (curr)
        {
            if (curr->getname() == name)
            {
                return false;
            }
            par = curr;
            curr = curr->getNext();
        }
        par->setNext(Info);
        return true;
    }
    SymbolInfo *LookUp(string &Name)
    {
        int index = sdbmhash(Name);
        SymbolInfo *curr = arr[index];
        while (curr)
        {
            if (curr->getname() == Name)
            {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }
    SymbolInfo *LookUp2(string &Name, string &type)
    {
        int index = sdbmhash(Name);
        SymbolInfo *curr = arr[index];
        while (curr)
        {
            if (curr->getname() == Name && curr->getIDType() == type)
            {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }
    bool Delete(string &Name, int &cnt, int &ind)
    {
        ind = sdbmhash(Name);
        SymbolInfo *curr = arr[ind];
        SymbolInfo *par = nullptr;
        while (curr)
        {
            if (curr->getname() == Name)
            {
                if (par == nullptr)
                {
                    arr[ind] = curr->getNext();
                }
                else
                {
                    par->setNext(curr->getNext());
                }
                delete curr;
                return true;
            }
            par = curr;
            curr = curr->getNext();
            cnt++;
        }
        return false;
    }
    void Print(ofstream &out)
    {
        out << "\tScopeTable# " << this->current_ID << "\n";
        for (int i = 0; i < Size; ++i)
        {
            SymbolInfo *curr = arr[i];
            out << "\t" << i + 1;
            if (curr)
                out << " --> ";
            while (curr)
            {
                out << "(" << curr->getname() << "," << curr->gettype() << ")";
                if (curr->getNext())
                    out << " --> ";
                curr = curr->getNext();
            }
            out << "\n";
        }
    }
    ~ScopeTable()
    {
        for (int i = 0; i < Size; ++i)
        {
            free(arr[i]);
        }
        delete (arr);
    }
};

class SymbolTable
{
private:
    ScopeTable *curr;
    int Size;

public:
    SymbolTable(int Size)
    {
        this->curr = nullptr;
        this->Size = Size;
    }
    void EnterScope()
    {
        if (curr)
        {
            ScopeTable *temp = new ScopeTable(this->Size);
            temp->setParentScope(curr);
            curr = temp;
            curr->setCurrentID();
        }
        else
        {
            curr = new ScopeTable(Size);
            curr->setCurrentID();
        }
    }
    bool ExitScope()
    {
        if (curr)
        {
            ScopeTable *temp = curr;
            if (curr->getParentScope())
            {
                curr = curr->getParentScope();
                curr->INC_Child();
                delete temp;
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    bool Insert(SymbolInfo *Info)
    {
        if (curr)
        {
            return curr->Insert(Info);
        }
        return false;
    }
    bool Remove(string &symbol, int &cnt, int &index)
    {
        if (curr)
        {
            return curr->Delete(symbol, cnt, index);
        }
        return false;
    }
    SymbolInfo *LookUp2(string &Name, string &type)
    {
        ScopeTable *mov = curr;
        while (mov)
        {
            SymbolInfo *temp = mov->LookUp2(Name, type);
            if (temp)
            {
                return temp;
            }
            else
            {
                mov = mov->getParentScope();
            }
        }
        return nullptr;
    }
    SymbolInfo *LookUp(string &Name)
    {
        ScopeTable *mov = curr;
        while (mov)
        {
            SymbolInfo *temp = mov->LookUp(Name);
            if (temp)
            {
                return temp;
            }
            else
            {
                mov = mov->getParentScope();
            }
        }
        return nullptr;
    }
    void PrintCurrentScopeTable(ofstream &out)
    {
        if (curr)
        {
            curr->Print(out);
        }
        else
            out << "\tNo ScopTables created yet.\n";
    }
    void PrintAllScopeTables(ofstream &out)
    {
        ScopeTable *temp = curr;
        if (!temp)
        {
            out << "\tNo ScopeTables available.\n";
            return;
        }
        while (temp)
        {
            temp->Print(out);
            temp = temp->getParentScope();
        }
    }
    string getCurrentID()
    {
        return curr->getCurrentID();
    }
    void cleanUp(ofstream &out)
    {
        if (curr)
        {
            while (curr)
            {
                out << "\tScopeTable# " << curr->getCurrentID() << " deleted\n";
                ScopeTable *temp = curr;
                curr = curr->getParentScope();
                delete temp;
            }
        }
    }
    ~SymbolTable()
    {
        if (curr)
        {
            while (curr)
            {
                ScopeTable *temp = curr;
                curr = curr->getParentScope();
                delete temp;
            }
        }
    }
};
