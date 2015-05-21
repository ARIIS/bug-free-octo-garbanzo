#ifndef WITNESSGRAPH_H
#define	WITNESSGRAPH_H

#include <list>
#include <vector>
#include <algorithm>
#include "../refineGame/Vertex.h"
#include "../refineGame/VertexWitness.h"

typedef enum {
        EQUAL,
        LESS,
        GREATER,
        INCOMP,
    } comparation;
    
class WitnessGraph{
    

	private:
                
		vector<Vertex*> nTV;
		set<Configuracao*> visited;
                list<TestemunhaDeFalha> witnesses;
		bool match(Configuracao* ci, Configuracao* cj);
		list<Vertex*> vertices;
                vector<Vertex*> verticesvector;
                void insertVertex(Vertex* v);
                Vertex* root;
                vector<revisionlist> vG;
                static int graphcount;
                int graphid;
                revisionlist evaGraphs(Vertex* v);
                revisionlist alfa(Vertex* v);
                revisionlist beta(Vertex* v);
                bool incrementer(vector<revisionlist>* children, vector<revisionlist::iterator>* childrenits, int digit);
                revision fusion(vector<revisionlist::iterator> childrenits);
                comparation compare(revision rev1, revision rev2);
                revisionlist minimals(revisionlist input);
                bool isComplement(change ch1, change ch2);
                bool isConsistent(revision input);

	public:
		WitnessGraph();
		WitnessGraph(Arena* a, list<TestemunhaDeFalha> w);
                WitnessGraph(Vertex* v);
                revisionlist evaMinimals();
		Vertex* cycleAncestor(Configuracao* ci);
		Vertex* nextVertex(Configuracao* ci);
		void createEdge(Vertex* origin, Vertex* destination);
                void connect(WitnessGraph* sub);
                list<Vertex*> getVertices();
                int rootId();
                Vertex* getRoot();

};


#endif
