/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: severste
 *
 * Created on April 10, 2017, 3:49 PM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

vector<string> stringToVector(const string & str){
    vector<string> postfixNot;
    stack<string> stack;
    string tmp;
    for( auto it = str.begin(); it <= str.end(); it++){
        if( it != str.begin() && ( *it == 47 || *it == 45 || (*it < 44 && *it > 39) ) ){
            postfixNot.push_back(tmp);
            tmp.erase(tmp.begin(), tmp.end());
            string a;
            a.assign(1, *it);
            postfixNot.push_back(a);
        }else{
            tmp.push_back(*it);
        }
    }
    return postfixNot;
}

void vectorToPostfixNot( vector<string> & vec ){
    pair<string, int> operatorPrecedence;
    vector<string> tmp;
    stack<string> stack;
    for(auto it = vec.begin(); it <= vec.end(); it++){
        if( (*it != "+") && (*it != "-") && (*it != "*") && (*it != "/") && (*it != "(") && (*it != ")") && (*it != "^") ){
            tmp.push_back(*it);
        }else{
            if(stack.empty() || *it == "("){
                stack.push(*it);
            }else if(*it == ")"){
                while( stack.top() != "(" ){
                    vec.push_back(stack.top());
                    stack.pop();
                }
            }else{
                if(*it < stack.top()){
                    stack.push(*it);
                }
            }
        }    
    }
    vec.erase(vec.begin(), vec.end());
    vec = tmp;
}
/*
 * 
 */
int main(int argc, char** argv) {
    
    string str1 = "a+b*(c-d)";
    string str = "-10+2*sin(4-1)";
    string str2 = "(4-1)";
    vector<string> vec;
    vec = stringToVector(str2);
    
    for(auto it = vec.begin(); it <= vec.end(); it++){
       cout << *it << "|";
    }
    cout << "\n===================" << endl;
    //vectorToPostfixNot(vec);
   // for(auto it = vec.begin(); it <= vec.end(); it++){
      //  cout << *it << ";";
    //}
    cout << endl;

    return 0;
}

