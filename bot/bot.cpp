#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <climits>
#include <cmath>
#include <cstring>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <numeric>
#include <deque>

using namespace std;

struct Params {

    double  LEN_WEIGHT              = 2000.0;
    double  LEN_WEIGHT_SMALL        = 2200.0;
    double  LEN_WEIGHT_WINNING_LATE = 2800.0;
    double  LEN_WEIGHT_LOSING_LATE  = 1800.0;

    double  GROWTH_BASE             = 600.0;
    double  SCARCITY_MULT_LOW       = 8.0;
    double  SCARCITY_MULT_MED       = 5.0;
    double  SCARCITY_MULT_HIGH      = 2.0;

    double  VORONOI_APPLE_CLEAR     = 1.0;
    double  VORONOI_APPLE_SLIGHT    = 0.65;
    double  VORONOI_APPLE_CONTESTED = 0.35;
    double  VORONOI_APPLE_LOSE      = -0.5;
    double  VORONOI_APPLE_TIE_LOSE  = -0.5;

    double  EAT_BONUS               = 2500.0;

    double  TERRITORY_WEIGHT              = 8.0;
    double  TERRITORY_WEIGHT_SMALL        = 15.0;
    double  TERRITORY_WEIGHT_SMALL_LATE   = 12.0;
    double  TERRITORY_WEIGHT_WINNING_LATE = 10.0;

    double  ENERGY_CONTROL_WEIGHT    = 180.0;
    double  CLOSEST_ENERGY_WEIGHT    = 350.0;
    double  CLOSEST_ENERGY_FALLBACK  = 180.0;
    double  NO_ENERGY_PEN            = -100.0;

    double  TRAP_SEVERE             = -900.0;
    double  TRAP_MILD               = -150.0;
    double  TRAP_MULT_SMALL         = 2.5;
    double  TRAP_MULT_TINY          = 3.5;
    double  OPP_TRAP_BONUS          = 350.0;
    double  OPP_TRAP_BONUS_SMALL    = 550.0;

    double  LOG_SPACE_BONUS         = 12.0;
    double  SPACE_GOOD              = 250.0;
    double  SPACE_BAD               = -180.0;

    double  NO_MOVES_PEN            = -2500.0;
    double  NO_MOVES_PEN_SMALL      = -4000.0;
    double  ONE_MOVE_PEN            = -500.0;
    double  ONE_MOVE_PEN_SMALL      = -900.0;
    double  TWO_MOVES_PEN_SMALL     = -150.0;
    double  MOBILITY_BONUS          = 20.0;

    double  HEAD_CLOSE_SMALLER       = -1800.0;
    double  HEAD_CLOSE_SMALLER_SMALL = -2500.0;
    double  HEAD_CLOSE_BIGGER        = 350.0;
    double  HEAD_CLOSE_BIGGER_SMALL  = 450.0;
    double  HEAD_NEAR_SMALLER        = -400.0;
    double  HEAD_NEAR_SMALLER_SMALL  = -650.0;
    double  HEAD_NEAR_LINE_SMALL     = -300.0;

    double  FAST_HEAD_CLOSE_SMALLER  = -900.0;
    double  FAST_HEAD_CLOSE_BIGGER   = 150.0;
    double  FAST_HEAD_NEAR_SMALLER   = -200.0;

    double  EDGE_X                  = -60.0;
    double  EDGE_Y                  = -140.0;
    double  CORNER_EXTRA            = -350.0;

    double  GRAVITY_RISK_NONE            = -800.0;
    double  GRAVITY_RISK_HIGH            = -60.0;
    double  GRAVITY_RISK_LOW             = -20.0;
    double  GRAVITY_DEATH                = -4500.0;
    double  GRAVITY_EXPLOIT              = 7.0;
    double  GRAVITY_EXPLOIT_FALL_DEATH   = 850.0;
    double  GRAVITY_EXPLOIT_FALL_FAR     = 100.0;
    double  GRAVITY_RISK_SMALL           = 5.0;
    double  GRAVITY_RISK_LARGE           = 3.0;

    double  ANTI_TRAMPOLINE         = -1750.0;
    double  STALL_REVISIT           = -600.0;
    double  STALL_URGENCY_CAP       = 1.3;

    double  ALIVE_EARLY             = 700.0;
    double  ALIVE_MID               = 450.0;
    double  ALIVE_LATE              = 300.0;
    double  ALIVE_WINNING_MULT      = 2.5;
    double  ALIVE_SMALL_MULT        = 3.0;

    double  ALIVE_OWN_PER_SNAKE     = 350.0;
    double  ALIVE_OPP_PER_SNAKE     = 200.0;

    double  TAIL_DEFAULT            = 30.0;
    double  TAIL_WINNING            = 200.0;
    double  TAIL_NO_FOOD            = 150.0;
    double  TAIL_NO_VORONOI         = 220.0;
    double  TAIL_SMALL_MULT         = 3.5;

    double  SHORT_3                 = -700.0;
    double  SHORT_3_SMALL           = -1200.0;
    double  SHORT_4                 = -450.0;
    double  SHORT_4_SMALL           = -700.0;

    double  STAIRCASE               = 10.0;

    double  OPP_MAXLEN_THREAT       = -300.0;
    double  GREEDY_APPLE_IMMEDIATE   = 3000.0;
    double  GREEDY_APPLE_DIST        = -120.0;
    double  GREEDY_SUPPORT           = 80.0;

    double  GREEDY_UP_PEN            = -120.0;
    double  GREEDY_BLOCKED_PEN       = -2500.0;
    double  GREEDY_HEAD_COLL_PEN     = -900.0;
    double  GREEDY_HEAD_COLL_PEN_SMALL = -1800.0;
    double  GREEDY_HEAD_COLL_BONUS   = 400.0;
    double  GREEDY_TRAPPED_PEN       = -800.0;
    double  GREEDY_TRAPPED_MILD_PEN  = -70.0;
    double  BEAM_TRAPPED_PEN        = -6000.0;

    double  TRAP_APPLE_EAT_PEN      = -550.0;
    double  TRAP_APPLE_EVAL_PEN     = -400.0;
    double  TRAP_APPLE_HARD_PEN     = -2200.0;
    double  TRAP_APPLE_COMBO_PEN    = -900.0;

    double  GREEDY_APPLE_HEIGHT_BONUS = 30.0;
    double  APPLE_HEIGHT_BONUS        = 25.0;

    double FAST_APPLE_FALLBACK      = 0.70;
    double FAST_OPP_NEAR_APPLE      = -80.0;
    double FAST_TRAP_SEVERE         = -200.0;
    double FAST_TRAP_MILD           = -30.0;
    double FAST_TAIL_WINNING        = 35.0;
    double FAST_TAIL_NO_FOOD        = 25.0;
    double FAST_TAIL_DEFAULT        = 8.0;
    double FAST_TAIL_SMALL_MULT     = 1.5;

    int BEAM_WIDTH_TINY = 120;   // was 100
    int BEAM_DEPTH_TINY = 10;     // was 8
    int BEAM_COMBO_TINY = 24;    // was 20
    int BEAM_WIDTH_SMALL = 180;  // was 150
    int BEAM_DEPTH_SMALL = 8;    // was 7
    int BEAM_COMBO_SMALL = 28;   // was 24
    int BEAM_WIDTH_FEW = 200;    // was 180
    int BEAM_DEPTH_FEW = 7;      // was 6
    int BEAM_COMBO_FEW = 32;     // was 27
    int BEAM_WIDTH_MED = 150;    // was 120
    int BEAM_DEPTH_MED = 6;      // was 5
    int BEAM_COMBO_MED = 22;     // was 18
    int BEAM_WIDTH_MANY = 100;    // was 70
    int BEAM_DEPTH_MANY = 6;     // was 4
    int BEAM_COMBO_MANY = 15;    // was 12
    int OPP_COMBO_LIMIT = 10;
    int OPP_COMBO_LIMIT_SMALL = 15;

    int REEVAL_TOP_K = 30;

    int    APPLE_RICH_THRESHOLD    = 12;
    double APPLE_RICH_APPLE_MULT   = 2.5;    // reduced: was causing over-focus on growth
    double APPLE_RICH_SPREAD_PEN   = 90.0;  // halved: was blocking nearest-apple eating
    double APPLE_RICH_SPREAD_DIST  = 5.0;    // tightened threshold (was 7)
    double APPLE_RICH_TERR_SCALE   = 0.55;   // raised: prevent evaluation plateau
    double APPLE_RICH_CLOSEST_MULT = 2.0;
};

static Params P;

static int  gAppleCount = 0;
static bool gAppleRich  = false;

static bool loadParamsJson(const string& filename) {
    ifstream f(filename);
    if (!f.is_open()) return false;

    unordered_map<string, double*> k = {
        {"LEN_WEIGHT", &P.LEN_WEIGHT}, {"LEN_WEIGHT_SMALL", &P.LEN_WEIGHT_SMALL},
        {"LEN_WEIGHT_WINNING_LATE", &P.LEN_WEIGHT_WINNING_LATE},
        {"LEN_WEIGHT_LOSING_LATE", &P.LEN_WEIGHT_LOSING_LATE},
        {"GROWTH_BASE", &P.GROWTH_BASE},
        {"SCARCITY_MULT_LOW", &P.SCARCITY_MULT_LOW}, {"SCARCITY_MULT_MED", &P.SCARCITY_MULT_MED},
        {"SCARCITY_MULT_HIGH", &P.SCARCITY_MULT_HIGH},
        {"VORONOI_APPLE_CLEAR", &P.VORONOI_APPLE_CLEAR},
        {"VORONOI_APPLE_SLIGHT", &P.VORONOI_APPLE_SLIGHT},
        {"VORONOI_APPLE_CONTESTED", &P.VORONOI_APPLE_CONTESTED},
        {"VORONOI_APPLE_LOSE", &P.VORONOI_APPLE_LOSE},
        {"VORONOI_APPLE_TIE_LOSE", &P.VORONOI_APPLE_TIE_LOSE},
        {"EAT_BONUS", &P.EAT_BONUS},
        {"TERRITORY_WEIGHT", &P.TERRITORY_WEIGHT},
        {"TERRITORY_WEIGHT_SMALL", &P.TERRITORY_WEIGHT_SMALL},
        {"TERRITORY_WEIGHT_SMALL_LATE", &P.TERRITORY_WEIGHT_SMALL_LATE},
        {"TERRITORY_WEIGHT_WINNING_LATE", &P.TERRITORY_WEIGHT_WINNING_LATE},
        {"ENERGY_CONTROL_WEIGHT", &P.ENERGY_CONTROL_WEIGHT},
        {"CLOSEST_ENERGY_WEIGHT", &P.CLOSEST_ENERGY_WEIGHT},
        {"CLOSEST_ENERGY_FALLBACK", &P.CLOSEST_ENERGY_FALLBACK},
        {"NO_ENERGY_PEN", &P.NO_ENERGY_PEN},
        {"TRAP_SEVERE", &P.TRAP_SEVERE}, {"TRAP_MILD", &P.TRAP_MILD},
        {"TRAP_MULT_SMALL", &P.TRAP_MULT_SMALL}, {"TRAP_MULT_TINY", &P.TRAP_MULT_TINY},
        {"OPP_TRAP_BONUS", &P.OPP_TRAP_BONUS}, {"OPP_TRAP_BONUS_SMALL", &P.OPP_TRAP_BONUS_SMALL},
        {"LOG_SPACE_BONUS", &P.LOG_SPACE_BONUS},
        {"SPACE_GOOD", &P.SPACE_GOOD}, {"SPACE_BAD", &P.SPACE_BAD},
        {"NO_MOVES_PEN", &P.NO_MOVES_PEN}, {"NO_MOVES_PEN_SMALL", &P.NO_MOVES_PEN_SMALL},
        {"ONE_MOVE_PEN", &P.ONE_MOVE_PEN}, {"ONE_MOVE_PEN_SMALL", &P.ONE_MOVE_PEN_SMALL},
        {"TWO_MOVES_PEN_SMALL", &P.TWO_MOVES_PEN_SMALL},
        {"MOBILITY_BONUS", &P.MOBILITY_BONUS},
        {"HEAD_CLOSE_SMALLER", &P.HEAD_CLOSE_SMALLER},
        {"HEAD_CLOSE_SMALLER_SMALL", &P.HEAD_CLOSE_SMALLER_SMALL},
        {"HEAD_CLOSE_BIGGER", &P.HEAD_CLOSE_BIGGER},
        {"HEAD_CLOSE_BIGGER_SMALL", &P.HEAD_CLOSE_BIGGER_SMALL},
        {"HEAD_NEAR_SMALLER", &P.HEAD_NEAR_SMALLER},
        {"HEAD_NEAR_SMALLER_SMALL", &P.HEAD_NEAR_SMALLER_SMALL},
        {"HEAD_NEAR_LINE_SMALL", &P.HEAD_NEAR_LINE_SMALL},
        {"EDGE_X", &P.EDGE_X}, {"EDGE_Y", &P.EDGE_Y}, {"CORNER_EXTRA", &P.CORNER_EXTRA},
        {"GRAVITY_RISK_NONE", &P.GRAVITY_RISK_NONE},
        {"GRAVITY_RISK_HIGH", &P.GRAVITY_RISK_HIGH},
        {"GRAVITY_RISK_LOW", &P.GRAVITY_RISK_LOW},
        {"GRAVITY_DEATH", &P.GRAVITY_DEATH},
        {"GRAVITY_EXPLOIT", &P.GRAVITY_EXPLOIT},
        {"GRAVITY_EXPLOIT_FALL_DEATH", &P.GRAVITY_EXPLOIT_FALL_DEATH},
        {"GRAVITY_EXPLOIT_FALL_FAR", &P.GRAVITY_EXPLOIT_FALL_FAR},
        {"GRAVITY_RISK_SMALL", &P.GRAVITY_RISK_SMALL},
        {"GRAVITY_RISK_LARGE", &P.GRAVITY_RISK_LARGE},
        {"ANTI_TRAMPOLINE", &P.ANTI_TRAMPOLINE}, {"STALL_REVISIT", &P.STALL_REVISIT},
        {"STALL_URGENCY_CAP", &P.STALL_URGENCY_CAP},
        {"ALIVE_EARLY", &P.ALIVE_EARLY}, {"ALIVE_MID", &P.ALIVE_MID},
        {"ALIVE_LATE", &P.ALIVE_LATE},
        {"ALIVE_WINNING_MULT", &P.ALIVE_WINNING_MULT},
        {"ALIVE_SMALL_MULT", &P.ALIVE_SMALL_MULT},
        {"ALIVE_OWN_PER_SNAKE", &P.ALIVE_OWN_PER_SNAKE},
        {"ALIVE_OPP_PER_SNAKE", &P.ALIVE_OPP_PER_SNAKE},
        {"TAIL_DEFAULT", &P.TAIL_DEFAULT}, {"TAIL_WINNING", &P.TAIL_WINNING},
        {"TAIL_NO_FOOD", &P.TAIL_NO_FOOD}, {"TAIL_NO_VORONOI", &P.TAIL_NO_VORONOI},
        {"TAIL_SMALL_MULT", &P.TAIL_SMALL_MULT},
        {"SHORT_3", &P.SHORT_3}, {"SHORT_3_SMALL", &P.SHORT_3_SMALL},
        {"SHORT_4", &P.SHORT_4}, {"SHORT_4_SMALL", &P.SHORT_4_SMALL},
        {"STAIRCASE", &P.STAIRCASE}, {"OPP_MAXLEN_THREAT", &P.OPP_MAXLEN_THREAT},
        {"GREEDY_APPLE_IMMEDIATE", &P.GREEDY_APPLE_IMMEDIATE},
        {"GREEDY_APPLE_DIST", &P.GREEDY_APPLE_DIST},
        {"GREEDY_SUPPORT", &P.GREEDY_SUPPORT},
        {"GREEDY_UP_PEN", &P.GREEDY_UP_PEN},
        {"GREEDY_BLOCKED_PEN", &P.GREEDY_BLOCKED_PEN},
        {"GREEDY_HEAD_COLL_PEN", &P.GREEDY_HEAD_COLL_PEN},
        {"GREEDY_HEAD_COLL_PEN_SMALL", &P.GREEDY_HEAD_COLL_PEN_SMALL},
        {"GREEDY_HEAD_COLL_BONUS", &P.GREEDY_HEAD_COLL_BONUS},
        {"GREEDY_TRAPPED_PEN", &P.GREEDY_TRAPPED_PEN},
        {"GREEDY_TRAPPED_MILD_PEN", &P.GREEDY_TRAPPED_MILD_PEN},
        {"BEAM_TRAPPED_PEN", &P.BEAM_TRAPPED_PEN},
    };

    string line;
    while (getline(f, line)) {
        size_t colon = line.find(':');
        if (colon == string::npos) continue;
        string key = line.substr(0, colon);
        string val = line.substr(colon + 1);
        auto strip = [](string& s) {
            string out; out.reserve(s.size());
            for (char c : s)
                if (c != ' ' && c != '\t' && c != '\n' && c != '\r' &&
                    c != '"' && c != ',' && c != '{' && c != '}')
                    out.push_back(c);
            s.swap(out);
        };
        strip(key); strip(val);
        if (key.empty() || val.empty()) continue;
        auto it = k.find(key);
        if (it == k.end()) continue;
        try { *(it->second) = stod(val); } catch (...) {}
    }
    return true;
}

using Clock = chrono::steady_clock;
using Ms    = chrono::milliseconds;
inline int64_t elapsed(Clock::time_point t0) {
    return chrono::duration_cast<Ms>(Clock::now() - t0).count();
}

constexpr int MAX_W = 50, MAX_H = 30, MAX_CELLS = MAX_W * MAX_H;
int W, H;
bool smallMap = false;
bool tinyMap  = false;
int totalCells = 0;

struct Coord {
    int x, y;
    constexpr Coord() : x(-1), y(-1) {}
    constexpr Coord(int x, int y) : x(x), y(y) {}
    inline int  idx()  const { return y * MAX_W + x; }
    inline bool operator==(const Coord& o) const { return x == o.x && y == o.y; }
    inline bool operator!=(const Coord& o) const { return !(*this == o); }
    inline bool operator< (const Coord& o) const { return idx() < o.idx(); }
    inline Coord operator+(const Coord& o) const { return {x + o.x, y + o.y}; }
    inline Coord operator-(const Coord& o) const { return {x - o.x, y - o.y}; }
    inline int   manhattan(const Coord& o) const { return abs(x - o.x) + abs(y - o.y); }
    inline bool  inBounds() const { return x >= 0 && x < W && y >= 0 && y < H; }
};

const Coord DIRS[4]        = {{0,-1},{0,1},{-1,0},{1,0}};
const string DIR_NAMES[4]  = {"UP","DOWN","LEFT","RIGHT"};
constexpr int DIR_UP=0, DIR_DOWN=1, DIR_LEFT=2, DIR_RIGHT=3;

constexpr int BW = (MAX_CELLS + 63) / 64;
struct BitBoard {
    uint64_t w[BW] = {};
    inline void  set(int i)          { w[i>>6] |=  (1ULL << (i&63)); }
    inline void  clr(int i)          { w[i>>6] &= ~(1ULL << (i&63)); }
    inline bool  tst(int i) const    { return (w[i>>6] >> (i&63)) & 1; }
    inline void  setC(Coord c)       { set(c.idx()); }
    inline void  clrC(Coord c)       { clr(c.idx()); }
    inline bool  tstC(Coord c) const { return tst(c.idx()); }
    inline BitBoard operator|(const BitBoard& o) const {
        BitBoard r; for(int i=0;i<BW;i++) r.w[i]=w[i]|o.w[i]; return r;
    }
    inline BitBoard operator&(const BitBoard& o) const {
        BitBoard r; for(int i=0;i<BW;i++) r.w[i]=w[i]&o.w[i]; return r;
    }
    inline BitBoard operator~() const {
        BitBoard r; for(int i=0;i<BW;i++) r.w[i]=~w[i]; return r;
    }
    inline int popcount() const {
        int c=0; for(int i=0;i<BW;i++) c+=__builtin_popcountll(w[i]); return c;
    }
    inline bool empty() const {
        for(int i=0;i<BW;i++) if(w[i]) return false; return true;
    }
    inline void reset() { for(int i=0;i<BW;i++) w[i]=0; }
};

static constexpr int BODY_CAP = 256;
static_assert(BODY_CAP <= 32767, "BODY_CAP must fit in int16_t");

struct SnakeBody {
    Coord   data[BODY_CAP];
    int16_t head_idx = 0;
    int16_t sz       = 0;

    inline void  clear()      { head_idx = 0; sz = 0; }
    inline int   size()  const { return sz; }
    inline bool  empty() const { return sz == 0; }
    inline Coord front() const { return data[head_idx]; }
    inline Coord back()  const { return data[(head_idx + sz - 1 + BODY_CAP) % BODY_CAP]; }

    inline const Coord& operator[](int i) const { return data[(head_idx + i) % BODY_CAP]; }
    inline       Coord& operator[](int i)       { return data[(head_idx + i) % BODY_CAP]; }

    inline void push_front(Coord c) {
        head_idx = (head_idx == 0) ? BODY_CAP - 1 : head_idx - 1;
        data[head_idx] = c;
        ++sz;
    }

    inline void pop_back()  { --sz; }

    inline void pop_front() { head_idx = (head_idx + 1) % BODY_CAP; --sz; }

    inline void push_back(Coord c) {
        data[(head_idx + sz) % BODY_CAP] = c;
        ++sz;
    }

    struct MIter {
        SnakeBody* sb; int i;
        Coord& operator*()  const { return (*sb)[i]; }
        MIter& operator++()       { ++i; return *this; }
        bool operator!=(const MIter& o) const { return i != o.i; }
    };
    struct CIter {
        const SnakeBody* sb; int i;
        const Coord& operator*()  const { return sb->data[(sb->head_idx + i) % BODY_CAP]; }
        CIter& operator++()             { ++i; return *this; }
        bool operator!=(const CIter& o) const { return i != o.i; }
    };
    MIter begin()       { return {this, 0}; }
    MIter end()         { return {this, sz}; }
    CIter begin() const { return {this, 0}; }
    CIter end()   const { return {this, sz}; }
};

constexpr int MAX_SNAKES = 8;
struct Snake {
    int  id      = -1;
    int  owner   = -1;
    bool alive   = false;
    SnakeBody body;
    int  lastDir = DIR_UP;

    inline Coord head() const { return body.front(); }
    inline Coord tail() const { return body.back();  }
    inline int   len()  const { return body.size();  }
    inline int   facing() const {
        if (body.size() < 2) return DIR_UP;
        Coord d = body[0] - body[1];
        for (int i=0;i<4;i++) if(DIRS[i].x==d.x&&DIRS[i].y==d.y) return i;
        return DIR_UP;
    }
    inline int forbidden() const {
        if (body.size() < 2) return -1;
        Coord d = body[1] - body[0];
        for (int i=0;i<4;i++) if(DIRS[i].x==d.x&&DIRS[i].y==d.y) return i;
        return -1;
    }
};

struct State {
    BitBoard walls;
    BitBoard apples;
    Snake    snakes[MAX_SNAKES];
    int      nSnakes   = 0;
    int      turn      = 0;
    int      losses[2] = {0, 0};
    BitBoard cachedBody;
    bool     bodyDirty = true;

    inline void rebuildBodyBoard() {
        cachedBody.reset();
        for (int i=0;i<nSnakes;i++)
            if (snakes[i].alive)
                for (auto& c : snakes[i].body) cachedBody.setC(c);
        bodyDirty = false;
    }
    inline const BitBoard& bodyBoard() {
        if (bodyDirty) rebuildBodyBoard();
        return cachedBody;
    }
    inline BitBoard bodyBoardConst() const {
        BitBoard b;
        for (int i=0;i<nSnakes;i++)
            if (snakes[i].alive)
                for (auto& c : snakes[i].body) b.setC(c);
        return b;
    }
    inline int scoreFor(int owner) const {
        int s=0;
        for (int i=0;i<nSnakes;i++)
            if (snakes[i].alive && snakes[i].owner==owner) s+=snakes[i].len();
        return s;
    }
    inline int aliveCount(int owner) const {
        int c=0;
        for (int i=0;i<nSnakes;i++)
            if (snakes[i].alive && snakes[i].owner==owner) c++;
        return c;
    }
};

inline bool cellSupported(int x, int y,
                           const BitBoard& walls, const BitBoard& apples,
                           const BitBoard& blocked) {
    if (y + 1 >= H) return true;
    Coord below(x, y + 1);
    return walls.tstC(below) || apples.tstC(below) || blocked.tstC(below);
}

void simulate(State& st, const int moves[]) {

    for (int i=0;i<st.nSnakes;i++) {
        Snake& sn = st.snakes[i];
        if (!sn.alive) continue;
        int dir = moves[i];
        if (dir == sn.forbidden() || dir < 0 || dir > 3) dir = sn.facing();
        sn.lastDir = dir;
        Coord newHead = sn.head() + DIRS[dir];
        bool willEat  = newHead.inBounds() && st.apples.tstC(newHead);
        if (!willEat) sn.body.pop_back();
        sn.body.push_front(newHead);
    }

    for (int i=0;i<st.nSnakes;i++) {
        Snake& sn = st.snakes[i];
        if (!sn.alive) continue;
        if (sn.head().inBounds() && st.apples.tstC(sn.head()))
            st.apples.clrC(sn.head());
    }

    bool   toBehead[MAX_SNAKES] = {};
    Coord  heads[MAX_SNAKES];
    for (int i=0;i<st.nSnakes;i++)
        heads[i] = st.snakes[i].alive ? st.snakes[i].head() : Coord(-1,-1);

    for (int i=0;i<st.nSnakes;i++) {
        Snake& sn = st.snakes[i];
        if (!sn.alive) continue;
        Coord h = heads[i];
        if (!h.inBounds())         { toBehead[i]=true; continue; }
        if (st.walls.tstC(h))      { toBehead[i]=true; continue; }
        for (int k=1;k<sn.len();k++)
            if (sn.body[k]==h)     { toBehead[i]=true; break; }
        if (toBehead[i]) continue;
        for (int j=0;j<st.nSnakes;j++) {
            if (j==i || !st.snakes[j].alive) continue;
            for (int k=1;k<st.snakes[j].len();k++)
                if (st.snakes[j].body[k]==h) { toBehead[i]=true; break; }
            if (toBehead[i]) break;
        }
        if (toBehead[i]) continue;
        for (int j=0;j<st.nSnakes;j++) {
            if (j==i || !st.snakes[j].alive) continue;
            if (heads[j]==h && st.snakes[j].len()>=sn.len()) { toBehead[i]=true; break; }
        }
    }

    for (int i=0;i<st.nSnakes;i++) {
        if (!toBehead[i]) continue;
        Snake& sn = st.snakes[i];
        if (sn.len() <= 3) { st.losses[sn.owner] += sn.len(); sn.alive = false; }
        else               { st.losses[sn.owner]++; sn.body.pop_front(); }
    }

    {
        int maxGravIter = H + 5;
        for (int gravIter=0; gravIter<maxGravIter; gravIter++) {
            bool somethingFell = false;
            bool isAirborne[MAX_SNAKES] = {};
            bool isGrounded[MAX_SNAKES] = {};
            for (int i=0;i<st.nSnakes;i++)
                if (st.snakes[i].alive) isAirborne[i] = true;

            bool gotGrounded = true;
            while (gotGrounded) {
                gotGrounded = false;
                for (int i=0;i<st.nSnakes;i++) {
                    if (!isAirborne[i]) continue;
                    Snake& sn = st.snakes[i];
                    bool grnd = false;
                    for (auto& c : sn.body) {
                        if (!c.inBounds()) continue;
                        Coord below(c.x, c.y+1);
                        if (below.y>=H || st.walls.tstC(below) || st.apples.tstC(below))
                            { grnd=true; break; }
                        for (int gi=0;gi<st.nSnakes;gi++) {
                            if (!isGrounded[gi]) continue;
                            for (auto& gp : st.snakes[gi].body)
                                if (gp==below) { grnd=true; break; }
                            if (grnd) break;
                        }
                        if (grnd) break;
                    }
                    if (grnd) { isGrounded[i]=true; isAirborne[i]=false; gotGrounded=true; }
                }
            }
            for (int i=0;i<st.nSnakes;i++) {
                if (!isAirborne[i]) continue;
                somethingFell = true;
                Snake& sn = st.snakes[i];
                for (auto& c : sn.body) c.y++;
                bool allOut = true;
                for (auto& c : sn.body) if (c.y<H) { allOut=false; break; }
                if (allOut) sn.alive = false;
            }
            if (!somethingFell) break;
        }
    }
    st.bodyDirty = true;
    st.turn++;
}

static int ff_visited[MAX_CELLS];
static int ff_token = 0;

int floodFillCount(Coord src, const BitBoard& walls, const BitBoard& blocked) {
    if (!src.inBounds()) return 0;
    ff_token++;
    static Coord q[MAX_CELLS];
    int qHead=0, qTail=0;
    q[qTail++] = src;
    ff_visited[src.idx()] = ff_token;
    int count = 0;
    while (qHead < qTail) {
        Coord c = q[qHead++]; count++;
        for (int d=0;d<4;d++) {
            Coord n = c + DIRS[d];
            if (!n.inBounds()) continue;
            int ni = n.idx();
            if (ff_visited[ni]==ff_token) continue;
            if (walls.tst(ni) || blocked.tst(ni)) continue;
            ff_visited[ni] = ff_token;
            q[qTail++] = n;
        }
    }
    return count;
}

static int ffg_visited[MAX_H][MAX_W];
static int ffg_token = 0;

int floodFillGravity(Coord src, const BitBoard& walls,
                     const BitBoard& apples, const BitBoard& blocked) {
    if (!src.inBounds()) return 0;
    ffg_token++;
    static Coord q[MAX_CELLS];
    int qHead=0, qTail=0;
    q[qTail++] = src;
    ffg_visited[src.y][src.x] = ffg_token;
    int count = 0;
    while (qHead < qTail) {
        Coord c = q[qHead++]; count++;
        for (int d=0;d<4;d++) {
            int nx = c.x+DIRS[d].x, ny = c.y+DIRS[d].y;
            if (nx<0||nx>=W||ny<0||ny>=H) continue;
            Coord next(nx,ny);
            if (!walls.tstC(next) && !blocked.tstC(next))
                if (ffg_visited[ny][nx] != ffg_token) {
                    ffg_visited[ny][nx] = ffg_token;
                    q[qTail++] = next;
                }
            int finalY = ny;
            if (!cellSupported(nx,ny,walls,apples,blocked)) {
                int fy = ny;
                while (fy+1<H) {
                    Coord b(nx,fy+1);
                    if (walls.tstC(b)||apples.tstC(b)||blocked.tstC(b)) break;
                    fy++;
                }
                if (fy+1>=H) {
                    Coord bottom(nx,fy);
                    if (fy<H && !walls.tstC(bottom) && !blocked.tstC(bottom)) finalY = fy;
                    else continue;
                } else { finalY = fy; }
            }
            if (ffg_visited[finalY][nx]==ffg_token) continue;
            Coord dest(nx,finalY);
            if (walls.tstC(dest)||blocked.tstC(dest)) continue;
            ffg_visited[finalY][nx] = ffg_token;
            q[qTail++] = dest;
        }
    }
    return count;
}

static int bfs_visited[MAX_H][MAX_W];
static int bfs_token = 0;

int bfsAppleDist(Coord src, const BitBoard& walls,
                 const BitBoard& blocked, const BitBoard& apples) {
    if (!src.inBounds()) return INT_MAX;
    bfs_token++;
    static Coord  q[MAX_CELLS];
    static int    dist[MAX_H][MAX_W];
    int qHead=0, qTail=0;
    q[qTail++] = src;
    bfs_visited[src.y][src.x] = bfs_token;
    dist[src.y][src.x] = 0;
    while (qHead < qTail) {
        Coord c = q[qHead++];
        int   cd = dist[c.y][c.x];
        if (apples.tstC(c)) return cd;
        for (int d=0;d<4;d++) {
            Coord n = c + DIRS[d];
            if (!n.inBounds()) continue;
            if (bfs_visited[n.y][n.x]==bfs_token) continue;
            if (walls.tstC(n)||blocked.tstC(n)) continue;
            bfs_visited[n.y][n.x] = bfs_token;
            dist[n.y][n.x] = cd+1;
            q[qTail++] = n;
        }
    }
    return INT_MAX;
}

inline int appleEatFreeSpace(Coord applePos, const BitBoard& walls,
                              const BitBoard& fullBlocked) {

    return floodFillCount(applePos, walls, fullBlocked);
}

inline int appleEatDeficit(Coord applePos, int snLen,
                            const BitBoard& walls, const BitBoard& fullBlocked) {
    int free = appleEatFreeSpace(applePos, walls, fullBlocked);
    return max(0, (snLen + 1) - free);
}

static int   bfsDirVisited[MAX_H][MAX_W];
static int8_t bfsDirFirst  [MAX_H][MAX_W];
static int   bfsDirToken = 0;

int bfsDir(Coord src, Coord target,
           const BitBoard& walls, const BitBoard& blocked) {
    if (!src.inBounds() || !target.inBounds()) return -1;
    if (src == target) return -1;

    bfsDirToken++;
    static Coord q[MAX_CELLS];
    int qHead = 0, qTail = 0;

    bfsDirVisited[src.y][src.x] = bfsDirToken;
    bfsDirFirst[src.y][src.x]   = -1;

    for (int d = 0; d < 4; d++) {
        Coord n = src + DIRS[d];
        if (!n.inBounds()) continue;
        if (bfsDirVisited[n.y][n.x] == bfsDirToken) continue;
        if (walls.tstC(n) || blocked.tstC(n)) continue;
        bfsDirVisited[n.y][n.x] = bfsDirToken;
        bfsDirFirst  [n.y][n.x] = (int8_t)d;
        if (n == target) return d;
        q[qTail++] = n;
    }

    while (qHead < qTail) {
        Coord c = q[qHead++];
        int8_t fd = bfsDirFirst[c.y][c.x];
        for (int d = 0; d < 4; d++) {
            Coord n = c + DIRS[d];
            if (!n.inBounds()) continue;
            if (bfsDirVisited[n.y][n.x] == bfsDirToken) continue;
            if (walls.tstC(n) || blocked.tstC(n)) continue;
            bfsDirVisited[n.y][n.x] = bfsDirToken;
            bfsDirFirst  [n.y][n.x] = fd;
            if (n == target) return fd;
            q[qTail++] = n;
        }
    }
    return -1;
}

void assignApplesToSnakes(const State& st, int myOwner,
                          const Coord appleList[], int nApples,
                          int assignOut[]) {
    fill(assignOut, assignOut + MAX_SNAKES, -1);
    if (nApples == 0) return;

    struct SA { int si, ai, dist; };
    static SA cands[MAX_SNAKES * 200];
    int nCand = 0;

    for (int i = 0; i < st.nSnakes; i++) {
        if (!st.snakes[i].alive || st.snakes[i].owner != myOwner) continue;
        Coord h = st.snakes[i].head();
        if (!h.inBounds()) continue;
        for (int a = 0; a < nApples; a++) {
            int md = h.manhattan(appleList[a]);

            cands[nCand++] = {i, a, md * (H + 1) + appleList[a].y};
        }
    }
    if (nCand == 0) return;

    sort(cands, cands + nCand, [](const SA& a, const SA& b){ return a.dist < b.dist; });

    bool snakeUsed[MAX_SNAKES] = {};
    bool appleUsed[200]        = {};
    for (int ci = 0; ci < nCand; ci++) {
        int si = cands[ci].si, ai = cands[ci].ai;
        if (snakeUsed[si] || appleUsed[ai]) continue;
        assignOut[si] = ai;
        snakeUsed[si] = true;
        appleUsed[ai] = true;
    }
}
struct VoronoiResult {
    int territory[2]   = {0, 0};
    int energyControl[2] = {0, 0};
    int reachable[MAX_SNAKES] = {};
    int closestEnergy[MAX_SNAKES];
    struct AppleInfo {
        int bestSi=-1, bestDist=INT_MAX, secondSi=-1, secondDist=INT_MAX;
    };
    AppleInfo appleInfos[200];
    int       nApples = 0;
};

struct VBucket {
    vector<uint32_t> data;
    inline void push(int x,int y,int si,int tether) {
        data.push_back((x)|(y<<8)|(si<<16)|(tether<<24));
    }
    inline void pop(int& x,int& y,int& si,int& tether) {
        uint32_t val = data.back(); data.pop_back();
        x=(val)&0xFF; y=(val>>8)&0xFF; si=(val>>16)&0xFF; tether=(val>>24)&0xFF;
    }
    inline bool empty() const { return data.empty(); }
    inline void reset()       { data.clear(); }
};
static VBucket vbuckets[4096];

VoronoiResult computeVoronoi(const State& st, const BitBoard& blocked,
                              Coord appleList[], int nApples) {
    VoronoiResult vr;
    vr.nApples = nApples;
    fill(vr.closestEnergy, vr.closestEnergy+MAX_SNAKES, INT_MAX);

    static int  dist1[MAX_H][MAX_W], dist2[MAX_H][MAX_W];
    static int  snake1[MAX_H][MAX_W], snake2[MAX_H][MAX_W];
    static bool visited[MAX_H][MAX_W];

    for (int y=0;y<H;y++) for (int x=0;x<W;x++) {
        dist1[y][x]=INT_MAX; snake1[y][x]=-1;
        dist2[y][x]=INT_MAX; snake2[y][x]=-1;
        visited[y][x]=false;
    }

    int vmax_bucket=0, vmin_bucket=0;

    for (int i=0;i<st.nSnakes;i++) {
        if (!st.snakes[i].alive) continue;
        Coord h = st.snakes[i].head();
        if (h.inBounds()) vbuckets[0].push(h.x,h.y,i,0);
    }

    while (vmin_bucket <= vmax_bucket) {
        if (vbuckets[vmin_bucket].empty()) { vmin_bucket++; continue; }
        int cx,cy,si,tether;
        vbuckets[vmin_bucket].pop(cx,cy,si,tether);
        int cost = vmin_bucket;

        bool dominated = false;
        if (cost < dist1[cy][cx]) {
            if (snake1[cy][cx]!=si) { dist2[cy][cx]=dist1[cy][cx]; snake2[cy][cx]=snake1[cy][cx]; }
            dist1[cy][cx]=cost; snake1[cy][cx]=si;
        } else if (snake1[cy][cx]!=si && cost < dist2[cy][cx]) {
            dist2[cy][cx]=cost; snake2[cy][cx]=si;
        } else { dominated=true; }
        if (dominated) continue;

        if (!visited[cy][cx] && cost==dist1[cy][cx] && snake1[cy][cx]==si) {
            visited[cy][cx]=true;
            int owner = st.snakes[si].owner;
            vr.territory[owner]++;
            vr.reachable[si]++;
            Coord c(cx,cy);
            if (st.apples.tstC(c)) {
                vr.energyControl[owner]++;
                vr.closestEnergy[si]=min(vr.closestEnergy[si],cost);
            }
        }
        for (int d=0;d<4;d++) {
            int nx=cx+DIRS[d].x, ny=cy+DIRS[d].y;
            if (nx<0||nx>=W||ny<0||ny>=H) continue;
            Coord next(nx,ny);
            if (blocked.tstC(next)) continue;
            bool supported = cellSupported(nx,ny,st.walls,st.apples,blocked);
            int nextTether  = supported ? 0 : (tether+1);
            if (nextTether < st.snakes[si].len()) {
                int cDirect = cost+(supported?1:2);
                if (cDirect<dist2[ny][nx]||cDirect<dist1[ny][nx]) {
                    int bc=min(cDirect,4095);
                    vbuckets[bc].push(nx,ny,si,nextTether);
                    if (bc>vmax_bucket) vmax_bucket=bc;
                }
            }
            if (!supported) {
                int fy=ny;
                while (fy+1<H && !cellSupported(nx,fy+1,st.walls,st.apples,blocked)) fy++;
                Coord bottom(nx,fy);
                if (fy<H && !st.walls.tstC(bottom) && !blocked.tstC(bottom)) {
                    int fallDist = fy-ny;
                    int cFall    = cost+1+fallDist*2;
                    if (cFall<dist2[fy][nx]||cFall<dist1[fy][nx]) {
                        int bc=min(cFall,4095);
                        vbuckets[bc].push(nx,fy,si,0);
                        if (bc>vmax_bucket) vmax_bucket=bc;
                    }
                }
            }
        }
    }

    for (int i=vmin_bucket; i<=vmax_bucket; ++i) vbuckets[i].reset();

    for (int a=0;a<nApples;a++) {
        Coord ap = appleList[a];
        if (!ap.inBounds()) continue;
        vr.appleInfos[a].bestSi     = snake1[ap.y][ap.x];
        vr.appleInfos[a].bestDist   = dist1[ap.y][ap.x];
        vr.appleInfos[a].secondSi   = snake2[ap.y][ap.x];
        vr.appleInfos[a].secondDist = dist2[ap.y][ap.x];
    }
    return vr;
}

double gravityExploitScore(const State& st, int myOwner, const BitBoard& blocked) {
    double score = 0.0;
    int oppOwner = 1-myOwner;
    for (int i=0;i<st.nSnakes;i++) {
        if (!st.snakes[i].alive || st.snakes[i].owner!=oppOwner) continue;
        for (auto& c : st.snakes[i].body) {
            Coord below(c.x,c.y+1);
            if (!below.inBounds()) continue;
            if (st.apples.tstC(below)) {
                int  fallDist=0;
                Coord fp=below;
                while (fp.y+1<H) {
                    Coord b(fp.x,fp.y+1);
                    if (st.walls.tstC(b)) break;
                    fp.y++; fallDist++;
                }
                if (fp.y+1>=H && !cellSupported(fp.x,fp.y,st.walls,st.apples,blocked))
                    score += P.GRAVITY_EXPLOIT_FALL_DEATH;
                else if (fallDist>=3)
                    score += fallDist*P.GRAVITY_EXPLOIT_FALL_FAR;
            }
        }
    }
    return score;
}

int validMovesSafe(const State& st, int si, const BitBoard& blocked, int out[]);

double headCollisionPenalty(const State& st, int si) {
    const Snake& sn = st.snakes[si];
    if (!sn.alive) return 0;
    Coord h = sn.head();
    if (!h.inBounds()) return 0;
    double penalty = 0;
    for (int j=0;j<st.nSnakes;j++) {
        if (j==si || !st.snakes[j].alive || st.snakes[j].owner==sn.owner) continue;
        Coord oh = st.snakes[j].head();
        if (!oh.inBounds()) continue;
        int hd = h.manhattan(oh);
        int myLen=sn.len(), oppLen=st.snakes[j].len();
        if      (hd<=1) {
            if (myLen<=oppLen) penalty+=(smallMap?P.HEAD_CLOSE_SMALLER_SMALL:P.HEAD_CLOSE_SMALLER);
            else               penalty+=(smallMap?P.HEAD_CLOSE_BIGGER_SMALL:P.HEAD_CLOSE_BIGGER);
        } else if (hd==2) {
            if (myLen<=oppLen) penalty+=(smallMap?P.HEAD_NEAR_SMALLER_SMALL:P.HEAD_NEAR_SMALLER);
            if (smallMap && (h.x==oh.x||h.y==oh.y) && myLen<=oppLen) penalty+=P.HEAD_NEAR_LINE_SMALL;
        }
    }
    return penalty;
}

double edgePenalty(Coord h) {
    if (!h.inBounds()) return 0;
    double pen=0;
    if (smallMap) {
        int dx=min(h.x, W-1-h.x), dy=min(h.y, H-1-h.y);
        if (dx==0) pen+=P.EDGE_X;
        if (dy==0) pen+=P.EDGE_Y;
        if (dx==0 && dy==0) pen+=P.CORNER_EXTRA;
    }
    return pen;
}

double snakeGravityRisk(const Snake& sn, const BitBoard& walls,
                         const BitBoard& apples, const BitBoard& blocked) {
    if (!sn.alive) return 0;
    Coord h = sn.head();
    if (!h.inBounds()) return P.GRAVITY_RISK_NONE;
    bool anySupported = false;
    for (auto& c : sn.body) {
        if (!c.inBounds()) continue;
        if (cellSupported(c.x,c.y,walls,apples,blocked)) { anySupported=true; break; }
    }
    if (anySupported) return 0;

    int minFall = INT_MAX;
    for (auto& c : sn.body) {
        if (!c.inBounds()) continue;
        int fy = c.y;
        while (fy + 1 < H) {
            Coord b(c.x, fy + 1);
            if (walls.tstC(b) || apples.tstC(b) || blocked.tstC(b)) break;
            fy++;
        }
        int fall = fy - c.y;

        if (fy + 1 >= H && !cellSupported(c.x, fy, walls, apples, blocked))
            fall = 100;
        minFall = min(minFall, fall);
    }

    if (minFall >= 100) return P.GRAVITY_DEATH;
    if (minFall == 0)   return 0;
    // Smooth quadratic ramp: penalty grows with fall distance, no cliff at minFall==1
    double fallPenalty = (minFall <= 2)
        ? -minFall * P.GRAVITY_RISK_LOW
        : -minFall * P.GRAVITY_RISK_HIGH;
    return fallPenalty;
}

double evaluate(const State& st, int myOwner, bool fast=false,
                const State* initSt=nullptr, double stallUrgency=1.0,
                const map<int,deque<Coord>>* hist=nullptr) {
    int opp=1-myOwner;
    int myAlive  = st.aliveCount(myOwner);
    int oppAlive = st.aliveCount(opp);

    if (myAlive==0 && oppAlive==0) return 0;
    if (myAlive==0)                return -1e6;
    if (oppAlive==0 && myAlive>0)  return 1e5 + st.scoreFor(myOwner)*100.0;

    int    myLen    = st.scoreFor(myOwner);
    int    oppLen   = st.scoreFor(opp);
    double score    = 0;

    int    turnsElapsed = st.turn;
    double timeFraction  = min(1.0, (double)turnsElapsed / 120.0);
    double scoreFraction = (myLen > 0 && oppLen > 0) ?
        abs(myLen - oppLen) / (double)(myLen + oppLen) : 0.0;
    double phase    = min(1.0, max(timeFraction, scoreFraction * 0.5));
    int    lenDiff  = myLen - oppLen;
    bool   winning  = lenDiff > 2;
    bool   losing   = lenDiff < -2;

    double lenWeight = smallMap ? P.LEN_WEIGHT_SMALL : P.LEN_WEIGHT;
    if (phase>0.5 && winning) lenWeight = P.LEN_WEIGHT_WINNING_LATE;
    if (phase>0.7 && losing)  lenWeight = P.LEN_WEIGHT_LOSING_LATE;
    score += lenDiff * lenWeight;

    if (initSt != nullptr) {
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive || st.snakes[i].owner!=myOwner) continue;
            if (st.snakes[i].head() == initSt->snakes[i].head())
                score += P.ANTI_TRAMPOLINE;
            int lenDelta = st.snakes[i].len() - initSt->snakes[i].len();
            if (lenDelta>0) score += lenDelta * P.EAT_BONUS * stallUrgency;
            if (hist != nullptr) {
                Coord h = st.snakes[i].head();
                auto it = hist->find(st.snakes[i].id);
                if (it != hist->end()) {

                    double revisitUrgency = min(stallUrgency, P.STALL_URGENCY_CAP);
                    for (const auto& past_h : it->second)
                        if (h==past_h) { score += P.STALL_REVISIT * revisitUrgency; break; }
                }
            }
        }
    }

    Coord  appleList[200];
    int    nApples=0;
    for (int y=0;y<H&&nApples<200;y++)
        for (int x=0;x<W&&nApples<200;x++)
            if (st.apples.tstC({x,y})) appleList[nApples++]={x,y};

    double scarcityMult = (nApples<=2) ? P.SCARCITY_MULT_LOW :
                          (nApples<=5) ? P.SCARCITY_MULT_MED :
                          (nApples<=10)? P.SCARCITY_MULT_HIGH : 1.0;
    if (smallMap && scarcityMult<1.5) scarcityMult=1.5;
    double advantageMult  = (myAlive>oppAlive) ? 1.0+0.3*(myAlive-oppAlive) : 1.0;
    double aggressionMult = (phase>0.6&&winning)?0.6:((phase>0.5&&losing)?1.5:1.0);
    double growthWeight   = P.GROWTH_BASE * scarcityMult * advantageMult * aggressionMult * stallUrgency;

    if (turnsElapsed > 0 && turnsElapsed <= 20) {
        double earlyMult = 1.0 + 1.5 * max(0.0, (20.0 - turnsElapsed) / 20.0);
        growthWeight *= earlyMult;
    }

    if (gAppleRich) {
        growthWeight *= P.APPLE_RICH_APPLE_MULT;
    }

    {
        Coord myHeads[MAX_SNAKES]; int nMyH = 0;
        for (int i = 0; i < st.nSnakes; i++) {
            if (!st.snakes[i].alive || st.snakes[i].owner != myOwner) continue;
            if (st.snakes[i].head().inBounds())
                myHeads[nMyH++] = st.snakes[i].head();
        }
        if (nMyH > 1) {
            double spreadScale = gAppleRich ? 1.0 : 0.4;
            for (int a = 0; a < nMyH; a++)
                for (int b = a+1; b < nMyH; b++) {
                    int d = myHeads[a].manhattan(myHeads[b]);
                    int thresh = (int)P.APPLE_RICH_SPREAD_DIST;
                    if (d < thresh)
                        score -= P.APPLE_RICH_SPREAD_PEN * (thresh - d) * spreadScale;
                }
        }
    }

    BitBoard bodyBrd  = st.bodyBoardConst();
    BitBoard blocked  = st.walls | bodyBrd;

    {
        BitBoard myBrd;
        for (int i=0;i<st.nSnakes;i++)
            if (st.snakes[i].alive && st.snakes[i].owner==myOwner)
                for (auto& c : st.snakes[i].body) myBrd.setC(c);
        int staircases=0;
        for (int i=0;i<st.nSnakes;i++)
            if (st.snakes[i].alive && st.snakes[i].owner==myOwner)
                for (auto& c : st.snakes[i].body)
                    if (c.y+1<H && myBrd.tstC({c.x,c.y+1})) staircases++;
        score += staircases * P.STAIRCASE;
    }

    if (fast) {
        bool appleAssigned[200]={}, snakeAssigned[MAX_SNAKES]={};
        struct SA { int si,ai,dist; };
        static SA candidates[200*MAX_SNAKES];
        int nCand=0;
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive || st.snakes[i].owner!=myOwner) continue;
            Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
            for (int a=0;a<nApples;a++) {
                int md = h.manhattan(appleList[a]);

                candidates[nCand++]={i, a, md*(H+1)+appleList[a].y};
            }
        }
        sort(candidates, candidates+nCand, [](const SA& a,const SA& b){ return a.dist<b.dist; });
        for (int ci=0;ci<nCand;ci++) {
            auto& ca=candidates[ci];
            if (snakeAssigned[ca.si]||appleAssigned[ca.ai]) continue;
            snakeAssigned[ca.si]=appleAssigned[ca.ai]=true;
            int realDist = ca.dist / (H+1);

            double appleScore = growthWeight / (1.0 + realDist);
            if (realDist <= 2) {
                int snLen = st.snakes[ca.si].len();
                int deficit = appleEatDeficit(appleList[ca.ai], snLen, st.walls, blocked);
                if (deficit > 0) {
                    appleScore += P.TRAP_APPLE_EAT_PEN * deficit * 0.5;
                    if (deficit >= snLen)
                        appleScore += P.TRAP_APPLE_HARD_PEN * 0.5;
                }
            }

            if (H > 1)
                appleScore += P.APPLE_HEIGHT_BONUS * (H - 1 - appleList[ca.ai].y) / (double)(H-1) * 0.5;
            score += appleScore;
        }
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner||snakeAssigned[i]) continue;
            Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
            int bestMD=INT_MAX; int bestAppleY=H;
            for (int a=0;a<nApples;a++) {
                int d=h.manhattan(appleList[a]);
                if (d<bestMD||(d==bestMD&&appleList[a].y<bestAppleY))
                    { bestMD=d; bestAppleY=appleList[a].y; }
            }
            if (bestMD<INT_MAX) {
                score+=growthWeight*P.FAST_APPLE_FALLBACK/(1.0+bestMD);
                if (H>1) score+=P.APPLE_HEIGHT_BONUS*(H-1-bestAppleY)/(double)(H-1)*0.25;
            }
        }
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=opp) continue;
            Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
            int bestMD=INT_MAX;
            for (int a=0;a<nApples;a++) bestMD=min(bestMD,h.manhattan(appleList[a]));
            if (bestMD<=3) score+=P.FAST_OPP_NEAR_APPLE/(1.0+bestMD);
        }
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            int safeMoves[4];
            int nSafe=validMovesSafe(st,i,blocked,safeMoves);
            if      (nSafe==0) score+=(smallMap?P.NO_MOVES_PEN_SMALL:P.NO_MOVES_PEN);
            else if (nSafe==1) score+=(smallMap?P.ONE_MOVE_PEN_SMALL:P.ONE_MOVE_PEN);
            else if (nSafe==2&&smallMap) score+=P.TWO_MOVES_PEN_SMALL;
            else if (nSafe>2) score+=P.MOBILITY_BONUS*(nSafe-2);
        }
        if (smallMap) {
            for (int i=0;i<st.nSnakes;i++) {
                if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
                Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
                int reachable=floodFillCount(h,st.walls,blocked);
                int snLen=st.snakes[i].len();
                if (reachable<snLen)    score+=(snLen-reachable+1)*P.FAST_TRAP_SEVERE;
                else if (reachable<snLen*2) score+=(snLen*2-reachable)*P.FAST_TRAP_MILD;
            }
        }
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            Coord h=st.snakes[i].head(), t=st.snakes[i].tail();
            if (!h.inBounds()||!t.inBounds()) continue;
            int tailDist=h.manhattan(t);
            double tailWeight = (phase>0.6&&winning)?P.FAST_TAIL_WINNING:
                                (nApples==0)?P.FAST_TAIL_NO_FOOD:P.FAST_TAIL_DEFAULT;
            if (smallMap) tailWeight*=P.FAST_TAIL_SMALL_MULT;
            if (tailDist>0) score+=tailWeight/(1.0+tailDist);
        }

        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            if (smallMap) {

                score+=headCollisionPenalty(st,i);
                score+=edgePenalty(st.snakes[i].head());
            } else {

                Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
                int myLen=st.snakes[i].len();
                for (int j=0;j<st.nSnakes;j++) {
                    if (j==i||!st.snakes[j].alive||st.snakes[j].owner==st.snakes[i].owner) continue;
                    Coord oh=st.snakes[j].head(); if (!oh.inBounds()) continue;
                    int hd=h.manhattan(oh), oppLen=st.snakes[j].len();
                    if      (hd<=1) { score+=(myLen<=oppLen)?P.FAST_HEAD_CLOSE_SMALLER:P.FAST_HEAD_CLOSE_BIGGER; }
                    else if (hd==2) { if (myLen<=oppLen) score+=P.FAST_HEAD_NEAR_SMALLER; }
                }
            }
        }
    } else {

        VoronoiResult vr = computeVoronoi(st, blocked, appleList, nApples);

        for (int a=0;a<nApples;a++) {
            auto& ai=vr.appleInfos[a];
            if (ai.bestSi<0||ai.bestDist==INT_MAX) continue;
            int bestOwner   = st.snakes[ai.bestSi].owner;
            int secondOwner = (ai.secondSi>=0)?st.snakes[ai.secondSi].owner:-1;

            int trapDeficit = 0;
            if (bestOwner == myOwner && ai.bestDist <= 3) {

                int snLen = st.snakes[ai.bestSi].len();
                trapDeficit = appleEatDeficit(appleList[a], snLen, st.walls, blocked);
            }

            double heightBonus = 0.0;
            if (H > 1)
                heightBonus = P.APPLE_HEIGHT_BONUS * (H - 1 - appleList[a].y) / (double)(H - 1);

            double appleBaseScore = 0.0;
            if (bestOwner==myOwner) {
                if (ai.secondSi>=0 && secondOwner==opp &&
                    ai.bestDist==ai.secondDist &&
                    st.snakes[ai.secondSi].len()>=st.snakes[ai.bestSi].len())
                    appleBaseScore = growthWeight*P.VORONOI_APPLE_TIE_LOSE/(1.0+ai.bestDist);
                else if (ai.secondSi<0||ai.secondDist==INT_MAX||secondOwner==myOwner)
                    appleBaseScore = growthWeight*P.VORONOI_APPLE_CLEAR/(1.0+ai.bestDist);
                else if (ai.bestDist<ai.secondDist-1)
                    appleBaseScore = growthWeight/(1.0+ai.bestDist);
                else if (ai.bestDist<ai.secondDist)
                    appleBaseScore = growthWeight*P.VORONOI_APPLE_SLIGHT/(1.0+ai.bestDist);
                else
                    appleBaseScore = growthWeight*P.VORONOI_APPLE_CONTESTED/(1.0+ai.bestDist);

                if (trapDeficit > 0) {
                    appleBaseScore += P.TRAP_APPLE_EVAL_PEN * trapDeficit;
                    if (trapDeficit >= st.snakes[ai.bestSi].len())
                        appleBaseScore += P.TRAP_APPLE_HARD_PEN;
                }

                score += appleBaseScore + heightBonus;
            } else {
                if (ai.secondSi>=0 && st.snakes[ai.secondSi].owner==myOwner) {
                    int myDist=ai.secondDist;
                    if (myDist<ai.bestDist+2) score+=growthWeight*0.2/(1.0+myDist)+heightBonus*0.3;
                    else                       score+=P.OPP_MAXLEN_THREAT/(1.0+ai.bestDist);
                } else {
                    score+=P.OPP_MAXLEN_THREAT/(1.0+ai.bestDist);
                }
            }
        }

        score += (vr.energyControl[myOwner]-vr.energyControl[opp])*P.ENERGY_CONTROL_WEIGHT;

        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            double ceW = P.CLOSEST_ENERGY_WEIGHT * (gAppleRich ? P.APPLE_RICH_CLOSEST_MULT : 1.0);
            if (vr.closestEnergy[i]<INT_MAX)
                score+=ceW*scarcityMult*stallUrgency/(1.0+vr.closestEnergy[i]);
            else {
                int bfsDist=bfsAppleDist(st.snakes[i].head(),st.walls,blocked,st.apples);
                if (bfsDist<INT_MAX)
                    score+=P.CLOSEST_ENERGY_FALLBACK*scarcityMult*stallUrgency/(1.0+bfsDist);
                else {

                    Coord h=st.snakes[i].head();
                    if (h.inBounds()) {
                        int reach=floodFillCount(h,st.walls,blocked);
                        score += reach * 2.0;
                    }
                    score+=P.NO_ENERGY_PEN;
                }
            }
        }

        double territoryWeight = (phase>0.7&&winning)?P.TERRITORY_WEIGHT_WINNING_LATE:P.TERRITORY_WEIGHT;
        if (smallMap) {
            territoryWeight=(phase>0.5)?P.TERRITORY_WEIGHT_SMALL_LATE:P.TERRITORY_WEIGHT_SMALL;
            if (tinyMap) territoryWeight*=1.5;
            if (winning && phase>0.5) territoryWeight*=1.5;
        }

        if (gAppleRich) territoryWeight *= P.APPLE_RICH_TERR_SCALE;
        score += (vr.territory[myOwner]-vr.territory[opp])*territoryWeight;

        double trapMult = smallMap ? P.TRAP_MULT_SMALL : 1.0;
        if (tinyMap) trapMult = P.TRAP_MULT_TINY;

        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
            int reachable=floodFillCount(h,st.walls,blocked);
            int snLen=st.snakes[i].len();
            if      (reachable<snLen)    score+=(snLen-reachable+1)*P.TRAP_SEVERE*trapMult;
            else if (reachable<snLen*2)  score+=(snLen*2-reachable)*P.TRAP_MILD*trapMult;
            else                         score+=log(reachable+1)*P.LOG_SPACE_BONUS;
            if (smallMap) {
                double spaceRatio=(double)reachable/max(1,totalCells);
                if (spaceRatio>0.5) score+=P.SPACE_GOOD;
                else if (spaceRatio<0.2) score+=P.SPACE_BAD;
            }
        }
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=opp) continue;
            Coord h=st.snakes[i].head(); if (!h.inBounds()) continue;
            int reachable=floodFillCount(h,st.walls,blocked);
            int snLen=st.snakes[i].len();
            if (reachable<snLen) {
                double trapBonus=smallMap?P.OPP_TRAP_BONUS_SMALL:P.OPP_TRAP_BONUS;
                score+=(snLen-reachable+1)*trapBonus;
            }
        }

        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            Coord h=st.snakes[i].head(), t=st.snakes[i].tail();
            if (!h.inBounds()||!t.inBounds()) continue;
            int tailDist=h.manhattan(t);
            double tailWeight=(phase>0.6&&winning)?P.TAIL_WINNING:
                               (nApples==0)?P.TAIL_NO_FOOD:
                               (vr.closestEnergy[i]==INT_MAX)?P.TAIL_NO_VORONOI:P.TAIL_DEFAULT;
            if (smallMap) tailWeight*=P.TAIL_SMALL_MULT;
            if (tailDist>0) score+=tailWeight/(1.0+tailDist);
        }

        score += gravityExploitScore(st, myOwner, blocked) * P.GRAVITY_EXPLOIT;
        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            score+=headCollisionPenalty(st,i);
            score+=edgePenalty(st.snakes[i].head());
        }

        for (int i=0;i<st.nSnakes;i++) {
            if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
            int safeMoves[4];
            int nSafe=validMovesSafe(st,i,blocked,safeMoves);
            if      (nSafe==0) score+=(smallMap?P.NO_MOVES_PEN_SMALL:P.NO_MOVES_PEN);
            else if (nSafe==1) score+=(smallMap?P.ONE_MOVE_PEN_SMALL:P.ONE_MOVE_PEN);
            else if (nSafe==2&&smallMap) score+=P.TWO_MOVES_PEN_SMALL;
            else if (nSafe>2)  score+=P.MOBILITY_BONUS*(nSafe-2);
        }
    }

    double aliveWeight=(phase<0.3)?P.ALIVE_EARLY:((phase<0.7)?P.ALIVE_MID:P.ALIVE_LATE);
    if (winning&&phase>0.5) aliveWeight*=P.ALIVE_WINNING_MULT;
    if (smallMap)           aliveWeight*=P.ALIVE_SMALL_MULT;
    score += (myAlive-oppAlive)*aliveWeight;

    score += myAlive  * P.ALIVE_OWN_PER_SNAKE;
    score -= oppAlive * P.ALIVE_OPP_PER_SNAKE;

    int myMaxLen=0, oppMaxLen=0;
    for (int i=0;i<st.nSnakes;i++) {
        if (!st.snakes[i].alive) continue;
        if (st.snakes[i].owner==myOwner) myMaxLen=max(myMaxLen,st.snakes[i].len());
        else                             oppMaxLen=max(oppMaxLen,st.snakes[i].len());
    }
    if (oppMaxLen>myMaxLen+2) score+=(oppMaxLen-myMaxLen)*P.OPP_MAXLEN_THREAT;

    for (int i=0;i<st.nSnakes;i++) {
        if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
        double risk=snakeGravityRisk(st.snakes[i],st.walls,st.apples,blocked);
        score += risk*(smallMap?P.GRAVITY_RISK_SMALL:P.GRAVITY_RISK_LARGE);
    }
    for (int i=0;i<st.nSnakes;i++) {
        if (!st.snakes[i].alive||st.snakes[i].owner!=myOwner) continue;
        if (st.snakes[i].len()<=3) score+=(smallMap?P.SHORT_3_SMALL:P.SHORT_3);
        else if (st.snakes[i].len()==4) score+=(smallMap?P.SHORT_4_SMALL:P.SHORT_4);
    }
    return score;
}

int validMovesCount(const State& st, int si, int out[]) {
    const Snake& sn = st.snakes[si];
    if (!sn.alive) return 0;
    int forb = sn.forbidden();
    int n = 0;
    for (int d=0;d<4;d++) {
        if (d==forb) continue;
        Coord nh = sn.head()+DIRS[d];
        if (!nh.inBounds()||st.walls.tstC(nh)) continue;
        out[n++]=d;
    }
    if (n==0) { for (int d=0;d<4;d++) out[n++]=d; }
    return n;
}

int validMovesSafe(const State& st, int si, const BitBoard& blocked, int out[]) {
    const Snake& sn = st.snakes[si];
    if (!sn.alive) return 0;
    int forb = sn.forbidden();
    BitBoard blk = blocked;
    if (sn.len()>=2) blk.clrC(sn.body.back());

    int safe[4],nSafe=0, risky[4],nRisky=0;
    for (int d=0;d<4;d++) {
        if (d==forb) continue;
        Coord nh = sn.head()+DIRS[d];
        if (!nh.inBounds())    { risky[nRisky++]=d; continue; }
        if (st.walls.tstC(nh)) continue;
        if (blk.tstC(nh))      { risky[nRisky++]=d; continue; }
        safe[nSafe++]=d;
    }
    if (nSafe>0)  { for (int i=0;i<nSafe;i++)  out[i]=safe[i];  return nSafe; }
    if (nRisky>0) { for (int i=0;i<nRisky;i++) out[i]=risky[i]; return nRisky; }
    int n=0; for (int d=0;d<4;d++) out[n++]=d; return n;
}

int greedyMove(const State& st, int si, const BitBoard* preBlocked=nullptr) {
    BitBoard blocked;
    if (preBlocked) blocked = *preBlocked;
    else            blocked = st.walls | st.bodyBoardConst();

    int moves[4];
    int nm=validMovesSafe(st,si,blocked,moves);
    if (nm==0) return st.snakes[si].facing();
    Coord h=st.snakes[si].head();
    if (!h.inBounds()) return moves[0];
    int snLen = st.snakes[si].len();

    bool anyAppleReachable = false;
    if (st.apples.popcount() > 0) {
        int dist = bfsAppleDist(h, st.walls, blocked, st.apples);
        anyAppleReachable = (dist < INT_MAX);
    }
    if (!anyAppleReachable) {

        int bestMove = moves[0]; int bestReach = -1;
        for (int mi=0;mi<nm;mi++) {
            Coord nh=h+DIRS[moves[mi]];
            if (!nh.inBounds()) continue;
            BitBoard tmpBlk=blocked; tmpBlk.setC(h);
            int reach=floodFillCount(nh,st.walls,tmpBlk);
            if (reach>bestReach) { bestReach=reach; bestMove=moves[mi]; }
        }
        return bestMove;
    }

    int bestMove=moves[0]; double bestScore=-1e9;
    for (int mi=0;mi<nm;mi++) {
        Coord nh=h+DIRS[moves[mi]];
        double sc=0;

        bool willEat = nh.inBounds() && st.apples.tstC(nh);
        if (willEat) {

            int deficit = appleEatDeficit(nh, snLen, st.walls, blocked);
            if (deficit > 0) {

                sc += P.TRAP_APPLE_EAT_PEN * deficit;
                if (deficit >= snLen)
                    sc += P.TRAP_APPLE_HARD_PEN;
            } else {

                sc += P.GREEDY_APPLE_IMMEDIATE;
            }

            int heightH = max(1, H - 1);
            sc += P.GREEDY_APPLE_HEIGHT_BONUS * (heightH - nh.y) / (double)heightH;
        }

        if (!willEat) {
            int bestMD = INT_MAX;
            int bestAppleY = H;
            for (int y=0;y<H;y++) for (int x=0;x<W;x++) {
                if (!st.apples.tstC({x,y})) continue;
                int d = nh.inBounds() ? nh.manhattan({x,y}) : 100;
                if (d < bestMD) { bestMD = d; bestAppleY = y; }
                else if (d == bestMD && y < bestAppleY) bestAppleY = y;
            }
            if (bestMD < INT_MAX) {

                double distPenMult = (st.turn < 15) ? 0.4 : 1.0;
                sc += bestMD * P.GREEDY_APPLE_DIST * distPenMult;

                int heightH = max(1, H - 1);
                sc += P.GREEDY_APPLE_HEIGHT_BONUS * (heightH - bestAppleY) / (double)heightH * 0.4;
            }
        }

        if (nh.inBounds()) {
            if (cellSupported(nh.x,nh.y,st.walls,st.apples,blocked)) sc+=P.GREEDY_SUPPORT;
            if (moves[mi]==DIR_UP) sc+=P.GREEDY_UP_PEN;
            if (smallMap) sc+=edgePenalty(nh)*0.3;
        }
        if (nh.inBounds()&&blocked.tstC(nh)) sc+=P.GREEDY_BLOCKED_PEN;
        for (int j=0;j<st.nSnakes;j++) {
            if (j==si||!st.snakes[j].alive) continue;
            Coord oh=st.snakes[j].head();
            if (!oh.inBounds()||!nh.inBounds()) continue;
            int hd=nh.manhattan(oh);
            if (hd<=1 && st.snakes[si].len()<=st.snakes[j].len())
                sc+=(smallMap?P.GREEDY_HEAD_COLL_PEN_SMALL:P.GREEDY_HEAD_COLL_PEN);
            if (hd<=1 && st.snakes[si].len()>st.snakes[j].len()+1)
                sc+=P.GREEDY_HEAD_COLL_BONUS;
        }
        if (smallMap && nh.inBounds()) {
            BitBoard tmpBlk=blocked; tmpBlk.setC(h);
            int reach=floodFillCount(nh,st.walls,tmpBlk);
            if (reach<st.snakes[si].len())    sc+=P.GREEDY_TRAPPED_PEN;
            else if (reach<st.snakes[si].len()*2) sc+=P.GREEDY_TRAPPED_MILD_PEN;
        }
        if (sc>bestScore) { bestScore=sc; bestMove=moves[mi]; }
    }
    return bestMove;
}

int smartOppMove(const State& st, int si, const BitBoard& blocked) {
    int oppOwner = st.snakes[si].owner;
    int moves[4];
    int nm=validMovesSafe(st,si,blocked,moves);
    if (nm<=1) return (nm==1)?moves[0]:st.snakes[si].facing();
    int bestMove=moves[0]; double bestScore=-1e9;
    for (int mi=0;mi<nm;mi++) {
        State simSt=st;
        int allMoves[MAX_SNAKES]={};
        for (int i=0;i<st.nSnakes;i++) allMoves[i]=st.snakes[i].facing();
        allMoves[si]=moves[mi];
        simulate(simSt,allMoves);
        double sc=evaluate(simSt,oppOwner,true);
        if (sc>bestScore) { bestScore=sc; bestMove=moves[mi]; }
    }
    return bestMove;
}

int smarterOppMove(const State& st, int si, const BitBoard& blocked,
                   const int myMoves[], const int myIdxArr[], int nMy) {
    int moves[4];
    int nm = validMovesSafe(st, si, blocked, moves);
    if (nm <= 1) return (nm == 1) ? moves[0] : st.snakes[si].facing();

    int bestMove = moves[0]; double bestScore = -1e9;
    int oppOwner = st.snakes[si].owner;
    for (int mi = 0; mi < nm; mi++) {
        State simSt = st;
        int allMoves[MAX_SNAKES] = {};
        for (int i = 0; i < st.nSnakes; i++) allMoves[i] = st.snakes[i].facing();

        for (int m = 0; m < nMy; m++) allMoves[myIdxArr[m]] = myMoves[m];
        allMoves[si] = moves[mi];
        simulate(simSt, allMoves);
        double sc = evaluate(simSt, oppOwner, true);
        if (sc > bestScore) { bestScore = sc; bestMove = moves[mi]; }
    }
    return bestMove;
}

struct BeamNode {
    State state;
    int   firstMoves[MAX_SNAKES];
    double score;
};

static const int MAX_BEAM_POOL = 340;
static BeamNode beamPoolA[MAX_BEAM_POOL];
static BeamNode beamPoolB[MAX_BEAM_POOL];
static int      beamIdxA[MAX_BEAM_POOL];
static int      beamIdxB[MAX_BEAM_POOL];
static int      beamSzA = 0;
static int      beamSzB = 0;

vector<int> beamSearch(const State& initSt, int myOwner, int64_t budgetMs,
                       double stallUrgency, const map<int,deque<Coord>>& hist) {
    auto t0 = Clock::now();
    beamSzA = beamSzB = 0;

    int myIdx[MAX_SNAKES], oppIdx[MAX_SNAKES];
    int nMy=0, nOpp=0;
    for (int i=0;i<initSt.nSnakes;i++) {
        if (!initSt.snakes[i].alive) continue;
        if (initSt.snakes[i].owner==myOwner) myIdx[nMy++]=i;
        else                                  oppIdx[nOpp++]=i;
    }
    if (nMy==0) return {};

    int totalAlive=nMy+nOpp;
    int beamWidth, beamDepthMax, comboLimit;
    if      (tinyMap)       { beamWidth=P.BEAM_WIDTH_TINY;  beamDepthMax=P.BEAM_DEPTH_TINY;  comboLimit=P.BEAM_COMBO_TINY; }
    else if (smallMap)      { beamWidth=P.BEAM_WIDTH_SMALL; beamDepthMax=P.BEAM_DEPTH_SMALL; comboLimit=P.BEAM_COMBO_SMALL; }
    else if (totalAlive<=4) { beamWidth=P.BEAM_WIDTH_FEW;   beamDepthMax=P.BEAM_DEPTH_FEW;   comboLimit=P.BEAM_COMBO_FEW; }
    else if (totalAlive<=6) { beamWidth=P.BEAM_WIDTH_MED;   beamDepthMax=P.BEAM_DEPTH_MED;   comboLimit=P.BEAM_COMBO_MED; }
    else                    { beamWidth=P.BEAM_WIDTH_MANY;  beamDepthMax=P.BEAM_DEPTH_MANY;  comboLimit=P.BEAM_COMBO_MANY; }

    beamWidth = min(beamWidth, MAX_BEAM_POOL);

    BitBoard initBlocked = initSt.walls | initSt.bodyBoardConst();

    Coord bsAppleList[200];
    int   bsNApples = 0;
    for (int y=0;y<H&&bsNApples<200;y++)
        for (int x=0;x<W&&bsNApples<200;x++)
            if (initSt.apples.tstC({x,y})) bsAppleList[bsNApples++]={x,y};

    int bsAppleAssign[MAX_SNAKES];
    int bsPreferDir  [MAX_SNAKES];
    fill(bsAppleAssign, bsAppleAssign+MAX_SNAKES, -1);
    fill(bsPreferDir,   bsPreferDir  +MAX_SNAKES, -1);

    if (bsNApples > 0) {
        assignApplesToSnakes(initSt, myOwner, bsAppleList, bsNApples, bsAppleAssign);
        for (int mi = 0; mi < nMy; mi++) {
            int si = myIdx[mi];
            int ai = bsAppleAssign[si];
            if (ai >= 0) {
                int d = bfsDir(initSt.snakes[si].head(), bsAppleList[ai],
                               initSt.walls, initBlocked);
                bsPreferDir[mi] = d;
            }
        }
    }
    vector<vector<int>> combos = {{}};
    for (int mi=0;mi<nMy;mi++) {
        int moves[4];
        int nm=validMovesSafe(initSt,myIdx[mi],initBlocked,moves);

        int sortedMoves[4];
        {

            pair<int,int> ranked[4];
            for (int j=0;j<nm;j++) {
                Coord nh=initSt.snakes[myIdx[mi]].head()+DIRS[moves[j]];
                int sc=0;
                if (nh.inBounds()&&initSt.apples.tstC(nh)) sc=10000;
                else if (nh.inBounds()&&bsNApples>0) {
                    int minD=INT_MAX;
                    for (int a=0;a<bsNApples;a++) minD=min(minD,nh.manhattan(bsAppleList[a]));
                    if (minD<INT_MAX) sc=1000-minD;
                }
                ranked[j]={-sc,moves[j]};
            }

            for (int a=1;a<nm;a++) {
                auto key=ranked[a];
                int b=a-1;
                while (b>=0 && ranked[b].first > key.first) { ranked[b+1]=ranked[b]; b--; }
                ranked[b+1]=key;
            }
            for (int j=0;j<nm;j++) sortedMoves[j]=ranked[j].second;
        }
        vector<vector<int>> next;
        for (auto& c : combos)
            for (int j=0;j<nm;j++) { auto nc=c; nc.push_back(sortedMoves[j]); next.push_back(nc); }
        combos=next;
    }

    if ((int)combos.size() > MAX_BEAM_POOL) {

        vector<pair<double,int>> comboScores(combos.size());
        for (int ci=0;ci<(int)combos.size();ci++) {
            double sc=0;
            for (int mi=0;mi<nMy&&mi<(int)combos[ci].size();mi++) {
                int si=myIdx[mi];
                Coord nh=initSt.snakes[si].head()+DIRS[combos[ci][mi]];
                if (nh.inBounds()&&initSt.apples.tstC(nh)) sc+=1000;
                if (nh.inBounds()&&!initBlocked.tstC(nh))  sc+=20;
                if (nh.inBounds()&&cellSupported(nh.x,nh.y,initSt.walls,initSt.apples,initBlocked)) sc+=5;

                for (int j=0;j<initSt.nSnakes;j++) {
                    if (!initSt.snakes[j].alive||initSt.snakes[j].owner==myOwner) continue;
                    Coord oh=initSt.snakes[j].head(); if (!oh.inBounds()||!nh.inBounds()) continue;
                    if (nh.manhattan(oh)<=1 && initSt.snakes[si].len()<=initSt.snakes[j].len())
                        sc-=600;
                }
            }
            comboScores[ci]={sc,ci};
        }
        sort(comboScores.begin(),comboScores.end(),[](auto& a,auto& b){return a.first>b.first;});
        vector<vector<int>> pruned; pruned.reserve(MAX_BEAM_POOL);
        for (int ci=0;ci<MAX_BEAM_POOL;ci++) pruned.push_back(combos[comboScores[ci].second]);
        combos=pruned;
    }
    int oppComboLimit=smallMap?P.OPP_COMBO_LIMIT_SMALL:P.OPP_COMBO_LIMIT;
    vector<vector<int>> oppCombos = {{}};
    for (int oi=0;oi<nOpp;oi++) {
        int moves[4];
        int nm=validMovesSafe(initSt,oppIdx[oi],initBlocked,moves);
        vector<vector<int>> next;
        for (auto& c : oppCombos)
            for (int j=0;j<nm;j++) { auto nc=c; nc.push_back(moves[j]); next.push_back(nc); }
        oppCombos=next;
        if ((int)oppCombos.size()>oppComboLimit) break;
    }
    if ((int)oppCombos.size()>oppComboLimit) {
        bool useSmart=(nOpp<=2 && elapsed(t0)<budgetMs/3) || smallMap;
        int defaultOppMoves[MAX_SNAKES];
        for (int oi=0;oi<nOpp;oi++)
            defaultOppMoves[oi]=useSmart ? smartOppMove(initSt,oppIdx[oi],initBlocked)
                                         : greedyMove(initSt,oppIdx[oi],&initBlocked);
        vector<int> defaultCombo;
        for (int oi=0;oi<nOpp;oi++) defaultCombo.push_back(defaultOppMoves[oi]);
        vector<vector<int>> filtered; filtered.push_back(defaultCombo);
        for (auto& oc : oppCombos) {
            if ((int)filtered.size()>=oppComboLimit) break;
            if (oc!=defaultCombo) filtered.push_back(oc);
        }
        oppCombos=filtered;
    }

    bool useFullEval=(int)combos.size()*(int)oppCombos.size()<=300||smallMap;
    bool useMinimax =(int)oppCombos.size()>1 && elapsed(t0)<budgetMs-20;
    constexpr int64_t TIMEOUT_MARGIN=6;   // was 5 — extra 1ms for cout.flush()

    int greedyOppMoves[MAX_SNAKES]={};
    for (int oi=0;oi<nOpp;oi++)
        greedyOppMoves[oi]=greedyMove(initSt,oppIdx[oi],&initBlocked);

    for (auto& combo : combos) {
        if (elapsed(t0)>budgetMs-TIMEOUT_MARGIN) break;
        if (beamSzA>=MAX_BEAM_POOL) break;

        int allMovesGreedy[MAX_SNAKES]={};
        for (int i=0;i<initSt.nSnakes;i++) allMovesGreedy[i]=-1;
        for (int i=0;i<nMy;i++)  allMovesGreedy[myIdx[i]]=combo[i];
        for (int oi=0;oi<nOpp;oi++) allMovesGreedy[oppIdx[oi]]=greedyOppMoves[oi];

        BeamNode& node = beamPoolA[beamSzA];
        node.state = initSt;
        simulate(node.state, allMovesGreedy);

        double worstScore=1e9;
        if (useMinimax) {

            double greedyScore = evaluate(node.state, myOwner, !useFullEval, &initSt, stallUrgency, &hist);
            worstScore = greedyScore;

            for (auto& oppCombo : oppCombos) {
                if (elapsed(t0)>budgetMs-TIMEOUT_MARGIN) break;

                bool isGreedy=true;
                for (int oi=0;oi<nOpp&&oi<(int)oppCombo.size();oi++)
                    if (oppCombo[oi]!=greedyOppMoves[oi]) { isGreedy=false; break; }
                if (isGreedy) continue;

                State simSt=initSt;
                int allMoves[MAX_SNAKES]={};
                for (int i=0;i<initSt.nSnakes;i++) allMoves[i]=-1;
                for (int i=0;i<nMy;i++) allMoves[myIdx[i]]=combo[i];
                for (int oi=0;oi<nOpp&&oi<(int)oppCombo.size();oi++)
                    allMoves[oppIdx[oi]]=oppCombo[oi];
                simulate(simSt,allMoves);
                double sc=evaluate(simSt,myOwner,!useFullEval,&initSt,stallUrgency,&hist);
                worstScore=min(worstScore,sc);
            }
        } else {
            worstScore=evaluate(node.state,myOwner,!useFullEval,&initSt,stallUrgency,&hist);
        }

        for (int i=0;i<nMy;i++) node.firstMoves[myIdx[i]]=combo[i];
        node.score = worstScore;
        beamIdxA[beamSzA] = beamSzA;
        beamSzA++;
    }

    sort(beamIdxA, beamIdxA+beamSzA, [](int a, int b){
        return beamPoolA[a].score > beamPoolA[b].score;
    });
    if (beamSzA > beamWidth) beamSzA = beamWidth;

    if (!useFullEval && elapsed(t0) < budgetMs-25) {
        int reEvalCount = min(beamSzA, P.REEVAL_TOP_K);
        for (int i=0;i<reEvalCount;i++) {
            BeamNode& n = beamPoolA[beamIdxA[i]];
            n.score = evaluate(n.state, myOwner, false, &initSt, stallUrgency, &hist);
        }
        sort(beamIdxA, beamIdxA+beamSzA, [](int a, int b){
            return beamPoolA[a].score > beamPoolA[b].score;
        });
    }

    for (int depth=1; depth<beamDepthMax; depth++) {
        if (elapsed(t0)>budgetMs-TIMEOUT_MARGIN) break;
        beamSzB=0;
        bool timeout=false;
        int evalCount=0;

        for (int bi=0; bi<beamSzA && !timeout; bi++) {
            const BeamNode& node = beamPoolA[beamIdxA[bi]];
            BitBoard nodeBlocked = node.state.walls | node.state.bodyBoardConst();

            int cMyIdx[MAX_SNAKES], cOppIdx[MAX_SNAKES];
            int cNMy=0, cNOpp=0;
            for (int i=0;i<node.state.nSnakes;i++) {
                if (!node.state.snakes[i].alive) continue;
                if (node.state.snakes[i].owner==myOwner) cMyIdx[cNMy++]=i;
                else                                      cOppIdx[cNOpp++]=i;
            }
            if (cNMy==0) continue;

            vector<vector<int>> cCombos={{}};
            for (int mi=0;mi<cNMy;mi++) {
                int mv[4];
                int nm=validMovesSafe(node.state,cMyIdx[mi],nodeBlocked,mv);

                if (gAppleRich && bsNApples > 0) {

                    int si = cMyIdx[mi];
                    Coord h = node.state.snakes[si].head();
                    int prefD = -1;
                    if (h.inBounds()) {
                        int bestScore = INT_MAX;
                        for (int j=0;j<nm;j++) {
                            Coord nh = h + DIRS[mv[j]];
                            if (!nh.inBounds()) continue;
                            if (node.state.apples.tstC(nh)) { prefD=mv[j]; bestScore=-1; break; }
                            int minD = INT_MAX;
                            for (int a=0;a<bsNApples;a++) minD=min(minD,nh.manhattan(bsAppleList[a]));
                            if (minD < bestScore) { bestScore=minD; prefD=mv[j]; }
                        }
                    }
                    if (prefD >= 0) {
                        int ordered[4]; int nOrdered=0;
                        for (int j=0;j<nm;j++) if (mv[j]==prefD) { ordered[nOrdered++]=mv[j]; break; }
                        if (nOrdered==0 && nm>0) ordered[nOrdered++]=mv[0];
                        // Raised from 2→3: allows more coordinated multi-snake apple routing
                        for (int j=0;j<nm && nOrdered<3;j++) if (mv[j]!=prefD) ordered[nOrdered++]=mv[j];
                        vector<vector<int>> next;
                        for (auto& c : cCombos)
                            for (int j=0;j<nOrdered;j++) { auto nc=c; nc.push_back(ordered[j]); next.push_back(nc); }
                        cCombos=next;
                    } else {
                        vector<vector<int>> next;
                        for (auto& c : cCombos)
                            for (int j=0;j<nm;j++) { auto nc=c; nc.push_back(mv[j]); next.push_back(nc); }
                        cCombos=next;
                    }
                } else {
                    vector<vector<int>> next;
                    for (auto& c : cCombos)
                        for (int j=0;j<nm;j++) { auto nc=c; nc.push_back(mv[j]); next.push_back(nc); }
                    cCombos=next;
                }
                if ((int)cCombos.size()>comboLimit*2) break;
            }

            if ((int)cCombos.size()>comboLimit) {
                vector<pair<double,int>> scored(cCombos.size());
                for (int ci=0;ci<(int)cCombos.size();ci++) {
                    double sc=0;
                    for (int mi=0;mi<cNMy&&mi<(int)cCombos[ci].size();mi++) {
                        Coord nh=node.state.snakes[cMyIdx[mi]].head()+DIRS[cCombos[ci][mi]];
                        if (nh.inBounds()&&node.state.apples.tstC(nh)) {

                            int snLen = node.state.snakes[cMyIdx[mi]].len();
                            int deficit = appleEatDeficit(nh, snLen,
                                                          node.state.walls, nodeBlocked);
                            if (deficit > 0) {
                                sc += P.TRAP_APPLE_COMBO_PEN;
                                if (deficit >= snLen)
                                    sc += P.TRAP_APPLE_HARD_PEN * 0.5;
                            } else {
                                sc += 1000;

                                if (H > 1)
                                    sc += 40.0 * (H - 1 - nh.y) / (double)(H - 1);
                            }
                        } else {
                            if (nh.inBounds()&&!nodeBlocked.tstC(nh)) sc+=10;
                            if (nh.inBounds()&&cellSupported(nh.x,nh.y,node.state.walls,node.state.apples,nodeBlocked)) sc+=5;

                            if (nh.inBounds() && bsNApples > 0) {

                                int bestY = H;
                                for (int a=0;a<bsNApples;a++)
                                    if (bsAppleList[a].y < bestY) bestY = bsAppleList[a].y;
                                if (nh.y < node.state.snakes[cMyIdx[mi]].head().y)
                                    sc += 3;
                            }
                        }
                    }
                    scored[ci]={sc,ci};
                }
                sort(scored.begin(),scored.end(),[](const pair<double,int>& a,const pair<double,int>& b){ return a.first>b.first; });
                vector<vector<int>> best; best.reserve(comboLimit);
                for (int ci=0;ci<comboLimit;ci++) best.push_back(cCombos[scored[ci].second]);
                cCombos=best;
            }

            int cOppMv[MAX_SNAKES];

            bool useSmarter = (elapsed(t0) < budgetMs * 2 / 3) && (cNOpp <= 2);
            for (int i = 0; i < cNOpp; i++) {
                if (useSmarter) {

                    int preferredMoves[MAX_SNAKES] = {};
                    for (int m = 0; m < cNMy; m++)
                        preferredMoves[m] = node.state.snakes[cMyIdx[m]].facing();
                    cOppMv[i] = smarterOppMove(node.state, cOppIdx[i], nodeBlocked,
                                               preferredMoves, cMyIdx, cNMy);
                } else {
                    cOppMv[i] = greedyMove(node.state, cOppIdx[i]);
                }
            }

            for (auto& combo : cCombos) {
                if (beamSzB>=MAX_BEAM_POOL) { timeout=true; break; }
                if ((evalCount++&3)==0 && elapsed(t0)>budgetMs-TIMEOUT_MARGIN)
                    { timeout=true; break; }

                BeamNode& child=beamPoolB[beamSzB];
                child.state=node.state;
                memcpy(child.firstMoves,node.firstMoves,sizeof(node.firstMoves));

                int allMv[MAX_SNAKES]={};
                for (int i=0;i<child.state.nSnakes;i++) allMv[i]=-1;
                for (int i=0;i<cNMy&&i<(int)combo.size();i++) allMv[cMyIdx[i]]=combo[i];
                for (int i=0;i<cNOpp;i++) allMv[cOppIdx[i]]=cOppMv[i];

                simulate(child.state,allMv);
                child.score=evaluate(child.state,myOwner,true,&initSt,stallUrgency,&hist);
                beamIdxB[beamSzB]=beamSzB;
                beamSzB++;
            }
        }

        if (beamSzB==0) break;

        sort(beamIdxB, beamIdxB+beamSzB, [](int a, int b){
            return beamPoolB[a].score > beamPoolB[b].score;
        });
        if (beamSzB>beamWidth) beamSzB=beamWidth;

        int newSzA = beamSzB;
        for (int i=0;i<newSzA;i++) {
            beamPoolA[i] = beamPoolB[beamIdxB[i]];
            beamIdxA[i]  = i;
        }
        beamSzA = newSzA;
    }

    if (beamSzA==0) {

        vector<int> r;
        for (int i=0;i<nMy;i++) r.push_back(greedyMove(initSt,myIdx[i]));
        return r;
    }

    if (smallMap && beamSzA>1) {
        for (int bi=0;bi<beamSzA;bi++) {
            BeamNode& node=beamPoolA[beamIdxA[bi]];
            bool trapped=false;
            for (int i=0;i<initSt.nSnakes;i++) {
                if (!node.state.snakes[i].alive||node.state.snakes[i].owner!=myOwner) continue;
                Coord h=node.state.snakes[i].head();
                if (!h.inBounds()) { trapped=true; break; }
                BitBoard nb=node.state.walls|node.state.bodyBoardConst();
                int reach=floodFillCount(h,node.state.walls,nb);
                if (reach<node.state.snakes[i].len()) { trapped=true; break; }
            }
            if (trapped) node.score+=P.BEAM_TRAPPED_PEN;
        }
        sort(beamIdxA, beamIdxA+beamSzA, [](int a, int b){
            return beamPoolA[a].score > beamPoolA[b].score;
        });
    }

    const BeamNode& best = beamPoolA[beamIdxA[0]];
    vector<int> result;
    for (int i=0;i<nMy;i++) result.push_back(best.firstMoves[myIdx[i]]);
    return result;
}

vector<Coord> parseBody(const string& s) {
    vector<Coord> r;
    string c=s;
    for (char& ch : c) if (ch==':'||ch==';') ch=' ';
    istringstream ss(c); string t;
    while (ss>>t) {
        auto cm=t.find(',');
        if (cm==string::npos) continue;
        r.push_back({stoi(t.substr(0,cm)), stoi(t.substr(cm+1))});
    }
    return r;
}

void printMap(const State& st, ostream& os=cerr) {
    char grid[MAX_H][MAX_W];
    for (int y=0;y<H;y++) for (int x=0;x<W;x++) {
        if (st.walls.tstC({x,y}))  grid[y][x]='#';
        else if (st.apples.tstC({x,y})) grid[y][x]='*';
        else grid[y][x]='.';
    }
    for (int i=st.nSnakes-1;i>=0;i--) {
        const Snake& sn=st.snakes[i]; if (!sn.alive) continue;
        char bodyChar=(sn.owner==0)?('a'+(sn.id%8)):('A'+(sn.id%8));
        char headChar=(sn.id>=0&&sn.id<=9)?('0'+sn.id):'?';
        for (int k=sn.len()-1;k>=0;k--) {
            Coord c=sn.body[k];
            if (c.x>=0&&c.x<W&&c.y>=0&&c.y<H)
                grid[c.y][c.x]=(k==0)?headChar:bodyChar;
        }
    }
    os << "+"<<string(W,'-')<<"+"<<endl;
    for (int y=0;y<H;y++) { os<<"|"; for (int x=0;x<W;x++) os<<grid[y][x]; os<<"|"<<endl; }
    os << "+"<<string(W,'-')<<"+"<<endl;
    os<<"Mine:"; for (int i=0;i<st.nSnakes;i++) if(st.snakes[i].alive&&st.snakes[i].owner==0) os<<" "<<st.snakes[i].id<<"("<<st.snakes[i].len()<<")";
    os<<" | Opp:"; for (int i=0;i<st.nSnakes;i++) if(st.snakes[i].alive&&st.snakes[i].owner==1) os<<" "<<st.snakes[i].id<<"("<<st.snakes[i].len()<<")";
    os<<endl;
}

int main(int argc, char* argv[]) {
    for (int i=1;i<argc;i++) {
        string arg=argv[i];
        if (arg=="--config"&&i+1<argc) loadParamsJson(argv[++i]);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int myId, spp;
    cin>>myId; cin.ignore();
    cin>>W;    cin.ignore();
    cin>>H;    cin.ignore();

    totalCells = W*H;
    smallMap   = (W<=20&&H<=15)||totalCells<=250;
    tinyMap    = (W<=10&&H<=10)||totalCells<=100;

    BitBoard walls;
    for (int y=0;y<H;y++) {
        string row; getline(cin,row);
        for (int x=0;x<(int)row.size()&&x<W;x++)
            if (row[x]=='#') walls.setC({x,y});
    }

    cin>>spp; cin.ignore();
    vector<int> myIds(spp), oppIds(spp);
    for (int i=0;i<spp;i++) { cin>>myIds[i];  cin.ignore(); }
    for (int i=0;i<spp;i++) { cin>>oppIds[i]; cin.ignore(); }

    map<int,int> id2idx, id2owner;
    int idx=0;
    for (int id : myIds)  { id2idx[id]=idx; id2owner[id]=0; idx++; }
    for (int id : oppIds) { id2idx[id]=idx; id2owner[id]=1; idx++; }
    int totalSnakes=idx;

    int turn=0, previousMyScore=-1, stallCounter=0;
    map<int,deque<Coord>> hist;

    if (smallMap) cerr<<"SMALL MAP MODE ("<<W<<"x"<<H<<")"<<endl;
    if (tinyMap)  cerr<<"TINY MAP MODE ("<<W<<"x"<<H<<")"<<endl;
    cerr<<"[SnakeBody ring buffer, BODY_CAP="<<BODY_CAP<<"]"<<endl;

    while (true) {
        turn++;

        int nrg; cin>>nrg; cin.ignore();
        gAppleCount = nrg;
        gAppleRich  = (nrg >= P.APPLE_RICH_THRESHOLD);
        BitBoard apples;
        for (int i=0;i<nrg;i++) {
            int x,y; cin>>x>>y; cin.ignore();
            apples.setC({x,y});
        }

        int nb; cin>>nb; cin.ignore();
        State st;
        st.walls=walls; st.apples=apples;
        st.nSnakes=totalSnakes; st.turn=turn; st.bodyDirty=true;
        for (int i=0;i<totalSnakes;i++) { st.snakes[i].alive=false; st.snakes[i].id=-1; st.snakes[i].owner=-1; }

        set<int> aliveIds;
        for (int i=0;i<nb;i++) {
            int sid; string bodyStr;
            cin>>sid>>bodyStr; cin.ignore();
            if (!id2idx.count(sid)) continue;
            int si=id2idx[sid];
            st.snakes[si].id=sid; st.snakes[si].owner=id2owner[sid];
            auto body=parseBody(bodyStr);
            if (body.empty()) continue;
            st.snakes[si].alive=true;

            st.snakes[si].body.clear();
            for (auto& c : body) st.snakes[si].body.push_back(c);
            aliveIds.insert(sid);
        }

        auto t0=Clock::now();   // TIMER STARTS HERE, after all I/O

        for (int i=0;i<totalSnakes;i++) {
            if (st.snakes[i].alive && st.snakes[i].owner==0) {
                hist[st.snakes[i].id].push_back(st.snakes[i].head());

                if (hist[st.snakes[i].id].size()>15) hist[st.snakes[i].id].pop_front();
            } else {
                hist.erase(st.snakes[i].id);
            }
        }

        {
            int currentMyScore = st.scoreFor(0);  // FIXED: my snakes are always owner=0
            if (currentMyScore > previousMyScore) {
                stallCounter = 0;            // ate something
            } else if (currentMyScore < previousMyScore) {
                stallCounter = 0;            // lost a head — volatile state, don't panic
            } else if (turn > 1) {
                stallCounter++;
            }
            previousMyScore = currentMyScore;
        }

        // Urgency curve re-tuned for override threshold of 15 (was 30).
        // Now urgency kicks in much earlier, giving beam search a chance to escape before override fires.
        double stallUrgency=1.0;
        if      (stallCounter>=13) stallUrgency=2.0;  // was >=25 → 2.5 (override handles >=15)
        else if (stallCounter>=8)  stallUrgency=1.7;  // was >=15 → 2.0
        else if (stallCounter>=4)  stallUrgency=1.4;  // was >=8  → 1.6
        else if (stallCounter>=2)  stallUrgency=1.2;  // was >=3  → 1.3

        int64_t budget=(turn==1)?980:47;  // 3ms margin for overhead

        cerr<<"\n=== T"<<turn<<" "<<W<<"x"<<H;
        int myS=st.scoreFor(0), opS=st.scoreFor(1), delta=myS-opS;
        cerr<<" "<<myS<<"v"<<opS<<" ("; if(delta>0) cerr<<"+"; cerr<<delta<<")";
        cerr<<" E="<<nrg<<(gAppleRich?" [APPLE-RICH]":"");
        int turnsLeft=200-turn;
        string phase=(turnsLeft>140)?"EXPAND":((turnsLeft>60)?"CONTROL":"CONSERVE");
        if (delta<-2&&turnsLeft<=80) phase="AGGRESS";
        cerr<<" "<<phase<<" | STALL="<<stallCounter<<" (x"<<stallUrgency<<") ==="<<endl;

        // Lower threshold: engage at 15 instead of 30
        if (stallCounter > 15) {
            cerr << "  [STALL OVERRIDE] escape (stall=" << stallCounter << ")" << endl;
            BitBoard blocked = st.walls | st.bodyBoardConst();
            string out;

            for (int i = 0; i < spp; i++) {
                int sid = myIds[i];
                if (!aliveIds.count(sid)) continue;
                int si = id2idx[sid];
                if (!st.snakes[si].alive) continue;

                // Strategy 1: find closest reachable apple using weighted BFS
                int dir = -1;
                {
                    Coord h = st.snakes[si].head();
                    int bestDist = INT_MAX;
                    Coord bestApple(-1, -1);
                    // Prefer apples that are supported (won't cause gravity fall to miss)
                    for (int y = 0; y < H; y++) for (int x = 0; x < W; x++) {
                        if (!st.apples.tstC({x,y})) continue;
                        int md = h.manhattan({x,y});
                        // Weight by height (lower apples harder to reach via gravity)
                        int weighted = md * 2 + (H - 1 - y);
                        if (weighted < bestDist) { bestDist = weighted; bestApple = {x,y}; }
                    }
                    if (bestApple.inBounds())
                        dir = bfsDir(h, bestApple, st.walls, blocked);
                }

                // Strategy 2: fallback to greedy (which uses BFS internally)
                if (dir < 0)
                    dir = greedyMove(st, si, &blocked);

                // Strategy 3: pick the move with most reachable cells (survival)
                if (dir < 0) {
                    int safeMoves[4]; int nm = validMovesSafe(st, si, blocked, safeMoves);
                    int bestReach = -1;
                    for (int mi = 0; mi < nm; mi++) {
                        Coord nh = st.snakes[si].head() + DIRS[safeMoves[mi]];
                        if (!nh.inBounds()) continue;
                        BitBoard tmpBlk = blocked; tmpBlk.setC(st.snakes[si].head());
                        int r = floodFillCount(nh, st.walls, tmpBlk);
                        if (r > bestReach) { bestReach = r; dir = safeMoves[mi]; }
                    }
                }
                if (dir < 0 || dir > 3) dir = st.snakes[si].facing();

                if (!out.empty()) out += ";";
                out += to_string(sid) + " " + DIR_NAMES[dir];
            }

            cout << (out.empty() ? "WAIT" : out) << "\n";
            cout.flush();
            cerr << "  => " << out << " (stall override, " << elapsed(t0) << "ms)" << endl;
            continue;
        }

        vector<int> bestMoves=beamSearch(st,0,budget,stallUrgency,hist);

        string out;
        int mi=0;
        for (int i=0;i<spp;i++) {
            int sid=myIds[i];
            if (!aliveIds.count(sid)) continue;
            int dir=(mi<(int)bestMoves.size())?bestMoves[mi]:0;
            mi++;
            if (dir<0||dir>3) dir=0;
            if (!out.empty()) out+=";";
            out+=to_string(sid)+" "+DIR_NAMES[dir];
        }
        // FLUSH STDOUT FIRST — judge clock stops here
        cout<<(out.empty()?"WAIT":out)<<"\n";
        cout.flush();
        // Debug logging after — no timing impact
        printMap(st);
        cerr<<"  => "<<out<<" ("<<elapsed(t0)<<"ms)"<<endl;
    }
}
