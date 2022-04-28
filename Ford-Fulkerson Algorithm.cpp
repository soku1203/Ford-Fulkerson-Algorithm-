#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
const int V = 52; // 노드의 개수(a부터 Z까지의 개수)
const int IM = 1'000'000'000; // 매우 큰 수 

// 문자 A 부터 z 까지 정수로 변환하는 함수
int ctoi(char c) {
	if (c <= 'Z')
		return c - 'A';
	else
		return c - 'a' + 26;
}
int main()
{
	int c[V][V] = { 0 }; // 간선의 용량
	int f[V][V] = { 0 }; // 간선의 유량
	vector<int> adj[V]; // 인접 노드 리스트

	int N; // 간선의 개수
	cin >> N; // 간선의 개수 입력
	for (int i = 0; i < N; ++i)
	{
		// 노드 u,v와 용량 w
		char u, v;
		int w;
		cin >> u >> v >> w;
		u = ctoi(u); v = ctoi(v);
		c[u][v] = c[v][u] += w; // 간선의 용량
		adj[u].push_back(v); // 인접 노드 추가
		adj[v].push_back(u); // 역방향 노드 추가
	}
	int totalf = 0; // 총 유량
	int source = ctoi('A'); // 소스
	int sink = ctoi('Z'); // 싱크

	while (true)
	{
		// 증가 경로를 DFS로 찾는다.
		int prev[50]; // 경로 기록 배열
		memset(prev, -1, sizeof prev); // 배열을 -1로 초기화
		stack<int> s;
		s.push(source);
		// stack이 비거나 싱크에 도착할 때까지 반복
		while (!s.empty() && prev[sink] == -1) {
			int curr = s.top();
			s.pop();
			for (int next : adj[curr]) {
				// 인접 노드에 대하여 용량 - 유량이 0 이상이고 싱크에 도착하지 않았으면
				if (c[curr][next] - f[curr][next] > 0 && prev[next] == -1) {
					s.push(next); // 스택에 추가
					prev[next] = curr; // 경로저 장
					if (next == sink) break; // 싱크에 도착했을 경우 break
				}
			}
		}
		if (prev[sink] == -1)
			break; // 싱크로의 추가 경로가 없을 경우 break

		int flow = IM; // 플로우 변수에 INT_MAX값을 부여
		for (int i = sink; i != source; i = prev[i])
			flow = min(flow, c[prev[i]][i] - f[prev[i]][i]); // 플로우 변수에 증가 경로 상 최소값을 넣는다

		for (int i = sink; i != source; i = prev[i]) {
			f[prev[i]][i] += flow; // 증가 경로의 모든 간선에 플로우 값을 추가한다
			f[i][prev[i]] -= flow; // 역방향에는 음의 플로우 값을 추가한다.
		}
		totalf += flow; // 총 유량에 플로우를 추가시킨다.
	}

	cout << totalf; // 최대 플로우값 출력
}
