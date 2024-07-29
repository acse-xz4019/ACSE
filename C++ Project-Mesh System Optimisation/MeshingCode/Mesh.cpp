#include "Mesh.h"

// Constructor
Mesh::Mesh(const std::vector<Node>& _nodes,
	const std::vector<double>& _temperatures, const std::vector<double>& _pressures)
	: nodes(_nodes),  temperatures(_temperatures), pressures(_pressures)
{
}

// Display mesh information
void Mesh::displayInfo() const
{
	std::cout << "Mesh Information:" << std::endl;
	// Display nodes
	std::cout << "Nodes:" << std::endl;
	for (const auto& node : nodes)
	{
		std::cout << "  (" << node.x << ", " << node.y << ", " << node.z << ")" << std::endl;
	}

	// Display temperatures
	std::cout << "Temperatures:" << std::endl;
	for (double temp : temperatures)
	{
		std::cout << temp << " ";
	}
	std::cout << std::endl;

	// Display pressures
	std::cout << "Pressures:" << std::endl;
	for (double pressure : pressures)
	{
		std::cout << pressure << " ";
	}
	std::cout << std::endl;
}
