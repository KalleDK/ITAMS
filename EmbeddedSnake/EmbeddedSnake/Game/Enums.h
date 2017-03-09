/*
 * Enums.h
 *
 * Created: 3/8/2017 8:13:33 PM
 *  Author: live
 */ 


#ifndef GAME_ENUMS_H_
#define GAME_ENUMS_H_


namespace Game {
	
	enum Direction : uint8_t
	{
		None  = 0,
		Up    = 1,
		Down  = 2,
		Left  = 3,
		Right = 4
	};
	
	enum class border_value : uint8_t
	{
		North     = 0,
		South     = 1,
		West      = 2,
		East      = 3,
		NorthEast = 4,
		NorthWest = 5,
		SouthEast = 6,
		SouthWest = 7
	};
	
	enum class type_id : uint8_t
	{
		None		= 0,
		Snake		= 1,
		Border		= 2,
		Fruit		= 3
		
	};

	enum class game_state : uint8_t
	{
		Idle     = 0,
		Playing  = 1,
		GameOver = 2,
		Win      = 3
	};
	
	enum class program_state : uint8_t
	{
		Idle     = 0,
		Playing  = 1,
		GameOver = 2,
		Win      = 3
	};
	
	enum class player_state : uint8_t
	{
		Playing     = 0,
		Lost        = 1,
		Won         = 2
	};

	enum class fruit_value : uint8_t
	{
		Banana		= 1,
		Apple    	= 2,
	};

	using snake_value = Direction;
}


#endif /* GAME_ENUMS_H_ */