#include "SDL_Wrapper.h"
#include "Image_Processing.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int mainMenu(SDL_Surface* ImageSurface);
int imgMenu();
int colourMenu();
int transformMenu();
int filterMenu();
void selectDisplay(SDL_Surface* ImageSurface, string Location);
void selectRGB(SDL_Surface* ImageSurface, string Location);
void selectContrast(SDL_Surface* ImageSurface);
void selectBrightness(SDL_Surface* ImageSurface);
void selectInvert(SDL_Surface* ImageSurface);
void selectBlur(SDL_Surface* ImageSurface);
void selectMotionBlur(SDL_Surface* ImageSurface);
void selectEmboss(SDL_Surface* ImageSurface);
void selectEdgeDetection(SDL_Surface* ImageSurface);
void selectRotate(SDL_Surface* ImageSurface);
void selectFlip(SDL_Surface* ImageSurface);
void selectCrop(SDL_Surface* ImageSurface);

int main(int argc, char * argv[]) {
	SDL_Surface* ImageSurface = NULL;
	string Location;

	int mainChoice = 0;
	//Runs the Main Menu
	do {
		//Prevents save option showing before image is loaded
		if (mainChoice == 0) {
			mainChoice = mainMenu(NULL);
		}
		else {
			mainChoice = mainMenu(ImageSurface);
		}

		//Handles main menu choice
		switch (mainChoice) {
		//Exits the program
		case 0:
			SDL_FreeSurface(ImageSurface);
			break;
		//Load an image
		case 1: {
			//Clears the screen
			system("cls");

			//Gets the image location from the user
			cout << "Please enter the name, or file path, of the image you wish to open. (Include file extension)" << endl;
			cin >> Location;

			// Load in the Image
			ImageSurface = LoadSDLImage(Location.c_str());

			// Check if the image has been loaded correctly
			if (ImageSurface == NULL)
			{
				system("cls");
				cout << "!!! Unable to Load Image !!!" << endl;
				cout << "Press Esc to return to the Main Menu." << endl;
				waitForEscape();
				continue;
			}
			else {
				system("cls");
				int imgChoice = 0;
				//Runs the Image Processing Menu
				do {
					system("cls");
					cout << "Using image: " << Location << endl << endl;
					imgChoice = imgMenu();
					switch (imgChoice) {
					//Returns to main menu
					case 0:
						break;
					//Displays image
					case 1:
						selectDisplay(ImageSurface, Location);
						break;
					//Gets RGB value of pixel
					case 2:
						selectRGB(ImageSurface, Location);
						waitForEscape();
						break;
					//Opens colour adjustment menu
					case 3: {
						int colourChoice = 0;
						//Runs the Colour Adjustment Menu
						do {
							system("cls");
							colourChoice = colourMenu();
							switch (colourChoice) {
							//Return to image processing menu
							case 0:
								break;
							//Adjust contrast
							case 1:
								selectContrast(ImageSurface);
								waitForEscape();
								break;
							//Apply grayscale
							case 2:
								makeGrayscale(ImageSurface, false);
								waitForEscape();
								break;
							//Adjust brightness
							case 3:
								selectBrightness(ImageSurface);
								waitForEscape();
								break;
							//Invert colours
							case 4:
								invertColours(ImageSurface);
								waitForEscape();
								break;
							}
						} while (colourChoice != 0);
						//Colour Adjustment Menu closes
						break;
					}
					//Open Filter menu
					case 4: {
						int filterChoice = 0;
						//Runs the Filter Menu
						do {
							system("cls");
							filterChoice = filterMenu();
							switch (filterChoice) {
							//Return to image processing menu
							case 0:
								break;
							//Red Filter
							case 1:
								applyFilter(ImageSurface, 1);
								waitForEscape();
								break;
							//Green Filter
							case 2:
								applyFilter(ImageSurface, 2);
								waitForEscape();
								break;
							//Blue Filter
							case 3:
								applyFilter(ImageSurface, 3);
								waitForEscape();
								break;
							//Cyan Filter
							case 4:
								applyFilter(ImageSurface, 4);
								waitForEscape();
								break;
							//Purple Filter
							case 5:
								applyFilter(ImageSurface, 5);
								waitForEscape();
								break;
							//Yellow Filter
							case 6:
								applyFilter(ImageSurface, 6);
								waitForEscape();
								break;
							}
						} while (filterChoice != 0);
						//Filter Menu closes
						break;
					}
					//Display transformation menu
					case 5: {
						int transformChoice = 0;
						//Runs the Transformation Menu
						do {
							system("cls");
							transformChoice = transformMenu();
							switch (transformChoice) {
							//Return to image processing menu
							case 0:
								break;
							//Rotate image
							case 1:
								selectRotate(ImageSurface);
								waitForEscape();
								break;
							//Flip image
							case 2:
								selectFlip(ImageSurface);
								waitForEscape();
								break;
						    //Crop image
							case 3:
								selectCrop(ImageSurface);
								waitForEscape();
							}
						} while (transformChoice != 0);
						//Transformation Menu Closes
						break;
					}
					}
				} while (imgChoice != 0);
				//Image Menu Closes
			}

			//End of Switch statement
			break; }
		case 2:
			saveImage(NULL, ImageSurface, false);
			break;
		}
	} while (mainChoice != 0);
	//Main Menu closes

	return 0;
}

//Displays the Main Menu
int mainMenu(SDL_Surface* ImageSurface) {
	system("cls");

	cout << "Welcome to Jed's Image Processor." << endl;
	cout << "Please select an opton from the list below:" << endl << endl;
	
	cout << "(1) Load new image." << endl;
	//Shows save option if image has been loaded
	if (ImageSurface != NULL) {
		cout << "(2) Save Loaded Image." << endl;
	}

	cout << endl << "(0) Exit Program." << endl;

	int choice;
	do {
		//Makes sure a number is entered
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		//Makes sure the input is within the available range
		if (choice < 0 || choice > 1) {
			if (choice == 2 && ImageSurface != NULL) {
				return choice;
			}
			else {
				cout << "Please enter one of the displayed numbers." << endl;
			}
		}
		//Runs whilst input is out of the available range
	} while (choice < 0 || choice > 1);
	return choice;
}

//Displays the Image Processing Menu
int imgMenu() {
	system("cls");
	cout << "Image Processing Menu" << endl;
	cout << "Select an option:" << endl << endl;

	cout << "(1) Display Image" << endl;
	cout << "(2) Get RGB values of a pixel" << endl;
	cout << "(3) Colour Adjustment" << endl;
	cout << "(4) Apply Filter" << endl;
	cout << "(5) Image Transformation" << endl;

	cout << endl << "(0) Go To Main Menu" << endl;

	int choice;
	do {
		//Makes sure a number is entered
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		//Makes sure the input is within the available range
		if (choice < 0 || choice > 5) {
			cout << "Please enter one of the displayed numbers." << endl;
		}
	} while (choice < 0 || choice > 5);
	return choice;
}

//Displays the Colour Adjustment Menu
int colourMenu() {
	system("cls");

	cout << "Colour Adjustment Menu" << endl;
	cout << "What you you like to do?" << endl << endl;

	cout << "(1) Change the contrast" << endl;
	cout << "(2) Apply Grayscale" << endl;
	cout << "(3) Adjust Brightness" << endl;
	cout << "(4) Invert Colours" << endl;

	cout << endl << "(0) Go To Image Processing Menu" << endl;

	int choice;
	do {
		//Makes sure a number is entered
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		//Makes sure the input is within the available range
		if (choice < 0 || choice > 4) {
			cout << "Please enter one of the displayed numbers." << endl;
		}
		//Runs whilst input is out of the available range
	} while (choice < 0 || choice > 4);
	return choice;
}

int transformMenu() {
	system("cls");

	cout << "Image Transformation Menu" << endl;
	cout << "How would you like to transform the image?" << endl << endl;

	cout << "(1) Rotate Image (90, 180 or 270 degrees)" << endl;
	cout << "(2) Flip Image" << endl;
	cout << "(3) Crop Image" << endl;
	
	cout << endl << "(0) Go To Image Processing Menu" << endl;

	int choice;
	do {
		//Makes sure a number is entered
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		//Makes sure the input is within the available range
		if (choice < 0 || choice > 3) {
			cout << "Please enter one of the displayed numbers." << endl;
		}
		//Runs whilst input is out of the available range
	} while (choice < 0 || choice > 3);
	return choice;
}

int filterMenu() {
	system("cls");

	cout << "Image Filter Menu" << endl;
	cout << "Which filter would you like to apply?" << endl << endl;

	cout << "(1) Red Filter" << endl;
	cout << "(2) Green Filter" << endl;
	cout << "(3) Blue Filter" << endl;
	cout << "(4) Cyan Filter" << endl;
	cout << "(5) Purple Filter" << endl;
	cout << "(6) Yellow Filter" << endl;

	cout << endl << "(0) Return to Image Processing Menu" << endl;

	int choice;
	do {
		//Makes sure a number is entered
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		//Makes sure the input is within the available range
		if (choice < 0 || choice > 6) {
			cout << "Please enter one of the displayed numbers." << endl;
		}
		//Runs whilst input is out of the available range
	} while (choice < 0 || choice > 6);
	return choice;
}

void selectDisplay(SDL_Surface* ImageSurface, string Location) {
	system("cls");

	//Displays the image until the window is closed or the ESC key is pressed
	CreateWindow(Location.c_str(), ImageSurface->w, ImageSurface->h);
	cout << "Here is the image you loaded." << endl;
	cout << "To continue: close the window, or press ESC in window." << endl;
	DisplayImagePreview(ImageSurface);
	CloseSDLWindow();
}

void selectRGB(SDL_Surface* ImageSurface, string Location) {
	system("cls");

	Uint8 R = 0, G = 0, B = 0;
	//Displays the image until the window is closed or a click is registered
	CreateWindow(Location.c_str(), ImageSurface->w, ImageSurface->h);
	cout << "Click on the pixel you wish to check the RGB values of." << endl;
	//Stores the RGB values of the selected pixel
	getSelectedRGBValue(ImageSurface, &R, &G, &B);
	CloseSDLWindow();
	//Displays the RGB values
	cout << "The RGB values of the selected pixel are:" << endl;
	cout << "R: " << (int)R << endl;
	cout << "G: " << (int)G << endl;
	cout << "B: " << (int)B << endl;
	cout << endl << "Press Esc to continue.";
}

void selectContrast(SDL_Surface* ImageSurface) {
	system("cls");

	int c = 0;
	cout << "By how much would you like to adjust the contrast? (+/- 255)" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> c)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		if (c < -255 || c > 255) {
			cout << "Please enter an integer between -255 and 255." << endl;
		}
		//Makes sure input is within the range
	} while (c < -255 || c > 255);
	changeContrast(ImageSurface, c);
}

void selectBrightness(SDL_Surface* ImageSurface) {
	system("cls");

	int brightness = 0;
	cout << "By how much would you like to adjust the brightness? (+/- 255)" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> brightness)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		if (brightness < -255 || brightness > 255) {
			cout << "Please enter an integer between -255 and 255." << endl;
		}
		//Makes sure input is within the range
	} while (brightness < -255 || brightness > 255);
	adjustBrightness(ImageSurface, brightness);
}

void selectRotate(SDL_Surface* ImageSurface) {
	system("cls");

	int degrees = 0;
	cout << "By how many degrees, clockwise, would you like to rotate the image? (90/180/270)" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> degrees)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		if (degrees != 90 && degrees != 180 && degrees != 270) {
			cout << "Please enter either 90, 180 or 270." << endl;
		}
		//Makes sure input is within the range
	} while (degrees != 90 && degrees != 180 && degrees != 270);
	rotateImage(ImageSurface, degrees);
}

void selectFlip(SDL_Surface* ImageSurface) {
	system("cls");

	cout << "How would you like to flip the image?" << endl << endl;
	cout << "(1) Horizontally" << endl;
	cout << "(2) Vertically" << endl;

	cout << endl << "(0) Cancel" << endl;

	int choice;
	do {
		//Makes sure input is a number
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}
		if (choice < 0 && choice > 2) {
			cout << "Please enter one of the displayed numbers." << endl;
		}
		else {
			switch (choice) {
			case 0:
				break;
			case 1:
				flipImage(ImageSurface, 'h');
				break;
			case 2:
				flipImage(ImageSurface, 'v');
				break;
			}
		}
		//Makes sure input is within the range
	} while (choice < 0 || choice > 2);
}

void selectCrop(SDL_Surface* ImageSurface) {
	system("cls");

	int left = 0, top = 0, right = 0, bottom = 0;
	cout << "The dimensions of your current image are (width x height): " << ImageSurface->w << " x " << ImageSurface->h << endl;

	cout << "How much would you like to crop from the left side of the image?" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> left)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}

		//Makes sure number entered is greater than zero and does not exceed the image dimensions
		if (left >= ImageSurface->w || left < 0) {
			cout << "Please enter a number between 0 and " << ImageSurface->w << "." << endl;
		}

	} while (left >= ImageSurface->w || left < 0);

	cout << "How much would you like to crop from the top of the image?" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> top)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}

		//Makes sure number entered is greater than zero and does not exceed the image dimensions
		if (top >= ImageSurface->h || top < 0) {
			cout << "Please enter a number between 0 and " << ImageSurface->h << "." << endl;
		}

	} while (top >= ImageSurface->h << top < 0);

	cout << "How much would you like to crop from the right side of the image?" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> right)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}

		//Makes sure number entered is greater than zero and does not exceed the image dimensions
		if (right >= ImageSurface->w - left || right < 0) {
			cout << "Please enter a number between 0 and " << ImageSurface->w - left << "." << endl;
		}

	} while (right >= ImageSurface->w - left || right < 0);

	cout << "How much would you like to crop from the bottom side of the image?" << endl;
	do {
		//Makes sure input is a number
		while (!(cin >> bottom)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number" << endl;
		}

		//Makes sure number entered is greater than zero and does not exceed the image dimensions
		if (bottom >= ImageSurface->h - top || bottom < 0) {
			cout << "Please enter a number between 0 and " << ImageSurface->h - top << "." << endl;
		}

	} while (bottom >= ImageSurface->h - top || bottom < 0);

	cropImage(ImageSurface, left, top, right, bottom);
}
