#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <string>
#include <ctime>


#include "knife.h"



using namespace std;
using vecInt = vector<int>;
using vecInt2d =  vector <vector<int>>;
using vecDbl = vector<double>;
using vecDbl2d =  vector <vector<double>>;
using vecStr = vector<string>;

namespace _ = knife::_;


struct person {

    int age;
    string name;

    person(int age, string name) {
        this->age = age;
        this->name = name;
    }

    person() {
        this->age = 0;
        this->name = "Jon Doe";
    }
};

using person_ptr = shared_ptr<person>;

bool isEven(int item) {
    return item % 2 != 0;
}


void doubler(int & i){
    i *= i;
}

string getName(const person & p){
    return p.name;
}


double sum(auto && func, auto n){

    auto sum = 0.0;
    
    for(auto & i:_::range(n)){
        sum+=func(n);
    }   

    return sum;
}



int main() { 

    auto print = [](auto item ){
        cout << item << " ";
    };

   // cout << endl << "For Each Argument: ";
   // _::forArgs(print, 1, "Edgar", 2.12f, 'A');


   auto numbers = _::range(1,10);




   auto oddNumbers = _::reject<vecInt>(numbers, isEven);
   cout << endl << "Odd: ";
   _::forEach( oddNumbers, print);

   auto evenNumbers = _::filter<vecInt>(numbers, isEven);
   cout << endl << "Even: ";
   _::forEach( evenNumbers, print);

   evenNumbers = _::without<vecInt>(numbers, oddNumbers);
   cout << endl << "Even using without: ";
   _::forEach( evenNumbers, print);

   auto sum = _::reduce(numbers, 0, [](auto &currentSum, auto num){
       return currentSum + num;
   });
   cout << "\nsum of all :" << sum << endl;

   _::repeat(3, [](auto i){
       cout << "Hello World!!!!" << endl;
   });

   auto isFive = [](auto & num){ return num == 5; };
   cout << "Find five: " << _::find<int>(numbers, isFive);


   vector<person> group = {
           person{25,"Edgar"},
           person{19,"Andy"},
           person{27, "Marcos"},
           person{31, "Chris"}
   };

   auto getAge = [](const auto & p){ return p.age;};
   auto ages = _::map<vecInt>(group, getAge);
   cout << endl <<"Group ages: ";
   _::forEach(ages, print);

   auto names = _::map<vecStr>(group, getName);
   cout << endl <<"Group names: ";
   _::forEach(names, print);

   auto isGreaterThanTen = _::every(numbers,[](auto & num){ return num <= 10; });
   cout << "\nAll numbers <= 10 : " << (isGreaterThanTen ? "true" : "false");

   cout << "\nDoes numbers contain 5: " << ( _::contains(numbers, 5) ? "true" : "false");
   cout << "\nDoes numbers contain 69: " << ( _::contains(numbers, 69) ? "true" : "false");


   auto sortedNames = _::sortBy<vecStr>(names,[](auto & a, auto & b){
       return a < b;
   });
   cout << endl <<"Sorted names: ";
   _::forEach(sortedNames, print);

    return 0;
}