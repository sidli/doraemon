/*
 * File:   main.cpp
 * Author: JingW
 *
 * Created on
 */

#include<iostream>
#include<cstring>
#include<set>
#include<vector>
#include<algorithm>


using namespace std;

void findSteps(int step);

int ans,cntMap[5],cardsCnt[16];

vector<vector<int>> finalArr;
set<vector<vector<int>>> result;

void take(int n, int k, vector<int> &ansArr){
	cntMap[cardsCnt[k]]--;
	cardsCnt[k]-=n;
	cntMap[cardsCnt[k]]++;
	for(int i=0;i<n;i++){
		ansArr.push_back(k);
	}
}

void back(int n, int k, vector<int> & ansArr){
	cntMap[cardsCnt[k]]--;
	cardsCnt[k]+=n;
	cntMap[cardsCnt[k]]++;
	for(int i=0;i<n;i++){
		ansArr.pop_back();
	}
}

void proceedWithValueChanged(int step, int n, int k, vector<int> & ansArr){
	take(n,k,ansArr);
	finalArr.push_back(ansArr);
	findSteps(step+1);
	finalArr.pop_back();
	back(n,k,ansArr);
}

bool check(){
	for (int i=1;i<=4;++i){
	  if (cntMap[i]>0){
		  return false;
	  }
	}
	return true;
}

void findSteps(int step){
	int i,j,k,w,o,p,q,r,cnt;
	vector<int> ansArr;
	if (check()){
		vector<vector<int>> temp;
		for(int i=0;i<finalArr.size();i++){
			vector<int> buf(finalArr[i]);
			sort(buf.begin(),buf.end());
			temp.push_back(buf);
		}
		sort(temp.begin(),temp.end());
		result.emplace(temp);
	}

	if(step>=ans){
		return;
	}

	ans=min(ans,step+cntMap[1]+cntMap[2]+cntMap[3]+cntMap[4]);
	if(cntMap[4])for(i=2;i<=14;i++)if(cardsCnt[i]==4){
		take(4,i,ansArr);
		for(j=2;j<=15;j++)if(cardsCnt[j]){
			take(1,j,ansArr);
			for(k=j;k<=15;k++)if(cardsCnt[k]){
				proceedWithValueChanged(step,1,k,ansArr);
			}
			back(1,j,ansArr);
		}
		if(cntMap[2]||cntMap[3]||cntMap[4])for(j=2;j<=15;j++)if(cardsCnt[j]>=2){
			take(2,j,ansArr);
			for(k=j;k<=15;k++)if(cardsCnt[k]>=2){
				proceedWithValueChanged(step,2,k,ansArr);
			}
			back(2,j,ansArr);
		}
		back(4,i,ansArr);
	}
	if(cntMap[3])for(i=2;i<=14;i++)if(cardsCnt[i]>=3){
		take(3,i,ansArr);
		finalArr.push_back(ansArr);
		findSteps(step+1);
		finalArr.pop_back();
		for(j=2;j<=15;j++)if(cardsCnt[j]){
			proceedWithValueChanged(step,1,j,ansArr);
		}
		if(cntMap[2]||cntMap[3]||cntMap[4])for(j=2;j<=15;j++)if(cardsCnt[j]>=2){
			proceedWithValueChanged(step,2,j,ansArr);
		}
		back(3,i,ansArr);
	}
	if(cntMap[3]+cntMap[4]>=2)for(i=3;i<14;i++)if(cardsCnt[i]>=3&&cardsCnt[i+1]>=3){
		take(3,i,ansArr);
		for(j=i+1;cardsCnt[j]>=3&&j<=14;j++){
			take(3,j,ansArr);
			finalArr.push_back(ansArr);
			findSteps(step+1);
			finalArr.pop_back();
			w = j;
			cnt = j-i+1;
			if(cntMap[2]+cntMap[3]+cntMap[4]*2 >= cnt)for(o=2;o<=15;o++)if(cardsCnt[o]>=2){
				take(2,o,ansArr);
				for(p=o;p<=15;p++)if(cardsCnt[p]>=2){
					if(cnt ==2){
						proceedWithValueChanged(step,2,p,ansArr);
					}else if(cnt ==3){
						take(2,p,ansArr);
						for(q=p;q<=15;q++)if(cardsCnt[q]>=2){
							proceedWithValueChanged(step,2,q,ansArr);
						}
						back(2,p,ansArr);
					}else if(cnt ==4){
						take(2,p,ansArr);
						for(q=p;q<=15;q++)if(cardsCnt[q]>=2){
							take(2,q,ansArr);
							for(r=q;r<=15;r++)if(cardsCnt[r]>=2){
								proceedWithValueChanged(step,2,r,ansArr);
							}
							back(2,q,ansArr);
						}
						back(2,p,ansArr);
					}
				}
				back(2,o,ansArr);
			}
			if(cntMap[1]+cntMap[2]*2+cntMap[3]*3+cntMap[4]*4>=cnt){
				for(o=2;o<=15;o++)if(cardsCnt[o]>0){
					take(1,o,ansArr);
					for(p=o;p<=15;p++)if(cardsCnt[p]>0){
						if(cnt == 2){
							proceedWithValueChanged(step,1,p,ansArr);
						}else if(cnt == 3){
							take(1,p,ansArr);
							for(q=p;q<=15;q++)if(cardsCnt[q]>0){
								proceedWithValueChanged(step,1,q,ansArr);
							}
							back(1,p,ansArr);
						}else if(cnt ==4){
							take(1,p,ansArr);
							for(q=p;q<=15;q++)if(cardsCnt[q]>0){
								take(1,q,ansArr);
								for(r=q;r<=15;r++)if(cardsCnt[r]>0){
									proceedWithValueChanged(step,1,r,ansArr);
								}
								back(1,q,ansArr);
							}
							back(1,p,ansArr);
						}
					}
					back(1,o,ansArr);
				}
			}
		}
		for(j=i;j<=w;j++){
			back(3,j,ansArr);
		}
	}
	if(cntMap[2]+cntMap[3]+cntMap[4]>=3)for(i=3;i<13;i++)if(cardsCnt[i]>=2&&cardsCnt[i+1]>=2&&cardsCnt[i+2]>=2){
		take(2,i,ansArr);
		take(2,i+1,ansArr);
		for(j=i+2;cardsCnt[j]>=2&&j<=14;j++){
			take(2,j,ansArr);
			finalArr.push_back(ansArr);
			findSteps(step+1);
			finalArr.pop_back();
			w=j;
		}
		for(j=i;j<=w;j++){
			back(2,j,ansArr);
		}
	}
	if(cntMap[1]+cntMap[2]+cntMap[3]+cntMap[4]>=5)for(i=3;i<11;i++)if(cardsCnt[i]&&cardsCnt[i+1]&&cardsCnt[i+2]&&cardsCnt[i+3]&&cardsCnt[i+4]){
		take(1,i,ansArr);
		take(1,i+1,ansArr);
		take(1,i+2,ansArr);
		take(1,i+3,ansArr);
		for(j=i+4;cardsCnt[j]&&j<=14;j++){
			take(1,j,ansArr);
			finalArr.push_back(ansArr);
			findSteps(step+1);
			finalArr.pop_back();
			w=j;
		}
		for(j=i;j<=w;j++){
			back(1,j,ansArr);
		}
	}
	if(cntMap[2])for(i=2;i<=15;i++)if(cardsCnt[i]==2){
		proceedWithValueChanged(step,2,i,ansArr);
	}
	if(cntMap[1])for(i=2;i<=15;i++)if(cardsCnt[i]>0){
		proceedWithValueChanged(step,1,i,ansArr);
	}
}

int PlayCard(char * cards){
	int x;
	char y;
	memset(cardsCnt,0,sizeof(cardsCnt));
	memset(cntMap,0,sizeof(cntMap));

	for(int i=0; i<17; i++){
		y=cards[i];
		switch (y){
		case 'S':
			x = 10;
			break;
		case 'J':
			x = 11;
			break;
		case 'Q':
			x = 12;
			break;
		case 'K':
			x = 13;
			break;
		case 'A':
			x = 14;
			break;
		case 'W':
			x = 15;
			break;
		default:
			x = y-'0';
			break;
		}
		cardsCnt[x]++;
	}

	for(int i=2;i<=15;i++){
		if(cardsCnt[i]){
			ans++;
		}
		cntMap[cardsCnt[i]]++;
	}
	findSteps(0);
	printf("%d\n",ans);
	for(auto it = result.begin();it!=result.end();++it){
		if(it->size()==ans){
			for(int i=0;i<it->size();i++){
				for(int j=0;j<(*it)[i].size();j++){
					switch ((*it)[i][j]){
						case 10:
							y = 'S';
							break;
						case 11:
							y = 'J';
							break;
						case 12:
							y = 'Q';
							break;
						case 13:
							y = 'K';
							break;
						case 14:
							y = 'A';
							break;
						case 15:
							y = 'W';
							break;
						default:
							y = (*it)[i][j]+'0';
							break;
						}
					printf("%c",y);
				}
				printf(" ");
			}
			printf("\n");
		}
	}
	return 0;
}



int main(int argc, char** argv){
	char cards[18]={0};
	for(int i=0;i<17;i++){
		cin >> cards[i];
	}
	return PlayCard(cards);
	/*int x;
	char y;
	memset(cardsCnt,0,sizeof(cardsCnt));
	memset(cntMap,0,sizeof(cntMap));

	for(int i=0; i<17; i++){
		cin >> y;
		switch (y){
		case 'S':
			x = 10;
			break;
		case 'J':
			x = 11;
			break;
		case 'Q':
			x = 12;
			break;
		case 'K':
			x = 13;
			break;
		case 'A':
			x = 14;
			break;
		case 'W':
			x = 15;
			break;
		default:
			x = y-'0';
			break;
		}
		cardsCnt[x]++;
	}

	for(int i=2;i<=15;i++){
		if(cardsCnt[i]){
			ans++;
		}
		cntMap[cardsCnt[i]]++;
	}
	findSteps(0);
	printf("%d\n",ans);
	for(auto it = result.begin();it!=result.end();++it){
		if(it->size()==ans){
			for(int i=0;i<it->size();i++){
				for(int j=0;j<(*it)[i].size();j++){
					switch ((*it)[i][j]){
						case 10:
							y = 'S';
							break;
						case 11:
							y = 'J';
							break;
						case 12:
							y = 'Q';
							break;
						case 13:
							y = 'K';
							break;
						case 14:
							y = 'A';
							break;
						case 15:
							y = 'W';
							break;
						default:
							y = (*it)[i][j]+'0';
							break;
						}
					printf("%c",y);
				}
				printf(" ");
			}
			printf("\n");
		}
	}*/
}
