/* Changelog:
*/

// g++ -Wall mtrans.cpp main.cpp -lopengl32 -lglew32 -lglfw3dll
#include "mtrans.h"

int main()
{
	// Initialise GLFW
	if (glfwInit())
	{
		// Creating 600x600 window
		GLFWwindow* window = glfwCreateWindow(600, 600, "Tugas Besar Aljabar Geometri", NULL, NULL);
		glewExperimental = true;
		glewInit();
		glfwMakeContextCurrent(window);
		
		//Gambar warna background dan peta kartesian kosong
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
		drawCartesian();
		glfwSwapBuffers(window);
		glfwPollEvents();

		//Input titik-titik dari polygon
		vfloat gambarPolygon;
		vfloat kondisiAwal;
		glfwWaitEvents();
		gambarPolygon = getVertexByUser();
		kondisiAwal = gambarPolygon;

		//Mencari banyak vertex
		int banyakVertex = gambarPolygon.size()/4;
		
		//Gambar polygon
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		drawCartesian();
		drawPolygon(gambarPolygon);
		glfwSwapBuffers(window);
		glfwPollEvents();

		
		cout << endl;
		cout << "Daftar command yang tersedia:                						" << endl;
		cout << "                                             						" << endl;
		cout << "		translate <dx> <dy>                                  			" << endl;
		cout << "		dilate <k>                                       				" << endl;
		cout << "		rotate <degree> <x rotation pivot> <y rotation pivot>			" << endl;
		cout << "		reflect <param>                              					" << endl;
		cout << "		shear <param> <k>                                 		  		" << endl;
		cout << "		stretch <param> <k>                              	  			" << endl;
		cout << "		custom <a> <b> <c> <d>		                           	     " << endl;
		cout << "		multiple 	                              	        				" << endl;
		cout << "		reset                                                 			" << endl;
		cout << "		exit                                                 			" << endl;
		cout << "                                             						" << endl;
		cout << "Input command (tidak case sensitive): ";
		
		//Input command, jika "exit" langsung keluar
		string command;
		cin >> command;
		transform(command.begin(), command.end(), command.begin(), ::tolower);
		
		cout << endl;

		while (command != "exit"){
			if ( command == "translate" )
			{
				//Prosedur translate
				float dx,dy;

				//Input besar pergeseran x & y
				cin >> dx >> dy;

				float nilaiSignedDx = dx<0? -1 : 1;
				float nilaiSignedDy = dy<0? -1 : 1;

				//animasi Translate
				for (float i = 1.0; i <= nilaiSignedDx*dx; i = i+.1)
				{
					commandTranslate(&gambarPolygon, nilaiSignedDx*.1 , 0, banyakVertex);

					glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
					drawCartesian();
					drawPolygon(gambarPolygon);
					glfwSwapBuffers(window);
					glfwPollEvents();

					
				}

				//animasi Translate
				for (float i = 1.0; i <= nilaiSignedDy*dy; i = i + .1)
				{
					commandTranslate(&gambarPolygon, 0 , nilaiSignedDy*.1, banyakVertex);

					glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
					drawCartesian();
					drawPolygon(gambarPolygon);
					glfwSwapBuffers(window);
					glfwPollEvents();

				}
				
				glfwSwapBuffers(window);
				glfwPollEvents();

				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			}
			else if ( command == "dilate" )
			{
				// Procedure dilate

				commandDilate(&gambarPolygon, banyakVertex);

				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				drawCartesian();
				drawPolygon(gambarPolygon);
				glfwSwapBuffers(window);
				glfwPollEvents();

				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			}	
			else if ( command == "rotate" )
			{
				// Procedure rotate
				float angle_in_degrees,  a,  b;
				cin >> angle_in_degrees >> a >> b;
				commandRotate(&gambarPolygon, angle_in_degrees,   a,   b,   banyakVertex);

				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				drawCartesian();
				drawPolygon(gambarPolygon);
				glfwSwapBuffers(window);
				glfwPollEvents();

				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			}
			else if ( command == "reflect" )
			{
				// Input reflect
				string input;
				cin >> input;
				
				// Get new polygon
				gambarPolygon = commandReflect(gambarPolygon, input);
				
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				drawCartesian();
				drawPolygon(gambarPolygon);
				
				glfwSwapBuffers(window);
				glfwPollEvents();
	
				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			}
			else if ( command == "shear" )
			{
				// Procedure shear

				commandShear(&gambarPolygon, banyakVertex);

				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				drawCartesian();
				drawPolygon(gambarPolygon);
				glfwSwapBuffers(window);
				glfwPollEvents();

				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			}
			else if ( command == "stretch" )
			{
				// Procedure stretch

				commandStretch(&gambarPolygon,  banyakVertex);

				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				drawCartesian();
				drawPolygon(gambarPolygon);
				glfwSwapBuffers(window);
				glfwPollEvents();
				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);	
			} 
			else if (command == "custom")
			{
				//Procedure custom
				commandCustom(&gambarPolygon,  banyakVertex);

				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				drawCartesian();
				drawPolygon(gambarPolygon);
				glfwSwapBuffers(window);
				glfwPollEvents();
				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			} 
			else if (command == "multiple")
			{
				// Input banyak N
				int n;
				
				cin >> n;
				
				for(int i = 0; i < n; i++)
				{
					string input;
					
					cin >> input;

					if( input == "multiple" or input == "reset" or input == "exit" )
					{
						cout << "Input salah. Silahkan masukkan perintah lagi." << endl;
					}
					else
					{
						if ( input == "translate" )
						{
							//Prosedur translate
							float dx,dy;

							//Input besar pergeseran x & y
							cin >> dx >> dy;

							float nilaiSignedDx = dx<0? -1 : 1;
							float nilaiSignedDy = dy<0? -1 : 1;

							//animasi Translate
							for (float i = 1.0; i <= nilaiSignedDx*dx; i = i+.1)
							{
								commandTranslate(&gambarPolygon, nilaiSignedDx*.1 , 0, banyakVertex);

								glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
								drawCartesian();
								drawPolygon(gambarPolygon);
								glfwSwapBuffers(window);
								glfwPollEvents();

								
							}

							//animasi Translate
							for (float i = 1.0; i <= nilaiSignedDy*dy; i = i + .1)
							{
								commandTranslate(&gambarPolygon, 0 , nilaiSignedDy*.1, banyakVertex);

								glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
								drawCartesian();
								drawPolygon(gambarPolygon);
								glfwSwapBuffers(window);
								glfwPollEvents();

							}

							glfwSwapBuffers(window);
							glfwPollEvents();
						}
						else if ( input == "dilate" )
						{
							// Procedure dilate

							commandDilate(&gambarPolygon, banyakVertex);

							glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
							drawCartesian();
							drawPolygon(gambarPolygon);
							glfwSwapBuffers(window);
							glfwPollEvents();

						}	
						else if ( input == "rotate" )
						{
							// Procedure rotate
							float angle_in_degrees,  a,  b;
							cin >> angle_in_degrees >> a >> b;
							commandRotate(&gambarPolygon, angle_in_degrees,   a,   b,   banyakVertex);

							glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
							drawCartesian();
							drawPolygon(gambarPolygon);
							glfwSwapBuffers(window);
							glfwPollEvents();
						}
						else if ( input == "reflect" )
						{	
							// Input reflect
							string input;
							cin >> input;
							
							// Get new polygon
							gambarPolygon = commandReflect(gambarPolygon, input);
							
							glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
							drawCartesian();
							drawPolygon(gambarPolygon);
							
							glfwSwapBuffers(window);
							glfwPollEvents();
						}
						else if ( input == "shear" )
						{
							// Procedure shear

							commandShear(&gambarPolygon, banyakVertex);

							glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
							drawCartesian();
							drawPolygon(gambarPolygon);
							glfwSwapBuffers(window);
							glfwPollEvents();

						}
						else if ( input == "stretch" )
						{
							// Procedure stretch

							commandStretch(&gambarPolygon,  banyakVertex);

							glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
							drawCartesian();
							drawPolygon(gambarPolygon);
							glfwSwapBuffers(window);
							glfwPollEvents();
						} 
						else if (input == "custom")
						{
							//Procedure custom
							commandCustom(&gambarPolygon,  banyakVertex);

							glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
							drawCartesian();
							drawPolygon(gambarPolygon);
							glfwSwapBuffers(window);
							glfwPollEvents();
						}
						else 
						{
							cout << "Input salah. Silahkan masukkan perintah lagi." << endl;
						}
					}
				}
				
				cout << endl;
				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);
			}	
			else if (command == "reset")
			{
				gambarPolygon = kondisiAwal;
				commandReset(gambarPolygon);
				glfwSwapBuffers(window);
				glfwPollEvents();
				cout << "Masukkan perintah selanjutnya." << endl;
				cin >> command;
				transform(command.begin(), command.end(), command.begin(), ::tolower);

			} else {
				cout << "Input salah, silahkan masukkan kembali perintah." << endl;
				cin >> command;
			}
			
			cout << endl;
		}

		glfwTerminate();
	}
	return 0;
}
