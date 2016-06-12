class Tweet {
public:
  int id;
  int time;
  Tweet(int _id, int _time): id(_id), time(_time) {}
};

class User {
public:
  int uid;
  vector<Tweet> tweets;
  set<int> followed;
  User(int id): uid(id) { followed.insert({uid}); }
};

class Twitter {
public:
    map<int, User*> users;
    int time = 0;
    /** Initialize your data structure here. */
    Twitter() {
        time = 0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if(users.find(userId) == users.end()) {
            users.insert({userId, new User(userId)});
        }
        users[userId]->tweets.push_back(Tweet(tweetId, time++));
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        if(users.find(userId) == users.end()) {
            users.insert({userId, new User(userId)});
        }
        auto followed = users[userId]->followed;
        vector<pair<int, int>> points;
        for(auto user : followed) {
            if(users[user]->tweets.size() > 0)
                points.push_back({users[user]->uid, users[user]->tweets.size()-1});
        }
        vector<int> recent;
        auto cmp = [this](pair<int,int> a, pair<int,int> b) { return users[a.first]->tweets[a.second].time < users[b.first]->tweets[b.second].time; };
        make_heap(points.begin(), points.end(), cmp);
        for(int i = 0; i < 10 && points.size() > 0; i++) {
            auto top = points[0];
            pop_heap(points.begin(), points.end(), cmp);
            points.pop_back();
            recent.push_back(users[top.first]->tweets[top.second].id);
            if(--top.second >= 0) {
                points.push_back(top);
                push_heap(points.begin(), points.end(), cmp);
            }
        }
        return recent;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if(users.find(followerId) == users.end()) {
            users.insert({followerId, new User(followerId)});
        }
        if(users.find(followeeId) == users.end()) {
            users.insert({followeeId, new User(followeeId)});
        }
        users[followerId]->followed.insert({followeeId});
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(followerId == followeeId)
            return;
        if(users.find(followerId) == users.end()) {
            users.insert({followerId, new User(followerId)});
        }
        if(users.find(followeeId) == users.end()) {
            users.insert({followeeId, new User(followeeId)});
        }
        users[followerId]->followed.erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */
