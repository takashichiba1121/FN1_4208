#pragma once
#include "Object.h"
#include <memory>

class EditorTicket
{
public:
	virtual void Undo() {}
	virtual void Redo() {}
	virtual void SaveData() {}

private:

};

//ˆ—“à—e
namespace EditContent 
{

	enum class Content
	{
		Add,
		Delete,
		Move,
		ChangeTag,
		None
	};

	struct TicketData
	{
		Object* object = nullptr;
		Vector2 pos;
		Vector2 size;

		ObjectType type_ = ObjectType::NONE;
		ObjectType oldType_ = ObjectType::NONE;

		void setData(Object* Obj, Vector2 Pos = {}, Vector2 Size = {}) { object = Obj; pos = Pos; size = Size; }
	};

#include <memory>
	class AddObject:public EditorTicket
	{
	public:
		void Undo()override;
		void Redo()override;

		void SaveData()override;

	private:

		//ˆê•Û—p
		Object object_;

	};

	//‚±‚¢‚Â‚¾‚¯makeuniqe‚Ì‚â‚è•û‚ªˆá‚¤‚Ì‚Å’ˆÓ
	class DeleteObject :public EditorTicket
	{
	public:
		void Undo()override;
		void Redo()override;

		void SaveData(Object* object,int32_t num);

	private:

		//ˆê•Û—p
		Object object_;

		int32_t num_ = 0;

	};

	class MoveTransform :public EditorTicket
	{
	public:
		void Undo()override;
		void Redo()override;

		void SaveData(TicketData data, int32_t num);

	private:

		Vector2 pos_;
		Vector2 size_;

		Vector2 oldPos_;
		Vector2 oldSize_;

		int32_t num_ = 0;

	};

	class ChangeObjectType :public EditorTicket
	{
	public:
		void Undo()override;
		void Redo()override;

		void SaveData(ObjectType type, ObjectType oldType, int32_t num);

	private:

		ObjectType type_ = ObjectType::NONE;
		ObjectType oldType_ = ObjectType::NONE;

		int32_t num_ = 0;

	};

	std::unique_ptr<Object> makeObject(Object& object);

}