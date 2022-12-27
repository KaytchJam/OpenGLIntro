#pragma once
#include "Test.h"

namespace test {
	class TestTexture2D : public Test {
	public:
		TestTexture2D();
		~TestTexture2D();

		void onUpdate(float deltaTime);
		void onRender();
		void onImGuiRender();
	private:
		float m_ClearColor[4]; // RBGA
	};
}