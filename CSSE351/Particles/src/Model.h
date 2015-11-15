#ifndef __MODEL
#define __MODEL

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include "objload/objLoader.h"
using namespace std; //makes using vectors easy

#define PARTICLE_SIZE_X 350
#define PARTICLE_SIZE_Y 4350
#define PARTICLE_COUNT (PARTICLE_SIZE_X)*(PARTICLE_SIZE_Y)

class Model
{
public:
	

	void init()
	{
		for(size_t y=0; y<PARTICLE_SIZE_Y; y++)
		{
			for(size_t x=0; x<PARTICLE_SIZE_X; x++)
			{
				addAttr(elements, x+PARTICLE_SIZE_X*y);
				
				glm::vec3 p = glm::ballRand(1.0);
				addAttr(positions, p[0], p[1], p[2], 1);
				
				glm::vec3 v = glm::ballRand(1.0);
				addAttr(velocities, v[0], v[1], v[2], 1);
			}
		}
		
		
		min = computeMinBound();
		max = computeMaxBound();
		center = computeCentroid();
		dim = computeDimension();
	}
	
	vector<GLfloat> const getPosition() const
	{ return positions; }
	
	vector<GLfloat> const getVelocities() const
	{ return velocities; }
	
	vector<GLuint> const getElements() const
	{ return elements; }
	
	size_t getVertexCount() const
	{ return positions.size()/4; }
	
	size_t getPositionBytes() const
	{ return positions.size()*sizeof(GLfloat); }
	
	size_t getVelocitiesBytes() const
	{ return velocities.size()*sizeof(GLfloat); }
	
	size_t getElementBytes() const
	{ return elements.size()*sizeof(GLuint); }
	
	glm::vec3 getMinBound() const
	{ return min; }
	
	glm::vec3 getMaxBound() const
	{ return max; }
	
	glm::vec3 getCentroid() const
	{ return center; }
	
	glm::vec3 getDimension() const
	{ return dim; }
	
private:
	
	glm::vec3 computeMinBound()
	{
		glm::vec3 bound;
		
		for(int c=0; c<3; c++)
			bound[c] = std::numeric_limits<float>::max();
		
		for(int i=0; i<positions.size(); i+=4)
		{
			for(int c=0; c<3; c++)
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
		
		for(int c=0; c<3; c++)
			bound[c] = -std::numeric_limits<float>::max();
		
		for(int i=0; i<positions.size(); i+=4)
		{
			for(int c=0; c<3; c++)
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
		float positionCount = 1.0f/(getVertexCount());
		
		for(int i=0; i<positions.size(); i+=4)
		{
			center[0] += positions[i] * positionCount;
			center[1] += positions[i+1] * positionCount;
			center[2] += positions[i+2] * positionCount;
		}
		
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
	vector<GLfloat> velocities;
	vector<GLuint> elements;
	size_t objectCount;
	
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 dim;
	glm::vec3 center;
};

#endif