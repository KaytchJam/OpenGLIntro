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
	class TestDrawRect : public Test {
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
		VertexBuffer* m_VB = nullptr;

		//STACK OBJECTS
		glm::mat4 proj;
		glm::mat4 view;
		glm::vec3 translationB;

	};
}

