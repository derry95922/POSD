#include <vector>
#include <fstream> 
#include <string.h>
#include <iostream>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/sort.h"
using namespace std;

void Sort_shape(vector<Shape*>&test_array,string method,string order){   
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
}

int main(int argc,char **argv){
    if(argc<5){
        cout<<"Wrong Argument!\n";
        return 0;
    }
    string input,output,method,order;
    input = argv[1];
    output = argv[2];
    method = argv[3];
    order = argv[4];

    ifstream in;
    in.open(input,ifstream::in);
    /*
    vector<string>content;
    split(content, input);
    */
    //split .txt
    string s;
    const char *del = " (),";
    vector<string>content;
	while(getline(in, s)){
        char *s_t = new char [s.length()]; 
		strcpy(s_t, s.c_str());		
		char *p;
        p = strtok(s_t,del);
        while(p){
        	//cout<<p<<endl;
            content.push_back(p);
            p=strtok(NULL,del);
        }
 		delete[] s_t;
    }
    //new test_array
    vector<Shape*>test_array;
    int temp=0;
    for(int i=0;i<content.size();i++){
            
        if(content[i]=="Circle"){
            test_array.push_back(new Circle(stod(content[i+1]))); 
        }
        else if(content[i]=="Rectangle"){
            test_array.push_back(new Rectangle(stod(content[i+1]),stod(content[i+2])));
        }
        else if(content[i]=="Triangle"){
            test_array.push_back(new Triangle(stod(content[i+1]),stod(content[i+2]),stod(content[i+3]),stod(content[i+4]),stod(content[i+5]),stod(content[i+6])));
        }    
    }
    in.close();
    
    Sort_shape(test_array,method,order);

    ofstream out;
    out.open(output,ofstream::out);
    out<<"[";
    for(int i=0; i < test_array.size(); i++){
        if(method == "area")out << test_array[i]->area(); 
        else if(method == "perimeter")out<< test_array[i]->perimeter();
        if(test_array.size()-1!=i)out<<',';
    }
    out<<"]";
    out.close();
    return 0;
}