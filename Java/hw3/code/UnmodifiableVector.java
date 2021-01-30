public class UnmodifiableVector {
    private final double[] elms;

    public UnmodifiableVector(double[] _elms) {
        this.elms = _elms.clone();
    }
    // return the dimension of this vector
    public int dim(){
        return this.elms.length;
    }
    // get some element by index
    public double elemAt(int index){
        return this.elms[index];
    }
    // return a new vector after some position being set
    public UnmodifiableVector setElemAt(int index, double x){
        double[] a = this.elms.clone();
        a[index] = x;
        return new UnmodifiableVector(a);
    }
    // return a number product with another vector
    public UnmodifiableVector numMul(int k){
        double[] a = this.elms.clone();
        for(int i=0; i<a.length; i++) a[i] *= k;
        return new UnmodifiableVector(a);
    }
    // return the sum with another vector
    public UnmodifiableVector add(UnmodifiableVector x){
        if(x.dim()!=this.dim()){
            System.err.println("Two vectors in addition should have the same dimension.");
            return null;
        }
        double[] a = this.elms.clone();
        for(int i=0; i<a.length; i++)
            a[i] += x.elms[i];
        return new UnmodifiableVector(a);
    }
    // return the inner product with another vector
    public double dotMul(UnmodifiableVector x){
        if(x.dim()!=this.dim())
            System.err.println("Two vectors in inner production should have the same dimension.");
        double res = 0;
        for(int i=0; i<this.dim()&&i<x.dim(); i++)
            res += this.elms[i] * x.elms[i];
        return res;
    }
    // like "equals" in String
    public boolean equals(UnmodifiableVector x){
        if(this.dim() != x.dim()) return false;
        for(int i=0; i<this.dim(); i++)
            if(this.elms[i] != x.elms[i]) return false;
        return true;
    }
    @Override // transform the vector into a string, serve for print
    public String toString(){
        String s = "[";
        for(int i=0; i<this.elms.length; i++)
            s += (i==0?"":"  ") + this.elms[i];
        s += "]";
        return s;
    }

    // test cases
    public static void main(String[] args){
        double[] a1 = {1,2,3,4,5};
        double[] a2 = {2,3,4,5,6};
        UnmodifiableVector v1 = new UnmodifiableVector(a1);
        UnmodifiableVector v2 = new UnmodifiableVector(a2);

        System.out.println("v1.dim: " + v1.dim());
        System.out.println("v1[0]: " + v1.elemAt(0));
        System.out.println("v1.setElemAt(0,12): " + v1.setElemAt(0,12));
        System.out.println("v1 after v1.setElemAt(0,12): " + v1);
        System.out.println("2*v1: " + v1.numMul(2));
        System.out.println("v1+v2: " + v1.add(v2));
        System.out.println("v1·v2: " + v1.dotMul(v2));
        System.out.println("v1: " + v1);
    }
}
