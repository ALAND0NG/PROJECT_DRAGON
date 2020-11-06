//Very very very basic parenting system
#pragma once
//attached to an entity, sets a parent then gets updated in RenderingSystem -> ECSUpdate()
class Parent
{
public:
	
	void SetParent(int Parent)
	{
		m_Parent = Parent;
	}

	int GetParent()
	{
		return m_Parent;
	}


private:
	int m_Parent;
};