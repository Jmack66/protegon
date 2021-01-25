#pragma once

#include "HopperComponent.h"
struct StateVectorComponent {
	StateVectorComponent() = default;

	double k_gains[2][6] = { 0.0000, 0.0000 , 1.4142 ,  4.1900, 0.0000 , 0.0000,
						1.4142 ,  2.0355 , 0.0000,0.0000, 7.4330,1.2961 };
	//-0.0000 - 0.0000    1.4142    4.1900 - 0.0000 - 0.0000
		//1.4142    2.0355 - 0.0000    0.0000    7.4330    1.2961
	double sv[6][1] = { 0,0,0,0,0,0 };
	
	void Update(V2_double origin,RigidBody &rb,HopperComponent &hopper ) {
			
		//AHHHHHHHHHHHHHHHHH idk a better way to assing matrix values in the loop
		sv[0][0] = rb->position.x - origin.x;
		sv[1][0] = rb.body->velocity.x;
		sv[2][0] = rb.body->position.y - origin.y;
		sv[3][0] = rb.body->velocity.y;
		sv[4][0] = rb.body->orientation;
		sv[5][0] = hopper.theta_d;
		LOG(transform.position.x - transform.original_position.x);
	}
	V2_double ComputeControl(){
		int rowFirst = 2;
		int columnFirst = 6;
		int rowSecond = 6;
		int columnSecond = 1;
		int i, j, k;
		double mult[2][1] = { 0,0 };

		// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
		for (i = 0; i < rowFirst; ++i)
		{
			for (j = 0; j < columnSecond; ++j)
			{
				for (k = 0; k < columnFirst; ++k)
				{
					mult[i][j] += -1.0*k_gains[i][k] * sv[k][j];
				}
			}
		}
	
		return { mult[0][0],mult[1][0] };
	
	}

};