#include "test_runner.h"
#include "profile.h"
#include "paginator.h"

#include <map>
#include <sstream>
#include <string>
#include <future>
using namespace std;

string operator*(const string& s, unsigned int n) {
	string result;
	result.reserve(s.size() * n);
	for (size_t i = 0; i < n; ++i) {
		result += s;
	}
	return result;
}

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (const auto& [key, value] : other.word_frequences) {
			word_frequences[key] += value;
		}
	}
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	stringstream ss(line);
	string word;
	while (ss >> word) {
		if (key_words.count(word) != 0) {
			++result.word_frequences[word];
		}
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
	Stats result;
	for (string line; getline(input, line); ) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreVector(const set<string>& key_words, const vector<string>& data) {
	Stats result;
	for (const auto& line : data) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	const size_t max_size = 5000;
	vector<string> lines;
	lines.reserve(max_size);
	vector<future<Stats>> futures;
	Stats result;

	for (string line; getline(input, line); ) {
		lines.push_back(line);
		if (lines.size() >= max_size) {
			futures.push_back(async(ExploreVector, ref(key_words), move(lines)));
		}
	}

	if (!lines.empty()) {
		result += ExploreVector(key_words, lines);
	}

	for (auto& f : futures) {
		result += f.get();
	}
	return result;
}

void TestBasic() {
	const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
		{"yangle", 6},
		{"rocks", 2},
		{"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

void StressTest() {
	{
		const set<string> key_words = { "yangle", "rocks", "sucks", "all" };
		stringstream ss;
		string yangle = "yangle ";
		yangle = (yangle * 1000 + '\n') * 5000;
		string rocks = "rocks ";
		rocks = (rocks * 1000 + '\n') * 5000;
		string sucks = "sucks ";
		sucks = (sucks * 1000 + '\n') * 5000;
		string all = "all ";
		all = (all * 1000 + '\n') * 5001;
		ss << yangle;
		ss << rocks;
		ss << sucks;
		ss << all;
		{
			LOG_DURATION("Multi thread");
			const auto stats = ExploreKeyWords(key_words, ss);
			const map<string, int> expected = {
				{"yangle", 5000000},
				{"rocks", 5000000},
				{"sucks", 5000000},
				{"all", 5001000},
			};
			ASSERT_EQUAL(stats.word_frequences, expected);
		}
	}
	{
		const set<string> key_words = { "yangle", "rocks", "sucks", "all" };
		stringstream ss;
		string yangle = "yangle ";
		yangle = (yangle * 1000 + '\n') * 5000;
		string rocks = "rocks ";
		rocks = (rocks * 1000 + '\n') * 5000;
		string sucks = "sucks ";
		sucks = (sucks * 1000 + '\n') * 5000;
		string all = "all ";
		all = (all * 1000 + '\n') * 5000;
		ss << yangle;
		ss << rocks;
		ss << sucks;
		ss << all;
		{
			LOG_DURATION("Single thread");
			const auto stats = ExploreKeyWordsSingleThread(key_words, ss);
			const map<string, int> expected = {
				{"yangle", 5000000},
				{"rocks", 5000000},
				{"sucks", 5000000},
				{"all", 5000000},
			};
			ASSERT_EQUAL(stats.word_frequences, expected);
		}
	}
}

int main() {
	TestRunner tr;
	// RUN_TEST(tr, TestBasic);
	RUN_TEST(tr, StressTest);
}