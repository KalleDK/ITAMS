/*
* nescontroller.h
*
* Created: 3/3/2017 2:35:11 PM
*  Author: live
*/


#ifndef NES_CONTROLLER_H_
#define NES_CONTROLLER_H_

#include "Enums.h"

namespace NES {
	

	template<typename TC4021Driver>
	struct Controller : TC4021Driver {
		
		using base = TC4021Driver;
		
		bool a;
		bool b;
		bool start;
		bool select;
		bool up;
		bool down;
		bool right;
		bool left;
		
		void update() {
			uint8_t data = base::read();
			a      = get(data, ButtonOrder::A);
			b      = get(data, ButtonOrder::B);
			select = get(data, ButtonOrder::Select);
			start  = get(data, ButtonOrder::Start);
			up     = get(data, ButtonOrder::Up);
			down   = get(data, ButtonOrder::Down);
			left   = get(data, ButtonOrder::Left);
			right  = get(data, ButtonOrder::Right);
		}
		
		inline bool get(const uint8_t& data, ButtonOrder button) {
			return !!(data & (1 << button));
		}
	};
}
#endif /* NES_CONTROLLER_H_ */