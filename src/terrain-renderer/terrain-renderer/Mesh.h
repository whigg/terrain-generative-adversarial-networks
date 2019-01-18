#ifndef MESH_H
#define MESH_H

#include "Material.h"
#include "cgmath.h"
#include <vector>

class Mesh
{
public:
	class Vertex;
private:
	Material material;
	std::vector<Vertex>   vertices;
	std::vector<uint32_t> indices;
public:
	class Vertex
	{
	public:
		vec3 position;
		vec3 normal;
		vec2 texCoords;
	public:
		Vertex() = default;
		Vertex(const vec3&, const vec3&, const vec2&);
		Vertex(const Vertex&);
		Vertex& operator=(const Vertex&);
		Vertex(Vertex&&);
		Vertex& operator=(Vertex&&);
		
		float & operator[](int i);
		float const & operator[](int i) const;
	};
public:
	Mesh() = default;
	Mesh(const Mesh&);
	Mesh& operator=(const Mesh&);
	Mesh(Mesh&&);
	Mesh& operator=(Mesh&&);

	void setMaterial	(const Material& material			 );
	void setVertexBuffer(const std::vector<Vertex>& vertices );
	void setIndexBuffer	(const std::vector<uint32_t>& indices);
};

#endif