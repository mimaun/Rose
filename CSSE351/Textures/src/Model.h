#ifndef __MODEL
#define __MODEL

#include <vector>
#include "glm/glm.hpp"
#include "objload/objLoader.h"
using namespace std; //makes using vectors easy

class Model
{
public:


	void init()
	{
		initTexVertices();

		min = computeMinBound();
		max = computeMaxBound();
		center = computeCentroid();
		dim = computeDimension();
	}

	vector<GLfloat> const getPosition() const
	{ return positions; }

	vector<GLfloat> const getTexCoord() const
	{ return texCoords; }

	vector<GLuint> const getElements() const
	{ return elements; }

	size_t getVertexCount() const
	{ return positions.size()/2; }

	size_t getPositionBytes() const
	{ return positions.size()*sizeof(GLfloat); }

	size_t getTexCoordBytes() const
	{ return texCoords.size()*sizeof(GLfloat); }

	size_t getElementBytes() const
	{ return elements.size()*sizeof(GLuint); }

	glm::vec3 getMinBound()
	{ return min; }

	glm::vec3 getMaxBound()
	{ return max; }

	glm::vec3 getCentroid()
	{ return center; }

	glm::vec3 getDimension()
	{ return dim; }

private:

	void initTexVertices()
	{
		//leftmost  quad, uses 1st image
		addAttr(positions, 0, 0);
		addAttr(positions, 422, 0);
		addAttr(positions, 422, 187);
		addAttr(texCoords, 0, 1);
		addAttr(texCoords, 1, 1);
		addAttr(texCoords, 1, 0);

		addAttr(positions, 0, 0);
		addAttr(positions, 422, 187);
		addAttr(positions, 0, 187);
		addAttr(texCoords, 0, 1);
		addAttr(texCoords, 1, 0);
		addAttr(texCoords, 0, 0);

		//middle quad, uses 2nd image
		addAttr(positions, 422, 56);
		addAttr(positions, 818, 56);
		addAttr(positions, 818, 187);
		addAttr(texCoords, 0, 0.7);
		addAttr(texCoords, 1, 0.7);
		addAttr(texCoords, 1, 0);

		addAttr(positions, 422, 56);
		addAttr(positions, 818, 187);
		addAttr(positions, 422, 187);
		addAttr(texCoords, 0, 0.7);
		addAttr(texCoords, 1, 0);
		addAttr(texCoords, 0, 0);

		//bottom quad, uses 3rd image
		addAttr(positions, 422, 0);
		addAttr(positions, 1156, 0);
		addAttr(positions, 1156, 56);
		addAttr(texCoords, 1, 1);
		addAttr(texCoords, 0, 1);
		addAttr(texCoords, 0, 0);

		addAttr(positions, 422, 0);
		addAttr(positions, 1156, 56);
		addAttr(positions, 422, 56);
		addAttr(texCoords, 1, 1);
		addAttr(texCoords, 0, 0);
		addAttr(texCoords, 1, 0);

		//right most upper quad, uses 4th image
		addAttr(positions, 818, 56);
		addAttr(positions, 1156, 56);
		addAttr(positions, 1156, 187);
		addAttr(texCoords, 0.5, 0);
		addAttr(texCoords, 0.5, 1);
		addAttr(texCoords, 1, 1);

		addAttr(positions, 818, 56);
		addAttr(positions, 1156, 187);
		addAttr(positions, 818, 187);
		addAttr(texCoords, 0.5, 1);
		addAttr(texCoords, 0, 0);
		addAttr(texCoords, 0, 1);
	}

	glm::vec3 computeMinBound()
	{
		glm::vec3 bound;

		for(int c=0; c<2; c++)
			bound[c] = std::numeric_limits<float>::max();

		for(int i=0; i<positions.size(); i+=2)
		{
			for(int c=0; c<2; c++)
			{
				if(positions[i+c] < bound[c])
					bound[c] = positions[i+c];
			}
		}

		return bound;
	}

	glm::vec3 computeMaxBound()
	{
		glm::vec3 bound;

		for(int c=0; c<2; c++)
			bound[c] = -std::numeric_limits<float>::max();

		for(int i=0; i<positions.size(); i+=2)
		{
			for(int c=0; c<2; c++)
			{
				if(positions[i+c] > bound[c])
					bound[c] = positions[i+c];
			}
		}

		return bound;
	}

	glm::vec3 computeCentroid()
	{
		glm::vec3 center = glm::vec3(0);
		center = (max - min)/2.0f;

		return center;
	}

	glm::vec3 computeDimension()
	{
		glm::vec3 max = getMaxBound();
		glm::vec3 min = getMinBound();
		glm::vec3 dim = max - min;
		return dim;
	}

	template<typename Container, typename Value>
	void addAttr(Container & c, Value v)
	{
		c.push_back(v);
	}

	template<typename Container, typename Value, typename... Args>
	void addAttr(Container & c, Value v, Args... args)
	{
		c.push_back(v);
		addAttr(c, args...);
	}
	
	vector<GLfloat> positions;
	vector<GLfloat> texCoords;
	vector<GLuint> elements;
	size_t objectCount;

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 dim;
	glm::vec3 center;
};

#endif
