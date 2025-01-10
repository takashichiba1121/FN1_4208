#include "EditorTicket.h"
#include "StageManager.h"
#include "Player.h"
#include "Block.h"
#include "Goal.h"
#include "levitationBlock.h"
#include "BreakBlock.h"
#include "Water.h"
#include "Window.h"
#include "Key.h"
#include "SpongeBlock.h"
#include "Drain.h"
#include "TutorialObject.h"
#include "Water.h"

namespace EditContent
{

	void AddObject::Undo()
	{
		StageManager::GetInstance()->stageObjData_.pop_back();
	}

	void AddObject::Redo()
	{
		

		std::shared_ptr<Object> addobj = std::move(object_);

		StageManager::GetInstance()->stageObjData_.push_back(std::move(addobj));

	}

	void AddObject::SaveData()
	{
		object_ = StageManager::GetInstance()->stageObjData_.back().get()->Clone();
	}

	void DeleteObject::Undo()
	{
		int32_t count = 0;

		std::shared_ptr<Object> addobj = std::move(object_);

		if (StageManager::GetInstance()->stageObjData_.size() == 0)
		{
			StageManager::GetInstance()->stageObjData_.push_back(std::move(addobj));
			return;
		}

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (count == num_-1)
			{
				StageManager::GetInstance()->stageObjData_.insert(objectI, std::move(addobj));
				break;
			}
			else if (num_ == StageManager::GetInstance()->stageObjData_.size())
			{
				StageManager::GetInstance()->stageObjData_.push_back(std::move(addobj));
				break;
			}
			count++;
		}
	}

	void DeleteObject::Redo()
	{
		int32_t count = 0;

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (count == num_)
			{
				StageManager::GetInstance()->stageObjData_.erase(objectI);
				break;
			}
			count++;
		}
	}

	void DeleteObject::SaveData(Object* object, int32_t num)
	{
		object_ = std::move(object->Clone());
		num_ = num;
	}

	void MoveTransform::Undo()
	{
		int32_t count = 0;

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (count == num_)
			{
				objectI->get()->SetPos(oldPos_);
				objectI->get()->SetSize(oldSize_);
				break;
			}
			count++;
		}
	}

	void MoveTransform::Redo()
	{
		int32_t count = 0;

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (count == num_)
			{
				objectI->get()->SetPos(pos_);
				objectI->get()->SetSize(size_);
				break;
			}
			count++;
		}
	}

	void MoveTransform::SaveData(TicketData data, int32_t num)
	{
		pos_ = data.object->GetPos();
		size_ = data.object->GetSize();

		oldPos_ = data.pos;
		oldSize_ = data.size;

		num_ = num;
	}

	void ChangeObjectType::Undo()
	{
		int32_t count = 0;

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (count == num_)
			{
				StageManager::GetInstance()->ChengeTag(objectI, oldType_);
				break;
			}
			count++;
		}
	}

	void ChangeObjectType::Redo()
	{
		int32_t count = 0;

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (count == num_)
			{
				StageManager::GetInstance()->ChengeTag(objectI, type_);
				break;
			}
			count++;
		}
	}

	void ChangeObjectType::SaveData(ObjectType type, ObjectType oldType, int32_t num)
	{
		type_ = type;
		oldType_ = oldType;
		num_ = num;
	}

}