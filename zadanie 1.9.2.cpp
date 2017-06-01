#include <stdio.h>    
#include <stdlib.h> 
#include <math.h>

typedef struct {
	float x,y;
}POINT;

typedef struct {
	float r;
	POINT c;
	
}CIRCLE;

typedef struct {
	float a,b,c;
	
}LINE;

float vzdialenost_bodov(int x1,int y1,int x2,int y2){
	float t;
	
	t=sqrt(pow((x1-x2),2)+pow((y1-y2),2));
	
	return t;
}



char circ_circ_inner_tangents(CIRCLE *c1, CIRCLE *c2, LINE *t1, LINE *t2){
	
	
	POINT a,b,c;
	float vzdialenost,l,d,uhol,vx1,vy1,vx2,vy2,vektorssX,vektorssY,medzi_vypocet,tolerancia=0.001;				//l->vzdialenost stredu kruznice od priesecniku kruznic, vzdialenost ->vzdialenost stredov kruznic,d->strana pravouhleho trojuhokniku
	
	
	vzdialenost=vzdialenost_bodov(c1->c.x,c1->c.y,c2->c.x,c2->c.y);												//vzdialenost stredov kruznic
	
	vektorssX=c2->c.x-c1->c.x;					
	vektorssY=c2->c.y-c1->c.y;																					//suradnice vektoru medzi stredmi kruznic

	if(c1->c.x==c2->c.x&&c1->c.y==c2->c.y&&c1->r==c2->r)	 return 0;

	else if(((vzdialenost<(c1->r+c2->r))&&(fabs(vzdialenost-fabs(c1->r-c2->r))>=tolerancia))||vzdialenost<abs(c1->r-c2->r))		return 0;	//v pripade ak nemaju ziadne vnutorne dotycnice

	else if(fabs(vzdialenost-fabs(c1->r+c2->r))<=tolerancia){  													//v pripade ak maju 1 vnutornu dotycnicu jedna kruznica nelezi v druhej
		
		
		medzi_vypocet=c1->c.x+(c1->r/(c1->r+c2->r));
		a.x=medzi_vypocet*(vektorssX);
		a.y=medzi_vypocet*(vektorssY);																			//bod dotiku kruznic
		
		t1->a=vektorssX;
		t1->b=vektorssY;
		t1->c=-(t1->a*a.x+t1->b*a.y);
		
		return 1;														
	}
	else if (fabs(vzdialenost-fabs(c1->r-c2->r))<=tolerancia){													//v pripade ak maju 1 vnutornu dotycnicu jedna kruznica lezi v druhej
		
		
	
		if(c1->r>c2->r){																						
			a.x=c2->c.x+((c1->r+vzdialenost)/(c1->r+c2->r))*(vektorssX);
			a.y=c2->c.y+((c1->r+vzdialenost)/(c1->r+c2->r))*(vektorssY);										//bod dotiku kruznic													
		}
		else{
			a.x=c1->c.x+(-(vzdialenost+c2->r)/(c1->r+c2->r))*(vektorssX);
			a.y=c1->c.y+(-(vzdialenost+c2->r)/(c1->r+c2->r))*(vektorssY);										//bod dotiku kruznic
		}
	
		t1->a=vektorssX;
		t1->b=vektorssY;
		t1->c=-(t1->a*a.x+t1->b*a.y);		
		
		return 1;
	}
	else if(vzdialenost>(c1->r+c2->r)){ 																		//v pripade ak maju  vnutorne dotycnice
		
	
	
	
		l=(c1->r*vzdialenost)/(c1->r+c2->r);																	//vzdialenost od priesecniku po stred jednej kruznice
	
		a.x=c1->c.x+l/vzdialenost*(vektorssX);
		a.y=c1->c.y+l/vzdialenost*(vektorssY);																	//bod presecniku dotycnic
		
		d=sqrt(pow(l,2)-pow(c1->r,2));																			//vzdialenost priesecniku a dotikoveho bodu
	
		uhol=acos((pow(l,2)+pow(d,2)-pow(c1->r,2))/(2*l*d));													//uhol doticnice kruznice a vektora medzi stredmi kruznic 
	
		vx1=cos(uhol)*vektorssX-sin(uhol)*vektorssY	;										
		vy1=sin(uhol)*vektorssX+cos(uhol)*vektorssY	;															//smerovy vektor prvej doticnice
	
		vx2=cos(-uhol)*vektorssX-sin(-uhol)*vektorssY;
		vy2=sin(-uhol)*vektorssX+cos(-uhol)*vektorssY;															//smerovy vektor druhej doticnice
		
		t1->a=-vy1;
		t1->b=vx1;
		t1->c=-(t1->a*a.x+t1->b*a.y);													
		
		t2->a=-vy2;	
		t2->b=vx2;
		t2->c=-(t2->a*a.x+t2->b*a.y);																			//vypocet koeficientov vseobecneho tvaru oboch priamok
	
		return 2;
	}	
}

main(){
	
	CIRCLE c1,c2;
	LINE l1,l2;
	int r1,r2,x1,y1,x2,y2;
	char d;
	float tolerancia=0.001;
	
	printf("zadaj polomer, x-ovu a y-ovu suradnicu prvej kruznice: ");
	scanf("%d%d%d",&x1,&y1,&r1);
	printf("zadaj polomer, x-ovu a y-ovu suradnicu druhej kruznice: ");
	scanf("%d%d%d",&x2,&y2,&r2);
	
	if(fabs(r1)<=tolerancia||fabs(r2)<=tolerancia) printf("zle zadany polomer");
	
	c1.r=r1;
	c1.c.x=x1;
	c1.c.y=y1;
	c2.r=r2;
	c2.c.x=x2;
	c2.c.y=y2;
	
	d=circ_circ_inner_tangents(&c1, &c2, &l1, &l2);
	printf("pocet dot %d",d);
}
