#include<bits/stdc++.h>

using namespace std;

#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define sz(s) (int)s.size()


int priority(char op)
{
    if (op == '-' || op == '+')
        return 1;
    if (op == '*' || op =='/')
        return 2;
    if (op == '^')
        return 3;
    return -1;
}

int logic_priority(string lg)
{
    if (lg == "~")   return 4;
    if (lg == "&" || lg =="|")  return 3;
    if (lg == "->")    return 2;
    if (lg == "<->") return 1;
    return -1;
}

bool isOperator(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

string Infix2Postfix(string infix)
{
    string postfix="";
    stack<char> st;
    for (int i=0;i<sz(infix);i++)
    {
        char ch=infix[i];
        if (infix[i] >= '0' && infix[i]<='9')
        {
            postfix += infix[i];
        }   
        else if (ch == '(')
            st.push(ch);
        else if (ch == ')')
        {
            while (st.top() != '('){
                postfix=postfix + st.top();
                st.pop();
            }
            st.pop();
        }
        else if (isOperator(ch))
        {
            while (!st.empty() && st.top()!='(' && priority(ch) <= priority(st.top()))
            {
                postfix=postfix + st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty())
    {
        postfix=postfix + st.top();
        st.pop();
    }
    return postfix;
}


int main() {
    string test;    int ntest;
    getline(cin, test);     ntest = stoi(test);
    string tmp; getline(cin, tmp);
    while (ntest--) {
        string ch;
        string s;
        while (getline(cin, ch) && sz(ch) != 0) s+=ch;
        if (ntest >= 1)    cout << Infix2Postfix(s) << "\n\n";
        else cout << Infix2Postfix(s) << "\n";
    }
}