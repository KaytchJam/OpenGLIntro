#include "TestTexture2D.h"

namespace test {

	TestTexture2D::TestTexture2D() {

		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f, 50.0f, 0.0f, 1.0f
		};

		unsigned int indices[]{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	}

	TestTexture2D::~TestTexture2D() {

	}

	void TestTexture2D::onUpdate(float deltaTime) {

	}

	void TestTexture2D::onRender() {

	}

	void TestTexture2D::onImGuiRender() {

	}
}
