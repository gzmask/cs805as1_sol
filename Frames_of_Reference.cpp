
// Billy Hamilton, student id 200288539
// Thursday, September 27th, 2012.
// CS405/805, Dr. XD Yang
// Assignment 1, question 3

// Frames_of_Reference.cpp -- Contains functions to find the transformation
//  matrices needed to convert points between world, camera, and light
//  coordinates.
// Also contains a main program to test these functions with the provided
//  testing data.
// This program writes its output to "test_out.txt".

#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Calc_uvn.h"

#include <iostream>
#include <fstream>

using namespace std;

ofstream fout; // a global file out stream for testing

void calculate_world_camera_matrices (
	Vector3D   vrp,   // In -- View reference point in world co-ords
	Vector3D   vpn,   // In -- View plane normal in world co-ords
	Vector3D   vup,   // In -- View up direction in world co-ords
	Matrix4x4& m_wc,  // Out -- Matrix to go from world to camera
	Matrix4x4& m_cw,  // Out -- Matrix to go from camera to world
	bool	   output // Whether to print the matrices found to fout
	)
{
	// First find u, v, and n (the basis of the camera co-ordinate system)
	//  using the function developed earlier.
	Vector3D u, v, n;
	calculate_uvn (vpn, vup, u, v, n);

	// If output is enabled, output u, v, and n.
	fout << "u: " << u << endl;
	fout << "v: " << v << endl;
	fout << "n: " << n << endl << endl;

	// The translation matrix required to go from world to camera is
	//  simply the difference between the world origin and the vrp.
	//  Thus x, y, and z to translate by are -1 * the coordinates of
	//  the camera.
	Matrix4x4 t_wc = Matrix4x4::translation( -vrp.x, -vrp.y, -vrp.z );

	// Print out translation matrix if output enabled
	if (output)
	{
		fout << "Translation from World to Camera:" << endl
			 << t_wc << endl;
	}

	// The rotation matrix required to go from world to camera is found
	//  using u, v, n.  (This is based on the fact that dot products can
	//  be used to project a vector onto another vector.)
	Matrix4x4 r_wc ( u.x, u.y, u.z, 0.0,
					 v.x, v.y, v.z, 0.0,
					 n.x, n.y, n.z, 0.0,
					 0.0, 0.0, 0.0, 1.0 );

	// Print out rotation matrix if output enabled
	if (output)
	{
		fout << "Rotation from World to Camera:" << endl
			 << r_wc << endl;
	}

	// Concatenate those two to give us the overall m_wc
	m_wc = r_wc * t_wc;

	// Print out combined matrix if output enabled
	if (output)
	{
		fout << "Combined transformation from World to Camera:" << endl
			 << m_wc << endl;
	}

	// To figure out m_cw, we use the inverse of m_wc.
	// The inverse of a product of matrices is given by the
	//  product of the inverses but in the opposite order.

	// For the inverse of t_wc, we reverse the signs on the
	//  three translation components.  Thus they are now positive.
	Matrix4x4 t_cw = Matrix4x4::translation ( vrp.x, vrp.y, vrp.z );

	// Print out inverted translation matrix if output enabled
	if (output)
	{
		fout << "Translation from Camera to World:" << endl
			 << t_cw << endl;
	}

	// For the inverse of r_wc, we take the transverse.
	//  (Because the matrix is orthogonal.)
	Matrix4x4 r_cw = r_wc.transpose();

	// Print out inverted rotation matrix if output enabled
	if (output)
	{
		fout << "Rotation from Camera to World:" << endl
			 << r_cw << endl;
	}

	// Now we concatenate the two inverses in reversed order
	//  to find the inverse.
	m_cw = t_cw * r_cw;

	// Print out combined inverse matrix if output enabled
	if (output)
	{
		fout << "Combined transformation from Camera to World:" << endl
			 << m_cw << endl;
	}
}

void calculate_world_light_matrices (
	Vector3D   lrp,   // In -- Light's position in world co-ords
	Vector3D   lpn,   // In -- Light plane normal in world co-ords
	Vector3D   lup,   // In -- Light's up direction in world co-ords (???)
	Matrix4x4& m_wl,  // Out -- Matrix to go from world to light
	Matrix4x4& m_lw,  // Out -- Matrix to go from light to world
	bool	   output // Whether to print the final matrices to fout
	)
{
	// The process is exactly analogous to the process used to find the
	//  matrices for converting between camera and world co-ords.
	//  Refer to the comments on that section for details.

	// 1 - Find the matrix for world to light

	Vector3D u, v, n;
	calculate_uvn (lpn, lup, u, v, n);

	Matrix4x4 t_wl = Matrix4x4::translation( -lrp.x, -lrp.y, -lrp.z );
	Matrix4x4 r_wl ( u.x, u.y, u.z, 0.0,
					 v.x, v.y, v.z, 0.0,
					 n.x, n.y, n.z, 0.0,
					 0.0, 0.0, 0.0, 1.0 );

	m_wl = r_wl * t_wl;

	// Print out combined matrix if output enabled
	if (output)
	{
		fout << "Combined transformation from World to Light:" << endl
			 << m_wl << endl;
	}

	// 2 - Find the matrix for going from Light to World

	Matrix4x4 t_lw = Matrix4x4::translation ( lrp.x, lrp.y, lrp.z );
	Matrix4x4 r_lw = r_wl.transpose();
	
	m_lw = t_lw * r_lw;

	// Print out combined inverse matrix if output enabled
	if (output)
	{
		fout << "Combined transformation from Light to World:" << endl
			 << m_lw << endl;
	}
}

// Main testing function using the provided testing data.
int main()
{
	// Open the file stream for output.
	fout.open("test_out.txt");

	// Define the position of the camera in world co-ordinates
	Vector3D vrp (  6.0,  10.0, -5.0 );
	Vector3D vpn ( -6.0,  -9.0,  5.0 );
	Vector3D vup (  0.0,   1.0,  0.0 );

	// Define the position of the light source in world co-ords.
	Vector3D lrp ( -10.0, 10.0,  0.0 );
	Vector3D lpn (  10.0,  9.0,  0.0 );
	Vector3D lup (   0.0,  1.0,  0.0 );

	// Define matrices for all the different transformations
	//  we wish to perform.
	Matrix4x4 world_to_camera,
			  camera_to_world,
			  world_to_light,
			  light_to_world,
			  camera_to_light,
			  light_to_camera;

	// Calculate the first two matrices (between camera and world)
	calculate_world_camera_matrices( vrp, vpn, vup,
									 world_to_camera,
									 camera_to_world,
									 true );	// provide output to fout


	// Calculate the second two matrices (between light and world)
	calculate_world_light_matrices( lrp, lpn, lup,
									world_to_light,
									light_to_world,
									true );	// provide output to fout

	// Find the last two matrices by concatenating those we have already found.
	camera_to_light = world_to_light * camera_to_world;
	light_to_camera = world_to_camera * light_to_world;

	// Print those last two matrices.
	fout << "Combined transformation from Camera to Light:" << endl
		 << camera_to_light << endl;
	fout << "Combined transformation from Light to Camera:" << endl
		 << light_to_camera << endl;

	// Test the transformations on a set of provided points.
	const Vector3D POINT[4] = {  Vector3D( 0.0, 0.0, 0.0 ),
								 Vector3D( 0.0, 1.0, 0.0 ),
								 Vector3D( 1.0, 1.0, 1.0 ),
								 Vector3D( 1.0, 1.0, 0.0 )
							  };

	// Transform each point into camera coordinates
	fout << "Points transformed into camera coordinates:" << endl;
	for (unsigned int i = 0; i < 4; i++)
	{
		Vector3D temp = world_to_camera * POINT[i];
		fout << temp << endl;
	}

	// Transform each point into light coordinates
	fout << endl << "Points transformed into light coordinates:" << endl;
	for (unsigned int i = 0; i < 4; i++)
	{
		Vector3D temp = world_to_light * POINT[i];
		fout << temp << endl;
	}

	fout.close();

	return 0;
}

