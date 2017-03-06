/*
 * screenbuffer.h
 *
 * Created: 3/6/2017 8:51:59 AM
 *  Author: live
 */ 


#ifndef SCREENBUFFER_H_
#define SCREENBUFFER_H_

struct Point {
	int8_t x;
	int8_t y;
};

template<uint8_t COLUMNS, uint8_t ROWS, typename DISPLAY>
struct ScreenBuffer 
{
	static uint8_t const rows = ROWS;
	static uint8_t const columns = COLUMNS;
	static uint16_t const size = columns*rows;
	
	uint8_t buffer[size];
	DISPLAY * const display;
	
	ScreenBuffer(DISPLAY *const display) : display(display) {}
	
	void update() {
		display->Write(buffer, size);
	}
	
	bool is_inside (const Point& point, uint8_t width, uint8_t height) {
		
		// Is outside to the right
		if (point.x > columns) {
			return false;
		}
		
		// Is outside to the down
		if (point.y > columns * 8) {
			return false;
		}
		
		// Is outside to the left
		if (point.x + width < 0) {
			return false;
		}
		
		// Is outside to the up
		if (point.y + height < 0) {
			return false;
		}
		
		return true;
	}
	
	void draw_square(Point point, uint8_t width, uint8_t height) {
		if (!is_inside()) {
			return;
		}
		
		// Moving x into the screen an makes the width smaller
		if (point.x < 0) {
			width += point.x;
			point.x = 0;
		}
		
		// Moving y into the screen and makes height smaller
		if (point.y < 0) {
			height += point.y;
			point.y = 0;
		}
		
		// The squares goes out to the botton, so we make it smaller
		if ((point.y + height) > (rows * 8)) {
			height = (rows * 8) - point.y;
		}
		
		// The box goes out to the right, so we make it smaller
		if ((point.x + width) > columns) {
			width = columns - point.x;
		}
		
		
		while (height > 0) {
			uint8_t bottom_height = point.y % 8;
			uint8_t middle_height = (bottom_height + height > 7? 8-bottom_height: height);
			uint8_t top_height = (8 - middle_height - bottom_height);
			
			uint8_t row = point.y / 8;
			uint8_t mask = ~(0x00) << (point.y % 8);
			if ((point.y % 8 + height) < 8) {
				uint8_t high_mask =  ~(0x00) << (point.y % 8 + height);
				mask &= ~high_mask;
			}
			
			for (auto x = point.x; x < point.x + width; ++x) {
			
			
				
			}
			height -= middle_height;
			point.y += middle_height;
		}
	}
};



#endif /* SCREENBUFFER_H_ */