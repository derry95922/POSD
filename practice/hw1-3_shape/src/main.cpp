#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<string.h>
#include"shape.h"
#include"circle.h"
#include"rectangle.h"
#include"triangle.h"
#include"sort.h"

using namespace std;
int main(int argc,char **argv){
    if(argc<5){
        cout<<"few argc!!!\n";
        return 0;
    }
    string input,output,method,order;
    input=argv[1];
    output=argv[2];
    method=argv[3];
    order=argv[4];
    
    ifstream in;
    in.open(input,ifstream::in);
    vector<string>content;
    string s;
    const char *del = " ,()";
    while(getline(in,s)){
        char *s_t=new char[s.length()];
        strcpy(s_t,s.c_str());
        char *p=strtok(s_t,del);
        while(p){
            content.push_back(p);
            p=strtok(NULL,del);
        }
        delete[] s_t;
    }
    in.close();

    vector<Shape*>test_array;
    for(int i=0;i<content.size();i++){
        if(content[i]=="Circle")test_array.push_back(new Circle(stod(content[i+1])));
        else if(content[i]=="Rectangle")test_array.push_back(new Rectangle(stod(content[i+1]),stod(content[i+2])));
        else if(content[i]=="Triangle")test_array.push_back(new Triangle(stod(content[i+1]),stod(content[i+2]),stod(content[i+3]),stod(content[i+4]),stod(content[i+5]),stod(content[i+6])));
    }

    Sort ting(&test_array);
    if(method == "area"){
        if(order == "inc"){
            ting.sortArea([](Shape * a, Shape *b){return a->area() < b->area();});
        }else if(order == "dec"){
            ting.sortArea([](Shape * a, Shape *b){return a->area() > b->area();});
        }else cout<<"order?\n";
    }else if(method == "perimeter"){
        if(order == "inc"){
            ting.sortPerimeter(perimeterAscendingComparison);
        }else if(order == "dec"){
            ting.sortPerimeter(perimeterDescendingComparison);
        }else cout<<"order?\n";
    }else cout<< "method?\n";

    ofstream out;
    out.open(output,ofstream::out);
    out<<"[";
    for(int i=0;i<test_array.size();i++){
        if(method == "area")out << test_array[i]->area(); //要給他指定的目標
        else if(method == "perimeter")out<< test_array[i]->perimeter();
        if(i!=(test_array.size()-1))out<<",";
    }
    out<<"]";
    out.close();
}