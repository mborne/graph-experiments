#include <iostream>
#include <memory>
#include <map>
#include <set>

class Edge;

class Vertex
{
    friend class Graph;
    friend class Edge;
public:

    const int id() const
    {
        return _id;
    }

private:
    int _id;
    std::set<Edge*> _inEdges;
    std::set<Edge*> _outEdges;

    Vertex(int id) : _id(id)
    {
    }
};

class Edge {
public:
    Edge(int id,Vertex* source,Vertex* target) :
        _id(id),
        _source(source),
        _target(target)
    {
        _source->_outEdges.insert(this);
        _target->_inEdges.insert(this);
    }

    Vertex* source() const {
        return _source;
    }

    Vertex* target() const {
        return _target;
    }

private:
    int _id;
    Vertex* _source;
    Vertex* _target;
};



class Graph
{
public:
    typedef std::map<int,Vertex*> vertex_map;
    typedef std::map<int,Edge*>   edge_map;

    typedef vertex_map::const_iterator vertex_iterator;
    typedef edge_map::const_iterator   edge_iterator;

    virtual ~Graph(){
        for ( edge_iterator it = _edges.begin(); it != _edges.end(); ++it ){
            delete it->second;
        }
        for ( vertex_iterator it = _vertices.begin(); it != _vertices.end(); ++it ){
            delete it->second;
        }
    }

    Vertex* getVertex(int id){
        auto it = _vertices.find(id);
        if ( it != _vertices.end() ){
            return it->second;
        }else{
            return nullptr;
        }
    }

    Vertex* getOrCreateVertex(int id)
    {
        auto it = _vertices.find(id);
        if ( it != _vertices.end() ){
            return it->second;
        }else{
            Vertex* vertex = new Vertex(id);
            _vertices.insert(std::make_pair(id,vertex));
            return vertex;
        }
    }

    Edge* createEdge(int id,Vertex* source, Vertex* target){
        Edge* edge = new Edge(id,source,target);
        _edges.insert(std::make_pair(id,edge));
        return edge;
    }

    const vertex_map & vertices() const {
        return _vertices;
    }

    const edge_map & edges() const {
        return _edges;
    }

private:
    vertex_map _vertices;
    edge_map   _edges;
};


int main(int argc, char *argv[])
{
    {
        std::shared_ptr<Graph> graph(new Graph());
        Vertex* a = graph->getOrCreateVertex(15);
        Vertex* b = graph->getOrCreateVertex(19);
        Vertex* c = graph->getOrCreateVertex(50);
        std::cout << a->id() << std::endl;
        std::cout << b->id() << std::endl;
        std::cout << c->id() << std::endl;

        Edge* edge = graph->createEdge(15,a,b);
        std::cout << edge->source()->id() << " " << edge->target()->id() << std::endl;

        const Graph::vertex_map & vertices = graph->vertices();
        for ( Graph::vertex_iterator it = vertices.begin(); it != vertices.end(); ++it ){
            Vertex * vertex = it->second;
            std::cout << vertex->id() << std::endl;
        }
    }
    return 0;
}