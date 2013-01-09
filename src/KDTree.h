#pragma once

#include "BBox.h"

class KDTree
{


public:

    KDTree (const std::vector<glm::vec3>& rPoints, size_t nMaxPointsPerCell = 10);
    ~KDTree();


    size_t getDepth() const {return m_nDepth;}

    void findKNearest(size_t k, const glm::vec3& rPoint, std::vector<glm::vec3>& rKNearest) const;

private:

    class Node
    {

    public:
        Node(): m_nAxis(AXIS_X), m_fMedian(0.0f), m_pLeft(NULL), m_pRight(NULL), m_pParent(NULL)
        {

        }
        ~Node()
        {
            delete m_pLeft;
            delete m_pRight;
        }

        bool isLeaf() {return m_pLeft == NULL && m_pRight == NULL;}

        TAxis   m_nAxis;
        float   m_fMedian;
        Node*   m_pParent;
        Node*   m_pLeft;
        Node*   m_pRight;
    
        std::vector<glm::vec3> m_aPoints;
    private:
        Node(Node&){}
        Node& operator& (Node&){return *this;}
    };


    size_t  checkNode(size_t nLevel, Node* pNode);
    size_t  splitNode(size_t nLevel, Node* pNode);
    Node*   findNode(const glm::vec3& rPoint, Node* pNode) const;
    void    selectKNearest(size_t k, const std::vector<glm::vec3>& rCandidates, std::vector<glm::vec3>& rKNearest) const;

    Node*                   m_pRoot;
    const size_t            m_nMaxPointsPerCell;
    size_t                  m_nDepth;

    const BBox              m_aBBox;
    
    friend class KDTreeDebugger;
};