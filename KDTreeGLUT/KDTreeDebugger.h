#pragma once


#include "KDTree.h"


class KDTreeDebugger
{


public:

    static void render(const KDTree& rTree, size_t nDebugLevel, bool bRenderPoints);


private:

    static void renderNode(KDTree::Node* pNode, const BBox& rBBox, size_t nLevel, size_t nDebugLevel, bool bRenderPoints);

};

