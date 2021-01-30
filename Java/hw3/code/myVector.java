public class myVector {
    private double elems[];
//    public int capacity;
//    public int size;

    public myVector(double[] x){
        this.elems = x.clone();
    }
    public myVector(int dim){
        this.elems = new double[dim];
    }
    // return the dimension of this vector
    public int dim(){
        return this.elems.length;
    }
    public myVector copy(){
        return new myVector(this.elems.clone());
    }
    // set the value of some element by index
    public void setElemAt(int dim, double x){
        elems[dim] = x;
    }
    // return the result of a scalar multiplication on this vector
    public myVector numMul(int k){
        myVector res = this.copy();
        for(int i=0; i<elems.length; i++)
            res.elems[i] *= k;
        return res;
    }
    // return the sum of two vectors, new object
    public myVector add(myVector x){
        if(x.dim()!=this.dim())
            return null;
        myVector res = x.copy();
        for(int i=0; i<elems.length; i++)
            res.elems[i] += this.elems[i];
        return res;
    }
    // return the inner product of two vectors, new object
    public double dotMul(myVector x){
        if(x.dim()!=this.dim())
            System.err.println("Two vectors in inner production should have the same dimension.");
        double res = 0;
        for(int i=0; i<this.dim()&&i<x.dim(); i++)
            res += this.elems[i] * x.elems[i];
        return res;
    }
    // return a element by index
    public double elemAt(int index){
        return elems[index];
    }
    // like "equals" in String
    public boolean equals(myVector x){
        if(this.dim() != x.dim()) return false;
        for(int i=0; i<this.dim(); i++)
            if(this.elems[i] != x.elems[i]) return false;
        return true;
    }
    @Override // transform the vector into a string, serve for print
    public String toString(){
        String s = "[";
        for(int i=0; i<this.elems.length; i++)
            s += (i==0?"":"  ") + this.elems[i];
        s += "]";
        return s;
    }

    static public void main(String[] args){
        double[] a1 = {1,2,3,4,5};
        double[] a2 = {2,3,4,5,6};
        myVector v1 = new myVector(a1);
        myVector v2 = new myVector(a2);

        myVector v3 = v1.numMul(2);
        myVector v4 = v1.add(v2);
        double v5 = v1.dotMul(v2);

        System.out.println("v1: " + v1);
        System.out.println("v2: " + v2);
        System.out.println("v1.dim: " + v1.dim());
        System.out.println("v1.elemAt(0)" + v1.elemAt(0));
        v1.setElemAt(0,12);
        System.out.println("v1 after set(0,12): " + v1);
        v1.setElemAt(0,1);
        System.out.println("v1 after set(0,1): " + v1);
        System.out.println("2*v1: " + v1.numMul(2));
        System.out.println("v1+v2: " + v1.add(v2));
        System.out.println("v1·v2: " + v1.dotMul(v2));
    }
}
