//
//  EventManager.h
//  EventManager
//
//  Created by Tiny Oh 2018.1.14
//  Copyright (c) 2018 White Sky. All rights reserved.
//

#include "ThreadBase.h"
using namespace TO;
using namespace std;

TOThreadBase::TOThreadBase():m_dormant(false),m_status(false),m_threadResponseInterval(DEFAULT_RESPONSE_INTERVAL)
{
	m_calssName = typeid(*this).name();
}

TOThreadBase::~TOThreadBase()
{
	if(m_status)
	{
		stopThread();
	}
}

bool TOThreadBase::startThread()
{
	if(m_status)
	{
		cerr << "already have one thread runing" << endl;
		return false;
	}
	m_status = true;
	int retT = pthread_create(&m_threadID, NULL, TOThreadBase::threadMain, this);
    if (retT != 0)
    {
        cerr << "[TOThreadBase::startThread] start pthread_create error: error_code=" << retT << endl;
        return false;
    }
    return true;
}

bool TOThreadBase::dormantThread()
{
	m_dormant = !m_dormant;
	return m_dormant;
}

bool TOThreadBase::stopThread()
{
	if(m_status)
	{
		m_status = false;
		void* returnValue;
		pthread_join(pthread_self(),&returnValue);
		return true;
	}else
	{
		cerr << "none thread runing" << endl;
		return false;
	}
}

void TOThreadBase::run()
{
	cout << "no implement to run , run the base string output" << endl;
}

void* TOThreadBase::threadMain(void* args)
{
	pthread_detach(pthread_self());
	TOThreadBase * pThread = static_cast<TOThreadBase *>(args);  

	while(pThread->m_status)
	{
		if(pThread->m_dormant)
		{
			usleep(pThread->m_threadResponseInterval*50);
		}else
		{
			pThread->run();
		}
		usleep(pThread->m_threadResponseInterval);
	}

	return NULL;
}

void TOThreadBase::setResponseInterval(unsigned long interval)
{
	m_threadResponseInterval = interval;
}

TOStatusThreadBase::TOStatusThreadBase():m_rule(NULL)
{
	m_calssName = typeid(*this).name();
	startThread();
}

TOStatusThreadBase::~TOStatusThreadBase()
{
	//
}
void TOStatusThreadBase::addStatusUnit(TO_THREAD_STATUS_UNIT& unit)
{
	m_baseStatusFuncList.push_back(unit);
	if(1 == m_baseStatusFuncList.size())
	{
		m_current = m_baseStatusFuncList[0];
	}
}

void TOStatusThreadBase::defineStatusRule(TO_STATUS_RULE func)
{
	m_rule = func;
}

void TOStatusThreadBase::run()
{
	if(m_baseStatusFuncList.size() > 0)
	{
		m_current.StatusExecute();
	}else
	{
		cout << "no unit in status list" << endl;
	}
}  

void TOStatusThreadBase::nextStatus()
{
	if(NULL == m_rule)
	{
		cout << "no rule define with normal status change." << endl;
		return;
	}
	string next =  m_rule(m_current.StatusName);
	for (int i = 0; i < m_baseStatusFuncList.size(); ++i)
	{
		if(m_baseStatusFuncList[i].StatusName == next)
		{
			m_current = m_baseStatusFuncList[i];
		}
	}
}
