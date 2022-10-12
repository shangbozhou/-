#include <bits/stdc++.h> 
using namespace std;
int min(int a,int b)
{
	if(a>=b) return b;
	return a;
} 
int min(int a,int b,int c,int d,int e)
{
	a=min(a,b);
	a=min(a,c);
	a=min(a,d);
	a=min(a,e);
	return a;
}
class orcs
{
	private:
		int life;
		int price[5];
		int army;
		int jundui[5];
		string name[5];
		int huihe;
		int lunci;
		int zhenying;
		int jieshu;
	public:
		orcs(int m,int one,int two,int three,int four,int five,int i);
		int tride();
		void output();
		int panduan();
};
orcs::orcs(int m,int one,int two,int three,int four,int five,int i)
{
	life=m;zhenying=i;lunci=0;jieshu=0;huihe=0;
	army=0;
	for(int k=0;k<=4;k++)
	{
		jundui[k]=0;
	}
	if(i==0)//red
	{
		price[0]=three; name[0]="iceman";
		price[1]=four;  name[1]="lion";
		price[2]=five;  name[2]="wolf";
		price[3]=two;   name[3]="ninja";
		price[4]=one;   name[4]="dragon";
	}
	else if(i==1)//blue
	{
		price[0]=four;  name[0]="lion";
		price[1]=one;   name[1]="dragon";
		price[2]=two;   name[2]="ninja";
		price[3]=three; name[3]="iceman";
		price[4]=five;  name[4]="wolf";
	}
}
int orcs::tride() 
{
	if(life>=min(price[0],price[1],price[2],price[3],price[4])) return 1;
	return 0;
}
int orcs::panduan()
{
	if(jieshu==0) return 0;
	return 1;
}
void orcs::output()  
{
	if(jieshu==1) return;
	if(huihe<=9) cout<<"00"<<huihe<<" ";
	else if(huihe>=10&&huihe<=99) cout<<"0"<<huihe<<" ";
	else cout<<huihe<<" ";
	if(zhenying==0) cout<<"red ";
	else if(zhenying==1) cout<<"blue ";
	if(tride()==0) 
	{
		cout<<"headquarter stops making warriors"<<endl;
		jieshu=1;
		return;
	}
	while(life<price[lunci])
	{
		lunci=(lunci+1)%5;
	}
	life=life-price[lunci];
	army++;jundui[lunci]++;
	cout<<name[lunci]<<" "<<army<<" born with strength "<<price[lunci]<<","<<jundui[lunci]<<" "<<name[lunci]<<" in ";
	if(zhenying==0) cout<<"red headquarter"<<endl;
	else if(zhenying==1) cout<<"blue headquarter"<<endl;
	lunci=(lunci+1)%5;
	huihe++;
	return;
}

int main()
{
	int cishu;
	cin>>cishu;
	for(int i=0;i<cishu;i++)
	{
		cout<<"Case:"<<i+1<<endl; 
		int mlife,o,t,s,f,fv;
		cin>>mlife>>o>>t>>s>>f>>fv;
		orcs red(mlife,o,t,s,f,fv,0),blue(mlife,o,t,s,f,fv,1);
		while((red.tride() ==1||blue.tride() ==1)||(red.tride() ==0&&blue.tride() ==0&&(blue.panduan() ==0||red.panduan() ==0)))
		{
			red.output() ;   
			blue.output() ;
		}  
	}
	return 0;
}
