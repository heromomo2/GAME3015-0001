#include "World.hpp"
#include <fstream>
#include <string>//
#include <iostream>// to print to console

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mRaptor1(nullptr)
	, mRaptor2(nullptr)
	, mBackground(nullptr)
	, mBackground2(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(-5.0f)//(-1.0f)
	, Floorloopcounter(0)
	, IsRaptorOneLimitX(false)
	, IsRaptorTwoLimitX(false)
	, Raptor1_X(0.0)
	, Raptor2_X(0.0)
{
}
// add it for input
CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::update(const GameTimer& gt)
{
	//const float dt = gt.DeltaTime();

	//mPlayerAircraft->setVelocity(0.0f,0.0f,0.0f);

	// add it for unput
	//while (!mCommandQueue.isEmpty())

	//{
	//	mSceneGraph->onCommand(mCommandQueue.pop(), dt);

	//}
	////mPlayerAircraft->accelerate(0.0f, 0.0f, 0.0f);


	////Keep player's position inside the screen bounds, at least borderDistance units from the border
	//XMFLOAT3 position = mPlayerAircraft->getWorldPosition();

	//if (position.x < -1.5)
	//{
	//	position.x = -1.5f;
	//}
	//else if (position.x > 1.5)
	//{
	//	position.x = 1.5f;
	//}
	//else if (position.z < -0.9)
	//{
	//	position.z = -0.9f;
	//}
	//else if (position.z > 0.9)
	//{
	//	position.z = 0.9f;
	//}

	//mPlayerAircraft->setPosition(position.x,position.y,position.z);



	// loop background
	if (mBackground->getWorldPosition().z < -50.0f)
	{
		// place back  the mBackground to it's original position
		mBackground->setPosition(0, -50, 150.0);
		// tracking how many times it loop.
		Floorloopcounter = Floorloopcounter + 1;
		//std::cout << "Floorloopcounter: "<< Floorloopcounter;
	}
	else
	{
		// to move the background
		mBackground->setVelocity(0, 0, mScrollSpeed + gt.DeltaTime());
		
	}

	if (mBackground2->getWorldPosition().z < -50.0f)
	{
		// place back  the mBackground to it's original position
		mBackground2->setPosition(0, -50, 150.0);
		// tracking how many times it loop.
		Floorloopcounter = Floorloopcounter + 1;
		//std::cout << "Floorloopcounter: "<< Floorloopcounter;
	}
	else
	{
		// to move the background
		mBackground2->setVelocity(0, 0, mScrollSpeed + gt.DeltaTime());
	}

	/*float playerWPX = mPlayerAircraft->getWorldPositionX();
	float playerWPY = mPlayerAircraft->getWorldPositionY();
	float PlayerWPZ = mPlayerAircraft->getWorldPositionY();*/

	//std::ofstream myfile;
	//myfile.open("example.txt");
	//myfile << "dicks\n";
	//myfile.close();


	//OnPlayerInput(gt);


	mSceneGraph->update(gt);
	MoveRaptorSideToSide(gt);
}

//void World::OnPlayerInput(const GameTimer& gt)
//{
//	const float dt = gt.DeltaTime();
//	float x = 0;
//	float z = 0;
//	float Speed = 500.0f;
//
//	if (GetAsyncKeyState('A') & 0x8000)
//	{
//		if (mPlayerAircraft->getWorldPositionX() >= -1.0)
//		{
//			x -= Speed;
//		}
//	}
//
//	if (GetAsyncKeyState('S') & 0x8000)
//	{
//		if (mPlayerAircraft->getWorldPositionZ() >= -0.9)
//		{
//			z -= Speed;
//		}
//	}
//	if (GetAsyncKeyState('D') & 0x8000)
//	{
//		if (mPlayerAircraft->getWorldPositionX() <= 1.0)
//		{
//			x += Speed;
//		}
//	}
//	if (GetAsyncKeyState('W') & 0x8000)
//	{
//		
//		if (mPlayerAircraft->getWorldPositionZ() <= 0.9)
//		{
//			z += Speed;
//		}
//		/*float PlayerWPZ = mPlayerAircraft->getWorldPositionZ();
//		float playerWPX = mPlayerAircraft->getWorldPositionX();
//		float playerWPY = mPlayerAircraft->getWorldPositionY();*/
//	}
//
//	if (abs(x) == abs(z) &&x!=0)
//	{
//		x *= 0.7071;
//		z *= 0.7071;
//	}
//	mPlayerAircraft->setVelocity(x * dt, 0, z * dt);
//
//	mRaptor2->setVelocity(x * dt, 0, z * dt);
//	mRaptor1->setVelocity(x * dt, 0, z * dt);
//	mPlayerAircraftShadow->setVelocity(x * dt, 0, z * dt);
//}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 1.0, 0.0);
	mPlayerAircraft->setScale(3.0f, 0.0f, 3.0f);//(0.5, 0.01, 0.5);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	mRaptor1 = enemy1.get();
	mRaptor1->setPosition(-0.5, 1.0, 20.0);
	mRaptor1->setScale(3.0f, 0.0f, 3.0);
	mRaptor1->setWorldRotation(0, XM_PI, 0);
	mSceneGraph->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	mRaptor2 = enemy2.get();
	mRaptor2->setPosition(10.0, 1.0, 20.0);
	mRaptor2->setScale(3.0f, 0.0f, 3.0);
	mRaptor2->setWorldRotation(0, XM_PI, 0);
	mSceneGraph->attachChild(std::move(enemy2));



	//std::unique_ptr<AircraftShadow> raptorshadowtest(new AircraftShadow(AircraftShadow::RaptorShadow, mGame));
	//auto raptorshadow = raptorshadowtest.get();
	//raptorshadow->setPosition(0.0, 0.0, 0.0);
	//raptorshadow->setScale(0.5, 0.5, 1.0);
	//raptorshadow->setWorldRotation(0, 0, 0);
	//mRaptor1->attachChild(std::move(raptorshadowtest));




	//std::unique_ptr<AircraftShadow> raptorshadowtest2(new AircraftShadow(AircraftShadow::RaptorShadow, mGame));
	//auto raptorshadow2 = raptorshadowtest2.get();
	//raptorshadow2->setPosition(0.0, 0.0, 0.0);
	//raptorshadow2->setScale(0.5, 0.5, 1.0);
	//raptorshadow2->setWorldRotation(0, 0, 0);
	//mRaptor2->attachChild(std::move(raptorshadowtest2));



	//std::unique_ptr<AircraftShadow> Eagleshadowtest1(new AircraftShadow(AircraftShadow::EagleShadow, mGame));
	//mPlayerAircraftShadow = Eagleshadowtest1.get();
	//mPlayerAircraftShadow->setPosition(0.0, -0.01, -0.5);
	//mPlayerAircraftShadow->setScale(0.5, 0.5, 0.5);
	////mPlayerAircraftShadow->setWorldRotation(0, 0, 0);
	////mPlayerAircraft->attachChild(std::move(Eagleshadowtest1));
	//mPlayerAircraft->attachChild(std::move(Eagleshadowtest1));


	//std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	//mBackground = backgroundSprite.get();
	////mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	//mBackground->setPosition(0.0f, -20.0, 15.0);
	//mBackground->setScale(50.0, 50.0, 50.0);
	////mBackground->setVelocity(0, 0, -mScrollSpeed);
	//mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Skybox> skyboxSprite(new Skybox(mGame));
	mSkybox = skyboxSprite.get();
	mSkybox->setPosition(0, 0, 0);
	mSkybox->setScale(5000.0, 5000.0, 5000.0);
	mSceneGraph->attachChild(std::move(skyboxSprite));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(SpriteNode::Desert,mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0.0f, -50, 50.0);
	mBackground->setScale(100.0f, 100.0f, 100.0f);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	
	std::unique_ptr<SpriteNode> backgroundSprite2(new SpriteNode(SpriteNode::Desert, mGame));
	mBackground2 = backgroundSprite2.get();
	mBackground2->setPosition(0.0f, -50, 150.0);
	mBackground2->setScale(100.0f, 100.0f, 100.0f);
	mSceneGraph->attachChild(std::move(backgroundSprite2));

	std::unique_ptr<DebugShadowMap> shadowMap(new DebugShadowMap(mGame));
	mDebugMap = shadowMap.get();
	mSceneGraph->attachChild(std::move(shadowMap));



	mSceneGraph->build();
}

void World::MoveRaptorSideToSide(const GameTimer& gt)
{

	const float dt = gt.DeltaTime();
	// ememy 1
	float x_Raptor1 = 0;
	float z_Raptor1 = 0;
	// ememy 2
	float x_Raptor2 = 0;
	float z_Raptor2 = 0;

	Raptor1_X = mRaptor1->getWorldPositionX();
	Raptor2_X = mRaptor2->getWorldPositionX();
	float Speed = 100.0f;

	// first ememy air place
	if (IsRaptorOneLimitX == false)
	{
		x_Raptor1 -= Speed;

		if (Raptor1_X < 100.5 && IsRaptorOneLimitX != true)
		{
			IsRaptorOneLimitX = true;
			/*myfile.open("example.txt");
			myfile << "RaptorLimitXBounds: " << Raptor1_X << "\n";
			myfile << " IsRaptorOneLimitX: " << IsRaptorOneLimitX;
			myfile.close();*/
		}
	}
	else if (IsRaptorOneLimitX == true)
	{
		x_Raptor1 += Speed;
		if (Raptor1_X > 2.0 && IsRaptorOneLimitX != false)
		{
			IsRaptorOneLimitX = false;
			/*myfile.open("example.txt");
			myfile << "RaptorLimitXBounds: " << Raptor1_X << "\n";
			myfile << " IsRaptorOneLimitX: " << IsRaptorOneLimitX;
			myfile.close();*/
		}
	}

	// ememy 2
	if (IsRaptorTwoLimitX == false)
	{
		x_Raptor2 -= Speed;

		if (Raptor2_X < -2.0 && IsRaptorTwoLimitX != true)
		{
			IsRaptorTwoLimitX = true;
			/*myfile.open("example.txt");
			myfile << "RaptorLimitXBounds: " << Raptor1_X << "\n";
			myfile << " IsRaptorOneLimitX: " << IsRaptorOneLimitX;
			myfile.close();*/
		}
	}
	else if (IsRaptorTwoLimitX == true)
	{
		x_Raptor2 += Speed;
		if (Raptor2_X > -0.5 && IsRaptorTwoLimitX != false)
		{
			IsRaptorTwoLimitX = false;
			/*myfile.open("example.txt");
			myfile << "RaptorLimitXBounds: " << Raptor1_X << "\n";
			myfile << " IsRaptorOneLimitX: " << IsRaptorOneLimitX;
			myfile.close();*/
		}
	}

	mRaptor1->setVelocity(x_Raptor1 * dt, 0, z_Raptor1 * dt);
	mRaptor2->setVelocity(x_Raptor2 * dt, 0, z_Raptor2 * dt);
}