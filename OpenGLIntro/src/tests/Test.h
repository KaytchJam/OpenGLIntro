#pragma once
#include <vector>
#include <functional>
#include <string>
#include "TestClearColor.h"
#include <iostream>

namespace test {
	class Test {
	public:
		Test() {};
		virtual ~Test() {};

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		virtual void onImGuiRender() override;

		template<typename T>
		void registerTest(const std::string& name) {
			std::cout << "Registering test: " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T();  }));
		}

	private:
		Test*& m_CurrentTest;
		// we could've made a struct instead of a pair here but it doesn't really matter
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	 };
}
