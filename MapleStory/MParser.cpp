#include "pch.h"
#include "MParser.h"

//void MParser::Mob(const std::string& _filename)
//{
//	Node node = Node(_filename.c_str());
//
//	if (!node.IsNull())
//		return;
//
//	std::string sprname = _filename; // ÀÌ¸§
//	sprname.replace(sprname.find(".xml"), 4, "");
//
//	int sprid = std::stoi(node.GetName());
//
//	if (SPRMGR->GetSpriteDataCnt(sprid) == 0)
//	{
//		for (auto anim = node.begin(); anim; anim = anim++) //anim name
//		{
//			if (!strcmp(anim.GetName(), "info"))
//			{
//				LoadInfo(anim);
//			}
//			else
//			{
//				SPRDATA sprdata;
//				int nCnt = 0;
//
//				sprdata.path = sprname;
//				sprdata.name = anim.GetName();
//				sprdata.type = AnimTypeSetting(sprdata.name);
//				
//				for (auto num = node[anim.GetName()].begin(); num; num = num++) // num
//				{
//					IMG_DATA imgdata;
//
//					imgdata.filename = sprname + '/' + sprdata.name + '.' + num.GetName() + ".png";
//					imgdata.id = atoi(num.GetName());
//					imgdata.imgsize = num.GetValuePoint();
//
//					if (imgdata.imgsize.X * imgdata.imgsize.Y == 1)
//					{
//						std::string templink;
//						if (!num["_inlink"].IsNull())
//						{
//							char from = '/', to = '.';
//
//							templink = num["_inlink"].GetValueString();
//
//							std::replace(templink.begin(), templink.end(), from, to);
//
//							imgdata.link = sprname + '/' + sprdata.name + '.' + templink + ".png";
//						}
//
//						//if (!t["_outlink"].IsNull())
//						//	imgdata.origin = t["origin"].GetValuePoint();
//					}
//
//					if (!num["origin"].IsNull())
//						imgdata.origin = num["origin"].GetValuePoint();
//					else
//					{
//						imgdata.origin.X = imgdata.imgsize.X / 2;
//						imgdata.origin.Y = imgdata.imgsize.Y / 2;
//					}
//
//					if (!num["lt"].IsNull())
//						imgdata.leftTop = num["lt"].GetValuePoint();
//
//					if (!num["rb"].IsNull())
//						imgdata.rightBottom = num["rb"].GetValuePoint();
//
//					if (!num["head"].IsNull())
//						imgdata.head = num["head"].GetValuePoint();
//
//					if (!num["delay"].IsNull())
//						imgdata.delay = num["delay"].GetValueInt();
//
//					if (!num["a0"].IsNull())
//						imgdata.beginAlpha = num["a0"].GetValueInt();
//					else
//						imgdata.beginAlpha = 0;
//
//					if (!num["a1"].IsNull())
//						imgdata.endAlpha = num["a1"].GetValueInt();
//					else
//						imgdata.endAlpha = 0;
//
//					if (!num["z"].IsNull())
//						imgdata.z = num["z"].GetValueInt();
//					else
//						imgdata.z = 2;
//
//
//					ASSETMGR->SetAssetData(imgdata);
//					nCnt++;
//				}
//
//				sprdata.cnt = nCnt;
//
//				SPRMGR->SetSpriteData(sprid, sprdata);
//			}
//		}
//	}
//
//	else
//	{
//		for (auto o = node.begin(); o; o = o++) //anim name
//		{
//			if (!strcmp(o.GetName(), "info"))
//			{
//				LoadInfo(o);
//				break;
//			}
//		}
//	}
//
//	//m_pSprites = new MSpriteComponent(sprid, EMRenderType::eMRenderType_Object);
//
//	//m_vComponent.push_back(pSC);
//}

EMAnimType MParser::AnimTypeSetting(std::string& InAnim)
{
	for (int i = 0; i < EMAnimType::eMAnimType_Cnt; ++i)
	{
		if(!InAnim.find(ANIM_TYPE[i]))
			return static_cast<EMAnimType>(i);
	}

	return EMAnimType::eMAnimType_Static;
}
void MParser::GetImgData(IMG_DATA& outImgData, Node& inNode)
{
	if (inNode.IsNull())
		return;

	//outImgData.filename = sprname + '/' + sprdata.name + '.' + inNode.GetName() + ".png";
	outImgData.id = atoi(inNode.GetName());
	outImgData.imgsize = inNode.GetValuePoint();

	//if (outImgData.imgsize.X * outImgData.imgsize.Y == 1)
	//{
	//	std::string templink;
	//	if (!inNode["_inlink"].IsNull())
	//	{
	//		char from = '/', to = '.';

	//		templink = inNode["_inlink"].GetValueString();

	//		std::replace(templink.begin(), templink.end(), from, to);

	//		outImgData.link = sprname + '/' + sprdata.name + '.' + templink + ".png";
	//	}

	//	//if (!t["_outlink"].IsNull())
	//	//	outImgData.origin = t["origin"].GetValuePoint();
	//}

	if (!inNode["origin"].IsNull())
		outImgData.origin = inNode["origin"].GetValuePoint();
	else
	{
		outImgData.origin.X = outImgData.imgsize.X / 2;
		outImgData.origin.Y = outImgData.imgsize.Y / 2;
	}

	if (!inNode["lt"].IsNull())
		outImgData.leftTop = inNode["lt"].GetValuePoint();

	if (!inNode["rb"].IsNull())
		outImgData.rightBottom = inNode["rb"].GetValuePoint();

	if (!inNode["head"].IsNull())
		outImgData.head = inNode["head"].GetValuePoint();

	if (!inNode["delay"].IsNull())
		outImgData.delay = inNode["delay"].GetValueInt();

	if (!inNode["a0"].IsNull())
		outImgData.beginAlpha = inNode["a0"].GetValueInt();
	else
		outImgData.beginAlpha = 0;

	if (!inNode["a1"].IsNull())
		outImgData.endAlpha = inNode["a1"].GetValueInt();
	else
		outImgData.endAlpha = 0;

	if (!inNode["z"].IsNull())
		outImgData.z = inNode["z"].GetValueInt();
	else
		outImgData.z = 2;
}

void MParser::GetMobData(MobData& outMobData, Node& inNode)
{
	if (inNode.IsNull())
		return;

	outMobData.level = inNode["level"].GetValueInt();
	outMobData.bodyAttack = inNode["bodyAttack"].GetValueInt();
	outMobData.maxHp = inNode["maxHP"].GetValueInt();
	outMobData.maxMp = inNode["maxMP"].GetValueInt();
	outMobData.speed = inNode["speed"].GetValueInt();
	outMobData.PADamge = inNode["PADamage"].GetValueInt();
	outMobData.PDDamge = inNode["PDDamage"].GetValueInt();
	outMobData.PDRate = inNode["PDRate"].GetValueInt();
	outMobData.MADamge = inNode["MADamage"].GetValueInt();
	outMobData.MDDamge = inNode["MDDamage"].GetValueInt();
	outMobData.MDRate = inNode["MDRate"].GetValueInt();
	outMobData.acc = inNode["acc"].GetValueInt();
	outMobData.eva = inNode["eva"].GetValueInt();
	outMobData.pushed = inNode["pushed"].GetValueInt();
	outMobData.fs = inNode["fs"].GetValueInt();
	outMobData.exp = inNode["exp"].GetValueInt();
	outMobData.category = inNode["category"].GetValueInt();
}
