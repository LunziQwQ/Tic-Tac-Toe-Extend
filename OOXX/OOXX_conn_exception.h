#include <string>
#include <exception>

using std::string;
using std::exception;

//connection exception
class ConnException : public exception
{
public:
	int exc;
	string msg;
	DWORD err;

public:
	ConnException(int e,const string str,DWORD er){
		exc=e;
		msg=str;
		err=er;
	}

	~ConnException(){
	}
};