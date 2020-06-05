#include "Renderer.h"

#include<GLCore/Core/Application.h>
#include<glfw/include/GLFW/glfw3.h>

#include"../../OpenGL/Camera.h"
#include"../TextureAtlas.h"
#include"..//Chunk/Chunk.h"
#include"../../OpenGL/Model2D.h"

Renderer::Renderer()
	:m_chunkShader("3dVert", "TextureFrag"), m_2dTextureShader("2dVert", "TextureFrag")
{
	glfwSetInputMode(static_cast<GLFWwindow*>(GLCore::Application::Get().GetWindow().GetNativeWindow()),
					 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::bindCameraImpl(Camera& camera)
{
	m_camera = &camera;
}

void Renderer::addChunkToQueueImpl(const Chunk& chunk)
{
	m_chunks.push_back(&chunk);
}

void Renderer::add2DModelToQueueImpl(const Model2D& model)
{
	m_2dModels.push_back(&model);
}

void Renderer::clearImpl()
{
	glClearColor(0.15, 0.52, 0.90, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::updateImpl()
{
	m_chunkShader.bind();
	m_chunkShader.loadUniformMatrix("u_projView", m_camera->getProjectionViewMatrix());
	TextureAtlas::bind();

	for(const Chunk* chunk : m_chunks)
	{
		unsigned blockIndicesCount = chunk->getBlockMesh().getNumberIndicies();


		chunk->getBlockMesh().bind();
		glDrawElements(GL_TRIANGLES, blockIndicesCount, GL_UNSIGNED_INT, nullptr);
	}

	//bind water shader here

	for(const Chunk* chunk : m_chunks)
	{
		unsigned waterIndicesCount = chunk->getWaterMesh().getNumberIndicies();

		chunk->getWaterMesh().bind();
		glDrawElements(GL_TRIANGLES, waterIndicesCount, GL_UNSIGNED_INT, nullptr);
	}

	m_chunks.clear();

	m_2dTextureShader.bind();

	for(const Model2D* model : m_2dModels)
	{
		m_2dTextureShader.loadUniformMatrix("u_transform", model->getTransform());
		model->bind();
		glDrawElements(GL_TRIANGLES, model->getNumberIndicies(), GL_UNSIGNED_INT, nullptr);
	}
	m_2dModels.clear();
}

void Renderer::initImpl(Camera& camera)
{
	bindCameraImpl(camera);
	auto& window = GLCore::Application::Get().GetWindow();

	float aspect = static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight());
	m_camera->setProjectionMatrix(90.f, aspect);
}
