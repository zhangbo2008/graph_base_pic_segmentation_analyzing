#include <iostream>
using namespace std;



class Test{
public:
    int a;
    Test(){             /*��Ĺ��췽�������ö��������� */
        a = 1;

    }    Test2(){
        a = 1;
    
}};

int main()
{
    Test* t1 = new Test();
    t1->a = 10;   
    t1->Test2();
	cout <<t1->a<<endl;
    Test* t2 = new Test();
    t2->a = 5;
    int a =1;
    cout << "324""" << sizeof(t1) << endl;
    cout << "342" << sizeof(a)<< endl;
    cout << "&t1:" << t1 << " a = " << t1->a << endl;
    cout << "&t2:" << t2 <<  " a = " << t2->a <<endl;
    
    cout << "------------------------------" << endl;
    t2 = t1;
    cout << "&t1:" << t1 << " a = " << t1->a << endl;
    cout << "&t2:" << t2 <<  " a = " << t2->a <<endl;
    
    cout << "------------------------------" << endl;
    
    t1->a = 111;
    t2->a = 222;  /* ��Ϊ��ַ����,��ͬ�±�*/ 
    cout << "&t1:" << t1 << " a = " << t1->a << endl;
    cout << "&t2:" << t2 <<  " a = " << t2->a <<endl;
    
    
    
 	Test *a1=new Test[10];
    Test *a2=&a1[5]; 
    cout<<"1212121"<<a1<<endl;	 
    cout<<"a2........."<<a2<<endl;	 
    cout<<"a1[5]........."<<&a1[5]<<endl;	 
    cout<<"12121212222"<<a2+1<<endl;	 
    cout<<"12121212222"<<a2+2<<endl;	 
    cout<<"12121212222"<<a2+3<<endl;	 
    
    
    
    
    
    
    return 0;
}
