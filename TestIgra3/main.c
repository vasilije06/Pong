#include <raylib.h>
#include <stdio.h>

void ScreenDraw(struct Rectangle box_A, struct Rectangle box_B, struct Rectangle box_C);
//void PlayAudio();


int main()
{

	const int screenW = 1200;
	const int screenH = 1000;
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
			boxA.y = 0;

		if (boxA.y + boxA.height >= GetScreenHeight())
			boxA.y = GetScreenHeight() - boxA.height;



		printf("X:%.lf Y:%.lf\n", boxA.x, boxA.y);
		ScreenDraw(boxA, boxB, boxC);
		
	}

	CloseWindow();

	return 0;

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