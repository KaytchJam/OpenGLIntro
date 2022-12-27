#include "TestDrawRect.h"
#include "../ErrorManager.h"
#include "imgui/imgui.h"
#include <iostream>

namespace test {
	TestDrawRect::TestDrawRect() : proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), translationB(glm::vec3(200, 200, 0)) {
		float x = 100.0f;
		float y = 200.0f;
		float length = 200.0f;
		float height = 150.0f;

		float positions[16] = {
				x,			y,			0.0f, 0.0f,	// bottom left of square - 0
				x + length, y,			1.0f, 0.0f,	// bottom right - 1
				x + length, y + height,	1.0f, 1.0f, // top right - 2
				x,			y + height,	0.0f,  1.0f // top left - 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VA = new VertexArray();
		VertexBuffer vb(positions, 16 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);

		std::cout << "VertexBuffer created" << std::endl;

		m_VA->addBuffer(vb, layout);

		m_IB = new IndexBuffer(indices, 6);
		m_Sh = new Shader("res/shaders/TestBasic.shader");
		m_Sh->Bind();
		m_Sh->setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		m_VA->UnBind();
		m_Sh->UnBind();
		vb.UnBind();
		m_IB->UnBind();

	}

	TestDrawRect::~TestDrawRect() {
		//std::cout << "Deleting all Buffers" << std::endl;
		delete m_VA;
		delete m_IB;
		delete m_Sh;
	}

	void TestDrawRect::onUpdate(float deltaTime) {
		glm::mat4 model = glm::translate(glm::mat4(1.0), translationB);
		glm::mat4 mvp = proj * view * model;
		m_Sh->Bind();
		m_Sh->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		m_Sh->setUniformMat4f("u_ModelViewProjection", mvp);
	}

	void TestDrawRect::onRender() {
		// Rendering
		m_Sh->Bind();
		m_VA->Bind();
		m_IB->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, m_IB->getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void TestDrawRect::onImGuiRender() {
		 ImGui::SliderFloat2("Rectangle Position", &translationB.x, 0.0f, 960.0f);
	}
}
