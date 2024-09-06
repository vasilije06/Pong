#include <raylib.h>
#include <stdio.h>

void ScreenDraw(struct Rectangle box_A);

int main()
{

	const int screenH = 1200;
	const int screenW = 1000;

	InitWindow(screenH, screenW, "test igra");

	Rectangle boxA = { 100, 100, 10, 50 };
	printf("%d", GetScreenWidth());

	while (!WindowShouldClose())
	{
		
			ScreenDraw(boxA);
		
	}

	CloseWindow();
	return 0;

}

void ScreenDraw(struct Rectangle box_A)
{
	ClearBackground(BLACK);

	BeginDrawing();

	DrawRectangleRec(box_A, WHITE);

	EndDrawing();
			

}