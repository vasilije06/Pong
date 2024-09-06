#include <raylib.h>
#include <stdio.h>

void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C);
void BallMovement(struct Rectangle *boxA,struct Rectangle *boxB, struct Rectangle *boxC ,int *ballSpeed_X, int *ballSpeed_Y);
void aiPeddal(struct Rectangle *boxB, struct Rectangle *boxC,int *movementSpeed);

//void PlayAudio();


int main()
{
	const int screenW = 1200;
	const int screenH = 1000;
	int ballSpeedX = 5;
	int ballSpeedY = 6;


	int brzinaKretanja = 12;

	InitWindow(screenW, screenH, "test igra");

	SetTargetFPS(60);

	Rectangle boxA = { 40.0f , GetScreenWidth() / 2 - 200 , 20, 120};
	Rectangle boxB = { screenW - 60, GetScreenWidth() / 2.0f - 200 , 20, 120};
	Rectangle boxC = { screenW / 2 , screenH / 2 - 40, 20, 20};



	while (!WindowShouldClose())
	{	

		if (IsKeyDown(KEY_UP))
		{

			boxA.y = boxA.y - brzinaKretanja;

		}
		if (IsKeyDown(KEY_DOWN))
		{

			boxA.y = boxA.y + brzinaKretanja;

		}

		if (boxA.y <= 0)
		{
			boxA.y = 0;
		}
		if (boxA.y + boxA.height >= GetScreenHeight())
		{
			boxA.y = GetScreenHeight() - boxA.height;
		}

		BallMovement(&boxA, &boxB, &boxC, &ballSpeedX, &ballSpeedY);
		aiPeddal(&boxB, &boxC, &brzinaKretanja);



		printf("X:%.lf Y:%.lf\n", boxC.x, boxC.y);
		ScreenDraw(boxA, boxB, boxC);
		
	}

	CloseWindow();

	return 0;

}

void aiPeddal(struct Rectangle *boxB, struct Rectangle *boxC, int *movementSpeed)
{

	if (boxC->y >= boxB->y + (boxB->height / 2))
	{

		boxB->y += *movementSpeed;

	}
	if (boxC->y <= boxB->y)
	{

		boxB->y -= *movementSpeed;

	}

}

void BallMovement(struct Rectangle *boxA, struct Rectangle *boxB, struct Rectangle *boxC, int *ballSpeed_X, int *ballSpeed_Y)
{

	if (boxC->y <= 0 || boxC->y + boxC->height >= GetScreenHeight())
	{
		*ballSpeed_Y *= -1;
		printf("sudar\n");
	}
	if (boxC->x <= 0 || boxC->x + boxC->width >= GetScreenWidth())
	{
		*ballSpeed_X *= -1;
		printf("sudar\n");
	}
	
	bool collisionAC = CheckCollisionRecs(*boxA, *boxC);
	bool collisionBC = CheckCollisionRecs(*boxB, *boxC);

	if (collisionAC == true || collisionBC == true)
	{

		*ballSpeed_X *= -1;
		
	}

	boxC -> x += *ballSpeed_X;
	boxC -> y += *ballSpeed_Y;

	

}

void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C)
{
	ClearBackground(BLACK);

	BeginDrawing();

	DrawRectangleRec(box_A, WHITE);
	DrawRectangleRec(box_B, WHITE);
	DrawRectangleRec(box_C, WHITE);


	EndDrawing();
			

}