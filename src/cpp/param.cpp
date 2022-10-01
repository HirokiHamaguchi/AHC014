#include <bits/stdc++.h>  // clang-format off
using namespace std;constexpr int INF=1001001001;constexpr long long INFll=1001001001001001001;namespace viewer{using s=string;template<class T>s f(T i){s S=i==INF||i==INFll?"inf":to_string(i);return s(max(0,3-int(S.size())),' ')+S;}
template<class T>auto v(T&x,s&&e)->decltype(cerr<<x){return cerr<<x<<e;}void v(int x,s&&e){cerr<<f(x)<<e;}void v(long long x,s&&e){cerr<<f(x)<<e;}void v(float x,s&&e){cerr<<fixed<<setprecision(5)<<x<<e;}void v(double x,s&&e){cerr<<fixed<<setprecision(5)<<x<<e;}void v(long double x,s&&e){cerr<<fixed<<setprecision(5)<<x<<e;}
template<class T,class U>void v(const pair<T,U>&p,s&&e="\n"){cerr<<"(";v(p.first,", ");v(p.second,")"+e);}template<class T,class U>void v(const tuple<T,U>&t,s&&e="\n"){cerr<<"(";v(get<0>(t),", ");v(get<1>(t),")"+e);}template<class T,class U,class V>void v(const tuple<T,U,V>&t,s&&e="\n"){cerr<<"(";v(get<0>(t),", ");v(get<1>(t),", ");v(get<2>(t),")"+e);}template<class T,class U,class V,class W>void v(const tuple<T,U,V,W>&t,s&&e="\n"){cerr<<"(";v(get<0>(t),", ");v(get<1>(t),", ");v(get<2>(t),", ");v(get<3>(t),")"+e);}
template<class T>void v(const vector<T>&vx,s);template<class T>auto ve(int,const vector<T>&vx)->decltype(cerr<<vx[0]){cerr<<"{";for(const T&x:vx)v(x,",");return cerr<<"}\n";}template<class T>auto ve(bool,const vector<T>&vx){cerr<<"{\n";for(const T&x:vx)cerr<<"  ",v(x,",");cerr<<"}\n";}template<class T>void v(const vector<T>&vx,s){ve(0,vx);}
template<class T>void v(const deque<T>&q,s&&e){v(vector<T>(q.begin(),q.end()),e);}template<class T,class C>void v(const set<T,C>&S,s&&e){v(vector<T>(S.begin(),S.end()),e);}template<class T,class C>void v(const multiset<T,C>&S,s&&e){v(vector<T>(S.begin(),S.end()),e);}template<class T>void v(const unordered_set<T>&S,s&&e){v(vector<T>(S.begin(),S.end()),e);}
template<class T,class U,class V>void v(const priority_queue<T,U,V>&p,s&&e){priority_queue<T,U,V>q=p;vector<T>z;while(!q.empty()){z.push_back(q.top());q.pop();}v(z,e);}template<class T,class U>void v(const map<T,U>&m,s&&e){cerr<<"{"<<(m.empty()?"":"\n");for(const auto&kv:m){cerr<<"  [";v(kv.first,"");cerr<<"] : ";v(kv.second,"");cerr<<"\n";}cerr<<"}"+e;}
template<class T>void _view(int n,s&S,T&var){cerr<<"\033[1;32m"<<n<<"\033[0m: \033[1;36m"<<S<<"\033[0m = ";v(var,"\n");}template<class T>void grid([[maybe_unused]]T _){}void grid(const vector<vector<bool>>&vvb){cerr<<"\n";for(const vector<bool>&vb:vvb){for(const bool&b:vb)cerr<<(b?".":"#");cerr<<"\n";}}
void _debug(int,s){}template<typename H,typename... T>void _debug(int n,s S,const H&h,const T&... t){int i=0,cnt=0;for(;i<int(S.size());i++){if(S[i]=='(')cnt++;if(S[i]==')')cnt--;if(cnt==0&&S[i]==',')break;}if(i==int(S.size()))_view(n,S,h);else{s S1=S.substr(0,i),S2=S.substr(i+2);if(S2=="\"grid\""){cerr<<"\033[1;32m"<<n<<"\033[0m: \033[1;36m"<<S1<<"\033[0m = ";grid(h);}else _view(n,S1,h),_debug(n,S2,t...);}}}
template<class T>bool chmax(T&a,const T&b){return a<b?a=b,1:0;}template<class T>bool chmin(T&a,const T&b){return a>b?a=b,1:0;}
#ifndef hari64
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define debug(...)
#else
#define debug(...) viewer::_debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#endif

struct Timer{
    void start(){_start=chrono::system_clock::now();}
    void stop(){_end=chrono::system_clock::now();sum+=chrono::duration_cast<chrono::nanoseconds>(_end-_start).count();}
    inline int ms()const{const chrono::system_clock::time_point now=chrono::system_clock::now();return static_cast<int>(chrono::duration_cast<chrono::microseconds>(now-_start).count()/1000);}
    inline int ns()const{const chrono::system_clock::time_point now=chrono::system_clock::now();return static_cast<int>(chrono::duration_cast<chrono::microseconds>(now-_start).count());}
    string report(){return to_string(sum/1000000)+"[ms]";}
    void reset(){_start=chrono::system_clock::now();sum=0;}
    private: chrono::system_clock::time_point _start,_end;long long sum=0;
}timer;
struct Xor128{// period 2^128 - 1
    uint32_t x,y,z,w;
    static constexpr uint32_t min(){return 0;}
    static constexpr uint32_t max(){return UINT32_MAX;}
    Xor128(uint32_t seed=0):x(123456789),y(362436069),z(521288629),w(88675123+seed){}
    uint32_t operator()(){uint32_t t=x^(x<<11);x=y;y=z;z=w;return w=(w^(w>>19))^(t^(t>>8));}
    uint32_t operator()(uint32_t l,uint32_t r){return((*this)()%(r-l))+l;}
    uint32_t operator()(uint32_t r){return(*this)()%r;}};
struct Rand{// https://docs.python.org/ja/3/library/random.html
    Rand(){};
    Rand(int seed):gen(seed){};
    // シードを変更します
    inline void set_seed(int seed){Xor128 _gen(seed);gen=_gen;}
    // ランダムな浮動小数点数（範囲は[0.0, 1.0)) を返します
    inline double random(){return(double)gen()/(double)gen.max();}
    // a <= b であれば a <= N <= b 、b < a であれば b <= N <= a であるようなランダムな浮動小数点数 N を返します
    inline double uniform(double a,double b){if(b<a)swap(a,b);return a+(b-a)*double(gen())/double(gen.max());}
    // range(0, stop) の要素からランダムに選ばれた要素を返します
    inline uint32_t randrange(uint32_t r){return gen(r);}
    // range(start, stop) の要素からランダムに選ばれた要素を返します
    inline uint32_t randrange(uint32_t l,uint32_t r){return gen(l,r);}
    // a <= N <= b であるようなランダムな整数 N を返します randrange(a, b + 1) のエイリアスです
    inline uint32_t randint(uint32_t l,uint32_t r){return gen(l,r+1);}
    // シーケンス x をインプレースにシャッフルします
    template<class T>void shuffle(vector<T>&x){for(int i=x.size(),j;i>1;){j=gen(i);swap(x[j],x[--i]);}}
    // 空でないシーケンス seq からランダムに要素を返します
    template<class T>T choice(const vector<T>&seq){assert(!seq.empty());return seq[gen(seq.size())];}
    // 相対的な重みに基づいて要素が選ばれます (※複数回呼ぶ場合は処理を変えた方が良い)
    template<class T,class U>T choice(const vector<T>&seq,const vector<U>&weights){assert(seq.size()==weights.size());vector<U>acc(weights.size());acc[0]=weights[0];for(int i=1;i<int(weights.size());i++)acc[i]=acc[i-1]+weights[i];return seq[lower_bound(acc.begin(),acc.end(),random()*acc.back())-acc.begin()];}
    // 母集団のシーケンスまたは集合から選ばれた長さ k の一意な要素からなるリストを返します 重複無しのランダムサンプリングに用いられます
    template<class T>vector<T>sample(const vector<T>&p,int k){int j,i=0,n=p.size();assert(0<=k&&k<=n);vector<T>ret(k);unordered_set<int>s;for(;i<k;i++){do{j=gen(n);}while(s.find(j)!=s.end());s.insert(j);ret[i]=p[j];}return ret;}
    // 正規分布です mu は平均で sigma は標準偏差です
    double normalvariate(double mu=0.0,double sigma=1.0){double u2,z,NV=4*exp(-0.5)/sqrt(2.0);while(true){u2=1.0-random();z=NV*(random()-0.5)/u2;if(z*z/4.0<=-log(u2))break;}return mu+z*sigma;}
    private: Xor128 gen;
}myrand;

namespace esc{const vector<int>colors{196,208,226,46,77,14,12,13,5,136,195,245};constexpr int RED=0,ORANGE=1,YELLOW=2,LIGHTGREEN=3,GREEN=4,AQUA=5,BLUE=6,PINK=7,PURPLE=8,BROWN=9,WHITE=10,GRAY=11;
void back(int n){cerr<<"\e["<<n<<"A";}void locate(int r,int c){cerr<<"\e["<<r+1<<+";"<<c+1<<"H";}void reset(){cerr<<"\e[0m";}
void color(int c){cerr<<"\e[38;5;"<<colors[c]<<"m";}void color(int c,string s){color(c);cerr<<s;reset();}void color(int c,int s){color(c,to_string(s));}
void bcolor(int c){cerr<<"\e[4;"<<colors[c]<<"m";}void bcolor(int c,string s){bcolor(c);cerr<<s;reset();}void bcolor(int c,int s){color(c,to_string(s));}
string with_sep(int n,char sep=','){string ret="",s=to_string(n);reverse(s.begin(),s.end());for(int i=0,len=s.length();i<=len;){ret+=s.substr(i,3);if((i+=3)>=len)break;ret+=sep;}reverse(ret.begin(),ret.end());return ret;}
string with_fill(int n,int num=3,char space=' '){string s=to_string(n);return string(max(0,num-int(s.size())),space)+s;}
// **VISUALIZER-TEMPLATE**
// int N=20,M=30,vis_length=10;
// for(int vis_cnt=1;vis_cnt<=vis_length;vis_cnt++){cerr<<esc::with_fill(vis_cnt)<<"/"<<vis_length<<endl;cerr<<"";
// for(int x=0;x<M;x++)esc::color(esc::GRAY,x%10);cerr<<""<<endl;
// for(int y=0;y<N;y++){esc::color(esc::GRAY,y%10);esc::reset();
// for(int x=0;x<M;x++){/*wirte here*/esc::bcolor(y%10,myrand.randint(0,9));}esc::color(esc::GRAY,y%10);cerr<<endl;}cerr<<"";
// for(int x=0;x<M;x++)esc::color(esc::GRAY,x%10);cerr<<""<<endl;if(vis_cnt<vis_length)esc::back(N+2+1);usleep(1.0*1000000);}
}// namespace esc

struct YX {
    int y, x;
    YX() : y(-1), x(-1) {}
    YX(int y, int x) : y(y), x(x) {}
    int abs() const { return std::abs(y) + std::abs(x); }
    bool operator==(YX const& r) const { return y == r.y && x == r.x; }
    bool operator!=(YX const& r) const { return !((*this) == r); }
    bool operator<(YX const& r) const { return y == r.y ? x < r.x : y < r.y; }
    bool operator>(YX const& r) const { return r < (*this); }
    YX& operator+=(YX const& r) { y += r.y; x += r.x; return *this; }
    YX& operator-=(YX const& r) { y -= r.y; x -= r.x; return *this; }
    YX operator+(YX const& r) const { return YX{y + r.y, x + r.x}; }
    YX operator-(YX const& r) const { return YX{y - r.y, x - r.x}; }
    YX operator*(int const& v) { return YX{x * v, y * v}; }
    YX operator/(int const& v) { return YX{x / v, y / v}; }
    YX& operator*=(int const& v) { x *= v; y *= v; return *this; }
    YX& operator/=(int const& v) { x /= v; y /= v; return *this; }
    YX operator-() const { return YX{-x, -y}; }
    void flip() { swap(x, y); }
    friend istream& operator>>(istream& is, YX& r) { return is >> r.x >> r.y; }
    friend ostream& operator<<(ostream& os, YX const& r) { return os << r.x << " " << r.y; }
};
// clang-format on

int N;
int M;
vector<YX> POINTS;
vector<vector<int>> wTable;

constexpr int dirLen = 8;
constexpr int DX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
constexpr int DY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

constexpr int maxN = 61;
constexpr int PATTERN_NUM = 16;
constexpr int HASH_SIZE = 16;
constexpr int BEAM_TL = 4600;
constexpr int CHOKUDAI_TL = 4800;
constexpr int TRUE_TL = 5000;

int BOUNDARY_LOOPCNT;
int SECURE_PATTERN_NUM;
int BW_1;
int BW_2;

using Bitset = bitset<maxN * maxN * dirLen>;
using Grid = bitset<maxN * maxN>;

int initSumW;
double scoreCoef;
size_t BEAM_WIDTH;

inline int to_idx2(int y, int x) { return y * N + x; };
inline int to_idx2(const YX& yx) { return to_idx2(yx.y, yx.x); };
inline int to_idx3(int y, int x, int dir) {
    return to_idx2(y, x) * dirLen + dir;
};
inline int to_idx3(const YX& yx, int dir) { return to_idx3(yx.y, yx.x, dir); };
inline pair<int, int> to_hw(int idx) { return {idx / N, idx % N}; };
inline int sign(int val) { return (0 < val) - (val < 0); }
int getDir(int dy, int dx) {
    dy = sign(dy), dx = sign(dx);
    for (int dir = 0; dir < 8; dir++)
        if (dx == DX[dir] && dy == DY[dir]) return dir;
    assert(false);
}
int getDir(const YX& yx) { return getDir(yx.y, yx.x); }

struct Hash {
    vector<int> hash;
    Hash() {}
    void setup() {
        hash.resize(N * N * dirLen);
        for (int i = 0; i < N * N * dirLen; i++)
            hash[i] = myrand.randint(0, 1 << HASH_SIZE);
    }
    inline int get2(int y, int x) { return hash[to_idx2(y, x)]; }
    inline int get2(const YX& yx) { return hash[to_idx2(yx)]; }
    inline int get3(int y, int x, int dir) { return hash[to_idx3(y, x, dir)]; }
} HASH;

struct Rect {
    YX YXs[4];
    bool is_ok = false;

    Rect() {}
    Rect(int y1, int x1, int y2, int x2, int y3, int x3, int y4, int x4,
         int pattern) {
        YXs[0] = YX(y1, x1);
        YXs[1] = YX(y2, x2);
        YXs[2] = YX(y3, x3);
        YXs[3] = YX(y4, x4);
        int dir1 = getDir(YXs[1] - YXs[0]), dir2 = getDir(YXs[2] - YXs[1]),
            dir3 = getDir(YXs[3] - YXs[2]), dir4 = getDir(YXs[0] - YXs[3]);
        assert((dir1 + 2) % dirLen == dir2 && (dir2 + 2) % dirLen == dir3 &&
               (dir3 + 2) % dirLen == dir4 && (dir4 + 2) % dirLen == dir1);
        is_ok = _is_ok(pattern);
    }

    inline int dir() const { return getDir(YXs[1] - YXs[0]); }
    inline int getW() const { return wTable[YXs[0].y][YXs[0].x]; }
    inline int len() const {
        YX d1 = YXs[1] - YXs[0], d2 = YXs[3] - YXs[0];
        return (max(abs(d1.x), abs(d1.y)) + max(abs(d2.x), abs(d2.y)));
    }
    inline int size() const {
        YX d1 = YXs[1] - YXs[0], d2 = YXs[2] - YXs[0], d3 = YXs[3] - YXs[0];
        return (abs(d1.x * d2.y - d2.x * d1.y) +
                abs(d3.x * d2.y - d2.x * d3.y)) /
               2;
    }
    inline bool is_valid() const {
        assert((YXs[0].y != -1 && YXs[0].x != -1) ||
               (YXs[0] == YXs[1] && YXs[1] == YXs[2] && YXs[2] == YXs[3]));
        return YXs[0].y != -1;
    }

    YX topRight() const {
        return YX(max({YXs[0].y, YXs[1].y, YXs[2].y, YXs[3].y}),
                  max({YXs[0].x, YXs[1].x, YXs[2].x, YXs[3].x}));
    }

    int getRegion() const {
        int ret = -1;
        for (int i = 0; i < 4; i++) {
            int r = _regionPoint(YXs[i]);
            if (r == -1) return -1;
            if (i == 0) ret = r;
            if (ret != r) return -1;
        }
        return ret;
    }

    bool containPoint(const YX& p) const {
        return p == YXs[0] || p == YXs[1] || p == YXs[2] || p == YXs[3];
    }

    bool operator==(Rect const& r) const {
        return YXs[0] == r.YXs[0] && YXs[1] == r.YXs[1] && YXs[2] == r.YXs[2] &&
               YXs[3] == r.YXs[3];
    }
    friend ostream& operator<<(ostream& os, const Rect& rect) {
        return os << rect.YXs[0] << " " << rect.YXs[1] << " " << rect.YXs[2]
                  << " " << rect.YXs[3];
    }

   private:
    int _regionPoint(const YX& point) const {
        // -1    -1
        //    1
        //  2 -2 0
        //    3
        // -1    -1
        if (point.y == point.x || point.y + point.x == N - 1) {
            return (point.y == point.x && point.y + point.x == N - 1) ? -2 : -1;
        } else {
            return (int(point.y + point.x < N) * 3) ^ int((point.y > point.x));
        }
    }

    int _isNearBorder(const YX& point) const {
        return abs(point.y - point.x) == 1 ||
               abs(point.y + point.x - N + 1) == 1;
    }

    bool _is_ok(const int pattern) const {
        assert(0 <= pattern && pattern < PATTERN_NUM);
        if (len() == 2) {
            if (getDir(YXs[1] - YXs[0]) % 2 == 0) {
                // □
                YX tr = topRight();
                return abs(tr.y - tr.x) % 2 == (pattern & 1);
            } else {
                // ◇
                int centerx = YXs[0].x + YXs[1].x + YXs[2].x + YXs[3].x;
                int centery = YXs[0].y + YXs[1].y + YXs[2].y + YXs[3].y;
                assert(centerx % 4 == 0 && centery % 4 == 0);
                centerx /= 4;
                centery /= 4;
                if ((pattern >> 3) & 1) {
                    // (pattern>>2) & 1は使用しない
                    int r = _regionPoint(YX(centery, centerx));
                    if (r < 0) return r == -2;
                    if (r % 2) {
                        return (centerx % 2 == (N / 4) % 2) ^
                               ((pattern >> 2) & 1);
                    } else {
                        return (centery % 2 != (N / 4) % 2) ^
                               ((pattern >> 2) & 1);
                    }
                } else {
                    // return centery % 2 == ((pattern >> 1) & 1) &&
                    //        centerx % 2 == ((pattern >> 2) & 1);
                    if ((pattern >> 1) & 1) {
                        return centery % 2 == ((pattern >> 2) & 1);
                    } else {
                        return centerx % 2 == ((pattern >> 2) & 1);
                    }
                }
            }
        }
        return false;
    }
};
using Rects = vector<Rect>;

int calcRawScore(const Rects& ans, const double init = initSumW) {
    double sumW = init;
    for (auto& r : ans) sumW += r.getW();
    return int(round(scoreCoef * sumW));
}
int calcRawScore(const Rects& ans, const Rects& newlyAns,
                 const double init = initSumW) {
    double sumW = init;
    for (auto& r : ans) sumW += r.getW();
    for (auto& r : newlyAns) sumW += r.getW();
    return int(round(scoreCoef * sumW));
}

void readInput(int seed) {
    ifstream reading_file;
    reading_file.open("./input2/" + esc::with_fill(seed, 4, '0') + ".txt",
                      ios::in);

    reading_file >> N >> M;
    POINTS.resize(M);
    for (int i = 0; i < M; i++) reading_file >> POINTS[i];

    string _no_str;
    reading_file >> _no_str;
    assert(_no_str == string("") && reading_file.eof());
    reading_file.close();

    auto w = [&](int y, int x) -> int {
        int c = (N - 1) / 2;
        return (x - c) * (x - c) + (y - c) * (y - c) + 1;
    };
    double S = 0;
    wTable.resize(N);
    for (int y = 0; y < N; y++) {
        wTable[y].resize(N);
        for (int x = 0; x < N; x++) {
            wTable[y][x] = w(y, x);
            S += wTable[y][x];
        }
    }
    initSumW = 0;
    for (auto& p : POINTS) initSumW += wTable[p.y][p.x];
    scoreCoef = 1e6 * (double(N * N) / double(M)) / double(S);
    BEAM_WIDTH = int(round(BW_1 + BW_2 / (double(N * N * N) / double(M))));
    HASH.setup();
}

void printAns(const Rects& ans) {
#ifdef TEST
    cerr << ans.size() << endl;
    for (auto& r : ans) cerr << r << endl;
    cout << calcRawScore(ans) << endl;
#else
    cout << ans.size() << endl;
    for (auto& r : ans) cout << r << endl;
    debug(calcRawScore(ans));
#endif
}

int MODE = -1;
struct StateInfo {
    int prevStateIdx = -1;    // chokudaiSearch
    bool doApplyAll = false;  // chokudaiSearch

    int stateIdx = -1;
    int candIdx = -1;
    int pattern = -1;
    int ok_nums = 0;
    int blocked = 0;
    int numNewPoints = 0;
    int _grid_hash = 0;
    int _used_hash = 0;
    float _temporaryScore = -INF;

    StateInfo() {}
    StateInfo(int stateIdx, int candIdx, int pattern, int ok_nums, int blocked,
              int numNewPoints)
        : stateIdx(stateIdx),
          candIdx(candIdx),
          pattern(pattern),
          ok_nums(ok_nums),
          blocked(blocked),
          numNewPoints(numNewPoints) {}

    inline int hash() const { return (_grid_hash << HASH_SIZE) + _used_hash; }

    void setTemporaryScore(int loop_cnt, const Rects& ans,
                           const Rects& newlyAns) {
        if (MODE == 100) {
            _temporaryScore =
                calcRawScore(ans, newlyAns) * (0.9 + 0.2 * myrand.random());
            return;
        }
        if (loop_cnt < BOUNDARY_LOOPCNT) {
            if (MODE == 0) {
                _temporaryScore = ok_nums * (0.9 + 0.2 * myrand.random());
            } else if (MODE == 1) {
                _temporaryScore = sqrt(sqrt(1 + ok_nums)) *
                                  calcRawScore(ans, newlyAns) *
                                  (0.9 + 0.2 * myrand.random());
            } else {
                assert(false);
            }
        } else {
            _temporaryScore = calcRawScore(ans, newlyAns);
        }
    }
    int getTemporaryScore() const {
        assert(_temporaryScore != -1);
        return _temporaryScore;
    }

    friend ostream& operator<<(ostream& os, const StateInfo& info) {
        return os << "[Idx: " << info.stateIdx << "-" << info.candIdx
                  << ", pattern: " << info.pattern
                  << ", ok_nums: " << info.ok_nums
                  << ", blocked: " << info.blocked
                  << ", numNewPoints: " << info.numNewPoints
                  << ", _grid_hash: " << info._grid_hash
                  << ", _used_hash: " << info._used_hash
                  << ", _temporaryScore:" << info._temporaryScore << "]"
                  << endl;
    }
};

struct State {
    int stateIdx = -1;  // chokudaiSearch

    Bitset used;
    Grid grid;
    Rects cands;
    Rects ans;
    StateInfo info;

    State() {}
    State(int pattern, bool do_setup = true) : info(-1, -1, pattern, 0, 0, 0) {
        assert(!do_setup ^ (0 <= pattern && pattern < PATTERN_NUM));
        used.reset();
        grid.reset();
        if (do_setup) setup();
    }

    void setup() {
        for (auto& p : POINTS) {
            grid[to_idx2(p)] = 1;
            info._grid_hash ^= HASH.get2(p);
        }
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                if (grid[to_idx2(y, x)]) {
                    for (int dir = 0; dir < dirLen; dir++) {
                        const Rect rect = getDoubleNext(y, x, dir);
                        if (rect.is_valid()) {
                            cands.push_back(rect);
                        }
                    }
                }
            }
        }
    }

    tuple<int, int, int> getNext(int y, int x, int dir) const {
        if (y == -1 || x == -1) return {-1, -1, -1};
        int len = 0;
        while (0 < x && x < N - 1 && 0 < y && y < N - 1) {
            if (used[to_idx3(y, x, dir)]) return {-1, -1, -1};
            y += DY[dir], x += DX[dir];
            len++;
            if (grid[to_idx2(y, x)]) return {y, x, len};
        }
        return {-1, -1, -1};
    }

    tuple<int, int> getNextWithLen(int y, int x, int dir, int len) const {
        if (y == -1 || x == -1) return {-1, -1};
        int cnt = 0;
        while (0 < x && x < N - 1 && 0 < y && y < N - 1) {
            if (used[to_idx3(y, x, dir)]) return {-1, -1};
            y += DY[dir], x += DX[dir];
            cnt++;
            if (grid[to_idx2(y, x)] || cnt == len) return {y, x};
        }
        return {-1, -1};
    }

    Rect getDoubleNext(int y, int x, int dir) const {
        assert(grid[to_idx2(y, x)]);
        int dir1 = dir, dir2 = (dir + 2) % dirLen;
        auto [ny11, nx11, len1] = getNext(y, x, dir1);
        auto [ny12, nx12, len2] = getNext(y, x, dir2);
        if (ny11 == -1 || ny12 == -1) return Rect();
        auto [ny21, nx21] = getNextWithLen(ny11, nx11, dir2, len2);
        auto [ny22, nx22] = getNextWithLen(ny12, nx12, dir1, len1);
        if (ny21 != -1 && ny22 != -1 && ny21 == ny22 && nx21 == nx22 &&
            !grid[to_idx2(ny21, nx21)]) {
            return Rect(ny21, nx21, ny12, nx12, y, x, ny11, nx11, info.pattern);
        }
        return Rect();
    }

    Rect getTripleNext(int y, int x, int dir, bool rectDir) const {
        assert(grid[to_idx2(y, x)]);
        int dir1 = dir, dir2 = (dir + (rectDir ? 2 : 6)) % dirLen,
            dir3 = (dir + (rectDir ? 2 : 6) * 2) % dirLen;
        auto [ny1, nx1, len1] = getNext(y, x, dir1);
        if (ny1 == -1) return Rect();
        auto [ny2, nx2, len2] = getNext(ny1, nx1, dir2);
        if (ny2 == -1) return Rect();
        auto [ny3, nx3] = getNextWithLen(ny2, nx2, dir3, len1);
        if (ny3 == -1) return Rect();
        auto [ny4, nx4] = getNextWithLen(y, x, dir2, len2);
        if (ny4 != -1 && nx4 != -1 && ny3 == ny4 && nx3 == nx4 &&
            !grid[to_idx2(ny3, nx3)]) {
            if (rectDir)
                return Rect(ny3, nx3, y, x, ny1, nx1, ny2, nx2, info.pattern);
            else
                return Rect(ny3, nx3, ny2, nx2, ny1, nx1, y, x, info.pattern);
        }
        return Rect();
    }

    void fillUsed(const Rect& rect) {
        for (auto i = 0; i < 4; i++) {
            int x = rect.YXs[i].x, y = rect.YXs[i].y;
            int tx = rect.YXs[(i + 1) % 4].x, ty = rect.YXs[(i + 1) % 4].y;
            int dir = getDir(ty - y, tx - x);
            while (x != tx || y != ty) {
                info.blocked++;
                assert(!used[to_idx3(y, x, dir)]);
                used[to_idx3(y, x, dir)] = true;
                info._used_hash ^= HASH.get3(y, x, dir);
                x += DX[dir];
                y += DY[dir];
                assert(!used[to_idx3(y, x, dir ^ 4)]);
                used[to_idx3(y, x, dir ^ 4)] = true;
                info._used_hash ^= HASH.get3(y, x, dir ^ 4);
            }
            info.blocked--;
        }
    }

    void eraseInvalid() {
        cands.erase(remove_if(cands.begin(), cands.end(),
                              [&](const Rect& cand) {
                                  if (grid[to_idx2(cand.YXs[0])]) return true;
                                  for (auto i = 0; i < 4; i++) {
                                      int x = cand.YXs[i].x, y = cand.YXs[i].y;
                                      int tx = cand.YXs[(i + 1) % 4].x,
                                          ty = cand.YXs[(i + 1) % 4].y;
                                      int dir = getDir(ty - y, tx - x);
                                      while (x != tx || y != ty) {
                                          if (used[to_idx3(y, x, dir)])
                                              return true;
                                          x += DX[dir];
                                          y += DY[dir];
                                          if (used[to_idx3(y, x, dir ^ 4)])
                                              return true;
                                          if (x == tx && y == ty) break;
                                          if (grid[to_idx2(y, x)]) return true;
                                      }
                                  }
                                  return false;
                              }),
                    cands.end());
    }

    // okだけを消すので、衝突が発生しない eraseをしなくてよい
    void applyAllOkRect() {
        deque<Rect> oks;          // ◇より□を優先する
        unordered_set<int> seen;  // 恐らくこれはいらない気もするが...

        cands.erase(remove_if(cands.begin(), cands.end(),
                              [&](const Rect& cand) {
                                  if (cand.is_ok) {
                                      if (cand.dir() % 2 == 0) {
                                          seen.insert(to_idx2(cand.YXs[0]));
                                          oks.push_back(cand);
                                      } else {
                                          oks.push_front(cand);
                                      }
                                      return true;
                                  } else {
                                      return false;
                                  }
                              }),
                    cands.end());

        if (oks.empty()) return;

        while (!oks.empty()) {
            Rect rect = oks.back();
            oks.pop_back();
            if (grid[to_idx2(rect.YXs[0])] ||
                (rect.dir() % 2 == 1 &&
                 seen.find(to_idx2(rect.YXs[0])) != seen.end())) {
                continue;
            }
            int y = rect.YXs[0].y, x = rect.YXs[0].x;
            info.numNewPoints++;
            info.ok_nums++;
            ans.push_back(rect);
            int yx_idx = to_idx2(rect.YXs[0]);
            assert(!grid[yx_idx]);
            grid[yx_idx] = true;
            info._grid_hash ^= HASH.hash[yx_idx];

            fillUsed(rect);

            // 候補への追加
            for (int dir = 0; dir < 8; dir++) {
                vector<Rect> new_rects = {getDoubleNext(y, x, dir),
                                          getTripleNext(y, x, dir, true),
                                          getTripleNext(y, x, dir, false)};
                for (auto& new_rect : new_rects) {
                    if (new_rect.is_valid()) {
                        if (new_rect.is_ok) {
                            if (new_rect.dir() % 2 == 0) {
                                seen.insert(to_idx2(new_rect.YXs[0]));
                                oks.push_back(new_rect);
                            } else {
                                oks.push_front(new_rect);
                            }
                        } else
                            cands.push_back(new_rect);
                    }
                }
            }
        }

        eraseInvalid();
    }

    void applyRect(const int candIdx) {
        assert(0 <= candIdx && candIdx < int(cands.size()));

        // 更新
        int y = cands[candIdx].YXs[0].y, x = cands[candIdx].YXs[0].x;
        info.numNewPoints++;
        if (cands[candIdx].is_ok) info.ok_nums++;
        ans.push_back(cands[candIdx]);
        int yx_idx = to_idx2(cands[candIdx].YXs[0]);
        assert(!grid[yx_idx]);
        grid[yx_idx] = true;
        info._grid_hash ^= HASH.hash[yx_idx];

        fillUsed(cands[candIdx]);

        // 候補から削除
        cands.erase(cands.begin() + candIdx);
        eraseInvalid();

        // 候補への追加
        for (int dir = 0; dir < 8; dir++) {
            Rect new_rect1 = getDoubleNext(y, x, dir);
            if (new_rect1.is_valid()) cands.push_back(new_rect1);
            Rect new_rect2 = getTripleNext(y, x, dir, true);
            if (new_rect2.is_valid()) cands.push_back(new_rect2);
            Rect new_rect3 = getTripleNext(y, x, dir, false);
            if (new_rect3.is_valid()) cands.push_back(new_rect3);
        }
    }

    void applyRectByRect(const Rect& rect) {
        // 更新
        int y = rect.YXs[0].y, x = rect.YXs[0].x;
        info.numNewPoints++;
        if (rect.is_ok) info.ok_nums++;
        ans.push_back(rect);
        int yx_idx = to_idx2(rect.YXs[0]);
        assert(!grid[yx_idx]);
        grid[yx_idx] = true;
        info._grid_hash ^= HASH.hash[yx_idx];

        fillUsed(rect);

        // 候補から削除
        cands.erase(remove_if(cands.begin(), cands.end(),
                              [&](const Rect& cand) { return cand == rect; }),
                    cands.end());
        eraseInvalid();

        // 候補への追加
        for (int dir = 0; dir < 8; dir++) {
            Rect new_rect1 = getDoubleNext(y, x, dir);
            if (new_rect1.is_valid()) cands.push_back(new_rect1);
            Rect new_rect2 = getTripleNext(y, x, dir, true);
            if (new_rect2.is_valid()) cands.push_back(new_rect2);
            Rect new_rect3 = getTripleNext(y, x, dir, false);
            if (new_rect3.is_valid()) cands.push_back(new_rect3);
        }
    }

    StateInfo IfDoTheStep(const int loop_cnt, const int stateIdx,
                          const int candIdx) {
        assert(0 <= candIdx && candIdx < int(cands.size()) &&
               info.stateIdx == -1 && info.candIdx == -1);

        StateInfo z_info = info;
        Bitset z_used = used;
        Grid z_grid = grid;

        info.stateIdx = stateIdx;
        info.candIdx = candIdx;

        deque<Rect> oks;          // ◇より□を優先する
        unordered_set<int> seen;  // 恐らくこれはいらない気もするが...

        // for (auto& cand : cands) {
        //     if (cand.is_ok) {
        //         assert(false);
        //     }
        // }

        assert(!cands[candIdx].is_ok);
        oks.push_back(cands[candIdx]);

        Rects newlyAns;
        while (!oks.empty()) {
            Rect rect = oks.back();
            oks.pop_back();
            if (grid[to_idx2(rect.YXs[0])] ||
                (rect.dir() % 2 == 1 &&
                 seen.find(to_idx2(rect.YXs[0])) != seen.end())) {
                continue;
            }
            int y = rect.YXs[0].y, x = rect.YXs[0].x;
            info.numNewPoints++;
            if (rect.is_ok) {
                // 最初に適用するrectはokでない
                info.ok_nums++;
            }
            newlyAns.push_back(rect);
            int yx_idx = to_idx2(rect.YXs[0]);
            assert(!grid[yx_idx]);
            grid[yx_idx] = true;
            info._grid_hash ^= HASH.hash[yx_idx];

            fillUsed(rect);

            for (int dir = 0; dir < 8; dir++) {
                vector<Rect> new_rects = {getDoubleNext(y, x, dir),
                                          getTripleNext(y, x, dir, true),
                                          getTripleNext(y, x, dir, false)};
                for (auto& new_rect : new_rects) {
                    if (new_rect.is_valid()) {
                        if (new_rect.is_ok) {
                            if (new_rect.dir() % 2 == 0) {
                                seen.insert(to_idx2(new_rect.YXs[0]));
                                oks.push_back(new_rect);
                            } else {
                                oks.push_front(new_rect);
                            }
                        }
                    }
                }
            }
        }

        info.setTemporaryScore(loop_cnt, ans, newlyAns);

        swap(info, z_info);
        swap(used, z_used);
        swap(grid, z_grid);

        return z_info;
    }

    pair<StateInfo, StateInfo> IfDoTheStep2(const int dep, const int candIdx) {
        assert(0 <= candIdx && candIdx < int(cands.size()));

        StateInfo ret_info;
        StateInfo z_info = info;
        Bitset z_used = used;
        Grid z_grid = grid;

        info.prevStateIdx = stateIdx;
        info.candIdx = candIdx;

        deque<Rect> oks;          // ◇より□を優先する
        unordered_set<int> seen;  // 恐らくこれはいらない気もするが...

        // assert(!cands[candIdx].is_ok);
        oks.push_back(cands[candIdx]);

        Rects newlyAns;
        bool is_first = true;
        while (!oks.empty()) {
            Rect rect = oks.back();
            oks.pop_back();
            if (grid[to_idx2(rect.YXs[0])] ||
                (rect.dir() % 2 == 1 &&
                 seen.find(to_idx2(rect.YXs[0])) != seen.end())) {
                continue;
            }
            int y = rect.YXs[0].y, x = rect.YXs[0].x;
            info.numNewPoints++;
            if (rect.is_ok) {
                // 最初に適用するrectはokでない
                info.ok_nums++;
            } else {
                assert(is_first);
            }
            newlyAns.push_back(rect);
            int yx_idx = to_idx2(rect.YXs[0]);
            assert(!grid[yx_idx]);
            grid[yx_idx] = true;
            info._grid_hash ^= HASH.hash[yx_idx];

            fillUsed(rect);

            for (int dir = 0; dir < 8; dir++) {
                vector<Rect> new_rects = {getDoubleNext(y, x, dir),
                                          getTripleNext(y, x, dir, true),
                                          getTripleNext(y, x, dir, false)};
                for (auto& new_rect : new_rects) {
                    if (new_rect.is_valid()) {
                        if (new_rect.is_ok) {
                            if (new_rect.dir() % 2 == 0) {
                                seen.insert(to_idx2(new_rect.YXs[0]));
                                oks.push_back(new_rect);
                            } else {
                                oks.push_front(new_rect);
                            }
                        }
                    }
                }
            }
            if (is_first) {
                is_first = false;
                ret_info = info;
                ret_info.setTemporaryScore(dep, ans, newlyAns);
                ret_info.doApplyAll = false;
            }
        }
        assert(info.numNewPoints == int(ans.size() + newlyAns.size()));
        info.setTemporaryScore(dep, ans, newlyAns);
        info.doApplyAll = true;

        swap(info, z_info);
        swap(used, z_used);
        swap(grid, z_grid);

        return {ret_info, z_info};
    }
};

bool compare(const StateInfo& a, const StateInfo& b) {
    return a.getTemporaryScore() < b.getTemporaryScore();
};
using PQ = priority_queue<StateInfo, vector<StateInfo>,
                          function<bool(const StateInfo&, const StateInfo&)>>;

void genTxtOfBeamContent(const State& state) {
    ofstream writing_file;
    writing_file.open("beamContent" + to_string(state.info.hash()) + ".txt",
                      ios::out);
    writing_file << to_string(state.ans.size()) << endl;
    for (auto& r : state.ans) writing_file << r << endl;
    writing_file.close();
}

void transferBeam(vector<State>& nowBeam, PQ& nextBeam, int loop_cnt) {
    vector<State> newNowBeam;
    set<int> seen;
    vector<int> seen_patterns(PATTERN_NUM, 0);
    int now = timer.ms();
    if (now > BEAM_TL) BEAM_WIDTH = 5;
    while (!nextBeam.empty() && newNowBeam.size() < BEAM_WIDTH) {
        const StateInfo selected = nextBeam.top();
        nextBeam.pop();
        if (seen.find(selected.hash()) != seen.end()) continue;
        seen.insert(selected.hash());
        seen_patterns[selected.pattern]++;
        newNowBeam.push_back(nowBeam[selected.stateIdx]);
        newNowBeam.back().applyRect(selected.candIdx);
        newNowBeam.back().applyAllOkRect();
        assert(newNowBeam.back().info.hash() == selected.hash());
    }
    if (now < BEAM_TL && loop_cnt < BOUNDARY_LOOPCNT) {  // パラメータ
        while (!nextBeam.empty()) {
            const StateInfo selected = nextBeam.top();
            nextBeam.pop();
            assert(0 <= selected.pattern && selected.pattern < PATTERN_NUM);
            if (seen_patterns[selected.pattern] <= SECURE_PATTERN_NUM) {
                seen_patterns[selected.pattern]++;
                newNowBeam.push_back(nowBeam[selected.stateIdx]);
                newNowBeam.back().applyRect(selected.candIdx);
                newNowBeam.back().applyAllOkRect();
            }
        }
    }
    debug(newNowBeam.size());
    nowBeam.clear();
    swap(nowBeam, newNowBeam);
    // debug(seen_patterns);
}

tuple<State, int> beamSearch() {
    State bestState;
    int bestScore = -1;

    vector<State> nowBeam;
    for (int pattern = 0; pattern < PATTERN_NUM; pattern++) {
        nowBeam.emplace_back(pattern);
        nowBeam.back().applyAllOkRect();
    }

    int loop_cnt = 0;
    while (!nowBeam.empty() && timer.ms() < CHOKUDAI_TL) {
        loop_cnt++;
        debug(loop_cnt);
        debug(nowBeam.size());
        PQ nextBeam{compare};
        for (int stateIdx = 0; stateIdx < int(nowBeam.size()); stateIdx++) {
            auto& state = nowBeam[stateIdx];
            if (state.cands.empty()) {
                if (chmax(bestScore, calcRawScore(state.ans))) {
                    swap(bestState, state);
                }
                continue;
            }
            for (int candIdx = 0; candIdx < int(state.cands.size());
                 candIdx++) {
                StateInfo new_state_info =
                    state.IfDoTheStep(loop_cnt, stateIdx, candIdx);
                nextBeam.push(new_state_info);
            }
        }
        transferBeam(nowBeam, nextBeam, loop_cnt);
    }
    debug(loop_cnt);

    return {bestState, bestScore};
}

int chokudaiSearch(State& bestState, int& bestScore) {
    // 評価値を全て保存しておく為のオブジェクト
    map<int, PQ> PQs;
    PQs[0] = PQ{compare};
    // hashを保存する これまでのとは別物にしておく
    set<int> hash_seen;
    // 実体があるStateを保持しておく このidxをStateInfo.prevIdxは持っておく
    vector<State> store;
    // beamSearchの最大深さ
    int MAXDEP = 1500;

    State initState(bestState.info.pattern, true);
    initState.stateIdx = 0;
    store.push_back(initState);
    for (int i = 0; i < int(bestState.ans.size()); i++) {
        if (timer.ms() > CHOKUDAI_TL) break;
        StateInfo info = store.back().info;
        assert(info.numNewPoints == i);
        store.push_back(store.back());
        State& state = store.back();
        state.stateIdx = int(store.size()) - 1;
        state.applyRectByRect(bestState.ans[i]);
        if (state.cands.empty()) {
            assert(i == int(bestState.ans.size()) - 1);
            int score = calcRawScore(state.ans);
            assert(score == bestScore);
            store.pop_back();
            continue;
        }
        if (!bestState.ans[i].is_ok) {
            continue;
        }
        for (int candIdx = 0; candIdx < int(state.cands.size()); candIdx++) {
            if (state.cands[candIdx].is_ok) {
                continue;
            }
            auto [new_state_info_dont_all, new_state_info_do_all] =
                state.IfDoTheStep2(i, candIdx);
            for (auto& new_state_info :
                 {new_state_info_dont_all, new_state_info_do_all}) {
                assert(new_state_info.prevStateIdx == state.stateIdx);
                assert(new_state_info.pattern == state.info.pattern);
                if (hash_seen.find(new_state_info.hash()) != hash_seen.end()) {
                    continue;
                }
                hash_seen.insert(new_state_info.hash());
                if (PQs.find(new_state_info.numNewPoints) == PQs.end()) {
                    PQs[new_state_info.numNewPoints] = PQ{compare};
                }
                PQs[new_state_info.numNewPoints].push(new_state_info);
            }
        }
    }

    int _loop_cnt = 0;
    while (timer.ms() < CHOKUDAI_TL) {
        _loop_cnt++;
        for (int dep = 1; dep < MAXDEP; dep++) {
            if (timer.ms() > CHOKUDAI_TL) break;
            if (PQs.find(dep - 1) == PQs.end()) PQs[dep - 1] = PQ{compare};
            if (PQs[dep - 1].empty()) continue;
            StateInfo info = PQs[dep - 1].top();
            PQs[dep - 1].pop();
            assert(hash_seen.find(info.hash()) != hash_seen.end());
            assert(0 <= info.prevStateIdx &&
                   info.prevStateIdx < int(store.size()));
            store.push_back(store[info.prevStateIdx]);
            State& state = store.back();
            assert(state.stateIdx == info.prevStateIdx);
            state.stateIdx = int(store.size()) - 1;
            assert(0 <= info.candIdx && info.candIdx < int(state.cands.size()));

            state.applyRect(info.candIdx);
            if (info.doApplyAll) {
                state.applyAllOkRect();
            }

            if (state.cands.empty()) {
                int score = calcRawScore(state.ans);
                debug(score);
                if (chmax(bestScore, score)) {
                    swap(bestState, state);
                }
                store.pop_back();
                continue;
            }
            for (int candIdx = 0; candIdx < int(state.cands.size());
                 candIdx++) {
                auto [new_state_info_dont_all, new_state_info_do_all] =
                    state.IfDoTheStep2(dep, candIdx);
                for (auto& new_state_info :
                     {new_state_info_dont_all, new_state_info_do_all}) {
                    assert(new_state_info.prevStateIdx == state.stateIdx);
                    if (hash_seen.find(new_state_info.hash()) !=
                        hash_seen.end()) {
                        continue;
                    }
                    hash_seen.insert(new_state_info.hash());
                    if (PQs.find(new_state_info.numNewPoints) == PQs.end()) {
                        PQs[new_state_info.numNewPoints] = PQ{compare};
                    }
                    PQs[new_state_info.numNewPoints].push(new_state_info);
                }
            }
        }
    }

    debug(hash_seen.size());
    debug(_loop_cnt);
    debug(timer.ms());

    return calcRawScore(bestState.ans);

    // printAns(bestState.ans);

    // assert(timer.ms() < TRUE_TL);

#ifdef ONLINE_JUDGE
    quick_exit(0);
#endif
}

int solve() {
    State bestState;
    int bestScore = -1;

    MODE = 0;
    auto [beamState1, beamScore1] = beamSearch();
    if (chmax(bestScore, beamScore1)) {
        swap(bestState, beamState1);
    }

    MODE = 1;
    auto [beamState2, beamScore2] = beamSearch();
    if (chmax(bestScore, beamScore2)) {
        swap(bestState, beamState2);
    }

    if (timer.ms() < CHOKUDAI_TL) {
        MODE = 100;
        return chokudaiSearch(bestState, bestScore);
    } else {
        if (timer.ms() > TRUE_TL) {
            return -INF;
        }
        return calcRawScore(bestState.ans);
    }
}

void test() {
    long long scoreSum = 0;
    for (int seed = 0; seed < 50; seed++) {
        cerr << "seed  : " << seed << endl;
        timer.reset();
        timer.start();
        readInput(seed);
        int score = solve();
        cerr << "|score: " << score << endl;
        timer.stop();
        scoreSum += score;
        if (score == -INF) {
            break;
        }
    }
    cout << scoreSum / 50 << endl;
}

// int main() {
//     cin.tie(0);
//     ios::sync_with_stdio(false);

// #ifdef ONLINE_JUDGE
//     timer.start();
// #endif

//     readInput();

// #ifndef ONLINE_JUDGE
//     timer.start();
// #endif

//     solve();

//     // dead code
//     timer.stop();

//     return 0;
// }

////
////
////

int main(int argc, char* argv[]) {
    assert(argc == 5);
    BOUNDARY_LOOPCNT = atoi(argv[1]);
    SECURE_PATTERN_NUM = atoi(argv[2]);
    BW_1 = atoi(argv[3]);
    BW_2 = atoi(argv[4]);
    test();
    return 0;
}
