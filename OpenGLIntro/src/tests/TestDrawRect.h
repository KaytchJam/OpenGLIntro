#pragma once
#include "Test.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {
	class TestDrawRect : Test {
	public:
		TestDrawRect();
		~TestDrawRect();

		void onUpdate(float deltaTime);
		void onRender();
		void onImGuiRender();
	private:
		// HEAP OBJECTS
		VertexArray* m_VA = nullptr;
		IndexBuffer* m_IB = nullptr;
		Shader* m_Sh = nullptr;

		//STACK OBJECTS
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::vec3 translationB;

	};
}

