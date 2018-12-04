#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<limits.h>
using namespace std;

int test (int height,int width,unsigned char * img_data, int *points)
{
	int cnt = 0;
	vector<vector<unsigned int > > graph(height,vector<unsigned int>(width,0));
	vector<vector<int> > go(height,vector<int>(width,0));
	
	for(int i  =0;i<height;i++)
	{
		for(int j = 0;j<width;j++)
		{
			graph[i][j] = img_data[cnt];
			cnt++;
		}
	}
	queue<pair<int,int> > q;
	//here we using bfs to deal this problem
	int line =0;
	for(int i =0;i<height;i++)	
	{
		for(int j =0;j<width;j++)
		{
			if(graph[i][j] == 0)
				go[i][j] = 1;
			else if(go[i][j] == 0)
			{
				int xmin = INT_MAX;
				int ymin = INT_MAX;
				int xmax = INT_MIN;
				int ymax = INT_MIN;
				int area = 0;
				go[i][j] =1;
				q.push(pair<int,int>(i,j));
				while(!q.empty())
				{
					pair<int,int> point = q.front();
					q.pop();
					area++;
					int y = point.first;
					int x = point.second;
					//cout<<y<<","<<x<<endl;
					xmin = x<xmin?x:xmin;
					ymin = y<ymin?y:ymin;
					xmax = x>xmax?x:xmax;
					ymax = y>ymax?y:ymax;
					if(y-1>=0)
					{
						if(go[y-1][x] == 0 && graph[y-1][x] > 0)
						{
							go[y-1][x]=1; 
							q.push(pair<int,int>(y-1,x));
						}
					}
					if(y+1<height)
					{
						if(go[y+1][x] == 0 && graph[y+1][x] > 0)
						{
							go[y+1][x]=1; 
							q.push(pair<int,int>(y+1,x));
						}
					}
					if(x-1>=0)
					{
						if(go[y][x-1] == 0 && graph[y][x-1] > 0)
						{
							go[y][x-1]=1; 
							q.push(pair<int,int>(y,x-1));
						}
					}
					if(x+1<width)
					{
						if(go[y][x+1] == 0 && graph[y][x+1] > 0)
						{
							go[y][x+1]=1; 
							q.push(pair<int,int>(y,x+1));
						}
					}
				
				}
				if(area>10)
				{
					cout<<"get min rect here is : "<<xmin<<","<<ymin<<","<<xmax<<","<<ymax<<endl;
					points[line*5+0] = 0;
					points[line*5+1] = xmin;
					points[line*5+2] = ymin;
					points[line*5+3] = xmax;
					points[line*5+4] = ymax;
					line++;
				}

			}

		}
	}


	return line;
}
extern "C"
{
	int c_test(int height,int width,unsigned char * img,int * points)
	{
		return test(height,width,img,points);
	}
}
