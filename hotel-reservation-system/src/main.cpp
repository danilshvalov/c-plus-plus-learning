#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <numeric>
#include <deque>
#include <iterator>
#include <queue>

#include "test_runner.h"
#include "profile.h"

using namespace std;

struct Hotel {
	int64_t time;
	int roomCount;
	vector<int> clientList;
};

ostream& operator<<(ostream& os, const Hotel& h) {
	return os << "{count: " << h.roomCount << ", clients: " << h.clientList << "}";
}

int TIME = 86400;

// TODO сделать deque и хранить на него итераторы в queue;

class Database {
private:
	unordered_map<int, int> clientsAndRooms_;
public:
	void Book(int64_t time, string& hotelName, int clientId, int roomCount) {
		currentTime_ = time;
		if (data_.size() != 0 && data_.back().first == time) {
			auto& hotel = data_.back().second[hotelName];
			hotel.roomCount += roomCount;
			hotel.clientList.push_back(clientId);
		} else {
			data_.push_back({ time, {{hotelName, {roomCount, {clientId}}}} });
			iterators_.push(prev(data_.end()));
		}

		while (iterators_.front()->first <= currentTime_ - TIME) {
			iterators_.pop();
		}
	}
	int Clients(const string& hotelName) {
		vector<int> clientsIds;
		auto copyHotels = iterators_;
		while (!copyHotels.empty()) {
			for (const auto& client : copyHotels.front()->second[hotelName].clientList) {
				clientsIds.push_back(client);
			}
			copyHotels.pop();
		}

		sort(clientsIds.begin(), clientsIds.end());
		auto last = unique(clientsIds.begin(), clientsIds.end());
		clientsIds.erase(last, clientsIds.end());
		return clientsIds.size();
	}
	int Rooms(const string& hotelName) {
		int counter = 0;
		auto copyHotels = iterators_;
		while (!copyHotels.empty()) {
			counter += copyHotels.front()->second[hotelName].roomCount;
			copyHotels.pop();
		}
		return counter;
	}
};

int main() {
	Database db;

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		string command;
		cin >> command;

		string hotelName;
		int64_t time;
		int clientId, roomCount;

		if (command == "BOOK") {
			cin >> time >> hotelName >> clientId >> roomCount;
			db.Book(time, hotelName, clientId, roomCount);
		} else if (command == "CLIENTS") {
			cin >> hotelName;
			cout << db.Clients(hotelName) << endl;
		} else if (command == "ROOMS") {
			cin >> hotelName;
			cout << db.Rooms(hotelName) << endl;
		}
	}
}