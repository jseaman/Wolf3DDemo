#pragma once
#include <stdint.h>

class Graphics
{
	public:
		static Graphics* get();

		void setDrawingColor(int r, int g, int b, int a);
		void setDrawingColor(uint32_t color);
		void drawRectangle(int x, int y, int w, int h);
		void drawFilledRectangle(int x, int y, int w, int h);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawPixel(int x, int y);
		void clearScreen();
		void render();


		const int getScreenWidth();
		const int getScreenHeight();

		~Graphics();		

	private:
		Graphics();
		void initializeSDL();
		
		int fullScreenWidth;
		int fullScreenHeight;
};

