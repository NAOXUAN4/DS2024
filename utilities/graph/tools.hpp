#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

#include "Graph.hpp"
#include <vector>

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    std::vector<Vertex<Tv>> V;
    std::vector<std::vector<Edge<Te>*>> E;

public:
    GraphMatrix() { this->n = this->e = 0; }

    ~GraphMatrix() {
        for (int j = 0; j < this->n; j++)
            for (int k = 0; k < this->n; k++)
                if (E[j][k]) delete E[j][k];
    }

    // Vertex Operations
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    
    virtual int firstNbr(int i) { return nextNbr(i, this->n); }
    
    virtual int nextNbr(int i, int j) {
        while ((j > -1) && (!exists(i, --j)));
        return j;
    }

    virtual VStatus& status(int i) { return V[i].status; }
    virtual int& dTime(int i) { return V[i].dTime; }
    virtual int& fTime(int i) { return V[i].fTime; }
    virtual int& parent(int i) { return V[i].parent; }
    virtual int& priority(int i) { return V[i].priority; }

    // Vertex Insertion and Removal
    virtual int insert(Tv const& vertex) {
        for (int j = 0; j < this->n; j++) 
            E[j].push_back(nullptr);
        this->n++;
        
        E.push_back(std::vector<Edge<Te>*>(this->n, nullptr));
        
        return V.size() - 1;
    }

    virtual Tv remove(int i) {
        // Remove incoming edges
        for (int j = 0; j < this->n; j++)
            if (exists(i, j)) { 
                delete E[i][j]; 
                V[j].inDegree--; 
            }
        
        // Remove this vertex's row
        E.erase(E.begin() + i);
        this->n--;

        // Remove outgoing edges and decrement degrees
        for (int j = 0; j < this->n; j++)
            if (exists(j, i)) { 
                delete E[j][i]; 
                V[j].outDegree--; 
            }

        Tv vBak = vertex(i);
        V.erase(V.begin() + i);
        return vBak;
    }

    // Edge Operations
    virtual bool exists(int i, int j) { 
        return (0 <= i) && (i < this->n) && 
               (0 <= j) && (j < this->n) && 
               (E[i][j] != nullptr); 
    }

    virtual EStatus& status(int i, int j) { return E[i][j]->status; }
    virtual Te& edge(int i, int j) { return E[i][j]->data; }
    virtual int& weight(int i, int j) { return E[i][j]->weight; }

    virtual void insert(Te const& edge, int w, int i, int j) {
        if (exists(i, j)) return;
        
        E[i][j] = new Edge<Te>(edge, w);
        this->e++;
        V[i].outDegree++;
        V[j].inDegree++;
    }

    virtual Te remove(int i, int j) {
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = nullptr;
        
        this->e--;
        V[i].outDegree--;
        V[j].inDegree--;
        
        return eBak;
    }
};






#endif // GRAPH_MATRIX_HPP