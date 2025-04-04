#pragma once



// Vertex
// ��ü�� ���¸� �̷�� ���� �⺻ ����
struct Vtx
{	
	Vec3	vPos;		// ������ ��ġ
	Vec4	vColor;		// ������ ����	
	Vec2	vUV;		// ������ ������ �ؽ����� ��ġ(��ǥ)
};

// DebugShapeInfo
struct tDebugShapeInfo
{
	DEBUG_SHAPE Shape;
	Vec3	    WorldPos;
	Vec3		WorldScale;
	Vec3		WorldRotation;
	Matrix		MatWorld;
	Vec4		Color;
	float		CurTime;
	float		Duration;
	bool		DepthTest;
};

struct tTask
{
	TASK_TYPE Type;
	DWORD_PTR Param0;
	DWORD_PTR Param1;
};

struct tLight2DInfo
{
	LIGHT_TYPE	Type;		// ���� ����
	Vec3		Color;		// ���� ����
	Vec3		WorldPos;	// ���� ��ġ	
	float		Radius;		// ���� ����, �ݰ�
	Vec3		Dir;		// ������ ����
	float		Angle;		// ���� ����(����Ʈ ����Ʈ)	
};


// =============
// Particle ����
// =============
struct tParticle
{
	Vec4	LocalPos;		// ���� ������Ʈ�� ������ ��� ��ǥ
	Vec4	WorldPos;		// ��ƼŬ�� ���� ��ǥ
	Vec4	WorldScale;		// ��ƼŬ ���� ũ��
	Vec4	Color;			// ��ƼŬ ����

	Vec4	Force;			// ��ƼŬ�� �־����� �ִ� ���� ����
	Vec4	Velocity;		// ��ƼŬ �ӵ�
	float	Mass;			// ��ƼŬ ����

	float	Age;			// ��ƼŬ ����, Age �� Life �� �����ϸ� ������ ���� ��
	float	Life;			// ��ƼŬ �ִ� ����
	float	NormalizedAge;  // ��ü ���� ���, ���� Age ����. �ڽ��� Age �� Life ��� ����ȭ �� ��

	int		Active;			// ��ƼŬ Ȱ��ȭ ����
	int		padding[3];		// ��ƼŬ ����ü ũ�⸦ 16 ����� ���߱� ���� �е� ����Ʈ
};

struct tSpawnCount
{
	int		SpawnCount;
	Vec3	vPadding;
};

// Particle Module
struct tParticleModule
{
	// Spawn Modlue
	float	SpawnRate;			// �ʴ� ��ƼŬ ������
	Vec4	StartColor;			// �ʱ� ��ƼŬ ����
	Vec4	EndColor;			// ��ƼŬ ���� ����
	Vec3	MinScale;			// ���� �� �ּ� ũ��
	Vec3	MaxScale;			// ���� �� �ִ� ũ��
	float	MinLife;			// ���� �� �ּ� �ֱ�
	float	MaxLife;			// ���� �� �ִ� �ֱ�
	int		SpawnShape;			// 0 : Box, 1 : Sphere
	Vec3	SpawnShapeScale;
	int		SpaceType;			// 0 : Local, 1 : World

	// �߰� ������
	Vec3	ObjectWorldPos;

	int		padding[3];
};








// ===================
// ������� ���� ����ü
// ===================
struct tTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;

	Matrix	matWV;
	Matrix	matWVP;
};
extern tTransform g_Trans;

// ������ ���ؼ� ���޵Ǵ� ���
struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];

	//�ؽ��� ���ε� ����
	int		bTex[TEX_END];
	int		padding[2];
};

// Global Data
struct tGlobal
{
	Vec2	g_Resolution;
	float   g_DT;
	float   g_EngineDT;
	float   g_AccTime;
	int     g_Light2DCount;
	int     g_Light3DCount;
	int     padding;
};
extern tGlobal g_global;