#include <iostream>
#include <unordered_map>
#include <cassert>

struct Position
{
	float x, y;

	Position() 
		:x(0), y(0)
	{

	}
	Position(float x, float y)
		:x(x), y(y)
	{
	}
};

struct Velocity
{
	float dx, dy;
	Velocity()
		:dx(0.0), dy(0.0)
	{
	}
};

struct Entity
{
private:
	std::unordered_map<size_t, void*> m_Components;

public:
	Entity();
	~Entity();

	template<typename T>
	void AddComponent(T component);

	template<typename T>
	T GetComponent();

};
Entity::Entity()
{
}

Entity::~Entity()
{
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it) 
	{
		delete it->second;
	}
}
template<typename T>
void Entity::AddComponent(T component)
{
	const std::type_info& info = typeid(T);
	int key = info.hash_code();

	// Check if the component already exists
	if (m_Components.count(key) > 0)
	{
		// The component already exists
		std::cout << "The component already exists!" << std::endl;
	}
	else {
		// Attach the component if it does not already exist
		m_Components[key] = new T(component);
	}
}

template<typename T>
T Entity::GetComponent()
{
	const std::type_info& info = typeid(T);
	int key = info.hash_code();

	// Check if the component exists
	if (m_Components.count(key) > 0)
	{
		// The component exists, so return it.
		return *((T*)(m_Components[key]));
	}
	else {
		// The component does not exist.
		std::cout << "The component does not exist!" << std::endl;
		assert(false); // Bomb the program
	}
}

int main()
{
	Entity e;
	e.AddComponent<Position>({ 1.0f, 2.0f });

	Position p = e.GetComponent<Position>();

	std::cout << p.y;

	std::cin.get();
	return 0;
}
