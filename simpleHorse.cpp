#include "iostream"
using namespace std;

#define row 5
#define colum 6
typedef struct //存储方向的结构体 
{
	int x;  //方向x值
	int y;  //方向y值
}array;

array direction[8]; //声明一个数组用来存储8个方向
bool flag[row * colum];  //设置一个是否已经入队的标记
int dir[row * colum];      //存储马行走的路径
bool finish = false;         //结束标记

void initial()
{
	direction[0].x = 2; direction[0].y = 1;
	direction[1].x = 1; direction[1].y = 2;
	direction[2].x = -1; direction[2].y = 2;
	direction[3].x = -2; direction[3].y = 1;
	direction[4].x = -2; direction[4].y = -1;
	direction[5].x = -1; direction[5].y = -2;
	direction[6].x = 1; direction[6].y = -2;
	direction[7].x = 2; direction[7].y = -1;
}

int change(array now)   //坐标转换函数
{ 
	return (now.x * colum + now.y + 1);    //将二维坐标转换为一维坐标
}

void search(array now, int k)  //进行回溯
{
	array next;
	if(finish == true)
		return;
	if(k == row * colum)  //k已经到头
	{
		finish = true;
		for (int i = 0; i < row * colum - 1; i++)
			cout<<dir[i]<<" ";
		cout<<dir[row * colum - 1]<<endl;
		
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			next.x = now.x + direction[i].x;
			next.y = now.y + direction[i].y;
			int n = change(next);  //计算出一维坐标
			if(next.x >= 0 && next.x < row && next.y >=0 && next.y < colum && !flag[n])
			{
				flag[n] = true;      //将next标记为走过
				dir[k] = n;         //记录下马行走的路径
				k++;
				search(next,k);
				flag[n] = false;  //如果从上一层回溯出来，则将上一个n置false，也将k--
				k--;			
			}
		}

	}
	

}

int main()
{
	initial(); //方向初始化
	array start; //声明开始节点
	int n;//输入起点
	cin>>n;
	while (n != -1)
	{
		start.x = (n - 1) / colum;  //坐标转换
		start.y = (n -1) % colum;
		for (int i = 0; i < row*colum; i++)
		{
			flag[i] = false;              //将flag标记初始化为false
		}
		finish = false;      //结束标记为false
		dir[0] = n;       //路径第一个数字为起点
 		flag[n] = true;
		search(start,1);
		cin>>n;

	}
	
	return 0;
}