#include <iostream>
#include "Message.h"
#include "Notifications.h"
namespace w5 {

		Notifications::Notifications() {
			messageTable = new Message[MAX_MESSAGE_COUNT];
		}// default constructor - empty

		Notifications::Notifications(const Notifications& rhs) {
			//cout << "copy constructor\n";
			count = rhs.count;
			messageTable = new Message[MAX_MESSAGE_COUNT];
			for (size_t i = 0; i < count; i++) {
				messageTable[i] = rhs.messageTable[i];
			}
		} //- copy constructor

		Notifications& Notifications::operator=(const Notifications& rhs) {
			//cout << "copy assignment operator\n";
			if (this != &rhs) {
				delete[] messageTable;
				count = 0;
				count = rhs.count;
				messageTable = new Message[MAX_MESSAGE_COUNT];
				for (size_t i = 0; i < count; i++) {
					messageTable[i] = rhs.messageTable[i];
				}

			}
			return *this;
		}//-copy assignment operator

		Notifications::Notifications(Notifications&& rhs) {
			//cout << "move constructor\n";
			//steal brain
			count = rhs.count;
			messageTable = rhs.messageTable;
			//rhs become zombie
			rhs.count = 0;
			rhs.messageTable = nullptr;
		}//- move constructor

		Notifications&& Notifications::operator=(Notifications&& rhs) {
			//cout << "move assignment operator\n";
			if (this != &rhs) {
				delete[] messageTable;
				count = 0;
				count = rhs.count;
				messageTable = rhs.messageTable;
				//rhs become zombie
				rhs.count = 0;
				rhs.messageTable = nullptr;

			}
			return std::move(*this);
		}//-move assignment operator

		Notifications::~Notifications() {
			delete[] messageTable;
			//cout << "destructor\n";
		} //- destructor

		void Notifications::operator+=(const Message& msg) {
			if (count < MAX_MESSAGE_COUNT) {
				messageTable[count] = msg;
				count++;
			}
		} //- adds msg to the set

		void Notifications::display(std::ostream& os) const {
			for (size_t i = 0; i < count; i++) {
				messageTable[i].display(os);
			}
		} //- inserts the Message objects to the os output stream

}
