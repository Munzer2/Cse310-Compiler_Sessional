#include<bits/stdc++.h>
using namespace std;

class SymbolInfo{
private:
    string name,type;
    SymbolInfo *next;
public:
    SymbolInfo(string name,string type)
    {
        this->name = name;
        this->type = type;
        this->next = nullptr;
    }
    string getname() { return name; }
    string gettype() { return type; }
    void setNext(SymbolInfo* info2)
    {
        next = info2;
    }
    SymbolInfo* getNext() const { return this->next; }
};

int outmost = 1;

class ScopeTable{
private:
    string current_ID;
    SymbolInfo **arr;
    ScopeTable *parent;
    int Size;
    int cnt;
    public:
        ScopeTable(int sz)
        {
            arr = new SymbolInfo*[sz];
            this->Size = sz ;
            for(int i = 0; i < sz; ++i )
            {
                arr[i] = nullptr;
            }
            this->parent = nullptr;
            this->cnt = 1;
        }
        void setCurrentID()
        {
            ScopeTable *par = this->getParentScope();
            if(par)
            {
                this->current_ID = this->getParentScope()->getCurrentID() + "." + to_string(par->getChild());
            }
            else this->current_ID = to_string(outmost);
        }
        int getChild() {  return this->cnt; }
        void INC_Child() {  this->cnt++;  }
        string getCurrentID()
        {
            return this->current_ID;
        }
        void setParentScope(ScopeTable* table)
        {
            this->parent = table;
        }
        ScopeTable* getParentScope()
        {
            return this->parent;
        }
        unsigned long long int sdbmhash(string &str)
        {
            unsigned long long int Hashval = 0;
            for(char c: str)
            {
                Hashval = c + (Hashval << 6) + (Hashval << 16) - Hashval;
            }
            return Hashval % Size;
        }
        bool Insert(SymbolInfo *Info,int &cnt,int &index)
        {
            string name = Info->getname();
            index = sdbmhash(name);
            SymbolInfo *curr = arr[index], *par = nullptr;
            if(curr == nullptr)
            {
                arr[index] = Info;
                return true;
            }
            while(curr)
            {
                if(curr->getname() == name)
                {
                    return false;
                }
                par = curr;
                curr = curr->getNext();
                cnt++;
            }
            par->setNext(Info);
            return true;
        }
        SymbolInfo* LookUp(string &Name,int &cnt,int &index,string &ID)
        {
            index= sdbmhash(Name);
            SymbolInfo *curr = arr[index];
            while(curr)
            {
                if( curr->getname() == Name )
                {
                    ID = this->current_ID;
                    return curr;
                }
                curr = curr->getNext();
                cnt++;
            }
            return nullptr;
        }
        bool Delete(string &Name, int& cnt, int& ind)
        {
            ind = sdbmhash(Name);
            SymbolInfo *curr = arr[ind];
            SymbolInfo *par = nullptr;
            while(curr)
            {
                if(curr->getname() == Name)
                {
                    if(par == nullptr)
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
            for(int i =0; i < Size; ++i)
            {
                SymbolInfo *curr = arr[i];
                out<< "\t" << i+1;
                if(curr) out << " --> ";
                while(curr)
                {
                    out << "(" <<  curr->getname() << "," << curr->gettype() << ")";
                    if(curr->getNext()) out << " --> ";
                    curr = curr->getNext();
                }
                out << "\n";
            }
        }
        ~ScopeTable()
        {
            for(int i =0; i < Size; ++i)
            {
                free(arr[i]);
            }
            delete(arr);
        }
};

class SymbolTable{
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
        if(curr)
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
        if(curr)
        {
            ScopeTable* temp = curr;
            if(curr->getParentScope())
            {
                curr = curr->getParentScope();
                curr->INC_Child();
                delete temp;
                return true;
            }
            else return false;
        }
        else return false;
    }
    bool Insert(SymbolInfo *Info,int &cnt, int &index)
    {
        if(curr)
        {
            return curr->Insert(Info,cnt,index);
        }
        return false;
    }
    bool Remove(string &symbol,int &cnt, int &index)
    {
        if(curr)
        {
            return curr->Delete(symbol,cnt,index);
        }
        return false;
    }
    SymbolInfo* LookUp(string &Name,int &cnt,int &index,string &ID)
    {
        ScopeTable *mov = curr;
        while(mov)
        {
            SymbolInfo *temp = mov->LookUp(Name,cnt,index,ID);
            if(temp)
            {
                return temp;
            }
            else
            {
                cnt = 0;
                mov = mov->getParentScope();
            }
        }
        return nullptr;
    }
    void PrintCurrentScopeTable(ofstream &out)
    {
        if(curr)
        {
            curr->Print(out);
        }
        else out << "\tNo ScopTables created yet.\n";
    }
    void PrintAllScopeTables(ofstream &out)
    {
        ScopeTable *temp = curr;
        if(!temp)
        {
            out << "\tNo ScopeTables available.\n";
            return;
        }
        while(temp)
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
        if(curr)
        {
            while(curr)
            {
                out << "\tScopeTable# " << curr->getCurrentID() << " deleted\n" ;
                ScopeTable* temp = curr;
                curr = curr->getParentScope();
                delete temp;
            }
        }
    }
    ~SymbolTable()
    {
        if(curr)
        {
            while(curr)
            {
                ScopeTable* temp = curr;
                curr = curr->getParentScope();
                delete temp;
            }
        }
    }
};
