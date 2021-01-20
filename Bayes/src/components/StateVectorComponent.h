#pragma once

struct StateVectorComponent {
	StateVectorComponent() = default;
	double x = 0.0;
	double x_dot = 0.0;
	double z = 0.0;
	double z_dot = 0.0;
	double theta = 0.0;
	double theta_dot = 0.0;
	double k_gains[2][6] = { 0.0000, 0.0000 , 3.4157, 6.5247, 0.0000 , 0.0000,
						1.2910 ,  2.2258 , 0.0000,0.0000,13.7573,0.4557 };
	//-0.0000 - 0.0000    3.4157    6.5247 - 0.0000 - 0.0000
	//	1.2910    2.2258    0.0000    0.0000   13.7573    0.4557
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
					//LOG(mult[i][j]);
				}
			}
		}
		
		V.x = mult[0][0];
		V.y = mult[1][0];
		return V;
	
	}

};