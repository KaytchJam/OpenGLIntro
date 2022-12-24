#include "Test.h"
#include "imgui/imgui.h"

namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {

	}

	void TestMenu::onImGuiRender() {
		for (auto& testPair : m_Tests) {
			if (ImGui::Button(testPair.first.c_str())) {
				m_CurrentTest = testPair.second();
			}
		}
	}
}