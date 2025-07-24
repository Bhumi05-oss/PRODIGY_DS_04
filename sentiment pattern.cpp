#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

// Load positive or negative words into a set
unordered_set<string> loadWordSet(const string& filename) {
    unordered_set<string> wordSet;
    ifstream file(filename);
    string word;
    while (getline(file, word)) {
        wordSet.insert(word);
    }
    return wordSet;
}

// Convert to lowercase
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Tokenize a sentence into words
vector<string> tokenize(const string& sentence) {
    stringstream ss(sentence);
    string word;
    vector<string> tokens;
    while (ss >> word) {
        tokens.push_back(toLower(word));
    }
    return tokens;
}

// Analyze sentiment
int analyzeSentiment(const string& text, const unordered_set<string>& positiveWords, const unordered_set<string>& negativeWords) {
    vector<string> tokens = tokenize(text);
    int score = 0;
    for (const string& word : tokens) {
        if (positiveWords.count(word)) score++;
        else if (negativeWords.count(word)) score--;
    }
    return score;
}

int main() {
    // Load word lists
    unordered_set<string> positiveWords = loadWordSet("positive.txt");
    unordered_set<string> negativeWords = loadWordSet("negative.txt");

    ifstream file("tweets.csv");
    string line;
    int tweetCount = 0, positive = 0, negative = 0, neutral = 0;

    cout << "Tweet Sentiment Analysis:\n--------------------------\n";
    while (getline(file, line)) {
        tweetCount++;
        int score = analyzeSentiment(line, positiveWords, negativeWords);
        string label;
        if (score > 0) {
            label = "Positive";
            positive++;
        } else if (score < 0) {
            label = "Negative";
            negative++;
        } else {
            label = "Neutral";
            neutral++;
        }
        cout << "Tweet #" << tweetCount << " [" << label << "]: " << line << "\n";
    }

    cout << "\nSummary:\n";
    cout << "Total Tweets: " << tweetCount << "\n";
    cout << "Positive: " << positive << "\n";
    cout << "Negative: " << negative << "\n";
    cout << "Neutral : " << neutral << "\n";

    return 0;
}