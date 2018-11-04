
#include <iostream>
#include <string>
#include <fstream>
#include "Message.h"
#include "Notifications.h"


namespace w5 {

		Message::Message() {
			//need a default constructor 
		}
		Message::Message(std::ifstream& in, char recDelin) {
			std::string line;
			std::getline(in, line, recDelin);
			auto cr = line.find('\r');
			if (cr != std::string::npos)
				line.erase(cr);
			//cout << "-->" << line << "<--\n"; 
			size_t index = 0;
			//read name
			while (index < line.size() && line[index] != ' ') {
				name += line[index];
				index++;
			}
			//cout << "name[" << name << "]\n";
			index++; //skip ' ' (line[index] is ' ')
			if (index < line.size() && line[index] == '@') {
				index++; // skip '@'
				while (index < line.size() && line[index] != ' ') {
					reply += line[index];
					index++;
				}
				//cout << "reply[" << reply << "]\n";
				index++;
			}
			while (index < line.size()) {
				tweet += line[index];
				index++;
			}
			//cout << "tweet[" << tweet << "]\n";
			//display(cout);

		}//- constructor retrieves a record from the in file object, parses the record(as described above) 
		 //and stores its components in the Message object.c is the character that delimits each record
		bool Message::empty() const {
			return tweet.empty();
		}//- returns true if the object is in a safe empty state
		void Message::display(std::ostream& os) const {
			os << "Message\n";
			os << "User  : " << name << "\n";
			if (!reply.empty())
				os << "Reply : " << reply << "\n";
			os << "Tweet : " << tweet << "\n\n";
		}//- displays the Message objects within the container
	
}
