// VectorVictor3.hpp ///////////////////////////////////////////////////////////
// Has anybody here seen Tron? /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Source.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#ifndef VectorVictor3
#define VectorVictor3

//#define VECTORVICTOR_DEBUG

#define Pi 	3.14159265358979323846
#define Tau 6.283185308								
// Hopefully this doesnt anger the anti-tau-ans. ooh wait, the antautans! Or
// maybe just anti-tauntans 
// anti-tauntans: smell even better on the inside!
#define Pau 4.712388980

// utility functions for formatting output

std::string Convert_to_string(float num, int precision);
std::string Convert_to_string(long int num);

namespace SI
{	std::string Get_formatted_value(float value, int precision, std::string unit);
	std::string Get_formatted_value(std::string prefix, float value, int precision, std::string unit);
	
	std::string Get_formatted_value(long int value, std::string unit);
	std::string Get_formatted_value(std::string prefix, long int value, std::string unit);
}

// The VectorVictor namespace //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef long double number;

namespace VectorVictor
{	
	
	class Vector3	
	{	// core entity of VectorVictor for now
		public:
		Vector3();
		// Init the vector as (0,0)
		Vector3(number ix, number iy, number iz);
		// Init the vector with the supplied values
		number x, y, z;
		// the actual data itself, stored as a long double
		public:
		void Set_x (number ix);
		void Set_y (number iy);
		void Set_z (number iz);	
		void Set_values(number ix, number iy, number iz);
		// exactly what it sounds like
		number Get_x();
		number Get_y();
		number Get_z();		
		// return the values of each element in the vector	
		std::string Get_vector(std::string unit);
		// returns a string nicely formatted with units and si prefixes
		// helpful for data retrieval when printing to a window and stuff
		// absolute monster of a function though
		number Get_vector_magnitude();	
		// returns the length of the vector						
		number Get_vector_magnitude_squared();
		// returns the length of the vector, but squared so we dont need to
		// run an expensive call to sqrt()	
		void Normalize();	
		// Normalizes the vector
		Vector3 Vector_normalized();	
		// (magnitude of 1)						
		bool Zero_vector();
		// returns true if the vector in question is the zero vector, ie (0,0,0)
								
								
		number Dot(VectorVictor::Vector3 &vector);
		// Returns the value of the dot product of the vector calling dot with
		// the vector that was passed as a parameter.  Not sensitive to order
		// so you can go wild with whichever object you choose to call it from
		VectorVictor::Vector3 Cross(VectorVictor::Vector3 &vector);
		// Returns the value of the cross product of the vector calling Cross()
		// with the vector passed as a parameter.
		// **IS sensitive to the order**, so it is important to remember that
		// the Vector3 calling the function is considered the first vector and
		// so on. v1 cross v2 = -(v2 cross v1) in vector maths
		
		
		//void Rotate_vector(long double rotation);
		// Rotate the vector clockwise by rotation in degrees
		
		// this... hmmm					
		//Vector2 Get_rotated_vector(long double rotation);
		
		// rotation calls are broken at the moment, since their behaviour is
		// much different in 3D than in 2D
		
		
		
		// returns a copy of the rotated vector				
		Vector3 operator + (const Vector3);							
		Vector3 operator += (const Vector3);
		// addition operators, just what they sound like
		// components are added along each axis							
		Vector3 operator - (const Vector3);							
		Vector3 operator -= (const Vector3);	
		// subtraction operators, same behaviour as 						
		Vector3 operator = (const Vector3 v);	
		// copy operator						
		
		Vector3 operator * (const number c);	
		Vector3 operator *= (const number c);				
		
		Vector3 operator / (const number c);	
		Vector3 operator /= (const number c);			
		// multiply each element by some value						
		bool operator != (const Vector3 v);							
		bool operator == (const Vector3 v);	
		// comparison operators, == returns true all elements are the same, and
		// != returns true if one or more are different				
		bool Is_nan();
		// try to compare each element of the vector against itself, and return
		// true if comparing it against itself fails to indicate that shit
		// went out the window (apparently this is a fundamental thing about
		// nan in C)	
		~Vector3(void);						
	};

	number Get_dot_product(Vector3 First_vector, Vector3 Second_vector);
	// and the same thing, but done with the objects passed through
	number Get_angle_between(Vector3 First_vector, Vector3 Second_vector);
	// returns the angle in radians, odd, usually degrees are better for return
	// types
	VectorVictor::Vector3 Get_cross_product(Vector3 First_vector, Vector3 Second_vector);
	// obviously we cant do a cross product in two space, what this actually
	// does is pretend the vectors are 3D vectors lying flat in the xy plane,
	// then calculate the z component of their cross and return it. This is
	// needed to calculate the magnitude of the Torque vector for a given force
	// by getting the cross of the Force with the radial vector, the definition
	// of torque
	number Get_vector_separation(Vector3 First_vector, Vector3 Second_vector);
	// Not sure this was ever even used, but I dont think it can hurt anything..
	
	
	
	
	
	
	
	
	
	
	
	
};

long double Absolute_value(long double value);


long double Minimum(long double value1, long double value2);
long double Maximum(long double value1, long double value2);
bool In_range(long double value1, long double value2, long double target_value);

#endif
