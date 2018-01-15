//
//  EventManager.h
//  EventManager
//
//  Created by Tiny Oh 2018.1.14
//  Copyright (c) 2018 White Sky. All rights reserved.
//

#ifndef TO_THREAD_BASE_H
#define TO_THREAD_BASE_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include "EventManager.h"

#define _DEBUG_TO_THREAD_BASE true
#define DEFAULT_RESPONSE_INTERVAL 2000

typedef struct 
{
	std::string StatusName;
	void (*StatusExecute)(void);
}TO_THREAD_STATUS_UNIT;

typedef std::string (*TO_STATUS_RULE)(const std::string&);

using namespace TO;
namespace TO {
	class TOThreadBase
	{
	public:
		TOThreadBase();
		virtual ~TOThreadBase();
		virtual void run();
		bool dormantThread();
		void setResponseInterval(unsigned long interval);
		void name(){cout << m_calssName << endl;}
	protected:
		bool startThread();
		bool stopThread();
	    pthread_t m_threadID;
	    bool m_dormant;
	    bool m_status;
	    string m_calssName;
	private:
	    static void* threadMain(void* args);
	    unsigned long m_threadResponseInterval;
	};

	class TOStatusThreadBase:public TOThreadBase
	{
	public:
		TOStatusThreadBase();
		virtual ~TOStatusThreadBase();
		void addStatusUnit(TO_THREAD_STATUS_UNIT& unit);
		void defineStatusRule(TO_STATUS_RULE func);
		virtual void run();
	protected:
		void nextStatus();
	private:

		TO_THREAD_STATUS_UNIT m_current;
		TO_STATUS_RULE m_rule;
		std::vector<TO_THREAD_STATUS_UNIT> m_baseStatusFuncList;
	};
}

#endif