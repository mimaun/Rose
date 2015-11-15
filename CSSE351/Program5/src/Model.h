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
        objLoader loader;
        //loader.load("resources/cube.obj");
        //loader.load("resources/sphere.obj");
//        loader.load("resources/teapot.obj");
        loader.load("/Users/misato/ROSE/CSSE351/1516a-csse351-groupG/PlanetsObj/earth/earth.obj");
        //loader.load("resources/test.obj");
        
        for(size_t i=0; i<loader.vertexCount; i++) {
            positions.push_back(loader.vertexList[i]->e[0]);
            positions.push_back(loader.vertexList[i]->e[1]);
            positions.push_back(loader.vertexList[i]->e[2]);
            //printf("v%zu: %f %f %f\n", i, positions[i*3+0], positions[i*3+1], positions[i*3+2]);
        }
        
        for(size_t i=0; i<loader.faceCount; i++) {
            if(loader.faceList[i]->vertex_count != 3) {
                fprintf(stderr, "Only triangle primitives are supported.\n");
                exit(1);
            }
            
            elements.push_back(loader.faceList[i]->vertex_index[0]);
            elements.push_back(loader.faceList[i]->vertex_index[1]);
            elements.push_back(loader.faceList[i]->vertex_index[2]);
            //printf("f%zu: %i %i %i\n", i, elements[i*3+0], elements[i*3+1], elements[i*3+2]);
        }
        
        
        for(size_t i=0; i<positions.size(); i++) {
            colors.push_back( 0 );
            colors.push_back( 0 );
            colors.push_back( 0 );
        }
        
        colors.resize(positions.size());
        
        //TODO compute the vertex normals by averaging the face normals
        vector<glm::vec3> faceNormals;
        
        vector<glm::vec3> vertexNormals;
        for(size_t i=0; i<loader.vertexCount; i++) {
            vertexNormals.push_back(glm::vec3(0, 0, 0));
        }
        
        //compute all face normals
        for(size_t i=0; i<elements.size(); i+=3) {
            
            vector<size_t> vertexIds;
            size_t vertexId[3];
            for(size_t v=0; v<3; v++) {
                vertexId[v] = elements[i+v];
                vertexIds.push_back(vertexId[v]);
            }
            
            glm::vec3 vertexPos[3];
            for(size_t v=0; v<3; v++)
                for(size_t c=0; c<3; c++)
                    vertexPos[v][c] = positions[ vertexId[v]*3 + c ];
            
            glm::vec3 a = vertexPos[1] - vertexPos[0];
            glm::vec3 b = vertexPos[2] - vertexPos[1];
            glm::vec3 faceNormal = glm::normalize(glm::cross(a, b));
            
            faceNormals.push_back(faceNormal);
            
            // accumulate face normal.
            for(size_t v = 0; v < vertexIds.size(); v++) {
                vertexNormals[vertexIds[v]] += faceNormal;
            }
            
            //scale to RGB range (undo this when using as a normal vector!)
            //faceNormal = (faceNormal + 1.0f) * 0.5f;
            
//            for(size_t v=0; v<3; v++)
//                for(size_t c=0; c<3; c++)
//                    colors[ vertexId[v]*3 + c ] = faceNormal[c];
        }
        
        //accumulate face normals at vertices
        
        //normalize vertex normals
        for(size_t j = 0; j < vertexNormals.size(); j++) {
            vertexNormals[j] = glm::normalize(vertexNormals[j]);
            vertexNormals[j] = (vertexNormals[j] + 1.0f) * 0.5f;
        }
        
        for(size_t j = 0; j < vertexNormals.size(); j++) {
            colors[j * 3 + 0] = vertexNormals[j].r;
            colors[j * 3 + 1] = vertexNormals[j].g;
            colors[j * 3 + 2] = vertexNormals[j].b;
        }

        min = computeMinBound();
        max = computeMaxBound();
        center = computeCentroid();
        dim = computeDimension();
    }
    
    vector<GLfloat> const getPosition() const
    { return positions; }
    
    vector<GLfloat> const getColor() const
    { return colors; }
    
    vector<GLuint> const getElements() const
    { return elements; }
    
    size_t getVertexCount() const
    { return positions.size()/3; }
    
    size_t getPositionBytes() const
    { return positions.size()*sizeof(GLfloat); }
    
    size_t getColorBytes() const
    { return colors.size()*sizeof(GLfloat); }
    
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
    
    glm::vec3 computeMinBound()
    {
        glm::vec3 bound;
        
        for(int c=0; c<3; c++)
            bound[c] = std::numeric_limits<float>::max();
        
        for(int i=0; i<positions.size(); i+=3)
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
        
        for(int i=0; i<positions.size(); i+=3)
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
        float positionCount = 1.0f/(positions.size()/3.0f);
        
        for(int i=0; i<positions.size(); i+=3)
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
    
    vector<GLfloat> positions;
    vector<GLfloat> colors;
    vector<GLuint> elements;
    size_t objectCount;
    
    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 dim;
    glm::vec3 center;
};

#endif