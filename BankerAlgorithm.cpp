#include <iostream>
#include <string>
using namespace std;

int Available[3] = { 3,3,2 };//系统可用资源 
int Max[5][3] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };//进程最大资源需求量 
int Allocation[5][3] = { {0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2} };//系统已经给进程分配的资源 
int Need[5][3] = { {7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1} };//进程的资源最大需求量 
int Work[3];//系统可提供给进程继续运行所需要的各类资源数目
string Finish[5] = { "false" ,"false" , "false" , "false" , "false" };
int SafeArray[5];//安全序列 
int Request[3];//请求资源向量 

void Show() {
	cout << "T0时刻的系统资源分配情况如下：" << endl;
	cout << "进程名\tMax\t\tAllocation\tNeed\t\tAvailable" << endl;
	for (int i = 0; i < 5; i++) {
		cout << "P" << i << "\t";
		for (int j = 0; j < 3; j++) {
			cout << Max[i][j] << " ";
		}
		cout << "\t\t";
		for (int j = 0; j < 3; j++) {
			cout << Allocation[i][j] << " ";
		}
		cout << "\t\t";
		for (int j = 0; j < 3; j++) {
			cout << Need[i][j] << " ";
		}
		cout << "\t\t";
		if (i == 0) {
			for (int j = 0; j < 3; j++) {
				cout << Available[j] << " ";
			}
		}
		cout << endl;
	}
}
void SafeLine() {
	cout << "当前系统处于安全状态..." << endl;
	cout << "其中一个安全序列为：";
	for (int i = 0; i < 5; i++) {
		if (i == 4)cout << "P" << SafeArray[i];
		else cout << "P" << SafeArray[i] << "-->";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) {
		Finish[i] = "false";
	}
}

int NeedLessWork(int n) {
	for (int i = 0; i < 3; i++) {
		if (Work[i] < Need[n][i]) {
			return 0;
		}
	}
	return 1;
}
void ShowSafe(int i) {
	cout << "P" << i << "\t";
	for (int j = 0; j < 3; j++) {
		cout << Work[j] << " ";
	}
	cout << "\t\t";
	for (int j = 0; j < 3; j++) {
		cout << Need[i][j] << " ";
	}
	cout << "\t\t";
	for (int j = 0; j < 3; j++) {
		cout << Allocation[i][j] << " ";
	}
	cout << "\t\t";
	for (int j = 0; j < 3; j++) {
		cout << Work[j] + Allocation[i][j] << " ";
	}
	cout << "\t\t";
	cout << Finish[i];
	cout << endl;

}
void IsSafe(int n) {
	for (int i = 0; i < 5; i++) {
		if (Finish[i] == "false" && NeedLessWork(i)) {
			Finish[i] = "true";
			SafeArray[n] = i;
			n++;
			ShowSafe(i);
			for (int j = 0; j < 3; j++) {
				Work[j] += Allocation[i][j];
			}
			break;
		}

	}
	int mult = 1;
	//如果五个标志都为1即都已经完成，则打印安全序列，否则继续执行安全性检查算法 
	for (int k = 0; k < 5; k++) {
		if (Finish[k] == "false")
			mult *= 0;
		else
			mult *= 1;
	}
	if (mult == 0) {
		IsSafe(n);
	}
	else {
		SafeLine();
	}
}
void SafeCheck() {
	cout << "试探着将资源分配给它后，系统安全情况分析如下：" << endl;
	cout << "进程\tWork\t\tNeed\t\tAllocation\tWork+Allocation\tFinish" << endl;
	for (int i = 0; i < 3; i++) {
		Work[i] = Available[i];
	}
	IsSafe(0);
}

int RequestLessNeed(int n) {
	for (int i = 0; i < 3; i++) {
		if (Request[i] > Need[n][i]) {
			return 0;
		}
	}
	return 1;
}
int RequestLessAvailable(int n) {
	for (int i = 0; i < 3; i++) {
		if (Request[i] > Available[i]) {
			return 0;}
	}
	return 1;
}
void RequestResourse() {
	cout << "请输入发出资源请求的进程：";
	int n;
	cin >> n;
	cout << "请依次输入所请求的资源数量：";
	for (int i = 0; i < 3; i++) {
		cin >> Request[i];
	}
	if (RequestLessNeed(n)) {
		if (RequestLessAvailable(n)) {
			for (int i = 0; i < 3; i++) {
				Allocation[n][i] += Request[i];
				Available[i] -= Request[i];
				Need[n][i] -= Request[i];
			}
			SafeCheck();
		}
		else {
			cout << "P" << n << "请求的资源向量已超过系统可用资源向量，请求失败！让其继续等待..." << endl;
			cout << "-------------------------------------------------------------------" << endl;
			return;
		}
	}
	else {
		cout << "P" << n << "请求的资源向量已超过其最大需求向量，请求失败！让其继续等待..." << endl;
		cout << "-------------------------------------------------------------------" << endl;
		return;
	}
}

int main()
{
	cout << "*************************银行家算法的模拟*************************" << endl;
	cout << "    \t\t\t1.显示当前系统资源情况" << endl;
	cout << "    \t\t\t2.进程发出请求向量" << endl;
	cout << "    \t\t\t3.退出系统" << endl;
	cout << "******************************************************************" << endl;
	while (true) {
		int choose;
		cout << "请选择你要执行的操作：";
		cin >> choose;
		switch (choose) {
		case 1:
			Show();//展示当前系统资源分配情况 
			break;
		case 2:
			RequestResourse();//处理进程发出的资源请求 
			break;
		case 3:
			cout << "已退出系统！" << endl;
			return 0;
		default:
			cout << "输入错误，请重新输入！" << endl;
			continue;
		}
	}
}