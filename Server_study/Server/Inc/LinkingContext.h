//링킹
//어떤 데이터는 하나 이상의 포인터로 여러 곳에서 참조되는 경우가 있다.
//이걸 기존의 방법대로 복사한다면 원래 하나만 있어야 할 기지 객체가 복원 시 똑같은 내용으로 두개 만들어지는 문제가 생긴다.

//여러번 참조될 법한 객체에 고유 식별자 혹은 ID를 부여해 두었다가 이들 객체를 직렬화 할때 오로지 식별가 값만 직렬화시킨다.
//일단 수신자가 모든 객체 데이터를 복원한뒤, 수정 루틴을 돌려 각 식별자에 대응되는 참조 객체를 찾아 적절한 멤버 변수에 끼워 넣는다.
//이렇게 객체를 사후에 링크, 즉 연결해 주는 방식이므로 이 절차를 링킹 이라 부른다.
#ifndef RoboCat_LinkingContext_h
#define RoboCat_LinkingContext_h

class GameObject;

enum PacketType
{
	PT_HELLO,
	PT_ReplicationData,
	PT_Disconnect,
	PT_MAX
};

class LinkingContext
{
public:

	LinkingContext() :mNextNetworkId(1){}

	uint32_t GetNetworkId(GameObject* inGameObject, bool inShouldCreateIfNotFound)
	{
		auto it = mGameObjectToNetworkIdMap.find(inGameObject);
		if (it != mGameObjectToNetworkIdMap.end())
		{
			return it->second;
		}
		else if (inShouldCreateIfNotFound)
		{
			uint32_t newNetworkId = mNextNetworkId++;
			AddGameObject(inGameObject, newNetworkId);
			return newNetworkId;
		}
		else
		{
			return 0;
		}
	}

	GameObject* GetGameObject(uint32_t inNetworkId) const
	{
		auto it = mNetworkIdToGameObjectMap.find(inNetworkId);
		if (it != mNetworkIdToGameObjectMap.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

	void AddGameObject(GameObject* inGameObject, uint32_t inNetworkId)
	{
		mNetworkIdToGameObjectMap[inNetworkId] = inGameObject;
		mGameObjectToNetworkIdMap[inGameObject] = inNetworkId;
	}

	void RemoveGameObject(GameObject* inGameObject)
	{
		uint32_t networkId = mGameObjectToNetworkIdMap[inGameObject];
		mGameObjectToNetworkIdMap.erase(inGameObject);
		mNetworkIdToGameObjectMap.erase(networkId);
	}

private:
	std::unordered_map< uint32_t, GameObject* > mNetworkIdToGameObjectMap;
	std::unordered_map< const GameObject*, uint32_t > mGameObjectToNetworkIdMap;

	uint32_t mNextNetworkId;
};

#endif
