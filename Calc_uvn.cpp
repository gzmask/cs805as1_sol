
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 2

// Calc_uvn.cpp -- contains the implementation of the calc_uvn function.

#include "Vector3D.h"
#include <cmath>

using namespace std;

// Calculate the three vectors that look like this.
//                v
//                |
//                |____u
//               /
//              /
//             n
// This is useful for doing a viewing transform; n is the direction
// the camera is facing, v is the up direction, and u sticks out the
// left hand side of the view.
void calculate_uvn ( Vector3D  V1,	// in
					 Vector3D  V2,	// in
					 Vector3D& u,	// out
					 Vector3D& v,	// out
					 Vector3D& n  )// out
{
	// n is found by normallizing V1
	n = V1.normalize();

	// u is a unit vector perpendicular to both V1 and V2.
	// Therefore u can be found by normallizing the cross-product
	//  of V1 and V2.  (The cross product must be V2 X V1 so that
	//  the vector will go the right way as shown in the picture.)
	u = Vector3D::cross_product( V2, V1 );
	u = u.normalize();

	// v is a unit vector perpendicular to both n and u.
	// Therefore u can be found by normallizing the cross-product
	//  of n and u.
	v = Vector3D::cross_product( n, u );
	v = v.normalize();
}

