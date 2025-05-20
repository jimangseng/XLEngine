#include "SceneObject.h"
#include "PrimitiveFactory.h"

const std::shared_ptr<Primitive>& PrimitiveFactory::CreatePrimitive(Primitives _primitive)
{
	layout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Primitive::Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Primitive::Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	switch (_primitive)
	{
	case Primitives::Triangle:
		vertices =
		{
			{ { 0.0f, 0.5f, 0.1f }, { 1.f, 0.f, 0.f, 1.f } },
			{ { 0.5f, -0.5f, 0.1f }, { 0.f, 1.f, 0.f, 1.f } },
			{ { -0.5f, -0.5f, 0.1f }, { 0.f, 0.f, 1.f, 1.f } }
		};

		indices = { 0, 1, 2 };


		break;

	case Primitives::Quad:
		vertices = {
			{ { -0.5f,  0.5f, 0.1f }, { 1.f, 0.f, 0.f, 1.f } }, // Top-left
			{ {  0.5f,  0.5f, 0.1f }, { 0.f, 1.f, 0.f, 1.f } }, // Top-right
			{ {  0.5f, -0.5f, 0.1f }, { 0.f, 0.f, 1.f, 1.f } }, // Bottom-right
			{ { -0.5f, -0.5f, 0.1f }, { 1.f, 1.f, 0.f, 1.f } }  // Bottom-left
		};

		indices = {
			0, 1, 2,   // 첫 번째 삼각형 (Top-left → Top-right → Bottom-right)
			0, 2, 3    // 두 번째 삼각형 (Top-left → Bottom-right → Bottom-left)
		};

		break;

	case Primitives::Cube:
		vertices = {
			// Front (+Z)
			{ { -0.5f,  0.5f,  0.5f }, {1, 0, 0, 1} }, // 0
			{ {  0.5f,  0.5f,  0.5f }, {1, 0, 0, 1} }, // 1
			{ {  0.5f, -0.5f,  0.5f }, {1, 0, 0, 1} }, // 2
			{ { -0.5f, -0.5f,  0.5f }, {1, 0, 0, 1} }, // 3

			// Back (-Z)
			{ {  0.5f,  0.5f, -0.5f }, {0, 1, 0, 1} }, // 4
			{ { -0.5f,  0.5f, -0.5f }, {0, 1, 0, 1} }, // 5
			{ { -0.5f, -0.5f, -0.5f }, {0, 1, 0, 1} }, // 6
			{ {  0.5f, -0.5f, -0.5f }, {0, 1, 0, 1} }, // 7

			// Top (+Y)
			{ { -0.5f,  0.5f, -0.5f }, {0, 0, 1, 1} }, // 8
			{ {  0.5f,  0.5f, -0.5f }, {0, 0, 1, 1} }, // 9
			{ {  0.5f,  0.5f,  0.5f }, {0, 0, 1, 1} }, //10
			{ { -0.5f,  0.5f,  0.5f }, {0, 0, 1, 1} }, //11

			// Bottom (-Y)
			{ { -0.5f, -0.5f,  0.5f }, {1, 1, 0, 1} }, //12
			{ {  0.5f, -0.5f,  0.5f }, {1, 1, 0, 1} }, //13
			{ {  0.5f, -0.5f, -0.5f }, {1, 1, 0, 1} }, //14
			{ { -0.5f, -0.5f, -0.5f }, {1, 1, 0, 1} }, //15

			// Left (-X)
			{ { -0.5f,  0.5f, -0.5f }, {0, 1, 1, 1} }, //16
			{ { -0.5f,  0.5f,  0.5f }, {0, 1, 1, 1} }, //17
			{ { -0.5f, -0.5f,  0.5f }, {0, 1, 1, 1} }, //18
			{ { -0.5f, -0.5f, -0.5f }, {0, 1, 1, 1} }, //19

			// Right (+X)
			{ { 0.5f,  0.5f,  0.5f }, {1, 0, 1, 1} }, //20
			{ { 0.5f,  0.5f, -0.5f }, {1, 0, 1, 1} }, //21
			{ { 0.5f, -0.5f, -0.5f }, {1, 0, 1, 1} }, //22
			{ { 0.5f, -0.5f,  0.5f }, {1, 0, 1, 1} }, //23
		};

		indices = {
			// Front
			0, 1, 2,  0, 2, 3,
			// Back
			4, 5, 6,  4, 6, 7,
			// Top
			8, 9,10,  8,10,11,
			// Bottom
		   12,13,14, 12,14,15,
		   // Left
		  16,17,18, 16,18,19,
		  // Right
		 20,21,22, 20,22,23
		};

		break;
	default:
		break;
	}

	primitive = std::make_shared<Primitive>() ;

	primitive->SetVertices(vertices);
	primitive->SetIndices(indices);
	primitive->SetLayout(layout);

	return primitive;
}
