#include <raylib.h>
#include <stdio.h>

void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C, int playerSxore, int enemyScore);
void BallMovement(struct Rectangle *boxA,struct Rectangle *boxB, struct Rectangle *boxC ,int *ballSpeed_X, int *ballSpeed_Y);
void aiPeddal(struct Rectangle *boxB, struct Rectangle *boxC,int *movementSpeed);
void playerMovement(struct Rectangle *boxA, int *playerSpeed);
void gameScore(struct Rectangle *boxC, int *playerScore, int *enemyScore, bool *playerWin, bool *enemyWin);

//void PlayAudio();


int main()
{
	const int screenH = 1000;//visina ekrana u pikselima
	const int screenW = 1200;//širina ekrana u pikselima
	
	//Promenljive za brzinu lopte za x i ipsilon osuu
	int ballSpeedX = 5;
	int ballSpeedY = 6;

	//promenljiva za brzinu kretanja protivnièke pedale
	int aiMovementSpeed = 5;

	//promenljuiva brzine kretanja igraèa
	int brzinaKretanja = 12;

	int playerScore = 0;
	int enemyScore = 0;
	bool didPlayerWin = false;
	bool didEnemyWin = false;

	//inicijalizacija prozora
	InitWindow(screenW, screenH, "test igra");

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
		gameScore(&boxC, &playerScore, &enemyScore, &didPlayerWin, &didEnemyWin);
		playerMovement(&boxA, &brzinaKretanja);
		BallMovement(&boxA, &boxB, &boxC, &ballSpeedX, &ballSpeedY);
		aiPeddal(&boxB, &boxC, &aiMovementSpeed);

		printf("p:%d e:%d\n", playerScore, enemyScore);
		ScreenDraw(boxA, boxB, boxC, playerScore, enemyScore);
		
	}

	CloseWindow();

	return 0;

}

void gameScore(struct Rectangle *boxC, int *playerScore, int *enemyScore, bool *playerWin, bool *enemyWin)
{

	if (boxC->x <= 0)
	{

		*enemyScore += 1;

	}
	if (boxC->x + boxC->width >= GetScreenWidth())
	{

		*playerScore += 1;

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
	//Provere da li igraè izašao iz polja ekrana----------------------------------------
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
	if (boxC->y <= boxB->y)
	{

		boxB->y -= *movementSpeed;

	}
	//------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------

//funkcija za kretanje lopte----------------------------------------------------------------------------------------------------------
void BallMovement(struct Rectangle *boxA, struct Rectangle *boxB, struct Rectangle *boxC, int *ballSpeed_X, int *ballSpeed_Y)
{
	//Provere ako lopta doðe do gornje ili donje ivice do se invertuje ballSpeedY-------------------------------------------------
	if (boxC->y <= 0 || boxC->y + boxC->height >= GetScreenHeight())
	{
		*ballSpeed_Y *= -1;
		printf("sudar\n");
	}
	//----------------------------------------------------------------------------------------------------------------------------
	if (boxC->x <= 0 || boxC->x + boxC->width >= GetScreenWidth())
	{
		*ballSpeed_X *= -1;
		printf("sudar\n");
	}
	
	//boolijani koju se koriste da bi se proverilo da lilopta je došle u kontakt sa pedalama---------------------------------------
	bool collisionAC = CheckCollisionRecs(*boxA, *boxC);
	bool collisionBC = CheckCollisionRecs(*boxB, *boxC);
	//-----------------------------------------------------------------------------------------------------------------------------

	//Provera da li je lopta došla u kontakt sapedalama----------------------------------------------------------------------------
	if (collisionAC == true || collisionBC == true)
	{

		*ballSpeed_X *= -1;
		
	}
	//-----------------------------------------------------------------------------------------------------------------------------

	//Promena pozicije lopte-------------------------------------------------------------------------------------------------------
	boxC -> x += *ballSpeed_X;
	boxC -> y += *ballSpeed_Y;
	//------------------------------------------------------------------------------------------------------------------------------
	

}
//------------------------------------------------------------------------------------------------------------------------------------

//funkcija za crtanje ekrana----------------------------------------------------------------------------------------------------------
void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C, int playerScore, int enemyScore)
{	
	//funkcija za èišæenje pozadine----------------------------------------------------------------------------------------------------
	ClearBackground(BLACK);
	//---------------------------------------------------------------------------------------------------------------------------------
	BeginDrawing();

		DrawRectangleRec(box_A, WHITE);
		DrawRectangleRec(box_B, WHITE);
		DrawRectangleRec(box_C, WHITE);
		DrawText(TextFormat("%d", playerScore), 120, 100, 40, WHITE);
		DrawText(TextFormat("%d", enemyScore), 1080, 100, 40, WHITE);


	EndDrawing();
			

}