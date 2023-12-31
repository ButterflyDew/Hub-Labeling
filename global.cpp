#include "global.h"
#include <cstdio>
#include <string>
#include <utility>

const int inf = 0x3f3f3f3f;
const double INF = 1e18;
const double eps = 1e-10;
int generateRandomNumber(int l, int r)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}

double getRandomRealNumber(double l, double r) 
{
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_real_distribution<double> dis(l, r); 
    return dis(gen);
}

tuple<int, int, double, int> extract_values(const string& lin) 
{
    int a, b, d;
    double c;
    istringstream ss(lin);
    ss >> a >> b >> c >> d;
    return make_tuple(a, b, c, d);
}


double Graph::get_one_double(string line)
{
    cerr << "double: " << line << endl;
    try {
        double num = std::stod(line);
        return num;
    } catch (const invalid_argument& e) {
        cerr << "error in get_one_double" << endl;
        exit(0);
    }
    return -1;
}

int Graph::get_one_num(string line)
{
    cerr << "int: " << line << endl;
    try {
        int num = std::stoi(line);
        return num;
    } catch (const invalid_argument& e) {
        cerr << "error in get_one_num" << endl;
        exit(0);
    }
    return -1;
}

vector <int> Graph::get_num(string line)
{
    vector <int> ret;
    try{
        int pos;
        while((pos = line.find(" "))!=string::npos)
        {
            int u = get_one_num(line.substr(0,pos));
            ret.push_back(u);
            line = line.substr(pos+1);
            //cout << line << endl;
        }
        ret.push_back(get_one_num(line));
    } catch (const invalid_argument& e) {
        cerr << "error in get_two_num" << endl;
    }
    return ret;
}

pair < pair <int, int> , double > Graph::get_edge(string line)
{
    //vector <int> ret;
    pair <int, int> r;
    double w = INF;
    try{
        istringstream ss(line);
        ss >> r.first >> r.second >> w;
        //fprintf(stderr, "[%d %d]: %.10lf\n", r.first, r.second, w);
        // int pos;
        // while((pos = line.find(" "))!=string::npos)
        // {
        //     int u = get_one_num(line.substr(0,pos));
        //     ret.push_back(u);
        //     line = line.substr(pos+1);
        //     //cout << line << endl;
        // }
        // if(ret.size() == 2) w = get_one_double(line);
        // else ret.push_back(get_one_num(line));
    } catch (const invalid_argument& e) {
        cerr << "error in get_two_num" << endl;
    }
    //r = {ret[0], ret[1]};
    return make_pair(r, w);
}

void Graph::build_ed()
{
    for(int i = 0; i <= n; i++)
        ed.push_back(vector < pair <int, double> > ());
    for(auto [e, w]: edge)
    {
        auto [u, v] = e;
        //cout << "[" << u << "," << v << "," << w << "]" << endl;
        auto ve = make_pair(v, u);
        if(gval.find(e) != gval.end())
        {
            gval[e] = min(gval[e], w);
            gval[ve] = min(gval[ve], w);
        }
        else
        {
            gval[e] = w;
            gval[ve] = w;
        }

        ed[u].push_back(make_pair(v, w));
        ed[v].push_back(make_pair(u, w));
    }
}

void Graph::clear()
{
    n = 0;
    gval.clear();
    edge.clear();
    ed.clear();
}

void Graph::random_graph_nm(int n_,int m_,int M)
{
    clear();
    n = n_;
    for(int i = 1; i <= m_; i++)
    {
        int u = generateRandomNumber(1, n);
        int v = generateRandomNumber(1, n);
        int w = generateRandomNumber(1, M);
        edge.push_back(make_pair(make_pair(u, v), w));
    }
    build_ed();
}

void Graph::random_graph_real(int n_, int m_, double M)
{
    clear();
    n = n_;
    for(int i = 1; i <= m_; i++)
    {
        int u = generateRandomNumber(1, n);
        int v = generateRandomNumber(1, n);
        double w = getRandomRealNumber(0, M);
        edge.push_back(make_pair(make_pair(u, v), w));
    }
    build_ed();
}

vector<int> extractIntegers(const string& input) 
{
    vector<int> integers;
    istringstream iss(input);
    string token;

    while (iss >> token) 
    {
        try 
        {
            int number = stoi(token);
            integers.push_back(number);
        } catch (const invalid_argument&) 
        {
            cerr << "not a number" << endl;
        }
    }

    return integers;
}


void Graph::read(string filename = "Data/graph.in", int typ = 0)
{
    clear();
    //string filename = "Data/graph.in";

    ifstream inputFile(filename);

    if (!inputFile.is_open()) 
        cerr << "Can't open file: " << filename << endl;

    string line;
    getline(inputFile, line);

    n = extractIntegers(line)[0];
    //get_one_num(line);

    while (getline(inputFile, line)) 
    {
        //cout << line << endl;
        auto [e, w] = get_edge(line);
        if(abs(INF-w) < eps) edge.push_back(make_pair(e, 1));
        else edge.push_back(make_pair(e, w));

        // auto num = extractIntegers(line);
        // if(num.size() == 2 || num.size() == 3)
        //     edge.push_back(make_pair(make_pair(num[0] + typ, num[1] + typ), num.size()==2? 1: num[2]));
        // else
        // {
        //     cerr << "Input invalid!" << endl;
        //     exit(0);
        // }
    }
    build_ed();
    inputFile.close();
}

void Tree::random_tree(int n_, int M)
{
    clear();
    n = n_;
    for(int i = 1; i < n; i++)
    {
        int u = generateRandomNumber(1, n);
        int v = generateRandomNumber(1, n);
        int w = generateRandomNumber(1, M);
        edge.push_back(make_pair(make_pair(u, v), w));
    }
    build_ed();
}
/*检测是否为树，待修改*/
bool Tree::check_tree()
{
    if(edge.size() != n-1) return false;
    vector <int> f(n+1);
    for(int i = 1; i <= n; i++) f[i] = i;
    auto Find = [&f](int x) {
        vector <int> rev;
        while(f[x] != x)
        {
            rev.push_back(x);
            x = f[x];
        }
        for(auto y: rev)
            f[y] = x;
        return x;
    };
    for(auto [e, w]: edge)
    {
        auto [u, v] = e;
        if(Find(u) == Find(v)) return false;
        f[Find(u)] = Find(v);
    }
    return true;
}

void Tree::clear()
{
    vex.clear();
    Id.clear();
    par.clear();
    chi.clear();
    n = rt = 0;
}

void Tree::add_vex(int u)
{
    if(Id.find(u) == Id.end()) 
    {
        Id[u] = n++;
        chi.push_back(set <int> ());
        par.push_back(-1);
        vex.insert(u);
    }    
}

void Tree::add_root(int u)
{
    rt = u;
    add_vex(u);
}

void Tree::add_edge(int u, int v)
{
    add_vex(u), add_vex(v);
    //fprintf(stderr, "addedge: %d %d\n", Id[u], Id[v]);
    chi[Id[u]].insert(Id[v]);
    par[Id[v]] = Id[u];
}

int Tree::GET_UD_T(int u,int v)
{
    map <int, int> h;
    int tu = Id[u], ct = 0;
    while(tu != Id[rt])
    {
        h[tu] = ct++;
        tu = par[tu];
    }
    h[tu] = ct++;

    int tv = Id[v]; 
    ct = 0;
    while(h.find(tv) == h.end())
    {
        ct++;
        tv = par[tv];
    }
    return h[tv] + ct;
}

double Tree::get_sumvalue()
{
    double ret = 0;
    map <int, int> fid;
    for(auto [u, nu]: Id)
        fid[nu] = u;
    for(int i = 0; i < chi.size(); i++) 
        for(auto v: chi[i])
            ret += gval[make_pair(fid[i], fid[v])];
            //fprintf(stderr, "[%d %d]\n", fid[i], fid[v]);
    return ret;
}

void Tree::Print()
{
    map <int, int> fid;
    fprintf(stderr, "The point are: ");
    for(auto x: vex)
        fprintf(stderr, "%d ", x);
    fprintf(stderr, "\nThe edges are:\n");

    for(auto [u, nu]: Id)
        fid[nu] = u;
    for(int i = 0; i < chi.size(); i++) 
        for(auto v: chi[i])
            fprintf(stderr, "[%d %d]\n", fid[i], fid[v]);
    fprintf(stderr, "\n");
}

void Tree::Print_to_file(string prefile, int qid, int D, vector <int> M)
{
    string folderName = prefile + '/' +to_string(qid);

    struct stat info;
    if (stat(folderName.c_str(), &info) != 0) 
    {
        // 子文件夹不存在，创建它
        int status = mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (status != 0) 
        {
            std::cerr << "无法创建子文件夹" << std::endl;
            return;
        }
    }

    ofstream outputFile(folderName + "/diameter_" + to_string(D) + "_result.txt");

    outputFile << "D is "  << D << endl;
    outputFile << "The point are: ";
    
    for(auto x: vex)
        outputFile << x << " ";
    outputFile << endl;

    outputFile << "The edges are: ";
    
    map <int, int> fid;
    for(auto [u, nu]: Id)
        fid[nu] = u;
    for(int i = 0; i < chi.size(); i++) 
        for(auto v: chi[i])
            outputFile << "[" << fid[i] << " " << fid[v] << "]" << endl;

    outputFile << "Query size is: " << M.size() << endl;
    for(auto x: M) outputFile << x << " ";
    outputFile << endl;

    outputFile << "The sum weight of Tree is: " << get_sumvalue() << endl;

    outputFile.close();
}

double get_now_time()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());
    return ms.count();
}