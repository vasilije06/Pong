#include <raylib.h>
#include <stdio.h>

void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C, int playerSxore, int enemyScore, int screenNum);
void BallMovement(struct Rectangle *boxA,struct Rectangle *boxB, struct Rectangle *boxC ,int *ballSpeed_X, int *ballSpeed_Y, Sound *sound, Sound *sound1);
void aiPeddal(struct Rectangle *boxB, struct Rectangle *boxC,int *movementSpeed);
void playerMovement(struct Rectangle *boxA, int *playerSpeed);
void gameScore(struct Rectangle* boxA, struct Rectangle* boxB, struct Rectangle *boxC, int *playerScore, int *enemyScore, int *screenNum, int *ballSpeedX, int *ballSpeedY , bool *gameStart);
void StartGame(bool *startGame,int *screenNum, int *playerScore, int *enemyScore, int *ballSpeedX, int *ballSpeedY);




int main()
{
	const int screenH = 1000;//visina ekrana u pikselima
	const int screenW = 1200;//širina ekrana u pikselima
	
	//Promenljive za brzinu lopte za x i ipsilon osuu
	int ballSpeedX = 6;
	int ballSpeedY = 5;

	//promenljiva za brzinu kretanja protivnièke pedale
	int aiMovementSpeed = 6;

	//promenljuiva brzine kretanja igraèa
	int brzinaKretanja = 8;

	//promenljive peona pedala
	int playerScore = 0;
	int enemyScore = 0;

	//promenljiva koja kontroliše koji ekran se crta
	int screenNumber = 0;

	//bulijan koji proverava da li je igra poèela
	bool gameStart = false;
	
	//inicijalizacija prozora
	InitWindow(screenW, screenH, "Pong");
	
	InitAudioDevice();
	
	Sound sfxZid;
	Sound sfxPedala;

	sfxZid = LoadSound("sfxZid.wav");
	sfxPedala = LoadSound("sfxPedala.wav");
	
	//ciljani fps
	SetTargetFPS(60);

	//Inicijalizacija struktura za lopte i pedale
	Rectangle boxA = { 40.0f , GetScreenWidth() / 2 - 200 , 20, 120};
	Rectangle boxB = { screenW - 60, GetScreenWidth() / 2.0f - 200 , 20, 120};
	Rectangle boxC = { screenW / 2 , screenH / 2 - 40, 20, 20};


	//glavni loop igre
	while (!WindowShouldClose())
	{	

		
		//pozivanje funkcioja
		StartGame(&gameStart, &screenNumber, &playerScore, &enemyScore, &ballSpeedX, &ballSpeedY);
		
		if (gameStart == true)
		{
		
			gameScore(&boxA, &boxB, &boxC, &playerScore, &enemyScore, &screenNumber, &ballSpeedX, &ballSpeedY, &gameStart);
			BallMovement(&boxA, &boxB, &boxC, &ballSpeedX, &ballSpeedY, &sfxPedala, &sfxZid);
			playerMovement(&boxA, &brzinaKretanja);
			aiPeddal(&boxB, &boxC, &aiMovementSpeed);

		
		}
		/*if (IsKeyPressed(KEY_A))
		{
			PlaySound(sound);
			printf("test zvuka");
		}*/
		//printf("screen Number: %d\n", screenNumber);
		ScreenDraw(boxA, boxB, boxC, playerScore, enemyScore, screenNumber);
		
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;

}

//funkcija koja se koristi sa bodove igre i odreðivanje broja ekrana
void gameScore(struct Rectangle *boxA, struct Rectangle *boxB, struct Rectangle *boxC, int *playerScore, int *enemyScore, int *screenNum, int *ballSpeedX, int *ballSpeedY, bool *gameStart)
{
	bool ballReset = false;
	bool playerPoint = false;
	bool enemyPoint = false;

	if (boxC->x <= 0)
	{

		*enemyScore += 1;
		ballReset = true;
		playerPoint = true;


	}
	if (boxC->x + boxC->width >= GetScreenWidth())
	{

		*playerScore += 1;
		ballReset = true;
		enemyPoint = true;

	}

	if (*gameStart == false)
		*screenNum = 0;

	if (*gameStart == true)
	{
		*screenNum = 1;
		//*gameStart = false;
	}

	if (*playerScore >= 9)
	{
		*screenNum = 2;
		*gameStart = false;
	}
	if (*enemyScore >= 9)
	{
		*screenNum = 3;
		*gameStart = false;
	}
	if (ballReset == true)
	{
		boxC->x = GetScreenWidth() / 2;
		boxC->y = GetScreenWidth() / 2 - 200;
		if (playerPoint = true)
		{
			*ballSpeedX = 5;
			*ballSpeedY = 5;
			playerPoint = false;
		}
		if (enemyPoint = true)
		{

			*ballSpeedX = -5;
			*ballSpeedY = 5;
			enemyPoint = false;

		}
		ballReset = false;
		//printf("ballReset\n");
	}



}

//funkcija za kretanje igraèa----------------------------------------------------------
void playerMovement(struct Rectangle *boxA, int *playerSpeed)
{
	//Preveravanje da li igraè stste dugmiæe na tastaturi-------------------------------
	if (IsKeyDown(KEY_UP))
	{

		boxA->y -= *playerSpeed;

	}
	if (IsKeyDown(KEY_DOWN))
	{

		boxA->y += *playerSpeed;

	}
	//----------------------------------------------------------------------------------

	//Provere da li igraè izašao iz polja ekrana----------------------------------------
	if (boxA->y <= 0)
	{
		boxA->y = 0;
	}
	if (boxA->y + boxA->height >= GetScreenHeight())
	{
		boxA->y = GetScreenHeight() - boxA->height;
	}
	//-----------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------

//funkcija za kretanje protivnièke pedale----------------------------------------------------------
void aiPeddal(struct Rectangle *boxB, struct Rectangle *boxC, int *movementSpeed)
{
	//Provere da li protivnik izašao iz polja ekrana----------------------------------------
	if (boxB->y <= 0)
	{
		boxB->y = 0;
	}
	if (boxB->y + boxB->height >= GetScreenHeight())
	{
		boxB->y = GetScreenHeight() - boxB->height;
	}
	//-----------------------------------------------------------------------------------

	//pomeranje protivnika u zavisnosi od pozicije lopte---------------------------------
	if (boxC->y >= boxB->y + (boxB->height / 2))
	{

		boxB->y += *movementSpeed;

	}
	if (boxC->y <= boxB->y + (boxB->height / 2))
	{

		boxB->y -= *movementSpeed;

	}
	//------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------

//funkcija za kretanje lopte----------------------------------------------------------------------------------------------------------
void BallMovement(struct Rectangle *boxA, struct Rectangle *boxB, struct Rectangle *boxC, int *ballSpeed_X, int *ballSpeed_Y, Sound *sound, Sound *sound1)
{
	//Provere ako lopta doðe do gornje ili donje ivice do se invertuje ballSpeedY-------------------------------------------------
	if (boxC->y <= 0 || boxC->y + boxC->height >= GetScreenHeight())
	{
		*ballSpeed_Y *= -1;
		PlaySound(*sound);

		//printf("sudar\n");
	}
	//----------------------------------------------------------------------------------------------------------------------------
	if (boxC->x <= 0 || boxC->x + boxC->width >= GetScreenWidth())
	{
		*ballSpeed_X *= -1;
		PlaySound(*sound);
		//printf("sudar\n");
	}
	
	//boolijani koju se koriste da bi se proverilo da lilopta je došle u kontakt sa pedalama---------------------------------------
	bool collisionAC = CheckCollisionRecs(*boxA, *boxC);
	bool collisionBC = CheckCollisionRecs(*boxB, *boxC);
	//-----------------------------------------------------------------------------------------------------------------------------

	//Provera da li je lopta došla u kontakt sa pedalama----------------------------------------------------------------------------
	if (collisionAC == true || collisionBC == true)
	{
		if (collisionAC)
		{
			boxC->x = boxA->x + boxA->width;  
		}
		else if (collisionBC)
		{
			boxC->x = boxB->x - boxC->width;  // Assuming paddleB is on the right side
		}

		*ballSpeed_X = -(*ballSpeed_X + GetRandomValue(-10, 12));

		if (abs(*ballSpeed_X) < 5)
		{
			*ballSpeed_X = (*ballSpeed_X < 0) ? -10 : 10;  // Set a minimum speed in the correct direction
		}

		
		*ballSpeed_Y = (*ballSpeed_Y + GetRandomValue(1, 2));

		if (abs(*ballSpeed_Y) < 3)
		{
			*ballSpeed_Y = (*ballSpeed_Y < 0) ? -4 : 4;  // Set a minimum speed in the correct direction
		}

		PlaySound(*sound1);
		
	}
	//-----------------------------------------------------------------------------------------------------------------------------

	//Promena pozicije lopte-------------------------------------------------------------------------------------------------------
	boxC -> x += *ballSpeed_X;
	boxC -> y += *ballSpeed_Y;
	//------------------------------------------------------------------------------------------------------------------------------
	

}
//------------------------------------------------------------------------------------------------------------------------------------

//funkcija za crtanje ekrana----------------------------------------------------------------------------------------------------------
void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C, int playerScore, int enemyScore, int screenNum)
{	
	//funkcija za èišæenje pozadine----------------------------------------------------------------------------------------------------
	ClearBackground(BLACK);
	//---------------------------------------------------------------------------------------------------------------------------------
	BeginDrawing();

		switch (screenNum)
		{
			case 0:
				DrawText("PONG", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, WHITE);
				break;

			case 1:
			DrawRectangleRec(box_A, WHITE);
			DrawRectangleRec(box_B, WHITE);
			DrawRectangleRec(box_C, WHITE);
			DrawText(TextFormat("%d", playerScore), 120, 100, 40, WHITE);
			DrawText(TextFormat("%d", enemyScore), 1080, 100, 40, WHITE);
			DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
			DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, 250, WHITE);
			break;

			case 2:
				DrawText("Pobedio Si", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, WHITE);
				break;

			case 3:
				DrawText("Izgubio Si", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, WHITE);
				break;

		}



	EndDrawing();
			

}

void StartGame(bool *startGame,int *screenNum, int *playerScore, int *enemyScore, int *ballSpeedX, int *ballSpeedY)
{

	if (IsKeyPressed(KEY_SPACE))
	{

		*startGame = true;
		//printf("radi");

	}
	if (IsKeyPressed(KEY_R) && *screenNum != 1)
	{
		*startGame = false;
		*screenNum = 0;
		*playerScore = 0;
		*enemyScore = 0;
		*ballSpeedX = 5;
		*ballSpeedY = 4;
		

	}

}
