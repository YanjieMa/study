#include <iostream>

using namespace std;






/*
//test 9
class BasicException{
public:
	char *where(){
		return "BasicException...";
	}
};
class FileSysException:public BasicException{
public:
	char *where(){
		return "FileSysException...";
	}
};
class FileNotFound:public FileSysException{
public:
	char *where(){
		return "FileNotFound...";
	}
};
class DiskNotFound:public FileSysException{
public:
	char *where(){
		return "DiskNotFound...";
	}
};


void test9()
{
	try{
		throw FileSysException();
	}
	catch(FileNotFound p) { cout << p.where() << endl;} //子类不能捕获父类抛出的异常
	catch(DiskNotFound p) { cout << p.where() << endl;}
	catch(BasicException p) { cout << p.where() << endl;}//父类可以捕获子类和本身抛出的异常
	//catch(FileSysException p) { cout << p.where() << endl;}
}
*/

//test 9-2
class BasicException{
public:
	virtual char *where(){
		return "BasicException...";
	}
};
class FileSysException:public BasicException{
public:
	virtual char *where(){
		return "FileSysException...";
	}
};
class FileNotFound:public FileSysException{
public:
	virtual char *where(){
		return "FileNotFound...";
	}
};
class DiskNotFound:public FileSysException{
public:
	virtual char *where(){
		return "DiskNotFound...";
	}
};

void test9_2(){
	try{
		DiskNotFound err;
		throw &err;
	}
	catch(BasicException *p){// 可以通过虚函数 catch 基类异常 ，获取所有继承类的异常
		cout << p->where() << endl;
	}


}


int main()
{
	test9_2();
	return 0;
}
