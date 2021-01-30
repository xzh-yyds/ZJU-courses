public class UnmodifiableMatrix {
    private final double[][] elms;

    public UnmodifiableMatrix(double[][] _elms){
        this.elms = new double[_elms.length][];
        for(int i=0; i<this.elms.length; i++)
            this.elms[i] = _elms[i].clone();
    }
    // return the number of rows of the matrix
    public int rows(){
        return this.elms.length;
    }
    // return the number of cols of the matrix
    public int cols(){
        if(this.elms.length<=0) return 0;
        return this.elms[0].length;
    }
    // get some element by index
    public double elemAt(int i, int j){
        return this.elms[i][j];
    }
    // return a new matrix after some position being set
    public UnmodifiableMatrix setElemAt(int i, int j, double x){
        double[][] a = new double[this.rows()][];
        for(int k=0; k<a.length; k++){
            a[k] = this.elms[k].clone();
        }
        a[i][j] = x;
        return new UnmodifiableMatrix(a);
    }
    // return a multiple of the matrix
    public UnmodifiableMatrix numMul(int k){
        double[][] a = new double[this.rows()][];
        for(int i=0; i<a.length; i++)
            a[i] = this.elms[i].clone();
        for(int i=0; i<a.length; i++)
            for(int j=0; j<a[0].length; j++)
                a[i][j] *= k;
        return new UnmodifiableMatrix(a);
    }
    // return the sum with another matrix
    public UnmodifiableMatrix add(UnmodifiableMatrix x){
        if(this.rows()!=x.rows() || this.cols()!=x.cols()){
            System.err.println("Two matrices in addition should have the same shape.");
            return null;
        }
        double[][] a = new double[this.rows()][];
        for(int k=0; k<a.length; k++)
            a[k] = this.elms[k].clone();
        for(int i=0; i<a.length; i++)
            for(int j=0; j<a[0].length; j++)
                a[i][j] += x.elms[i][j];
        return new UnmodifiableMatrix(a);
    }
    // return the product with another matrix multiplied on its right
    public UnmodifiableMatrix mul(UnmodifiableMatrix x){
        if(this.cols()!=x.rows()){
            System.err.println("The cols of the left and the rows of the right");
            return null;
        }
        double[][] a = new double[this.rows()][x.cols()];
        for(int i=0; i<a.length; i++)
            for(int j=0; j<a[0].length; j++)
                for(int k=0; k<this.cols(); k++)
                    a[i][j] += this.elms[i][k]*x.elms[k][j];
        return new UnmodifiableMatrix(a);
    }
    // return the transposition of the matrix
    public UnmodifiableMatrix transpose(){
        double[][] a = new double[this.cols()][this.rows()];
        for(int i=0; i<this.cols(); i++)
            for(int j=0; j<this.rows(); j++)
                a[i][j] = this.elms[j][i];
        return new UnmodifiableMatrix(a);
    }
    // just like the "equals" in String
    public boolean equals(UnmodifiableMatrix x){
        if(this.rows()!=x.rows() || this.cols()!=x.cols()) return false;
        for(int i=0; i<this.rows(); i++)
            for(int j=0; j<this.cols(); j++)
                if(this.elms[i][j]!=x.elms[i][j]) return false;
        return true;
    }
    @Override // transform the matrix into a string, serve for print
    public String toString(){
        String s = "[";
        for(int i=0; i<this.rows(); i++){
            s += (i==0?"":" ") + "[";
            for(int j=0; j<this.cols(); j++)
                s += (j==0?"":"  ") + this.elms[i][j];
            s += (i==this.rows()-1 ? "]" : "]\n");
        }
        s += "]\n";
        return s;
    }

    // test cases
    public static void main(String[] args){
        double[][] a1 = {
                {1,2,3},
                {4,5,6}
        };
        double[][] a2 = {
                {2,3,4},
                {5,6,7}
        };
        double[][] a3 = {
                {1,2},
                {3,4},
                {5,6}
        };
        UnmodifiableMatrix m1 = new UnmodifiableMatrix(a1);
        UnmodifiableMatrix m2 = new UnmodifiableMatrix(a2);
        UnmodifiableMatrix m3 = new UnmodifiableMatrix(a3);

        System.out.println("m1.rows(): " + m1.rows());
        System.out.println("m1.cols(): " + m1.cols());
        System.out.println("m1[0][0]: " + m1.elemAt(0,0));
        System.out.println("m1.setElemAt(0,0,12):\n" + m1.setElemAt(0,0,12));
        System.out.println("m1 after m1.setElemAt(0,0,12):\n" + m1);

        System.out.println("2*m1:\n" + m1.numMul(2));
        System.out.println("m1+m2:\n" + m1.add(m2));
        System.out.println("m1·m3:\n" + m1.mul(m3));
        System.out.println("m1.transpose():\n" + m1.transpose());
        System.out.println("m1:\n" + m1);
    }
}
