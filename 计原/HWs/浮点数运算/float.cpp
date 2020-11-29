#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<vector>
using namespace std;

typedef unsigned dwrd;

vector<int> strIntAdd(vector<int> a, vector<int> b, int n){
	if(b.size()>a.size()){
		vector<int> t=a;
		a=b;
		b=t;
	}
	while(b.size()<a.size()){
		b.insert(b.begin(),0);
	}
	int c=0;
	vector<int> res;
	for(int i=a.size()-1;i>=0;i--){
		res.insert(res.begin(),(c+a[i]+b[i])%n);
		c=(a[i]+b[i]+c)/n;
	}
	while(c){
		res.insert(res.begin(),c%n);
		c/=n;
	}
	return res;
}
int strIntCmp(vector<int> a, vector<int> b){
	if(b.size()<a.size()){
		return 1;
	}
	if(a.size()<b.size()){
		return -1;
	}
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[i]){
			return a[i]-b[i];
		}
	}
	return 0;
}
vector<int> strIntSub(vector<int> a, vector<int> b, int n){
	while(b.size()<a.size()){
		b.insert(b.begin(),0);
	}
	int c=0;
	vector<int> res;
	for(int i=a.size()-1;i>=0;i--){
		res.insert(res.begin(),(a[i]-b[i]-c+n)%n);
		c=(a[i]<b[i]+c)?1:0;
	}
	for(int i=0;i<res.size();i++){
		if(res[i]) break;
		res.erase(res.begin());
	}
	return res;
}
vector<int> strIntDiv(vector<int> a, vector<int> b, int n){
	vector<int> res;
	vector<int> one;
	one.push_back(1);
	while(strIntCmp(a,b)>=0){
		res=strIntAdd(res,one,n);
		a=strIntSub(a,b,n);
	}
	return res;
}
vector<int> inteb2d(vector<int> inte){
	vector<int> res;
	vector<int> flag;
	flag.push_back(1);
	vector<int> dec_flag;
	dec_flag.push_back(1);
	while(strIntCmp(flag,inte)<0){
		flag=strIntAdd(flag,flag,2);
		dec_flag=strIntAdd(dec_flag,dec_flag,10);
	}
	vector<int> two;
	two.push_back(2);
	while(flag.size()){
		if(strIntCmp(flag,inte)<=0){
			res=strIntAdd(res,dec_flag,10);
			inte=strIntSub(inte,flag,2);
		}
		flag.pop_back();
		dec_flag=strIntDiv(dec_flag,two,10);
	}
	return res;
}
vector<int> strFracAdd(vector<int> a, vector<int> b, int n){
	if(b.size()>a.size()){
		vector<int> t=a;
		a=b;
		b=t;
	}
	while(b.size()<a.size()){
		b.insert(b.end(),0);
	}
	int c=0;
	vector<int> res;
	for(int i=a.size()-1;i>=0;i--){
		res.insert(res.begin(),(c+a[i]+b[i])%n);
		c=(a[i]+b[i]+c)/n;
	}
	
	return res;
}
vector<int> strFracSub(vector<int> a, vector<int> b, int n){
	while(b.size()<a.size()){
		b.insert(b.end(),0);
	}
	while(a.size()<b.size()){
		a.insert(a.end(),0);
	}
	int c=0;
	vector<int> res;
	for(int i=a.size()-1;i>=0;i--){
		res.insert(res.begin(),(a[i]-b[i]-c+n)%n);
		c=(a[i]<b[i]+c)?1:0;
	}
	while(res.size()>0 && res[res.size()-1]==0){
		res.erase(res.end()-1);
	}
	return res;
}
vector<int> strFracDiv(vector<int> a, int b, int n){
	vector<int> res;
	int c=0;
	for(int i=0;i<a.size();i++){
		res.push_back((a[i]+c*n)/b);
		c=(a[i]+c*n)%b;
	}
	while(c){
		res.push_back((c*n)/b);
		c=(c*n)%b;
		if(res.size()>32) break;
	}
	return res;
}
int strFracCmp(vector<int> a, vector<int> b){
	for(int i=0;i<a.size()&&i<b.size();i++){
		if(a[i]!=b[i]) return a[i]-b[i];
	}
	if(a.size()<b.size()) return -1;
	if(a.size()>b.size()) return 1;
	return 0;
}
vector<int> fracb2d(vector<int>& frac){
	vector<int> res;
	vector<int> flag;
	flag.push_back(1);
	vector<int> dec_flag;
	dec_flag.push_back(5);
	while(res.size()<32){
		if(strFracCmp(flag,frac)<=0){
			res=strFracAdd(res,dec_flag,10);
			frac=strFracSub(frac,flag,2);
			if(frac.size()==0){
				break;
			}
		}
		flag=strFracDiv(flag,2,2);
		dec_flag=strFracDiv(dec_flag,2,10);
	}
	while(res.size()>0 && res[res.size()-1]==0){
		res.erase(res.end()-1);
	}
	return res;
}

char* ftoa(dwrd f){
    dwrd fs=f&0x80000000;
	//sign bit
    dwrd fe=(f&0x7F800000)>>23;
	//exponent bits
	dwrd ff=f & 0x007FFFFF;
    //fraction bits
	ff|=0x00800000;
    ff<<=8;

	vector<int> inte;
	vector<int> frac;

	int e=fe-127;
	e++;
	while(e>0){
		inte.push_back((ff>>31)%2);
		ff<<=1;
		e--;
	}
	while(ff){
		frac.push_back((ff>>31)%2);
		ff<<=1;
	}
	while(e<0){
		frac.insert(frac.begin(),0);
		e++;
	}

	vector<int> a=inteb2d(inte);
	vector<int> b=fracb2d(frac);

	string str;
	for(int i=0;i<a.size();i++){
		str.insert(str.end(),a[i]+'0');
	}
	str.insert(str.end(),'.');
	for(int i=0;i<b.size();i++){
		str.insert(str.end(),b[i]+'0');
	}
	if(fs) str.insert(str.begin(),'-');
	char *s=(char*)malloc((str.length()+1)*sizeof(char));
	for(int i=0;i<str.length();i++){
		s[i]=str[i];
	}
	s[str.length()]='\0';
    return s;
}
dwrd atof(char* str){
    dwrd s=0x00000000;
	int i=0;
	if(strlen(str)&&str[0]=='-'){
		s=0x80000000;
		i++;
	}
	dwrd e=31;
	dwrd a=0;
	while(i<strlen(str)&&str[i]!='.'){
		a=a*10;
		a+=str[i]-'0';
	}
	while((a>>e)%2==0){
		e--;
	}
	dwrd f=a<<28;
	int j=i;//j is a backup of i
	i++;
	dwrd b=0;
	
	int l=strlen(str+i);
	dwrd flag=5*pow(10,l-1);
	while(i-j<=10 && i<strlen(str)){
		b*=10;
		b+=str[i]-'0';
	}
	dwrd ff=0;
	for(i=0;i<32;i++){
		ff<<=1;
		if(b>=flag){
			ff++;
			b-=flag;
		}
		flag>=1;
	}
	f|=ff>>e;
	
}

dwrd fadd(dwrd a, dwrd b){
    if(a&0x7FFFFFFF < b&0x7FFFFFFF){
		dwrd t=a;
		a=b;
		b=t;
	}
	dwrd as=a & 0x80000000;
    dwrd bs=b & 0x80000000;
	//sign bit
    dwrd ae=(a&0x7F800000)>>23;
    dwrd be=(b&0x7F800000)>>23;
	//exponent bits
    dwrd af=a & 0x007FFFFF;
	dwrd bf=b & 0x007FFFFF;
    //fraction bits
	
	af|=0x00800000;
    bf|=0x00800000;
    af<<=7;
    bf<<=7;

    int de=ae-be;
    while(de<0){//ae<be
        af>>=1;
        de++;
        ae++;
    }
    while(de>0){//ae>be
        bf>>=1;
        de--;
        be++;
    }
	//align exponents

    dwrd f,e,s;
    e=ae;
	s=as;
    if(as==bs){
        f=af+bf;
    }else{
        f=af-bf;
    }
	if(f==0){
		e=0;
	}
	if(f&0x80000000){
		f>>=1;
		e++;
	}
	f+=f&0x00000040;
	if(f&0x80000000){
		f>>=1;
		e++;
	}
	f>>=7;
	f&=0x007FFFFF;
    
    dwrd res=s|e<<23|f;

    return res;
}
dwrd fsub(dwrd a, dwrd b){
    b^=0x80000000;
    return fadd(a,b);
}
dwrd fmul(dwrd a, dwrd b){
    dwrd as=(a & 0x80000000);
    dwrd bs=(b & 0x80000000);
	//sign bit
	dwrd ae=(a & 0x7F800000)>>23;
    dwrd be=(b & 0x7F800000)>>23;
	//exponent bits
	dwrd af=a & 0x007FFFFF;
	dwrd bf=b & 0x007FFFFF;
	//fraction bits

	dwrd s=as^bs;
	dwrd e=ae+be-127;    

    af|=0x00800000;
    bf|=0x00800000;
	af>>=8;
	bf>>=8;

    dwrd f=0;
    for(int i=0;i<32;i++){
        f += bf%2?a<<i:0;
        bf>>=1;
    }
	f+=f & 0x00000080;
    f>>=8;
	f&=0x007FFFFF;
    
    dwrd res=s|e<<23|f;

	return res;
}
dwrd fdiv(dwrd a, dwrd b){
    dwrd as=(a & 0x80000000);
    dwrd bs=(b & 0x80000000);
	//sign bit
	dwrd ae=(a & 0x7F800000)>>23;
    dwrd be=(b & 0x7F800000)>>23;
	//exponent bits
	dwrd af=a & 0x007FFFFF;
	dwrd bf=b & 0x007FFFFF;
	//fraction bits

	dwrd s=as^bs;
	dwrd e=ae-be+127;

	af|=0x00800000;
    bf|=0x00800000;
	
	dwrd f=0;
	for(int i=0;i<32;i++){
		f<<=1;
		if(af>bf){
			f+=1;
			af-=bf;
		}
		af<<=1;
	}
	while(f&0x80000000==0){
		f<<=1;
		e--;
	}
	f>>=8;
	f&=0x007FFFFF;

	dwrd res=s|e<<23|f;

	return res;
}


int main(){
    dwrd a=0x42FF0000;//127.5
    dwrd b=0x427D0000;//63.25
	char *sa=ftoa(a);
	char *sb=ftoa(b);
	printf("%s\n",sa);
	printf("%s\n",sb);

	dwrd sum=fadd(a,b);
    dwrd dif=fsub(a,b);
    dwrd prd=fmul(a,b);
    dwrd quo=fdiv(a,b);

	printf("sum: %s\n",ftoa(sum));
	printf("dif: %s\n",ftoa(dif));
	printf("prd: %s\n",ftoa(prd));
	printf("quo: %s\n",ftoa(quo));

    printf("%08f\n",a);

    system("pause");
    return 0;
}