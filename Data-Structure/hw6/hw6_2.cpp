#include <vector>
#include <map>
#include <iostream>
#define MAXNUM 10000

using namespace std;

class Vertex;
class Edge;

class Edge{
private:
    int act,time, e, l, slack;
    Vertex * VertexHead, * VertexTail;
public:
    int ACT(){return act;}
    int E(){return e;}
    int L(){return l;}
    int Slack(){return slack;}
    int Head();
    int Tail();
    Vertex * VHead(){return VertexHead;}
    Vertex * VTail(){return VertexTail;}
    int Time(){return time;}
    void Show();
    Edge(int a,Vertex * vh, Vertex * vt, int t);
    int ComputeEETime();
    int ComputeLETime();
    int ComputeETime();
    int ComputeLTime();
    int Computeslack(){slack = l - e; return slack;}
};

class Vertex{
private:
    int index,le;
    map<int, Edge *> inEdge;
    map<int, Edge *> outEdge;
    int ee;
public:
    int Index(){return index;}
    int LE(){return le;}
    void addInEdges(Edge * e){inEdge[e->ACT()] = e;}
    void addOutEdge(Edge * e){outEdge[e->ACT()] = e;}
    Vertex(int num){le = ee = 0;index = num;}
    Vertex(){le = ee = 0;index = -1;}
    void Show();
    int ComputeEETime();
    int ComputeLETime();
};

int Edge::Head(){return VertexHead->Index();}
int Edge::Tail(){return VertexTail->Index();}
void Edge::Show(){
    printf("<%d , %d> : e = %d\tl = %d\n",VertexHead->Index(),VertexTail->Index(),e,l);
}

int Vertex::ComputeEETime(){
    if(ee) return ee;
    int LastNUM = -1;
    if(inEdge.size()){
        for(map<int, Edge *>::iterator it = inEdge.begin(); it != inEdge.end(); it++){
            if(it->second->ComputeEETime() > LastNUM){
                LastNUM = it->second->ComputeEETime();
            }
        }
    }else return 0;
    ee = LastNUM;
    return ee;
}

int Edge::ComputeEETime(){
    return time + VertexHead->ComputeEETime();
}

int Vertex::ComputeLETime(){
    if(le) return le;
    int LE = MAXNUM;
    if(outEdge.size()){
        for(map<int, Edge *>::iterator it = outEdge.begin(); it != outEdge.end(); it++){
            if(it->second->ComputeLETime() < LE){
                LE = it->second->ComputeLETime();
            }
        }
    }else return ee;

    le = LE;
    return le;
}

int Edge::ComputeLETime(){
    return VertexTail->ComputeLETime() - time;
}

int Edge::ComputeETime(){
    e = VertexHead->ComputeEETime();
    return e;
}

int Edge::ComputeLTime(){
    l = VertexTail->ComputeLETime() - time;
    return l; 
}
 
void Vertex::Show(){
    map<int, Edge *>::iterator it;
    printf("Vertex %d\n",index);
    cout<<"Out-Edge"<<endl;
    for(it = outEdge.begin(); it != outEdge.end(); it++)
        it->second->Show();
    cout<<"In-Edge"<<endl;
    for(it = inEdge.begin(); it != inEdge.end(); it++)
        it->second->Show();
}

vector<Edge> InputEdge(map<int, Vertex> & vertices){
    int edgeAmount;
    int act, head, tail, time;
    cin>>edgeAmount;
    vector<Edge> edges;
    for(int i = 0; i < edgeAmount; i++){
        cin>>act>>head>>tail>>time;
        try{
            vertices.at(head);
        }catch(out_of_range){
            Vertex v(head);
            vertices[head] = v;
        }

        try{
            vertices.at(tail);
        }catch(out_of_range){
            Vertex v(tail);
            vertices[tail] = v;
        }
        Edge newEdge(act,&vertices.at(head), &vertices.at(tail) , time);
        edges.push_back(newEdge);
    }
    return edges;
}

Edge::Edge(int a, Vertex * vh, Vertex * vt, int t){
    act = a;
    VertexHead = vh;
    VertexTail = vt;
    time = t;
    e = l = slack = 0;
    // Show();
}

void AddEdge(vector<Edge> & edges, map<int, Vertex>  & vertices){
    for(int i = 0; i < edges.size(); i++){
        vertices[edges[i].Head()].addOutEdge(&edges[i]);
        vertices[edges[i].Tail()].addInEdges(&edges[i]);
    }
}

void Computation(vector<Edge> * edges, map<int, Vertex> * vertices){
    for(map<int, Vertex >::iterator it = vertices->begin(); it != vertices->end(); it++)
        it->second.ComputeEETime();
    for(map<int, Vertex >::iterator it = vertices->begin(); it != vertices->end(); it++)
        it->second.ComputeLETime();
    for(int i = 0; i < edges->size(); i++){
        (*edges)[i].ComputeETime();
        (*edges)[i].ComputeLTime();
        (*edges)[i].Computeslack();
    }
        
}

int main(){
    vector<Edge> edges;
    map<int,Vertex> vertices;
    edges = InputEdge(vertices);
    AddEdge(edges,vertices);
    Computation(&edges,&vertices);
    printf("%-10s%-10s%-10s%-10s%-10s\n","act.","e","l","slack","critical");
    for(int i = 0 ; i < edges.size(); i++){
        printf("%-10d%-10d%-10d%-10d%-10s\n",edges[i].ACT(),edges[i].E(),edges[i].L(),edges[i].Slack(),edges[i].E() == edges[i].L() ? "Yes":"No");
    }
}