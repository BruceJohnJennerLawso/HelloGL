// VectorVictor3.cpp ///////////////////////////////////////////////////////////
// Has anybody here seen Tron? /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "VectorVictor3.hpp"
#include <iostream>
#include <math.h>	// Roger, Roger.
//#include "Inertia_moment.h"




std::string Convert_to_string(float num, int precision)
{	// the solution to all the problems with MS Windows not having a proper
	// to_string() call, we simply dump any value into the function, and get it
	// printed back at whatever precision we like
	
	// this should be made a template function for the type of the value to
	// be passed through
	std::stringstream s;
	s << std::setprecision(precision) << num;
	return s.str();
}	
// this is a really handy function
// so much of like
// my preciousss

std::string Convert_to_string(long int num)
{	// the solution to all the problems with MS Windows not having a proper
	// to_string() call, we simply dump any value into the function, and get it
	// printed back at whatever precision we like
	
	// this should be made a template function for the type of the value to
	// be passed through
	std::stringstream s;
	s << std::to_string((long long)num);
	return s.str();
}	

std::string SI::Get_formatted_value(float value, int precision, std::string unit)
{	std::string formatted_value = Convert_to_string(value, precision);
	std::string space = " ";
	formatted_value.append(space);
	formatted_value.append(unit);
	return formatted_value;
}

std::string SI::Get_formatted_value(std::string prefix, float value, int precision, std::string unit)
{	std::string formatted_value = Convert_to_string(value, precision);
	std::string space = " ";
	prefix.append(space);
	prefix.append(formatted_value);
	prefix.append(space);
	prefix.append(unit);
	return prefix;
}

std::string SI::Get_formatted_value(long int value, std::string unit)
{	std::string formatted_value = Convert_to_string(value);
	std::string space = " ";
	formatted_value.append(space);
	formatted_value.append(unit);
	return formatted_value;
}

std::string SI::Get_formatted_value(std::string prefix, long int value, std::string unit)
{	std::string formatted_value = Convert_to_string(value);
	std::string space = " ";
	prefix.append(space);
	prefix.append(formatted_value);
	prefix.append(space);
	prefix.append(unit);
	return prefix;
}




// The VectorVictor namespace //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// VV3 Constructors ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

VectorVictor::Vector3::Vector3 ()
{	// if nothing is passed, we assume the user wanted (0,0)
	Set_values(0,0,0);	
}	

VectorVictor::Vector3::Vector3(number ix, number iy, number iz)
{	// otherwise we set the values of the vector as requested
	Set_values(ix, iy, iz);
}

// Set/Get Operators ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void VectorVictor::Vector3::Set_x(number ix)
{	x = ix;					
}

void VectorVictor::Vector3::Set_y(number iy)
{	y = iy;					
}

void VectorVictor::Vector3::Set_z(number iz)
{	z = iz;					
}

void VectorVictor::Vector3::Set_values(number ix, number iy, number iz)
{	this->Set_x(ix);
	this->Set_y(iy);
	this->Set_z(iz);
}

number VectorVictor::Vector3::Get_x()
{	return x;
}

number VectorVictor::Vector3::Get_y()
{	return y;
}

number VectorVictor::Vector3::Get_z()
{	return z;
}

// and equally boring getters that just return the value itself

std::string VectorVictor::Vector3::Get_vector(std::string unit)	// this would make a lot of sense as a template function for the cast type
{	// the idea behind this is to provide a nice interface for getting strings
	// of a given vector formatted nicely with brackets, unit abbreviations
	// (meters, kilograms, gees, etc.) and SI prefixes (kilo, mega, giga...)
	std::string vector = "(";
	// we create the start bracket
	int exponent = 0;
	// and initialize the exponent of the value used later
	
	number x_output = Get_x();
	// since operations on the content of the Vector2 will need to change its
	// values, we need to copy to a temporary variable for the duration 
	if((x_output >= 1000.0000)||(x_output <= -1000.00000))
	{	// if the magnitude of the x value isnt within +/- 10^3,
		// we are going to scale it back until it is within those bounds
		
		// this is so that output displays printed to the game window can stay
		// a nice short, easy to read length instead of a long bloated mess that
		// jumps back & forth every time the order of magnitude changes
		while((x_output >= 1000.0000)||(x_output <= -1000.00000))
		{	// while we are outside of our target bounds, divide our magnitude 
			// by 10^3, and increase the exponent scale by 1 each time
			x_output /= 1000.00000;
			exponent++;
		}
	}
	
	if(exponent > 7)
	{	// as we will see in a minute, if we go past 10^7, I dont actually have
		// a SI prefix for that, although Im sure it exists. If that is the case
		// we scale the value up by 10^3 in magnitude again so that the display
		// remains accurate, but no longer is concise
		
		// this problem should be pretty rare though, as 10^7 is freaking Zetta,
		// ^ Famous last words lol
		while(exponent > 7)
		{	x_output *= 1000.00;
			exponent--;
			// odd that last call to -- was missing. What the hell was it doing
			// before?
			
			// mildly concerning to say the least 
		}
	}

	vector.append(Convert_to_string((float)x_output , 4));
	if(exponent != 0)
	{	// if the exponent wasnt zero, we need to add a SI prefix to the vector
		// so we sort through the possible options at every 3 orders of
		// magnitude, and apply the one that fits to the string
		switch(exponent)
		{	case 1:
			vector.append("k");	
			// kilo
			break;
			case 2:
			vector.append("M"); 	
			// Mega
			break;
			case 3:
			vector.append("G");	
			// Giga
			break;		
			case 4:
			vector.append("T");		
			// Tera	// (actual usefulness pretty much ends here)
			break;
			case 5:
			vector.append("P");	
			// Peta
			break;								
			case 6:
			vector.append("E");	
			// Exa
			break;
			case 7:
			vector.append("Z");		
			// Zetta
			break;						
		}
	}
	vector.append(unit);
	// we append the unit of the vector after the si prefix, ie 'm'
	vector.append(" , ");
	// and  we tack on the comma, since we have the y value to add as well
	exponent = 0;
	number y_output = Get_y();	
	// same as with the x value, cant mess with our internal x & y values, so
	// we make a copy to work with
	if((y_output >= 1000.0000)||(y_output <= -1000.00000))
	{	// if the magnitude of y isnt within the acceptable range, we scale it
		// back until it is
		while((y_output >= 1000.0000)||(y_output <= -1000.00000))
		{	y_output /= 1000.00000;
			exponent++;
		}
	}

	if(exponent > 7)
	{	// as we will see in a minute, if we go past 10^7, I dont actually have
		// a SI prefix for that, although Im sure it exists. If that is the case
		// we scale the value up by 10^3 in magnitude again so that the display
		// remains accurate, but no longer is concise
		
		// this problem should be pretty rare though, as 10^7 is freaking Zetta,
		// ^ Famous last words lol
		while(exponent > 7)
		{	y_output *= 1000.00;
			exponent--;
			// odd that last call to -- was missing. What the hell was it doing
			// before? That should have been an infinite loop!
			
			// mildly concerning to say the least 
		}
	}
	
	vector.append(Convert_to_string((float)y_output , 4));	
	if(exponent != 0)
	{	// if the exponent wasnt zero, we need to add a SI prefix before the
		// unit, so we sort through and tack an appropriate one on
		switch(exponent)
		{	case 1:
			vector.append("k");		
			// kilo
			break;
			case 2:
			vector.append("M"); 	
			// Mega
			break;
			case 3:
			vector.append("G");	
			// Giga
			break;		
			case 4:
			vector.append("T");		
			// Tera
			break;
			case 5:
			vector.append("P");	
			// Peta
			break;								
			case 6:
			vector.append("E");	
			// Exa		// (actual usefulness pretty much ends here)
			break;
			case 7:
			vector.append("Z");		
			// Zetta
			break;						
		}
	}
	
	
	vector.append(" , ");
	// and  we tack on the comma, since we have the z value to add as well
	exponent = 0;
	number z_output = Get_z();	
	// same as with the x value, cant mess with our internal x & y values, so
	// we make a copy to work with
	if((z_output >= 1000.0000)||(z_output <= -1000.00000))
	{	// if the magnitude of y isnt within the acceptable range, we scale it
		// back until it is
		while((z_output >= 1000.0000)||(z_output <= -1000.00000))
		{	z_output /= 1000.00000;
			exponent++;
		}
	}

	if(exponent > 7)
	{	// as we will see in a minute, if we go past 10^7, I dont actually have
		// a SI prefix for that, although Im sure it exists. If that is the case
		// we scale the value up by 10^3 in magnitude again so that the display
		// remains accurate, but no longer is concise
		
		// this problem should be pretty rare though, as 10^7 is freaking Zetta,
		// ^ Famous last words lol
		while(exponent > 7)
		{	z_output *= 1000.00;
			exponent--;
			// odd that last call to -- was missing. What the hell was it doing
			// before? That should have been an infinite loop!
			
			// mildly concerning to say the least 
		}
	}
	
	vector.append(Convert_to_string((float)z_output , 4));	
	if(exponent != 0)
	{	// if the exponent wasnt zero, we need to add a SI prefix before the
		// unit, so we sort through and tack an appropriate one on
		switch(exponent)
		{	case 1:
			vector.append("k");		
			// kilo
			break;
			case 2:
			vector.append("M"); 	
			// Mega
			break;
			case 3:
			vector.append("G");	
			// Giga
			break;		
			case 4:
			vector.append("T");		
			// Tera
			break;
			case 5:
			vector.append("P");	
			// Peta
			break;								
			case 6:
			vector.append("E");	
			// Exa		// (actual usefulness pretty much ends here)
			break;
			case 7:
			vector.append("Z");		
			// Zetta
			break;						
		}
	}
	vector.append(unit);	
	// we append the unit in question after the SI prefix
	vector.append(")");
	// add the close bracket in as well
	return vector;
	// and finally, we return the string that this function created
}	


number VectorVictor::Vector3::Get_vector_magnitude()
{	number output = this->Get_vector_magnitude_squared(); 
	// get the squared magnitude of the vector from the function
	output = sqrt(output);
	// and run an expensive call to sqrt() to finish applying pythagorean
	// theorem if we must have the true length of the vector
	return output;							
}

number VectorVictor::Vector3::Get_vector_magnitude_squared()
{	number output, output_x, output_y, output_z;
	output_x = (x*x);
	output_y = (y*y);
	output_z = (z*z);
	
	// define our variables just like before
	output = (output_x + output_y + output_z);
	// add them up, but simply return that result as is, since we dont need to
	// run that expensive call to sqrt() if we only want the vectors magnitude
	// *squared*
	return output;				
}


void VectorVictor::Vector3::Normalize()
{	if(this->Zero_vector() == true)
	{	// if we have the zero vector, obviously dont go dividing by zero
		// magnitude, just make the vector 0,0,0
		this->Set_values(0,0,0);
	}
	else
	{	number vector_magnitude = this->Get_vector_magnitude();
		// we find the current magnitude of the vector
		x /= vector_magnitude;
		y /= vector_magnitude;
		z /= vector_magnitude;
		// and divide by it to normalize the vector and give it a magnitude of 1
	}
}

VectorVictor::Vector3 VectorVictor::Vector3::Vector_normalized()
{	
	if(this->Zero_vector() == true)
	{	// if we have the zero vector, obviously dont go dividing by zero
		// magnitude, just return 0,0,0
		return Vector3(0,0,0);
	}
	// otherwise...
	number vector_magnitude = this->Get_vector_magnitude();
	// we find the current magnitude of the vector
	VectorVictor::Vector3 output(x, y, z);
	output.x /= vector_magnitude;
	output.y /= vector_magnitude;
	output.z /= vector_magnitude;
	// and divide by it to normalize the vector and give it a magnitude of 1
	return output;
}

bool VectorVictor::Vector3::Zero_vector()
{	if((x == 0)&&(y == 0)&&(z == 0))
	{	return true;
	}
	return false;
}

number VectorVictor::Vector3::Dot(VectorVictor::Vector3 &vector)
{	number output = ((x*vector.x)+(y*vector.y)+(z*vector.z));
	return output;
}

VectorVictor::Vector3 VectorVictor::Vector3::Cross(VectorVictor::Vector3 &vector)
{	Vector3 output(((y*vector.z)-(z*vector.y)),((z*vector.x)-(x*vector.z)),((x*vector.y)-(y*vector.x)));
	// construct a vector based on the definition of the cross product & return
	// it as the new vector representing the cross product of the two vectors
	return output;
}


// Standard Class Operators ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// important tools for a vector class, since they make objects of the type much
// more intuitive to work with

VectorVictor::Vector3  VectorVictor::Vector3::operator+ (VectorVictor::Vector3 pplus)
{	VectorVictor::Vector3 tplus(this->Get_x(), this->Get_y(), this->Get_z());
	tplus.x += pplus.x;
	tplus.y += pplus.y;
	tplus.z += pplus.z;	
	return (tplus);		
}

VectorVictor::Vector3  VectorVictor::Vector3::operator+= (VectorVictor::Vector3 pplus)
{	x += pplus.x;
	y += pplus.y;
	
	z += pplus.z;	
	return (*this);		
}

VectorVictor::Vector3  VectorVictor::Vector3::operator- (VectorVictor::Vector3 pminus)
{	VectorVictor::Vector3 tminus(this->Get_x(), this->Get_y(), this->Get_z());
	tminus.x -= pminus.x;
	tminus.y -= pminus.y;
	tminus.z -= pminus.z;	
	return (tminus);		
}

VectorVictor::Vector3  VectorVictor::Vector3::operator-= (VectorVictor::Vector3 pminus)
{	x -= pminus.x;
	y -= pminus.y;
	z -= pminus.z;	
	return (*this);		
}

VectorVictor::Vector3 VectorVictor::Vector3::operator= (const VectorVictor::Vector3 v)
{	x = v.x;
	y = v.y;
	z = v.z;
	return (*this);		
}

VectorVictor::Vector3 VectorVictor::Vector3::operator * (const number c)
{	
	x *= c;
	y *= c;
	z *= c;
	return (*this);
}

VectorVictor::Vector3 VectorVictor::Vector3::operator *= (const number c)
{	// multiply every element in the vector by some value c
	x *= c;
	y *= c;
	z *= c;
	return (*this);		
}



VectorVictor::Vector3 VectorVictor::Vector3::operator / (const number c)
{	// divide every element in the vector by some value c
	x /= c;
	y /= c;
	z /= c;
	return (*this);
}

VectorVictor::Vector3 VectorVictor::Vector3::operator /= (const number c)
{	// divide every element in the vector by some value c
	x /= c;
	y /= c;
	z /= c;
	return (*this);		
}

	// dangerous because c cannot be guaranteed to not be zero
	
	// but we are not going to worry about that here


bool VectorVictor::Vector3::operator != (const VectorVictor::Vector3 v)
{	// to check if the vectors are not equivalent, we specifically look at
	// each element in each vector to see if any are different. If both of x 
	// and y and z are equivalent, we return false to indicate that it was == 
	
	// specifically this function evaluates if the given functions are the
	// *exact same*	
	if(this->x != v.x)
	{	return true;
	}
	if(this->y != v.y)
	{	return true;
	}	
	if(this->z != v.z)
	{	return true;
	}	
	// if we get to the end of it and all of the elements were not != or ==
	// depending on your point of view, we return false
	return false;
}

bool VectorVictor::Vector3::operator == (const VectorVictor::Vector3 v)
{	// same idea as !=, now we just to check to see if each element in each
	// vector is the same as the one in the other
	if(this->x != v.x)
	{	return false;
	}
	if(this->y != v.y)
	{	return false;
	}	
	if(this->z != v.z)
	{	return false;
	}	
	// if we get to the end of it and all of the elements were not == or !=
	// depending on your point of view, we return false
	return true;
}

bool VectorVictor::Vector3::Is_nan()
{	if(this->x != this->x)
	{	return true;
		// if it isnt equivalent to itself its NAN, and shit is goin down
	}
	else
	{	if(this->y != this->y)
		{	return true;
		}
		else
		{	return false;
		}
	}
}


// Extended Vector Operators ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//void VectorVictor::Vector3::Rotate_vector(long double rotation)
//{	rotation = ((rotation/360)*2*Pi);	
	//// we convert our rotation from degrees to radians, since standard library
	//// math calls want radians to do their calculations			
	//long double new_x = ( (x*(cos(rotation)))+(y*(sin(rotation))) );	
	//// AHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	//// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	
	//// the variables are changing with respect to themselves!!!!
	//// AM WINNER PROGRAMMER, SUCH OF FULL oF WIN
	//y = ( (x*((-1)*sin(rotation)))+(y*(cos(rotation))) );
	//// multiply the vector by the 2d rotational matrix, rotating clockwise
	//// around the origin. 
	//x = new_x;
	//// [cos(theta)		sin(theta)]
	//// [-sin(theta		cos(theta)]
	
	//// important to note that this vector affects the contents of the vector
	//// that calls it. If you want to get the rotated vector without affecting
	//// its current orientation, you need to call the next method below  															 	
//}	
	
//VectorVictor::Vector2 VectorVictor::Vector2::Get_rotated_vector(long double rotation)
//{	VectorVictor::Vector2 V_rotated(0, 0);
	//// pointless to be explicit about it being 0,0
	//// this would work better with setting its value as the parents
	//// x and y here instead
	//rotation = ((rotation/360)*2*Pi);
	//// convert our rotation from degrees to radians				
	//V_rotated.x = ( (x*(cos(rotation)))+(y*(sin(rotation))) );	
	//V_rotated.y = ( (x*((-1)*sin(rotation)))+(y*(cos(rotation))) );
	//// multiply the vector by the 2d rotational matrix, rotating clockwise
	//// around the origin. 
	
	//// [cos(theta)		sin(theta)]
	//// [-sin(theta		cos(theta)]
	
	//return V_rotated;															 	
	//// and send the resulting VV2 vector on its way
//}	

// what to do with these meddling functions...

// Destructor //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

VectorVictor::Vector3::~Vector3()
{	// no memory allocations, so nothing much to do here

	// that is how we like it though :)
}


// Extended non-member Vector Operators ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



number VectorVictor::Get_dot_product(VectorVictor::Vector3 First_vector, VectorVictor::Vector3 Second_vector)
{	number output = First_vector.Dot(Second_vector);
	// just maintaining this function so it is still here if necessary
	return output;
}

number VectorVictor::Get_angle_between(VectorVictor::Vector3 First_vector, VectorVictor::Vector3 Second_vector)
{	// given that a dot b = ||a|| ||b|| cos(theta)
	// we look to solve for the angle between the two vectors
	number theta = acos((First_vector.Dot(Second_vector))/(First_vector.Get_vector_magnitude()*Second_vector.Get_vector_magnitude()));
	// finally we run a call to arccos, perhaps a wee bit expensive, but we
	// gotta execute instructions sometime
	return theta;
}

VectorVictor::Vector3 VectorVictor::Get_cross_product(VectorVictor::Vector3 First_vector, VectorVictor::Vector3 Second_vector)
{	VectorVictor::Vector3 output = First_vector.Cross(Second_vector);
	return output;
}	

number VectorVictor::Get_vector_separation(Vector3 First_vector, Vector3 Second_vector)
{	number separation = 0;
	if(First_vector == Second_vector)
	{	return separation;
	}
	VectorVictor::Vector3 offset = First_vector;
	offset -= Second_vector;
	separation = offset.Get_vector_magnitude();
	return separation;
}

long double Minimum(long double value1, long double value2)
{	if(value1 < value2)
	{	return value1;
	}
	else
	{	if(value1 == value2)
		{	return value1;
			// it dont matter
		}
		else
		{	return value2;
		}
	}
}

long double Maximum(long double value1, long double value2)
{	if(value1 > value2)
	{	return value1;
	}
	else
	{	if(value1 == value2)
		{	return value1;
			// it dont matter
		}
		else
		{	return value2;
		}
	}
}

bool In_range(long double boundary1, long double boundary2, long double target_value)
{	if((target_value >= Minimum(boundary1, boundary2))&&(target_value <= Maximum(boundary1, boundary2)))
	{	// if the value falls in the range we're good to go
		return true;
	}
	return false;
}

long double Absolute_value(long double value)
{	if(value < 0)
	{	value = -value;
	}
	return value;
}
