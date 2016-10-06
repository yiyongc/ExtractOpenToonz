#include "Skeleton.h"

Skeleton::Skeleton() {}

Skeleton::~Skeleton() {}

int Skeleton::getSelectedVertex() {
	return m_selectedVertex;
}

void Skeleton::setSelectedVertex(int vertexID) {
	m_selectedVertex = vertexID;
}

void Skeleton::addVertex(SkeletonVertex* v) {
	int parent = getSelectedVertex();
	if (parent != -1)
		v->setParent(parent);
	joints.push_back(v);
}

int Skeleton::getVertexCount() {
	return joints.size();
}

bool Skeleton::removeVertex(int id) {
	for (int i = 0; i < joints.size(); i++) {
		if (joints.at(i)->getID() == id) {
			joints.erase(joints.begin() + i);
			return true;
		}
	}

	return false;
}
