#ifndef w5_MESSAGE_H_
#define w5_MESSAGE_H_
#include <iostream>
#include <string>

namespace w5 {
	class Message {
		std::string name, reply, tweet;
	public:
		Message();
		Message(std::ifstream& in, char recDelin);//- constructor retrieves a record from the in file object, parses the record(as described above) 
		//and stores its components in the Message object.c is the character that delimits each record
		bool empty() const;//- returns true if the object is in a safe empty state
		void display(std::ostream& os) const;//- displays the Message objects within the container
	};
}
#endif