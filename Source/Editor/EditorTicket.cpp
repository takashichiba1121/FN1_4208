#include "EditorTicket.h"
#include "StageManager.h"
#include "Player.h"
#include "Block.h"
#include "levitationBlock.h"
#include "BreakBlock.h"
#include "Goal.h"

namespace EditContent
{

	void AddObject::Undo()
	{
		StageManager::GetInstance()->stageObjData_.pop_back();
	}

	void AddObject::Redo()
	{
		

		std::unique_ptr<Object> addobj = makeObject(object_);

		StageManager::GetInstance()->stageObjData_.push_back(std::move(addobj));

	}

	void AddObject::SaveData()
	{
		object_ = *StageManager::GetInstance()->stageObjData_.back().get();
	}

	void DeleteObject::Undo()
	{
		int32_t count = 0;

		std::unique_ptr<Object> addobj = makeObject(object_);

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
		object_ = *object;
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

	std::unique_ptr<Object> makeObject(Object& object)
	{

		std::unique_ptr<Object> addObject;
		//ƒ^ƒO‚Ì“à—e‚ÅŒˆ’è
		switch (object.GetObjectType())
		{
		case ObjectType::PLAYER:
			addObject = std::make_unique<Player>();

			break;

		case ObjectType::FLOAT_BLOCK:
			addObject = std::make_unique<LevitationBlock>();
			break;

		case ObjectType::NOT_FLOAT_BLOCK:
			addObject = std::make_unique<Block>();
			break;
		case ObjectType::BREAK_BLOCK:
			addObject = std::make_unique<BreakBlock>();
			break;
		case ObjectType::GOAL:
			addObject = std::make_unique<Goal>();
			break;
		default:
			break;
		}

		addObject->SetCollision(object.IsCollision());
		addObject->SetExclude(object.IsExclude());
		addObject->SetObjectType(object.GetObjectType());
		addObject->SetPos(object.GetPos());
		addObject->SetSize(object.GetSize());

		return std::move(addObject);
	}

}