/*
 * screenbuffer.h
 *
 * Created: 3/6/2017 8:51:59 AM
 *  Author: live
 */ 


#ifndef SCREEN_BUFFER_H_
#define SCREEN_BUFFER_H_

#include <string.h>
#include "Point.h"

namespace Screen {


	template<uint8_t WIDTH, uint8_t HEIGHT, typename DISPLAY>
	struct Buffer
	{
		using point = Point;
		
		using point_type     = Point;
		using point_type_ptr = Point*;
		
		using array_point_type     = ArrayPoint;
		using array_point_type_ptr = ArrayPoint*;
		
		static uint8_t const rows = (HEIGHT+7)/8;
		static uint8_t const columns = WIDTH;
		static uint16_t const size = columns*rows;
		
		uint8_t buffer[size];
		DISPLAY * const display;
		
		Buffer(DISPLAY *const display) : display(display) {
		}
		
		void init() {
			clear();
			update();
		}
		
		void update() {
			display->SetYAddress(0);
			display->SetXAddress(0);
			display->Write(buffer, size);
		}
		
		void update(Point point, uint8_t width, uint8_t height) {
			
			uint8_t row = (point.y/8 < 0 ? 0 : point.y/8);
			//uint8_t row_height = 2;
			uint8_t row_height = ((point.y+height+7)/8 > rows ? rows : (point.y+height+7)/8) - row;
			
			for (uint8_t column = point.x; column < point.x+width; ++column) {
				display->SetYAddress(row);
				display->SetXAddress(column);
				uint8_t* ptr = &buffer[column*rows+row];
				display->Write(ptr, row_height);
			}
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
		
		void set_data(const array_point_type& arr_point, const uint8_t& data) {
			*(&buffer[0] + (arr_point.column * rows) + arr_point.row) = data;
		}
		
		void set_data(const uint8_t& column, const uint8_t& row, const uint8_t& data) {
			*(&buffer[0] + (column * rows) + row) = data;
		}
		
		void draw_square(Point point, uint8_t width, uint8_t height) {
			if (!is_inside(point, width, height)) {
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
			
			// The squares goes out to the bottom, so we make it smaller
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
				uint8_t mask = ~(0x00) << (bottom_height + top_height);
				mask = mask >> top_height;
				uint8_t* ptr = &buffer[rows*point.x+row];
				
				for (auto x = point.x; x < point.x + width; ++x) {
					*ptr |= mask;
					ptr += rows;
				}
				height -= middle_height;
				point.y += middle_height;
			}
		}
		
		void set(uint8_t data ) {
			memset(buffer, data, size);
		}
		
		void clear() {
			set(0x00);
		}
		
		void set() {
			set(0xFF);
		}
		
		void set(Point point) {
			draw_square(point, 1, 1);
		}
		
		void clear(Point point) {
			clear_square(point, 1, 1);
		}
		
		void clear_square(Point point, uint8_t width, uint8_t height) {
			if (!is_inside(point, width, height)) {
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
			
			// The squares goes out to the bottom, so we make it smaller
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
				uint8_t mask = ~(0x00) << (bottom_height + top_height);
				mask = mask >> top_height;
				uint8_t* ptr = &buffer[rows*point.x+row];
				
				for (auto x = point.x; x < point.x + width; ++x) {
					*ptr &= ~mask;
					ptr += rows;
				}
				height -= middle_height;
				point.y += middle_height;
			}
		}
		
		void draw_border(Point point, uint8_t width, uint8_t height, uint8_t thickness) {
			draw_square(point, width, thickness);
			draw_square(point, thickness, height);
			draw_square(Point{point.x, point.y+height-thickness}, width, thickness);
			draw_square(Point{point.x+width-thickness, point.y}, thickness, height);
		}
		
		void draw_square_with_border(Point point, uint8_t width, uint8_t height, uint8_t thickness) {
			clear_square(point, width, height);
			draw_border(point, width, height, thickness);
		}
	};

}



#endif /* SCREEN_BUFFER_H_ */