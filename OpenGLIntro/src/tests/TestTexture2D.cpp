#include "TestTexture2D.h"
#include "imgui/imgui.h"
#include "../ErrorManager.h"
#include <iostream>

namespace test {

	TestTexture2D::TestTexture2D() : 
		proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		translationA(200, 200, 0),
		translationB(400, 200, 0) {

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

		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		m_VA->addBuffer(vb, layout);

		m_IB = new IndexBuffer(indices, 6);

		m_Sh = new Shader("res/shaders/Basic.shader");
		m_Sh->Bind();

		m_Tx = new Texture("res/textures.Data_Heart.png");
		m_Tx->Bind();
		m_Sh->setUniform1i("u_Texture", 0);

		m_VA->UnBind();
		m_Sh->UnBind();
		vb.UnBind();
		m_IB->UnBind();
		m_Tx->UnBind();

		std::cout << "Out of constructor" << std::endl;
	}

	TestTexture2D::~TestTexture2D() {
		delete m_VA; // delete vertex array
		delete m_IB; // delete index buffer
		delete m_Sh; // delete shader
		delete m_Tx; // delete texture

	}

	void TestTexture2D::onUpdate(float deltaTime) {

	}

	void TestTexture2D::onRender() {
		Renderer myRenderer;
		glm::mat4 model;
		glm::mat4 mvp;
		m_Tx->Bind();

		// Object 1 Rendering
		{
		    model = glm::translate(glm::mat4(1.0), translationA);
		    mvp = proj * view * model;
		    m_Sh->Bind();
		    m_Sh->setUniformMat4f("u_ModelViewProjection", mvp);
		    myRenderer.Draw(*m_VA, *m_IB, *m_Sh);
		}

		std::cout << "Rendered object 1" << std::endl;

		// Object 2 Rendering
		{
		    model = glm::translate(glm::mat4(1.0), translationB);
		    mvp = proj * view * model;
		    m_Sh->Bind();
		    m_Sh->setUniformMat4f("u_ModelViewProjection", mvp);
			myRenderer.Draw(*m_VA, *m_IB, *m_Sh);
		}

		std::cout << "Rendered object 2" << std::endl;
	}

	void TestTexture2D::onImGuiRender() {
		    ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		    ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);

	}
}
