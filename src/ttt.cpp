#include <cstdlib>
#include <malloc.h>
#include <cstdio>
#include <cstring>

#define MAX_N 400

int inputTail[MAX_N];
int inputHead[MAX_N];
char inputJ[MAX_N];
int inputV[MAX_N];
int cc;

int way_id;

struct eNode
{
    int u, v;
    int nu, nv; // nu : next edge of u
    char val;
}enodes[MAX_N];

struct vNode
{
    int val;
    int in_edge, out_edge;
} vnodes[MAX_N];

struct path
{
    int vs[MAX_N];
    int es[MAX_N];
    int len;
} paths[MAX_N];

path cur_path;
bool hasVisitedE[MAX_N];

bool isNewNode(int node, int cnt)
{
    for (int i = 0; i < cnt; i++) {
        if (inputV[i] == node) return false;
    }
    inputV[cnt] = node;
    return true;
}

int findVtxIdx(int val, int max_i)
{
    for (int i = 0; i < max_i; i++) {
        if (vnodes[i].val == val) return i;
    }
    return -1;
}

bool hasTpn(int x)
{
    int max_id = cur_path.len;
    for (int i = 0; i < max_id; i++) {
        if (cur_path.vs[i] == x) 
            return true;
    }
    return false;
}

bool shouldAdd()
{
    for (int i = 0; i < cur_path.len; i++) {
        if (!hasVisitedE[cur_path.es[i]]) {
            return true;
        }
    }
    return false;
}

void dfs(int cur_n)
{
    int p;
    int cur_len = cur_path.len;
    cur_path.vs[cur_len] = cur_n;
    if (!hasTpn(cur_n)) {
        p = vnodes[cur_n].out_edge;
        while (p != -1) {
            if (enodes[p].val == 'F') {
                cur_path.es[cur_len] = p;
                cur_path.len = cur_len + 1;
                int tpn = enodes[p].v;
                dfs(tpn);
                break;
            }
            p = enodes[p].nu;
        }
        p = vnodes[cur_n].out_edge;
        while (p != -1) {
            if (enodes[p].val == 'T') {
                cur_path.es[cur_len] = p;
                cur_path.len = cur_len + 1;
                int tpn = enodes[p].v;
                dfs(tpn);
                break;
            }
            p = enodes[p].nu;
        }
        p = vnodes[cur_n].out_edge;
        while (p != -1) {
            if (enodes[p].val == 'N') {
                cur_path.es[cur_len] = p;
                cur_path.len = cur_len + 1;
                int tpn = enodes[p].v;
                dfs(tpn);
                break;
            }
            p = enodes[p].nu;
        }
    }
    //
    if (shouldAdd()) {
        for (int i = 0; i < cur_len; i++) {
            hasVisitedE[cur_path.es[i]] = true;
            paths[way_id].es[i] = cur_path.es[i];
            paths[way_id].vs[i] = cur_path.vs[i];
            paths[way_id].len = cur_len;
        }
        paths[way_id].vs[cur_len] = cur_path.vs[cur_len];
        paths[way_id].len++;
        way_id++;
    }
}

bool cmp(int j, int k)
{
    if (paths[j].len < paths[k].len) return true;
    if (paths[j].len > paths[k].len) return false;
    int tplen = paths[j].len;
    for (int i = 0; i < tplen; i++) {
        if (vnodes[paths[j].vs[i]].val < vnodes[paths[k].vs[i]].val) return true;
        if (vnodes[paths[j].vs[i]].val > vnodes[paths[k].vs[i]].val) return false;
    }
    printf("j=%d, k=%d\n", j, k);
    return true;
}

int main()
{
    char s[80];
    bool ext = false;
    int nodeCnt = 0;
    int edgeCnt = 0;
    cc = 0;
    scanf("%s", s);
    if (strcmp(s, "END") == 0) return 0;
    //
    int tmp;
    sscanf(s, "%d", &tmp);
    inputV[nodeCnt++] = tmp;
    while (1) {
        scanf("%s", s);
        if (strcmp(s, "EXT") == 0) {
            ext = true;
            break;
        }
        if (strcmp(s, "END") == 0) break;
        // add one line
        int t_head, t_tail;
        char t_judge;
        sscanf(s, "%d->%d,%c", &t_head, &t_tail, &t_judge);
        if (isNewNode(t_head, nodeCnt)) nodeCnt++; // has added it in inputV if it returns true
        if (isNewNode(t_tail, nodeCnt)) nodeCnt++;
        inputHead[edgeCnt] = t_head;
        inputTail[edgeCnt] = t_tail;
        inputJ[edgeCnt] = t_judge;
        //printf("edgeC %d t_ju %c\n", edgeCnt, t_judge);
        edgeCnt++;
    }
    if (ext) {
        while (1) {
            scanf("%s", s);
            if (strcmp(s, "END") == 0) break;
            // add one line in another way
            int nodex;
            char judex[8];
            sscanf(s, "%d,%s", &nodex, judex);
            if (nodex == tmp)
                tmp = nodex * 10 + 1;
            int F_tail, T_tail;
            if (strcmp(judex, "AND") == 0) {
                int judex1 = nodex * 10 + 1;
                int judex2 = nodex * 10 + 2;
                if (isNewNode(judex1, nodeCnt)) nodeCnt++;
                if (isNewNode(judex2, nodeCnt)) nodeCnt++;
                for (int i = 0; i < edgeCnt; i++) {
                    if (inputTail[i] == nodex) {
                        inputTail[i] = judex1;
                    }
                    if (inputHead[i] == nodex) {
                        if (inputJ[i] == 'F') F_tail = inputTail[i];
                        if (inputJ[i] == 'T') T_tail = inputTail[i];
                    }
                }
                inputHead[edgeCnt] = judex1;
                inputTail[edgeCnt] = judex2;
                inputJ[edgeCnt] = 'T';
                edgeCnt++;
                
                inputHead[edgeCnt] = judex1;
                inputTail[edgeCnt] = F_tail;
                inputJ[edgeCnt] = 'F';
                edgeCnt++;
                
                inputHead[edgeCnt] = judex2;
                inputTail[edgeCnt] = T_tail;
                inputJ[edgeCnt] = 'T';
                edgeCnt++;
                
                inputHead[edgeCnt] = judex2;
                inputTail[edgeCnt] = F_tail;
                inputJ[edgeCnt] = 'F';
                edgeCnt++;
            }
            if (strcmp(judex, "OR") == 0) {
                int judex1 = nodex * 10 + 1;
                int judex2 = nodex * 10 + 2;
                if (isNewNode(judex1, nodeCnt)) nodeCnt++;
                if (isNewNode(judex2, nodeCnt)) nodeCnt++;
                for (int i = 0; i < edgeCnt; i++) {
                    if (inputTail[i] == nodex) {
                        inputTail[i] = judex1;
                    }
                    if (inputHead[i] == nodex) {
                        if (inputJ[i] == 'F') F_tail = inputTail[i];
                        if (inputJ[i] == 'T') T_tail = inputTail[i];
                    }
                }
                inputHead[edgeCnt] = judex1;
                inputTail[edgeCnt] = judex2;
                inputJ[edgeCnt] = 'F';
                edgeCnt++;
                
                inputHead[edgeCnt] = judex1;
                inputTail[edgeCnt] = T_tail;
                inputJ[edgeCnt] = 'T';
                edgeCnt++;
                
                inputHead[edgeCnt] = judex2;
                inputTail[edgeCnt] = T_tail;
                inputJ[edgeCnt] = 'T';
                edgeCnt++;
                
                inputHead[edgeCnt] = judex2;
                inputTail[edgeCnt] = F_tail;
                inputJ[edgeCnt] = 'F';
                edgeCnt++;
            }
        }
    }
    // input end
    //printf("input end\n");
    // create graph by inputHead, inputTail, inputJ, inputV 
    for (int i = 0; i < nodeCnt; i++) {
        vnodes[i].val = inputV[i];
        vnodes[i].in_edge = -1;
        vnodes[i].out_edge = -1;
    }
    //printf("edgeC %d\n", edgeCnt);
    for (int i = 0; i < edgeCnt; i++) {
        if (inputJ[i] == 'T') {
            cc++;
            //printf("%d ++\n", i);
        }
        int head_idx = findVtxIdx(inputHead[i], nodeCnt);
        int tail_idx = findVtxIdx(inputTail[i], nodeCnt);
        enodes[i].u = head_idx;
        enodes[i].v = tail_idx;
        enodes[i].nu = vnodes[head_idx].out_edge;
        vnodes[head_idx].out_edge = i;
        enodes[i].nv = vnodes[tail_idx].in_edge;
        vnodes[tail_idx].in_edge = i;
        enodes[i].val = inputJ[i];
    }
    // create end
    //printf("create end\n");
    way_id = 0;
    cur_path.len = 0;
    memset(hasVisitedE, false, sizeof(hasVisitedE));
    dfs(findVtxIdx(tmp, nodeCnt));
    printf("CC=%d\n", way_id);
    
    int lst[MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        lst[i] = i;
    }
    for (int i = 0; i < way_id - 1; i++) {
        for (int j = 0; j < way_id - i - 1; j++) {
            if (cmp(lst[j + 1], lst[j])) {
                int k = lst[j + 1];
                lst[j + 1] = lst[j];
                lst[j] = k;
            }
        }
    }
    
    for (int i = 0; i < way_id; i++) {
        int k = lst[i];
        //printf("%d k\n", k);
        printf("%d", vnodes[paths[k].vs[0]].val);
        for (int j = 1; j < paths[k].len; j++) {
            printf(",%d", vnodes[paths[k].vs[j]].val);
        }
        printf("\n");
    }
    return 0;
}