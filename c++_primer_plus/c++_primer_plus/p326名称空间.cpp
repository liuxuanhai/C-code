#include <iostream>
// 名称空间可以是全局的, 也可以位于另一个名称空间中, 但是不能位于代码块中, 因此, 在默认情况下, 在名称空间中生命的名称连接为外部的(除非他引用了常量);
namespace Jack {
	double pail;            // variable declaration
	void fetch();		   // function prototype
	int pal = 1;				   // variable declaration
	struct Well{int in;};	   // structure declaration
}
namespace Jill {
	double bucket(double){return 0.0;}  // function definition
	double fetch;						 // variable declaration
	int pal;							 // variable declaration
	struct Hill {int in;};				 // structure declaration
	int pp = 222;
}

// 原来的Jack名称空间为fetch()函数提供了原型, 可以在该文件后面(或是另外一个文件中)再次使用Jack名称空间来提供该函数的代码
namespace Jack {
	void fetch()
	{
		int in;
	}
}