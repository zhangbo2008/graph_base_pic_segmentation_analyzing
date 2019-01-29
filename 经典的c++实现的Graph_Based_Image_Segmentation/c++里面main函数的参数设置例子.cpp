#include <iostream>
using namespace std;
int main(int count, char* input_parameters[])
{	cout<<count<<"......."<<endl;
    for(int i=0;i<count;i++)
        cout<<input_parameters[i]<<"......."<<i<<endl;
    return 0;
/*
c++  里面参数的传递的总结.
第一个是count,表示命令行中写入的参数个数+1
 input_parameters,表示第一个是文件本身路径,第二个到最后一个表示命令行输入的参数 

*/
}
