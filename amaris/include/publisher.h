#pragma once

#include "amaris.h"

#include <vector>

namespace amaris
{

	class AMARIS_API Event 
	{
	public:
		explicit Event(const int type) : m_type(type) {};
		virtual ~Event() {};
		int getType() const { return m_type; };
	protected:
		int m_type = -1;
	};	

	class Listener;

	class AMARIS_API Publisher
	{
	public:
		Publisher();
		virtual ~Publisher();
		void addListener(Listener* listener);
		void notify(const Event& event);
	protected:
		std::vector<Listener*> m_pListeners;
		Event* m_pEvent{nullptr};
	};

	class AMARIS_API Listener
	{
	public:
		Listener();
		~Listener();
		virtual void update(const Event& event) = 0;
	protected:
	};
}