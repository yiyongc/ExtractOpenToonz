#include "SkeletonVertex.h"

//---- Constructors and Deconstructors ----//

SkeletonVertex::SkeletonVertex() : 
xPos(0),
yPos(0),
parent_id(-1) {}

SkeletonVertex::SkeletonVertex(int x, int y) :
xPos(x),
yPos(y),
parent_id(-1) {}

SkeletonVertex::~SkeletonVertex() {}

//---- Getters and Setters ----//

int SkeletonVertex::getParent() {
	return parent_id;
}

void SkeletonVertex::setParent(int parent) {
	parent_id = parent;
}

int SkeletonVertex::getID() {
	return vertex_id;
}

void SkeletonVertex::setID(int id) {
	vertex_id = id;
}