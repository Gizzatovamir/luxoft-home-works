#include <iostream>
#include <cmath>
#include <array>
#include <set>
#include <vector>



class MyClass{
	public:
	int Digit;
	std::string DigitName;
	int flag = 0;
	std::array<std::string,10> DigitNames = {"zero","one","two","three","four","five","six","seven","eight","nine"};
	MyClass(int i){
		if((i >= 0) && (i < 10)){
			Digit = i;
			DigitName = DigitNames[i];
		}
		else{
			Digit = i;
			DigitName = "error";
		}
	};
	MyClass(MyClass&& other) noexcept{
		Digit = other.Digit;
		DigitName = other.DigitName;
	};
	MyClass() = default;
	MyClass(const MyClass& other){
		Digit = other.Digit;
		DigitName = other.DigitName;
	};

	MyClass& operator=(const MyClass& other){
		if (this == &other)
			return *this;
		Digit = other.Digit;
                DigitName = other.DigitName;
		flag++;
		return *this;
	};
	MyClass& operator=(const MyClass&& other){
                if (this == &other)
                        return *this;
		Digit = other.Digit;
                DigitName = other.DigitName;
                return *this;
        };


};


MyClass createMyClass(int i){
	return MyClass(i);
}

int main(){
	MyClass mc = createMyClass(5);
	MyClass mc1;
	mc1 = createMyClass(4);
	MyClass mc2;
	mc2 = mc1;
	std::cout << mc.Digit << " name - " << mc.DigitName <<  " iter - "<< mc.flag << std::endl;
	std::cout << mc1.Digit << " name - " << mc1.DigitName <<  " iter - "<< mc1.flag << std::endl;
	std::cout << mc2.Digit << " name - " << mc2.DigitName <<  " iter - "<< mc2.flag << std::endl;
        return 0;

}
