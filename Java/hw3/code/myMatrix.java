public class myMatrix {
    private double[][] elems;

    public myMatrix(int m, int n){
        elems = new double[m][n];
    }
    public myMatrix(double[][] x){
        for(int i=0; i<x.length; i++){
            if(x[i].length != x[0].length) {
                System.err.println("Each row in a matrix should have the same length.");
                return;
            }
        }
        this.elems = x.clone();
    }
    public myMatrix copy(){
        double[][] aa = new double[this.rows()][this.cols()];
        myMatrix res = new myMatrix(aa);
        return res;
    }
    // return the number of rows of the matrix
    public int rows(){
        return elems.length;
    }
    // return the number of cols of the matrix
    public int cols(){
        if(elems.length<=0) return 0;
        return elems[0].length;
    }
    // set the value of some element by index
    public void setElemAt(int i, int j, double x){
        this.elems[i][j] = x;
    }
    // return a element by index
    public double elemAt(int i, int j){
        return this.elems[i][j];
    }
    // return the result of a scalar multiplication on this matrix
    public myMatrix numMul(int k){
        myMatrix res = new myMatrix(this.rows(), this.cols());
        for(int i=0; i<this.rows(); i++)
            for(int j=0; j<this.cols(); j++)
                res.elems[i][j] = this.elems[i][j] * k;
        return res;
    }
    // return the sum of two matrices, new object
    public myMatrix add(myMatrix x){
        if(this.rows()!=x.rows() || this.cols()!=x.cols())
            return null;
        myMatrix res = new myMatrix(this.rows(), this.cols());
        for(int i=0; i<res.rows(); i++)
            for(int j=0; j<res.cols(); j++)
                res.elems[i][j] = this.elems[i][j] + x.elems[i][j];
        return res;
    }
    // return the product of two matrices, new object
    // require the rows of the left equals the cols of the right
    public myMatrix mul(myMatrix x){
        if(this.cols()!=x.rows())
            return null;
        myMatrix res = new myMatrix(this.rows(), x.cols());
        for(int i=0; i<res.rows(); i++)
            for(int j=0; j<res.cols(); j++)
                for(int k=0; k<this.cols(); k++)
                    res.elems[i][j] += this.elems[i][k] * x.elems[k][j];
        return res;
    }
    // transpose of a matrix, return a new object
    public myMatrix transpose(){
        myMatrix res = new myMatrix(this.cols(), this.rows());
        for(int i=0; i<res.rows(); i++)
            for(int j=0; j<res.cols(); j++)
                res.elems[i][j] = this.elems[j][i];
        return res;
    }
    // just like the "equals" in String
    public boolean equals(myMatrix x){
        if(this.rows()!=x.rows() || this.cols()!=x.cols()) return false;
        for(int i=0; i<this.rows(); i++)
            for(int j=0; j<this.cols(); j++)
                if(this.elems[i][j]!=x.elems[i][j]) return false;
        return true;
    }
    @Override // transform the matrix into a string, serve for print
    public String toString(){
        String s = "[";
        for(int i=0; i<this.rows(); i++){
            s += (i==0?"":" ") + "[";
            for(int j=0; j<this.cols(); j++)
                s += (j==0?"":"  ") + this.elems[i][j];
            s += (i==this.rows()-1 ? "]" : "]\n");
        }
        s += "]\n";
        return s;
    }

    // test cases
    public static void main(String[] args){
        double[][] a1 = {
                {1,2},
                {3,4},
                {5,6},
        };
        double[][] a2 = {
                {2,3},
                {4,5},
                {6,7},
        };
        double[][] a3 = {
                {1,2,3},
                {4,5,6}
        };
        myMatrix m1 = new myMatrix(a1);
        myMatrix m2 = new myMatrix(a2);
        myMatrix m3 = new myMatrix(a3);

        myMatrix m4 = m1.numMul(2);
        myMatrix m5 = m1.add(m2);
        myMatrix m6 = m1.mul(m3);
        myMatrix m7 = m2.transpose();

        System.out.println("m1:\n" + m1);
        System.out.println("m2:\n" + m2);
        System.out.println("m3:\n" + m3);
        System.out.println("m1.rows: " + m1.rows());
        System.out.println("m1.cols: " + m1.cols());
        System.out.println("m1[0][0]: " + m1.elemAt(0,0));
        m1.setElemAt(0,0,0);
        System.out.println("m1 after set(0,0,0):\n" + m1);
        m1.setElemAt(0,0,1);
        System.out.println("m1 after set(0,0,1):\n" + m1);

        System.out.println("2*m1:\n" + m4);
        System.out.println("m1+m2:\n" + m5);
        System.out.println("m1·m3:\n" + m6);
        System.out.println("m2.transpose():\n" + m7);
    }
}
