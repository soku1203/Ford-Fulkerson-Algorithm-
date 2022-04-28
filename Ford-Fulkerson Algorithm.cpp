#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
const int V = 52; // ����� ����(a���� Z������ ����)
const int IM = 1'000'000'000; // �ſ� ū �� 

// ���� A ���� z ���� ������ ��ȯ�ϴ� �Լ�
int ctoi(char c) {
	if (c <= 'Z')
		return c - 'A';
	else
		return c - 'a' + 26;
}
int main()
{
	int c[V][V] = { 0 }; // ������ �뷮
	int f[V][V] = { 0 }; // ������ ����
	vector<int> adj[V]; // ���� ��� ����Ʈ

	int N; // ������ ����
	cin >> N; // ������ ���� �Է�
	for (int i = 0; i < N; ++i)
	{
		// ��� u,v�� �뷮 w
		char u, v;
		int w;
		cin >> u >> v >> w;
		u = ctoi(u); v = ctoi(v);
		c[u][v] = c[v][u] += w; // ������ �뷮
		adj[u].push_back(v); // ���� ��� �߰�
		adj[v].push_back(u); // ������ ��� �߰�
	}
	int totalf = 0; // �� ����
	int source = ctoi('A'); // �ҽ�
	int sink = ctoi('Z'); // ��ũ

	while (true)
	{
		// ���� ��θ� DFS�� ã�´�.
		int prev[50]; // ��� ��� �迭
		memset(prev, -1, sizeof prev); // �迭�� -1�� �ʱ�ȭ
		stack<int> s;
		s.push(source);
		// stack�� ��ų� ��ũ�� ������ ������ �ݺ�
		while (!s.empty() && prev[sink] == -1) {
			int curr = s.top();
			s.pop();
			for (int next : adj[curr]) {
				// ���� ��忡 ���Ͽ� �뷮 - ������ 0 �̻��̰� ��ũ�� �������� �ʾ�����
				if (c[curr][next] - f[curr][next] > 0 && prev[next] == -1) {
					s.push(next); // ���ÿ� �߰�
					prev[next] = curr; // ����� ��
					if (next == sink) break; // ��ũ�� �������� ��� break
				}
			}
		}
		if (prev[sink] == -1)
			break; // ��ũ���� �߰� ��ΰ� ���� ��� break

		int flow = IM; // �÷ο� ������ INT_MAX���� �ο�
		for (int i = sink; i != source; i = prev[i])
			flow = min(flow, c[prev[i]][i] - f[prev[i]][i]); // �÷ο� ������ ���� ��� �� �ּҰ��� �ִ´�

		for (int i = sink; i != source; i = prev[i]) {
			f[prev[i]][i] += flow; // ���� ����� ��� ������ �÷ο� ���� �߰��Ѵ�
			f[i][prev[i]] -= flow; // �����⿡�� ���� �÷ο� ���� �߰��Ѵ�.
		}
		totalf += flow; // �� ������ �÷ο츦 �߰���Ų��.
	}

	cout << totalf; // �ִ� �÷ο찪 ���
}
