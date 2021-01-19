#pragma once

struct StateVectorComponent {
	StateVectorComponent() = default;
	double x = 0.0;
	double x_dot = 0.0;
	double z = 0.0;
	double z_dot = 0.0;
	double theta = 0.0;
	double theta_dot = 0.0;
	double k_gains[2][6] = { 1.0000, 1.0000 , -3.1623, -5.9064, -1.0, -1.0,
						-3.1623 , -1.7612, -1.0,-1.0,-4.6563,-0.2833 };
	//    0.0000    0.0000    3.1623    5.9064    0.0000    0.0000
	//3.1623    1.7612 - 0.0000    0.0000    4.6563    0.2833
	double sv[6][1] = { x,x_dot,z,z_dot,theta,theta_dot };
	Vector2<double> V;
	void Update(double x, double x_dot, double z, double z_dot, double theta, double theta_dot) {
		this->x = x;
		this->x_dot = x_dot;
		this->z = z;
		this->z_dot = z_dot;
		this->theta = theta;
		this->theta_dot = theta_dot;
		//AHHHHHHHHHHHHHHHHH idk a better way to assing matrix values in the loop
		sv[0][0] = x;
		sv[1][0] = x_dot;
		sv[2][0] = z;
		sv[3][0] = z_dot;
		sv[4][0] = theta;
		sv[5][0] = theta_dot;
	}
	Vector2<double> ComputeControl(){
		int rowFirst = 6;
		int columnFirst = 1;
		int rowSecond = 2;
		int columnSecond = 6;
		int i, j, k;
		double mult[2][1] = { 0,0 };

		// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
		for (i = 0; i < rowFirst; ++i)
		{
			for (j = 0; j < columnSecond; ++j)
			{
				for (k = 0; k < columnFirst; ++k)
				{
					mult[i][j] += k_gains[i][k] * sv[k][j];
				}
			}
		}
		
		V.x = mult[0][0];
		V.y = mult[1][0];
		return V;
	
	}

};