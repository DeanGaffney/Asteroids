// ===============================================
// @file   text_Vector2f.cpp
// @author kmurphy
// @brief  Test driver for class Vector2f
// ===============================================

#include <iostream>
#include "Vector2f.h"

using namespace std;

int main () {
	
	int DEBUG = 1;
	int failures = 0;
	int totalFailures = 0;
	
	
	cout <<"Testing class Vector2f ... \n";

	cout <<"Test 1 - Static members ...\n";
	cout <<"\tRounding error tolerance (EPS) = " <<Vector2f::EPS <<endl;
	cout <<"\tUnit vector along x-axis (X) = " <<Vector2f::X <<endl;
	cout <<"\tUnit vector along y-axis (X) = " <<Vector2f::Y <<endl;

	cout <<"Test 2 - Basic arithmetic operations ...\n";


	cout <<"\tTest 2a - formula : a - 2*a = -a \n";
	failures = 0;
	for(int k=0; k<10; ++k) {
		Vector2f a = Vector2f(randomFloatWithError(0,10), randomFloatWithError(0,10));
		Vector2f lhs = a - 2*a;
		Vector2f rhs = -a;
		
		failures += (lhs!=rhs);
		
		if (DEBUG) {
			cout <<"\t\t" <<lhs <<"\t " <<rhs 
				<<"\t"  << (lhs==rhs ? "PASS" : "FAILED") 
				<<endl;
		}
	}
	cout << "\tNumber of failures = " <<failures <<endl; 
	totalFailures += failures;


	cout <<"\tTest 2b - formula : 2*(a + b) - b = 2*a + b \n";
	failures = 0;
	for(int k=0; k<10; ++k) {
		Vector2f a = Vector2f(randomFloatWithError(0,10), randomFloatWithError(0,10));
		Vector2f b = Vector2f(randomFloatWithError(0,10), randomFloatWithError(0,10));
		Vector2f lhs = 2*(a+b) - b;
		Vector2f rhs = 2*a + b;
		
		failures += (lhs!=rhs);
		
		if (DEBUG) {
			cout <<"\t\t" <<lhs <<"\t " <<rhs 
				<<"\t"  << (lhs==rhs ? "PASS" : "FAILED") 
				<<endl;
		}
	}
	cout << "\tNumber of failures = " <<failures <<endl; 
	totalFailures += failures;


	cout <<"\tTest 2c - formula : (1,0) + (2,0) + ... + (n,0) = (n*(n+1)/2,0) \n";
	failures = 0;
	{
		int n = 10;
		Vector2f a = Vector2f();
		for(int k=1; k<=n; ++k) {
			a += Vector2f(k,0);
			Vector2f lhs = a;
			Vector2f rhs = Vector2f(k*(k+1)/2.0f, 0);

			failures += (lhs!=rhs);
		
			if (DEBUG) {
				cout <<"\t\t" <<lhs <<"\t " <<rhs 
					<<"\t"  << (lhs==rhs ? "PASS" : "FAILED") 
					<<endl;
			}
		}
	}
	cout << "\tNumber of failures = " <<failures <<endl; 
	totalFailures += failures;


	cout <<"\tTest 2d - formula dot(a,a) = a.lengthSqr() ...\n";
	failures = 0;
	for(int k=0; k<10; ++k) {
		Vector2f a = Vector2f(randomFloatWithError(0,10), randomFloatWithError(0,10));
		float lhs = a.dot(a);
		float rhs = a.lengthSqr();
		
		failures += !isEqual(lhs,rhs);
		
		if (DEBUG) {
			cout <<"\t\t" <<lhs <<"\t " <<rhs 
				<<"\t"  << (isEqual(lhs,rhs) ? "PASS" : "FAILED") 
				<<endl;
		}
	}
	cout << "\tNumber of failures = " <<failures <<endl; 
	totalFailures += failures;


	cout <<"\tTest 3 - input/output using overloaded stream operators \n";
	failures = 0;
	for (int k=0; k<10; ++k) {
		Vector2f a = Vector2f(randomFloatWithError(0,10), randomFloatWithError(0,10));
		std::ostringstream outs;
		outs <<a.x <<" " <<a.y;
		string s = outs.str();
		std::stringstream stream(s);
		Vector2f b;
		stream >> b;
		failures += (a!=b);
		if (DEBUG) {
			cout <<"\t\t" <<a <<"\t " <<s
				<<"\t"  << ((a==b) ? "PASS" : "FAILED") 
				<<endl;
		}
	}
	cout << "\tNumber of failures = " <<failures <<endl; 
	totalFailures += failures;
	
	cout << "\n\tTotal number of failures = " <<totalFailures <<endl; 
	
	return 0;
}



