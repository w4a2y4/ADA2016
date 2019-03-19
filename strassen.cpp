//////////////////////////////////////////////////////////////////////////
// Source Strassen Algorithm
double ** mat_strassen_n(
    double **rst, double **a, double **b, int n)
{
    int i, j, n2;
    double **p1, **p2, **p3, **p4, **p5, **p6, **p7;
    double **a11, **a12, **a21, **a22;
    double **b11, **b12, **b21, **b22;
    double **m11, **m12, **m21, **m22;
    double **arst, **brst;
 
    if(n==2) return mat_strassen_2(rst, a, b);
 
    n2 = n/2;  
 
    //
    // allocate memory    
    //
    p1 = mat_new(n2, n2), p2 = mat_new(n2, n2), p3 = mat_new(n2, n2);
    p4 = mat_new(n2, n2), p5 = mat_new(n2, n2), p6 = mat_new(n2, n2);
    p7 = mat_new(n2, n2);
 
    a11 = mat_new(n2, n2), a12 = mat_new(n2, n2);
    a21 = mat_new(n2, n2), a22 = mat_new(n2, n2);
    b11 = mat_new(n2, n2), b12 = mat_new(n2, n2);
    b21 = mat_new(n2, n2), b22 = mat_new(n2, n2);    
    m11 = mat_new(n2, n2), m12 = mat_new(n2, n2);
    m21 = mat_new(n2, n2), m22 = mat_new(n2, n2);    
    arst = mat_new(n2, n2), brst = mat_new(n2, n2);
 
    //
    // divide matrix
    //     
    for(i=0 ; i<n2; ++i){
        for(j=0 ; j<n2; ++j){
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][n2+j];
            a21[i][j] = a[i+n2][j];
            a22[i][j] = a[i+n2][j+n2];
 
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][n2+j];
            b21[i][j] = b[i+n2][j];
            b22[i][j] = b[i+n2][j+n2];
        }
    }
 
    //
    // calculate p1~p7 , m11,m12,m21,m22
    //     
 
    //  p1 = (a12 - a22) * (b21 + b22)
    mat_strassen_n(p1,
        mat_sub(arst, a12, a22,n2,n2),
        mat_add(brst, b21, b22,n2,n2),
        n2);
 
    //     p2 = (a11 + a22) * (b11 + b22)
    mat_strassen_n(p2,
        mat_add(arst, a11, a22,n2,n2),
        mat_add(brst, b11, b22,n2,n2),
        n2);
 
    //     p3 = (a11 - a21) * (b11 + b12)
    mat_strassen_n(p3,
        mat_sub(arst, a11, a21,n2,n2),
        mat_add(brst, b11, b12,n2,n2),
        n2);
 
    //     p4 = (a11 + a12) * b22
    mat_strassen_n(p4,
        mat_add(arst, a11, a12,n2,n2),
        b22,
        n2);
 
    // p5 = a11 * (b12 - b22)
    mat_strassen_n(p5,
        a11,
        mat_sub(brst, b12, b22,n2,n2),
        n2);
 
 
    //  p6 = a22 * (b21 - b11)
    mat_strassen_n(p6,
        a22,
        mat_sub(brst, b21,b11,n2,n2),
        n2);
 
    
    //  p7 = (a21 + a22) * b11
    mat_strassen_n(p7,
        mat_add(arst,a21,a22,n2,n2),
        b11,
        n2);
 
    //     m11 = p1 + p2 - p4 + p6
    //  m11 = p1 + p2 - (p4 - p6)
    mat_sub(
        m11,
        mat_add(arst, p1, p2, n2,n2),
        mat_sub(brst, p4, p6, n2,n2),
        n2, n2);
 
    //     m12 = p4 + p5
    mat_add( m12, p4, p5, n2, n2);
 
    //     m21 = p6 + p7
    mat_add(m21, p6, p7, n2, n2);
 
    //     m22 = p2 - p3 + p5 - p7
    mat_add(
        m22,
        mat_sub(arst, p2, p3, n2, n2),
        mat_sub(brst, p5, p7, n2, n2),
        n2,n2);
 
    //
    // record result
    //     
    for(i=0; i<n2; ++i){
        for(j=0; j<n2; ++j){
            rst[i][j]       = m11[i][j];
            rst[i][j+n2]    = m12[i][j];
            rst[i+n2][j]    = m21[i][j];
            rst[i+n2][j+n2] = m22[i][j];
        }
    }
 
    //
    // release memory
    //
    free(p1), free(p2), free(p3), free(p4), free(p5);
    free(p6), free(p7), free(arst), free(brst);
    free(m11), free(m12), free(m21), free(m22);
    return rst;
}