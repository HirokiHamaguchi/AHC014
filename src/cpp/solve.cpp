#include <bits/stdc++.h>  // clang-format off
using namespace std;constexpr int INF=1001001001;constexpr long long INFll=1001001001001001001;namespace viewer{using s=string;template<class T>s f(T i){s S=i==INF||i==INFll?"inf":to_string(i);return s(max(0,3-int(S.size())),' ')+S;}
template<class T>auto v(T&x,s&&e)->decltype(cerr<<x){return cerr<<x<<e;}void v(int x,s&&e){cerr<<f(x)<<e;}void v(long long x,s&&e){cerr<<f(x)<<e;}void v(float x,s&&e){cerr<<fixed<<setprecision(5)<<x<<e;}void v(double x,s&&e){cerr<<fixed<<setprecision(5)<<x<<e;}void v(long double x,s&&e){cerr<<fixed<<setprecision(5)<<x<<e;}
template<class T,class U>void v(const pair<T,U>&p,s&&e="\n"){cerr<<"(";v(p.first,", ");v(p.second,")"+e);}template<class T,class U>void v(const tuple<T,U>&t,s&&e="\n"){cerr<<"(";v(get<0>(t),", ");v(get<1>(t),")"+e);}template<class T,class U,class V>void v(const tuple<T,U,V>&t,s&&e="\n"){cerr<<"(";v(get<0>(t),", ");v(get<1>(t),", ");v(get<2>(t),")"+e);}template<class T,class U,class V,class W>void v(const tuple<T,U,V,W>&t,s&&e="\n"){cerr<<"(";v(get<0>(t),", ");v(get<1>(t),", ");v(get<2>(t),", ");v(get<3>(t),")"+e);}
template<class T>void v(const vector<T>&vx,s);template<class T>auto ve(int,const vector<T>&vx)->decltype(cerr<<vx[0]){cerr<<"{";for(const T&x:vx)v(x,",");return cerr<<"}\n";}template<class T>auto ve(bool,const vector<T>&vx){cerr<<"{\n";for(const T&x:vx)cerr<<"  ",v(x,",");cerr<<"}\n";}template<class T>void v(const vector<T>&vx,s){ve(0,vx);}
template<class T>void v(const deque<T>&q,s&&e){v(vector<T>(q.begin(),q.end()),e);}template<class T,class C>void v(const set<T,C>&S,s&&e){v(vector<T>(S.begin(),S.end()),e);}template<class T,class C>void v(const multiset<T,C>&S,s&&e){v(vector<T>(S.begin(),S.end()),e);}template<class T>void v(const unordered_set<T>&S,s&&e){v(vector<T>(S.begin(),S.end()),e);}
template<class T,class U,class V>void v(const priority_queue<T,U,V>&p,s&&e){priority_queue<T,U,V>q=p;vector<T>z;while(!q.empty()){z.push_back(q.top());q.pop();}v(z,e);}template<class T,class U>void v(const map<T,U>&m,s&&e){cerr<<"{"<<(m.empty()?"":"\n");for(const auto&kv:m){cerr<<"  [";v(kv.first,"");cerr<<"] : ";v(kv.second,"");cerr<<"\n";}cerr<<"}"+e;}
template<class T>void _view(int n,s&S,T&var){cerr<<"\033[1;32m"<<n<<"\033[0m: \033[1;36m"<<S<<"\033[0m = ";v(var,"\n");}template<class T>void grid([[maybe_unused]]T _){}void grid(const vector<vector<bool>>&vvb){cerr<<"\n";for(const vector<bool>&vb:vvb){for(const bool&b:vb)cerr<<(b?".":"#");cerr<<"\n";}}
void _debug(int,s){}template<typename H,typename... T>void _debug(int n,s S,const H&h,const T&... t){int i=0,cnt=0;for(;i<int(S.size());i++){if(S[i]=='(')cnt++;if(S[i]==')')cnt--;if(cnt==0&&S[i]==',')break;}if(i==int(S.size()))_view(n,S,h);else{s S1=S.substr(0,i),S2=S.substr(i+2);if(S2=="\"grid\""){cerr<<"\033[1;32m"<<n<<"\033[0m: \033[1;36m"<<S1<<"\033[0m = ";grid(h);}else _view(n,S1,h),_debug(n,S2,t...);}}}
template<class T>bool chmax(T&a,const T&b){return a<b?a=b,1:0;}template<class T>bool chmin(T&a,const T&b){return a>b?a=b,1:0;} // https://rsk0315.hatenablog.com/entry/2021/01/18/065720
namespace internal{template<class T>using is_signed_int128=typename conditional<is_same<T,__int128_t>::value||is_same<T,__int128>::value,true_type,false_type>::type;template<class T>using is_unsigned_int128=typename conditional<is_same<T,__uint128_t>::value||is_same<T,unsigned __int128>::value,true_type,false_type>::type;template<class T>using is_integral=typename conditional<std::is_integral<T>::value||is_signed_int128<T>::value||is_unsigned_int128<T>::value,true_type,false_type>::type;
template<class T>using is_signed_int=typename conditional<(is_integral<T>::value&&is_signed<T>::value)||is_signed_int128<T>::value,true_type,false_type>::type;template<class T>using is_unsigned_int=typename conditional<(is_integral<T>::value&&is_unsigned<T>::value)||is_unsigned_int128<T>::value,true_type,false_type>::type;template<class T>using is_signed_int_t=enable_if_t<is_signed_int<T>::value>;template<class T>using is_unsigned_int_t=enable_if_t<is_unsigned_int<T>::value>;
constexpr long long safe_mod(long long x,long long m){x%=m;if(x<0)x+=m;return x;}struct barrett{unsigned int _m;unsigned long long im;explicit barrett(unsigned int m):_m(m),im((unsigned long long)(-1)/m+1){}unsigned int umod()const{return _m;}unsigned int mul(unsigned int a,unsigned int b)const{unsigned long long z=a;z*=b;unsigned long long x=(unsigned long long)(((unsigned __int128)(z)*im)>>64);unsigned int v=(unsigned int)(z-x*_m);if(_m<=v)v+=_m;return v;}};
constexpr long long pow_mod_constexpr(long long x,long long n,int m){if(m==1)return 0;unsigned int _m=(unsigned int)(m);unsigned long long r=1;unsigned long long y=safe_mod(x,m);while(n){if(n&1)r=(r*y)%_m;y=(y*y)%_m;n>>=1;}return r;}constexpr pair<long long,long long>inv_gcd(long long a,long long b){a=safe_mod(a,b);if(a==0)return{b,0};long long s=b,t=a;long long m0=0,m1=1;while(t){long long u=s/t;s-=t*u;m0-=m1*u;auto tmp=s;s=t;t=tmp;tmp=m0;m0=m1;m1=tmp;}if(m0<0)m0+=b/s;return{s,m0};}
constexpr bool is_prime_constexpr(int n){if(n<=1)return false;if(n==2||n==7||n==61)return true;if(n%2==0)return false;long long d=n-1;while(d%2==0)d/=2;constexpr long long bases[3]={2,7,61};for(long long a:bases){long long t=d;long long y=pow_mod_constexpr(a,t,n);while(t!=n-1&&y!=1&&y!=n-1){y=y*y%n;t<<=1;}if(y!=n-1&&t%2==0)return false;}return true;}template<int n>constexpr bool is_prime=is_prime_constexpr(n);} // namespace internal
template<int m>struct static_modint{using mint=static_modint;static constexpr int mod(){return m;}static mint raw(int v){mint x;x._v=v;return x;}static_modint():_v(0){}template<class T,internal::is_signed_int_t<T>* =nullptr>static_modint(T v){long long x=(long long)(v%(long long)(umod()));if(x<0)x+=umod();_v=(unsigned int)(x);}template<class T,internal::is_unsigned_int_t<T>* =nullptr>static_modint(T v){_v=(unsigned int)(v%umod());}unsigned int val()const{return _v;}
mint&operator++(){_v++;if(_v==umod())_v=0;return*this;}mint&operator--(){if(_v==0)_v=umod();_v--;return*this;}mint operator++(int){mint result=*this;++*this;return result;}mint operator--(int){mint result=*this;--*this;return result;}mint&operator+=(const mint&rhs){_v+=rhs._v;if(_v>=umod())_v-=umod();return*this;}mint&operator-=(const mint&rhs){_v-=rhs._v;if(_v>=umod())_v+=umod();return*this;}
mint&operator*=(const mint&rhs){unsigned long long z=_v;z*=rhs._v;_v=(unsigned int)(z%umod());return*this;}mint&operator/=(const mint&rhs){return*this=*this*rhs.inv();}mint operator+()const{return*this;}mint operator-()const{return mint()-*this;}mint pow(long long n)const{assert(0<=n);mint x=*this,r=1;while(n){if(n&1)r*=x;x*=x;n>>=1;}return r;}mint inv()const{if(prime){assert(_v);return pow(umod()-2);}else{auto eg=internal::inv_gcd(_v,m);assert(eg.first==1);return eg.second;}}
friend mint operator+(const mint&lhs,const mint&rhs){return mint(lhs)+=rhs;}friend mint operator-(const mint&lhs,const mint&rhs){return mint(lhs)-=rhs;}friend mint operator*(const mint&lhs,const mint&rhs){return mint(lhs)*=rhs;}friend mint operator/(const mint&lhs,const mint&rhs){return mint(lhs)/=rhs;}friend bool operator==(const mint&lhs,const mint&rhs){return lhs._v==rhs._v;}friend bool operator!=(const mint&lhs,const mint&rhs){return lhs._v!=rhs._v;}
friend ostream&operator<<(ostream&os,const mint&rhs){return os<<rhs._v;}friend istream&operator>>(istream&is,mint&rhs){long long v;is>>v;v%=(long long)(umod());if(v<0)v+=umod();;rhs._v=(unsigned int)v;return is;}static constexpr bool prime=internal::is_prime<m>;private:unsigned int _v;static constexpr unsigned int umod(){return m;}};
constexpr int MOD = 1000000007;using mint=static_modint<MOD>;vector<mint>mint_factorial={mint(1)};/*n>1e8 ⇒ fast_modfact(deprecated)*/mint modfact(int n){assert(n<=100000000);if(int(mint_factorial.size())<=n){for(int i=mint_factorial.size();i<=n;i++){mint next=mint_factorial.back()*i;mint_factorial.push_back(next);}}return mint_factorial[n];}
/*x s.t. x^2 ≡ a (mod Prime) or -1*/mint modsqrt(mint a){long long p=mint::mod();if(a.val()==1)return a;if(a.pow((p-1)>>1).val()!=1)return -1;mint b=1,one=1;while(b.pow((p-1)>>1).val()==1)b+=one;long long m=p-1,e=0;while(m%2==0)m>>=1,e++;mint x=a.pow((m-1)>>1);mint y=a*x*x;x*=a;mint z=b.pow(m);while(y!=1){long long j=0;mint t=y;while(t!=one)j++,t*=t;z=z.pow(1ll<<(e-j-1));x*=z;z*=z;y*=z;e=j;}return x;}mint nCk(int n,int k){if(k<0||n<k)return mint(0);return modfact(n)*(modfact(k)).inv()*modfact(n-k).inv();}
/*min x s.t. a^x ≡ b (mod M) or -1*/int modlog(mint a,mint b){if(gcd(a.mod(),a.val())!=1){cout<<"\033[1;31mCAUTION: m must be coprime to a.\033[0m"<<endl;assert(false);}long long m=mint::mod();long long sq=round(sqrt(m))+1;unordered_map<long long,long long>ap;mint re=a;for(long long r=1;r<sq;r++){if(ap.find(re.val())==ap.end())ap[re.val()]=r;re*=a;}mint A=a.inv().pow(sq);re=b;for(mint q=0;q.val()<sq;q++){if(re==1&&q!=0)return(q*sq).val();if(ap.find(re.val())!=ap.end())return(q*sq+ap[re.val()]).val();re*=A;}return-1;};
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

constexpr int TL = 4900;

int N;
int M;
vector<YX> POINTS;
vector<vector<int>> wTable;

constexpr int dirLen = 8;
constexpr int DX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
constexpr int DY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int initSumW;
double scoreCoef;

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

struct Rect {
    YX YXs[4];
    int age;

    Rect() : age(-1) {}
    Rect(int y1, int x1, int y2, int x2, int y3, int x3, int y4, int x4,
         int age)
        : age(age) {
        YXs[0] = YX(y1, x1);
        YXs[1] = YX(y2, x2);
        YXs[2] = YX(y3, x3);
        YXs[3] = YX(y4, x4);
        int dir1 = getDir(YXs[1] - YXs[0]);
        int dir2 = getDir(YXs[2] - YXs[1]);
        int dir3 = getDir(YXs[3] - YXs[2]);
        int dir4 = getDir(YXs[0] - YXs[3]);
        assert((dir1 + 2) % dirLen == dir2 && (dir2 + 2) % dirLen == dir3 &&
               (dir3 + 2) % dirLen == dir4 && (dir4 + 2) % dirLen == dir1);
    }

    int size() const {
        YX d1 = YXs[1] - YXs[0];
        YX d2 = YXs[2] - YXs[0];
        YX d3 = YXs[3] - YXs[0];
        return (abs(d1.x * d2.y - d2.x * d1.y) +
                abs(d3.x * d2.y - d2.x * d3.y)) /
               2;
    }
    int len() const {
        YX d1 = YXs[1] - YXs[0];
        YX d2 = YXs[3] - YXs[0];
        return (max(abs(d1.x), abs(d1.y)) + max(abs(d2.x), abs(d2.y)));
    }
    int dir() const { return getDir(YXs[1] - YXs[0]); }

    int _regionPoint(const YX& point) const {
        // -1    -1
        //    1
        //  2 -1 0
        //    3
        // -1    -1
        if (point.y == point.x || point.y + point.x == N - 1) {
            return -1;
        } else {
            return (int(point.y + point.x < N) * 3) ^ int((point.y > point.x));
        }
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
    YX topRight() const {
        return YX(max({YXs[0].y, YXs[1].y, YXs[2].y, YXs[3].y}),
                  max({YXs[0].x, YXs[1].x, YXs[2].x, YXs[3].x}));
    }
    inline bool is_valid() const {
        assert((YXs[0].y != -1 && YXs[0].x != -1) ||
               (YXs[0] == YXs[1] && YXs[1] == YXs[2] && YXs[2] == YXs[3]));
        return YXs[0].y != -1;
    }
    inline int getW() const { return wTable[YXs[0].y][YXs[0].x]; }

    bool is_ok(int pattern) const {
        if (len() == 2) {
            YX tr = topRight();
            if (getDir(YXs[1] - YXs[0]) % 2 == 0) {
                // □
                return abs(tr.y - tr.x) % 2 == (pattern & 1);
            } else {
                // ◇
                if ((pattern >> 3) & 1) {
                    int region = getRegion();
                    if (region == -1) return false;
                    if (region % 2 == 0) {
                        return tr.y % 2 == ((pattern >> 1) & 1);
                    } else {
                        return tr.x % 2 == ((pattern >> 2) & 1);
                    }
                } else {
                    if ((pattern >> 1) & 1) {
                        return tr.y % 2 == ((pattern >> 2) & 1);
                    } else {
                        return tr.x % 2 == ((pattern >> 2) & 1);
                    }
                }
            }
        }
        return false;
    }

    bool operator==(Rect const& r) const {
        return YXs[0] == r.YXs[0] && YXs[1] == r.YXs[1] && YXs[2] == r.YXs[2] &&
               YXs[3] == r.YXs[3];
    }
    friend ostream& operator<<(ostream& os, const Rect& rect) {
        return os << rect.YXs[0] << " " << rect.YXs[1] << " " << rect.YXs[2]
                  << " " << rect.YXs[3];
    }
};
using Rects = vector<Rect>;

constexpr int maxN = 61;
// bool[]の方が速い?
using Bitset = bitset<maxN * maxN * dirLen>;
using Grid = bitset<maxN * maxN>;

struct State {
    Bitset used;
    Grid grid;
    Rects cands;
    Rects ans;
    const int pattern;

    int blocked = 0;
    int numNewPoints = 0;

    State(const Rects& prevAns, int pattern, bool do_setup) : pattern(pattern) {
        assert(do_setup);
        ans = prevAns;
        used.reset();
        grid.reset();
        for (auto& rect : prevAns) {
            grid[to_idx2(rect.YXs[0])];
            fillUsed(rect, true);
        }
        setup();
    }
    State(int pattern, bool do_setup = true) : pattern(pattern) {
        assert(!do_setup ^ (0 <= pattern && pattern < 16));
        used.reset();
        grid.reset();
        if (do_setup) {
            setup();
        }
    }

    void setup() {
        for (auto& p : POINTS) grid[to_idx2(p)] = 1;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                for (int dir = 0; dir < dirLen; dir++) {
                    if (grid[to_idx2(y, x)]) {
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
            y += DY[dir];
            x += DX[dir];
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
            y += DY[dir];
            x += DX[dir];
            cnt++;
            if (grid[to_idx2(y, x)] || cnt == len) return {y, x};
        }
        return {-1, -1};
    }

    // pair<bool, any> is_valid(int y, int x, int dir) const {
    //     return {false, Rect()};
    // }

    Rect getDoubleNext(int y, int x, int dir) const {
        assert(grid[to_idx2(y, x)]);
        int dir1 = dir;
        int dir2 = (dir + 2) % dirLen;
        auto [ny11, nx11, len1] = getNext(y, x, dir1);
        auto [ny12, nx12, len2] = getNext(y, x, dir2);
        if (ny11 == -1 || ny12 == -1) return Rect();
        auto [ny21, nx21] = getNextWithLen(ny11, nx11, dir2, len2);
        auto [ny22, nx22] = getNextWithLen(ny12, nx12, dir1, len1);
        if (ny21 != -1 && ny22 != -1 && ny21 == ny22 && nx21 == nx22 &&
            !grid[to_idx2(ny21, nx21)]) {
            return Rect(ny21, nx21, ny12, nx12, y, x, ny11, nx11, -1);
        }
        return Rect();
    }

    Rect getTripleNext(int y, int x, int dir, bool rectDir) const {
        assert(grid[to_idx2(y, x)]);
        int dir1 = dir;
        int dir2 = (dir + (rectDir ? 2 : 6)) % dirLen;
        int dir3 = (dir + (rectDir ? 2 : 6) * 2) % dirLen;
        auto [ny1, nx1, len1] = getNext(y, x, dir1);
        if (ny1 == -1) return Rect();
        auto [ny2, nx2, len2] = getNext(ny1, nx1, dir2);
        if (ny2 == -1) return Rect();
        auto [ny3, nx3] = getNextWithLen(ny2, nx2, dir3, len1);
        if (ny3 == -1) return Rect();
        auto [ny4, nx4] = getNextWithLen(y, x, dir2, len2);
        if (ny4 != -1 && nx4 != -1 && ny3 == ny4 && nx3 == nx4 &&
            !grid[to_idx2(ny3, nx3)]) {
            if (rectDir) {
                return Rect(ny3, nx3, y, x, ny1, nx1, ny2, nx2, -1);
            } else {
                return Rect(ny3, nx3, ny2, nx2, ny1, nx1, y, x, -1);
            }
        }
        return Rect();
    }

    void fillUsed(const Rect& rect, bool fillValue) {
        for (auto i = 0; i < 4; i++) {
            int x = rect.YXs[i].x, y = rect.YXs[i].y;
            int tx = rect.YXs[(i + 1) % 4].x, ty = rect.YXs[(i + 1) % 4].y;
            int dir = getDir(ty - y, tx - x);
            while (x != tx || y != ty) {
                blocked += (fillValue ? 1 : -1);
                used[to_idx3(y, x, dir)] = fillValue;
                x += DX[dir];
                y += DY[dir];
                used[to_idx3(y, x, dir ^ 4)] = fillValue;
            }
            blocked -= (fillValue ? 1 : -1);
        }
    }

    void eraseInvalid() {
        cands.erase(remove_if(cands.begin(), cands.end(),
                              [this](const Rect& cand) {
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
                                  if (cand.is_ok(pattern)) {
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

        while (!oks.empty()) {
            Rect rect = oks.back();
            oks.pop_back();
            if (!grid[to_idx2(rect.YXs[0])] && rect.dir() % 2 == 1 &&
                seen.find(to_idx2(rect.YXs[0])) != seen.end()) {
                continue;
            }
            if (grid[to_idx2(rect.YXs[0])]) {
                continue;
            }
            int y = rect.YXs[0].y, x = rect.YXs[0].x;
            numNewPoints++;
            ans.push_back(rect);
            grid[to_idx2(rect.YXs[0])] = true;
            assert(int(grid.count()) == int(POINTS.size()) + numNewPoints);
            fillUsed(rect, true);

            // 候補への追加
            for (int dir = 0; dir < 8; dir++) {
                vector<Rect> new_rects = {getDoubleNext(y, x, dir),
                                          getTripleNext(y, x, dir, true),
                                          getTripleNext(y, x, dir, false)};
                for (auto& new_rect : new_rects) {
                    if (new_rect.is_valid()) {
                        if (new_rect.is_ok(pattern)) {
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

    void applyRect(int candIdx, int age) {
        assert(0 <= candIdx && candIdx < int(cands.size()));

        // 更新
        int y = cands[candIdx].YXs[0].y, x = cands[candIdx].YXs[0].x;
        numNewPoints++;
        ans.push_back(cands[candIdx]);
        grid[to_idx2(cands[candIdx].YXs[0])] = true;
        fillUsed(cands[candIdx], true);

        // 候補から削除
        cands.erase(cands.begin() + candIdx);
        eraseInvalid();

        // 候補への追加
        for (int dir = 0; dir < 8; dir++) {
            Rect new_rect1 = getDoubleNext(y, x, dir);
            new_rect1.age = age;
            if (new_rect1.is_valid()) cands.push_back(new_rect1);
            Rect new_rect2 = getTripleNext(y, x, dir, true);
            new_rect2.age = age;
            if (new_rect2.is_valid()) cands.push_back(new_rect2);
            Rect new_rect3 = getTripleNext(y, x, dir, false);
            new_rect3.age = age;
            if (new_rect3.is_valid()) cands.push_back(new_rect3);
        }
    }
};

int calcScore(const Rects& ans) {
    double sumW = initSumW;
    for (auto& r : ans) sumW += r.getW();
    return int(round(scoreCoef * sumW));
}

void readInput() {
    cin >> N >> M;
    POINTS.resize(M);
    for (int i = 0; i < M; i++) cin >> POINTS[i];
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
}

void printAns(const Rects& ans) {
#ifdef TEST
    cout << calcScore(ans) << endl;
    cerr << ans.size() << endl;
    for (auto& r : ans) cerr << r << endl;
#else
    debug(calcScore(ans));
    cout << ans.size() << endl;
    for (auto& r : ans) cout << r << endl;
#endif
}

Rects solveSub(int pattern, const Rects& prevAns = {}) {
    State state(prevAns, pattern, true);
    int loop_cnt = 0;
    while (!state.cands.empty()) {
        loop_cnt++;

        state.applyAllOkRect();
        if (state.cands.empty()) break;

        vector<int> eval_values(state.cands.size(), 0);
        for (int i = int(state.cands.size()) - 1; i >= 0; i--) {
            State new_state = state;
            new_state.applyRect(i, loop_cnt);
            for (auto& new_cand : new_state.cands) {
                eval_values[i] += new_cand.getW();
            }
            if (state.cands[i].len() <= 2) {
                eval_values[i] *= 2;
            }
            if (!state.cands[i].is_ok(state.pattern)) {
                eval_values[i] -= INF;
            } else {
                assert(false);
            }
        }
        int best_idx =
            distance(eval_values.begin(),
                     max_element(eval_values.begin(), eval_values.end()));
        // if (eval_values[best_idx] < -INF / 2) {
        //     // debug(loop_cnt);
        //     for (auto& v : eval_values) {
        //         v += INF;
        //         chmax(v, 0);
        //     }
        //     vector<int> Ps(eval_values.size());
        //     iota(Ps.begin(), Ps.end(), 0);
        //     best_idx = myrand.choice(Ps, eval_values);
        // }
        state.applyRect(best_idx, loop_cnt);
        // int bestIdx = -1;
        // for (int i = 0; i < int(state.cands.size()) && bestIdx == -1; i++) {
        //     if (state.cands[i].is_ok(state.pattern)) {
        //         bestIdx = i;
        //     }
        // }
        // if (bestIdx == -1) {
        //     vector<int> eval_values(state.cands.size(), 0);
        //     for (int i = 0; i < int(state.cands.size()); i++) {
        //         eval_values[i] += state.cands[i].getW();
        //     }
        //     bestIdx =
        //         distance(eval_values.begin(),
        //                  max_element(eval_values.begin(),
        //                  eval_values.end()));
        // }
        // debug(bestIdx);
        // state.applyRect(bestIdx, loop_cnt);
    }
    return state.ans;
}

void solve() {
    Rects bestAns;
    int bestScore = -1;
    int bestPattern = -1;

    // while (timer.ms() < 10000) {
    for (int pattern = 0; pattern < 16; pattern++) {
        debug(pattern);
        Rects ans = solveSub(pattern);
        if (chmax(bestScore, calcScore(ans))) {
            bestPattern = pattern;
            // debug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            swap(bestAns, ans);
        }
    }
    // }
    printAns(bestAns);
    debug(bestPattern);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    readInput();

    timer.start();
    solve();
    timer.stop();

#ifdef hari64
    assert(timer.ms() < TL);
#endif

    return 0;
}
