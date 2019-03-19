#include <iostream>
#include <stdio.h>
using namespace std;

//“多重背包”通用模板
const int MAX_V = 150010;
//v、n、w：当前所处理的这类物品的体积、个数、价值
//V：背包体积， MAX_V：背包的体积上限值
//f[i]：体积为i的背包装前几种物品，能达到的价值上限。
inline void pack(long long int f[], int V, int v, int n, int w)
{
  if (n == 0 || v == 0) return;
  if (n == 1) {               //01背包
    for (int i = V; i >= v; --i)
      if (f[i] < f[i - v] + w) f[i] = f[i - v] + w*1LL;
    return;
  }
  if (n * v >= V - v + 1) {   //完全背包(n >= V / v)
    for (int i = v; i <= V; ++i)
      if (f[i] < f[i - v] + w) f[i] = f[i - v] + w*1LL;
    return;    
  }

  long long int va[MAX_V], vb[MAX_V];   //va/vb: 主/辅助队列
  for (int j = 0; j < v; ++j) {     //多重背包
    long long int *pb = va, *pe = va - 1;     //pb/pe分别指向队列首/末元素
    long long int *qb = vb, *qe = vb - 1;     //qb/qe分别指向辅助队列首/末元素  
    for (int k = j, i = 0; k <= V; k += v, ++i) {
      if (pe  == pb + n) {       //若队列大小达到指定值，第一个元素X出队。
        if (*pb == *qb) ++qb;   //若辅助队列第一个元素等于X，该元素也出队。 
        ++pb;
      }
      long long int tt = (f[k] - 1LL * i * w)*1LL;
      *++pe = tt;                  //元素X进队
      //删除辅助队列所有小于X的元素，qb到qe单调递减，也可以用二分法
      while (qe >= qb && *qe < tt) --qe;
      *++qe = tt;              //元素X也存放入辅助队列        
      f[k] = (*qb + 1LL * i * w )*1LL;      //辅助队列首元素恒为指定队列所有元素的最大值
    }
  }
}

int main() {

  int N, M, n[355], p[355], s[355]; 
  scanf("%d%d", &N, &M);
  //cin >> N >> M;
  for ( int i=1; i<=N; i++ )
    scanf("%d%d%d", &n[i], &p[i], &s[i]);
    //cin >> n[i] >> p[i] >> s[i];
  long long int dp[M+1];
  for( int j=0; j<=M; j++ ) dp[j] = 0;
  for( int i=1; i<=N; i++ )
    pack(dp, M, p[i], n[i], s[i]);

  cout << dp[M] << endl;

  return 0;
}