#include "Hacks.hpp"

// Standard.
#include <cmath>

// Boost.
#include <boost/format.hpp>

namespace pwny
{
	namespace hacks
	{
		void TeleportToActor(std::string const& name)
		{
			World* GameWorld = GetWorldObject();
			if (!GameWorld) return;

			for (auto const& actorRef : GameWorld->m_actors)
			{
				IActor* actor = actorRef.m_object;
				if (actor != nullptr)
				{
					std::string actorName(actor->vfptr->GetDisplayName(actor));
					if (actorName.find(name) != std::string::npos)
					{
						Vector3 pos;
						actor->vfptr->GetLookPosition(actor, &pos);
						TeleportTo(&pos);
						return;
					}
				}
			}

			Chat("Could not find actor \"" + name + "\"");
		}

		void TeleportTo(Vector3* position)
		{
			IPlayer* me = GetMe();
			if (!me) return;

			Player* playerMe = me->GetPlayer();
			if (!playerMe) return;

			IActor* actorMe = me->vfptr->GetActorInterface(me);
			if (!actorMe) return;

			IUE4Actor* ue4actor = playerMe->baseclass_0.m_target;
			if (!ue4actor) return;

			World* GameWorld = GetWorldObject();
			if (!GameWorld) return;

			//auto const logMsg = boost::str(boost::format("TeleportTo(%.2f,%.2f,%.2f)")
			//	% position->x % position->y % position->z);
			//Chat(logMsg);

			Rotation rot{ 0, 0, 0 };
			GameWorld->vfptr->SendRespawnEvent(GameWorld, me->GetPlayer(), position, &rot);
			ue4actor->vfptr->LocalRespawn(ue4actor, position, &rot);
		}

		void TeleportForward(float distance)
		{
			IPlayer* me = GetMe();
			if (!me) return;

			Player* playerMe = me->GetPlayer();
			if (!playerMe) return;

			IActor* actorMe = me->vfptr->GetActorInterface(me);
			if (!actorMe) return;

			IUE4Actor* ue4actor = playerMe->baseclass_0.m_target;
			if (!ue4actor) return;

			Vector3 position;
			Rotation rotation;
			ue4actor->vfptr->GetPosition(ue4actor, &position);
			ue4actor->vfptr->GetRotation(ue4actor, &rotation);

			// Their angles go from [0, 180) and [-0, -180), convert to [0, 360).
			float facing = rotation.yaw;
			if (facing < 0.0f)
			{
				facing += 360.0f;
			}

			facing = facing * static_cast<float>(M_PI) / 180.0f;
			float const x = std::cos(facing);
			float const y = std::sin(facing);

			position.x += distance * x;
			position.y += distance * y;

			TeleportTo(&position);
		}

		void SetPlayerSpeed(float speed)
		{
			GetMe()->GetPlayer()->m_walkingSpeed = speed;
		}

		void Chat(std::string const& message)
		{
			IPlayer* me = GetMe();
			me->vfptr->Chat(me, message.c_str());
			//me->GetPlayer()->m_chatMessageCounter = 0;
		}

		Vector3 GetNamedLocation(std::string const& location)
		{
			GameAPI* api = GetGameAPIObject();
			auto const points = api->GetNamedLocationPointList(location);
			if (!points.empty())
			{
				// We just need one.
				return points[0].location;
			}

			return Vector3{ 0, 0, 0 };
		}
	} // hacks
} // pwny