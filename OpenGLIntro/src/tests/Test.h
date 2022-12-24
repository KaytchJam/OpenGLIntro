#pragma once
#include <vector>
#include <functional>

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
		TestMenu() {}
		~TestMenu();

		void onUpdate(float deltaTime) override;
		virtual void onRender() override;
		virtual void onImGuiRender() override;
	private:
		// we could've made a struct instead of a pair here but it doesn't really matter
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	 };
}
