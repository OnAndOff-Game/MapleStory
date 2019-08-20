#pragma once


enum EMRenderType : int{
	eMR_Back,
	eMR_Map,
	eMR_Obj,
	eMR_UI,
	eMR_Cnt,
};

enum EMAnimType : int{

	eMA_Static,
	eMA_Standing,
	eMA_Moving,
	eMA_Jumping,
	eMA_Hit,
	eMA_Die,
	eMA_Attack,
	eMA_Skill,
	eMA_Chase,
	eMA_Cnt,
};

enum EMObjType : int{
	eMO_Obj,
	eMO_Player,
	eMO_Mob,
	eMO_PSkill,
	eMO_MSkill,
	eMO_Item,
	eMO_Cnt,
};

struct BatchElement
{
	Gdiplus::Point Pos;
	int SizeX;
	int SizeY;
	Gdiplus::Image* img;

	int z;
	float alpha;

	bool bFlip;

	/*
	rotation
	proxyid;
	float u;
	float v;
	*/

};

typedef struct MTransform
{
	MTransform() : Scale(1), Rotation(0)
	{}

	Gdiplus::Point	Translation;
	float			Scale;
	float			Rotation;
}MTRASFORM;

typedef struct SprData
{
	EMAnimType type;	// ��ο� Ÿ��
	std::string path;   // ��� ex) Object\acc1.img
	std::string sprname; // ���� ��Ī ex) woodMarble.artificiality / pv
	std::string name;	// �̸� ���� 2
	int	cnt;			// ���� 0 ��� = woodMarble.artificiality.2.0
}SPRDATA, *LPSPRDATA;

typedef struct Img_Data
{
	std::string filename; // ���� ��� + �̸� ex)  Object\acc1.img\woodMarble.artificiality.2.0.png
	int id;				  // png �տ� �ִ� ���� Sprdata�� cnt�� MAX ����

	Gdiplus::Point imgsize; // x * y == 1 link

	Gdiplus::Point origin; // ��ǥ �̰� ������ ���� ��ǥ�� ����ؼ� �־����
	Gdiplus::Point head; //�浹���ϸ� �Ⱦ�
	Gdiplus::Point lt;  //�浹���ϸ� �Ⱦ�
	Gdiplus::Point rb; // �浹���ϸ�

	int delay;			// anim ��� ������
				
	int z;				// z��

	int a0;				// ���� 0��
	int a1;				// ���� 1��

	std::string link;   // ��ũ �Ⱦ�
}IMG_DATA, *LPIMG_DATA;

struct MobInfo
{
	int acc; // ����
	bool bodyAttack; // ���� ����
	int category;
	int eva;//ȸ��
	int exp;//����ġ
	bool firstAttack; //���� ����
	int level;
	int maxHp;
	int maxMp;
	int speed; // �÷��̾��� �̵��ӵ��� 100%�϶��� ���ӵ��� �÷��̾�� ������ +, ������ -)
	int PADamge; // ���� ���� ������
	int MADamge; // ���� ���� ������
	int PDDamge; // ���� ��� ������?
	int MDDamge; // ���� ��� ������?
	int PDRate; //���� ��� ������?
	int MDRate; //���� ��� ������?
	int pushed; // �˹� �Ÿ�?
	char elemAttr[256]; //����? ����? 2 �ݰ� 3 ���� / I = ����, F = ��, L = ����, S = �� 
	int fs; // �̲�����
};

struct RoadLine
{
	int layer;
	int group;
	int id;
	Gdiplus::Point line1;
	Gdiplus::Point line2;
	int prv;
	int nxt;
};

struct MRoadGroup
{
	int layer;
	int num;

	std::vector<int> line;

	Gdiplus::Point colpt1;
	Gdiplus::Point colpt2;

	int Begin;
	int End;
};

struct akt
{
	int atkafter;
	Gdiplus::Rect range;
	   
};
struct effect
{
};
