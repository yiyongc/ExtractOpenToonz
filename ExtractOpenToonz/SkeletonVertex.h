#ifndef SKELETONVERTEX_H
#define SKELETONVERTEX_H

class SkeletonVertex {

public:
	SkeletonVertex();
	SkeletonVertex(int x, int y);
	~SkeletonVertex();

	int getParent();
	void setParent(int parent);

	int getID();
	void setID(int id);

private:
	int xPos;
	int yPos;
	int parent_id;
	int vertex_id;


};


#endif // !SKELETONVERTEX_H
