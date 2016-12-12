//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。
//cin.peek()观测输入的第一个字符（返回char） cin.peek() == '\n' 判断输入了换行符
//unsigned int 1<<32及以上为什么等于3520 / 3504？
//01011111101111111111100000111000

/*

*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <list>

#define FIN(i,N) for(i=0;i<(N);++i)
#define FIN1(i,N) for(i=1;i<=(N);++i)
#define FINM(i,N) for(i=((N)-1);i>=0;--i)
#define FINM1(i,N) for(i=(N);i>=1;--i)
#define inf 1<<30 // 2*inf<=2^31, 1<<30 is good
#define iginf 0x7fffffff // 2147483647
#define PI 3.141593
#define MAX_LEN 30

using namespace std;
typedef long long int ll;

const int dir[][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

struct pos {
    int x, y, z;
};

int main() {
    int mymap[MAX_LEN][MAX_LEN][MAX_LEN];
    int vis[MAX_LEN][MAX_LEN][MAX_LEN];
    int l, r, c, t = 0, i, j, k, rst = 0;
    string tmp;
    pos stt, cur, nxt;
    queue<pos> que;
    
    while (cin >> l >> r >> c) {
        if (!l && !r && !c) break;
        memset(mymap, 0, sizeof(mymap)); memset(vis, 0, sizeof(vis));
        t = rst = 0;
        FIN(i, l) {
            FIN(j, r) {
                cin >> tmp;
                FIN(k, c) {
                    mymap[k][j][i] = tmp.at(k);
                    if (tmp.at(k) == 'S') { stt.x = k; stt.y = j; stt.z = i; }
                }
            }
        }
        vis[stt.x][stt.y][stt.z] = 1;
        que.push(stt);
        while (!que.empty()) {
            cur = que.front();
            t = vis[cur.x][cur.y][cur.z] >> 1;
            FIN(i, 6) {
                nxt.x = cur.x + dir[i][0]; nxt.y = cur.y + dir[i][1]; nxt.z = cur.z + dir[i][2];
                if (nxt.x < 0 || nxt.y < 0 || nxt.z < 0 || nxt.x >= c || nxt.y >= r || nxt.z >= l ||
                    mymap[nxt.x][nxt.y][nxt.z] == '#' || vis[nxt.x][nxt.y][nxt.z] & 1) continue;
                if (mymap[nxt.x][nxt.y][nxt.z] == 'E') { rst = t + 1; break; }
                vis[nxt.x][nxt.y][nxt.z] = (t + 1 << 1) + 1;
                que.push(nxt);
            }
            que.pop();
        }
        
        if (rst) cout << "Escaped in " << rst << " minute(s)." << endl;
        else cout << "Trapped!" << endl;
    }
}

/*
struct p {
    int des; // destination
    int dis; // distance
};

p path[MAX_LEN][MAX_LEN];
int MinPos[MAX_LEN];
int n;
 */
/*
int my_cmp(const void *a, const void *b) {
    int m = ((p*)a)->dis; int n = ((p*)b)->dis;
    // throw 0s behind
    if (!m) return 1;
    if (!n) return -1;
    return (m - n);
}

// find the min positive number(and its index) in an array
p findMinPos(p path[][MAX_LEN], int begin) {
    p tmp[MAX_LEN], rst;
    memcpy(&tmp, path + begin, sizeof(p) * MAX_LEN);
    qsort(tmp, MAX_LEN, sizeof(p), my_cmp);
    rst.des = tmp[0].des; rst.dis = tmp[0].dis; // still can be 0
    return rst;
}
*/
/*
int main() {
    int i, j, k, dis, curVill = 0, rst = 0, Amin = inf, Bmin = inf;
    char cur, vill;
    p minV, minS;
    while (cin >> n) {
        if (!n) break;
        memset(path, 0, sizeof(path)); memset(MinPos, 0, sizeof(MinPos));
        curVill = rst = 0; Amin = Bmin = inf;
        FIN(i, n - 1) {
            cin >> cur >> k;
            while (k--) {
                cin >> vill >> dis;
                p tmp; tmp.des = vill - 'A'; tmp.dis = dis;
                path[cur - 'A'][vill - 'A'] = tmp;
                tmp.des = cur - 'A';
                path[vill - 'A'][cur - 'A'] = tmp;
            }
        }
        FIN(i, n - 1) {
            MinPos[curVill] |= (1 << 16);
            minV.des = 0; minV.dis = inf;
            FIN(j, n) {
                if (MinPos[j] & (1 << 16)) {
                    for (int k = 0; k < n; k++) {
                        if (!path[j][k].dis || MinPos[k] & (1 << 16)) continue;
                        if (path[j][k].dis < minV.dis) {
                            minV.dis = minS.dis = path[j][k].dis;
                            minV.des = k; curVill = j;
                        }
                    }
                }
            }
            rst += minV.dis;
            path[curVill][minV.des].dis = path[minV.des][curVill].dis = 0;
            curVill = minV.des;
        }
        cout << rst << endl;
    }
    
}
*/

/*
#define STK_OV "stack overflow!"
#define LEN_ZERO "length of the array == 0!"
#define INDEX_OFR "index of the array out of range!"
#define FIND_1_IN_0 "cannot find 1 because the input == 0!"

using namespace std;
typedef long long int ll;

const unsigned int bits_of_int = __SIZEOF_INT__ * 8;

class BitArray {
protected:
    bool neg = false;
    unsigned int len;
    unsigned int int_count;
    unsigned int *bits;
public:
    
    BitArray operator -(const BitArray);
    
    BitArray(unsigned int length) {
        if (!length) throw LEN_ZERO;
        this->int_count = (length + (bits_of_int - 1)) / bits_of_int;
        this->bits = new unsigned int[this->int_count]();
        this->len = length;
        //memset(this->bits, 0, this->int_count * __SIZEOF_INT__);
        //int i;
        //FIN(i, int_count) {
        //    bits[i] = 0;
        //}
    }
    
    BitArray(const BitArray &source):int_count(source.int_count) {
        bits = new unsigned int[int_count]();
        len = source.len;
        //memcpy(bits, &source.bits, sizeof(source.bits));
        int i;
        FIN(i, int_count) {
            bits[i] = source.bits[i];
        }
    }
    
    void init(unsigned int length) {
        if (!length) throw LEN_ZERO;
        this->int_count = (length + (bits_of_int - 1)) / bits_of_int;
        this->bits = new unsigned int[this->int_count]();
        this->len = length;
        memset(this->bits, 0, this->int_count * __SIZEOF_INT__);
    }
    
    void setBit(unsigned int index, unsigned int value) {
        if (index >= this->len) throw INDEX_OFR;
        if (value) {
            this->bits[index / bits_of_int] |= 1 << (index % bits_of_int);
        } else {
            this->bits[index / bits_of_int] &= ~(1 << (index % bits_of_int));
        }
    }
    
    unsigned int getBit(unsigned int index) const {
        if (index >= this->len) throw INDEX_OFR;
        if (this->bits[index / bits_of_int] & (1 << (index % bits_of_int))) {
            return 1;
        } else {
            return 0;
        }
    }
    
    unsigned int length() {
        return this->len;
    }
    
    void clear() {
        delete[] bits;
        len = 0;
        int_count = 0;
    }
    
    ~BitArray() {
        clear();
    }
    
    BitArray* operator =(ll num) {
        int i, zero = ~0;
        if (num < 0) this->neg = true;
        //memset(this->bits, 0, this->int_count * __SIZEOF_INT__);
        FIN(i, this->int_count) {
            this->bits[i] = num & (zero);
            num >>= bits_of_int;
            if (!num) break;
        }
        return this;
    }
    
    const BitArray &operator =(const BitArray &num) {
        if (&num == this) return *this;
        delete[] bits;
        neg = num.neg;
        len = num.len;
        int_count = num.int_count;
        bits = new unsigned int[int_count]();
        //memcpy(this->bits, &num.bits, sizeof(num.bits));
        int i;
        FIN(i, len) {
            setBit(i, num.getBit(i));
        }
        return *this;
    }
    
    const BitArray &copy(const BitArray &num, bool expand = false,
                         unsigned int destIndex = 0, unsigned int sourceIndex = 0,
                         unsigned int length = 0) {
        //if (&num == this) return *this;
        if (!length) length = num.len;
        if (sourceIndex + length > num.len) throw INDEX_OFR;
        if (expand && this->len - destIndex < length) {
            //delete[] bits;
            //len = num.len;
            //int_count = num.int_count;
            //bits = new unsigned int[int_count]();
            this->resize(destIndex + length);
        }
        //memcpy(this->bits, &num.bits, sizeof(num.bits));
        int i;
        //FIN(i, len) {
        //    if (i >= num.len) {
        //        setBit(i, 0);
        //    } else {
        //        setBit(i, num.getBit(i));
        //    }
        //}
        FIN(i, length) {
            if (i + destIndex >= this->len) break;
            this->setBit(i + destIndex, num.getBit(i + sourceIndex));
        }
        this->neg = num.neg;
        return *this;
    }
    
    unsigned int bitScan(bool reverse = false) { // find the highest / lowest 1's position
        unsigned int pos, i, tmp;
        if (reverse) {
            FINM(i, this->int_count) {
                if (!this->bits[i]) continue;
                tmp = this->bits[i];
                __asm {
                    bsr eax, tmp;
                    mov pos, eax;
                }
                return (pos + i * bits_of_int);
            }
        } else {
            FIN(i, this->int_count) {
                if (!this->bits[i]) continue;
                tmp = this->bits[i];
                __asm {
                    bsf eax, tmp;
                    mov pos, eax;
                }
                return (pos + i * bits_of_int);
            }
        }
        throw FIND_1_IN_0; // *this == 0
    }
    
    BitArray* resize(unsigned length) { // do not expand even if length < this->len
        BitArray tmp(length);
        int i;
        FIN(i, length) {
            if (len <= i) {
                tmp.setBit(i, 0);
            } else {
                tmp.setBit(i, this->getBit(i));
            }
        }
        delete[] bits;
        len = tmp.len;
        int_count = tmp.int_count;
        bits = new unsigned int[int_count]();
        FIN(i, length) {
            this->setBit(i, tmp.getBit(i));
        }
        return this;
    }
    
    BitArray &operator ~() {
        this->neg = !this->neg;
        return *this;
    }
    
    bool operator ==(unsigned int target) const {
        if (this->neg) return false;
        int i;
        FIN1(i, this->int_count - 1) {
            if (this->bits[i]) return false;
        }
        return (this->bits[0] == target);
    }
    
    bool operator ==(const BitArray& target) const {
        if (this->neg != target.neg) return false;
        if (len != target.len) return false;
        int i;
        FIN(i, len) {
            if (getBit(i) ^ target.getBit(i)) return false;
        }
        return true;
    }
    
    bool operator !=(unsigned int target) const {
        return !(*this == target);
    }
    
    bool operator !=(const BitArray& target) const {
        return !(*this == target);
    }
    
    bool operator !() const {
        return (*this == 0);
    }
    
    unsigned int operator [](unsigned int index) const {
        return getBit(index);
    }
    
    BitArray operator +(const BitArray &num) {
        unsigned int len = max(this->len, num.len) + 1;
        int i;
        int8_t c = 0; // carry flag, using 1 byte to store the flags
        //bool c = false;
        BitArray tmp1(len), tmp2(len);
        tmp1 = tmp1.copy(*this); tmp2 = tmp2.copy(num);
        FIN(i, tmp1.int_count) {
            unsigned int a = tmp1.bits[i], b = tmp2.bits[i];
            if (c & 1) { // carry
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    stc;             // carry flag = 1
                    adc eax, ebx;
                    mov a, eax;
                    lahf;            // lahf will effect the result????
                    mov c, ah;
                }
            } else {
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    clc;              // carry flag = 0
                    adc eax, ebx;
                    mov a, eax;
                    lahf;             // mov ah, flags
                    mov c, ah;
                }
            }
            tmp1.bits[i] = a;
            */
            /*
             ======bug====== the determination of carring or not remains bugs.
            if (c) {
                c = false;
                if (a == 4294963295) c = true;
                ++a;
                tmp1.bits[i] = a;
            }
            if ((a & b) >= (1 << 31)) c = true; else c = false;
            while (a && b) {
                tmp1.bits[i] = a ^ b;
                tmp2.bits[i] = a & b;
                a = tmp1.bits[i]; b = tmp2.bits[i] << 1;
            }
            tmp1.bits[i] = (a | b);
            */
            /*
        }
        if (c & 1) throw STK_OV;
        //tmp1 != 0 !!!!!!
        tmp1 = *tmp1.resize(tmp1.bitScan(true) + 1);
        *this = tmp1;
        return *this;
    }
    
    BitArray operator -(const BitArray &num) {
        if (this->neg != num.neg) return ~(~(*this) + num);
        unsigned int len = max(this->len, num.len) + 1;
        int i;
        int8_t c = 0; // carry flag, using 1 byte to store the flags
        //bool c = false;
        BitArray tmp1(len), tmp2(len);
        tmp1 = tmp1.copy(*this); tmp2 = tmp2.copy(num);
        FIN(i, tmp1.int_count) {
            unsigned int a = tmp1.bits[i], b = tmp2.bits[i];
            if (c & 1) { // carry
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    stc;             // carry flag = 1
                    adc eax, ebx;
                    mov a, eax;
                    lahf;            // lahf will effect the result????
                    mov c, ah;
                }
            } else {
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    clc;              // carry flag = 0
                    adc eax, ebx;
                    mov a, eax;
                    lahf;             // mov ah, flags
                    mov c, ah;
                }
            }
            tmp1.bits[i] = a;
            */
            /*
             ======bug====== the determination of carring or not remains bugs.
             if (c) {
             c = false;
             if (a == 4294963295) c = true;
             ++a;
             tmp1.bits[i] = a;
             }
             if ((a & b) >= (1 << 31)) c = true; else c = false;
             while (a && b) {
             tmp1.bits[i] = a ^ b;
             tmp2.bits[i] = a & b;
             a = tmp1.bits[i]; b = tmp2.bits[i] << 1;
             }
             tmp1.bits[i] = (a | b);
             */
            /*
        }
        if (c & 1) throw STK_OV;
        //tmp1 != 0 !!!!!!
        tmp1 = *tmp1.resize(tmp1.bitScan(true) + 1);
        *this = tmp1;
        return *this;
    }
    
    BitArray &operator *(const BitArray &num) {
        if (!(*this) || !num) {
            BitArray zero(1);
            *this = zero;
            return *this;
        }
        if (this->len == 1 && this->len == num.len) {
            BitArray rst(1);
            rst.setBit(0, 1); // now *this != 0 && num != 0
            *this = rst;
            return *this;
        }
        unsigned int len = max(this->len, num.len);
        int i;
        
        BitArray tmpa(len), tmpb(len);
        tmpa = tmpa.copy(*this); tmpb = tmpb.copy(num);
        BitArray tmp1(len >> 1), tmp2(len >> 1),
            tmp3(len - (len >> 1)), tmp4(len - (len >> 1)), rst(len << 1);
        tmp1 = tmp1.copy(tmpa); tmp2 = tmp2.copy(tmpb);
        tmp3 = tmp3.copy(tmpa, false, 0, len >> 1); tmp4 = tmp4.copy(tmpb, false, 0, len >> 1);
        rst = rst.copy(tmp1 * tmp2);
        rst = rst.copy(tmp1 * tmp4 + tmp2 * tmp3, false, len >> 1);
        rst = rst.copy(tmp3 * tmp4, false, len >> 1 << 1);
        return *this;
    }
    
    void printBin() const {
        int i;
        FINM(i, this->len) {
            printf("%u", getBit(i));
        }
        printf("\n");
    }
    
    void printDec() const { // bug
        int i;
        FINM(i, this->int_count) {
            printf("%u ", this->bits[i]);
        }
        printf("\n");
    }
};

int main() {
    try {
        BitArray b(64);
        b = 102030405060708090;
        BitArray c(64);
        c = 908070605040302010;
        c = b + c;
        c.printBin(); c.printDec();
    } catch(string dscpt) {
        cout << dscpt << endl;
    }
}
*/
