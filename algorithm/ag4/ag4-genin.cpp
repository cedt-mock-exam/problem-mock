#include "jngen.h" // Make sure jngen.h is in the same directory or in your include path
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <string>

struct Edge {
	int u;
	int v;
	long long w;
	int type;
};

struct CaseSpec {
	int idx;
	int minN;
	int maxN;
	int minM;
	int maxM;
	int minK;
	int maxK;
	bool sameColor;
	bool equalPrefixStarts;
	int altFriends;
};

static void shuffleEdges(std::vector<Edge>& edges) {
	for(int i = static_cast<int>(edges.size()) - 1; i > 0; --i) {
		int j = rnd.next(0, i);
		std::swap(edges[i], edges[j]);
	}
}

static void generateCase(const CaseSpec& spec, long long maxWeight) {
	int n = rnd.next(spec.minN, spec.maxN);
	int m = rnd.next(spec.minM, spec.maxM);
	int k = rnd.next(spec.minK, spec.maxK);

	const int meeting = n;
	std::vector<int> starts(k);
	if(spec.equalPrefixStarts && k > 1) {
		for(int i=0;i<k-1;i++) starts[i] = 1;
		int last = std::min(meeting-1, k + 1);
		if(last < 2) last = 2;
		starts[k-1] = last;
	} else {
		for(int i=0;i<k;i++) starts[i] = i + 1;
	}

	std::vector<Edge> edges;
	edges.reserve(m);

	auto addEdge = [&](int u, int v, long long w, int type) {
		if(static_cast<int>(edges.size()) >= m) return;
		edges.push_back({u, v, w, type});
	};

	const long long baseWeight = 600000000LL;
	const long long tiePenalty = 200000LL;
	const long long chainExtra = 5000000LL;
	const long long randomMin = baseWeight + 8000000LL;
	const long long randomMax = std::min(maxWeight, baseWeight + 20000000LL);

	int tieLimit = spec.sameColor ? 0 : std::min(spec.altFriends, k);
	for(int i=0;i<k;i++) {
		long long direct = baseWeight + i * 5000LL;
		addEdge(starts[i], meeting, direct, 0);
		if(!spec.sameColor) {
			long long directOther = (i < tieLimit) ? direct : (direct + tiePenalty + i * 300LL);
			addEdge(starts[i], meeting, directOther, 1);
		}
	}

	for(int u=1; u<n && static_cast<int>(edges.size()) < m; ++u) {
		int v = u + 1;
		if(v > n) break;
		int color = spec.sameColor ? 0 : (u & 1);
		addEdge(u, v, baseWeight + chainExtra + u, color);
	}

	while(static_cast<int>(edges.size()) < m) {
		int u = rnd.next(1, std::max(1, n - 1));
		int v = rnd.next(1, n);
		if(u == v) continue;
		int color = spec.sameColor ? 0 : rnd.next(0, 1);
		long long w = rnd.next(randomMin, randomMax);
		addEdge(u, v, w, color);
	}

	shuffleEdges(edges);

	std::ofstream fout(std::to_string(spec.idx) + ".in");
	if(!fout) {
		std::cerr << "Failed to create " << spec.idx << ".in\n";
		return;
	}

	fout << n << " " << m << " " << k << " " << meeting << "\n";
	for(const auto& e : edges) {
		fout << e.u << " " << e.v << " " << e.w << " " << e.type << "\n";
	}
	for(int i=0;i<k;i++) {
		fout << starts[i] << " ";
	}

	std::cerr << "Generated " << spec.idx << ".in with N=" << n
			  << ", M=" << edges.size() << ", K=" << k << std::endl;
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	const long long maxWeight = 1000000000LL;

	std::vector<CaseSpec> cases = {
		{1,   950,  1000, 1800,  2000, 1,  1, false, false, 0},
		{2,  1001,  2000, 1500,  2000, 3,  4, true,  false, 0},
		{3,  3500,  3800, 8000,  9000, 6,  8, false, false, 3},
		{4,  3801,  4200, 8500,  9500, 7,  9, false, false, 3},
		{5,  4201,  4600, 9000,  9800, 8, 10, false, false, 4},
		{6,  4601,  5000, 9500, 10000, 9, 10, false, false, 5},
		{7, 90000, 93000,90000, 99000,10, 12, false, false, 5},
		{8, 93001, 96000,95000,100000,12, 14, false, false, 6},
		{9, 96001, 99000,96000,100000,16, 18, false, true,  6},
		{10,99001,100000,97000,100000,18, 20, false, true,  8},
		{11,450000,452000,491000,494000,20,20, false, false,10},
		{12,452001,454500,492000,495000,21,21, false, false,12},
		{13,454501,456500,493000,495500,22,22, false, false,14},
		{14,456501,458500,494000,496000,20,20, false, false,8},
		{15,458501,460500,495000,497000,21,21, false, false,15},
		{16,460501,462500,496000,498000,22,22, false, false,12},
		{17,462501,464500,497000,499000,20,20, false, false,11},
		{18,464501,466500,497500,499200,21,21, false, false,13},
		{19,466501,468500,498000,499500,22,22, false, false,17},
		{20,500000,500000,500000,500000,22,22, false, false,18}
	};

	for(const auto& spec : cases) {
		generateCase(spec, maxWeight);
	}

	return 0;
}

