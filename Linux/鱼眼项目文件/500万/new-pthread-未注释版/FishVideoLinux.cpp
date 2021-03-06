#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <pthread.h>
#include <fstream>

#include "FishEyeCorrect.h"
#include  "opencv2/core/core.hpp"        // Basic OpenCV structures (cv::Mat, Scalar)
#include  "opencv2/imgproc/imgproc.hpp"  // Gaussian Blur
#include  "opencv2/highgui/highgui.hpp"// OpenCV window I/O

using namespace std;
using namespace cv;

int frameNumber = 0;
void  *thrd_func1(void *argv);
void  *thrd_func2(void *argv);
void str2num(string& str,vector<int>& rint);
int substr2num(string& str);
CFishEyeCorrect fishCorrect;
Mat frame;	
VideoCapture cap;
double jt;
int main(int argc, char *argv[])
{
	if(argc <2)
        {
	   return -1;
         }
	cap.open(argv[1]);
	frameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
	//cout<<"frameNumber "<<frameNumber<<endl;
	if(!cap.isOpened())
	{
		cout<<"��ȡ��Ƶʧ�ܣ�"<<endl;
		return 0;
	}
	int flag = 0;
	
	char  buf[100];
	ifstream in("test.txt");
	int totalnum = 0;
	pthread_t tid1,tid2;
     	void *tret;
	while (in.getline(buf,100))
	{
		string str = buf;
		vector<int>   myint;
		str2num(str,myint);
		//cout<<myint.size()<<endl;
		if(0==totalnum)
		{
			fishCorrect.w = myint[0];
			fishCorrect.h = myint[1];
		//cout<<myint[0]<<" "<<myint[1]<<endl; 
		}
		else if(1==totalnum)
		{
			fishCorrect.phi0 = myint[0];
			fishCorrect.sita0 = myint[1];
			fishCorrect.gama0 = myint[2];
		}
		else if(2==totalnum)
		{
			fishCorrect.phi1 = myint[0];
			fishCorrect.sita1 = myint[1];
			fishCorrect.gama1 = myint[2];
		}
		else if(3==totalnum)
		{
			fishCorrect.phi2 = myint[0];
			fishCorrect.sita2 = myint[1];
			fishCorrect.gama2 = myint[2];
		}
		else if(4==totalnum)
		{
			fishCorrect.phi3 = myint[0];
			fishCorrect.sita3 = myint[1];
			fishCorrect.gama3 = myint[2];
		}	
		/*for (int i=0;i<myint.size();i++)
		{
			cout<<myint[i]<<endl;
		}*/
		totalnum++;
	}
	namedWindow("Video0",0);
	namedWindow("Video1",0);
	//namedWindow("Video2",0);
	cout<<"playing...."<<endl;
	for(int i = 0;i < frameNumber;++i)
	{	   		
		
		if(i <= 31)
		{
			cap >> frame;			
		}
		if(i >30)
		{
		    //clock_t t1 = clock();
		    if (flag == 0)
		    {
			fishCorrect.GetArea(frame);
			flag =1;
		    }
		   if (i>31)
		    {
			clock_t t11 = clock();
		      if (pthread_create(&tid2,NULL,thrd_func2,NULL)!=0)
			 {
         		    printf("Create thread 2 error!\n");
         		    exit(1);
     			 }
		     if (pthread_join(tid1,&tret)!=0)
			{
		           printf("Join thread 1 error!\n");
		           exit(1);
		        }
		     clock_t end = clock();
		    // cout<<"fix time:"<< (end-t11)/1000.0<<endl;
		     imshow("Video0",fishCorrect.orgImg);
		     imshow("Video1",fishCorrect.dstImg);
          	     //imshow("Video2",fishCorrect.myTest);
		     clock_t t3 = clock();
			double tem = (t3 - end)/1000.0;
		    cout << "show is:"<<tem<<endl;
		    if (pthread_join(tid2,&tret)!=0)
			{
		           printf("Join thread 2 error!\n");
		       	   exit(1);
		        }
		    clock_t t2 = clock();
		    cout <<"fix1 time:"<<(t2-t11)/1000.0-tem-jt<<endl;
		    waitKey(1);				
		   }
	  	if (!frame.data)
			{
			   break;
			}
		  fishCorrect.orgImg  = frame(fishCorrect.correctArea);
		 // fishCorrect.myTest = fishCorrect.orgImg.clone();
		/*if(i==100)
		{
			imwrite("./fftest.jpg",fishCorrect.myTest);
		}*/
		 //imwrite("./11.jpg",fishCorrect.orgImg);
		  if (i ==31)
		  {
		     fishCorrect.ParamFix();
		     fishCorrect.CalculateParam(fishCorrect.orgImg.cols,fishCorrect.orgImg.rows);
		     fishCorrect.FishImgIndex(fishCorrect.orgImg);
		  }
		
     		 if (pthread_create(&tid1,NULL,thrd_func1,NULL)!=0) 
		  {
        	     printf("Create thread 1 error!\n");
                     exit(1);
                  }
	    }
	}
	      cout<<"play over"<<endl;
		 if (pthread_join(tid1,&tret)!=0)
			{
			   printf("Join thread 1 error!\n");
			   exit(1);
			}
	      return 0;
}

void  *thrd_func1(void *argv)
{
    fishCorrect.ImageCorrect();
    pthread_exit(NULL); 
}
	
void  *thrd_func2(void *argv)
{
	clock_t t1 =clock();
	cap >> frame;
	clock_t t2 = clock();
	jt = (t2-t1)/1000.0;
	cout<<"jie ma :"<<jt<<endl;
	pthread_exit(NULL); 
	
}
void str2num(string& str,vector<int>& rint)
{
	string strSep = "/";
	int size_pos = 0;
	string strresult;
	int size_prev_pos = 0;
	int itemp = 0;

	while((size_pos=str.find_first_of(strSep,size_pos))!=string::npos)
	{
		strresult = str.substr(size_prev_pos,size_pos - size_prev_pos);
		itemp = substr2num(strresult);
		rint.push_back(itemp);
		size_prev_pos=++size_pos;
	}
	if (size_prev_pos!=str.size())
	{
		strresult = str.substr(size_prev_pos,size_pos - size_prev_pos);
		itemp = substr2num(strresult);
		rint.push_back(itemp);
	}
}
int substr2num(string& str)
{
	int strlength = str.size();
	stringstream os;
	string strSep = "=";
	int size_pos=0;
	string tem;
	int result = 0;
	size_pos = str.find_first_of(strSep,size_pos);
	tem = str.substr(size_pos+1,strlength - size_pos);
	os<<tem;
	os>>result;
	return result;
}

