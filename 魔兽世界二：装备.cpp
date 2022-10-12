#include <bits/stdc++.h> 
using namespace std;
string tool[3]={"sword","bomb","arrow"};
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
class hero
{
	protected:
		int num;//±àºÅ
		int life;//ÊÙÃü
	public:
		virtual void output()=0;
		hero(int n,int l):num(n),life(l){} 
		virtual ~hero(){}
};
class dragon:public hero
{
	protected:
		string wuqi;
		float shiqi;
	public:
		dragon(int n,int l,int m):hero(n,l),wuqi(tool[n%3]),shiqi((float)m/(float)l){}
		virtual void output()
		{
			cout<<"It has a "<<wuqi<<",and it's morale is "<<fixed<<setprecision(2)<<shiqi<<endl;
		}
};
class ninja:public hero
{
	protected:
		string wuqi1;
		string wuqi2;
	public:
		ninja(int n,int l):hero(n,l),wuqi1(tool[n%3]),wuqi2(tool[(n+1)%3]){}
		virtual void output()
		{
			cout<<"It has a "<<wuqi1<<" and a "<<wuqi2<<endl;
		}
};
class iceman:public hero
{
	protected:
		string wuqi;
	public:
		iceman(int n,int l):hero(n,l),wuqi(tool[n%3]){}
		virtual void output()
		{
			cout<<"It has a "<<wuqi<<endl;
		}
};
class lion:public hero
{
	protected:
		int zhongcheng;
	public:
		lion(int n,int l,int m):hero(n,l),zhongcheng(m){}
		virtual void output()
		{
			cout<<"It's loyalty is "<<zhongcheng<<endl;
		}
};
class wolf:public hero
{
	public:
		wolf(int n,int l):hero(n,l){}
		virtual void output(){}
};

class orcs
{
	private:
		int soul;
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
	soul=m;zhenying=i;lunci=0;jieshu=0;huihe=0;
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
int orcs::tride() //ÅĞ¶ÏÊÇ·ñÄÜ¹»³ö±ø 
{
	if(soul>=min(price[0],price[1],price[2],price[3],price[4])) return 1;
	return 0;
}
int orcs::panduan()//ÅĞ¶ÏÊ±ºòÊä³ö½áÊø 
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
	while(soul<price[lunci])
	{
		lunci=(lunci+1)%5;
	}
	soul=soul-price[lunci];
	army++;jundui[lunci]++;
	char nam=name[lunci][0];
	dragon a(army,price[lunci],soul);
	ninja b(army,price[lunci]);
	iceman c(army,price[lunci]);
	lion d(army,price[lunci],soul);
	wolf e(army,price[lunci]);
	hero* he;
	if(nam=='d') he=&a;
	else if (nam=='n') he=&b;
	else if (nam=='i') he=&c;
	else if (nam=='l') he=&d;
	else if (nam=='w') he=&e;
	cout<<name[lunci]<<" "<<army<<" born with strength "<<price[lunci]<<","<<jundui[lunci]<<" "<<name[lunci]<<" in ";
	if(zhenying==0) cout<<"red headquarter"<<endl;
	else if(zhenying==1) cout<<"blue headquarter"<<endl;
	he->output() ;
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
		int msoul,o,t,s,f,fv;
		cin>>msoul>>o>>t>>s>>f>>fv;
		orcs red(msoul,o,t,s,f,fv,0),blue(msoul,o,t,s,f,fv,1);
		while((red.tride() ==1||blue.tride() ==1)||(red.tride() ==0&&blue.tride() ==0&&(blue.panduan() ==0||red.panduan() ==0)))
		{
			red.output() ;   
			blue.output() ;
		}  
	}
	return 0;
}
