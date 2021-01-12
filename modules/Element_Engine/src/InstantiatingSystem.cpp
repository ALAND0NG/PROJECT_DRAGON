#include <InstantiatingSystem.h>

// Borrowed from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
#pragma region String Trimming

// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

#pragma endregion 


std::vector<Prefab*> InstantiatingSystem::m_Prefabs;


void InstantiatingSystem::InitPrefab(int index, glm::vec3 origin)
{
	std::cout << "Loading Prefab\n";
	m_Prefabs[index]->LoadPrefab(ECS::GetSize(), origin);

}

void InstantiatingSystem::AddPrefab(Prefab* prefab)
{
	m_Prefabs.push_back(prefab);
}

void InstantiatingSystem::LoadPrefabFromFile(int index, glm::vec3 origin, std::string filename)
{
	//similar to OBJ loader, lots of if statements there is probably a better way to do this
	std::stringstream ss;
	std::ifstream file;
	file.open(filename, std::ios::binary);

	if (!file)
		throw std::runtime_error("Failed to open file");

	std::string line = "";
	std::string prefix = "";

	while (std::getline(file, line))
	{
		trim(line);
		ss = std::stringstream(line);
		ss >> prefix;
		if (prefix == "#")
		{
			//comment nothing happens
		}
		else if (prefix == "E")
		{
			//create a new entity
			int fileIndex;
			ss >> fileIndex;
			ECS::Create(index + fileIndex);
			std::cout << "Created entity: " << index + fileIndex << "\n";
		}
	}

}
