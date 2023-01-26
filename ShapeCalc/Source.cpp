#include <iostream>
#include <string>
# define M_PI           3.14159265358979323846  /* pi */
using namespace std;

//create an enum with our shape types
enum Shapes {
	circle, square, triangle, rect
	
};

bool circleTest(double x, double y, double radius) {
	//This will return true if our point at x,y is within the circle of radius = radius
	if (((x * x) + (y * y)) <= radius) {
		return true;
	}
	else {
		return false;
	}
}
bool squareTest(double x, double y, double radius) {
	//This will return true if our point at x,y is within the square with radius = radius
	if (abs(x + y) + abs(x - y) <= radius) {
		return true;
	}
	else {
		return false;
	}
}

bool triangleTest(double x, double y, double radius) {
	//Triangles are trickier so for this we have to check three lines to see if we are inside the triangle.
	bool l1 = y>= 0; //this is the first line, the one that is perfectly flat
	double a = ((radius * sqrt(3)) / 2); // this is a constant used in the next two equations
	bool l2 = y <= ((x * sqrt(3)) + a); // the next two equations are reflections of each other
	bool l3 = y <= ((-x * sqrt(3)) + a);
	if (l1 && l2 && l3) {
		//if we are on the correct side of each line then we return true
		return true;
	}
	else {
		return false;
	}
	
}

bool rectTest(double x, double y, double base, double height) {
	bool l1 = y <= (height / 2);
	bool l2 = y >= (-height / 2);
	bool l3 = x >= (-base / 2);
	bool l4 = x <= (base / 2);
	if (l1 && l2 && l3 && l4) {
		return true;
	}
	else {
		return false;
	}
}

string generateText(Shapes shape, double radius, double base, double height) {
	//This function returns a string out that contains the data for the shape
	double resolution = .1;//here we divide the shape into more characters so we can actually see it
	string out = "";
	//these nested for loops go character by character so we have an x,y coordinate at each character to test in our functions
	for (double y = -radius;  y <= radius;  y+= resolution*2)
	{
		//because the charcters aren't the same aspect ratio the y coords are half as many as the x
		for (double x = -radius; x <= radius; x += resolution)
		{
			//cout << "(" << x << ", " << y << ")" << endl;
			bool test = false;
			//here we switch based on our shape enum and test our current coords with the radius and set our bool
			switch (shape) {
			case circle:
				test = circleTest(x, y, radius);
				break;
			case square:
				test = squareTest(x, y, radius);
				break;
			case triangle:
				test = triangleTest(x, y, radius);
				break;
			case rect:
				test = rectTest(x, y, base, height);
				break;
			}
			//if our point is in the shape add a pound symbol otherwise add a space to our string
			if (test) {
				out.append("#");
			}
			else {
				out.append(" ");
			}
			

		}
		//at the end of each y line we add a return line so the shape draws correctly
		out.append("\n");
	}
	
	return out;
}

void main() {
	/*TODO
	* create menu of 5 shapes
	* have user input needed dimensions for area
	* display shape using console ASCII text art? (look into generating this for myself)
	* calculate area and display
	*/

	//Menu
	int choice = -1;
	while (choice != 0) {
		//creating the menu options
		cout << "Please choose a shape by entering a number or enter 0 to close: " << endl;
		cout << "Square: 1\nCircle: 2\n Equilateral Triangle: 3\nRectangle: 4" << endl;
		cout << "Input: ";
		cin >> choice;
		double radius;
		double area;
		double base;
		double height;
		switch (choice) {
		case 1:
			cout << "Choose the side length of the square: ";
			cin >> radius;
			area = radius * radius;
			cout << generateText(square, radius / 2, 0,0) << endl;
			cout << "The area of the square is " << area << " units squared." << endl;
			break;
		case 2:
			cout << "Choose the radius of the circle: ";
			cin >> radius;
			area = M_PI * (radius * radius);
			cout << generateText(circle, radius, 0,0) << endl;
			cout << "The area of the circle is " << area << " units squared." << endl;
			break;
		case 3:
			cout << "Choose the side length of the triangle: ";
			cin >> radius;
			area = ((radius * radius) * sqrt(3)) / 4;
			cout << generateText(triangle, radius, 0,0) << endl;
			cout << "The area of the triangle is " << area << " units squared." << endl;
			break;
		case 4:
			cout << "Choose the length of the base of the rectangle: ";
			cin >> base;
			cout << "Choose the length of the height of the rectangle: ";
			cin >> height;
			area = base * height;
			if (base >= height) {
				cout << generateText(rect, base, base, height) << endl;
			}
			else {
				cout << generateText(rect, height, base, height) << endl;
			}

			
			cout << "The area of the rectangle is " << area << " units squared." << endl;
			break;
		}
		
	}
	
	

}