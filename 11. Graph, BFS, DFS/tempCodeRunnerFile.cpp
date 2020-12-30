void Graph::load()
{
    ifstream file;
    file.open("graph.txt");

    int nv, ne;
    file>>nv>>ne;
    setnVertices(nv);

    for(int i = 0; i < nv; ++i){
        int u, sz, v;
        file>>u>>sz;
        for(int j = 0; j < sz; ++j){
            file>>v;
            matrix[u][v] = 1;
        }
    }
    file.close();
}