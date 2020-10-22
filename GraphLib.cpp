#include <iostream>
#include <map>
#include <vector> 

class Node
{
public:

    Node(char nodeName)
    {
        this->nodeName = nodeName;
    }

    const char GetNodeName()
    {
        return this->nodeName;
    }

    void AddNeighbour(Node& node, int edgeCost)
    {
        this->neighbours.insert(std::make_pair(node.GetNodeName(), edgeCost));
    }

    std::map<char, int> GetNodeNeighbours()
    {
        return neighbours;
    }

private:
    char nodeName;
    std::map<char, int> neighbours;
};

class Graph
{
public:

    void AddVertex(Node& node)
    {
        this->_graph.push_back(&node);
    }

    Node& GetNode(char nodeName)
    {
        for (auto elem : _graph)
        {
            if ((*elem).GetNodeName() == nodeName)
            {
                return (*elem);
            }
        }
    }

    std::vector<Node*> GetGraph()
    {
        return _graph;
    }

    int Size()
    {
        return this->_graph.size();
    }

    void Print(bool extend = false)
    {
        for (auto elem : this->_graph)
        {
            std::cout << "Node:\t" << (*elem).GetNodeName() << std::endl;

            if (extend)
            {
                auto neighbours = (*elem).GetNodeNeighbours();

                if (neighbours.size() != 0)
                {
                    std::cout << "Neighours: " << std::endl;

                    for (auto i : neighbours)
                    {
                        std::cout << "\tNode name: " << i.first << " Cost: " << i.second << std::endl;
                    }
                }

                else
                {
                    std::cout << "No Neighours" << std::endl;
                }
            }
        }
    }

private:

    std::vector<Node*> _graph;
};

std::pair<char, int> FindMinCostNode(std::map<char, int> nodeTable)
{
    std::vector<char> nodeNames;
    for (const auto i : nodeTable)
    {
        nodeNames.push_back(i.first);
    }

    char minNodeName = nodeNames[0];
    int minNodeCost = nodeTable[nodeNames[0]];

    for (int i = 1; i < nodeNames.size(); i++)
    {
        if (nodeTable[nodeNames[i]] < minNodeCost)
        {
            minNodeName = nodeNames[i];
            minNodeCost = nodeTable[nodeNames[i]];
        }
    }

    return std::make_pair(minNodeName, minNodeCost);
}

void FindShortestPath(Graph &graph, std::map<char, int> &toProcessed, std::map<char, int> &edgesCosts,Node *endNode)
{

    while (toProcessed.size() != 0)
    {
        std::pair<char, int> minVertex = FindMinCostNode(toProcessed);

        char minVertexName = minVertex.first;
        int minVertexCost = minVertex.second;

        std::map<char, int> neighbours = graph.GetNode(minVertexName).GetNodeNeighbours();

        if (neighbours.size() != 0)
        {
            for (const auto neighbour : neighbours)
            {
                int newCost = minVertexCost + neighbour.second;
                if (newCost < edgesCosts[neighbour.first])
                {
                    edgesCosts[neighbour.first] = newCost;
                    toProcessed[neighbour.first] = newCost;
                }
            }
        }
        toProcessed.erase(minVertexName);
    }

    std::cout << "The minimum cost to Node " << (*endNode).GetNodeName() << ": " << edgesCosts[(*endNode).GetNodeName()] << std::endl;
}


int main()
{
    Node s('S');
    Node b('B');
    Node a('A');
    Node f('F');
    Node h('H');

    s.AddNeighbour(a, 6);
    s.AddNeighbour(b, 2);

    b.AddNeighbour(a, 3);
    b.AddNeighbour(f, 5);

    a.AddNeighbour(f, 7);
    a.AddNeighbour(h, 1);

    h.AddNeighbour(f, 1);

    Graph graph;

    graph.AddVertex(s);
    graph.AddVertex(b);
    graph.AddVertex(a);
    graph.AddVertex(f);
    graph.AddVertex(h);

    //graph.Print(true);

    std::map<char, int> edgesCosts;
    std::map<char, int> toProcessed;

    Node* startNode = &s;
    Node* endNode = &f;

    auto neighbours = (*startNode).GetNodeNeighbours();

    for (const auto i : neighbours)
    {
        toProcessed.insert(std::make_pair(i.first, i.second));
        edgesCosts.insert(std::make_pair(i.first, i.second));
    }

    for (const auto j : graph.GetGraph())
    {
        char currNodeName = (*j).GetNodeName();
        if (currNodeName != (*startNode).GetNodeName() && neighbours.find(currNodeName) == neighbours.cend())
        {
            toProcessed.insert(std::make_pair(currNodeName, INT32_MAX));
            edgesCosts.insert(std::make_pair(currNodeName, INT32_MAX));
        }
    }

    FindShortestPath(graph, toProcessed, edgesCosts, endNode); 

}
