#include <bits/stdc++.h> 
using namespace std;
int M,N,R,K,T;
class city;
class sword
{
	public:
		int gongjili;//������
		sword():gongjili(0){}//��ʼֵΪ0 
		int gethurt()//���ú�������ʱ�Զ��ۻ� 
		{
			int g=gongjili;
			gongjili=gongjili*0.8;
			return g;
		} 
		void change(int gg)//��öԷ�������Ϊgg��sword
		{
			gongjili=gg;
			return;
		}
};
class arrow
{
	public:
		int gongjili;//������ 
		int shouming;//��ʹ�ô��� 
		arrow():shouming(0),gongjili(R){}
		int gethurt()//����Ϊ0ʱ����0������������-1 
		{
			if(shouming==0) return 0;
			shouming--;
			return gongjili;
		} 
		void change(int cc)//��öԷ���ʹ��cc�ε�arrow 
		{
			shouming=cc;
			return;
		} 
}; 
class hero
{
	public:
		int num;//��ʿ���
		int life;//��ʿ����
		int fight;//��ʿ������
		sword jian;//sword 
		arrow gong;//arrow
		int bomb;//����bomb��Ϊ1����û�У���Ϊ0 
		int zhenying;
		city* mycity;//���ڳ���ָ�� 
		int zhongcheng;//lion�ã�������ʿ��Ϊ100 
		int zengzhi;//lion����ʹ�ã���������Ϊ0 
		string name;//��ʿ���� 
		double shiqi;//ʿ��
		hero(int n,int l,int f,int t,city* cc):num(n),life(l),fight(f),bomb(0),zhenying(t),mycity(cc),zengzhi(0),zhongcheng(100),shiqi(0){}
		//bolΪ�Ƿ���bomb1Ϊ��0Ϊ��,��Ӫ��Ϊ1����Ϊ-1 
		virtual int attack()//�������� 
		{
			return fight+jian.gethurt() ;
		}
		int beattack()//�������� 
		{
			if(name=="ninja") return 0;
			return fight/2+jian.gethurt() ;
		}
		virtual void behurt(int h)//���˺���
		{
			life-=h;
			return;
		} 
		virtual void walk(city* ct)//��ʿ�н� 
		{
			mycity=ct;
			return;
		}
		virtual void beifen(){}//lion����ı�Է�����ֵʱ�ã���Ҫ��ս��ǰ����
		virtual void beipan(){}//lion�ı��ҳ϶� 
		virtual void jiaohuo(const hero loser){}//wolfʤ����ɻ�����ʱʹ��
		virtual void changeshiqi(int t){}//�ı�dragonʿ�� 
};
class dragon:public hero
{
	public:
		dragon(int n,int l,int f,int t,double shi,city* cc):hero(n,l,f,t,cc)//shiΪ����õ�ʿ��ֵ 
		{
			shiqi=shi;
			name="dragon";
			if(n%3==0) jian.change(f*0.2);
			else if(n%3==1) bomb=1;
			else if(n%3==2) gong.change(3);
			cout<<"Its morale is ";
			printf("%0.2lf\n",shiqi);
			//cout<<fixed<<setprecision(2)<<shiqi<<endl;
		}
		virtual void changeshiqi(int t)//1ΪӮ-1Ϊ��Ӯ 
		{
			if(t==1) shiqi+=0.2;
			else if(t==-1) shiqi-=0.2;
			return;
		}
};
class ninja:public hero
{
	public:
		ninja(int n,int l,int f,int t,city* cc):hero(n,l,f,t,cc)
		{
			name="ninja";
			if(n%3==0) jian.change(f*0.2);
			else if(n%3==1) bomb=1;
			else if(n%3==2) gong.change(3);
			if((n+1)%3==0) jian.change(f*0.2);
			else if((n+1)%3==1) bomb=1;
			else if((n+1)%3==2) gong.change(3);
		}	
};
class iceman:public hero
{
	public:
		int jishu;
		iceman(int n,int l,int f,int t,city* cc):hero(n,l,f,t,cc)
		{
			name="iceman";
			jishu=0;
			if(n%3==0) jian.change(f*0.2);
			else if(n%3==1) bomb=1;
			else if(n%3==2) gong.change(3);
		}
		virtual void walk(city* ct)
		{
			hero::walk(ct); 
			jishu++;
			if(jishu%2==0)
			{
				life=max(life-9,1);
				fight+=20;
			}
			return;
		}
};
class lion:public hero
{
	public:
		lion(int n,int l,int f,int t,int z,city* cc):hero(n,l,f,t,cc)//zΪ�ҳ϶� 
		{
			name="lion";
			zhongcheng=z;
			zengzhi=life;
			cout<<"Its loyalty is "<<z<<endl;
		}
		virtual void beipan()
		{
			zhongcheng-=K;
		} 
		virtual void beifen()
		{
			zengzhi=life;
			return;
		}
};
class wolf:public hero
{
	public:
		wolf(int n,int l,int f,int t,city* cc):hero(n,l,f,t,cc){name="wolf";}
		virtual void jiaohuo(const hero loser)
		{
			if(jian.gongjili==0) jian.change(loser.jian.gongjili);
			if(gong.shouming==0) gong.change(loser.gong.shouming);
			if(bomb==0) bomb=loser.bomb;
			return;
		}
};
class tribe
{
	public:
	int soul;//����Ԫ 
	int zhenying;//��Ӫ ��Ϊ1����Ϊ-1
	int life[5];//��ʿ���� 
	int fight[5];//��ʿ������ 
	string wushi[5];//��ʿ���� 
	int shu;//�Ѳ�������ʿ���� ����ʼΪ0 
	int enemy;//���˸�������ʼ��Ϊ0 
	int beiyongsoul;//����Ԫ���� 
	hero* xianqu;//�洢�ȵ����Ӫ����ʿ 
	tribe(int t,int l1,int l2,int l3,int l4,int l5,int f1,int f2,int f3,int f4,int f5)//;i=1Ϊ��,i=-1Ϊ�� 
		{
			soul=M;
			zhenying=t;
			shu=0;enemy=0;
			beiyongsoul=soul;
			xianqu=NULL;
			if(t==1) 
			{
				wushi[0]="iceman";wushi[1]="lion";wushi[2]="wolf";wushi[3]="ninja";wushi[4]="dragon";
				life[0]=l3;
				life[1]=l4;
				life[2]=l5;
				life[3]=l2;
				life[4]=l1;
				fight[0]=f3;
				fight[1]=f4;
				fight[2]=f5;
				fight[3]=f2;
				fight[4]=f1;
			}
			else if (t==-1) 
			{
				wushi[0]="lion";wushi[1]="dragon";wushi[2]="ninja";wushi[3]="iceman";wushi[4]="wolf";
				life[0]=l4;
				life[1]=l1;
				life[2]=l2;
				life[3]=l3;
				life[4]=l5;
				fight[0]=f4;
				fight[1]=f1;
				fight[2]=f2;
				fight[3]=f3;
				fight[4]=f5;
			}
		}
	hero* zhizao(int lunci,city* cc)
	{
		if(soul<life[lunci]) return NULL;
		shu++; soul-=life[lunci];
		cout<<":00 ";
		if(zhenying==1) cout<<"red ";
		else if(zhenying==-1) cout<<"blue ";
		cout<<wushi[lunci]<<" "<<shu<<" born"<<endl;                       
		if(zhenying==1)
		{                       
			if(lunci==0) 
			{
				iceman* ic=new iceman(shu,life[lunci],fight[lunci],zhenying,cc);
				return ic;
			}
			else if(lunci==1) 
			{
				lion* li=new lion(shu,life[lunci],fight[lunci],zhenying,soul,cc);
				return li;
			}
			else if(lunci==2)
			{
				wolf* wo=new wolf(shu,life[lunci],fight[lunci],zhenying,cc);
				return wo;
			}
			else if(lunci==3)
			{
				ninja* ni=new ninja(shu,life[lunci],fight[lunci],zhenying,cc);
				return ni;
			}
			else if(lunci==4)
			{
				double m=double(soul)/double(life[lunci]);   //cout<<"soul:"<<soul<<" life:"<<life[lunci]<<" morale:"<<m<<endl;
				dragon* dr=new dragon(shu,life[lunci],fight[lunci],zhenying,m,cc);
				return dr;
			}
		}
		else if(zhenying==-1)
		{                                                                                                
			if(lunci==3) 
			{
				iceman* ic=new iceman(shu,life[lunci],fight[lunci],zhenying,cc);
				return ic;
			}
			else if(lunci==0) 
			{
				lion* li=new lion(shu,life[lunci],fight[lunci],zhenying,soul,cc);
				return li;
			}
			else if(lunci==4)
			{
				wolf* wo=new wolf(shu,life[lunci],fight[lunci],zhenying,cc);
				return wo;
			}
			else if(lunci==2)
			{
				ninja* ni=new ninja(shu,life[lunci],fight[lunci],zhenying,cc);
				return ni;
			}
			else if(lunci==1)
			{
				double m=double(soul)/double(life[lunci]);   // cout<<"soul:"<<soul<<" life:"<<life[lunci]<<" morale:"<<m<<endl;
				dragon* dr=new dragon(shu,life[lunci],fight[lunci],zhenying,m,cc);
				return dr;
			}
		}
	}
	void huibao(int t)//��Ӫ���t������Ԫ
	{
		soul+=t;
	} 
};
class city
{
	public:
	int num;//���
	int soul;//��������Ԫ
	hero* red;
	hero* blue;//����ʿָ��
	city* rednext;
	city* bluenext;//����ʿ��һλ��ָ�� 
	int flag;//����1Ϊ�죬0Ϊ�ޣ�-1Ϊ��
	int flagjilu;//��¼����Ĺ���
	int Flag;//��¼��ʵ�Ƿ���� 
	city():num(0),soul(0),red(NULL),blue(NULL),rednext(NULL),bluenext(NULL),flag(0),flagjilu(0),Flag(0){}
	void shengchan()//���в�������Ԫ 
	{
		soul+=10;
		return;
	}
	int jielue()//��ʿ��ó�������Ԫ 
	{
		int tmp=soul;
		soul=0;
		return tmp;
	}
};
bool yupan(hero a,hero b,int t)//a�ж� t=1Ϊa������t=-1Ϊb���� 
{
	if(t==1)
	{                     //cout<<"t=1"<<endl;
		if(b.life-a.attack()<=0) return false;//cout<<"1111111  "<<a.life<<" "<<b.beattack()<<endl;
		if(a.life-b.beattack()<=0) return true;//cout<<"222222222"<<endl;
		return false;
	}	
	else if(t==-1)
	{         // cout<<"t=-1"<<endl;
		if(a.life-b.attack()<=0) return true;//cout<<"*********"<<endl;
		return false;
	}
}
int main()
{
	int cishu;
	cin>>cishu;
	for(int ww=0;ww<cishu;ww++)
	{
		cout<<"Case "<<ww+1<<":"<<endl; 
		int l1,l2,l3,l4,l5,f1,f2,f3,f4,f5;
		cin>>M>>N>>R>>K>>T>>l1>>l2>>l3>>l4>>l5>>f1>>f2>>f3>>f4>>f5;
		tribe redtribe(1,l1,l2,l3,l4,l5,f1,f2,f3,f4,f5);
		tribe bluetribe(-1,l1,l2,l3,l4,l5,f1,f2,f3,f4,f5);
		city cheng[25];
		for(int i=0;i<=N;i++) 
		{
			cheng[i].num=i;
			cheng[i].rednext= &cheng[i+1];
		}
		for(int i=1;i<=N+1;i++)
		{
			cheng[i].num=i;
			cheng[i].bluenext= &cheng[i-1];
		}
		cheng[0].bluenext=NULL;
		cheng[N+1].rednext=NULL; 
		for(int i=1;i<=N;i++)
		{
			if(i%2==1) cheng[i].flag=1;
			else cheng[i].flag =-1;
		}
		int time=T/60;int yutime=T%60;//cout<<setw(3)<<setfill('0')
		int t=0;
		int luncir=0;int luncib=0;
		while(t<=time)
		{
			//00���� 
			if(t==time&&yutime<0) break;
			if(redtribe.soul>=redtribe.life[luncir])
			{
				cout<<setw(3)<<setfill('0')<<t;
				cheng[0].red =redtribe.zhizao(luncir,&cheng[0]);                                  
				luncir=(luncir+1)%5;
			}
			if(bluetribe.soul>=bluetribe.life[luncib])
			{
				cout<<setw(3)<<setfill('0')<<t;
				cheng[N+1].blue =bluetribe.zhizao(luncib,&cheng[N+1]);
				luncib=(luncib+1)%5;
			}  
			//05���� 
			if(t==time&&yutime<5) break;  
			for(int i=0;i<=N+1;i++)
			{                                 
				if(i!=N+1)
				{       
					if(cheng[i].red!=NULL)
					{                       
					if(cheng[i].red->zhongcheng<=0)
					{
						cout<<setw(3)<<setfill('0')<<t;
						cout<<":05 red lion "<<cheng[i].red->num <<" ran away"<<endl;	
						cheng[i].red=NULL;  
					}  
					}                       
				}                           
				if(i!=0)
				{
					if(cheng[i].blue !=NULL)
					{
					if(cheng[i].blue->zhongcheng<=0)
					{
						cout<<setw(3)<<setfill('0')<<t;
						cout<<":05 blue lion "<<cheng[i].blue->num<<" ran away"<<endl;
						cheng[i].blue=NULL; 	  
					}
					}
				}
			}
			//10�н�
			if(t==time&&yutime<10) break;
			int zhongju=0;
			for(int i=N;i>=0;i--)
			{
				if(i==N&&cheng[i].red!=NULL) 
				{
					bluetribe.enemy++;
					if(cheng[N+1].red!=NULL)
					{             
						bluetribe.xianqu=cheng[N+1].red;
					}
				}
				if(cheng[i].red!=NULL) cheng[i].red->walk(cheng[i].rednext); 
				if(cheng[i].rednext!=NULL) cheng[i].rednext->red=cheng[i].red;
				if(cheng[i].red!=NULL) cheng[i].red=NULL; 
			}
			for(int i=1;i<=N+1;i++)
			{
				if(i==1&&cheng[i].blue!=NULL) 
				{
					redtribe.enemy++;//cout<<"*****"<<endl;
					if(cheng[0].blue!=NULL)
					{                                                                                              
						redtribe.xianqu=cheng[0].blue;
					}
				}
				if(cheng[i].blue!=NULL)cheng[i].blue->walk(cheng[i].bluenext); 
				if(cheng[i].bluenext!=NULL) cheng[i].bluenext->blue=cheng[i].blue;
				if(cheng[i].blue!=NULL)cheng[i].blue=NULL;
			}
			if(cheng[0].blue!=NULL)
			{
				cout<<setw(3)<<setfill('0')<<t;
				cout<<":10 blue "<<cheng[0].blue->name<<" "<<cheng[0].blue->num<<" reached red headquarter with ";
				cout<<cheng[0].blue->life<<" elements and force "<<cheng[0].blue->fight<<endl;
				redtribe.xianqu=cheng[0].blue ;
				cheng[0].blue =NULL;
			}
			if(redtribe.enemy==2)
			{
				cout<<setw(3)<<setfill('0')<<t;
				cout<<":10 red headquarter was taken"<<endl;
				zhongju=1;
			}
			for(int i=1;i<N+1;i++)
			{
				if(cheng[i].red!=NULL)
				{
					cout<<setw(3)<<setfill('0')<<t;
					cout<<":10 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" marched to city "<<i;
					cout<<" with "<<cheng[i].red->life<<" elements and force "<<cheng[i].red->fight<<endl;
				}
				if(cheng[i].blue!=NULL)
				{
					cout<<setw(3)<<setfill('0')<<t;
					cout<<":10 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" marched to city "<<i;
					cout<<" with "<<cheng[i].blue->life<<" elements and force "<<cheng[i].blue->fight<<endl;
				}
			} 
			if(cheng[N+1].red!=NULL)
			{
				cout<<setw(3)<<setfill('0')<<t;
				cout<<":10 red "<<cheng[N+1].red->name<<" "<<cheng[N+1].red->num<<" reached blue headquarter with ";
				cout<<cheng[N+1].red->life<<" elements and force "<<cheng[N+1].red->fight<<endl;
				bluetribe.xianqu=cheng[N+1].red ;
				cheng[N+1].red =NULL;
			}  
			if(bluetribe.enemy==2)
			{
				cout<<setw(3)<<setfill('0')<<t;
				cout<<":10 blue headquarter was taken"<<endl;
				zhongju=1;
			}   
			if(zhongju==1) break;
			//20����
			if(t==time&&yutime<20) break;
			for(int i=1;i<=N;i++)
			{
				cheng[i].shengchan() ;
			} 
			//30���� 
			if(t==time&&yutime<30) break;
			for(int i=1;i<=N;i++)
			{
				if(cheng[i].red!=NULL&&cheng[i].blue==NULL)
				{
					cout<<setw(3)<<setfill('0')<<t;
					cout<<":30 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" earned "<<cheng[i].soul<<" elements for his headquarter"<<endl;
					redtribe.huibao(cheng[i].jielue()); 
				}
				else if(cheng[i].red==NULL&&cheng[i].blue!=NULL)
				{
					cout<<setw(3)<<setfill('0')<<t;
					cout<<":30 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" earned "<<cheng[i].soul<<" elements for his headquarter"<<endl;
					bluetribe.huibao(cheng[i].jielue()); 
				}
			} 
			//35�ż�
			if(t==time&&yutime<35) break;
			for(int i=0;i<=N+1;i++)
			{
				if(i!=N+1&&i!=N)
				{
					if(cheng[i].red!=NULL&&cheng[i].rednext->blue!=NULL)
					{
						if(cheng[i].red->gong.shouming>0)
						{
							cout<<setw(3)<<setfill('0')<<t;
							cout<<":35 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" shot"; 
							cheng[i].rednext->blue->behurt(cheng[i].red->gong.gethurt()); 
							if(cheng[i].rednext->blue->life<=0) cout<<" and killed blue "<<cheng[i].rednext->blue->name<<" "<<cheng[i].rednext->blue->num;
							cout<<endl;
						}
					}
				}
				if(i!=0&&i!=1)
				{
					if(cheng[i].blue!=NULL&&cheng[i].bluenext->red!=NULL)
					{
						if(cheng[i].blue->gong.shouming>0)
						{
							cout<<setw(3)<<setfill('0')<<t;
							cout<<":35 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" shot"; 
							cheng[i].bluenext->red->behurt(cheng[i].blue->gong.gethurt()); 
							if(cheng[i].bluenext->red->life<=0) cout<<" and killed red "<<cheng[i].bluenext->red->name<<" "<<cheng[i].bluenext->red->num;
							cout<<endl;
						}
					}
				}
			}
			//38��ɱ
			if(t==time&&yutime<38) break;
			for(int i=1;i<=N;i++)
			{
				if(cheng[i].blue!=NULL&&cheng[i].red!=NULL&&cheng[i].red->life>0&&cheng[i].blue->life>0)
				{
					int gju=0;
					if(cheng[i].red->bomb==1)
					{                     // cout<<yupan(*cheng[i].red,*cheng[i].blue,cheng[i].flag)<<endl;
						if(yupan(*cheng[i].red,*cheng[i].blue,cheng[i].flag))
						{  
							cout<<setw(3)<<setfill('0')<<t;
							cout<<":38 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" used a bomb and killed blue ";
							cout<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<endl; 
							gju=1;
						} 
					}
					if(cheng[i].blue->bomb==1)
					{
						if(yupan(*cheng[i].blue,*cheng[i].red,-cheng[i].flag))
						{
							cout<<setw(3)<<setfill('0')<<t;
							cout<<":38 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" used a bomb and killed red ";
							cout<<cheng[i].red->name<<" "<<cheng[i].red->num<<endl; 
							gju=1;
						} 
					}
					if(gju==1)
					{
						cheng[i].red=NULL;
						cheng[i].blue=NULL;
					}
				}
			}
			//40ս��
			if(t==time&&yutime<40) break; 
			int shengfu[25];
			int ggg[25];
			memset(shengfu,0,sizeof(shengfu));
			memset(ggg,0,sizeof(ggg));
			redtribe.beiyongsoul=redtribe.soul;
			bluetribe.beiyongsoul=bluetribe.soul;
			for(int i=1;i<=N;i++)//ս�� 
			{
				if(cheng[i].red!=NULL&&cheng[i].blue==NULL&&cheng[i].red->life<=0) cheng[i].red=NULL;
				if(cheng[i].blue!=NULL&&cheng[i].red==NULL&&cheng[i].blue->life<=0) cheng[i].blue=NULL;
				if(cheng[i].red!=NULL&&cheng[i].blue!=NULL)
				{
					if(cheng[i].red->name=="lion") cheng[i].red->zengzhi=cheng[i].red->life;
					if(cheng[i].blue->name=="lion") cheng[i].blue->zengzhi=cheng[i].blue->life;
					shengfu[i]=0;
					if(cheng[i].red->life<=0&&cheng[i].blue->life<=0)
					{
						shengfu[i]=0;ggg[i]=1;
					} 
					else if(cheng[i].red->life>0&&cheng[i].blue->life<=0) shengfu[i]=1;
					else if(cheng[i].red->life<=0&&cheng[i].blue->life>0) shengfu[i]=-1;
					else
					{               
						if(cheng[i].flag==1)
						{
							cout<<setw(3)<<setfill('0')<<t;
							cout<<":40 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" attacked ";
							cout<<"blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" in city "<<i<<" with ";
							cout<<cheng[i].red->life<<" elements and force "<<cheng[i].red->fight<<endl;
							cheng[i].blue->behurt(cheng[i].red->attack());
							if(cheng[i].blue->life<=0) 
							{
								shengfu[i]=1;
								cout<<setw(3)<<setfill('0')<<t;
								cout<<":40 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" was killed in city "<<i<<endl;
							}
							else
							{
								if(cheng[i].blue->name!="ninja")
								{
								cout<<setw(3)<<setfill('0')<<t;
								cout<<":40 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" fought back against red ";
								cout<<cheng[i].red->name<<" "<<cheng[i].red->num<<" in city "<<i<<endl;
								}
								cheng[i].red->behurt(cheng[i].blue->beattack());
								if(cheng[i].red->life<=0) 
								{
									cout<<setw(3)<<setfill('0')<<t;
									cout<<":40 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" was killed in city "<<i<<endl;
									shengfu[i]=-1; 
								}
								else shengfu[i]=0;
							} 
						}
						else if(cheng[i].flag==-1)
						{
							cout<<setw(3)<<setfill('0')<<t;
							cout<<":40 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" attacked ";
							cout<<"red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" in city "<<i<<" with ";
							cout<<cheng[i].blue->life<<" elements and force "<<cheng[i].blue->fight<<endl;
							cheng[i].red->behurt(cheng[i].blue->attack());
							if(cheng[i].red->life<=0) 
							{
								shengfu[i]=-1;
								cout<<setw(3)<<setfill('0')<<t;
								cout<<":40 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" was killed in city "<<i<<endl;
							}
							else
							{
								if(cheng[i].red->name!="ninja")
								{
								cout<<setw(3)<<setfill('0')<<t;
								cout<<":40 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" fought back against blue ";
								cout<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" in city "<<i<<endl;
								}
								cheng[i].blue->behurt(cheng[i].red->beattack());
								if(cheng[i].blue->life<=0) 
								{
									cout<<setw(3)<<setfill('0')<<t;
									cout<<":40 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" was killed in city "<<i<<endl;
									shengfu[i]=1; 
								}
								else shengfu[i]=0;
							} 
						}		
					}
					if(cheng[i].flag==1&&cheng[i].red->life>0&&cheng[i].red->shiqi>0.8)//dragon���� 
					{
						cout<<setw(3)<<setfill('0')<<t;
						cout<<":40 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" yelled in city "<<i<<endl;
					}  
					else if(cheng[i].flag==-1&&cheng[i].blue->life>0&&cheng[i].blue->shiqi>0.8)
					{
						cout<<setw(3)<<setfill('0')<<t;
						cout<<":40 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" yelled in city "<<i<<endl;
					}
					if(shengfu[i]==1)//��ʿ�������Ԫ
					{
						cout<<setw(3)<<setfill('0')<<t;
						cout<<":40 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" earned "<<cheng[i].soul<<" elements for his headquarter"<<endl;
						redtribe.huibao(cheng[i].jielue());
					}
					else if(shengfu[i]==-1)
					{
						cout<<setw(3)<<setfill('0')<<t;
						cout<<":40 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" earned "<<cheng[i].soul<<" elements for his headquarter"<<endl;
						bluetribe.huibao(cheng[i].jielue()); 
					}
					if(shengfu[i]==1)//���lion���� 
					{
						cheng[i].red->life+=max(cheng[i].blue->zengzhi,0);
					}
					else if(shengfu[i]==-1)
					{
						cheng[i].blue->life+=max(cheng[i].red->zengzhi,0);
					}
					if(shengfu[i]==0||shengfu[i]==-1) cheng[i].red->beipan();//lion�ı��ҳ� 
					if(shengfu[i]==0||shengfu[i]==1) cheng[i].blue->beipan();
					if(shengfu[i]==1) cheng[i].red->jiaohuo(*cheng[i].blue) ;//wolf�ɻ����� 
					else if(shengfu[i]==-1) cheng[i].blue->jiaohuo(*cheng[i].red); 
					cheng[i].red->changeshiqi(shengfu[i]);//�ı�dragonʿ�� 
					cheng[i].blue->changeshiqi(-shengfu[i]);
					if(shengfu[i]==1&&redtribe.beiyongsoul>=8)//��ʿ��ý��� 
						{
							cheng[i].red->life+=8;
							redtribe.soul-=8;
							redtribe.beiyongsoul-=8; 
						} 
					if(shengfu[i]==-1&&bluetribe.beiyongsoul>=8)
					{
						cheng[i].blue->life+=8;
						bluetribe.soul-=8; 
						bluetribe.beiyongsoul-=8;
					}//��������    
					//	cout<<"s:"<<shengfu[i]<<" j:"<<cheng[i].flagjilu<<" F:"<<cheng[i].Flag<<" f:"<<cheng[i].flag<<endl;                                                        
					if(ggg[i]==1) {}
					else if(cheng[i].flagjilu==0) cheng[i].flagjilu+=shengfu[i];
					else if(shengfu[i]==0) cheng[i].flagjilu=0;
					else if(cheng[i].flagjilu==-shengfu[i]) cheng[i].flagjilu=shengfu[i];
					else if(cheng[i].flagjilu==shengfu[i])
					{
						cheng[i].flag=shengfu[i];
						if(cheng[i].Flag!=cheng[i].flag)
						{
						cout<<setw(3)<<setfill('0')<<t;
						if(shengfu[i]==1) cout<<":40 red flag raised in city "<<i<<endl;
						else if(shengfu[i]==-1) cout<<":40 blue flag raised in city "<<i<<endl;
						cheng[i].Flag=cheng[i].flag;
						}
						cheng[i].flagjilu=0;
					}
				}
			} 
			for(int i=1;i<=N;i++)//ʧ�ܷ����� 
			{
				if(shengfu[i]==1)
				{
					cheng[i].blue=NULL;
				}
				else if(shengfu[i]==-1)
				{
					cheng[i].red=NULL;
				}
				if(ggg[i]==1)
				{
					cheng[i].blue=NULL;
					cheng[i].red=NULL;
				}
			}
			//50����
			if(t==time&&yutime<50) break;
			cout<<setw(3)<<setfill('0')<<t;
			cout<<":50 "<<redtribe.soul<<" elements in red headquarter"<<endl; 
			cout<<setw(3)<<setfill('0')<<t;
			cout<<":50 "<<bluetribe.soul<<" elements in blue headquarter"<<endl; 
			//55�ϱ�
			if(t==time&&yutime<55) break;
			for(int i=0;i<=N+1;i++)
			{                 
				if(cheng[i].red!=NULL) 
				{            
					cout<<setw(3)<<setfill('0')<<t;
					cout<<":55 red "<<cheng[i].red->name<<" "<<cheng[i].red->num<<" has ";
					if(cheng[i].red->bomb==0&&cheng[i].red->jian.gongjili==0&&cheng[i].red->gong.shouming==0) cout<<"no weapon"<<endl;
					else
					{
					int gongju=0;
					if(cheng[i].red->gong.shouming!=0)
					{
						if(gongju!=0) cout<<",";
						gongju++;
						cout<<"arrow("<<cheng[i].red->gong.shouming<<")";
					}	
					if(cheng[i].red->bomb!=0)
					{
						if(gongju!=0) cout<<",";
						gongju++;
						cout<<"bomb";
					}
					if(cheng[i].red->jian.gongjili!=0)
					{                                                        
						if(gongju!=0) cout<<",";
						gongju++;
						cout<<"sword("<<cheng[i].red->jian.gongjili<<")";
					}                                
					cout<<endl;
					}//cout<<cheng[i].red->zhongcheng<<endl; 
				}
			} 
			if(bluetribe.xianqu!=NULL)
			{
				cout<<setw(3)<<setfill('0')<<t;
				cout<<":55 red "<<bluetribe.xianqu->name<<" "<<bluetribe.xianqu->num<<" has ";
				if(bluetribe.xianqu->bomb==0&&bluetribe.xianqu->jian.gongjili==0&&bluetribe.xianqu->gong.shouming==0) cout<<"no weapon"<<endl;
				else
				{
				int gongju=0;
				if(bluetribe.xianqu->gong.shouming!=0)
				{
					if(gongju!=0) cout<<",";
					gongju++;
					cout<<"arrow("<<bluetribe.xianqu->gong.shouming<<")";
				}	
				if(bluetribe.xianqu->bomb!=0)
				{
					if(gongju!=0) cout<<",";
					gongju++;
					cout<<"bomb";
				}
				if(bluetribe.xianqu->jian.gongjili!=0)
				{                                                        
					if(gongju!=0) cout<<",";
					gongju++;
					cout<<"sword("<<bluetribe.xianqu->jian.gongjili<<")";
				}
				cout<<endl;
				}
			} 
            if(redtribe.xianqu!=NULL)
			{                               
				cout<<setw(3)<<setfill('0')<<t;
				cout<<":55 blue "<<redtribe.xianqu->name<<" "<<redtribe.xianqu->num<<" has ";
				if(redtribe.xianqu->bomb==0&&redtribe.xianqu->jian.gongjili==0&&redtribe.xianqu->gong.shouming==0) cout<<"no weapon"<<endl;
				else
				{
				int gongju=0;
				if(redtribe.xianqu->gong.shouming!=0)
				{
					if(gongju!=0) cout<<",";
					gongju++;
					cout<<"arrow("<<redtribe.xianqu->gong.shouming<<")";
				}	
				if(redtribe.xianqu->bomb!=0)
				{
					if(gongju!=0) cout<<",";
					gongju++;
					cout<<"bomb";
				}
				if(redtribe.xianqu->jian.gongjili!=0)
				{                                                        
					if(gongju!=0) cout<<",";
					gongju++;
					cout<<"sword("<<redtribe.xianqu->jian.gongjili<<")";
				}
				cout<<endl;
				}
			}
			for(int i=0;i<=N+1;i++)
			{
				if(cheng[i].blue !=NULL) 
				{
					cout<<setw(3)<<setfill('0')<<t;
					cout<<":55 blue "<<cheng[i].blue->name<<" "<<cheng[i].blue->num<<" has ";
					if(cheng[i].blue->bomb==0&&cheng[i].blue->jian.gongjili==0&&cheng[i].blue->gong.shouming==0) cout<<"no weapon"<<endl;
					else
					{
						int gongju=0;
					if(cheng[i].blue->gong.shouming!=0)
					{
						if(gongju!=0) cout<<",";
						gongju++;
						cout<<"arrow("<<cheng[i].blue->gong.shouming<<")";
					}	
					if(cheng[i].blue->bomb!=0)
					{
						if(gongju!=0) cout<<",";
						gongju++;
						cout<<"bomb";
					}
					if(cheng[i].blue->jian.gongjili!=0)
					{
						if(gongju!=0) cout<<",";
						gongju++;
						cout<<"sword("<<cheng[i].blue->jian.gongjili<<")";
					}                            
					cout<<endl;
					}//cout<<cheng[i].blue->zhongcheng <<endl;
				}
			}
			t++;   
		}  
	}
 	return 0;
}
