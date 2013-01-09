#include "PCH.h"

#include "KDTree.h"

#include <algorithm>

#include "BBox.h"

struct XAxisComparator
{
    inline bool operator() (const glm::vec3& a, const glm::vec3& b)
    {
        return a.x < b.x;
    }
};

struct YAxisComparator
{
    inline bool operator() (const glm::vec3& a, const glm::vec3& b)
    {
        return a.y < b.y;
    }
};

struct ZAxisComparator
{
    inline bool operator() (const glm::vec3& a, const glm::vec3& b)
    {
        return a.z < b.z;
    }
};

struct LengthComparator
{
    inline bool operator() (const glm::vec3& a, const glm::vec3& b)
    {
        return glm::length(a) < glm::length(b);
    }
};

KDTree::KDTree(const std::vector<glm::vec3>& rPoints, size_t nMaxPointsPerCell)
    :   m_pRoot(new Node),
        m_nMaxPointsPerCell(nMaxPointsPerCell),
        m_aBBox(rPoints)
{
    m_pRoot->m_aPoints = rPoints;
    m_nDepth = checkNode(0, m_pRoot) + 1;
}

KDTree::~KDTree()
{
    delete m_pRoot;
}

size_t KDTree::checkNode(size_t nLevel, Node* pNode)
{
    if (pNode && pNode->m_aPoints.size() > m_nMaxPointsPerCell)
    {
        return splitNode(nLevel, pNode);
    }
    return nLevel;
}

size_t KDTree::splitNode(size_t nLevel, Node* pNode)
{
    if (pNode)
    {
       
        TAxis nAxis = static_cast<TAxis>(nLevel % 3);

        if (nAxis == AXIS_X)
            std::sort(pNode->m_aPoints.begin(), pNode->m_aPoints.end(), XAxisComparator());
        else if (nAxis == AXIS_Y)
            std::sort(pNode->m_aPoints.begin(), pNode->m_aPoints.end(), YAxisComparator());
        else if (nAxis == AXIS_Z)
            std::sort(pNode->m_aPoints.begin(), pNode->m_aPoints.end(), ZAxisComparator());

        size_t nMiddle = pNode->m_aPoints.size() / 2;

        Node* pLeftNode = new Node();
        pLeftNode->m_pParent = pNode;
        for (size_t i=0; i<nMiddle; i++)
        {
            pLeftNode->m_aPoints.push_back(pNode->m_aPoints[i]);
        }

        Node* pRightNode = new Node();
        pRightNode->m_pParent = pNode;
        for (size_t i=nMiddle; i<pNode->m_aPoints.size(); i++)
        {
            pRightNode->m_aPoints.push_back(pNode->m_aPoints[i]);
        }

        pNode->m_nAxis = nAxis;
        pNode->m_fMedian = pNode->m_aPoints[nMiddle][nAxis];
        pNode->m_pLeft = pLeftNode;
        pNode->m_pRight = pRightNode;
        
        const size_t nDepthLeft = checkNode(nLevel+1, pLeftNode);
        const size_t nDepthRight = checkNode(nLevel+1, pRightNode);
        return std::max(nDepthLeft, nDepthRight);
    }
    else
    {
        return nLevel;
    } 
}

KDTree::Node* KDTree::findNode(const glm::vec3& rPoint, Node* pNode) const
{
    if (pNode)
    {
        if (pNode->isLeaf())
        {
            return pNode;
        }
        else
        {
            if ( rPoint[pNode->m_nAxis] < pNode->m_fMedian)
                return findNode(rPoint, pNode->m_pLeft);
            else
                return findNode(rPoint, pNode->m_pRight);
        }
        
    }
    else
    {
        throw std::exception();//"KDTree is corrupt");
    }

}

void KDTree::findKNearest(size_t k, const glm::vec3& rPoint, std::vector<glm::vec3>& rKNearest) const
{
    Node* pNode = findNode(rPoint, m_pRoot);

    while (pNode && pNode->m_aPoints.size() >= k)
    {
        pNode = pNode->m_pParent;
    }

    if (pNode)
    {
        selectKNearest(k, pNode->m_aPoints, rKNearest);
    }
}

void KDTree::selectKNearest(size_t k, const std::vector<glm::vec3>& rCandidates, std::vector<glm::vec3>& rKNearest) const
{
    std::vector<glm::vec3> rCandidatesSortet(rCandidates);
    std::sort(rCandidatesSortet.begin(), rCandidatesSortet.end(), LengthComparator());

    if (k > rCandidates.size())
    {
        rKNearest = rCandidatesSortet;
    }
    else
    {
        rKNearest.resize(k);
        std::copy (rCandidatesSortet.begin(), rCandidatesSortet.begin()+k, rKNearest.begin());
    }
}