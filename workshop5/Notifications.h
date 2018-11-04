#ifndef w5_NOTIFICATIONS_H_
#define w5_NOTIFICATIONS_H_
#include <iostream>
#include "Message.h"

namespace w5 {
	class Notifications {
		Message* messageTable = nullptr;
		size_t count = 0;
		const size_t MAX_MESSAGE_COUNT = 10;
	public:
		Notifications();// default constructor - empty
		Notifications(const Notifications& rhs);//- copy constructor
		Notifications& operator=(const Notifications& rhs);//-copy assignment operator
		Notifications(Notifications&& rhs);//- move constructor
		Notifications&& operator=(Notifications&& rhs);//-move assignment operator
		~Notifications();//- destructor
		void operator+=(const Message& msg); //- adds msg to the set
		void display(std::ostream& os) const; //- inserts the Message objects to the os output stream
	};
}
#endif
