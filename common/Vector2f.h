// ===============================================
// @file   Vector2f.h
// @author kmurphy
// @brief  Simple implementation of 2D (float) vectors
// ===============================================

#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <string>
#include <sstream>

#include "math.h"

class Vector2f {
	
public:

	static const float EPS;

	static const Vector2f X;
	static const Vector2f Y;
	static const Vector2f ZERO;
		
	float x;
	float y;

	// -----------------------------------------------
	// Constructors / Destructor 
	// -----------------------------------------------
	
	Vector2f (const float x=0, const float y=0) : x(x), y(y) {}

	Vector2f (const Vector2f & other) : x(other.x), y(other.y) {}

	static Vector2f unitVector (const float radian) {
		return Vector2f(cos(radian),sin(radian));
	} 
	
	// -----------------------------------------------
	// Operations on single vectors (with this const)
	// -----------------------------------------------
	
	Vector2f operator - () const { return Vector2f (-x, -y); }
	
	float lengthSqr () const { return x*x + y*y; } 

	float length () const { return (float) sqrt(lengthSqr()); } 

	Vector2f normal () const { return Vector2f(-y,x); }

	Vector2f rotate (const float degrees) const { 
		float rad = DEG_TO_RAD*degrees;
		float c = cos(rad), s = sin(rad);
		return Vector2f (x*c-s*y, s*x+c*y); 
	}

	const std::string toString() const {
		std::ostringstream outs;
		outs <<"(" <<x <<", " <<y <<")";
		return outs.str();
	}
	
	friend std::ostream& operator <<(std::ostream& outputStream, const Vector2f& v);	

	// -----------------------------------------------
	// Operations on single vectors (and updating this)
	// -----------------------------------------------
	Vector2f & reset () { x = y = 0.0f;   return *this; }

	Vector2f & normalize () { 
		float factor = 1.0f/length(); 
		x *= factor;
		y *= factor;
		return *this;
	}

	friend std::istream& operator >>(std::istream& inputStream, Vector2f& v);

	// -----------------------------------------------
	// Operations on vector and scalar (with this const)
	// -----------------------------------------------

	Vector2f operator * (float scalar) const { 
		return Vector2f(x*scalar, y*scalar); 
	}

	Vector2f operator / (float scalar) const { 
		return Vector2f(x/scalar, y/scalar); 
	}

	bool operator == (const Vector2f other) const { 
		return (fabs(x-other.x) + fabs(y-other.y) < Vector2f::EPS); 
	}

	bool operator!=(const Vector2f& other) const {
		return !(*this==other);
	}
	
	friend Vector2f operator * (float scalar, const Vector2f& v);
	
	// -----------------------------------------------
 	// Operations on vector and scalar (and updating this)
	// -----------------------------------------------
	
	Vector2f & operator *= (float scalar) { 
		x *= scalar;   
		y *= scalar;   
		return *this; 
	}

	Vector2f & operator /= (float scalar) { 
		x /= scalar;   
		y /= scalar;   
		return *this; 
	}
	
	// -----------------------------------------------
	// Operations on two vectors (with this const)
	// -----------------------------------------------

	Vector2f operator + (const Vector2f & other) const { 
		return Vector2f (x+other.x, y+other.y); 
	}

	Vector2f operator - (const Vector2f & other) const { 
		return Vector2f (x-other.x, y-other.y); 
	}
		
	float dot (const Vector2f & other) const { 
		return x*other.x + y*other.y; 
	}

	friend float dot(const Vector2f& u, const Vector2f& v);
		
	// -----------------------------------------------
	// Operations on two vectors (and updating this)
	// -----------------------------------------------
	
	Vector2f & operator += (const Vector2f & other) { 
		x += other.x;   
		y += other.y;   
		return *this; 
	}

	Vector2f & operator -= (const Vector2f & other) { 
		x -= other.x;   
		y -= other.y;   
		return *this; 
	}

};

#endif 


