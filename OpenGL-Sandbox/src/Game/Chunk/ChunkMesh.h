#pragma once

#include"../../OpenGL/Mesh.h"

struct ChunkMesh
{
	Mesh blockMesh;
	unsigned blockIndexCount = 0;

	Mesh waterMesh;
	unsigned waterIndexCount = 0;

	Mesh translucentBlockMesh;
	unsigned translucentIndexCount = 0;

	Mesh xFaceMesh;
	unsigned xFaceIndexCount = 0;

	void clear()
	{
		blockMesh.clear();
		waterMesh.clear();
		translucentBlockMesh.clear();
		xFaceMesh.clear();

		blockIndexCount = 0;
		waterIndexCount = 0;
		translucentIndexCount = 0;
		xFaceIndexCount = 0;
	}
};