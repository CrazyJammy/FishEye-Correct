/*
*Copyright(c)2014,Ƚ����Ϣ�������޹�˾
*All rights reserved.
*
*�ļ����ƣ�Trace.h
*�ļ���ʶ�����ٳ������е���־��ͷ�ļ�
*ժ    Ҫ��һ���õĴ���Ӧ�þ��и��ٹ��ܡ�
*
*��ǰ�汾��1.0
*��    �ߣ�������
*������ڣ�2014.8.15
*/


#ifndef __CTRACE_H_
#define __CTRACE_H_



#include <stdio.h>//standard input & output
#include <Windows.h>
#include <iostream>


/*��ע��
       string ��string.h����ȫ��ͬ�������ļ���string��using namespace stdһ����
	   string.h��C�����ͷ�ļ������忴�洢���ĵ�*/
#include <string> 
using namespace std; //������ͷ�ļ���Ϊ����string���ͷ�ļ�


//����дlog�ĵ�ַ���Լ����سɹ�����һЩ���
#define FILE_PATH "TraceLog.txt"

//int WriteToLog(char *str);
//���ں���WriteToLog(char *str)������һЩ���ؽ��
//{дlog�ɹ�,���ļ�ʧ��,дlogʧ��}
enum{WRITE_SUCCESS,OPENFILE_FAILED,WRITE_FAILED};


//���ʱ���ǵ������
#include <ctime>
//��������{����+ʱ�䡢���ڡ�ʱ��}
enum{CTRACE_DATA_TIME,CTRACE_DATA,CTRACE_TIME};



//////////////////////////////////////////////////////////////////////////
//�����ƣ�
//    CTrace
//���Ա��
//    static bool traceIsActive-һ�������Ƿ񴥷����������ľ�̬��Ա
//    string *theFunctionName-�洢�����ٺ������Ƶ�ָ��                          
//��Ա������
//    void debug (const string&msg)-��������Ϣ����������ϵ�һ��������д
//                                  txt�ı�����Ҫ�õ��ú�����
//    int WriteToLog(char *str)-���ı�д��txt�����У�strΪ��Ӧ�ı�
//    int getSystemTime(char *out,int fmt)-��ȡϵͳʱ��ĺ���
//˵����
//    ��������г�Ա������������������ʽ��������ҪĿ�����Կռ任ȡʱ��
//    ������С���Բ��ֶ�������������ʱ���Ӱ�졣���ǣ���Ҫע�⣺��Ҫ��
//    �ü�¼����Ƕ�����޵�ѭ���ȵ�while��forѭ������ȥ����Ϊ������Ӱ��
//    ���������Ч�ʡ���Ȼ�Ѿ����й��Ż���
//�÷���
//    ��һ��������Ҫ�����FILE_PATH��·����
//    �ڶ�����Ҫע��ʹbool CMyTrace::traceIsActive��ֵΪtrue
//    ������������ʹ�ù����в�ȡ
//                              #ifdef _CTRACE
//                              CMyTrace t("myFunction");
//                              t.WriteToLog("��־��Ϣ")
//                              #endif
//            �ı��뷽ʽ
//////////////////////////////////////////////////////////////////////////

class CMyTrace
{
public:
	CMyTrace(const char *name) : theFunctionName(0)
	{
		if (traceIsActive)//�������Ĵ���
		{
			//cout << "Enter function" << name << endl;
			theFunctionName = new string(name);
		}
	};
	~CMyTrace();
	void debug (const string &msg);
	int WriteToLog(char *str);
	
	static bool traceIsActive;
protected:
	int getSystemTime(char *out, int fmt);

private:
	string *theFunctionName;
	
};

//////////////////////////////////////////////////////////////////////////
//�������ƣ�
//    ~CTrace()
//
//˵����
//    �ڴ�����������delete theFunctionName�Ŀռ䡣
//////////////////////////////////////////////////////////////////////////
inline CMyTrace::~CTrace()
{
	//
	if (traceIsActive)
	{
		//cout << "Exit function" << *theFunctionName<< endl;
		delete theFunctionName;
	}
}


//////////////////////////////////////////////////////////////////////////
//�������ƣ�
//    debug(const string &msg)
//
//����������
//    const string &msg-��dos���漴��Ҫ�������Ϣ
//����ֵ��
//    �� 
//˵����
//    ����dosϵͳ�µ���win32���̵�ʱ�򣬾Ͳ�����txt���������Ϣ�ˡ�����
//    ʹ��coutֱ�������Ϣ�����ʱ�����ʹ�øú�����
//////////////////////////////////////////////////////////////////////////
inline void CMyTrace::debug(const string &msg)
{
	if (traceIsActive)
	{
		//cout << msg << endl;
	}
}


//////////////////////////////////////////////////////////////////////////
//�������ƣ�
//    getSystemTime(char *out, int fmt=ZH_CTRACE_TIME)
//
//����������
//    char *out-��ʱ���Ѿ���ȡ�󣬱���ı��������ŵĵط�
//    int fmt-��Ҫ����ĸ�ʽ,Ĭ��ָ��ΪCTRACE_TIME�������ʽ
//            CTRACE_DATA_TIME ����-��-�� ʱ-��-��ĸ�ʽ
//            CTRACE_DATA ����-��-�յĸ�ʽ
//            CTRACE_TIME ��ʱ-��-��ĸ�ʽ
//            
//     
//����ֵ��
//    -1���ı�����Ϊ�գ���ȡʧ��
//    0 :��ȡ�ɹ�
//˵����
//    ��ȡ�ó�������ʱ��ʵʱʱ�䡣
//////////////////////////////////////////////////////////////////////////

inline int CMyTrace::getSystemTime(char *out, int fmt=CTRACE_TIME)
{
	//
	if (!traceIsActive)
	{
		return -1;
	}

	//
	if (NULL == out)
	{
		return -1;
	}

	time_t t;
	struct tm *tp;
	t = time(NULL);//������ctimeͷ�ļ� time�����᲻ʶ��

	tp = localtime(&t);
	if (CTRACE_DATA_TIME == fmt)
	{
		sprintf_s(out,25,"%2.2d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
			tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,
			tp->tm_hour,tp->tm_min,tp->tm_sec);
	} 
	else if (CTRACE_DATA == fmt)
	{
		sprintf_s(out,25,"%2.2d-%2.2d-%2.2d ",
			tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);
	}
	else if (CTRACE_TIME == fmt)
	{
		sprintf_s(out,25,"%2.2d:%2.2d:%2.2d",
			tp->tm_hour,tp->tm_min,tp->tm_sec);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//�������ƣ�
//    WriteToLog(char *str)
//
//����������
//    char *strt-��txt�м���Ҫд�����Ϣ     
//����ֵ��
//    int��
//       {дlog�ɹ�,���ļ�ʧ��,дlogʧ��}
//       enum{WRITE_SUCCESS,OPENFILE_FAILED,WRITE_FAILED};
//˵����
//    ��txt��д��Ϣ�Ľ����
//////////////////////////////////////////////////////////////////////////
inline int CMyTrace::WriteToLog(char *str)
{
	if (!traceIsActive)
	{
		return -1;
	}

	//
	FILE* pfile;
	if(NULL != fopen_s(&pfile,FILE_PATH,"a+"))
	{
		return OPENFILE_FAILED;
	};

	const char *pchar_theFunctionName=theFunctionName->c_str();

	char pchar_theTime[25];
	getSystemTime(pchar_theTime,CTRACE_DATA_TIME);

	if (NULL == fprintf_s(pfile,"%s%s%s%s%s%s%s%s\n\n",
		"The Tested Function ","\"",pchar_theFunctionName,"\""," : ",str,
		"------",pchar_theTime))
	{
		return WRITE_FAILED;
	};

	fclose(pfile);
	return WRITE_SUCCESS;

}
#endif

