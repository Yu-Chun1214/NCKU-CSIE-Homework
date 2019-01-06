#include <iostream>
#include <vector>
#include <map>
#define MAX_NUM 10000

using namespace std;

// Define prototype;
class cVertex;
class cEdge;
class cTree;

class cEdge{
private:
    cVertex * VertexHead, * VertexTail;
    int weight;
public:
    cEdge(cVertex * V1, cVertex * V2, int W);
    int Weight(){return weight;}
    void Show();
    int Selected;
    int Head();
    int Tail();
};




class cVertex{
private:
    map<int,cEdge *>edges;
    int index;
public:
    cVertex(int num);
    cVertex();
    cEdge * SelectEdge();
    int addEdge(cEdge *);
    void Show();
    int Index(){return index;}
    
};

cVertex::cVertex(){
    index = 100;
}

cVertex::cVertex(int num){
    index = num;
}

int cVertex::addEdge(cEdge * newEdge){
    edges[edges.size()] = newEdge;
    return edges.size();
}

cEdge * cVertex::SelectEdge(){
    int min = MAX_NUM;
    int min_index = 0;
    map<int, cEdge*>::iterator iter;
    for(iter = edges.begin(); iter != edges.end(); iter++){
        iter->second->Show();
        if(iter->second->Weight() < min && iter->second->Selected <= 1){
            min = iter->second->Weight();
            min_index = iter->first;
        }
    }
    
    return edges[min_index];
}

void cVertex::Show(){
    cout<<"Vertex : "<<index<<endl;
    for(map<int,cEdge *>::iterator iter = edges.begin(); iter!=edges.end(); iter++)
        iter->second->Show();
}

class cTree{
private:
    // vector<cVertex> vertices;
    map<int, cVertex *> vertices; 
    cEdge * newEdge;
public:
    void SelectEdge();
    void InputVertex(cVertex * v);
    void Show();
    bool MergeTree(cTree tree);
    bool IsInTree(int index);
    cEdge * NewEdge(){return newEdge;}
};

void cTree::Show(){
    cout<<"Tree : ";
    for(map<int,cVertex *>::iterator it = vertices.begin(); it!= vertices.end() ;it++)
        cout<<it->first<<endl;
}

void cTree::SelectEdge(){
    map<int, cVertex *>::iterator iter;
    cEdge * minEdge;
    cEdge * temp;
    int minCost = MAX_NUM;
    for(iter = vertices.begin(); iter != vertices.end(); iter++){
        temp = iter->second->SelectEdge();
        if(temp->Weight() < minCost && temp->Selected <= 1){
            minCost = temp->Weight();
            minEdge = temp;
        }
    }
    newEdge = minEdge;
    minEdge->Selected++;
}

void cTree::InputVertex(cVertex * v){
    vertices[v->Index()] = v;
}

bool cTree::IsInTree(int index){
    try{
        vertices.at(index);
        return true;
    }catch(out_of_range){
        return false;
    }
}

void cEdge::Show(){
    printf("<%d , %d> weight = %d  Selected = %d\n",VertexHead->Index(),VertexTail->Index(),weight,Selected /*? "True" : "False"*/);
}

int cEdge::Head(){return VertexHead->Index();}

int cEdge::Tail(){return VertexTail->Index();}

bool cTree::MergeTree(cTree tree){
    map<int, cVertex * >::iterator iter;
    newEdge->Selected++;
    cout<<"newEdge->Selected = "<<newEdge->Selected<<endl;
    for(iter = tree.vertices.begin(); iter != tree.vertices.end(); iter++)
        vertices[iter->first] = iter->second;
    if(tree.newEdge)
        try{
            vertices.at(tree.newEdge->Tail());
            newEdge = NULL;
            try{
                vertices.at(tree.newEdge->Head());
                newEdge = NULL;
                return false;
            }catch(out_of_range){
                newEdge = tree.newEdge;
            }
        }catch(out_of_range){
            newEdge = tree.newEdge;
        }
    else{
        newEdge = NULL;
        return false;
    }
    return true;
}

cEdge::cEdge(cVertex * V1, cVertex * V2, int W){
    VertexHead = V1; 
    VertexTail = V2; 
    weight = W;
    Selected = 0;
}

vector<cTree>::iterator SelectTree(vector<cTree> & trees,cTree tree, cEdge edge){
    for(vector<cTree>::iterator iter = trees.begin(); iter != trees.end(); iter++)
        if((iter->IsInTree(edge.Tail()) && tree.IsInTree(edge.Head())) || 
           (iter->IsInTree(edge.Head()) && tree.IsInTree(edge.Tail()))) 
           return iter;
    throw "This edge isn't in the graph";
}

void MergeTree(vector<cTree> & trees){
    cEdge * temp;
    vector<cTree>::iterator treeIter;
    for(int i = 0; i < trees.size(); i++){
        do{
            cout<<"Now Tree is"<<endl;
            trees[i].Show();
            temp = trees[i].NewEdge();
            cout<<"Tree's Selected new Edge"<<endl;
            temp->Show();
            treeIter = SelectTree(trees,trees[i],*temp);
            cout<<"Be Merged Tree"<<endl;
            treeIter->Show();
            trees[i].MergeTree(*treeIter);
            trees.erase(treeIter);
            system("pause");
            cout<<"\n";
        }while(trees[i].NewEdge());
    }
}

vector<cEdge> InputEdges(map<int,cVertex> & vertices){
    int edgeAmounts;
    // map<int,cVertex> vertices;
    vector<cEdge> edges;
    int v1,v2,weight;
    cin>>edgeAmounts;
    for(int i = 0; i < edgeAmounts; i++){
        cin>>v1>>v2>>weight;
        try{
            vertices.at(v1);
        }catch(std::out_of_range){
            cVertex newVertex(v1);
            vertices[v1] = newVertex;
        }
        try{
            vertices.at(v2);
        }catch(std::out_of_range){
            cVertex newVertex(v2);
            vertices[v2] = newVertex;
        }
        
        cEdge newEdge(&vertices.at(v1),&vertices.at(v2),weight);

        edges.push_back(newEdge);
    }
    return edges;
}

void AddEdges(map<int,cVertex> &vertices, vector<cEdge> & edges){
    for(int i = 0; i < edges.size(); i++){
        vertices[edges[i].Head()].addEdge(&edges[i]);
        vertices[edges[i].Tail()].addEdge(&edges[i]);
    }
}

int main(){
    int EdgeAmounts;
    int v1,v2,weight;
    map<int,cVertex> vertices;
    vector<cEdge> edges;
    vector<cTree> trees;


    edges = InputEdges(vertices);

    for(map<int,cVertex>::iterator it = vertices.begin(); it != vertices.end(); it++){
        cTree tree;
        tree.InputVertex(&it->second);
        trees.push_back(tree);
    }

    AddEdges(vertices,edges);

    for(auto a : edges){
        a.Show();
    }

    while(trees.size() > 1){
        for(int i = 0; i < trees.size(); i++)
            trees[i].SelectEdge();
        MergeTree(trees);
        cout<<"------------------"<<endl;
        for(int i = 0; i < trees.size(); i++)
            trees[i].Show();
        cout<<"trees size is "<<trees.size()<<endl;
    }
    cout<<"\n\n\n"<<endl;
    trees[0].Show();
    cout<<"\n\n\n"<<endl;
    for(vector<cEdge>::iterator it = edges.begin(); it!= edges.end(); it++){
        if(it->Selected) //it->Show();
            printf("%d %d %d\n",it->Head(), it->Tail(), it->Weight());
    }
}