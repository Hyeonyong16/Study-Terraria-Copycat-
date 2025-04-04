#pragma once

enum class CB_TYPE
{
	TRANSFORM,	// b0
	MATERIAL,	// b1
	GLOBAL,		// b2

	END,
};


// Rasterizer State
enum class RS_TYPE
{
	CULL_BACK, // cull_ccw, �޸�(�ݽð� ����) �ø�
	CULL_FRONT, // cull_cw
	CULL_NONE,  // �ø����� ����
	WIRE_FRAME, // �ø����� ����, 

	END,
};

// DepthStencilState
enum class DS_TYPE
{
	LESS,				// �������� : �� �۾ƾ� ���, ���� ��� O
	LESS_EQUAL,			// �������� : �� �۾ƾ� ������ ���, ���� ��� O

	GREATER,			// �������� : �� �־�� ���, ���� ��� 0

	NO_WRITE,			// �������� : �� �۾ƾ� ���(LESS), ���� ��� X
	NO_TEST_NO_WIRITE,	// �������� �׻� ����(�˻�X), ���� ��� X

	END,
};

// BlendState
enum class BS_TYPE
{
	DEFAULT,	// Src : 1, Dst : 0
	ALPHABLEND, // Src : A, Dst : (1 - A)
	ALPHABLEND_COVERAGE,
	ONE_ONE,

	END,
};

enum COMPONENT_TYPE
{
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	LIGHT2D,
	LIGHT3D,
	CAMERA,	
	BOUNDINGBOX,
	
	// Rendering Component
	MESHRENDER,			// ���� �⺻���� RenderComponent
	SPRITERENDER,		// Sprite �ϳ� �������ϴ� ������Ʈ
	FLIPBOOKRENDER,		// Flipbook ��� ������Ʈ
	TILERENDER,			// Ÿ�ϸ� ������
	PARTICLERENDER,		// ���� ������
	SKYBOX,				// 3D ���
	DECAL,				// ����
	LANDSCAPE,			// 3D ����

	COMPONENT_END,

	SCRIPT,				// �뺻, ����, ������
};

enum ASSET_TYPE
{
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	PREFAB,	
	SOUND,
	GRAPHIC_SHADER,	// ������
	COMPUTE_SHADER, // ���, GP(General Purpose)
	SPRITE,
	FLIPBOOK,
	ASSET_END,
};


// ����(Projection) ���
enum PROJ_TYPE
{
	ORTHOGRAPHIC,	// ��������
	PERSPECTIVE,	// ��������
};


// ����
enum class DIR
{
	RIGHT,
	UP,
	FRONT,
	END,
};

enum class SHADER_DOMAIN
{
	DOMAIN_QPAQUE,		// ������
	DOMAIN_MASKED,		// ������ + ���� ����
	DOMAIN_TRANSPARENT, // ������ + ����	
	DOMAIN_POSTPROCESS, // ��ó��

	DOMAIN_DEBUG,		// ����� ������
};

enum SCALAR_PARAM
{
	INT_0,		INT_1,		INT_2,		INT_3,
	FLOAT_0,	FLOAT_1,	FLOAT_2,	FLOAT_3,
	VEC2_0,		VEC2_1,		VEC2_2,		VEC2_3,
	VEC4_0,		VEC4_1,		VEC4_2,		VEC4_3,
	MAT_0,		MAT_1,		MAT_2,		MAT_3,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEX_END,
};


enum class DEBUG_SHAPE
{
	// 2D
	RECT,
	CIRCLE,
	LINE,

	// 3D
	CUBE,
	SPHERE,
};

enum class TASK_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_LEVEL,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,	// ���⼺ ����, ���� (�¾�, ��)
	POINT,			// ������, ����, ����, ȶ��
	SPOT,			// ����Ʈ����Ʈ, ������
};