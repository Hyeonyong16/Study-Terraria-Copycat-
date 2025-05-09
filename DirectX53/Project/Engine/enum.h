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
	CULL_BACK, // cull_ccw, 뒷면(반시계 순서) 컬링
	CULL_FRONT, // cull_cw
	CULL_NONE,  // 컬링하지 않음
	WIRE_FRAME, // 컬링하지 않음, 

	END,
};

// DepthStencilState
enum class DS_TYPE
{
	LESS,				// 깊이판정 : 더 작아야 통과, 깊이 기록 O
	LESS_EQUAL,			// 깊이판정 : 더 작아야 같으면 통과, 깊이 기록 O

	GREATER,			// 깊이판정 : 더 멀어야 통과, 깊이 기록 0

	NO_WRITE,			// 깊이판정 : 더 작아야 통과(LESS), 깊이 기록 X
	NO_TEST_NO_WIRITE,	// 깊이판정 항상 성공(검사X), 깊이 기록 X

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

enum class LEVEL_STATE
{
	PLAY,
	STOP,
	PAUSE,
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
	MESHRENDER,			// 가장 기본적인 RenderComponent
	SPRITERENDER,		// Sprite 하나 렌더링하는 컴포넌트
	FLIPBOOKRENDER,		// Flipbook 재생 컴포넌트
	TILERENDER,			// 타일맵 렌더링
	PARTICLERENDER,		// 입자 렌더링
	SKYBOX,				// 3D 배경
	DECAL,				// 문신
	LANDSCAPE,			// 3D 지형

	COMPONENT_END,

	SCRIPT,				// 대본, 역할, 컨텐츠
};
extern const char* COMPONENT_TYPE_STR[];
extern const wchar_t* COMPONENT_TYPE_WSTR[];

enum ASSET_TYPE
{
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	PREFAB,
	SOUND,
	GRAPHIC_SHADER,	// 렌더링
	COMPUTE_SHADER, // 계산, GP(General Purpose)
	SPRITE,
	FLIPBOOK,
	ASSET_END,
};
extern const char* ASSET_TYPE_STR[];
extern const wchar_t* ASSET_TYPE_WSTR[];

// 투영(Projection) 방식
enum PROJ_TYPE
{
	ORTHOGRAPHIC,	// 직교투영
	PERSPECTIVE,	// 원근투영
};


// 방향
enum class DIR
{
	RIGHT,
	UP,
	FRONT,
	END,
};

enum class SHADER_DOMAIN
{
	DOMAIN_QPAQUE,		// 불투명
	DOMAIN_MASKED,		// 불투명 + 완전 투명
	DOMAIN_TRANSPARENT, // 반투명 + 투명	
	DOMAIN_POSTPROCESS, // 후처리

	DOMAIN_DEBUG,		// 디버그 렌더링
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
	ADD_CHILD,
	CHANGE_LEVEL_STATE,
	CHANGE_LEVEL,
	DELETE_ASSET,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,	// 방향성 광원, 전역 (태양, 달)
	POINT,			// 점광원, 전구, 전등, 횃불
	SPOT,			// 스포트라이트, 손전등
};

// 파티클에 적용될 각각의 기능들
enum class PARTICLE_MODULE
{
	SPAWN,
	SPAWN_BURST,
	ADD_VELOCITY,
	SCALE,
	DRAG,
	NOISE_FORCE,
	RENDER,

	END,
};