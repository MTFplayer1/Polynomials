#include <bits/stdc++.h>
#include <vector>
using namespace std;

void reszta(vector <long double>& wsp, vector <long double>::iterator it, vector <long double>& wspp, int a, vector <long double>& wsppp, vector <long double>& wspppp){
	wsppp.clear();
	wspppp.clear();
	for(int i=0;i<wsp.size();i++){
		wsppp.push_back(wsp[i]);
	}
	for(int i=0;i<wspp.size();i++){
		wspppp.push_back(wspp[i]);
	}
	for(int j=0;j<100;j++){
		long double abc=wsp[0];
		long double abcd=wspp[0];
		for(int i=0;i<wspp.size();i++){
			long double minus=((abc)/(abcd))*wspp[i];
			wsp[i]=wsp[i]-minus;
		}
		while(abs(wsp[0])<0.00001){
			if(wsp.size()==1){
				break;
			}
			wsp.erase(wsp.begin());
		}
		if(wsp.size()<wspp.size()){
			break;
		}
	}
}


long double potega(long double y, int yy){
	long double k=1;
	for(int i=0;i<yy;i++){
		k=k*y;
	}
	return k;
}


void ciagisturma(vector <long double> wsp, vector <long double>::iterator it, long double pom, long double pomm, long double y, long double yz, vector <long double>& S, vector <long double>& Sprim, vector <long double> wspp, int a, vector <long double> wsppp, vector <long double> wspppp){
	S.clear();
	Sprim.clear();
	for(int i=0;i<wsp.size();i++){
		pom=pom+wsp[i]*potega(y,wsp.size()-1-i);
		pomm=pomm+wsp[i]*potega(yz,wsp.size()-1-i);
	}
	S.push_back(pom);
	Sprim.push_back(pomm);
	for(int i=0;i<100000;i++){
		pom=0;
		pomm=0;
		for(int j=0;j<wspp.size();j++){
			pom=pom + wspp[j]*potega(y,wspp.size()-1-j);
			pomm=pomm + wspp[j]*potega(yz,wspp.size()-1-j);
		}
		S.push_back(pom);
		Sprim.push_back(pomm);
		pom=0;
		pomm=0;
		if(abs(wspp[0])<0.0001){
			break;
		}
		reszta(wsp,it,wspp,a,wsppp,wspppp);
			wspp.clear();
			for(int j=0;j<wsp.size();j++){
				wspp.push_back(-1*wsp[j]);
			}
			wsp.clear();
			for(int j=0;j<wspppp.size();j++){
				wsp.push_back(wspppp[j]);
			}
	}
}


int zmianyznakow(vector <long double> S){
	int k=0;
	for(int i=0;i<S.size()-1;i++){
		if(S[i]*S[i+1]<-0.0001){
			k=k+1;
		}
	}
	return k;
}


long double msczero(long double y, long double yz, int a, vector <long double> wsp){
	long double wp=0;
	long double wk=0;
	long double ws=0;
	long double pp=y;
	long double kk=yz;
	long double ss=(pp+kk)/2;
	for(int d=0;d<9999;d++){
		if(kk-pp<=0.000000001){
			return pp;
			break;
		}
		for(int m=0;m<a+1;m++){
			wp=wp+potega(pp,a-m)*wsp[m];
			wk=wk+potega(kk,a-m)*wsp[m];
			ws=ws+potega(ss,a-m)*wsp[m];
		}if (wp*ws>0){
			pp=ss;
			ss=(pp+kk)/2;
		}if (wk*ws>0){
			kk=ss;
			ss=(pp+kk)/2;
		}if (ws==0){
			return ss;
			break;
		}	
		wp=0;
		ws=0;
		wk=0;
		}
}


int main(){
	///////////////////////////////////////DEKLARACJE ZMIENNYCH//////////////////////////////////////////////////////////////
	
	long double y,yz,m,yprim,yzprim;
	cout<<"Wpisz poczatek zakresu"<<endl;
	cin>>y;
	cout<<"Wpisz koniec zakresu"<<endl;
	cin>>yz;
	long double pom=0;
	long double pomm=0;
	vector <long double> wsp;
	vector <long double>::iterator it;
	vector <long double> wspp;
	vector <long double> wsppp;
	vector <long double> wspppp;
	cout<<"Wpisz najwyzsza potege wielomianu:"<<endl;
	int a;
	cin>>a;
	long double T[a+1];
	for(int i=0;i<a+1;i++){
		T[i]=0;
	}
	int zero=1;
	T[0]=y;
	vector <long double> S;
	vector <long double> Sprim;
	long double wp=0;
	long double wk=0;
	
	/////////////////////////////////////////WCZYTYWANIE///////////////////////////////////////////////////////
	
	for(int i=0;i<a+1;i++){
		cout<<"Wpisz wspolczynnik przy x^"<<a-i<<endl;
		int x;
		cin>>x;
		wsp.push_back(x);
	}
	for(int i=0;i<a;i++){
		int x=wsp[i]*(a-i);
		wspp.push_back(x);
	}
	
	/////////////////////////////////////////KOD////////////////////////////////////////////////////////
	

	ciagisturma(wsp,it,pom,pomm,y,yz,S,Sprim,wspp,a,wsppp,wspppp);
	int ile=zmianyznakow(S)-zmianyznakow(Sprim);
	if(zmianyznakow(S)-zmianyznakow(Sprim)==0){
		cout<<"Brak miejsc zerowych na zadanym przedziale";
	}else{
		for(int j=0;j<ile+1;j++){
			if(j!=0){
				cout<<T[j]<<endl;
			}
			ciagisturma(wsp,it,pom,pomm,T[j]+0.001,yz,S,Sprim,wspp,a,wsppp,wspppp);
			if(zmianyznakow(S)-zmianyznakow(Sprim)==0){
				break;
			}
			yzprim=yz;
			yprim=T[j];
			for(int z=0;z<100000;z++){	//Tw. Taylora
				wp=0;
				wk=0;
				ciagisturma(wsp,it,pom,pomm,yprim,yzprim,S,Sprim,wspp,a,wsppp,wspppp);
				if(zmianyznakow(S)-zmianyznakow(Sprim)>0){
					for(int i=0;i<wsp.size();i++){
						wp=wp+wsp[i]*potega(yprim,wsp.size()-1-i);
						wk=wk+wsp[i]*potega(yzprim,wsp.size()-1-i);
					}
					if(wp*wk<0){
						m=msczero(yprim,yzprim,a,wsp);
						ciagisturma(wsp,it,pom,pomm,yprim,m-0.001,S,Sprim,wspp,a,wsppp,wspppp);
						
						if(zmianyznakow(S)-zmianyznakow(Sprim)==0){
							T[j+1]=m+0.00001;
							zero=zero+1;
							break;
						}else{
						yzprim=m;
						}
					}else{
						yzprim=(yprim+yzprim)/2;
					}
				}else{
					long double zmop=abs(yzprim-yprim);
					yprim=yzprim;
					yzprim=yzprim+zmop;
				}
				
			}
		}
	}
	ciagisturma(wsp,it,pom,pomm,yprim,yzprim,S,Sprim,wspp,a,wsppp,wspppp);		
}
