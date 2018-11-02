// CrossyRoads.cpp: A program using the TL-Engine

//G20761896 DSKottachchi      Crossy Roads Game

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;
#include <sstream>
#include <ctime>
using namespace std;
bool i = true;
float xCoordinate;
bool win = true;
int point = 0;
bool pigDead = false;
bool play = true;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("./Media");
	myEngine->AddMediaFolder("./Media/backdrop");
	myEngine->AddMediaFolder("./Media/cars");
	myEngine->AddMediaFolder("./Media/ground");
	myEngine->AddMediaFolder("./Media/tyres");
	myEngine->AddMediaFolder("./Media/pig");

	/**** Set up your scene here ****/
	IMesh*floorMesh = myEngine->LoadMesh("Floor.x");
	IMesh*carMesh = myEngine->LoadMesh("Caddy_eldorado.x");
	IMesh*pigMesh = myEngine->LoadMesh("FF1FSL1P8D5ZOAPZBSYO3436F.x");
	IMesh*roverMesh = myEngine->LoadMesh("Rangerover.x");
	IMesh* pickupMesh = myEngine->LoadMesh("pickUp.x");
	IMesh* truckMesh = myEngine->LoadMesh("truck.x");
	IMesh*skyMesh = myEngine->LoadMesh("Skybox.x");
	IMesh*tunnelMesh = myEngine->LoadMesh("tyre.x");
	IMesh*roadMesh = myEngine->LoadMesh("island1.x");
	IMesh*coinMesh = myEngine->LoadMesh("TwoPence.x");

	IModel*coin = coinMesh->CreateModel(300, 100, -450);
	IModel*coin1 = coinMesh->CreateModel(600, 100, -20);
	IModel*coin2 = coinMesh->CreateModel(-450, 100, -250);
	IModel*coin3 = coinMesh->CreateModel(0, 100, 300);
	IModel*tunnel = tunnelMesh->CreateModel(-1217, 5, 20);
	IModel*tunnel1 = tunnelMesh->CreateModel(932, 5, 20);
	tunnel->SetSkin("black.jpeg"); tunnel1->SetSkin("black.jpeg");

	IModel*pickup = pickupMesh->CreateModel(300, 0, -350);
	IModel*truck = truckMesh->CreateModel(200, 10, 300);
	IModel*rover = roverMesh->CreateModel(-800, 0, -80);
	IModel*car = carMesh->CreateModel(800, 0, 120);
	rover->Scale(30); car->Scale(70); pickup->Scale(30); truck->Scale(17); coin->Scale(3); coin1->Scale(3); coin2->Scale(3); coin3->Scale(3); tunnel->Scale(1100); tunnel1->Scale(1100);
	rover->RotateLocalY(90); car->RotateLocalY(-90); pickup->RotateLocalY(-90); truck->RotateLocalY(90); tunnel->RotateLocalZ(-90); tunnel1->RotateLocalZ(-90);

	IModel*road = roadMesh->CreateModel(0, 3, 0);
	road->ScaleX(20);
	road->ScaleZ(25);

	IModel*floor = floorMesh->CreateModel(0, 0, 0);
	floor->SetSkin("Baize.jpg");
	floor->Scale(-1);

	IModel*sky = skyMesh->CreateModel(0, 0, 0);

	IModel*pig = pigMesh->CreateModel(0, 40, -900);
	pig->Scale(80);  pig->RotateLocalY(180);
	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);
	IFont* endFont = myEngine->LoadFont("Comic Sans MS", 100);

	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual);
	myCamera->SetPosition(0, 1000, -1800);
	myCamera->LookAt(floor);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		float currentTime = clock() / 1000;
		float countDown = 30 - currentTime;
		if (countDown <= 0)
		{
			endFont->Draw("GameOver!", 600, 200, kRed, kCentre);
		}

		/**** Update your scene each frame here ****/
		myFont->Draw("Collect all the coins in 30 seconds", 250, 600, kWhite, kCentre);

		stringstream outText;
		outText << "Time: " << countDown;
		myFont->Draw(outText.str(), 1000, 20, kWhite);
		outText.str("");

		//coin rotation
		coin->RotateY(1); coin1->RotateY(1); coin2->RotateY(1); coin3->RotateY(1);

		//rover movement
		rover->MoveX(0.5);
		xCoordinate = rover->GetX();

		if (i == true)
		{
			if (xCoordinate == 800)
			{
				rover->SetPosition(-800, 0, -80);
				i = false;
			}
		}

		if (i == false)
		{
			rover->MoveX(-0.5f);
			i = true;
		}

		//car movement
		car->MoveX(-1);
		xCoordinate = car->GetX();

		if (i == true)
		{
			if (xCoordinate == -800)
			{
				car->SetPosition(800, 0, 120);
				i = false;
			}
		}

		if (i == false)
		{
			car->MoveX(-1);
			i = true;
		}

		//pickup movement
		pickup->MoveX(-1);
		xCoordinate = pickup->GetX();

		if (i == true)
		{
			if (xCoordinate == -800)
			{
				pickup->SetPosition(800, 0, -350);
				i = false;
			}
		}

		if (i == false)
		{
			pickup->MoveX(-1);
			i = true;
		}

		//truck movement
		truck->MoveX(0.5);
		xCoordinate = truck->GetX();

		if (i == true)
		{
			if (xCoordinate == 800)
			{
				truck->SetPosition(-800, 10, 300);
				i = false;
			}

		}

		if (i == false)
		{
			truck->MoveX(-0.5f);
			i = true;
		}

		//Pig movement
		if (myEngine->KeyHit(Key_Up))
		{
			pig->MoveLocalZ(-2);
		}

		if (myEngine->KeyHit(Key_Down))
		{
			pig->MoveLocalZ(2);
		}

		if (myEngine->KeyHit(Key_Right))
		{
			pig->RotateY(90);
		}

		if (myEngine->KeyHit(Key_Left))
		{
			pig->RotateY(-90);
		}

		if (pigDead == false)
		{	
			// collision detection
			float x, y, z;
			x = pig->GetX();
			y = pig->GetY();
			z = pig->GetZ();

			float carMinX = car->GetX() - 200;
			float carMaxX = car->GetX() + 200;
			float carMinZ = car->GetZ() - 100;
			float carMaxZ = car->GetZ() + 100;

			if (x > carMinX && x < carMaxX && z>carMinZ && z < carMaxZ)
			{
				pigDead = true;
				pigMesh->RemoveModel(pig);
			}

			float roverMinX = rover->GetX() - 150;
			float roverMaxX = rover->GetX() + 150;
			float roverMinZ = rover->GetZ() - 100;
			float roverMaxZ = rover->GetZ() + 100;

			if (x > roverMinX && x < roverMaxX && z > roverMinZ && z < roverMaxZ)
			{
				pigDead = true;
				pigMesh->RemoveModel(pig);
			}

			float pickupMinX = pickup->GetX() - 180;
			float pickupMaxX = pickup->GetX() + 180;
			float pickupMinZ = pickup->GetZ() - 100;
			float pickupMaxZ = pickup->GetZ() + 100;

			if (x > pickupMinX && x < pickupMaxX && z > pickupMinZ && z < pickupMaxZ)
			{
				pigDead = true;
				pigMesh->RemoveModel(pig);
			}

			float truckMinX = truck->GetX() - 800;
			float truckMaxX = truck->GetX() + 250;
			float truckMinZ = truck->GetZ() - 100;
			float truckMaxZ = truck->GetZ() + 100;

			if (x > truckMinX && x < truckMaxX && z > truckMinZ && z < truckMaxZ)
			{
				pigDead = true;
				pigMesh->RemoveModel(pig);
			}

			float xPOS = x - coin->GetX();
			float yPOS = y - coin->GetY();
			float zPOS = z - coin->GetZ();
			float collisionDist = sqrt(xPOS*xPOS + yPOS * yPOS + zPOS * zPOS);

			if (collisionDist < 100)
			{
				coin->SetZ(1500);
				point++;
			}

			float xPOS1 = x - coin1->GetX();
			float yPOS1 = y - coin1->GetY();
			float zPOS1 = z - coin1->GetZ();
			float collisionDist1 = sqrt(xPOS1*xPOS1 + yPOS1 * yPOS1 + zPOS1 * zPOS1);

			if (collisionDist1 < 150)
			{
				coin1->SetZ(1500);
				point++;
			}

			float xPOS2 = x - coin2->GetX();
			float yPOS2 = y - coin2->GetY();
			float zPOS2 = z - coin2->GetZ();
			float collisionDist2 = sqrt(xPOS2*xPOS2 + yPOS2 * yPOS2 + zPOS2 * zPOS2);

			if (collisionDist2 < 100)
			{
				coin2->SetZ(1500);
				point++;
			}

			float xPOS3 = x - coin3->GetX();
			float yPOS3 = y - coin3->GetY();
			float zPOS3 = z - coin3->GetZ();
			float collisionDist3 = sqrt(xPOS3*xPOS3 + yPOS3 * yPOS3 + zPOS3 * zPOS3);

			if (collisionDist3 < 150)
			{
				coin3->SetZ(1500);
				point++;
			}

			// if the pig reaches the finishing line
			if (countDown > 0 && x > -800 && x < 800 && z > 800 && z < 1000 && point == 4)
			{
				endFont->Draw("Congratulations!", 600, 200, kRed, kCentre);
			}

			stringstream pointText;
			pointText << "Points: " << point;
			myFont->Draw(pointText.str(), 20, 20, kWhite);
			pointText.str("");
		}
		else
		{
			endFont->Draw("GameOver!", 600, 200, kRed, kCentre);
		}
		
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
