// Linker
// g++ -Wall mtrans.cpp main.cpp -lopengl32 -lglew32 -lglfw3dll

#include "mtrans.h"

using namespace std;
using namespace glm;

// Comparation function to sort vertex counter-clockwise using Barycenter
bool cmpBarycenter( tuple<points, points> a, tuple<points, points> b )
{
	// Declare point Barycenter, point A, and point B
	points bar = get<1>(a);
	points pa = get<0>(a);
	points pb = get<0>(b);
	
	// Compute angle of point A
	// Computation:
		// > Find angle of the vertex from some point in the polygon (Barycenter) using atan
	double aa = atan( ((get<1>(pa)-get<1>(bar))/(get<0>(pa)-get<0>(bar))) ) * 180 / 3.14;
	
	// Another manipulation for angle > 90
	if ( ((get<0>(pa)-get<0>(bar))<0) )
	{
		// If it is located in the 2nd OR 3rd quadrant
		aa += 180;
	}
	else
	{
		// If it is located in 4th quadrant
		if ( aa < 0 )
		{
			aa += 360;
		}
	}
	
	// Compute angle of point B
	double ab = atan( ((get<1>(pb)-get<1>(bar))/(get<0>(pb)-get<0>(bar))) ) * 180 / 3.14;
	
	// Another manipulation for angle > 90
	if ( ((get<0>(pb)-get<0>(bar))<0) )
	{
		ab += 180;
	}
	else
	{
		if ( ab < 0 )
		{
			ab += 360;
		}
	}

	// Sorted in non-decreasing order
	return (aa < ab);
}

// Function that returns sorted vertex counter-clockwise
vfloat sortBarycenter( polygon x )
{
	// Declare variable to hold coordinate of Barycenter
	points Barycenter;
	
	// Compute Barycenter
	double tx = 0, ty = 0, tz = 0, tw = 1;
	for( unsigned int i = 0; i < x.size(); i++)
	{
		tx += get<0>(x[i]);
		ty += get<1>(x[i]);
		tz += get<2>(x[i]);
	}
	
	// Got the coordinate
	Barycenter = make_tuple( tx/x.size(), ty/x.size(), tz/x.size(), tw );
	
	// Temporary vector that holds every vertex and Barycenter
	vector<tuple<points, points>> temp;
	
	// Insert vertex and Barycenter
	for( unsigned int i = 0; i < x.size(); i++)
	{
		temp.push_back(make_tuple(x[i], Barycenter));
	}
	
	// Sort using custom comparation function
	sort(temp.begin(), temp.end(), cmpBarycenter);
	
	// Variable that extracts sorted vertex (eliminating the Barycenter point)
 	vfloat retpol;
	
	// Extracting
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		double x = get<0>(get<0>(temp[i]));
		double y = get<1>(get<0>(temp[i]));
		double z = get<2>(get<0>(temp[i]));
		double w = 1;
		
		retpol.push_back(x);
		retpol.push_back(y);
		retpol.push_back(z);
		retpol.push_back(w);
	}
	
	// Return the sorted vertex
	return retpol;
}

// Draw Cartesian in the window
void drawCartesian()
{
	// White color
	glColor3f(1.0, 1.0, 1.0);
	
	// Specifying width of line
	glLineWidth(3.0);
	
	// Drawing line
	glBegin(GL_LINES);
		glVertex2f (-1.0, 0.0);
		glVertex2f (1.0, 0.0);
	glEnd();
	glFlush();  
	
	glBegin(GL_LINES);
		glVertex2f (0.0, -1.0);
		glVertex2f (0.0, 1.0);
	glEnd();
	glFlush();  
}

// Return vector of vertex made by user
vfloat getVertexByUser()
{
	// Variable to hold the vertex coordinate
	vfloat temp;
	
	cout << "Jumlah titik: ";
	int n;
	cin >> n;
	
	cout << "Jumlah titik yang dimasukkan: " << n << endl;
	cout << "Koordinat titik dimasukkan dengan asumsi titik pertama adalah x dan titik kedua adalah y" << endl;
	cout << "Masukkan koordinat titik: " << endl;

	polygon poltemp;
	for(int i = 0; i < n; i++)
	{
		int x, y, z = 0, w = 1;
		cin >> x;
		cin >> y;
		
		poltemp.push_back( make_tuple(x/PIXEL, y/PIXEL, z/PIXEL, w) );
	}

	temp = sortBarycenter(poltemp);
	
	return temp;
}

// Draw the polygon
void drawPolygon(vfloat v)
{
	
	glColor3f(0.6, 1.0, 0.6);

	glBegin(GL_POLYGON);
		for(unsigned int i = 0; i < v.size(); i += 4)
		{
			glVertex4fv( &v[i] );
		}
	glEnd();
	glFlush();

	// glfwPollEvents();
}



//Prosedur translate
void commandTranslate(vector<float> *gambarPolygonAwal, float dx, float dy,  int banyakVertex){
	
	vector<float> gambarPolygonBaru;
	glm::mat4 myMatrix( 1.0f );

	myMatrix[3].x = dx/PIXEL;
	myMatrix[3].y = dy/PIXEL;
	for (int i = 0; i < banyakVertex; ++i)
	{
		int hitung = i*4;
		glm::vec4 myVector;
		myVector.x = *(gambarPolygonAwal->begin()+hitung);
		myVector.y = *(gambarPolygonAwal->begin()+hitung+1);
		myVector.z = 0;
		myVector.w = 1;

		glm::vec4 transformedVector = myMatrix * myVector; // guess the result
		gambarPolygonBaru.push_back(transformedVector.x);
		gambarPolygonBaru.push_back(transformedVector.y);
		gambarPolygonBaru.push_back(transformedVector.z);
		gambarPolygonBaru.push_back(transformedVector.w);
	}

	*gambarPolygonAwal = gambarPolygonBaru;

}

//Prosedur dilate
void commandDilate(vector<float> *gambarPolygonAwal, int banyakVertex){
	vector<float> gambarPolygonBaru;
	glm::mat4 myMatrix( 1.0f );

	float k;
	//Input skala
	cin >> k;
	myMatrix[0].x = k;
	myMatrix[1].y = k;
	myMatrix[2].z = k;
	myMatrix[3].w = 1;

	for (int i = 0; i < banyakVertex; ++i)
	{
		int hitung = i*4;
		glm::vec4 myVector;
		myVector.x = *(gambarPolygonAwal->begin()+hitung);
		myVector.y = *(gambarPolygonAwal->begin()+hitung+1);
		myVector.z = 0;
		myVector.w = 1;

		glm::vec4 transformedVector = myMatrix * myVector; 
		gambarPolygonBaru.push_back(transformedVector.x);
		gambarPolygonBaru.push_back(transformedVector.y);
		gambarPolygonBaru.push_back(transformedVector.z);
		gambarPolygonBaru.push_back(transformedVector.w);
	}

	*gambarPolygonAwal = gambarPolygonBaru;

}

//Prosedur reset
void commandReset(vector<float> kondisiAwal){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	drawCartesian();
	drawPolygon(kondisiAwal);
}

//Prosedur rotate
void commandRotate(vector<float> *gambarPolygonAwal, float angle_in_degrees,  float a,  float b,  int banyakVertex){
	vector<float> gambarPolygonBaru;

	commandTranslate(gambarPolygonAwal, (-a), (-b), banyakVertex);

	for (int i = 0; i < banyakVertex; ++i)
	{
		int hitung = i*4;
		float x = *(gambarPolygonAwal->begin()+hitung);
		float y = *(gambarPolygonAwal->begin()+hitung+1);

		float xHasil, yHasil;
		xHasil = ((x*(cos ( angle_in_degrees * PI / 180.0 ))) - (y*(sin (angle_in_degrees*PI/180))) );
		yHasil = ((x*(sin (angle_in_degrees*PI/180))) + (y*(cos ( angle_in_degrees * PI / 180.0 ))) );
		gambarPolygonBaru.push_back(xHasil);
		gambarPolygonBaru.push_back(yHasil);
		gambarPolygonBaru.push_back(0);
		gambarPolygonBaru.push_back(1);
	}

	commandTranslate(&gambarPolygonBaru, (a), (b), banyakVertex);

	*gambarPolygonAwal = gambarPolygonBaru;

}

//Prosedur shear
void commandShear(vector<float> *gambarPolygonAwal,  int banyakVertex){
	vector<float> gambarPolygonBaru;
	char param;
	float k;
	//Input nilai
	cin >> param >> k;
	
	if (param == 'x' || param == 'X'){
		for (int i = 0; i < banyakVertex; ++i)
		{
			int hitung = i*4;
			float x = *(gambarPolygonAwal->begin()+hitung);
			float y = *(gambarPolygonAwal->begin()+hitung+1);

			float xHasil, yHasil;
			xHasil = x + (k*y);
			yHasil = y;
			gambarPolygonBaru.push_back(xHasil);
			gambarPolygonBaru.push_back(yHasil);
			gambarPolygonBaru.push_back(0);
			gambarPolygonBaru.push_back(1);
		}

	} else if (param == 'y' || param == 'Y') {
		for (int i = 0; i < banyakVertex; ++i)
		{
			int hitung = i*4;
			float x = *(gambarPolygonAwal->begin()+hitung);
			float y = *(gambarPolygonAwal->begin()+hitung+1);

			float xHasil, yHasil;
			xHasil = x;
			yHasil = y + (k*x);
			gambarPolygonBaru.push_back(xHasil);
			gambarPolygonBaru.push_back(yHasil);
			gambarPolygonBaru.push_back(0);
			gambarPolygonBaru.push_back(1);
		}

	} else {
		cout << "Parameter salah. Silahkan masukan kembali perintah." << endl;
	}
	

	*gambarPolygonAwal = gambarPolygonBaru;

}

void commandStretch(vector<float> *gambarPolygonAwal,  int banyakVertex){
	vector<float> gambarPolygonBaru;
	char param;
	float k;
	//Input nilai
	cin >> param >> k;
	
	if (param == 'x' || param == 'X'){
		for (int i = 0; i < banyakVertex; ++i)
		{
			int hitung = i*4;
			float x = *(gambarPolygonAwal->begin()+hitung);
			float y = *(gambarPolygonAwal->begin()+hitung+1);

			float xHasil, yHasil;
			xHasil = (k*x);
			yHasil = y;
			gambarPolygonBaru.push_back(xHasil);
			gambarPolygonBaru.push_back(yHasil);
			gambarPolygonBaru.push_back(0);
			gambarPolygonBaru.push_back(1);
		}

	} else if (param == 'y' || param == 'Y') {
		for (int i = 0; i < banyakVertex; ++i)
		{
			int hitung = i*4;
			float x = *(gambarPolygonAwal->begin()+hitung);
			float y = *(gambarPolygonAwal->begin()+hitung+1);

			float xHasil, yHasil;
			xHasil = x;
			yHasil =(k*y);
			gambarPolygonBaru.push_back(xHasil);
			gambarPolygonBaru.push_back(yHasil);
			gambarPolygonBaru.push_back(0);
			gambarPolygonBaru.push_back(1);
		}

	} else {
		cout << "Parameter salah. Silahkan masukan kembali perintah." << endl;
	}
	

	*gambarPolygonAwal = gambarPolygonBaru;

}

void commandCustom(vector<float> *gambarPolygonAwal,  int banyakVertex){
	vector<float> gambarPolygonBaru;
	float a,b,c,d;
	cin >> a >> b >> c >>d;
	
	for (int i = 0; i < banyakVertex; ++i)
	{
		int hitung = i*4;
		float x = *(gambarPolygonAwal->begin()+hitung);
		float y = *(gambarPolygonAwal->begin()+hitung+1);

		float xHasil, yHasil;
		xHasil = a*x + b*y;
		yHasil = c*x + d*y;
		gambarPolygonBaru.push_back(xHasil);
		gambarPolygonBaru.push_back(yHasil);
		gambarPolygonBaru.push_back(0);
		gambarPolygonBaru.push_back(1);
	
	}
		
	*gambarPolygonAwal = gambarPolygonBaru;

}


vfloat commandReflect(vfloat polygonBeforeTrans, string input)
{
	// Jenis input:
		// 1. x
		// 2. y
		// 3. y = x
		// 4. y = -x
		// 5. (a,b)
	
	int polsize = polygonBeforeTrans.size();
	
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	vfloat temp = polygonBeforeTrans;
		
	if (input == "x")
	{
		// Reflect across x-axis
		// Cuma mengubah y jadi -y
		
		for(auto i = 1; i < polsize; i+=4)
		{
			temp[i] *= -1;
		}
		
	}	
	else if (input == "y")
	{
		// Reflect across y-axis
		// Cuma mengubah x jadi -x
		
		for(auto i = 0; i < polsize; i+=4)
		{
			temp[i] *= -1;
		}
	}
	else if (input == "y=x")
	{
		// Reflect over the line y = x
			// Swap y dan x
			
		for(auto i = 0; i < polsize; i+=4)
		{
			float tx = temp[i];
			float ty = temp[i+1];
			float t;
			
			// Swap
			t = tx;
			tx = ty;
			ty = t;
			
			// Masukin lagi hasil transformasi
			temp[i] = tx;
			temp[i+1] = ty;
		}	
	}
	else if (input == "y=-x")
	{
		// Reflect over the line y = -x
			// Swap x-y
			// Swap sign

		
		for(auto i = 0; i < polsize; i+=4)
		{
			float tx = temp[i];
			float ty = temp[i+1];
			float t;
			
			// Swap x-y 
			// Dont forget the sign
			t = tx;
			tx = -ty;
			ty = -t;
			
			// Masukin lagi hasil transformasi
			temp[i] = tx;
			temp[i+1] = ty;
		}	
	}	
	else
	{
		// Reflect over the point (a,b)
		// Rotate 180 with (a,b) as pivot
		
		
		// Parsing "(a,b)" to extract the pivot
		string ta = "";
		string tb = "";
		bool comma = false;
		
		for(int i = 0; i < (int) input.length(); i++)
		{
			char x = input[i];
			
			if ( x != '(' and x != ')' )
			{
				if ( x == ',' )
				{
					comma = true;
				}
				else if ( not(comma) )
				{
					ta += x;
				}
				else if ( comma )
				{
					tb += x;
				}
			}
		}
		
		// Converting string to float
		float a = stof(ta, 0);
		float b = stof(tb, 0);

		commandRotate(&temp, -180, a, b, polsize/4);
	}
	
	return temp;

}
