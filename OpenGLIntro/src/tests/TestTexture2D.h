#pragma once
#include "Test.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../VertexBuffer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	class TestTexture2D : public Test {
	public:
		TestTexture2D();
		~TestTexture2D();

		void onUpdate(float deltaTime);
		void onRender();
		void onImGuiRender();
	private:
		// HEAP OBJECTS
		VertexArray* m_VA = nullptr;
		IndexBuffer* m_IB = nullptr;
		Shader* m_Sh = nullptr;
		Texture* m_Tx = nullptr;
		VertexBuffer* m_VB = nullptr;

		// STACK OBJECTS
		glm::mat4 proj, view;
		glm::vec3 translationA, translationB;
	};
}