## Programming Test

**Feelings about programming**: Nothing special.

**Time cost**: 5 mins

**Source code**:

```c
#include<stdio.h>

double weightedAverage(double organization, double structure, double logic, double assembly, double embedded){
	organization=organization<60?0:organization;
	structure=structure<60?0:structure;
	logic=logic<60?0:logic;
	double wtd_avrg=organization+structure+logic+assembly*0.9+embedded*0.8;
	wtd_avrg/=1+1+1+0.9+0.8;
	if(wtd_avrg<organization*0.6) return organization*0.6;
	return wtd_avrg;
}
int main(){
	double organization,structure,logic,assembly,embedded;
	printf("Please input the score of organization coures: ");
	scanf("%lf",&organization);
	printf("Please input the score of structure course: ");
	scanf("%lf",&structure);
	printf("Please input the score of logic course: ");
	scanf("%lf",&logic);
	printf("Please input the score of assembly course: ");
	scanf("%lf",&assembly);
	printf("Please input the score of embedded course: ");
	scanf("%lf",&embedded);
	double wtd_avrg=weightedAverage(organization,structure,logic,assembly,embedded);
	printf("The weighted average score is: %f\n",wtd_avrg);
	return 0;
}
```

