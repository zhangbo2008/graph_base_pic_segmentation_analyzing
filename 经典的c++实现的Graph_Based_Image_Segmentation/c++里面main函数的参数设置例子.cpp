#include <iostream>
using namespace std;
int main(int count, char* input_parameters[])
{	cout<<count<<"......."<<endl;
    for(int i=0;i<count;i++)
        cout<<input_parameters[i]<<"......."<<i<<endl;
    return 0;
/*
c++  ��������Ĵ��ݵ��ܽ�.
��һ����count,��ʾ��������д��Ĳ�������+1
 input_parameters,��ʾ��һ�����ļ�����·��,�ڶ��������һ����ʾ����������Ĳ��� 

*/
}
