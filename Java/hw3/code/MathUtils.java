public class MathUtils {
    // convert a vector into unmodifiable vector
    public static UnmodifiableVector getUnmodifiableVector(myVector v){
        double[] a = new double[v.dim()];
        for(int i=0; i<a.length; i++)
            a[i] = v.elemAt(i);
        return new UnmodifiableVector(a);
    }
    // convert a matrix into unmodifiable matrix
    public static UnmodifiableMatrix getUnmodifiableMatrix(myMatrix m){
        double[][] a = new double[m.rows()][m.cols()];
        for(int i=0; i<m.rows(); i++)
            for(int j=0; j<m.cols(); j++)
                a[i][j] = m.elemAt(i,j);
        return new UnmodifiableMatrix(a);
    }
    // test
    public static void main(String args[]){
        double[] a1 = {0,1,2,3,4,5,6,7,8,9};
        myVector v1 = new myVector(a1);
        UnmodifiableVector uv1 = getUnmodifiableVector(v1);
        System.out.println("vector conversion finished:\n" + uv1);

        double[][] a2 = {
                {1,2,3},
                {4,5,6}
        };
        myMatrix m1 = new myMatrix(a2);
        UnmodifiableMatrix um1 = getUnmodifiableMatrix(m1);
        System.out.println("matrix conversion finished:\n" + um1);
    }
}
