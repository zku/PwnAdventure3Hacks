#pragma once

// Windows.
#include <Windows.h>

// Standard.
#include <string>
#include <map>
#include <set>
#include <functional>
#include <vector>
#include <stddef.h>

namespace pwny
{
	// Classes extracted from binary, ugly and incomplete.
	// Only works if you use the proper MSVC runtime (e.g. with VS2013).

	struct Rotation;
	struct Vector3;
	struct IPlayer;
	struct Player;
	struct IActor;
	struct Actor;
	struct World;
	struct Socket;
	struct AIZoneListener;
	struct AIZone;
	struct GameAPI;
	struct IQuest;
	struct IAchievement;
	struct IFastTravel;
	struct IQuestState;
	struct IUE4Actor;
	struct IInventory;
	struct IItem;

	struct Rotation
	{
		float pitch;
		float yaw;
		float roll;
	};

	struct Vector3
	{
		float x;
		float y;
		float z;

		inline bool IsExactZero() const 
		{
			return x == 0 && y == 0 && z == 0;
		}
	};

	enum DamageType
	{
		PhysicalDamage = 0x0,
		FireDamage = 0x1,
		ColdDamage = 0x2,
		ShockDamage = 0x3,
	};

	enum ItemRarity
	{
		ResourceItem = 0x0,
		NormalItem = 0x1,
		RareItem = 0x2,
		LegendaryItem = 0x3,
		LeetItem = 0x4,
	};

	struct IItemVtbl
	{
		void *(__thiscall *__vecDelDtor)(IItem *pThis, unsigned int);
		const char *(__thiscall *GetName)(IItem *pThis);
		const char *(__thiscall *GetDisplayName)(IItem *pThis);
		const char *(__thiscall *GetItemTypeName)(IItem *pThis);
		const char *(__thiscall *GetDescription)(IItem *pThis);
		const char *(__thiscall *GetFlavorText)(IItem *pThis);
		bool(__thiscall *CanEquip)(IItem *pThis);
		unsigned int(__thiscall *GetMaximumCount)(IItem *pThis);
		bool(__thiscall *CanActivate)(IItem *pThis, IPlayer *);
		bool(__thiscall *CanActivateInInventory)(IItem *pThis);
		void(__thiscall *Activate)(IItem *pThis, IPlayer *);
		bool(__thiscall *ShowInInventory)(IItem *pThis);
		bool(__thiscall *ShowEventOnPickup)(IItem *pThis);
		bool(__thiscall *ShowEventOnDuplicatePickup)(IItem *pThis);
		bool(__thiscall *ShowNotificationOnPickup)(IItem *pThis);
		float(__thiscall *GetCooldownTime)(IItem *pThis);
		ItemRarity(__thiscall *GetItemRarity)(IItem *pThis);
		IItem *(__thiscall *GetAmmoType)(IItem *pThis);
		unsigned int(__thiscall *GetClipSize)(IItem *pThis);
		int(__thiscall *GetDamage)(IItem *pThis);
		int(__thiscall *GetDamagePerSecond)(IItem *pThis);
		DamageType(__thiscall *GetDamageType)(IItem *pThis);
		int(__thiscall *GetManaCost)(IItem *pThis);
		const char *(__thiscall *GetCustomCostDescription)(IItem *pThis);
		bool(__thiscall *IsAutoFire)(IItem *pThis);
		unsigned int(__thiscall *GetNumberOfProjectiles)(IItem *pThis);
		float(__thiscall *GetReloadTime)(IItem *pThis, int);
		bool(__thiscall *HasPartialReload)(IItem *pThis);
		float(__thiscall *GetRange)(IItem *pThis);
		int(__thiscall *GetTradeValue)(IItem *pThis);
		bool(__thiscall *IsDynamic)(IItem *pThis);
		bool(__thiscall *IsUpdating)(IItem *pThis);
	};

	struct IItem
	{
		IItemVtbl *vfptr;
	};


	struct Item
	{
		IItem baseclass_0;
	};


	struct IUE4ActorVtbl
	{
		void *(__thiscall *GetUE4Actor)(IUE4Actor *pThis);
		void(__thiscall *RemoveFromWorld)(IUE4Actor *pThis);
		Vector3 *(__thiscall *GetPosition)(IUE4Actor *pThis, Vector3 *result);
		Rotation *(__thiscall *GetRotation)(IUE4Actor *pThis, Rotation *result);
		Vector3 *(__thiscall *GetProjectilePosition)(IUE4Actor *pThis, Vector3 *result);
		Vector3 *(__thiscall *GetCharacterVelocity)(IUE4Actor *pThis, Vector3 *result);
		void(__thiscall *SetPosition)(IUE4Actor *pThis, Vector3 *);
		void(__thiscall *SetRotation)(IUE4Actor *pThis, Rotation *);
		void(__thiscall *SetCharacterVelocity)(IUE4Actor *pThis, Vector3 *);
		void(__thiscall *SetForwardAndStrafeMovement)(IUE4Actor *pThis, float, float);
		void(__thiscall *InterpolatePositionAndRotation)(IUE4Actor *pThis, Vector3 *, Rotation *, float, float);
		bool(__thiscall *MoveToLocation)(IUE4Actor *pThis, Vector3 *);
		bool(__thiscall *MoveToRandomLocationInRadius)(IUE4Actor *pThis, float);
		bool(__thiscall *MoveToActor)(IUE4Actor *pThis, IActor *);
		void(__thiscall *OnUpdateState)(IUE4Actor *pThis, const char *, bool);
		void(__thiscall *OnTriggerEvent)(IUE4Actor *pThis, const char *, IActor *);
		void(__thiscall *OnUpdatePvPEnabled)(IUE4Actor *pThis, bool);
		IActor *(__thiscall *LineTraceTo)(IUE4Actor *pThis, Vector3 *);
		void(__thiscall *FireBullets)(IUE4Actor *pThis, IItem *, int, DamageType, Vector3 *, unsigned int, float);
		void(__thiscall *LocalRespawn)(IUE4Actor *pThis, Vector3 *, Rotation *);
		bool(__thiscall *IsOnGround)(IUE4Actor *pThis);
		void(__thiscall *OnReload)(IUE4Actor *pThis, unsigned int);
	};

	struct IUE4Actor
	{
		IUE4ActorVtbl *vfptr;
	};


	struct ILocalPlayer
	{
		IUE4Actor baseclass_0;
	};

	struct IFastTravelVtbl
	{
		void *(__thiscall *__vecDelDtor)(IFastTravel *pThis, unsigned int);
		unsigned int(__thiscall *GetCount)(IFastTravel *pThis);
		const char *(__thiscall *GetRegionName)(IFastTravel *pThis, unsigned int);
		const char *(__thiscall *GetDisplayName)(IFastTravel *pThis, unsigned int);
		void(__thiscall *Destroy)(IFastTravel *pThis);
	};

	struct IFastTravel
	{
		IFastTravelVtbl *vfptr;
	};

	struct IInventoryVtbl
	{
		void *(__thiscall *__vecDelDtor)(IInventory *pThis, unsigned int);
		unsigned int(__thiscall *GetCount)(IInventory *pThis);
		IItem *(__thiscall *GetItem)(IInventory *pThis, unsigned int);
		unsigned int(__thiscall *GetItemCount)(IInventory *pThis, unsigned int);
		unsigned int(__thiscall *GetItemLoadedAmmo)(IInventory *pThis, unsigned int);
		void(__thiscall *Destroy)(IInventory *pThis);
	};

	struct IInventory
	{
		IInventoryVtbl *vfptr;
	};

	struct IQuestStateVtbl
	{
		const char *(__thiscall *GetName)(IQuestState *pThis);
		const char *(__thiscall *GetDescription)(IQuestState *pThis);
		void(__thiscall *CheckForEarlyCompletion)(IQuestState *pThis, IPlayer *);
		void(__thiscall *OnItemAcquired)(IQuestState *pThis, IPlayer *, IItem *);
		void(__thiscall *OnItemPickupUsed)(IQuestState *pThis, IPlayer *, const char *);
	};

	struct IQuestState
	{
		IQuestStateVtbl *vfptr;
	};

	struct IQuestVtbl
	{
		const char *(__thiscall *GetName)(IQuest *pThis);
		const char *(__thiscall *GetDescription)(IQuest *pThis);
		IQuestState *(__thiscall *GetStartingState)(IQuest *pThis);
		IQuestState *(__thiscall *GetStateByName)(IQuest *pThis, const char *);
	};

	struct IQuest
	{
		IQuestVtbl *vfptr;
	};

	struct PlayerQuestState
	{
		IQuestState *state;
		unsigned int count;
	};

	struct IAchievementVtbl
	{
		const char *(__thiscall *GetName)(IAchievement *pThis);
		const char *(__thiscall *GetDisplayName)(IAchievement *pThis);
		const char *(__thiscall *GetDescription)(IAchievement *pThis);
	};

	struct IAchievement
	{
		IAchievementVtbl *vfptr;
	};

	struct IPlayerVtbl
	{
		IActor *(__thiscall *GetActorInterface)(IPlayer *pThis);
		bool(__thiscall *IsLocalPlayer)(IPlayer *pThis);
		ILocalPlayer *(__thiscall *GetLocalPlayer)(IPlayer *pThis);
		const char *(__thiscall *GetPlayerName)(IPlayer *pThis);
		const char *(__thiscall *GetTeamName)(IPlayer *pThis);
		char(__thiscall *GetAvatarIndex)(IPlayer *pThis);
		const unsigned int *(__thiscall *GetColors)(IPlayer *pThis);
		bool(__thiscall *IsPvPDesired)(IPlayer *pThis);
		void(__thiscall *SetPvPDesired)(IPlayer *pThis, bool);
		IInventory *(__thiscall *GetInventory)(IPlayer *pThis);
		unsigned int(__thiscall *GetItemCount)(IPlayer *pThis, IItem *);
		unsigned int(__thiscall *GetLoadedAmmo)(IPlayer *pThis, IItem *);
		bool(__thiscall *AddItem)(IPlayer *pThis, IItem *, unsigned int, bool);
		bool(__thiscall *RemoveItem)(IPlayer *pThis, IItem *, unsigned int);
		bool(__thiscall *AddLoadedAmmo)(IPlayer *pThis, IItem *, IItem *, unsigned int);
		bool(__thiscall *RemoveLoadedAmmo)(IPlayer *pThis, IItem *, unsigned int);
		IItem *(__thiscall *GetItemForSlot)(IPlayer *pThis, unsigned int);
		void(__thiscall *EquipItem)(IPlayer *pThis, unsigned int, IItem *);
		unsigned int(__thiscall *GetCurrentSlot)(IPlayer *pThis);
		void(__thiscall *SetCurrentSlot)(IPlayer *pThis, unsigned int);
		IItem *(__thiscall *GetCurrentItem)(IPlayer *pThis);
		int(__thiscall *GetMana)(IPlayer *pThis);
		bool(__thiscall *UseMana)(IPlayer *pThis, int);
		void(__thiscall *SetItemCooldown)(IPlayer *pThis, IItem *, float, bool);
		bool(__thiscall *IsItemOnCooldown)(IPlayer *pThis, IItem *);
		float(__thiscall *GetItemCooldown)(IPlayer *pThis, IItem *);
		bool(__thiscall *HasPickedUp)(IPlayer *pThis, const char *);
		void(__thiscall *MarkAsPickedUp)(IPlayer *pThis, const char *);
		IQuest **(__thiscall *GetQuestList)(IPlayer *pThis, unsigned int *);
		void(__thiscall *FreeQuestList)(IPlayer *pThis, IQuest **);
		IQuest *(__thiscall *GetCurrentQuest)(IPlayer *pThis);
		void(__thiscall *SetCurrentQuest)(IPlayer *pThis, IQuest *);
		PlayerQuestState(__thiscall *GetStateForQuest)(IPlayer *pThis, IQuest *);
		void(__thiscall *StartQuest)(IPlayer *pThis, IQuest *);
		void(__thiscall *AdvanceQuestToState)(IPlayer *pThis, IQuest *, IQuestState *);
		void(__thiscall *CompleteQuest)(IPlayer *pThis, IQuest *);
		bool(__thiscall *IsQuestStarted)(IPlayer *pThis, IQuest *);
		bool(__thiscall *IsQuestCompleted)(IPlayer *pThis, IQuest *);
		void(__thiscall *EnterAIZone)(IPlayer *pThis, const char *);
		void(__thiscall *ExitAIZone)(IPlayer *pThis, const char *);
		void(__thiscall *UpdateCountdown)(IPlayer *pThis, int);
		bool(__thiscall *CanReload)(IPlayer *pThis);
		void(__thiscall *RequestReload)(IPlayer *pThis);
		float(__thiscall *GetWalkingSpeed)(IPlayer *pThis);
		float(__thiscall *GetSprintMultiplier)(IPlayer *pThis);
		float(__thiscall *GetJumpSpeed)(IPlayer *pThis);
		float(__thiscall *GetJumpHoldTime)(IPlayer *pThis);
		bool(__thiscall *CanJump)(IPlayer *pThis);
		void(__thiscall *SetJumpState)(IPlayer *pThis, bool);
		void(__thiscall *SetSprintState)(IPlayer *pThis, bool);
		void(__thiscall *SetFireRequestState)(IPlayer *pThis, bool);
		void(__thiscall *TransitionToNPCState)(IPlayer *pThis, const char *);
		void(__thiscall *BuyItem)(IPlayer *pThis, IActor *, IItem *, unsigned int);
		void(__thiscall *SellItem)(IPlayer *pThis, IActor *, IItem *, unsigned int);
		void(__thiscall *EnterRegion)(IPlayer *pThis, const char *);
		void(__thiscall *Respawn)(IPlayer *pThis);
		void(__thiscall *Teleport)(IPlayer *pThis, const char *);
		void(__thiscall *Chat)(IPlayer *pThis, const char *);
		IFastTravel *(__thiscall *GetFastTravelDestinations)(IPlayer *pThis, const char *);
		void(__thiscall *FastTravel)(IPlayer *pThis, const char *, const char *);
		void(__thiscall *MarkAsAchieved)(IPlayer *pThis, IAchievement *);
		bool(__thiscall *HasAchieved)(IPlayer *pThis, IAchievement *);
		void(__thiscall *SubmitDLCKey)(IPlayer *pThis, const char *);
		unsigned int(__thiscall *GetCircuitInputs)(IPlayer *pThis, const char *);
		void(__thiscall *SetCircuitInputs)(IPlayer *pThis, const char *, unsigned int);
		void(__thiscall *GetCircuitOutputs)(IPlayer *pThis, const char *, bool *, unsigned int);
	};

	struct IPlayer
	{
		IPlayerVtbl *vfptr;

		Player* GetPlayer() const;
	};

	struct IActorVtbl
	{
		void *(__thiscall *__vecDelDtor)(IActor *pThis, unsigned int);
		IUE4Actor *(__thiscall *GetUE4Actor)(IActor *pThis);
		bool(__thiscall *IsNPC)(IActor *pThis);
		bool(__thiscall *IsPlayer)(IActor *pThis);
		IPlayer *(__thiscall *GetPlayerInterface)(IActor *pThis);
		void(__thiscall *AddRef)(IActor *pThis);
		void(__thiscall *Release)(IActor *pThis);
		void(__thiscall *OnSpawnActor)(IActor *pThis, IUE4Actor *);
		void(__thiscall *OnDestroyActor)(IActor *pThis);
		const char *(__thiscall *GetBlueprintName)(IActor *pThis);
		bool(__thiscall *IsCharacter)(IActor *pThis);
		bool(__thiscall *CanBeDamaged)(IActor *pThis, IActor *);
		int(__thiscall *GetHealth)(IActor *pThis);
		int(__thiscall *GetMaxHealth)(IActor *pThis);
		void(__thiscall *Damage)(IActor *pThis, IActor *, IItem *, int, DamageType);
		void(__thiscall *Tick)(IActor *pThis, float);
		bool(__thiscall *CanUse)(IActor *pThis, IPlayer *);
		void(__thiscall *OnUse)(IActor *pThis, IPlayer *);
		void(__thiscall *OnHit)(IActor *pThis, IActor *, Vector3 *, Vector3 *);
		void(__thiscall *OnAIMoveComplete)(IActor *pThis);
		const char *(__thiscall *GetDisplayName)(IActor *pThis);
		bool(__thiscall *IsElite)(IActor *pThis);
		bool(__thiscall *IsPvPEnabled)(IActor *pThis);
		IItem **(__thiscall *GetShopItems)(IActor *pThis, unsigned int *);
		void(__thiscall *FreeShopItems)(IActor *pThis, IItem **);
		int(__thiscall *GetBuyPriceForItem)(IActor *pThis, IItem *);
		int(__thiscall *GetSellPriceForItem)(IActor *pThis, IItem *);
		Vector3 *(__thiscall *GetLookPosition)(IActor *pThis, Vector3 *result);
		Rotation *(__thiscall *GetLookRotation)(IActor *pThis, Rotation *result);
		IActor *(__thiscall *GetOwner)(IActor *pThis);
	};

	struct IActor
	{
		IActorVtbl *vfptr;
	};

	struct TimerSet
	{
		struct TimerEvent
		{
			float timeLeft;
			float initialTime;
			bool recurring;
			bool withContext;
			std::function<void __cdecl(void)> callback;
			std::function<void __cdecl(Actor *)> contextCallback;
		};

		std::map <std::string, TimerEvent> m_timers;
	};

	template <typename T>
	struct ActorRef
	{
		T *m_object;
	};

	struct AIZone
	{
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_name;
		unsigned int m_playerCount;
		std::set<AIZoneListener *, std::less<AIZoneListener *>, std::allocator<AIZoneListener *> > m_listeners;
	};

	struct AIZoneListenerVtbl
	{
		void *(__thiscall *__vecDelDtor)(AIZoneListener *pThis, unsigned int);
		void(__thiscall *OnAIZoneActivated)(AIZoneListener *pThis);
		void(__thiscall *OnAIZoneDeactivated)(AIZoneListener *pThis);
	};

	struct AIZoneListener
	{
		AIZoneListenerVtbl *vfptr;
		AIZone *m_zone;
	};

	struct Spawner
	{
		AIZoneListener baseclass_0;
		std::vector<ActorRef<Actor>, std::allocator<ActorRef<Actor> > > m_actors;
		Vector3 m_position;
		Rotation m_rotation;
		unsigned int m_maxActors;
		float m_maxSpawnTimer;
		float m_currentSpawnTimer;
	};

	struct Actor
	{
		IActor baseclass_0;
		unsigned int m_refs;
		unsigned int m_id;
		IUE4Actor *m_target;
		TimerSet *m_timers;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_blueprintName;
		ActorRef<IActor> m_owner;
		int m_health;
		std::map < std::string, bool> m_states;
		float m_forwardMovementFraction;
		float m_strafeMovementFraction;
		Vector3 m_remotePosition;
		Vector3 m_remoteVelocity;
		Rotation m_remoteRotation;
		float m_remoteLocationBlendFactor;
		Spawner *m_spawner;
	};

	struct ItemAndCount
	{
		IItem *item;
		unsigned int count;
		unsigned int loadedAmmo;
	};

	enum NPCStateTransitionType
	{
		EndConversationTransition = 0x0,
		ContinueConversationTransition = 0x1,
		ShopTransition = 0x2,
	};

	struct NPCStateTransition
	{
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
		NPCStateTransitionType type;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > nextState;
	};

	struct NPCState
	{
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
		std::vector<NPCStateTransition, std::allocator<NPCStateTransition> > transitions;
	};

	struct NPC
	{
		Actor baseclass_0;
		std::map < std::string, NPCState > m_states;
	};

	struct SocketVtbl
	{
		void *(__thiscall *__vecDelDtor)(Socket *pThis, unsigned int);
		bool(__thiscall *Read)(Socket *pThis, void *, unsigned int);
		bool(__thiscall *Write)(Socket *pThis, const void *, unsigned int);
	};

	struct Socket
	{
		SocketVtbl *vfptr;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_lastErrorMessage;
	};

	struct WriteStream
	{
		Socket *m_sock;
		std::vector<unsigned char, std::allocator<unsigned char> > m_buffer;
	};

	struct Player
	{
		Actor baseclass_0;
		IPlayer baseclass_70;
		unsigned int m_characterId;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_playerName;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_teamName;
		char m_avatarIndex;
		unsigned int m_colors[4];
		std::map<IItem *, ItemAndCount, std::less<IItem *>, std::allocator<std::pair<IItem * const, ItemAndCount> > > m_inventory;
		std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > m_pickups;
		std::map<IItem *, float, std::less<IItem *>, std::allocator<std::pair<IItem * const, float> > > m_cooldowns;
		std::map < std::string, unsigned int > m_circuitInputs;
		std::map < std::string, std::vector<bool, std::allocator<bool> >> m_circuitOutputs;
		bool m_admin;
		bool m_pvpEnabled;
		bool m_pvpDesired;
		float m_pvpChangeTimer;
		int m_pvpChangeReportedTimer;
		bool m_changingServerRegion;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_currentRegion;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_changeRegionDestination;
		std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > m_aiZones;
		int m_mana;
		float m_manaRegenTimer;
		float m_healthRegenCooldown;
		float m_healthRegenTimer;
		int m_countdown;
		Vector3 m_remoteLookPosition;
		Rotation m_remoteLookRotation;
		IItem *m_equipped[10];
		unsigned int m_currentSlot;
		std::map<IQuest *, PlayerQuestState, std::less<IQuest *>, std::allocator<std::pair<IQuest * const, PlayerQuestState> > > m_questStates;
		IQuest *m_currentQuest;
		float m_walkingSpeed;
		float m_jumpSpeed;
		float m_jumpHoldTime;
		ActorRef<NPC> m_currentNPC;
		std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_currentNPCState;
		ILocalPlayer *m_localPlayer;
		WriteStream *m_eventsToSend;
		bool m_itemsUpdated;
		float m_itemSyncTimer;
		unsigned int m_chatMessageCounter;
		float m_chatFloodDecayTimer;
		IItem *m_lastHitByItem;
		float m_lastHitItemTimeLeft;
		float m_circuitStateCooldownTimer;
	};

	struct WorldVtbl
	{
		void *(__thiscall *__vecDelDtor)(World *pThis, unsigned int);
		void(__thiscall *Tick)(World *pThis, float);
		bool(__thiscall *HasLocalPlayer)(World *pThis);
		bool(__thiscall *IsAuthority)(World *pThis);
		void(__thiscall *AddLocalPlayer)(World *pThis, Player *, ILocalPlayer *);
		void(__thiscall *AddRemotePlayer)(World *pThis, Player *);
		void(__thiscall *AddRemotePlayerWithId)(World *pThis, unsigned int, Player *);
		void(__thiscall *RemovePlayer)(World *pThis, Player *);
		void(__thiscall *Use)(World *pThis, Player *, Actor *);
		void(__thiscall *Activate)(World *pThis, Player *, IItem *);
		void(__thiscall *Reload)(World *pThis, Player *);
		void(__thiscall *Jump)(World *pThis, bool);
		void(__thiscall *Sprint)(World *pThis, bool);
		void(__thiscall *FireRequest)(World *pThis, bool);
		void(__thiscall *TransitionToNPCState)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *BuyItem)(World *pThis, Player *, Actor *, IItem *, unsigned int);
		void(__thiscall *SellItem)(World *pThis, Player *, Actor *, IItem *, unsigned int);
		void(__thiscall *Respawn)(World *pThis, Player *);
		void(__thiscall *Teleport)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *Chat)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *FastTravel)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *SetPvPDesired)(World *pThis, Player *, bool);
		void(__thiscall *SubmitDLCKey)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *SetCircuitInputs)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, unsigned int);
		void(__thiscall *SendAddItemEvent)(World *pThis, Player *, IItem *, unsigned int);
		void(__thiscall *SendRemoveItemEvent)(World *pThis, Player *, IItem *, unsigned int);
		void(__thiscall *SendLoadedAmmoEvent)(World *pThis, Player *, IItem *, unsigned int);
		void(__thiscall *SendPickedUpEvent)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *EquipItem)(World *pThis, Player *, char, IItem *);
		void(__thiscall *SetCurrentSlot)(World *pThis, Player *, char);
		void(__thiscall *SendEquipItemEvent)(World *pThis, Player *, char, IItem *);
		void(__thiscall *SendCurrentSlotEvent)(World *pThis, Player *, char);
		void(__thiscall *SetCurrentQuest)(World *pThis, Player *, IQuest *);
		void(__thiscall *SendSetCurrentQuestEvent)(World *pThis, Player *, IQuest *);
		void(__thiscall *SendStartQuestEvent)(World *pThis, Player *, IQuest *);
		void(__thiscall *SendAdvanceQuestToStateEvent)(World *pThis, Player *, IQuest *, IQuestState *);
		void(__thiscall *SendCompleteQuestEvent)(World *pThis, Player *, IQuest *);
		void(__thiscall *SendHealthUpdateEvent)(World *pThis, Actor *, int);
		void(__thiscall *SendManaUpdateEvent)(World *pThis, Player *, int);
		void(__thiscall *SendCountdownUpdateEvent)(World *pThis, Player *, int);
		void(__thiscall *SendPvPCountdownUpdateEvent)(World *pThis, Player *, bool, int);
		void(__thiscall *SendPvPEnableEvent)(World *pThis, Player *, bool);
		void(__thiscall *SendStateEvent)(World *pThis, Actor *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, bool);
		void(__thiscall *SendTriggerEvent)(World *pThis, Actor *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, Actor *, bool);
		void(__thiscall *SendFireBulletsEvent)(World *pThis, Actor *, IItem *, Vector3 *, unsigned int, float);
		void(__thiscall *SendDisplayEvent)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *SendNPCConversationStateEvent)(World *pThis, Player *, Actor *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *SendNPCConversationEndEvent)(World *pThis, Player *);
		void(__thiscall *SendNPCShopEvent)(World *pThis, Player *, Actor *);
		void(__thiscall *SendRespawnEvent)(World *pThis, Player *, Vector3 *, Rotation *);
		void(__thiscall *SendTeleportEvent)(World *pThis, Actor *, Vector3 *, Rotation *);
		void(__thiscall *SendRelativeTeleportEvent)(World *pThis, Actor *, Vector3 *);
		void(__thiscall *SendReloadEvent)(World *pThis, Player *, IItem *, IItem *, unsigned int);
		void(__thiscall *SendPlayerJoinedEvent)(World *pThis, Player *);
		void(__thiscall *SendPlayerLeftEvent)(World *pThis, Player *);
		void(__thiscall *SendPlayerItemEvent)(World *pThis, Player *);
		void(__thiscall *SendActorSpawnEvent)(World *pThis, Actor *);
		void(__thiscall *SendActorDestroyEvent)(World *pThis, Actor *);
		void(__thiscall *SendExistingPlayerEvent)(World *pThis, Player *, Player *);
		void(__thiscall *SendExistingActorEvent)(World *pThis, Player *, Actor *);
		void(__thiscall *SendChatEvent)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *SendKillEvent)(World *pThis, Player *, Actor *, IItem *);
		void(__thiscall *SendCircuitOutputEvent)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, unsigned int, std::vector<bool, std::allocator<bool> > *);
		void(__thiscall *SendActorPositionEvents)(World *pThis, Player *);
		void(__thiscall *SendRegionChangeEvent)(World *pThis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
		void(__thiscall *SendLastHitByItemEvent)(World *pThis, Player *, IItem *);
	};

	struct World
	{
		WorldVtbl *vfptr;
		std::set<ActorRef<IPlayer>, std::less<ActorRef<IPlayer> >, std::allocator<ActorRef<IPlayer> > > m_players;
		std::set<ActorRef<IActor>, std::less<ActorRef<IActor> >, std::allocator<ActorRef<IActor> > > m_actors;
		std::map<unsigned int, ActorRef<IActor>, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, ActorRef<IActor> > > > m_actorsById;
		ILocalPlayer *m_localPlayer;
		unsigned int m_nextId;
		std::map < std::string, AIZone * > m_aiZones;
	};

	struct LocationAndRotation
	{
		Vector3 location;
		Rotation rotation;
	};

	struct CharacterInfo
	{
		int id;
		const char *name;
		const char *location;
		char avatar;
		unsigned int colors[4];
		unsigned int flags;
	};

	struct GameAPIVtbl
	{
		bool(__thiscall *SpawnActor)(GameAPI *pThis, IActor *, Vector3 *, Rotation *, bool);
		bool(__thiscall *SpawnActorAtNamedLocation)(GameAPI *pThis, IActor *, const char *);
		bool(__thiscall *SpawnRemotePlayer)(GameAPI *pThis, IPlayer *, Vector3 *, Rotation *);
		void(__thiscall *DamageInRadius)(GameAPI *pThis, IActor *, IItem *, Vector3 *, float, int, DamageType);
		unsigned int(__thiscall *GetNamedLocationPoints)(GameAPI *pThis, const char *, LocationAndRotation **);
		void(__thiscall *FreeNamedLocationPoints)(GameAPI *pThis, LocationAndRotation *);
		Vector3 *(__thiscall *GetDirectionFromRotation)(GameAPI *pThis, Vector3 *result, Rotation *);
		Rotation *(__thiscall *GetRotationFromDirection)(GameAPI *pThis, Rotation *result, Vector3 *);
		void(__thiscall *OnWeaponFired)(GameAPI *pThis, IItem *, Vector3 *, Vector3 *);
		void(__thiscall *OnBulletHitActor)(GameAPI *pThis, IItem *, IActor *, Vector3 *, Vector3 *);
		void(__thiscall *OnBulletHitWorld)(GameAPI *pThis, IItem *, Vector3 *, Vector3 *);
		void(__thiscall *OnLog)(GameAPI *pThis, const char *);
		void(__thiscall *OnMasterServerConnected)(GameAPI *pThis, bool, const char *, const char *);
		void(__thiscall *OnLoginComplete)(GameAPI *pThis, bool, const char *, bool, CharacterInfo *, unsigned int);
		void(__thiscall *OnRegisterComplete)(GameAPI *pThis, bool, const char *, const char *, bool);
		void(__thiscall *OnCreateCharacterComplete)(GameAPI *pThis, bool, const char *, int);
		void(__thiscall *OnDeleteCharacterComplete)(GameAPI *pThis, bool, int);
		void(__thiscall *OnJoinGameServerComplete)(GameAPI *pThis, bool, const char *, bool, const char *, unsigned __int16, const char *);
		void(__thiscall *OnGameServerConnected)(GameAPI *pThis, bool, const char *, Vector3 *, Rotation *);
		void(__thiscall *OnTransitionToNewServer)(GameAPI *pThis);
		void(__thiscall *OnSubmitAnswerComplete)(GameAPI *pThis, bool, const char *);
		void(__thiscall *OnTeammatesListed)(GameAPI *pThis, const char **, const char **, unsigned int);
		unsigned int(__thiscall *GetDefaultCircuitInputs)(GameAPI *pThis, const char *);
		unsigned int(__thiscall *GetCircuitOutputCount)(GameAPI *pThis, const char *);
		void(__thiscall *GetCircuitOutputs)(GameAPI *pThis, const char *, unsigned int, bool *, unsigned int, bool *);
	};

	struct GameAPI
	{
		GameAPIVtbl *vfptr;

		std::vector<LocationAndRotation> GetNamedLocationPointList(std::string const& location);
	};

	struct Offsets
	{
		enum
		{
			kWorld = 0x00097D7C,
			kGameAPI = 0x00097D80,
			kPlayer = 0x00097E48,
			kGameAPI_Tick = 0x0001DBD0
		};
	};

	// Get the address of where GameLogic.dll is loaded in memory.
	DWORD GetModuleBaseAddress();

	// Rebase an address relative to the GameLogic.dll module to an absolute address.
	DWORD Rebase(DWORD address);

	// Get the global GameAPI object.
	GameAPI* GetGameAPIObject();

	// Get the global World object.
	World* GetWorldObject();

	// Get the connected player object.
	IPlayer* GetMe();

	// Lets make sure we are using the proper runtime and that the sizes add up!
	// Even if these sizes add up, it might still crash and burn. MSVC interop between 2 runtimes is.. interesting.
	static_assert(sizeof(std::map<IQuest *, PlayerQuestState, std::less<IQuest *>, std::allocator<std::pair<IQuest * const, PlayerQuestState> > >) == 8, "Bad std::map size.");
	static_assert(sizeof(std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >) == 8, "Bad std::set size.");
	static_assert(sizeof(Player) == 0x1DC, "Player size incorrect.");
	static_assert(offsetof(Player, m_admin) == 0xe4, "Player::m_admin");
	static_assert(offsetof(Player, m_mana) == 0x12c, "Player::m_mana");
	static_assert(offsetof(Player, m_eventsToSend) == 0x1bc, "Player::m_eventsToSend");
	static_assert(offsetof(Player, m_circuitStateCooldownTimer) == 0x1d8, "Player::m_circuitStateCooldownTimer");
	static_assert(offsetof(Actor, m_health) == 0x30, "Actor::m_health");
} // pwny